#include "RendererComponent.h"
#include "../Entity/Entity.h"
#include "../Camera.h"
#include "../Scene.h"

RendererComponent::RendererComponent(Entity* entity) : Component(entity)
{
    m_Shader = new Shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");
    m_Shader->Bind();
    m_Texture = new Texture("res/images/CubeFace.png");

    Mesh::setCubeData(m_Vertices);

    // init the VAO and VBO
    GLCall(glGenVertexArrays(1, &m_VAO));
    GLCall(glBindVertexArray(m_VAO));

    GLCall(glGenBuffers(1, &m_VBO));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW));

    // Position attribute
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0));
    GLCall(glEnableVertexAttribArray(0));

    // TexCoord attribute
    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, Vertex::texCoord))));
    GLCall(glEnableVertexAttribArray(1));

    GLCall(glBindVertexArray(0)); // Unbind VAO
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Unbind VBO

}

void RendererComponent::Render()
{
    m_Shader->Bind();

    // Bind Textures using texture units
    m_Texture->Bind();
    m_Shader->SetUniform1i("ourTexture1", 0);

    GLCall(glBindVertexArray(m_VAO));

    Camera* camera= GetEntity()->GetScene()->GetCamera();
    glm::mat4 model = GetEntity()->GetTransform()->GetWorldMatrix();
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(camera->GetFov(), (GLfloat)camera->GetWidth() / (GLfloat)camera->GetHeight(), 0.1f, 1000.0f);

    // Set world matrices 
    m_Shader->SetUniformMat4f("model", model);
    m_Shader->SetUniformMat4f("view", view);
    m_Shader->SetUniformMat4f("projection", projection);

    for (GLuint i = 0; i < 6; i++)
    {
        // Calculate the model matrix for each object and pass it to shader before drawing
        m_Shader->SetUniform3f("faceColor", glm::vec3(0.05f, 0.25f, 0.7f));
        GLCall(glDrawArrays(GL_TRIANGLES, i * 6, 6));
    }

    GLCall(glBindVertexArray(0));
}
