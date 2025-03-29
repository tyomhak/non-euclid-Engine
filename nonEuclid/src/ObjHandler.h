#pragma once

#include <unordered_map>
#include <string>

#include "Portal.h"

class ObjectHandler
{
public:
    ObjectHandler(){};

    static Object GetObject(const std::string& type, glm::mat4 worldMatrix = glm::mat4(1.0f));
    static Portal GetPortal(glm::mat4 worldMatrix = glm::mat4(1.0f));

public:
    static std::unordered_map<std::string, Model> models;

private:
    static int id;
};

