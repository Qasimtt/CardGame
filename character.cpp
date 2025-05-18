#include "Character.h"
#include "Card.h"
#include <iostream>
character:: character() {
	extraHp = 0;
	extraAttack = 0;
	hp = 5;
	mp = 10;
	oriMp = mp;
	defense = 0;
	getcardstate = true;
	firstTurn = true;
	getHurted = false;
	thornState = false;
	StoneState = false;
	SpectralState = false;
	handcardnums = 3;

	handcardMax = 0;
	getcardnums = 3;

	callcardState = 0;
}
character::~character() {
}
int getRandom(int min,int max) {
	int random = rand() % (max - min + 1) + min;
	return random;
}
void function_attack(character* caller, character* opponent) {
	if (opponent->thornState) caller->defense -= 1;
	if (opponent->hp+opponent->extraHp >= 5)
		opponent->defense -= 2+caller->extraAttack;
	else{
		opponent->hp = 0;
		opponent->extraHp = 0;
	}
}
void function_defense(character* caller, character* opponent) {
	caller->defense = 3;
}
void function_revenge(character* caller, character* opponent) {
	if (opponent->thornState) caller->defense -= 1;
	if (caller->getHurted) opponent->defense -= 2 + caller->extraAttack;
	else opponent->defense -= 1 + caller->extraAttack;
}
void function_chaos(character* caller, character* opponent) {
	if (opponent->thornState) caller->defense -= 1;
	opponent->defense -= rand() % 3 + 4 + caller->extraAttack;
}
void function_thorn(character* caller, character* opponent) {
	caller->defense = 3;
	caller->thornState = true;
}
void function_stone(character* caller, character* opponent) {
	caller->StoneState = true;
	caller->SummonState = true;

	caller->extraHp = 5;
	caller->extraAttack = 1;
}
void function_soul(character* caller, character* opponent) {
	opponent->extraHp -= 2;
	caller->mp += 1;
}
void function_abyssal(character* caller, character* opponent) {
	caller->extraHp -= 2;
	opponent->extraHp -= 2;
	opponent->mp -= 2;
}
void function_spectral(character* caller, character* opponent) {
	caller->SpectralState = true;
	caller->SummonState = true;
	caller->extraAttack = 3;
	caller->extraHp = 1;
}


void character::getCards(card cards[], int cardsLength) {
	for (int i = 0; i < handcardnums; i++) {
		if (this->handcards[i].cardstate == card::cardState::cardPool) {
            int index = getRandom(0, cardsLength-1);
			cards[index].cardstate = card::cardState::handPool;
			this->handcards[i] = cards[index];
		}
	}
	handcardMax = getcardnums;
}
void character::getEffect(Vector2i mouse,int i,character* opponent) {
	if ((mouse.x > this->getPosition().x && mouse.x < this->getPosition().x + this->getTexture()->getSize().x) &&
		(mouse.y > this->getPosition().y && mouse.y < this->getPosition().y + this->getTexture()->getSize().y)) {
		if ((this->handcards[i].cardtype <= 2 || this->handcards[i].cardtype >= 7) && this->firstTurn) {
			this->callcardState = -2;
		}
		else if (this->mp < this->handcards[i].cost) {
			this->callcardState = -1;
		}
		else if (this->SummonState && (this->handcards[i].cardtype >= 5 && this->handcards[i].cardtype <= 6)) {
			this->callcardState = -3;
		}
		else {
			opponent->oriHp = opponent->hp;
			this->mp -= this->handcards[i].cost;

			this->funtion(this->handcards[i].cardtype, opponent);

			if (opponent->extraHp < 0) {
				opponent->hp += opponent->extraHp;
				opponent->extraHp = 0;
			}
			else if (opponent->defense < 0) {
				opponent->extraHp += opponent->defense;
				if (opponent->extraHp < 0) {
					opponent->hp += opponent->extraHp;
					opponent->extraHp = 0;
				}
				opponent->defense = 0;
			}
			
			if (opponent->hp <= 0 && this->hp <= 0) {
				this->hp = 0;
				opponent->hp = 0;
				this->callcardState = 1;
			}
			else if (opponent->hp <= 0) {
				std::cout << 1;
				opponent->hp = 0;
				this->callcardState = 2;
			}
			else if (this->hp <= 0) {
				std::cout << 2;
				this->hp = 0;
				this->callcardState = 3;
			}
			if (opponent->oriHp > opponent->hp) opponent->getHurted = true;

			if (opponent->extraHp == 0) {
				if (opponent->StoneState) opponent->StoneState = false;
				else if(opponent->SpectralState) opponent->SpectralState = false;
				opponent->SummonState = false;
				opponent->extraAttack = 0;
			}

			if (this->extraHp == 0) {
				if (this->StoneState) this->StoneState = false;
				else if (this->SpectralState) this->SpectralState = false;
				this->SummonState = false;
				this->extraAttack = 0;
			}
			this->handcards[i].cardstate = card::cardState::cardPool;
			this->handcards[i].btnstate = button::btnState::normal;
			this->handcardMax--;
		}
	}
}

void character::discard(Vector2i mouse, int i, Sprite spDiscard) {
	if ((mouse.x > spDiscard.getPosition().x && mouse.x < spDiscard.getPosition().x + spDiscard.getTexture()->getSize().x) &&
		(mouse.y > spDiscard.getPosition().y && mouse.y < spDiscard.getPosition().y + spDiscard.getTexture()->getSize().y)) {
		this->handcards[i].cardstate = card::cardState::cardPool;
		this->handcards[i].btnstate = button::btnState::normal;
		this->handcardMax--;
	}
}

void character::funtion(card::cardType _cardtype, character* opponent) {
	switch (_cardtype) {
	case 0:
		function_attack(this,opponent);
		break;
	case 1:
		function_chaos(this, opponent);
		break;
	case 2:
		function_revenge(this, opponent);
		break; 
	case 3:
		function_defense(this, opponent);
		break;
	case 4:
		function_thorn(this, opponent);
		break;
	case 5:
		function_stone(this, opponent);
		break;
	case 6:
		function_spectral(this, opponent);
		break;
	case 7:
		function_soul(this, opponent);
		break;
	case 8:
		function_abyssal(this, opponent);
		break;
	default:
		break;

	}
	
}
void character::LoadSpriteAttribute(Texture& tHp, Texture& tMp, Texture& tDefense, Texture& tExtraHp) {
	for (auto& sprite : spHp) {
		sprite.setTexture(tHp);
	}
	for (auto& sprite : spMp) {
		sprite.setTexture(tMp);
	}
	for (auto& sprite : spDefense) {
		sprite.setTexture(tDefense);
	}
	for (auto& sprite : spExtraHp) {
		sprite.setTexture(tExtraHp);
	}
}

void character::reset() {
	extraHp = 0;
	extraAttack = 0;
	hp = 10;
	mp = 10;
	oriMp = mp;
	defense = 3;
	getcardstate = true;
	firstTurn = true;
	getHurted = false;
	thornState = false;
	StoneState = false;
	SpectralState = false;
	handcardnums = 3;

	handcardMax = 0;
	getcardnums = 3;

	callcardState = 0;

	for (auto& cardi : this->handcards)
		cardi.cardstate = card::cardState::cardPool;
}