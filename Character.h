#pragma once
#include <SFML/Graphics.hpp>
#include "Card.h"
using namespace sf;
class character:public Sprite{
public:
	Texture tCharacter;
	Sprite spHp[20], spMp[10], spDefense[3], spExtraHp[5];
	int extraHp;
	int extraAttack;
	int oriHp;
	int oriMp;
	int hp;
	int mp;
	int defense;
	int handcardMax;
	int callcardState;
	bool firstTurn;
	bool getHurted;
	bool thornState;
	bool SummonState;
	bool StoneState;
	bool SpectralState;
	character();
	~character();
	card handcards[3];
	int handcardnums;
	int getcardnums;

	bool getcardstate;

	void getCards(card[], int);
	void getEffect(Vector2i, int, character*);
	void discard(Vector2i, int, Sprite);

	void funtion(card::cardType, character*);
	void reset();
	void LoadSpriteAttribute(Texture&,Texture&,Texture&,Texture&);
};