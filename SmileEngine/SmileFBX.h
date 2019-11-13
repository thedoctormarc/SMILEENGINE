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

	// Set & Get 
	void AssignTextureToObj(const char* path, GameObject* obj); 
	void AssignCheckersTextureToObj(GameObject* mesh); // TODO: generic
	globalTextureData GetGlobalTextureinfo() const { return textInfo; };
	//void FreeMeshTexture(ComponentMesh* mesh); 
	
	// FBX
	void Load(const char* path, std::string extension);
	GameObject* LoadFBX(const char* path);


	
public: 
	void ResolveObjectFromFBX(GameObject*, ComponentMesh* m = nullptr, std::vector<std::string> = {});
private:
	// FBX
	ModelMeshData* FillMeshBuffers(aiMesh*, ModelMeshData*);
	std::vector<std::string> ReadFBXMaterials(const aiScene*);
	bool DoesFBXExistInAssets(const char* path); 
	bool DoesFBXHaveLinkedModel(const char* path); 
	const char* PushFBXToAssets(const char* path); 
	GameObject* GenerateModelFromFBX(const char*,const aiScene*, char* rawname);

	
	// Own File Format 
	bool LoadMesh(ModelMeshData* mesh);
	std::string SaveMesh(ModelMeshData* mesh);
	bool LoadMaterial(textureData* texture);
	std::string SaveMaterial(textureData* texture);
	bool LoadModel(const char* path);
	void SaveModel(GameObject*);

	bool IsFBXPathAlreadyConvertedToModel(const char* path);

private: 
	globalTextureData textInfo;
	const char* lastFBXPath; 
public: 
	bool debug = false;
	
};

