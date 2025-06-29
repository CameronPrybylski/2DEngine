#include <Engine/Scene/Scene.h>

void Scene::AddObject(std::shared_ptr<GameObject> object)
{
    objects.push_back(object);
}

void Scene::Update(float dt)
{

}

void Scene::Draw(Renderer& renderer)
{
    for(auto& obj : objects)
    {
        renderer.Draw(*obj->mesh, obj->transform, AssetManager::GetShader(obj->shaderName));
    }
}

void Scene::Clear(Renderer& renderer)
{
    renderer.Clear();
}