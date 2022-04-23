#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "Level.h"
#include "ObjHandler.h"

#include <map>
#include <set>

class Level
{
public:
    Level(Shader &_portalShader, Shader &_objectShader):
    portalShader(&_portalShader),
    objectShader(&_objectShader)
    {}
    
    Shader *GetPortalShaderPtr() { return portalShader; }
    Shader *GetObjectShaderPtr() { return objectShader; }
        
    string AddObject(std::string name, glm::vec3 position);

    void AddObject(Object obj);

    void AddPortalPair(Portal& first, Portal& second);


    void AddPortalPair(glm::vec3 position1, glm::vec3 position2);

    void AddPortalPair(glm::mat4 firstPos, glm::mat4 secondPos, float firstYaw = -90.0f, float secondYaw = -90.0f);

    std::map<std::string, Object>& GetObjects();

    void DeleteObject(std::string id);

    void DrawObjects(Camera& mainCamera, Shader* shader);

    void DrawObjects(Shader* shader);

    //void DrawPortalsObj()
    //{
    //    std::cout << "Not implemented. Line 97, Level.h" << std::endl;
    //    for (int i = 0; i < levelPortals.size(); ++i)
    //    {
    //       //  levelPortals.at(i).Draw(*objectShader);
    //    }
    //}

    void Draw(Camera& mainCamera);

    std::map<std::string /* object ID */, Object> GetObjects() const;

    std::map<std::string /* object ID */, Portal>& GetPortals();

    Object* GetObjectPointer(string id);

    Object GetObject(string id);

    void DrawPortals(Camera& camera);


    Camera GetCamera() const { return camera; }
    void SetCamera(Camera _camera) { camera = _camera; }


public:
    Camera camera;

private:
    std::map<std::string, Object> levelObjects;
    std::map<std::string, Portal> levelPortals;
    Shader* portalShader;
    Shader* objectShader;
};

class LevelHandler
{
public:
    static Level ReadLevel(string path, Camera& myCamera, Shader& portalShader, Shader& objectShader);

    static void WriteLevel(string fileName, Level& level, Camera myCamera);
    static void WriteLevel(string fileName, Level& level);
};