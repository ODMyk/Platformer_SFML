#include "PingPong.hpp"
#include "PongBall.hpp"
#include <iostream>

// MenuState::MenuState(StateStack &stack, Context context) : State(stack, context), mGUIContainer() {
PingPong::PingPong(StateStack &stack, Context context) : State(stack, context) {
    sf::RenderWindow &window = *getContext().window;
	// initialise the font
	this->font = new sf::Font();
	this->font->loadFromFile("resources/fonts/impact.ttf");

	// initialise the score texts
	this->player1Score = new score(*font, 32U);

	this->player2Score = new score(*font, 32U);
	this->player2Score->setPosition(window.getSize().x - this->player2Score->getGlobalBounds().width, 0);


	this->player1 = new paddle_player(0);
	this->player1->setPosition(30, window.getSize().y / 2);

	this->player2 = new paddle_player(1);
	// move player2 to the right
	this->player2->setPosition(window.getSize().x - this->player2->getGlobalBounds().width - 30, window.getSize().y / 2);

	this->theBall = new ball(this->player1, this->player2, player1Score, player2Score);
	
	this->theBall->setPosition(window.getSize().x / 2, window.getSize().y / 2);

	
}


void PingPong::draw() {
    sf::RenderWindow &window = *getContext().window;

	sf::Texture t;
    t.loadFromFile("resources/img/pp-bg-2.png");
    sf::Sprite s(t);
	window.draw(s);

	window.draw(*this->player1Score);
	window.draw(*this->player2Score);
	window.draw(*this->theBall);
	window.draw(*this->player1);
	window.draw(*this->player2);	
}


bool PingPong::update(sf::Time dt) {
    sf::RenderWindow &window = *getContext().window;
	this->player1->update();
	this->player2->update();
	this->theBall->update(&window);
	this->player1Score->update();
	this->player2Score->update();

    return true;
}

// void PingPong::Destroy(sf::RenderWindow* window) {
// 	delete this->player1;
// 	delete this->player2;
// 	delete this->theBall;
// 	delete this->player1Score;
// 	delete this->player2Score;

// }

bool PingPong::handleEvent(const sf::Event &event) {
//   CommandQueue &commands = mWorld.getCommandQueue();
//   mController.handleEvent(event, commands);

  if (event.type == sf::Event::KeyPressed &&
      event.key.code == sf::Keyboard::Escape)
    requestStackPush(States::Pause);
    // std::cout << event.type << "\n";
  return true;
}