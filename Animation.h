#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Animation : public Sprite {
public:
	Texture* frames;
	int frameLength;
	int frameIndex;
	void bindFrames(Texture[], int);
	void play();
	Animation();
	~Animation();
};
