#include "Game.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <iostream>

Game::Game(): mWindow(sf::VideoMode(1280, 768), "Cool title"),
mFont(),
mWorld(mWindow),
textFPS(),
framesCount(0),
statTime(sf::seconds(0)),
FrameTime(sf::seconds(1.f/144.f)) {
	if (!mFont.loadFromFile("./resources/fonts/impact.ttf")) {
		std::cout << "An error occured when font was tried to load\n";
	}

	mWindow.setVerticalSyncEnabled(true);

	textFPS.setFont(mFont);
	textFPS.setFillColor(sf::Color::White);
	textFPS.setCharacterSize(10);
	textFPS.setPosition(10, 10);
	textFPS.setString("FPS:");
}

void Game::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen()) {
		processEvents();
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > FrameTime) {
			timeSinceLastUpdate -= FrameTime;
			processEvents();
			update(FrameTime);
		}
		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			mWindow.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) {
				mWindow.close();
			}
			break;
		case sf::Event::KeyReleased:
			break;
		default:
			break;
		}
		
		if (event.type == sf::Event::Closed) {
			mWindow.close();
		}
	}
}

void Game::update(sf::Time timedelta) {
	mWorld.update(timedelta);
}

void Game::updateStatistics(sf::Time timedelta) {
	statTime += timedelta;
	framesCount += 1;

	if (statTime.asSeconds() >= 1) {
		textFPS.setString("FPS: " + std::to_string(framesCount));

		statTime -= sf::seconds(1);
		framesCount = 0;
	}
}

void Game::render() {
	mWindow.clear();
	mWorld.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(textFPS);
	mWindow.display();
}
