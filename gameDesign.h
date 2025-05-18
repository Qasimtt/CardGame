#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <sstream>
#include <atomic>
#include <thread>
#include <iomanip>
#include "button.h"
#include "Character.h"
#include "Animation.h"
#include "hintText.h"
using namespace sf;
using namespace std;


class Game {
public:
	sf::RenderWindow window;
	enum gameSceneStates{ SCENE_START,SCENE_FIGHT }gameSceneState;
	int windowWidth;
	int windowHeight;
	int selected;
	int topi;
	bool gameOver, gameQuit;
	bool getcardstate;
	bool playerTurn;
	bool Turnover;
	bool changeTurn;
	bool firstTurn, secondTurn;
	std::atomic<bool> isLoaded{ false };
	button Btn;
	character player, enemy;
	card cards[9];
	Animation anLoading;
	Texture tallcard[9][2];
	Texture tBackground, tStartBackground,tTop, tBottom;
	Texture tStartBtnNormal, tStartBtnClick;		//加载纹理
	Texture tbackToMenuNormal, tbackToMenuClick;
	button startBtn, backToMenuBtn;												//自定义button类
	Texture tBtnClick, tBtnNormal;
	Texture tloads[6];
	Texture tDiscardPlayer, tDiscardEnemy;
	Text clock;
	Texture tStone[2], tSpectral[2], tRevenge[2], tThorn[2];
	ostringstream ossHp, ossMp, ossDefense, ossClock;
	Sprite spBackground, spStartBackground,spTop, spBottom;
	Sprite spStone[2], spSpectral[2], spThorn[2], spRvenge[2];
	Sprite sBK;
	Sprite spDiscardPlayer,spDiscardEnemy;
	Font font;
	Clock timer;
	float threshold, elapsed;
	Clock delayTimer;
	float delayTS, delayED;
	RectangleShape dialog;
	Text pauseText, OverText;
	hintText hint;
	Texture tBoard;
	Sprite spPlayerBoard, spEnemyBoard;
	Texture tHp, tExtraHp, tMp, tDefense;
	//Sprite spPlayerHp[], spEnemyHp, spPlayerMp, spEnemyMp, spPlayerDefense, spEnemyDefense, spPlayerExtraHp, spEnemyExtraHp;
	Music gameStartMusic, fightMusic;
	bool startMusicState, fightMusicState;


	Game();
	~Game();
	void initial();
	void initialLoading();
	void loadMediaData();
	void loadcardData();
	void loadCharacter();
	void input(Vector2i, Event);
	void draw();
	void drawcard();
	void drawText();
	void drawLoading();
	void updateTimerLogic();
	void run();
	void initRun();
	void drawStart();
	void startInput(Vector2i, Event);
	void Input();
	void Draw();
	void loadMusic();
	void drawCharacter();
	void GameInit();
};