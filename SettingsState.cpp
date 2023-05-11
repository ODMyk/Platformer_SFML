#include "SettingsState.hpp"
#include "Keybindings.hpp"
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

  addButtonLabel(Keybindings::Left, 150.f, "Move Left", context);
  addButtonLabel(Keybindings::Right, 200.f, "Move Right", context);
  addButtonLabel(Keybindings::Up, 250.f, "Move Up", context);
  addButtonLabel(Keybindings::Down, 300.f, "Move Down", context);
  addButtonLabel(Keybindings::Interact, 350.f, "Interact", context);

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

  for (std::size_t action = 0; action < Keybindings::KeyCount; ++action) {
    if (mBindingButtons[action]->isActive()) {
      isKeyBinding = true;
      if (event.type == sf::Event::KeyPressed) {
        getContext().binds->assignKey(event.key.code,
                                      static_cast<Keybindings::Events>(action));
        mBindingButtons[action]->deactivate();
      }
      break;
    }
  }

  if (isKeyBinding) {
    updateLabels();
  } else
    mGUIContainer.handleEvent(event);

  return false;
}

void SettingsState::updateLabels() {
  Keybindings &player = *getContext().binds;

  for (std::size_t i = 0; i < Keybindings::KeyCount; ++i) {
    sf::Keyboard::Key key =
        player.getAssignedKey(static_cast<Keybindings::Events>(i));
    mBindingLabels[i]->setText(keyNames[int(key) + 1]);
  }
}

void SettingsState::addButtonLabel(Keybindings::Events action, float y,
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
