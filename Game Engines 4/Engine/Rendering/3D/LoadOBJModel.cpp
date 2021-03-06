#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()),
textureCoords(std::vector<glm::vec2>()), indices(std::vector<unsigned int>()),
normalIndices(std::vector<unsigned int>()), textureIndices(std::vector<unsigned int>()),
meshVertices(std::vector<Vertex>()), subMeshes(std::vector<SubMesh>()), currentMaterial(Material())
{
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(200);
}

LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox() const
{
	return boundingbox;
}

void LoadOBJModel::LoadModel(const std::string& filePath_)
{
	boundingbox.maxVert = glm::vec3(-1000.0f);
	boundingbox.minVert = glm::vec3(1000.0f);

	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("Cannot open OBJ file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}

	std::string line;

	while (std::getline(in, line))
	{
		//VERTEX DATA
		if (line.substr(0, 2) == "v ")
		{
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			if (boundingbox.maxVert.x < x)
				boundingbox.maxVert.x = x;
			else if (boundingbox.maxVert.y < y)
				boundingbox.maxVert.y = y;
			else if (boundingbox.maxVert.z < z)
				boundingbox.maxVert.z = z;
			if (boundingbox.minVert.x > x)
				boundingbox.minVert.x = x;
			else if (boundingbox.minVert.y > y)
				boundingbox.minVert.y = y;
			else if (boundingbox.minVert.z > z)
				boundingbox.minVert.z = z;
			vertices.push_back(glm::vec3(x, y, z));
		}

		//NORMAL DATA
		else if (line.substr(0, 2) == "vn")
		{
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}

		//TEXTURE COORD DATA
		else if (line.substr(0, 2) == "vt")
		{
			std::stringstream v(line.substr(2));
			float x, y;
			v >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}

		//FACE DATA
		else if (line.substr(0, 1) == "f")
		{
			std::stringstream v(line.substr(1));
			unsigned int v1[3], v2[3], v3[3];
			char whatever;
			v >> v1[0] >> whatever >> v2[0] >> whatever >> v3[0] >> v1[1] >> whatever >> v2[1] >> whatever >> v3[1] >> v1[2] >> whatever >> v2[2] >> whatever >> v3[2];

			indices.push_back(v1[0] - 1);
			indices.push_back(v1[1] - 1);
			indices.push_back(v1[2] - 1);
			textureIndices.push_back(v2[0] - 1);
			textureIndices.push_back(v2[1] - 1);
			textureIndices.push_back(v2[2] - 1);
			normalIndices.push_back(v3[0] - 1);
			normalIndices.push_back(v3[1] - 1);
			normalIndices.push_back(v3[2] - 1);
		}

		//NEW MESH
		else if (line.substr(0, 7) == "usemtl ")
		{
			if (indices.size() > 0)
				PostProcessing();

			LoadMaterial(line.substr(7));
		}
	}

	PostProcessing();
}

void LoadOBJModel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size(); i++)
	{
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.textureCoordinates = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);
}