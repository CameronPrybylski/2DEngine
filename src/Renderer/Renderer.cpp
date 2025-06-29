#include <Engine/Renderer/Renderer.h>
#include <iostream>
void checkGLError(const char* label) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "[OpenGL Error] (" << label << "): " << std::hex << err << std::endl;
    }
}

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::DrawQuad(const Mesh& mesh, const Transform& modelMatrix, Shader& shader, glm::mat4 projection)
{
    //mesh.Bind();
    //checkGLError("Bind Mesh");
    shader.Bind();
    //checkGLError("Bind Shader");
    mesh.Bind();
    //checkGLError("Bind Mesh");
    //mesh.getIDs();
    glm::mat4 mvp = projection * modelMatrix.GetModelMatrix();
    shader.setUniformMat4f("u_MVP", mvp);
    shader.setUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //checkGLError("Draw Error");
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}