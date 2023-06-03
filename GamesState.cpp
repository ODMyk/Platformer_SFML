#include "Headers/GamesState.hpp"
#include "Headers/Button.hpp"
#include "Headers/ResourceHolder.hpp"
#include "Headers/Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

GamesState::GamesState(StateStack &stack, Context context)
    : State(stack, context), mGUIContainer() {
  sf::Texture &texture = context.textures->get(Textures::TitleScreen);
  mBackgroundSprite.setTexture(texture);

  auto TopdownButton =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  TopdownButton->setPosition(540, 450);
  TopdownButton->setText("Topdown");
  TopdownButton->setCallback([this]() {
    requestStackPop();
    requestStackPush(States::Level1S);
  });

  auto SnakeButton =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  SnakeButton->setPosition(540, 500);
  SnakeButton->setText("Snake");
  SnakeButton->setCallback([this]() { requestStackPush(States::SnakeMenu); });

//  auto PongButton =
//      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
//  exitButton->setPosition(540, 550);
//  exitButton->setText("Ping Pong");
//  exitButton->setCallback([this]() { requestStackPop(); });

auto backButton =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  backButton->setPosition(540, 550);
  backButton->setText("Back");
  backButton->setCallback(std::bind(&GamesState::requestStackPop, this));


  TopdownButton->setTextColor(sf::Color::Black);
  SnakeButton->setTextColor(sf::Color::Black);
  backButton->setTextColor(sf::Color::Black);

  mGUIContainer.pack(TopdownButton);
  mGUIContainer.pack(SnakeButton);
//  mGUIContainer.pack(PingPongButton);
  mGUIContainer.pack(backButton);
}

void GamesState::draw() {
  sf::RenderWindow &window = *getContext().window;

  window.setView(window.getDefaultView());

  window.draw(mBackgroundSprite);
  window.draw(mGUIContainer);
}

bool GamesState::update(sf::Time) { return true; }

bool GamesState::handleEvent(const sf::Event &event) {
  mGUIContainer.handleEvent(event);
  return false;
}

