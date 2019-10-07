#pragma once
#include "SmileModule.h"
#include "SmileSetup.h"
#include "SmileFBX.h"
#include "parshapes/par_shapes.h"
#include <list>

#define ACCESS_TO_IMPORTER



class SmileScene : public SmileModule
{
public:
	SmileScene(SmileApp* app, bool start_enabled = true);
	~SmileScene();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

private: 
	void DrawGrid(); 

public: 
	void DrawMeshes();
	std::list<Mesh> meshes;


	/*// test
	par_shapes_mesh* testCube = nullptr;
	uint* vertexIDarray = nullptr; 
	uint* indexIDarray = nullptr;
	uint vertexID = 0; 
	uint indexID = vertexID; */

};
