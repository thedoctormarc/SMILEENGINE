#pragma once

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#include "SmileModule.h"
#include "parshapes/par_shapes.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include <list>
#include "DevIL/include/IL/il.h"
#include "glmath.h"

#include "ComponentMesh.h"

struct globalTextureData
{
	uint totalActiveTextures = 0;
	uint rgb = 0; 
	uint rgba = 0; 
};

class SmileFBX : public SmileModule
{
public:
	SmileFBX(SmileApp* app, bool start_enabled = true);
	~SmileFBX();
	bool Start();
	bool CleanUp();
	GameObject* ReadFBXData(const char* path);


	void AssignTextureToObj(const char* path, GameObject* obj); 
	void AssignCheckersTextureToObj(GameObject* mesh); // TODO: generic
	//void FreeMeshTexture(ComponentMesh* mesh); 
	bool LoadMesh(ModelMeshData* mesh);
	std::string SaveMesh(ModelMeshData* mesh);
	bool LoadMaterial(textureData* texture);
	std::string SaveMaterial(textureData* texture);
	bool LoadModel();
	bool SaveModel(ModelMeshData* mesh, textureData* texture, ComponentTransform* transform);

	globalTextureData GetGlobalTextureinfo() const { return textInfo; }; 
private:
	globalTextureData textInfo;
public: 
	bool debug = false;
	std::string mesh_path;
	std::string material_path;
	
};

