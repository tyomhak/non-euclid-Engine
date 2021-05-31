#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "Level.h"
#include "ObjHandler.h"

#include <map>

class Level
{
private:
    std::map<std::string /* object ID */, Object> levelObjects;
    std::map<std::string /* object ID */, Portal> levelPortals;
    Shader *portalShader;
    Shader *objectShader; 

public:
    Camera camera;

    Level(Shader &_portalShader, Shader &_objectShader):
    portalShader(&_portalShader),
    objectShader(&_objectShader)
    {}
    
    Shader *GetPortalShaderPtr() { return portalShader; }
    Shader *GetObjectShaderPtr() { return objectShader; }
        
    string AddObject(std::string name, glm::vec3 position)
    {
        glm::mat4 location(1.0f);
        location = glm::translate(location, position);
        Object obj = ObjectHandler::GetObject(name, location);
        string id = obj.getId();
        levelObjects.emplace(id, obj);
        return id;
    }

    void AddObject(Object obj)
    {
        levelObjects.emplace(obj.getId(), obj);
    }

    void AddPortalPair(Portal& first, Portal& second)
    {
        levelPortals.emplace(first.getId(), first);
        levelPortals.emplace(second.getId(), second);

        int size = levelPortals.size();
        levelPortals.find(first.getId())->second.SetPair(&levelPortals.find(second.getId())->second);
        levelPortals.find(second.getId())->second.SetPair(&levelPortals.find(first.getId())->second);

        //levelPortals.at(size - 2).SetPair(&levelPortals.at(size - 1));
        //levelPortals.at(size - 1).SetPair(&levelPortals.at(size - 2));
    }

    std::map<std::string /* object Id */, Object>& GetObjects() { return levelObjects; }

    void deleteObject(std::string id)
    {
        if (levelObjects.find(id) != levelObjects.end())
        {
            levelObjects.erase(id);
        }
    }

    void DrawObjects(Camera& mainCamera, Shader* shader)
    {
        glm::mat4 view = mainCamera.getViewMatrix();
        shader->setView(view);
        //shader->update();
        //glm::mat4 view = mainCamera.getViewMatrix();
        //unsigned int viewLoc  = glGetUniformLocation(shader->ID, "view");
        //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        DrawObjects(shader);
    }

    void DrawObjects(Shader *shader)
    {
        for (auto it = levelObjects.begin(); it != levelObjects.end(); it++)
        {
            it->second.Draw(*objectShader);
        }
    }

    void DrawPortalsObj()
    {
        std::cout << "Not implemented. Line 97, Level.h" << std::endl;
        for (int i = 0; i < levelPortals.size(); ++i)
        {
           //  levelPortals.at(i).Draw(*objectShader);
        }
    }

    void Draw(Camera &mainCamera) 
    {
        DrawPortals(mainCamera);
        objectShader->bind();        // don't know why, but deleting this breaks shit.
        DrawObjects(mainCamera, objectShader);
    }

    std::map<std::string /* object ID */, Object> getObjects() const
    {
        return levelObjects;
    }

    std::map<std::string /* object ID */, Portal> getPortals() const
    {
        return levelPortals;
    }

    Object* getObjectPointer(string id)
    {
        return &levelObjects.find(id)->second;
    }

    Object getObject(string id)
    {
        return levelObjects.find(id)->second;
    }

    void DrawPortals(Camera &camera)
    {
        for (auto &portal : levelPortals)
        {
            portal.second.Draw(*objectShader, *portalShader, camera, levelObjects, levelPortals);
        }
    }


    Camera GetCamera() const { return camera; }
    void SetCamera(Camera _camera) { camera = _camera; }

};

class LevelHandler
{
private:

public:
    Level ReadLevel(string path, ObjectHandler &oH, Camera &myCamera, Shader &portalShader, Shader &objectShader)
    {
        Level myLevel = Level(portalShader, objectShader);

        string line;
        ifstream myLevelFile(path);

        glm::mat4 worldMatrix(1.0f);

        while (getline(myLevelFile, line))
        {
            if (line[0] == 'o')
            {
                string objType = line.substr(2);

                for (int i = 0; i < 4; ++i)
                {
                    for (int j = 0; j < 4; ++j)
                    {
                        if(getline(myLevelFile, line))
                            worldMatrix[i][j] = std::stof(line);
                    }
                }
                myLevel.AddObject(oH.GetObject(objType, worldMatrix));
            }

            if (line == "camera")
            {
                glm::vec3 cPos(1.0f);
                for (int i = 0; i < 3; ++i)
                {
                    getline(myLevelFile, line);
                    cPos[i] = std::stof(line);
                }
                
                glm::vec3 cFront(1.0f);
                for (int i = 0; i < 3; ++i)
                {
                    getline(myLevelFile, line);
                    cFront[i] = std::stof(line);
                }

                getline(myLevelFile, line);
                float yaw = std::stof(line);

                getline(myLevelFile, line);
                float pitch = std::stof(line);

                // myCamera.SetPosition(cPos);
                // myCamera.SetFront(cFront);
                myCamera = Camera(cPos, cFront, yaw, pitch);
            }
        }

        return myLevel;
    }

    void static WriteLevel(string fileName, Level &level, Camera myCamera)
    {
        ofstream newLevel(fileName + ".lev");

        newLevel << "camera\n";
        for (int i = 0; i < 3; ++i)
            newLevel << std::to_string(myCamera.getPosition()[i]) + "\n";

        for (int i = 0; i < 3; ++i)
            newLevel << std::to_string(myCamera.getFront()[i]) + "\n";

        newLevel << std::to_string(YAW) + "\n";
        newLevel << std::to_string(PITCH) + "\n";


        for (std::pair<std::string, Object> const& obj : level.GetObjects())
        {
            newLevel << "o:" + obj.second.modelType + "\n";
            const glm::mat4 matrix = obj.second.GetWorldMat();
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    newLevel << std::to_string(matrix[i][j]) + "\n";
                }
            }
        }

        newLevel.close();
    }

    void WriteLevel(string fileName, Level &level)
    {
        return WriteLevel(fileName, level, level.GetCamera());
    }
};