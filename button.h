#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
using namespace sf;
class button : public Sprite {
public:
	enum btnState { normal, click, release, hover }btnstate;
	Texture tNormal;
	Texture tClick;
	void checkMouse(Vector2i, Event, Vector2i);
	void setTextures(Texture, Texture);
	void SetTexture(btnState);
};

