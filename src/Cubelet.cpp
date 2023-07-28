#include "Cubelet.h"

#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\transform.hpp"
#include <glm\gtc\type_ptr.hpp>
#include <iterator>
#include <algorithm>

Cubelet::Cubelet(glm::vec3** colorScheme, glm::vec3 position, Transform* parent)
    : m_Transform(position)
{
    m_Transform.SetParent(parent);

    // copy colorScheme
    for (int i = 0; i < FACE_COUNT; i++)
    {
        m_ColorScheme[i] = colorScheme[i];
    }

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

Cubelet::~Cubelet()
{
    GLCall(glDeleteVertexArrays(1, &m_VAO));
    GLCall(glDeleteBuffers(1, &m_VBO));
    delete[] m_Shader;
    delete[] m_Texture;
}

Transform* Cubelet::GetTransform()
{
    return &m_Transform;
}

void Cubelet::Render(glm::mat4 view, glm::mat4 projection)
{
    m_Shader->Bind();

    // Bind Textures using texture units
    m_Texture->Bind();
    m_Shader->SetUniform1i("ourTexture1", 0);

    GLCall(glBindVertexArray(m_VAO));

    // Set world matrices 
    m_Shader->SetUniformMat4f("model", m_Transform.GetWorldMatrix());
    m_Shader->SetUniformMat4f("view", view );
    m_Shader->SetUniformMat4f("projection", projection);
    for (GLuint i = 0; i < 6; i++)
    {
        // Calculate the model matrix for each object and pass it to shader before drawing
        m_Shader->SetUniform3f("faceColor", *m_ColorScheme[i]);
        GLCall(glDrawArrays(GL_TRIANGLES, i * 6, 6));
    }

    GLCall(glBindVertexArray(0));
}
