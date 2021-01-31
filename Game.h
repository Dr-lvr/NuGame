#pragma once
#include "TextureHolder.h"
#include <cassert>

class Game
{
public:
	Game();
	void run();
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	bool mIsMovingUp = false;
	bool mIsMovingDown = false; 
	bool mIsMovingLeft = false; 
	bool mIsMovingRight = false;
	bool flickFlock = false;
	float PlayerSpeed = 100;
	
private:
	TextureHolder textures;
	sf::RenderWindow mWindow;
	sf::Texture a_Texture;
	sf::Sprite playerPlane;
	sf::Sprite background;
	sf::Sprite missile;

	sf::Sprite zeppelin;
	std::vector<sf::Sprite>* enemy = new std::vector<sf::Sprite>(5);

};
Game::Game() : mWindow(sf::VideoMode(640, 410), "SFML Application"), textures(), playerPlane(), background() {

	textures.load(Textures::Airplane_1, "IMAGES/Textures/bombers_revised.png");
	textures.load(Textures::Landscape, "IMAGES/Textures/Landscape.png");
	textures.load(Textures::Zeppelin, "IMAGES/Textures/Zeppelin Boss.png");
	textures.load(Textures::Enemy, "IMAGES/Textures/enemy.png");
	//textures.load(Textures::Missile, "IMAGES/Textures/Missile.png");

	background.setTexture(textures.get(Textures::Landscape));
	playerPlane.setTexture(textures.get(Textures::Airplane_1));
	zeppelin.setTexture(textures.get(Textures::Zeppelin));
	zeppelin.setPosition(sf::Vector2f(250.f, 10.f));

	for (int i = 0; i < 5; ++i) {
		enemy->at(i).setTexture(textures.get(Textures::Enemy));
		enemy->at(i).setPosition(sf::Vector2f(i*90.f + 200, 200.f + i*20+50));
	}
	//missile.setTexture(textures.get(Textures::Missile));
}
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > sf::seconds(1.f / 60.f))
		{
			timeSinceLastUpdate -= sf::seconds(1.f / 60.f);
			processEvents();
			update(sf::seconds(1.f / 60.f));
		}
		render();
	}
}
void Game::handlePlayerInput(sf::Keyboard::Key key,
	bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}
void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}
void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	sf::Vector2f movementRoutine(0.f, 0.f);
	sf::Vector2f ZmovementRoutine(0.f, 0.f);
	if (mIsMovingUp) 
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight){
		movement.x += PlayerSpeed;
	}
	else {
		//player movement routine
		for (int i = 0; i < 6; ++i) {
			movementRoutine.y += 1;
			playerPlane.move(movementRoutine * deltaTime.asSeconds());
			movementRoutine.x -= 1;
			playerPlane.move(movementRoutine * deltaTime.asSeconds());
		}
	}
	/*
	for (int i = 0; i < 22; ++i) {
		ZmovementRoutine.y += 1;
		zeppelin.move(ZmovementRoutine * deltaTime.asSeconds());
	}
	for (int i = 0; i < 22; ++i) {
		ZmovementRoutine.y -= 1;
		zeppelin.move(ZmovementRoutine * deltaTime.asSeconds());
	}*/
	playerPlane.move(movement * deltaTime.asSeconds());
}
void Game::render()
{
	mWindow.clear();
	mWindow.draw(background);
	mWindow.draw(playerPlane);
	mWindow.draw(zeppelin);
	for (int i = 0; i < 5; ++i) {
		mWindow.draw(enemy->at(i));
	}
	//mWindow.draw(missile);
	mWindow.display();
}

