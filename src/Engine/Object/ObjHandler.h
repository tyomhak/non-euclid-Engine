#pragma once

#include "Portal.h"
#include <unordered_map>
#include <string>


class ObjectHandler
{
    public:
    ObjectHandler(){};

    static std::unordered_map<string, Model> models;

    static Object GetObject(string type, glm::mat4 worldMatrix = glm::mat4(1.0f))
    {
        if (models.find(type) == models.end())
        {
            string path = "./data/models/" + type + "/" + type + ".obj";
            models.emplace(std::make_pair(type, Model(path)));
        }
        id += 1;
        return Object(models.at(type), type , type + std::to_string(id), worldMatrix);
    }

    static Portal GetPortal(glm::mat4 worldMatrix = glm::mat4(1.0f))
    {
        string type = "portal";
        if (models.find("portal") == models.end())
        {
            string path = "./data/models/" + type + "/" + type + ".obj";
            models.emplace(std::make_pair(type, Model(path)));
        }
        id += 1;
        return Portal(models.at("portal"), "portal", "portal" + std::to_string(id), worldMatrix);
    }

private:
    static int id;
};

int ObjectHandler::id = 0;
std::unordered_map<string, Model> ObjectHandler::models;