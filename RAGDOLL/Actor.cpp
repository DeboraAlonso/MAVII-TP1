#include "Actor.h"

Actor::Actor(b2Body* body, RectangleShape* fig) : body_actor(body), actor_fig(fig)
{
	position = body_actor->GetPosition();

	dimention.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	dimention.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);

	for (b2Fixture* i = body_actor->GetFixtureList(); i = i->GetNext();)
	{
		dimention = i->GetAABB(0);
	}
	
	actor_fig->setSize({ dimention.GetExtents().x * 2, dimention.GetExtents().y * 2 });

	actor_fig->setOrigin(actor_fig->getSize().x / 2.f, actor_fig->getSize().y / 2.f);

	actor_fig->setPosition(position.x, position.y);
}

void Actor::Draw(RenderWindow& wind)
{
	position = body_actor->GetPosition();

	actor_fig->setPosition(position.x, position.y);

	actor_fig->setRotation(rad2deg(body_actor->GetAngle()));

	wind.draw(*actor_fig);


}

float Actor::rad2deg(float radian)
{
	return radian * 180/3.14;
}
