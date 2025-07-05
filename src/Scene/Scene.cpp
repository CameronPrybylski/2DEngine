#include <SDL.h>
#include <Engine/Scene/Scene.h>

void Scene::AddObject(std::string nameOfObject, std::shared_ptr<GameObject> object)
{
    if(objectMap.find(nameOfObject) != objectMap.end())
    {
        std::cerr << "Object named " + nameOfObject + "Already Exists" << std::endl;
        return;
    }
    objectMap[nameOfObject] = object;
    objectList.push_back(object);
}

void Scene::OnEvent(const Input& input)
{
    for(auto& obj : objectList)
    {
        obj->OnEvent(input);
    }
}

void Scene::OnUpdate(float dt)
{
    for(auto& obj : objectList)
    {
        obj->Update(dt);
    }

}

void Scene::DrawObjects(Renderer& renderer)
{
    for(auto& obj : objectList)
    {
        obj->Render(renderer, projection);
        //renderer.DrawQuad(*obj->mesh, obj->transform, AssetManager::GetShader(obj->shaderName), projection);
    }
}

void Scene::SetOrthoProjMat(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    projection = glm::ortho(minX, maxX, minY, maxY,  minZ, maxZ);
}
