#include "Headers/Application.hpp"
#include "Headers/Level1.hpp"
#include "Headers/MenuState.hpp"
#include "Headers/PauseState.hpp"
#include "Headers/GamesState.hpp"
#include "Headers/SnakeMenuState.hpp"
#include "Headers/SnakeGameState.hpp"
#include "Headers/SnakeGameOverState.hpp"

#include "Headers/SettingsState.hpp"
#include "Headers/State.hpp"
#include "Headers/StateIdentifiers.hpp"
#include "Headers/TitleState.hpp"
#include "Headers/Utility.hpp"

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
    : mWindow(sf::VideoMode(1280, 720), "Cool Title", sf::Style::Close),
      mTextures(), mFonts(), mBinds(),
      mStateStack(State::Context(mWindow, mTextures, mFonts, mBinds)),
      mStatisticsText(), mStatisticsUpdateTime(), mStatisticsNumFrames(0) {
  mWindow.setKeyRepeatEnabled(false);

  mFonts.load(Fonts::Main, "resources/fonts/impact.ttf");
  mTextures.load(Textures::TitleScreen, "resources/img/TitleScreen.png");
  mTextures.load(Textures::ButtonNormal, "resources/img/Button0.png");
  mTextures.load(Textures::ButtonSelected, "resources/img/Button1.png");
  mTextures.load(Textures::ButtonPressed, "resources/img/Button2.png");

  mStatisticsText.setFont(mFonts.get(Fonts::Main));
  mStatisticsText.setPosition(5.f, 5.f);
  mStatisticsText.setCharacterSize(10u);

  registerStates();
  mStateStack.pushState(States::Title);
}

void Application::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while (mWindow.isOpen()) {
    sf::Time dt = clock.restart();
    timeSinceLastUpdate += dt;
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;

      processInput();
      update(TimePerFrame);

      if (mStateStack.isEmpty())
        mWindow.close();
    }

    updateStatistics(dt);
    render();
  }
}

void Application::processInput() {
  sf::Event event;
  while (mWindow.pollEvent(event)) {
    mStateStack.handleEvent(event);

    if (event.type == sf::Event::Closed)
      mWindow.close();
  }
}

void Application::update(sf::Time dt) { mStateStack.update(dt); }

void Application::render() {
  mWindow.clear();

  mStateStack.draw();

  mWindow.setView(mWindow.getDefaultView());
  mWindow.draw(mStatisticsText);

  mWindow.display();
}

void Application::updateStatistics(sf::Time dt) {
  mStatisticsUpdateTime += dt;
  mStatisticsNumFrames += 1;
  if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {
    mStatisticsText.setString("FPS: " + std::to_string(mStatisticsNumFrames));

    mStatisticsUpdateTime -= sf::seconds(1.0f);
    mStatisticsNumFrames = 0;
  }
}

void Application::registerStates() {
  mStateStack.registerState<TitleState>(States::Title);
  mStateStack.registerState<MenuState>(States::Menu);
  mStateStack.registerState<Level1>(States::Level1S);
  mStateStack.registerState<PauseState>(States::Pause);
  mStateStack.registerState<SettingsState>(States::Settings);
  mStateStack.registerState<GamesState>(States::Games);
  mStateStack.registerState<SnakeMenuState>(States::SnakeMenu);
  mStateStack.registerState<SnakeGameState>(States::SnakeGame);
  mStateStack.registerState<SnakeGameOverState>(States::SnakeGameOver);
}
