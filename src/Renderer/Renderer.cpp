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

void Renderer::DrawQuad(const Mesh& mesh, const Transform& modelMatrix, const Camera& camera, Shader& shader, glm::mat4 projection, glm::vec4 color)
{
    shader.Bind();
    mesh.Bind();

    glm::mat4 mvp = projection * camera.GetViewMatrix() * modelMatrix.GetModelMatrix();
    shader.setUniformMat4f("u_MVP", mvp);
    shader.setUniform4f("u_Color", color.x, color.y, color.z, color.w);
    
    glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}