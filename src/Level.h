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


    void AddPortalPair(glm::vec3 position1, glm::vec3 position2)
    {
        glm::mat4 location = glm::mat4(1.0f);
        glm::mat4 locationFirst = glm::translate(location, position1);
        glm::mat4 locationSecond = glm::translate(location, position2);
        Portal first = ObjectHandler::GetPortal(locationFirst);
        Portal second = ObjectHandler::GetPortal(locationSecond);
        AddPortalPair(first, second);
    }

    void AddPortalPair(glm::mat4 firstPos, glm::mat4 secondPos, float firstYaw = -90.0f, float secondYaw = -90.0f)
    {
        Portal first = ObjectHandler::GetPortal(firstPos);
        Portal second = ObjectHandler::GetPortal(secondPos);

        first.yaw = firstYaw;
        second.yaw = secondYaw;

        AddPortalPair(first, second);
    }

    std::map<std::string /* object Id */, Object>& GetObjects() { return levelObjects; }

    void deleteObject(std::string id)
    {
        if (levelObjects.find(id) != levelObjects.end())
        {
            levelObjects.erase(id);
        }

        if (levelPortals.find(id) != levelPortals.end())
        {
            string pairId = levelPortals.find(id)->second.GetPairPtr()->getId();
            levelPortals.erase(id);
            levelPortals.erase(pairId);
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
        std::map<std::string /* object ID */, Object>::iterator it = levelObjects.find(id);
        if (it != levelObjects.end())
        {
            return &levelObjects.find(id)->second;
        }

        std::map<std::string /* object ID */, Portal>::iterator itPortal = levelPortals.find(id);
        if (itPortal != levelPortals.end())
        {
            return &levelPortals.find(id)->second;
        }
        return nullptr;
    }

    Object getObject(string id)
    {
        std::map<std::string /* object ID */, Object>::iterator it = levelObjects.find(id);
        if (it != levelObjects.end())
        {
            return levelObjects.find(id)->second;
        }

        std::map<std::string /* object ID */, Portal>::iterator itPortal = levelPortals.find(id);
        if (itPortal != levelPortals.end())
        {
            return levelPortals.find(id)->second;
        }
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
    static Level ReadLevel(string path, Camera &myCamera, Shader &portalShader, Shader &objectShader)
    {
        Level myLevel = Level(portalShader, objectShader);

        string line;
        ifstream myLevelFile(path);

        glm::mat4 worldMatrix(1.0f);
        glm::mat4 worldMatrixBackup(1.0f);

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
                myLevel.AddObject(ObjectHandler::GetObject(objType, worldMatrix));
            }

            if (line == "camera")
            {
                glm::vec3 cPos(1.0f);
                for (int i = 0; i < 3; ++i)
                {
                    getline(myLevelFile, line);
                    cPos[i] = std::stof(line);
                }
                
                glm::vec3 cUp(1.0f);
                for (int i = 0; i < 3; ++i)
                {
                    getline(myLevelFile, line);
                    cUp[i] = std::stof(line);
                }

                getline(myLevelFile, line);
                float yaw = std::stof(line);

                getline(myLevelFile, line);
                float pitch = std::stof(line);

                // myCamera.SetPosition(cPos);
                // myCamera.SetFront(cUp);
                myCamera = Camera(cPos, glm::vec3(0.0f, 1.0f, 0.0f), yaw, pitch);
            }

            if (line == "p1")
            {
                for (int i = 0; i < 4; ++i)
                {
                    for (int j = 0; j < 4; ++j)
                    {
                        if(getline(myLevelFile, line))
                            worldMatrix[i][j] = std::stof(line);
                    }
                }
                float yawFirst = 0;
                float yawSecond = 0;
                if(getline(myLevelFile, line))
                {
                    yawFirst = std::stof(line);
                }

                if(getline(myLevelFile, line) && line == "p2")  
                {
                    for (int i = 0; i < 4; ++i)
                    {
                        for (int j = 0; j < 4; ++j)
                        {
                            if(getline(myLevelFile, line))
                                worldMatrixBackup[i][j] = std::stof(line);
                        }
                    }
                    if(getline(myLevelFile, line))
                    {
                        yawSecond = std::stof(line);
                    }

                    myLevel.AddPortalPair(worldMatrix, worldMatrixBackup, yawFirst, yawSecond);
                }
                else
                {
                    std::cout << "AbortingLevelLoad::MissingPairPortal" << std::endl;
                    return myLevel;
                }              
            }
        }

        return myLevel;
    }

    static void WriteLevel(string fileName, Level &level, Camera myCamera)
    {
        ofstream newLevel(fileName + ".lev");

        newLevel << "camera\n";
        for (int i = 0; i < 3; ++i)
            newLevel << std::to_string(myCamera.getPosition()[i]) + "\n";

        for (int i = 0; i < 3; ++i)
            newLevel << std::to_string(myCamera.getUp()[i]) + "\n";

        newLevel << std::to_string(myCamera.Yaw) + "\n";
        newLevel << std::to_string(myCamera.Pitch) + "\n";


        for (std::pair<std::string, Object> const& obj : level.GetObjects())
        {
            newLevel << "o:" + obj.second.modelType + "\n";
            const glm::mat4 worldMatrix = obj.second.GetWorldMat();
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    newLevel << std::to_string(worldMatrix[i][j]) + "\n";
                }
            }
        }


        std::set<std::string> savedPorts;
        unsigned int portalNumber = 0;
        for (auto &port : level.getPortals())
        {
            if (savedPorts.count(port.second.getId()) == 0)
            {
                // SAVE THIS PORTAL //
                // ================ //
                savedPorts.insert(port.second.getId());
                newLevel << "p1\n";
                glm::mat4 worldMatrix = port.second.GetWorldMat();
                for (int i = 0; i < 4; ++i)
                {
                    for (int j = 0; j < 4; ++j)
                    {
                        newLevel << std::to_string(worldMatrix[i][j]) + "\n";
                    }
                }
                newLevel << std::to_string(port.second.yaw) + "\n";

                // SAVE THE PAIR PORTAL //
                // ==================== //
                savedPorts.insert(port.second.GetPairPtr()->getId());    // add pair port to set, to avoid duplicate saving
                newLevel << "p2\n";
                worldMatrix = port.second.GetPairPtr()->GetWorldMat();
                for (int i = 0; i < 4; ++i)
                {
                    for (int j = 0; j < 4; ++j)
                    {
                        newLevel << std::to_string(worldMatrix[i][j]) + "\n";
                    }
                }
                newLevel << std::to_string(port.second.GetPairPtr()->getYaw()) + "\n";
            }
        }
        newLevel.close();
    }

    static void WriteLevel(string fileName, Level &level)
    {
        return WriteLevel(fileName, level, level.GetCamera());
    }
};