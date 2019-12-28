#pragma once

#include <vector>
#include <map>
#include <variant>
#include <any>

#include "MathGeoLib/include/Math/float4.h"
#include "MathGeoLib/include/Math/float4x4.h"

#include "Component.h"


#include "FreeBillBoard.h"
#include "FreeTransform.h"

struct InitialRandomState
{
	float3 speed = float3::inf; 
	float4 color = float4::inf; 
};

struct CurrentState
{
	bool active;
	float life;
	float currentLifeTime; 
	float3 speed;
	float size;
	float transparency;
	float4 color;
	uint tileIndex = 0;  
	float lastTileframe = 0.f; 
	bool needTileUpdate = false; 
	// Stuff that is random, per-particle, can be stored here for updation:
	InitialRandomState randomData;
};

struct Particle
{
	FreeTransform transf;
	FreeBillBoard billboard;
	CurrentState currentState;

	float camDist = -floatMax; 
	bool operator<(Particle& other) { return this->camDist > other.camDist; }
};

// Once the particle system is created, this initialState is set to the recieved values 
// 1) Initial Value 2) Value over time, or no value (false)

struct InitialState
{
	// This Variables will be updated each frame if they have value over time (Current order: 0->5)
	std::pair<float, float> life = std::pair(1.f, 1.f);
	float3 speed = float3(0, 1, 0); // default
	std::pair<float, float> size = std::pair(1.f, 1.f); // initial & final
	float transparency = 0.f; 
	std::pair<float4, float4> color = std::pair(float4::inf, float4::inf); // initial & final
	std::pair<bool, float> tex = std::pair(false, 0.f); // has & anim speed 

};

enum class emmissionShape { CIRCLE, SPHERE, CONE }; // ... 
enum class blendMode { ADDITIVE, ALPHA_BLEND };
enum class lightMode { PER_EMITTER, PER_PARTICLE, NONE };


struct EmissionData
{
	bool gravity = true; 
	uint maxParticles = 100;
	std::string texPath = "empty"; 
	std::pair<bool, std::pair<float3, float3>> randomSpeed;
	std::pair<bool, std::pair<float4, float4>> randomColor; 
	float time = 0.5f, burstTime = 0.f, currenTime = 0.f,
		currentBustTime = 0.f, expireTime = 0.f, totalTime = 0.f;
	float3 spawnRadius = float3(5.f); // the radius or inner + outer
	emmissionShape shape = emmissionShape::CONE;
};

// This struct has it all: 
struct AllData
{
	// Generation
	EmissionData emissionData; 

	// Initial State
	InitialState initialState;
	// Modes
	blendMode blendmode = blendMode::ALPHA_BLEND;
	lightMode lightmode = lightMode::NONE; // TODO: maybe not :( 
};


class ComponentParticleEmitter; 
typedef void (ComponentParticleEmitter::*function)(Particle& p, float dt);

class ResourceMeshPlane;
class ResourceTexture;
class GameObject; 
class ComponentTransform; 

#define GLOBAL_GRAVITY 9.8f 
class ComponentParticleEmitter: public Component
{
public: 
	ComponentParticleEmitter(GameObject* parent); // Default emitter
	ComponentParticleEmitter(GameObject* parent, AllData data); // User defined 
	~ComponentParticleEmitter();

public: 
	void Update(float dt = 0); 
	void Draw();
	void CleanUp(); 
	void Enable() { active = true; data.emissionData.expireTime = 0.f; };
	void SetNewTexture(const char* path); 
	void SetMaxParticles(uint maxParticles);
	AllData GetData() { return data; };
	void OnSave(rapidjson::Writer<rapidjson::StringBuffer>& writer);

private: 
	// start
	void SetupMesh(); 
	void SetupTexture(); 
	void PushFunctions(); 


	// spawn
	void SpawnParticle(); 
	void BurstAction(float dt); 
	void DefaultSpawnAction(float dt); 
	float3 GetSpawnPos(); 

	// utilities
	float3 GetRandomRange(std::variant<float3, std::pair<float3, float3>> ranges);
	float4 GetRandomRange4(std::variant<float4, std::pair<float4, float4>> ranges);

	// cool
	inline void LifeUpdate(Particle& p, float dt);
	inline void SpeedUpdate(Particle& p, float dt);
	inline void SizeUpdate(Particle& p, float dt); // TODO 
	inline void ColorUpdate(Particle& p, float dt);
	inline void AnimUpdate(Particle& p, float dt); 

private: 
	uint_fast8_t lastUsedParticle = 0;
	std::vector<Particle> particles, drawParticles; 
	std::vector<function> pVariableFunctions; // They co-relate by order to particle state variables (Current order: 0->5)
	
public: 
	ResourceMeshPlane* mesh = nullptr; 
	ResourceTexture* texture = nullptr; 
	AllData data;
	// a pointer for easier access: 
	float4x4 camMatrix; 
	
};



