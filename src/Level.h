#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "ObjHandler.h"

class Level
{
    private:
        std::vector<Object> levelObjects; // maybe change this to a map, with IDs?

    public:
        Camera camera;
        
        Level() // need to change default values later 
        {}

        Level(Camera &_camera):
        camera(_camera)
        {}

        void Draw(Shader &myShader)
        {
            for (int i = 0; i < levelObjects.size(); ++i)
            {
                levelObjects.at(i).Draw(myShader);
            }
        }

        void AddObject(Object obj)
        {
            levelObjects.push_back(obj);
        }

        const std::vector<Object> GetObjects() { return levelObjects; }

        Camera GetCamera() const { return camera; }
        void SetCamera(Camera _camera) { camera = _camera; }

};

class LevelHandler
{
    private:

    public:
        Level ReadLevel(string path, ObjectHandler &oH, Camera &myCamera)
        {
            Level myLevel = Level();

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

        void WriteLevel(string fileName, Level &level, Camera myCamera)
        {
            ofstream newLevel(fileName + ".lev");

            newLevel << "camera\n";
            for (int i = 0; i < 3; ++i)
                newLevel << std::to_string(myCamera.GetPosition()[i]) + "\n";

            for (int i = 0; i < 3; ++i)
                newLevel << std::to_string(myCamera.GetFront()[i]) + "\n";

            newLevel << std::to_string(myCamera.GetYaw()) + "\n";
            newLevel << std::to_string(myCamera.GetPitch()) + "\n";


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