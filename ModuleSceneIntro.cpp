#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

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
	s_cube.Scale(100, 5, 100);
	pb_cube = App->physics->AddBody(s_cube, 0);
	pb_cube->SetPos(0, 25, 0);

	s_cube2.Scale(100, 5, 100);
	pb_cube2 = App->physics->AddBody(s_cube2, 0);
	pb_cube2->SetPos(0, 50, 100);

	s_cube3.Scale(100, 5, 100);
	pb_cube3 = App->physics->AddBody(s_cube3, 0);
	pb_cube3->SetPos(0, 25, 200);


	pb_cube3->GetTransform(&s_cube3.transform);
	pb_cube2->GetTransform(&s_cube2.transform);
	pb_cube->GetTransform(&s_cube.transform);

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
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	s_cube.Render();	
	s_cube2.Render();
	s_cube3.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

