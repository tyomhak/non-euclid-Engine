#pragma once

#include <unordered_map>
#include <string>

#include <assimp/scene.h>


#include "utils/id.h"
#include "shader.h"

namespace render
{

class RenderObject;
class Mesh;
class Model;
class Camera;
class Texture;
class Shader;

typedef RenderObject Obj;
typedef ID<Mesh>    ID_MESH;
typedef ID<Model>   ID_MODEL;
typedef ID<Obj>     ID_OBJ;
typedef ID<Camera>  ID_CAM;
typedef ID<Texture> ID_TEX;
typedef ID<Shader>  ID_SHADER;

class RenderEngine
{
public:
    static RenderEngine& singleton()
    {
        static RenderEngine engine{};
        return engine;
    }

    void tick(); // update render delta time, render if refresh needed
    void render();

    ID_CAM create_camera();
    Camera get_camera(ID_CAM);
    
    ID_OBJ create_new_obj();
    Obj get_obj(ID_OBJ);

    // ID_MODEL get_model_id(const std::string& path);
    ID_MODEL create_model(const std::string& file_name, const std::string& path);
    Model& get_model(ID_MODEL);

    // ID_MESH get_mesh_id(const std::string& path);
    // ID_MESH create_mesh(const std::string& path);
    // Mesh& get_mesh(ID_MESH);

    ID_TEX get_texture_id(const std::string& path);   
    ID_TEX create_texture(const std::string& path, TextureType type);
    Texture& get_texture(ID_TEX);

    ID_SHADER get_shader_id(const std::string& path);
    ID_SHADER create_shader(const std::string& vert_path, const std::string& frag_path, const std::string& geom_path);
    Shader& get_shader(ID_SHADER);

private:
    Model   load_model(const std::string& file_name, const std::string& path);
    void    load_model_node(const aiNode* node, const aiScene* scene, std::vector<Mesh>& mesh_storage);
    Mesh    load_mesh(const aiMesh *mesh, const aiScene *scene);

    Material load_material();
    std::vector<Texture> get_material_textures(aiMaterial *mat, aiTextureType type);
    Texture load_texture(const std::string& path);
    Shader  load_shader(const std::string& vert, const std::string& frag, const std::string& geom);

private:
    std::unordered_map<ID_CAM, Camera>      _cameras{};
    std::unordered_map<ID_OBJ, Obj>         _objects{};
    std::unordered_map<ID_MODEL, Model>     _models{};
    // std::unordered_map<ID_MESH, Mesh>       _meshes{};
    std::unordered_map<ID_TEX, Texture>    _textures{};
    std::unordered_map<ID_SHADER, Shader>   _shaders{};

    std::unordered_map<std::string, ID_MODEL>   _model_ids{};
    // std::unordered_map<std::string, ID_MESH>    _mesh_ids{};
    std::unordered_map<std::string, ID_TEX>     _texture_ids{};
    std::unordered_map<std::string, ID_SHADER>  _shader_ids{};

    double _previous_timestamp_s{0.};
    double _delta{0.1};

    double _framerate = 60;
};


}