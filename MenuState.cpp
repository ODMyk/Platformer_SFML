#include "Headers/MenuState.hpp"
#include "Headers/Button.hpp"
#include "Headers/ResourceHolder.hpp"
#include "Headers/Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

MenuState::MenuState(StateStack &stack, Context context)
    : State(stack, context), mGUIContainer() {
  sf::Texture &texture = context.textures->get(Textures::TitleScreen);
  mBackgroundSprite.setTexture(texture);

  auto playButton =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  playButton->setPosition(540, 450);
  playButton->setText("Play");
  playButton->setCallback([this]() {
    requestStackPop();
    //requestStackPush(States::Level1S);
    requestStackPush(States::Level2S);
  });

  auto settingsButton =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  settingsButton->setPosition(540, 500);
  settingsButton->setText("Settings");
  settingsButton->setCallback([this]() { requestStackPush(States::Settings); });

  auto exitButton =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  exitButton->setPosition(540, 550);
  exitButton->setText("Exit");
  exitButton->setCallback([this]() { requestStackPop(); });

  playButton->setTextColor(sf::Color::Black);
  settingsButton->setTextColor(sf::Color::Black);
  exitButton->setTextColor(sf::Color::Black);

  mGUIContainer.pack(playButton);
  mGUIContainer.pack(settingsButton);
  mGUIContainer.pack(exitButton);
}

void MenuState::draw() {
  sf::RenderWindow &window = *getContext().window;

  window.setView(window.getDefaultView());

  window.draw(mBackgroundSprite);
  window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time) { return true; }

bool MenuState::handleEvent(const sf::Event &event) {
  mGUIContainer.handleEvent(event);
  return false;
}
