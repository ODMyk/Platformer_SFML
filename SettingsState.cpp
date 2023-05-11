#include "SettingsState.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

const static std::string keyNames[] = {
    "Unknown",   "A",         "B",        "C",        "D",        "E",
    "F",         "G",         "H",        "I",        "J",        "K",
    "L",         "M",         "N",        "O",        "P",        "Q",
    "R",         "S",         "T",        "U",        "V",        "W",
    "X",         "Y",         "Z",        "Num0",     "Num1",     "Num2",
    "Num3",      "Num4",      "Num5",     "Num6",     "Num7",     "Num8",
    "Num9",      "Escape",    "LControl", "LShift",   "LAlt",     "LSystem",
    "RControl",  "RShift",    "RAlt",     "RSystem",  "Menu",     "LBracket",
    "RBracket",  "Semicolon", "Comma",    "Period",   "Quote",    "Slash",
    "Backslash", "Tilde",     "Equal",    "Hyphen",   "Space",    "Enter",
    "Backspace", "Tab",       "PageUp",   "PageDown", "End",      "Home",
    "Insert",    "Delete",    "Add",      "Subtract", "Multiply", "Divide",
    "Left",      "Right",     "Up",       "Down",     "Numpad0",  "Numpad1",
    "Numpad2",   "Numpad3",   "Numpad4",  "Numpad5",  "Numpad6",  "Numpad7",
    "Numpad8",   "Numpad9",   "F1",       "F2",       "F3",       "F4",
    "F5",        "F6",        "F7",       "F8",       "F9",       "F10",
    "F11",       "F12",       "F13",      "F14",      "F15",      "Pause",
    "KeyCount"};

SettingsState::SettingsState(StateStack &stack, Context context)
    : State(stack, context), mGUIContainer() {
  mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

  addButtonLabel(Player::MoveLeft, 150.f, "Move Left", context);
  addButtonLabel(Player::MoveRight, 200.f, "Move Right", context);
  addButtonLabel(Player::MoveUp, 250.f, "Move Up", context);
  addButtonLabel(Player::MoveDown, 300.f, "Move Down", context);
  addButtonLabel(Player::PrintPosition, 350.f, "Print Position", context);

  updateLabels();

  auto backButton =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  backButton->setPosition(540.f, 425.f);
  backButton->setText("Back");
  backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));
  backButton->setTextColor(sf::Color::Black);

  mGUIContainer.pack(backButton);
}

void SettingsState::draw() {
  sf::RenderWindow &window = *getContext().window;

  window.draw(mBackgroundSprite);
  window.draw(mGUIContainer);
}

bool SettingsState::update(sf::Time) { return true; }

bool SettingsState::handleEvent(const sf::Event &event) {
  bool isKeyBinding = false;

  for (std::size_t action = 0; action < Player::ActionCount; ++action) {
    if (mBindingButtons[action]->isActive()) {
      isKeyBinding = true;
      if (event.type == sf::Event::KeyPressed) {
        getContext().player->assignKey(static_cast<Player::Action>(action),
                                       event.key.code);
        mBindingButtons[action]->deactivate();
      }
      break;
    }
  }

  if (isKeyBinding) {
    updateLabels();
  }
  else
    mGUIContainer.handleEvent(event);

  return false;
}

void SettingsState::updateLabels() {
  Player &player = *getContext().player;

  for (std::size_t i = 0; i < Player::ActionCount; ++i) {
    sf::Keyboard::Key key =
        player.getAssignedKey(static_cast<Player::Action>(i));
    mBindingLabels[i]->setText(keyNames[int(key) + 1]);
  }
}

void SettingsState::addButtonLabel(Player::Action action, float y,
                                   const std::string &text, Context context) {
  mBindingButtons[action] =
      std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  mBindingButtons[action]->setPosition(450.f, y);
  mBindingButtons[action]->setText(text);
  mBindingButtons[action]->setToggle(true);
  mBindingButtons[action]->setTextColor(sf::Color::Black);

  mBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
  mBindingLabels[action]->setPosition(680.f, y + 15.f);

  mGUIContainer.pack(mBindingButtons[action]);
  mGUIContainer.pack(mBindingLabels[action]);
}
