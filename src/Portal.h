#pragma once

#include "Object.h"

uint texture_width = 2048;
uint texture_height = 2048;


class Portal: public Object 
{
public:
    Portal(Model &_model, string _modelType, glm::mat4 _worldMatrix = glm::mat4(1.0f)):
    Object(_model, _modelType, _worldMatrix)
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

    void Draw(Camera &mainCamera, vector<Object> &objs, vector<Portal> &ports)
    {
        Draw(*objectShader, *portalShader, mainCamera, objs, ports);
    }

    void Draw(  Shader &objShader, 
                Shader &portShader, 
                Camera &mainCamera, 
                vector<Object> &objs, 
                vector<Portal> &ports
             )
    {
        glDisable(GL_DEPTH_TEST);
        glViewport(0, 0, texture_width, texture_height);

        Shader &currShader = portShader;        
        currShader.use();

        Camera tempCamera = Camera();
        glm::mat4 view = glm::mat4(1.0f);
        view = mainCamera.GetView();

        GLuint viewLoc = glGetUniformLocation(currShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        glBindFramebuffer(GL_FRAMEBUFFER, portalFramebuffer);
        glClearColor(0.3, 0.7, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        for (auto obj : objs)
        {
            obj.Draw(currShader);
        }

        glEnable(GL_DEPTH_TEST);
        glViewport(0, 0, 1024, 768);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        currShader = objShader;
        currShader.use();

        view = mainCamera.GetView();
        viewLoc = glGetUniformLocation(currShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        GLuint modelLoc = glGetUniformLocation(currShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &worldMatrix[0][0]);
        
        for (auto &mesh : model->meshes)
        {
            glBindVertexArray(mesh.VAO);
            glBindTexture(GL_TEXTURE_2D, renderedTexture);
            glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        objShader.use();
        glViewport(0, 0, 1024, 768);
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
        // generate framebuffer

        glGenTextures(1, &renderedTexture);
        glBindTexture(GL_TEXTURE_2D, renderedTexture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2024, 2024, 0, GL_RGB,  GL_UNSIGNED_BYTE, 0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);

        // glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        // glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
        
        glGenRenderbuffers(1, &depthrenderbuffer); // changed 2 to 1. Maybe needs to be undone?
        glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 2024, 2024);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);


        // glDrawBuffers(1, DrawBuffers);
        // glDrawBuffer(GL_COLOR_ATTACHMENT0);
        // glReadBuffer(GL_NONE);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Portal frame buffer error" << std::endl;


        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
};