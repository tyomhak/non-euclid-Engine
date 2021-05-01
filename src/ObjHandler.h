#pragma once

#include "Object.h"
#include <unordered_map>
#include <string>


std::unordered_map<string, string> modelPaths = 
{
    {"backpack", "./models/backpack/backpack.obj"},
    {"treeMinimal", "./models/low_poly_tree/Lowpoly_tree_sample.obj"}
};

class ObjectHandler
{
    public:
    ObjectHandler(){};

    std::unordered_map<string, Model> models;

    Object GetObject(string type, glm::mat4 worldMatrix = glm::mat4(1.0f))
    {
        
        if (models.find(type) == models.end())
        {
            string path = "./models/" + type + "/" + type + ".obj";
            models.emplace(std::make_pair(type, Model(path)));
        }
        return Object(models.at(type), type, worldMatrix);
    }
};