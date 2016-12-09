#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

enum CarState
{
	BOTTOM,
	CHANGING,
	TOP,
};
struct PhysVehicle3D;

#define MAX_ACCELERATION 2000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f
#define ROTATION_VALUE 4.0f
#define ROTATION_LIMIT 180.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	void RotateCar();
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
private:
	CarState state;
	float totalRotation;
	bool gravityChange;
	bool startRotation;
	
	
};