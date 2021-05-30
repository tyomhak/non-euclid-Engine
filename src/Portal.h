#pragma once

#include "Object.h"
#include "Camera.h"

#include <iomanip>

unsigned int texture_width = 1920;
unsigned int texture_height = 1080;

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
    glm::mat4 GetWorldMat() const { return worldMatrix; }

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
                std::map<std::string, Object> &objs, 
                vector<Portal> &ports,
                GLuint depth = 0
            )
    {
        glDisable(GL_DEPTH_TEST);
        //glViewport(0, 0, texture_width, texture_height);

        Shader *currShader = &objShader;        
        currShader->bind();

        // Set the view (what you'll in the portal) //
        // ======================================== //
        glm::mat4 view = mainCamera.getViewMatrix();
        view = pair_portal->GetWorldMat() * glm::inverse(GetWorldMat()) * glm::inverse(view); 
        view = glm::inverse(view);


        // CAN USE THIS FOR PAIR CAMERA VIEW INSTEAD, BUT IT's MORE COMPLEX //
        // ================================================================ //
        // Camera tempCamera = GetPairCamera(mainCamera);
        // glm::mat4 view = tempCamera.getViewMatrix();


        // PAIR PORTAL CAMERAS POSITION CUBES //
        // ================================== // 
        // glm::mat4 view_clone = view;

        currShader->setView(view);

        // change the drawing location to portal framebuffer/texture, instead of the screen
        glBindFramebuffer(GL_FRAMEBUFFER, portalFramebuffer);
        glClearColor(0.3f, 0.8f,  1.0f , 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);


        // draw objects onto the portal texture
        for (auto &obj : objs)
        {
            obj.second.Draw(*currShader);
        }

        // move back to drawing on screen, instead of drawing on portal texture
        if (depth == 0)
        {
            glEnable(GL_DEPTH_TEST);
            //glViewport(0, 0, 1024, 768);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }


        currShader = &portShader;
        currShader->bind();

        view = mainCamera.getViewMatrix();

        currShader->setView(view);
        currShader->setModel(worldMatrix);
        currShader->update();

        for (auto &mesh : model->meshes)
        {
            glBindVertexArray(mesh.VAO);
            glBindTexture(GL_TEXTURE_2D, renderedTexture);
            glDrawElements(GL_TRIANGLES, (GLsizei)mesh.indices.size(), GL_UNSIGNED_INT, 0);
        }

        // PAIR PORTAL CAMERAS POSITION CUBES //
        // ================================== //
        // Object &cube = objs.at("cube2");
        // view_clone = glm::inverse(view_clone);
        // cube.SetWorldMatrix(view_clone);
        // cube.Draw(*currShader);
    }

    Camera GetPairCamera(Camera &mainCamera)
    {
        glm::mat4 view = mainCamera.getViewMatrix();
        view = pair_portal->GetWorldMat() * glm::inverse(GetWorldMat()) * glm::inverse(view); 
        // view = glm::inverse(view);

        glm::vec3 newPosition = glm::vec3(view[3][0], view[3][1], view[3][2]);

        // Inverse (instead of line 69)
        view = glm::inverse(view);
        
        GLfloat yawDiff = yaw - mainCamera.Yaw;
        GLfloat newYaw = pair_portal->yaw - yawDiff;
        
        // Camera tempCamera = Camera(newPosition, newFront, newRight, newUp);
        return Camera(newPosition, glm::vec3(0.0f, 1.0f, 0.0f), newYaw, mainCamera.Pitch);
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
        yaw = -90.0f;

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