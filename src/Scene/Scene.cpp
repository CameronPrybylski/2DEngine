#include <Engine/Scene/Scene.h>

void Scene::AddObject(std::shared_ptr<GameObject> object)
{
    objects.push_back(object);
}

void Scene::Update(float dt)
{

}

void Scene::DrawQuads(Renderer& renderer)
{
    for(auto& obj : objects)
    {
        renderer.DrawQuad(*obj->mesh, obj->transform, AssetManager::GetShader(obj->shaderName), projection);
    }
}

void Scene::SetOrthoProjMat(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    projection = glm::ortho(minX, maxX, minY, maxY,  minZ, maxZ);
}
