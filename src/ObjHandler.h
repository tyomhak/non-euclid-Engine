#pragma once

#include "Portal.h"
#include <unordered_map>
#include <string>


class ObjectHandler
{
    public:
    ObjectHandler(){};

    std::unordered_map<string, Model> models;

    Object GetObject(string type, glm::mat4 worldMatrix = glm::mat4(1.0f))
    {
        
        if (models.find(type) == models.end())
        {
            string path = "./data/models/" + type + "/" + type + ".obj";
            models.emplace(std::make_pair(type, Model(path)));
        }
        return Object(models.at(type), type, worldMatrix);
    }

    Portal GetPortal(glm::mat4 worldMatrix = glm::mat4(1.0f))
    {
        string type = "portal";
        if (models.find("portal") == models.end())
        {
            string path = "./data/models/" + type + "/" + type + ".obj";
            models.emplace(std::make_pair(type, Model(path)));
        }
        return Portal(models.at("portal"), "portal", worldMatrix);
    }
};