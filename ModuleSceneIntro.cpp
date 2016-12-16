#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include <time.h>  

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	srand(time(NULL));

	/*CreateFloor(vec3(12, 1, 48), 0, 0, BOTTOM_FLOOR);
	CreateFloor(vec3(12, 1, 48), 12, 0, BOTTOM_FLOOR);
	CreateFloor(vec3(12, 1, 48), 24, 0, BOTTOM_FLOOR);
	CreateFloor(vec3(12, 1, 48), 36, 0, BOTTOM_FLOOR);
	*/
	/*
	TOP_FLOOR,					0
	BOTTOM_FLOOR,				1					
	BOTTOM_OBSTACLE_FLOOR,		2
	TOP_OBSTACLE_FLOOR,			3
	WALL,						4
	MIDDLE_FLOOR_B,				5
	MIDDLE_FLOOR_T,				6		
	BOTTOM_TO_MIDDLE,			7
	MIDDLE_TO_BOTTOM,			8	
	MIDDLE_TO_TOP,				9
	TOP_TO_MIDDLE,				10
	SLIDER,						11
	EMPTY_FLOOR,				12
	*/
	int floors[100] = {
		1,1,1,1,
		1,1,1,1,
		0,0,0,0,
		0,0,0,0,
		1,1,1,1,
		1,1,1,1,
		12,12,12,11,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		11,12,12,12,
		1,12,12,12,
		1,1,1,1,
		12,1,1,1,
		0,1,1,1,
		0,12,7,7,
		0,0,0,0,
		3,3,3,3,
		2,1,2,0,
		1,2,1,0,
		2,1,2,0,
		1,2,1,0,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
	};
	for (int j = 0; j < 25; j++) {
		for (int i = 0; i < 4; i++) {
			FLOOR_STYLE test = static_cast<FLOOR_STYLE>(floors[(4*j)+i]);

			CreateFloor(vec3(20, 1, 48), 20*i, 48*j, test);

		}
	}

	s_victory.Size(100, 30, 10);

	pb_victory = App->physics->AddBody(s_victory, 0);
	pb_victory->SetPos(30, 0, 1010);
	pb_victory->GetTransform(&s_victory.transform);
	pb_victory->SetAsSensor(true);
	pb_victory->collision_listeners.add(this);

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	

	if (pb_cubes.Count() != 0 && s_cubes.Count() != 0 && s_cubes.Count()== pb_cubes.Count()) {
		for (int i = 0; i < s_cubes.Count(); i++) {
			pb_cubes[i]->GetTransform(&s_cubes[i].transform);
			s_cubes[i].Render();
		}
		
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if((body1 == pb_victory) || (body2 == pb_victory))
	{
		App->player->win = true;
		App->player->win_timer.Start();
	}

}

void ModuleSceneIntro::CreateFloor(vec3 scale, int posX, int posZ, FLOOR_STYLE floor1)
{
	Cube s_cube;
	PhysBody3D* pb_cube;
	//body->setActivationState(4);

		switch (floor1)
		{
		case TOP_FLOOR:
			s_cube.Size(scale.x, scale.y, scale.z);
			s_cubes.PushBack(s_cube);
			pb_cube = App->physics->AddBody(s_cube,0);
			pb_cube->SetPos(posX, TOPFLOR_Y, posZ);
			pb_cubes.PushBack(pb_cube);
			break;
		case MIDDLE_FLOOR_B:
			s_cube.Size(scale.x, MIDDLE_SCALE, scale.z);
			s_cubes.PushBack(s_cube);
			pb_cube = App->physics->AddBody(s_cube, 0);
			pb_cube->SetPos(posX, (TOPFLOR_Y*0.5)*0.5, posZ);
			pb_cubes.PushBack(pb_cube);
			break;
		case MIDDLE_FLOOR_T:
			s_cube.Size(scale.x, MIDDLE_SCALE, scale.z);
			s_cubes.PushBack(s_cube);
			pb_cube = App->physics->AddBody(s_cube, 0);
			pb_cube->SetPos(posX, TOPFLOR_Y*0.5+((TOPFLOR_Y*0.5)*0.5), posZ);
			pb_cubes.PushBack(pb_cube);
			break;
		case BOTTOM_FLOOR:
			s_cube.Size(scale.x, scale.y, scale.z);
			s_cubes.PushBack(s_cube);
			pb_cube = App->physics->AddBody(s_cube, 0);
			pb_cube->SetPos(posX, scale.y*0.5, posZ);
			pb_cubes.PushBack(pb_cube);
			break;
		case BOTTOM_TO_MIDDLE:

			s_cube.Size(scale.x, RAMP_SCALE, scale.z+2);
			s_cube.SetRotation(-15, vec3(1, 0,0));

			s_cubes.PushBack(s_cube);
			pb_cube = App->physics->AddBody(s_cube, 0);
			pb_cube->SetPos(posX,0, posZ);
			pb_cubes.PushBack(pb_cube);
			break;
		case MIDDLE_TO_BOTTOM:

			s_cube.Size(scale.x, RAMP_SCALE, scale.z + 2);
			s_cube.SetRotation(15, vec3(1, 0, 0));

			s_cubes.PushBack(s_cube);
			pb_cube = App->physics->AddBody(s_cube, 0);
			pb_cube->SetPos(posX,0, posZ);
			pb_cubes.PushBack(pb_cube);
			break;
		case TOP_TO_MIDDLE:

			s_cube.Size(scale.x, RAMP_SCALE, scale.z + 2);
			s_cube.SetRotation(-15, vec3(1, 0, 0));

			s_cubes.PushBack(s_cube);
			pb_cube = App->physics->AddBody(s_cube, 0);
			pb_cube->SetPos(posX, TOPFLOR_Y, posZ);
			pb_cubes.PushBack(pb_cube);
			break;
		case MIDDLE_TO_TOP:

			s_cube.Size(scale.x, RAMP_SCALE, scale.z + 2);
			s_cube.SetRotation(15, vec3(1, 0, 0));

			s_cubes.PushBack(s_cube);
			pb_cube = App->physics->AddBody(s_cube, 0);
			pb_cube->SetPos(posX, TOPFLOR_Y, posZ);
			pb_cubes.PushBack(pb_cube);
			break;
		case WALL:

			s_cube.Size(scale.x, TOPFLOR_Y, scale.y);
			s_cubes.PushBack(s_cube);
			pb_cube = App->physics->AddBody(s_cube, 0);
			pb_cube->SetPos(posX, TOPFLOR_Y*0.5, posZ);
			pb_cubes.PushBack(pb_cube);
			break;
		case BOTTOM_OBSTACLE_FLOOR:
			//FLOOR
			s_cube.Size(scale.x, scale.y, scale.z);
			s_cubes.PushBack(s_cube);
			pb_cube = App->physics->AddBody(s_cube, 0);
			pb_cube->SetPos(posX, scale.y*0.5, posZ);
			pb_cubes.PushBack(pb_cube);

			//OBSTACLE
			s_cube.Size(scale.x, OBSTACLE_SCALE, 2);
			s_cubes.PushBack(s_cube);
			pb_cube = App->physics->AddBody(s_cube, 0);
			pb_cube->SetPos(posX, 3, posZ + (scale.x *0.5));
			pb_cubes.PushBack(pb_cube);
			break;
		case TOP_OBSTACLE_FLOOR:
			//FLOOR
			s_cube.Size(scale.x, scale.y, scale.z);
			s_cubes.PushBack(s_cube);
			pb_cube = App->physics->AddBody(s_cube, 0);
			pb_cube->SetPos(posX, TOPFLOR_Y, posZ);
			pb_cubes.PushBack(pb_cube);
			//OBSTACLE
			s_cube.Size(scale.x, OBSTACLE_SCALE, 2);
			s_cubes.PushBack(s_cube);
			pb_cube = App->physics->AddBody(s_cube, 0);
			pb_cube->SetPos(posX, TOPFLOR_Y-3, posZ + (scale.x*0.5));
			pb_cubes.PushBack(pb_cube);
			break;
		case SLIDER:
			//FLOOR
			s_cube.Size(scale.x, scale.y, scale.z);
			s_cubes.PushBack(s_cube);
			pb_cube = App->physics->AddBody(s_cube, 0);
			pb_cube->SetPos(posX, scale.y*0.5, posZ);
			pb_cubes.PushBack(pb_cube);
			//SLIDER OBSTACLE
			s_cube.Size(scale.x, OBSTACLE_SCALE, scale.y);
			s_cubes.PushBack(s_cube);
			pb_cube = App->physics->AddBody(s_cube, 100);
			pb_cube->SetPos(posX, TOPFLOR_Y*0.5, posZ + (scale.x*0.5));
			App->physics->AddConstraintSlider(*pb_cube, true);
			pb_cubes.PushBack(pb_cube);
			pb_cube->GetBody()->setActivationState(4);
			break;
		case EMPTY_FLOOR:
			break;
		default:
			break;
		}
		
	
}



