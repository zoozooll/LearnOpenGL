#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <learnopengl/gl_header.h>
#include <glm/glm.hpp>
#include <map>
#include <string>

class Shader; // Forward declaration

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class GLRenderer
{
public:
    GLRenderer();
    virtual ~GLRenderer() = default;

    virtual void OnInit();
    virtual void OnSizeChanged(int width, int height);
    virtual void OnDraw();
    virtual void OnDestroy();

private:
    Shader* m_pShader;
    std::map<GLchar, Character> Characters;
    unsigned int m_VAO, m_VBO;
    int m_width;
    int m_height;

    void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color);
};

#endif //GLRENDERER_H
