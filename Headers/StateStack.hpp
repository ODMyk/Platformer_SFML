#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>

#include "State.hpp"
#include "StateIdentifiers.hpp"

class StateStack: private sf::NonCopyable {
public:
	enum Action {
		Push,
		Pop,
		Clear,
	};

	explicit StateStack(State::Context context);

	template <typename T>
	void registerState(States::ID stateID);
	void draw();
	void handleEvent(const sf::Event& event);

	void pushState(States::ID stateID);
	void popState();
	void clearStates();

	bool isEmpty() const;

private:
	State::Ptr createState(States::ID stateID);
	void applyPendingChanges();

	struct PendingChange {
		Action action;
		States::ID stateID;
	};

	std::vector<State::Ptr> mStack;
	std::vector<PendingChange> mPendingList;
	State::Context mContext;
	std::map<States::ID, std::function<State::Ptr()>> mFactories;
};

#endif
