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

  auto GamesButton =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  GamesButton->setPosition(540, 450);
  GamesButton->setText("Games");
  GamesButton->setCallback([this]() {
    requestStackPush(States::Games);
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

  GamesButton->setTextColor(sf::Color::Black);
  settingsButton->setTextColor(sf::Color::Black);
  exitButton->setTextColor(sf::Color::Black);

  mGUIContainer.pack(GamesButton);
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
