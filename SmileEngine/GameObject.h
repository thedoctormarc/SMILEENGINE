#pragma once
#include <map>
#include <vector>
#include "SmileSetup.h"
#include <variant>
 
#include "ComponentTypes.h"

class Component;
class ComponentMesh; 
// ----------------------------------------------------------------- [GameObject]
class GameObject
{
public: 
	GameObject();  
	GameObject(Component* comp);   
	GameObject(std::vector<Component*> components); 
	~GameObject() {}; 

public: 
	bool AddComponent(Component* comp); // you can add it to the GameObject or to a mesh
	bool AddComponentToMesh(Component* comp, ComponentMesh* mesh); // you can add it to the GameObject or to a mesh

	std::variant<Component*, std::vector<Component*>> GetComponent(COMPONENT_TYPE type) const
	{
		return components[type]; 
	}

	void Enable(); 
	void Update();
	void Disable();
	void CleanUp(); 

	void DrawMeshes(); 

private: 
	void FillComponentBuffers(); 

private: 
	std::variant<Component*, std::vector<Component*>> components[COMPONENT_TYPE::MAX_COMPONENT_TYPES]; // each component type has either one element or a vector 
	bool active = true; 


};