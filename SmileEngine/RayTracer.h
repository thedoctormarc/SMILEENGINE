#pragma once

#include "Glew/include/GL/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "Glew/lib/glew32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

#include "SmileApp.h"
#include "SmileCamera3D.h"
#include "SmileScene.h"
#include "SmileInput.h"
#include "SmileWindow.h"

#include "MathGeoLib/include/MathGeoLib.h"


#ifdef NDEBUG //no debug
#pragma comment (lib, "MathGeoLib/libx86/ReleaseLib/MathGeoLib.lib") 
#else
#pragma comment (lib, "MathGeoLib/libx86/DebugLib/MathGeoLib.lib") 
#endif

namespace rayTracer
{
	bool AssignSelectedMeshOnMouseClick(int mouse_x, int mouse_y)
	{
		// translate from window coordinates to inverted Y in OpenGL 
		float mouse_X_GL, mouse_Y_GL; 
		GLfloat mouse_Z_GL;
		mouse_X_GL = mouse_x;
		mouse_Y_GL = std::get<int>(App->window->GetWindowParameter("Height")) - mouse_y; 
		
		// Get matrixes and also a Z component to the mouse click
		GLint viewport[4];
		GLdouble projMatrix[16];  
		GLdouble mvMatrix[16];  

		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);

		glReadPixels(mouse_X_GL, mouse_Y_GL, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &mouse_Z_GL);

		// Unproject to find the final point coordinates in the world
		GLdouble fPos[3]; 
		gluUnProject(mouse_X_GL, mouse_Y_GL, mouse_Z_GL, mvMatrix, projMatrix, viewport, &fPos[0], &fPos[1], &fPos[2]);
		math::float3 fPosMath(fPos[0], fPos[1], fPos[2]);
		
		// trace a ray (line) from the camera to the point 
		math::float3 cameraPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
		math::float3 dir = (fPosMath - cameraPos).Normalized();
		math::Ray ray = math::Ray(cameraPos, dir);
		uint nIntersections = 0; 
		int foundAt[2] = { INT_MAX, INT_MAX }; // will store fbx and mesh index eg. "fbs.at(1).meshes.at(3)"
		int k = 0, j = 0; 

		// Loop meshes in the screen and find an intersection
		for (auto& fbx : App->scene_intro->fbxs)
		{
			for (auto& mesh : fbx.meshes)
			{
				for (int i = 0; i < mesh.num_vertex; i += 9) // 3 vertices * 3 (x,y,z) 
				{
					math::float3 v1(mesh.vertex[i], mesh.vertex[i + 1], mesh.vertex[i + 2]);
					math::float3 v2(mesh.vertex[i + 3], mesh.vertex[i + 4], mesh.vertex[i + 5]);
					math::float3 v3(mesh.vertex[i + 6], mesh.vertex[i + 7], mesh.vertex[i + 8]);

					math::Triangle tri = math::Triangle(v1, v2, v3);
					
					// check if the arbitrary ray interesects with the face (triangle) 
					if (ray.Intersects(tri))
					{
						foundAt[0] = k; 
						foundAt[1] = j;
					}
						
				
				}

				++j; 
			}
			++k;
		}
			
		// If clicked inside an object, select it, otherwise unselect the current selected
		if (foundAt[0] != INT_MAX && foundAt[1] != INT_MAX)
		{
			App->scene_intro->selected_mesh = &App->scene_intro->fbxs.at(foundAt[0]).meshes.at(foundAt[1]);
			LOG("Selected Mesh in the scene :)"); 
			return true; 
		}	
		else
		{
			App->scene_intro->selected_mesh = nullptr;
			LOG("Unselected Mesh in the scene :o");
			return false; 
		}
			
		return false; 
	}
}