#include "convertor.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/gtc/packing.hpp>

#include <fstream>

constexpr auto QMF_FILE_EXTENSION = "qmf";  // The file extension used by the QMF format
constexpr auto QMF_MAGIC = 0x514D4620;      // Equivalent to "QMF "

struct QMFHeader
{
	uint32_t magic;
	uint32_t numMeshes;
};

struct QMFMeshHeader
{
	uint32_t numVertices;
	uint32_t numFaces;
	uint8_t numUVComponents[AI_MAX_NUMBER_OF_TEXTURECOORDS];
	uint8_t numUVChannels;
	bool hasNormals;
};

void QE::ConvertToQMF(const fs::path& filepath)
{
	// Use Assimp to import the mesh file
	Assimp::Importer importer;
	const auto scene = importer.ReadFile(filepath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr)
	{
		// Replace the extension with .qmf
		auto path = filepath;
		path.replace_extension(fs::u8path(QMF_FILE_EXTENSION));

		// Create a binary output file stream to the qmf file
		std::ofstream file(path, std::ios::out | std::ios::binary);

		// Ensure the file was opened successfully
		if (file.is_open())
		{
			// Write the header
			QMFHeader header;
			header.magic = QMF_MAGIC;
			header.numMeshes = scene->mNumMeshes;
			file.write(reinterpret_cast<char*>(&header), sizeof(header));

			// For each mesh write its metadata + data
			for (auto i = 0U; i < header.numMeshes; ++i)
			{
				const auto mesh = scene->mMeshes[i];

				// Write the mesh header
				QMFMeshHeader meshHeader;
				meshHeader.numVertices = mesh->mNumVertices;
				meshHeader.numFaces = mesh->mNumFaces;
				meshHeader.numUVChannels = mesh->GetNumUVChannels();
				for (auto j = 0U; j < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++j)
				{
					meshHeader.numUVComponents[j] = static_cast<uint8_t>(mesh->mNumUVComponents[j]);
				}
				meshHeader.hasNormals = mesh->HasNormals();
				file.write(reinterpret_cast<char*>(&meshHeader), sizeof(meshHeader));

				// Write the vertex positions
				file.write(reinterpret_cast<char*>(mesh->mVertices), meshHeader.numVertices * sizeof(*mesh->mVertices));

				// Write the vertex texture coordinates
				for (auto j = 0U; j < meshHeader.numUVChannels; ++j)
				{
					if (meshHeader.numUVComponents[j] == 1)
					{
						std::vector<float> texcoords(meshHeader.numVertices);
						for (auto k = 0U; k < meshHeader.numVertices; ++k)
						{
							texcoords[k] = mesh->mTextureCoords[j][k].x;
						}
						file.write(reinterpret_cast<char*>(texcoords.data()), texcoords.size() * sizeof(float));
					}
					else if (meshHeader.numUVComponents[j] == 2)
					{
						std::vector<float> texcoords(meshHeader.numVertices * 2U);
						for (auto k = 0U; k < meshHeader.numVertices; ++k)
						{
							texcoords[k * 2U] = mesh->mTextureCoords[j][k].x;
							texcoords[k * 2U + 1] = mesh->mTextureCoords[j][k].y;
						}
						file.write(reinterpret_cast<char*>(texcoords.data()), texcoords.size() * sizeof(float));
					}
					else
					{
						file.write(reinterpret_cast<char*>(mesh->mTextureCoords[j]), sizeof(*mesh->mTextureCoords[j]));
					}
				}

				// Write the vertex normals
				if (meshHeader.hasNormals)
				{
					std::vector<uint16_t> normals(meshHeader.numVertices * 3U);
					for (auto j = 0U; j < meshHeader.numVertices; ++j)
					{
						normals[j * 3U] = glm::packHalf1x16(mesh->mNormals[j].x);
						normals[j * 3U + 1] = glm::packHalf1x16(mesh->mNormals[j].y);
						normals[j * 3U + 2] = glm::packHalf1x16(mesh->mNormals[j].z);
					}
					file.write(reinterpret_cast<char*>(normals.data()), normals.size() * sizeof(uint16_t));
				}

				// Write the index data
				if (meshHeader.numVertices <= 0x00FF)
				{
					std::vector<uint8_t> indices(meshHeader.numFaces * 3U);
					for (auto j = 0U; j < meshHeader.numFaces; ++j)
					{
						indices[j * 3U] = static_cast<uint8_t>(mesh->mFaces[j].mIndices[0]);
						indices[j * 3U + 1U] = static_cast<uint8_t>(mesh->mFaces[j].mIndices[1]);
						indices[j * 3U + 2U] = static_cast<uint8_t>(mesh->mFaces[j].mIndices[2]);
					}
					file.write(reinterpret_cast<char*>(indices.data()), indices.size());
				}
				else if (meshHeader.numVertices <= 0xFFFF)
				{
					std::vector<uint16_t> indices(meshHeader.numFaces * 3U);
					for (auto j = 0U; j < meshHeader.numFaces; ++j)
					{
						indices[j * 3U] = static_cast<uint16_t>(mesh->mFaces[j].mIndices[0]);
						indices[j * 3U + 1U] = static_cast<uint16_t>(mesh->mFaces[j].mIndices[1]);
						indices[j * 3U + 2U] = static_cast<uint16_t>(mesh->mFaces[j].mIndices[2]);
					}
					file.write(reinterpret_cast<char*>(indices.data()), indices.size() * sizeof(uint16_t));
				}
				else
				{
					std::vector<uint32_t> indices(meshHeader.numFaces * 3U);
					for (auto j = 0U; j < meshHeader.numFaces; ++j)
					{
						indices[j * 3U] = mesh->mFaces[j].mIndices[0];
						indices[j * 3U + 1U] = mesh->mFaces[j].mIndices[1];
						indices[j * 3U + 2U] = mesh->mFaces[j].mIndices[2];
					}
					file.write(reinterpret_cast<char*>(indices.data()), indices.size() * sizeof(uint32_t));
				}
			}
		}
	}
}
