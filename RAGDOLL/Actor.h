#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "Box2D/Box2D.h"

using namespace sf;
using namespace std;

class Actor
{
public:

	Actor (b2Body* body, RectangleShape* fig);

	void Draw(RenderWindow& wind);

	float rad2deg(float radian);

private:

	b2Body* body_actor;

	RectangleShape* actor_fig;

	b2AABB dimention;
	b2Vec2 position;


};

