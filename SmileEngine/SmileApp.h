#pragma once

#include "Timer.h"
#include <vector>
#include <list>

#include "SmileSetup.h"
#include "SmileModule.h"
#include "SmileWindow.h"
#include "SmileInput.h"
#include "SmileScene.h"
#include "SmileRenderer3D.h"
#include "SmileGui.h"
#include "SmileUtilitiesModule.h"
#include "SmileFBX.h"
#include "SmileGameObjectManager.h" 
#include "SmileSpatialTree.h"
#include "SmileResourceManager.h"
#include "SmileMaterialImporter.h"
#include "SmileFileSystem.h"
#include "SmileSerialization.h"

class SmileApp
{
public:
	SmileWindow* window;
	SmileInput* input;
	SmileScene* scene_intro;
	SmileRenderer3D* renderer3D;
	SmileGui* gui; 
	SmileUtilitiesModule* utilities;
	SmileFBX* fbx;
	SmileFileSystem* fs;
	SmileMaterialImporter* material_importer;
	SmileGameObjectManager* object_manager;
	SmileSpatialTree* spatial_tree; 
	SmileResourceManager* resources;
	SmileSerialization* serialization;

private:

	Timer	ms_timer;
	
	float dtMulti = 1.F; 
	float	dt;
	bool    terminated;
	std::list<SmileModule*> list_Modules;

public:
	std::vector<float> fps_log;
	std::vector<float> ms_log;
	
	SmileApp();
	~SmileApp();

	bool Init();
	update_status Update();
	bool CleanUp();

	float GetDT() const { return dt; }; 
	void SetDtMultiplier(float value) { dtMulti = value; };
private:

	void AddModule(SmileModule* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

extern SmileApp *App;

