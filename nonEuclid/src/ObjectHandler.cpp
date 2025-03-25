#include "ObjHandler.h"

int ObjectHandler::id = 0;
std::unordered_map<std::string, Model> ObjectHandler::models{};


Object ObjectHandler::GetObject(const std::string& type, glm::mat4 worldMatrix)
{
    if (models.find(type) == models.end())
    {
        std::string path = "./data/models/" + type + "/" + type + ".obj";
        models.emplace(std::make_pair(type, Model(path)));
    }
    id += 1;
    return Object(models.at(type), type , type + std::to_string(id), worldMatrix);
}

Portal ObjectHandler::GetPortal(glm::mat4 worldMatrix ) // = glm::mat4(1.0f)
{
    std::string type = "portal";
    if (models.find("portal") == models.end())
    {
        std::string path = "./data/models/" + type + "/" + type + ".obj";
        models.emplace(std::make_pair(type, Model(path)));
    }
    id += 1;
    return Portal(models.at("portal"), "portal", "portal" + std::to_string(id), worldMatrix);
}