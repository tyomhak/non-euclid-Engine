#pragma once

#include "Object.h"

unsigned int texture_width = 1024;
unsigned int texture_height = 768;

unsigned int max_depth = 2;


class Portal: public Object 
{
public:
    Portal(Model &_model, string _modelType, std::string id, glm::mat4 _worldMatrix = glm::mat4(1.0f)):
    Object(_model, _modelType, id, _worldMatrix)
    {
        SetupPortal();
    }


    void SetPair(Portal *_pair)
    {
        pair_portal = _pair;
    }

    void SetShaders(Shader &_objectShader, Shader &_portalShader)
    {
        objectShader = &_objectShader;
        portalShader = &_portalShader;
    }

    void Move(glm::vec3 move_vec)
    {
        worldMatrix = glm::translate(worldMatrix, move_vec);
    }

    Portal *GetPairPtr() { return pair_portal; }
    glm::mat4 GetWorldMat() { return worldMatrix; }

    void Draw(  Camera &mainCamera, 
                std::map<std::string /* object Id */, Object> &objs,
                vector<Portal> &ports,
                GLuint depth = 0
            )
    {
        Draw(*objectShader, *portalShader, mainCamera, objs, ports, depth);
    }

    void Draw(  Shader &objShader, 
                Shader &portShader, 
                Camera &mainCamera, 
                std::map<std::string /* object Id */, Object> &objs, 
                vector<Portal> &ports,
                GLuint depth = 0
            )
    {
        glDisable(GL_DEPTH_TEST);
        glViewport(0, 0, texture_width, texture_height);

        Shader &currShader = portShader;        
        currShader.use();

        Camera tempCamera = Camera();
        glm::mat4 view = glm::mat4(1.0f);
        view = mainCamera.getViewMatrix();

        GLuint viewLoc = glGetUniformLocation(currShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        glBindFramebuffer(GL_FRAMEBUFFER, portalFramebuffer);
        glClearColor(0.3f, 0.8f,  1.0f , 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        if (depth < max_depth)
        {
            for (auto &portal : ports)
            {
                if (&portal != pair_portal)
                    portal.Draw(objShader, portShader, mainCamera, objs, ports, depth + 1);
            }
        }

        for (auto obj : objs)
        {
            obj.second.Draw(currShader);
        }

        if (depth == 0)
        {
            glEnable(GL_DEPTH_TEST);
            glViewport(0, 0, 1024, 768);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        currShader = objShader;
        currShader.use();

        view = mainCamera.getViewMatrix();
        viewLoc = glGetUniformLocation(currShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        GLuint modelLoc = glGetUniformLocation(currShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &worldMatrix[0][0]);
        
        for (auto &mesh : model->meshes)
        {
            glBindVertexArray(mesh.VAO);
            glBindTexture(GL_TEXTURE_2D, renderedTexture);
            glDrawElements(GL_TRIANGLES, (GLsizei)mesh.indices.size(), GL_UNSIGNED_INT, 0);
        }
    }


private:
    Portal *pair_portal;
    Shader *objectShader;
    Shader *portalShader;

    GLuint portalFramebuffer;
    GLuint renderedTexture;
    GLuint depthrenderbuffer;
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};

    void SetupPortal()
    {
        glGenFramebuffers(1, &portalFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, portalFramebuffer);

        glGenTextures(1, &renderedTexture);
        glBindTexture(GL_TEXTURE_2D, renderedTexture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB,  GL_UNSIGNED_BYTE, 0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);

        glGenRenderbuffers(1, &depthrenderbuffer); // changed 2 to 1. Maybe needs to be undone?
        glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, texture_width, texture_height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Portal frame buffer error" << std::endl;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
};