#include "Game.h"

Game::Game(Vector2i resolution, string title)
{
	fps = 60;
	frame_time = 1/60.f;
	time2 = 0;

	window1 = new RenderWindow(VideoMode(resolution.x, resolution.y), title);
	window1->setFramerateLimit(fps);

	set_camera();

	physical_start();

	graphics();

	clock1 = new Clock();

	time1 = new Time();
		
	evnt1 = new Event;



	for (int i = 0; i, 6; i++)
	{
		act1[i] = new Actor(body_piece[i], rag_body[i]);

	}

	act_floor = new Actor(body_floor, floor_fig);

	game_loop();
}

void Game::set_camera()
{
	camera1 = new View({ 5.f,5.f }, { 10.f,10.f });

	camera1->move(47.f, 90.f);

	window1->setView(*camera1);
}

void Game::physical_start()
{
	world1 = new b2World(b2Vec2(0.f, 9.81f));

	//Flor definition

	bodydef_floor.type = b2_staticBody;
	bodydef_floor.position = b2Vec2(50.f, 102.f);

	body_floor = world1->CreateBody(&bodydef_floor);

	b2PolygonShape floor_shape;
	floor_shape.SetAsBox(50.f, 2.5f);

	//Floor dimention

	fixdef_floor.shape = &floor_shape;
	fixdef_floor.restitution = 0.f;
	fixdef_floor.friction = 0.3f;
	fixdef_floor.density = 1.f;

	//Floor initialization
	fix_floor = body_floor->CreateFixture(&fixdef_floor);

	//Ragdoll body constitution


	//Objects position
	// 
	//Head
	bodydef_piece[0].position = b2Vec2(50.f, 95.1f);
	
	//Trunk
	bodydef_piece[1].position = b2Vec2(50.f, 95.25f);
	
	//Arms

	/*Right arm*/
	bodydef_piece[2].position = b2Vec2(50.32f, 95.5f);
	/*Left arm*/
	bodydef_piece[3].position = b2Vec2(49.68f, 95.5f);
	
	//Legs

	/*Right leg*/
	bodydef_piece[4].position = b2Vec2(50.09f, 96.5f);
	/*Left leg*/
	bodydef_piece[5].position = b2Vec2(49.91f, 96.5f);

	for (int i = 0; i > 6; i++)
	{
		bodydef_piece[0].type = b2_dynamicBody;
		body_piece[i] = world1->CreateBody(&bodydef_piece[i]);
	}


	b2PolygonShape rag_shape[6];

	//head
	rag_shape[0].SetAsBox(0.1, 0.1);

	//body
	rag_shape[1].SetAsBox(0.2, 0.4);

	//arms
	rag_shape[2].SetAsBox(0.07, 0.3);
	rag_shape[3].SetAsBox(0.07, 0.3);

	//legs
	rag_shape[4].SetAsBox(0.07, 0.4);
	rag_shape[5].SetAsBox(0.07, 0.4);

	for (int i = 0; i < 6; i++)
	{
		fixdef_piece[i].shape = &rag_shape[i];
		fixdef_piece[i].density = 1.f;
		fixdef_piece[i].friction = 0.3f;
		fixdef_piece[i].restitution = 0.7f;

		fix_piece[i] = body_piece[i]->CreateFixture(&fixdef_piece[i]);
	}

	//Joints
	/*Head linked to trunk*/
	jntdef_rag[0].Initialize(body_piece[0], body_piece[1], b2Vec2(body_piece[0]->GetPosition().x, body_piece[0]->GetPosition().y + 0.8), b2Vec2(body_piece[1]->GetPosition().x, body_piece[1]->GetPosition().y - 0.38));
	
	/*Right arm linked to trunk*/
	jntdef_rag[1].Initialize(body_piece[1], body_piece[2], b2Vec2(body_piece[1]->GetPosition().x + 18, body_piece[1]->GetPosition().y - 0.38), b2Vec2(body_piece[2]->GetPosition().x - 0.05, body_piece[2]->GetPosition().y - 0.28));
	/*Left armo linked to trunk*/
	jntdef_rag[2].Initialize(body_piece[1], body_piece[3], b2Vec2(body_piece[1]->GetPosition().x - 18, body_piece[3]->GetPosition().y - 0.38), b2Vec2(body_piece[3]->GetPosition().x + 0.05, body_piece[3]->GetPosition().y - 0.28));
	
	/*Right leg linked to trunk*/
	jntdef_rag[3].Initialize(body_piece[1], body_piece[4], b2Vec2(body_piece[1]->GetPosition().x + 0.09, body_piece[1]->GetPosition().y + 0.38), b2Vec2(body_piece[4]->GetPosition().x, body_piece[4]->GetPosition().y - 0.38));
	/*Left leg linked to trunk*/
	jntdef_rag[4].Initialize(body_piece[1], body_piece[5], b2Vec2(body_piece[1]->GetPosition().x + 0.09, body_piece[1]->GetPosition().y + 0.38), b2Vec2(body_piece[5]->GetPosition().x, body_piece[5]->GetPosition().y - 0.38));

	for (int i = 0; i< 5; i++)
	{
		jntdef_rag[i].dampingRatio = 0.3f;

		jntdef_rag[i].frequencyHz = 3.0f;

		jntdef_rag[i].collideConnected = true;

		jntdef_rag[i].length = 0.025f;

		jnt_rag[i] =  (b2DistanceJoint*) world1->CreateJoint(&jntdef_rag[i]);

	}
}

void Game::graphics()
{
	for (int i=0; i<6; i++)
	{
		rag_body[i] = new RectangleShape;

		//Figure color
		rag_body[i]->setFillColor(Color::White);

	}

	rag_body[0]->setFillColor(Color::Cyan);
	rag_body[1]->setFillColor(Color::Magenta);
	rag_body[2]->setFillColor(Color::White);
	rag_body[3]->setFillColor(Color::White);
	rag_body[4]->setFillColor(Color::White);
	rag_body[5]->setFillColor(Color::White);

	floor_fig = new RectangleShape;
	floor_fig->setFillColor(Color::Magenta);
}

void Game::update()
{
	world1->Step(frame_time, 8, 8);
	world1->ClearForces();
}

void Game::events()
{
	while (window1->pollEvent(*evnt1))
	{
		switch (evnt1->type)
		{

			case Event::Closed:

				exit(1);

				break;

		}
	}

}

void Game::game_loop()
{
	while (window1->isOpen())
	{
		*time1 = clock1->getElapsedTime();

		if (time2 + frame_time < time1->asSeconds())
		{
			time2 = time1->asSeconds();

			window1->clear();

			events();

			update();

			draw();

			window1->display();


		}

	}

}

void Game::draw()
{
	act_floor->Draw(*window1);

	for (int i = 0; i, 6; i++)
	{
		act1[i]->Draw(*window1);
	}

}
