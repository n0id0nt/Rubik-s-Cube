#include "Texture.h"

#include "SOIL2.h"
#include "GL\glew.h"
#include "openglHelper.h"

Texture::Texture(const std::string& path)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(__nullptr), m_Width(0), m_Height(0), m_BPP(0)
{   
    // --== TEXTURE == --
    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID)); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
    // Set our texture parameters
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    // Set texture filtering
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    // Load, create texture and generate mipmaps
    m_LocalBuffer = SOIL_load_image(path.c_str(), &m_Width, &m_Height, 0, SOIL_LOAD_RGB);
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));

    SOIL_free_image_data(m_LocalBuffer);
    GLCall(glBindTexture(GL_TEXTURE_2D, 0)); // Unbind texture when done, so we won't accidentily mess up our texture.
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
