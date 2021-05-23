#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "Level.h"
#include "ObjHandler.h"

class Level
{
    private:
        std::vector<Object> levelObjects; // maybe change this to a map, with IDs?
        std::vector<Portal> levelPortals;
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
        
        void DrawObjects(Camera &mainCamera, Shader *shader)
        {
            glm::mat4 view = mainCamera.getViewMatrix();
            unsigned int viewLoc  = glGetUniformLocation(shader->ID, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);


            for (int i = 0; i < levelObjects.size(); ++i)
            {
                levelObjects.at(i).Draw(*objectShader);
            }
        }

        void DrawObjects(Shader *shader)
        {
            for (int i = 0; i < levelObjects.size(); ++i)
            {
                levelObjects.at(i).Draw(*objectShader);
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

        void Draw(Camera &mainCamera = Camera()) 
        {
            DrawPortals(mainCamera);
            // DrawPortalsObj();
            DrawObjects(mainCamera, portalShader);
        }

        void DrawPortals(Camera &camera)
        {
            for (auto &portal : levelPortals)
            {
                portal.Draw(*objectShader, *portalShader, camera, levelObjects, levelPortals);
            }
        }

        void AddObject(Object obj)
        {
            levelObjects.push_back(obj);
        }

        void AddPortalPair(Portal &first, Portal &second)
        {
            first.SetPair(&second);
            second.SetPair(&first);
            levelPortals.push_back(first);
            levelPortals.push_back(second);
        }

        const std::vector<Object> GetObjects() { return levelObjects; }

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


            for (Object const& obj : level.GetObjects())
            {
                newLevel << "o:" + obj.modelType + "\n";
                const glm::mat4 matrix = obj.GetWorldMat();
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