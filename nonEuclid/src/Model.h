#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <assimp/scene.h>

#include "Mesh.h"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model 
{
public:
    Model(std::string const &path, bool gamma = false);

    void Draw(Shader &shader, glm::mat4 worldMatrix = glm::mat4(1.0f));
    
private:
    void LoadModel(std::string const &path);

    void ProcessNode(aiNode *node, const aiScene *scene);
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
    
    // Material LoadMaterial(aiMaterial *mat);

public:
    std::vector<Texture> textures_loaded;
    std::vector<Mesh>    meshes;
    std::string directory;
    bool gammaCorrection;
};

