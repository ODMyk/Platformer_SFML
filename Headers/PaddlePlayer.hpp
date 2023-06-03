#ifndef PADDLEPLAYER_HPP
#define PADDLEPLAYER_HPP

#pragma once
#include "PongEntity.hpp"

class paddle_player : public PongEntity {
public:
	paddle_player(int player);
	void update();
private:
	int playerNumber;
};

#endif