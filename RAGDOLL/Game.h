#pragma once
#include "Actor.h"



class Game
{
public:

	Game(Vector2i resolution, string title);

	void set_camera();

	void physical_start();

	void graphics();

	void update();

	void events();

	void game_loop();

	void draw();


private:

	RenderWindow* window1;
	View* camera1;

	Event* evnt1;

	Time* time1;
	Clock* clock1;

	float fps, frame_time, time2;

	//World built

	b2World* world1;

	//Ragdoll built

	b2Body* body_piece[6];
	b2BodyDef bodydef_piece[6];
	b2Fixture* fix_piece[6];
	b2FixtureDef fixdef_piece[6];

	//Floor definition

	b2Body* body_floor;
	b2BodyDef bodydef_floor;
	b2Fixture* fix_floor;
	b2FixtureDef fixdef_floor;

	RectangleShape* rag_body[6];
	RectangleShape* floor_fig;

	Actor* act1[6];
	Actor* act_floor;

	//Joints

	b2DistanceJoint* jnt_rag[5];
	b2DistanceJointDef jntdef_rag[5];

};

