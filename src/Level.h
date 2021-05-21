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
        
        void DrawObjects(Camera mainCamera, Shader *shader)
        {
            glm::mat4 view = mainCamera.GetView();
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
                // levelPortals.at(i).Draw(*objectShader);
            }
        }

        void Draw(Portal *portalToSkip = nullptr, int depth = 0, Camera mainCamera = Camera()) 
        {
            if (depth < 4)
                DrawPortals(mainCamera, portalToSkip, depth + 1);
            // DrawPortalsObj();
            DrawObjects(mainCamera, portalShader);
        }

        void DrawPortals(Camera &camera, Portal *portalToSkip = nullptr, int depth = 0)
        {
            for (int i = 0; i < levelPortals.size(); ++i)
            {
                if (&levelPortals[i] == portalToSkip)
                    continue;

                levelPortals[i].Draw(*objectShader, *portalShader, camera, levelObjects, levelPortals);

                
                // Portal &this_portal = levelPortals[j];
                // Portal &pair_portal = *this_portal.GetPairPtr();

                // glDisable(GL_DEPTH_TEST);
                // glViewport(0, 0, 2024, 2024);
                // objectShader->use();
                // Camera tempCamera = Camera();
                // // TODO: Update camera and view mat                    
                // glm::mat4 view = glm::mat4(1.0f);
                // view = pair_portal.GetWorldMat() * 
                //         glm::inverse(this_portal.GetWorldMat()) * 
                //         camera.GetView();

                // glm::vec3 camPos = camera.GetPosition();
                // glm::vec3 camLook = camera.GetFront() - camPos;
                // glm::vec3 camUp = glm::vec3(0.0, 1.0, 0.0); 

                // glm::mat4 pwm = pair_portal.GetWorldMat();
                // camPos = glm::vec3(pwm[0][0], pwm[1][1], pwm[2][2]);  

                // tempCamera = Camera(camPos, camLook);
                // tempCamera.SetUp(camUp);
                // // view = tempCamera.GetView();
                // view = camera.GetView();
                // unsigned int viewLoc  = glGetUniformLocation(portalShader->ID, "view");
                // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
                
                // glBindFramebuffer(GL_FRAMEBUFFER, portalFramebuffer);
                // glClearColor(0.0, 0.9, 0.0, 1.0f);
                // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                // glEnable(GL_DEPTH_TEST);

                // // Draw(levelPortals[j].GetPairPtr(), depth, camera);
                // DrawObjects(objectShader);

                // glEnable(GL_DEPTH_TEST);
                // // Draw the Portal Object
                // glViewport(0, 0, 1024, 768);
                // glBindFramebuffer(GL_FRAMEBUFFER, 0);
                // // objectShader->use();
                // portalShader->use();

                // view = camera.GetView(); // glm::mat4(1.0f);
                // viewLoc  = glGetUniformLocation(objectShader->ID, "view");
                // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

                // unsigned int modelLoc = glGetUniformLocation(objectShader->ID, "model");
                // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(levelPortals[j].GetWorldMat()));

                // // glBindVertexArray(this_portal.VAO);
                // // glDisable(GL_DEPTH_TEST);
                // glBindTexture(GL_TEXTURE_2D, renderedTexture);
                // // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                // // glDrawElements(GL_TRIANGLES, levelPortals[j].GetModelPtr()->meshes[i].indices.size(), GL_UNSIGNED_INT, 0);
            }
            // glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // objectShader->use();
            // glViewport(0, 0, 1024, 768);
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