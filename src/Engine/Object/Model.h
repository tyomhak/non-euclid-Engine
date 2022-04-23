#pragma once

#include "Mesh.h"

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>


using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model 
{
public:
    Model(string const& modelPath, bool gamma = false);
    void Draw(Shader& shader, glm::mat4 worldMatrix = glm::mat4(1.0f));
    
private:
    void LoadModel(string const& path);

    // recursive node processing.
    void ProcessNode(aiNode* node, const aiScene* scene);

    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

    vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
    
    Material LoadMaterial(aiMaterial* mat);

public:
    vector<Texture> textures_loaded;
    vector<Mesh>    meshes;
    string directory;
    bool gammaCorrection;
};

