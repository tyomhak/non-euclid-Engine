#pragma once

#include "Model.h"

class Portal: public Model
{
public:
    Portal(const std::string &path)
    :Model(path)
    {} 

    static Portal GetPortal()
    {
       vector<Vertex> vertices;
       vector<unsigned int> indices;
       vector<Texture> textures; 

       
    }

private:
    Mesh mesh;
    glm::mat4 worldMatrix;
    
};