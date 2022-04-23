#pragma once

#include "Object.h"
#include "Camera.h"

#include <iomanip>


class Portal: public Object 
{
public:
    Portal(Model& _model, 
        string _modelType, 
        std::string id, 
        glm::mat4 _worldMatrix = glm::mat4(1.0f)
    );

    void SetShaders(Shader& _objectShader, Shader& _portalShader);

    void SetPair(Portal* _pair);
    Portal *GetPairPtr() const { return pair_portal; }
    Camera GetPairCamera(Camera& mainCamera) const;

    void Draw(Camera& mainCamera,
        std::map<std::string /* object Id */, Object>& objs,
        std::map<std::string /* object ID */, Portal>& ports,
        GLuint depth = 0
    );

    void Draw(Shader& objShader,
        Shader& portShader,
        Camera& mainCamera,
        std::map<std::string, Object>& objs,
        std::map<std::string /* object ID */, Portal>& ports,
        GLuint depth = 0
    );

    

private:
    void SetupPortal();



public:
    static std::vector<float> portalBackground;

private:
    Portal *pair_portal;
    Shader *objectShader;
    Shader *portalShader;

    GLuint portalFramebuffer;
    GLuint renderedTexture;
    GLuint depthrenderbuffer;
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};

    unsigned int texture_width = 1920;
    unsigned int texture_height = 1080;
};