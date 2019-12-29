#pragma once
#include "SmileModule.h"
#include "SmileSetup.h"
#include "SmileFBX.h"
#include "GameObject.h"
#include "ComponentMesh.h"
#include "ComponentCamera.h"
#include <vector>
#include <variant>

#include "MathGeoLib/include/Math/float2.h"
#include "MathGeoLib/include/Geometry/LineSegment.h"

#define MAXLINES 30

void CreateFireWork(); 
void CreateSmoke(float3 pos); 

class ResourceMeshPlane; 
class SmileScene : public SmileModule
{
public:
	SmileScene(SmileApp* app, bool start_enabled = true);
	~SmileScene();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	bool Reset(); 


	std::variant<ComponentMesh*, GameObject*> MouseOverMesh(int mouse_x, int mouse_y, bool assignClicked, bool GetMeshNotGameObject);
private: 
	void DrawObjects(); 
	void DrawGrid(); 
	void HandleGizmo(); 

	// Ray stuff (very splitted xd)
	math::LineSegment lastRay;
	bool SkipRayConditions() const; 
	math::LineSegment TraceRay(float2 normalizedMousePos); 
	float2 GetNormalizedMousePos(int, int); 
	ComponentMesh* FindRayIntersection(math::LineSegment ray);
	void DebugLastRay(); 
	std::variant<ComponentMesh*, GameObject*> EmptyRayReturn(bool GetMeshNotGameObject, bool assignClicked);
	std::variant<ComponentMesh*, GameObject*> ClickRayReturn(bool GetMeshNotGameObject, ComponentMesh* found);
	std::variant<ComponentMesh*, GameObject*> HoverRayReturn(bool GetMeshNotGameObject, ComponentMesh* found);
 

public:
	bool pause = false; 
	GameObject* rootObj = nullptr;
	GameObject* selectedObj = nullptr; 
	ComponentMesh* selected_mesh = nullptr;
	ComponentCamera* debugCamera = nullptr; 
	ComponentCamera* gameCamera = nullptr;

	bool generalDbug = true; 
	int lineWidth = 1;
	float linesLength = 0.5f;

	uint objectCandidatesBeforeFrustrumPrune = 0; 
	uint objectCandidatesAfterFrustrumPrune = 0;

public: 
	float3 smokepos[2] = { float3(0, 3.5f, 0), float3(10, 3.5f, 10) }; 
	bool rocketoAction = false; 
};
