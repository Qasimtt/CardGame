#include "Animation.h"
void Animation::bindFrames(Texture tFrames[], int Length) {
	frames = new Texture[Length];
	for (int i = 0; i < Length; i++) {
		frames[i] = tFrames[i];
	}
	frameLength = Length;
}
void Animation::play() {

	setTexture(frames[frameIndex]);
	frameIndex += 1;
	if (frameIndex == frameLength)
		frameIndex = 0;
}
Animation::Animation() {
	frameIndex = 0;
}
Animation::~Animation() {

}