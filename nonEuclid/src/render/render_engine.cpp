#include "render_engine.h"

#include <map>
#include <vector>
#include <string>

#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "utils/stb_image.h"

#include "render_object.h"
#include "model.h"
#include "mesh.h"
#include "material.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "asset_loader.h"


using namespace render;


void RenderEngine::tick()
{
    auto curr_timestamp_s = glfwGetTime();
    _delta = curr_timestamp_s - _previous_timestamp_s;

    if (1. / _framerate >= _delta)
    {
        _previous_timestamp_s = curr_timestamp_s;
        render();
    }
}
void RenderEngine::render()
{
    for (auto& [id, camera] : _cameras)
    {
        // set current camera

        // set render target
        
        for (auto& [obj_id, obj] : _objects)
        {
            // render obj
        }
    }
}

ID_CAM RenderEngine::create_camera()
{
    auto id = ID_CAM::create();
    _cameras.insert({id, Camera()});
    return id;
}
Camera RenderEngine::get_camera(ID_CAM id)
{
    return _cameras.at(id);
}

ID_OBJ RenderEngine::create_new_obj()
{
    auto id = ID_OBJ::create();
    _objects.insert({id, Obj()});
    return id;
}
Obj RenderEngine::get_obj(ID_OBJ id)
{
    return _objects.at(id);
}


// ID_MODEL RenderEngine::get_model_id(const std::string& path)
// {
//     if (!_model_ids.contains(path))
//         create_model(path);

//     return _model_ids.at(path);
// }
ID_MODEL RenderEngine::create_model(const std::string& file_name, const std::string& path)
{
    auto file_path = path + file_name;
    if (_model_ids.contains(file_path))
        return _model_ids.at(file_path);

    if (_model_ids.contains(file_path))
        return _model_ids.at(file_path);
    
    auto id = ID_MODEL::create();
    auto model = load_model(file_name, path);

    _models.insert({id, model});
    _model_ids.insert({file_path, id});
    return id;
}
Model& RenderEngine::get_model(ID_MODEL id)
{
    return _models.at(id);
}



ID_TEX RenderEngine::get_texture_id(const std::string& path)
{
    return _texture_ids.at(path);
}  
ID_TEX RenderEngine::create_texture(const std::string& path, TextureType type)
{
    auto id = ID_TEX::create();
    auto texture = load_texture(path);
    texture.type = type;

    _textures.insert({id, texture});
    return id;
}
Texture& RenderEngine::get_texture(ID_TEX id)
{
    return _textures.at(id);
}


ID_SHADER RenderEngine::get_shader_id(const std::string& path)
{

}
ID_SHADER RenderEngine::create_shader(const std::string& vert_path, const std::string& frag_path, const std::string& geom_path)
{
    auto id = ID_SHADER::create();
    auto shader = load_shader(vert_path, frag_path, geom_path);
    _shaders.insert({id, shader});
    return id;
}
Shader& RenderEngine::get_shader(ID_SHADER id)
{
    return _shaders.at(id);
}


Model RenderEngine::load_model(const std::string& file_name, const std::string& dir)
{
    Model model{};

    Assimp::Importer importer;
    unsigned int read_file_flags = aiProcess_Triangulate 
        | aiProcess_GenSmoothNormals 
        | aiProcess_FlipUVs 
        | aiProcess_CalcTangentSpace;

    auto file_path = dir + file_name;
    const aiScene* scene = importer.ReadFile(file_path, read_file_flags);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    
    auto mesh_count = scene->mNumMeshes;
    auto material_count = scene->mNumMaterials;


    std::map<int, std::vector<ID_TEX>> mat_textures_map{};
    for (auto mat_ndx = 0; mat_ndx < material_count; ++mat_ndx)
    {
        mat_textures_map.insert({mat_ndx, {}});

        auto material = scene->mMaterials[mat_ndx];
        std::vector<aiTextureType> tex_types {
            aiTextureType_DIFFUSE,
            aiTextureType_SPECULAR,
            aiTextureType_HEIGHT,
            aiTextureType_AMBIENT
        };

        std::map<aiTextureType, TextureType> type_map {
            { aiTextureType_DIFFUSE, TextureType::DIFFUSE },
            { aiTextureType_SPECULAR, TextureType::SPECULAR },
            { aiTextureType_HEIGHT, TextureType::NORMAL },
            { aiTextureType_AMBIENT, TextureType::HEIGHT }
        };

        for (auto tex_type : tex_types)
        {
            auto tex_count = material->GetTextureCount(tex_type);
            for (auto i = 0; i < tex_count; ++i)
            {
                aiString ai_tex_name;
                material->GetTexture(tex_type, i, &ai_tex_name);

                std::string tex_name = ai_tex_name.C_Str();
                if (!_texture_ids.contains(tex_name))
                {
                    auto tex_id = ID_TEX::create();
                    auto texture = load_texture(tex_name);
                    texture.type = type_map.at(tex_type);
                    
                    _texture_ids.insert({tex_name, tex_id});
                    _textures.insert({tex_id, texture});
                }

                auto tex_id = _texture_ids.at(tex_name);
                mat_textures_map.at(mat_ndx).push_back(tex_id);
            }
        }
    }

    for (auto mesh_ndx = 0;  mesh_ndx < mesh_count; ++mesh_ndx)
    {
        Mesh my_mesh{};
        auto mesh = scene->mMeshes[mesh_ndx];

        for (auto vert_ndx = 0; vert_ndx < mesh->mNumVertices; ++vert_ndx)
        {
            Vertex vertex{};

            auto& mesh_vertex = mesh->mVertices[vert_ndx];
            vertex.position = {
                mesh_vertex.x,
                mesh_vertex.y,
                mesh_vertex.z
            };

            if (mesh->HasNormals())
            {
                auto& mesh_norm = mesh->mNormals[vert_ndx];
                vertex.normal = {
                    mesh_norm.x,
                    mesh_norm.y,
                    mesh_norm.z
                };
            }

            if (mesh->HasTextureCoords(0))
            {
                auto& mesh_tex_coords = mesh->mTextureCoords[0][i];
                vertex.texture_coords = {
                    mesh_tex_coords.x,
                    mesh_tex_coords.y
                };

                auto& mesh_tangent = mesh->mTangents[i];
                vertex.tangent = {
                    mesh_tangent.x,
                    mesh_tangent.y,
                    mesh_tangent.z
                };

                auto& mesh_bitangent = mesh->mBitangents[i];
                vertex.bitangent = {
                    mesh_bitangent.x,
                    mesh_bitangent.y,
                    mesh_bitangent.z
                };
            }
            else
            {
                vertex.texture_coords = {0.0f, 0.0f};
            }

            my_mesh.vertices.push_back(vertex);
        }

        for (auto i = 0; i < mesh->mNumFaces; ++i)
        {
            auto mesh_face = mesh->mFaces[i];
            my_mesh.indices.insert(my_mesh.indices.end(), mesh_face.mIndices, mesh_face.mIndices + mesh_face.mNumIndices);
        }

        auto mat_ndx = mesh->mMaterialIndex;
        if (mat_textures_map.contains(mat_ndx))
        {
            auto& textures = mat_textures_map.at(mat_ndx);
            my_mesh.textures.insert(my_mesh.textures.end(), textures.begin(), textures.end());
        }
    }

    return model;
}

Texture RenderEngine::load_texture(const std::string& path)
{
    Texture texture{};

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        texture.internal_id = textureID;
        texture.path = path;
        texture.width = width;
        texture.height = height;
    }
    else
    {
        stbi_image_free(data);
    }

    return texture;
}
Shader  RenderEngine::load_shader(const std::string& vert, const std::string& frag, const std::string& geom)
{
    return ShaderLoader().CreateShader(vert, frag, geom);
}