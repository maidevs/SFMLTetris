#include "SFML/Graphics.hpp"
#include <iostream>
#include "Piece.h"

using namespace sf;

const int R = 20;
const int C = 10;

int map[R][C] = {0};

int pieces[7][4] =
{
	1,3,5,7, //I
	2,4,5,7, //Z
	3,5,4,6, //S
	3,5,4,7, //T
	2,3,5,7, //L
	3,5,7,6, //J
	2,3,4,5, //O
};

#pragma region Game_System
RenderWindow renderWindow(sf::VideoMode(320, 480), "Title");

float gameTimer = 0;
float delay = 0.3f;
#pragma endregion Game_System

#pragma region Rendering
Texture texture;
Sprite sprite;
#pragma endregion Rendering

Piece *currPiece;

void initGame()
{
	texture.loadFromFile("assets/tiles.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 18, 18));
}

int dx = 0;
bool rotate;

void handleEvents()
{
	Event event;

	while (renderWindow.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			renderWindow.close();
		}
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Left)
			{
				dx = -1;
			}
			else if (event.key.code == Keyboard::Right)
			{
				dx = 1;
			}
			else if (event.key.code == Keyboard::Up)
			{
				rotate = true;
			}
		}
	}
}

void clearEventVariables()
{
	dx = 0;
	rotate = false;
}

void update()
{
	if (gameTimer > delay)
	{
		currPiece->movePieceY(1);
		gameTimer = 0;
	}

	if (dx != 0)
		currPiece->movePieceX(dx);
	
	if (rotate)
		currPiece->rotate();
}

void render()
{
	renderWindow.clear(Color::White);
	
	for (int i = 0; i < 4; i++)
	{
		sprite.setPosition(
			currPiece->getPositions()[i].x * 18,
			currPiece->getPositions()[i].y * 18
		);

		renderWindow.draw(sprite);
	}

	renderWindow.display();
}

int main()
{
	initGame();

	float delay = 0.3f;
	
	int dx = 0;

	Clock clock;

	currPiece = new Piece(pieces[1]);

	while (renderWindow.isOpen()) 
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		gameTimer += time;

		handleEvents();
		update();
		render();

		clearEventVariables();
	}

	return 0;
}

