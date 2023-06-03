#include "Headers/SnakeGameOverState.hpp"
#include "Headers/Button.hpp"
#include "Headers/ResourceHolder.hpp"
#include "Headers/Utility.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

SnakeGameOverState::SnakeGameOverState(StateStack &stack, Context context)
    : State(stack, context), mBackgroundSprite(), mPausedText(),
      mGUIContainer() {
  sf::Font &font = context.fonts->get(Fonts::Main);
  sf::Vector2f windowSize(context.window->getSize());

  mPausedText.setFont(font);
  mPausedText.setString("Game Over");
  mPausedText.setCharacterSize(70);
  centerOrigin(mPausedText);
  mPausedText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

  auto retryButton =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  retryButton->setPosition(0.5f * windowSize.x - 100,
                            0.4f * windowSize.y + 75);
  retryButton->setText("Retry");
  retryButton->setCallback([this]() {
    requestStackPop();
    requestStackPop();
    requestStackPush(States::SnakeGame);});
  retryButton->setTextColor(sf::Color::Black);

  auto backToMenuButton =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  backToMenuButton->setPosition(0.5f * windowSize.x - 100,
                                0.4f * windowSize.y + 125);
  backToMenuButton->setText("Back to games");
  backToMenuButton->setCallback([this]() {
    requestStateClear();
    requestStackPush(States::Menu);
    requestStackPush(States::Games);
  });
  backToMenuButton->setTextColor(sf::Color::Black);

  mGUIContainer.pack(retryButton);
  mGUIContainer.pack(backToMenuButton);
}

void SnakeGameOverState::draw() {
  sf::RenderWindow &window = *getContext().window;
  window.setView(window.getDefaultView());

  sf::RectangleShape backgroundShape;
  backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
  backgroundShape.setSize(window.getView().getSize());

  window.draw(backgroundShape);
  window.draw(mPausedText);
  window.draw(mGUIContainer);
}

bool SnakeGameOverState::update(sf::Time) { return false; }

bool SnakeGameOverState::handleEvent(const sf::Event &event) {
  mGUIContainer.handleEvent(event);
  return false;
}

