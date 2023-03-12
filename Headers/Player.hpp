#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <SFML/Window.hpp>

#include "CommandQueue.hpp"

class Player {
public:
	enum Action {
		MoveUp,
		MoveDown,
		MoveLeft,
		MoveRight,
		PrintPosition,
	};

	Player();
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);
	void assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(Action action) const;

private:
	static bool isRealtimeAction(Action action);
	void initializeActions();
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action, Command> mActionBinding;
};

#endif
