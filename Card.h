#pragma once
#include <SFML/Graphics.hpp>
#include "button.h"

using namespace sf;
class card : public button {
public:
	enum cardType { Attack, Choas, Revenge, Defense, Thorn, Stone, Spectral, Soul, Abyssal }cardtype;
	enum cardState { cardPool, handPool }cardstate;

	int cost;

	card();
	~card();
	void move(Vector2i);
	void init(cardType);
	Vector2f originPosition;
	Vector2i originMousePosition;
};