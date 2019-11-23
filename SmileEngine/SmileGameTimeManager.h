#pragma once

#include "Timer.h"
#include "SmileSerialization.h" // do not include this there
#include "SmileApp.h"
#include "SmileRenderer3D.h"
#include "SmileGui.h"

namespace TimeManager
{
	namespace
	{
		struct timeData
		{
			Uint32 frameCount = 0, gameTimeSec = 0, realTimeSec = 0;
			double gameTimeScale = 3, deltaGameFrameSec = 0, deltaRealFrameSec = 0;
		};

		timeData _timeData;
		Timer realTimeClock = Timer();
		Timer gameClock = Timer(false);
		static bool isPlaying = false; 
	}

	static bool IsPlaying() { return isPlaying; };

	static void PlayButton() 
	{
		if (isPlaying == false)
		{
			gameClock.Start();
			App->serialization->SaveScene();
			App->SetDtMultiplier(_timeData.gameTimeScale);
			App->renderer3D->SwitchCamera(); 
		//	App->window->SetFullscreen(SDL_WINDOW_FULLSCREEN_DESKTOP, (SDL_bool)true);
			App->scene_intro->generalDbug = !App->scene_intro->generalDbug; 
		}
		else
		{
			gameClock.Stop();
			App->serialization->LoadScene("Library/Scenes/scene.json");
			App->SetDtMultiplier(1.F);
	//		App->window->SetFullscreen(0, (SDL_bool)false);
			App->scene_intro->generalDbug = !App->scene_intro->generalDbug;
		}
	
		isPlaying = !isPlaying;
	}; 

	static void PauseButton()
	{

		if (IsPlaying() == true)
		{
			App->SetDtMultiplier(0.F);
			gameClock.Stop();
		}
		else
		{
			App->SetDtMultiplier(1.F);
			gameClock.Start();
		}
		
	}; 

	static void PlayOne() // mananage this in the gui v
	{

		/*if (IsPlaying() == false)
		{
			PlayButton(); 
			gameClock.PlayOne(); 
		}*/

	};

}

