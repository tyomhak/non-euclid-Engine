#pragma once

#include "render/renderer.hpp"
#include "render/resource_descriptions.hpp"

#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
#include <stdexcept>

namespace njin
{

/// Standard vertex layout used by engine shaders.
struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
};

/// Result of loading a single mesh from a model file.
struct LoadedMesh
{
    std::vector<Vertex>   vertices;
    std::vector<uint32_t> indices;
    std::string           diffuse_texture_path; // empty if none
};

class MeshLoader
{
public:
    /// Load all meshes from a model file (OBJ, FBX, glTF, etc.).
    /// Returns one LoadedMesh per mesh in the file.
    static std::vector<LoadedMesh> load(const std::string& path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path,
            aiProcess_Triangulate |
            aiProcess_GenSmoothNormals |
            aiProcess_FlipUVs |
            aiProcess_CalcTangentSpace);

        if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode)
            throw std::runtime_error("MeshLoader: failed to load '" + path + "': " + importer.GetErrorString());

        // Extract the directory for resolving relative texture paths.
        std::string directory = path.substr(0, path.find_last_of("/\\"));

        std::vector<LoadedMesh> result;
        process_node(scene->mRootNode, scene, directory, result);
        return result;
    }

    /// Helper: create GPU buffers + pipeline for a LoadedMesh and return the IDs.
    struct GPUMesh
    {
        rend::BufferID   vbo;
        rend::BufferID   ibo;
        rend::PipelineID pipeline;
        uint32_t         index_count;
    };

    static GPUMesh upload(rend::Renderer& renderer,
                          const LoadedMesh& mesh,
                          rend::ShaderID shader)
    {
        rend::BufferDesc vbo_desc{};
        vbo_desc.size  = static_cast<uint32_t>(mesh.vertices.size() * sizeof(Vertex));
        vbo_desc.usage = rend::BufferUsage::Vertex;
        vbo_desc.data  = const_cast<Vertex*>(mesh.vertices.data());

        rend::BufferDesc ibo_desc{};
        ibo_desc.size  = static_cast<uint32_t>(mesh.indices.size() * sizeof(uint32_t));
        ibo_desc.usage = rend::BufferUsage::Index;
        ibo_desc.data  = const_cast<uint32_t*>(mesh.indices.data());

        rend::PipelineDesc pipe_desc{};
        pipe_desc.shader     = shader;
        pipe_desc.depthTest  = true;
        pipe_desc.depthWrite = true;
        pipe_desc.vertex_layout.stride = sizeof(Vertex);
        pipe_desc.vertex_layout.attributes = {
            { 0, rend::VertexAttribType::Float3, offsetof(Vertex, position) },
            { 1, rend::VertexAttribType::Float3, offsetof(Vertex, normal)   },
            { 2, rend::VertexAttribType::Float2, offsetof(Vertex, texcoord) },
        };

        GPUMesh gpu{};
        gpu.vbo         = renderer.create_buffer(vbo_desc);
        gpu.ibo         = renderer.create_buffer(ibo_desc);
        gpu.pipeline    = renderer.create_pipeline(pipe_desc);
        gpu.index_count = static_cast<uint32_t>(mesh.indices.size());
        return gpu;
    }

private:
    static void process_node(const aiNode* node, const aiScene* scene,
                             const std::string& directory,
                             std::vector<LoadedMesh>& out)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
            out.push_back(process_mesh(scene->mMeshes[node->mMeshes[i]], scene, directory));

        for (unsigned int i = 0; i < node->mNumChildren; i++)
            process_node(node->mChildren[i], scene, directory, out);
    }

    static LoadedMesh process_mesh(const aiMesh* mesh, const aiScene* scene,
                                   const std::string& directory)
    {
        LoadedMesh result;
        result.vertices.reserve(mesh->mNumVertices);

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex v{};
            v.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };

            if (mesh->HasNormals())
                v.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

            if (mesh->mTextureCoords[0])
                v.texcoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };

            result.vertices.push_back(v);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            const aiFace& face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                result.indices.push_back(face.mIndices[j]);
        }

        // Extract diffuse texture path from first material
        if (mesh->mMaterialIndex < scene->mNumMaterials)
        {
            const aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
            if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
            {
                aiString tex_path;
                mat->GetTexture(aiTextureType_DIFFUSE, 0, &tex_path);
                result.diffuse_texture_path = directory + "/" + tex_path.C_Str();
            }
        }

        return result;
    }
};

} // namespace njin
