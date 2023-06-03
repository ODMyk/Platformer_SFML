#include "Headers/SnakeMenuState.hpp"
#include "Headers/Button.hpp"
#include "Headers/ResourceHolder.hpp"
#include "Headers/Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

SnakeMenuState::SnakeMenuState(StateStack &stack, Context context)
    : State(stack, context), mGUIContainer() {
  sf::Texture &texture = context.textures->get(Textures::TitleScreen);
  mBackgroundSprite.setTexture(texture);

  auto playButton =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  playButton->setPosition(540, 450);
  playButton->setText("Level 1");
  playButton->setCallback([this]() {
    requestStackPush(States::SnakeGame);

  });

  auto settingsButton =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  settingsButton->setPosition(540, 500);
  settingsButton->setText("Settings");
  settingsButton->setCallback([this]() { requestStackPush(States::Settings); });

  auto backButton =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  backButton->setPosition(540, 550);
  backButton->setText("Back");
  backButton->setCallback(std::bind(&SnakeMenuState::requestStackPop, this));


  playButton->setTextColor(sf::Color::Black);
  settingsButton->setTextColor(sf::Color::Black);
  backButton->setTextColor(sf::Color::Black);

  mGUIContainer.pack(playButton);
  mGUIContainer.pack(settingsButton);
  mGUIContainer.pack(backButton);
}

void SnakeMenuState::draw() {
  sf::RenderWindow &window = *getContext().window;

  window.setView(window.getDefaultView());

  window.draw(mBackgroundSprite);
  window.draw(mGUIContainer);
}

bool SnakeMenuState::update(sf::Time) { return true; }

bool SnakeMenuState::handleEvent(const sf::Event &event) {
  mGUIContainer.handleEvent(event);
  return false;
}

