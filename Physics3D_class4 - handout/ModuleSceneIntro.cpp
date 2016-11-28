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

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	/*
	btRigidBody* body = new btRigidBody(rbInfo);
	PhysBody3D* pbody = new PhysBody3D(body);
	AddBody(const Sphere& sphere, float mass)

	*/	for (int i = 0; i < MAX_SNAKE; ++i){
		pb_snake[i] = App->physics->AddBody(s_snake[i]);
		pb_snake[i]->SetPos(i*2, 10, 0);

	}
	for (int i = 0; i < MAX_SNAKE - 1; ++i) {
		App->physics->ConstrainUnion(pb_snake[i], pb_snake[i + 1]);

	}
	for (int i = 0; i < MAX_SNAKE; ++i) {
		pb_snake2[i] = App->physics->AddBody(s_snake2[i],i+0.1);
		pb_snake2[i]->SetPos(i*2, 5, 4);

	}
	for (int i = 0; i < MAX_SNAKE - 1; ++i) {
		App->physics->HingeUnion(pb_snake2[i], pb_snake2[i + 1], btVector3 (0,0,1), btVector3(0, 0,1));

	}
	pb_cube=App->physics->AddBody(s_cube);
	pb_cube->SetPos(6, 2, 5);
	

	// TODO 2: Chain few N spheres together to form a snake
	// TODO 4: Chain few N spheres together to form a a bike's sphere
	// Be sure to put the right axis

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

	for(int i = 0; i < MAX_SNAKE; ++i)
	{
		pb_snake[i]->GetTransform(&(s_snake[i].transform));
		s_snake[i].Render();
	}

	for(int i = 0; i < MAX_SNAKE; ++i)
	{
		pb_snake2[i]->GetTransform(&(s_snake2[i].transform));
		s_snake2[i].Render();
	}
	pb_cube->GetTransform(&s_cube.transform);
	s_cube.Render();
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

