#include "Card.h"
#include <cmath>

card::card() {
	cardstate = cardPool;
}
card::~card() {

}
void card::move(Vector2i mouse) {
	bool xTrue; bool yTrue;
	xTrue = yTrue = false;
	if (mouse.x - originMousePosition.x > 0) xTrue = true;
	if (mouse.y - originMousePosition.y > 0) yTrue = true;
	this->setPosition(originPosition.x + (abs(mouse.x - originMousePosition.x) > 500 ?(xTrue ==true?500:-500): mouse.x - originMousePosition.x),
		originPosition.y + (abs(mouse.y - originMousePosition.y) > 1150 ? (yTrue == true ? 1150 : -1150) : mouse.y - originMousePosition.y));
}
void card::init(cardType _cardtype) {
	this->cardtype = _cardtype;
	switch (this->cardtype) {
	case Attack:
		this->cost = 3;
		break;
	case Choas:
		this->cost = 1;
		break;
	case Revenge:
		this->cost = 2;
		break;
	case Defense:
		this->cost = 1;
		break;
	case Thorn:
		this->cost = 2;
		break;
	case Stone:
		this->cost = 3;
		break;
	case Spectral:
		this->cost = 4;
		break;
	case Soul:
		this->cost = 3;
		break;
	case Abyssal:
		this->cost = 1;
		break;
	default:
		break;
	}
}