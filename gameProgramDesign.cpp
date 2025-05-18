#include "gameDesign.h"
#include <iostream>

Game::Game() {
	topi = 0;
	windowWidth = 1600;
	windowHeight = 900;
	window.create(VideoMode(windowWidth, windowHeight), L"OurGame",Style::Titlebar| Style::Close);

}
Game::~Game() {

}

void Game::initial() {
	startMusicState = true;
	fightMusicState = false;
	window.setFramerateLimit(60);
	loadMediaData();
	gameSceneState = SCENE_START;
	Turnover = gameOver = gameQuit = false;
	getcardstate = true;
	firstTurn = playerTurn = true;
	secondTurn = false;
	changeTurn = false;
	gameStartMusic.play();
}

void Game::initialLoading() {
	stringstream ss;
	for (int i = 0; i < 6; i++) {
		ss <<"data/images/"<<i+1<<"-removebg-preview.png";
		tloads[i].loadFromFile(ss.str());
		ss.str("");
	}
	anLoading.bindFrames(tloads, sizeof(tloads) / sizeof(tloads[0]));
	anLoading.setScale(4, 4);
}

void Game::loadMediaData() {
	tBoard.loadFromFile("data/images/����.png");
	if (!gameStartMusic.openFromFile("data/music/����.ogg")) {
		cout << "�Ҳ���data/music/game.ogg" << endl;
	}
	if (!fightMusic.openFromFile("data/music/ս��.ogg")) {
		cout << "�Ҳ���data/music/game.ogg" << endl;
	}
	
	dialog.setSize(sf::Vector2f(400, 300));
	dialog.setFillColor(sf::Color(50, 50, 50));
	dialog.setOutlineThickness(2);
	dialog.setOutlineColor(sf::Color::White);

	
	pauseText.setFont(font);
	pauseText.setString(L"��ĻغϽ�����");
	pauseText.setCharacterSize(48);
	pauseText.setFillColor(sf::Color::White);

	OverText.setFont(font);
	OverText.setCharacterSize(48);
	OverText.setFillColor(sf::Color::White);

	font.loadFromFile("data/Fonts/SourceHanSansCN-ExtraLight.ttf");
	clock.setFont(font);

	tBackground.loadFromFile("data/images/����.png");
	tStartBackground.loadFromFile("data/images/��ʼ�ı���.png");
	tDiscardPlayer.loadFromFile("data/images/����Ͱ.png");
	tDiscardEnemy.loadFromFile("data/images/����Ͱ.png");
	spBackground.setTexture(tBackground);
	spStartBackground.setTexture(tStartBackground);
	spTop.setTexture(tTop);
	spBottom.setTexture(tBottom);
	spDiscardPlayer.setTexture(tDiscardPlayer);
	spDiscardEnemy.setTexture(tDiscardEnemy);

	tBtnClick.loadFromFile("data/images/overd.png");
	tBtnNormal.loadFromFile("data/images/over.png");
	if (!tStartBtnNormal.loadFromFile("data/images/��ʼ��ť.png")) {
		cout << "�Ҳ���data/button/start.png" << endl;
	}

	if (!tStartBtnClick.loadFromFile("data/images/��ʼ��ťd.png")) {
		cout << "�Ҳ���data/button/startClick.png" << endl;
	}

	if (!tbackToMenuNormal.loadFromFile("data/images/back.png")) {
		cout << "�Ҳ���data/button/start.png" << endl;
	}

	if (!tbackToMenuClick.loadFromFile("data/images/backd.png")) {
		cout << "�Ҳ���data/button/startClick.png" << endl;
	}
	
	startBtn.setTextures(tStartBtnNormal,  tStartBtnClick);
	backToMenuBtn.setTextures(tbackToMenuNormal, tbackToMenuClick);

	Btn.setTextures(tBtnNormal, tBtnClick);

	loadcardData();
	loadCharacter();

	isLoaded.store(true, std::memory_order_release);
}
void Game::loadcardData() {
	tallcard[0][0].loadFromFile("data/images/ʥ��ն��.png");
	tallcard[1][0].loadFromFile("data/images/ǿ������.png");
	tallcard[2][0].loadFromFile("data/images/����֮��.png");

	tallcard[0][1].loadFromFile("data/images/ʥ��ն��d.png");
	tallcard[1][1].loadFromFile("data/images/ǿ������.d.png");
	tallcard[2][1].loadFromFile("data/images/����֮��.d.png");

	tallcard[3][0].loadFromFile("data/images/��������.png");
	tallcard[4][0].loadFromFile("data/images/��������.png");
	tallcard[5][0].loadFromFile("data/images/ʯ�������.png");

	tallcard[3][1].loadFromFile("data/images/��������.d.png");
	tallcard[4][1].loadFromFile("data/images/��������.d.png");
	tallcard[5][1].loadFromFile("data/images/ʯ�������.d.png");

	tallcard[6][0].loadFromFile("data/images/������ʿ.png");
	tallcard[7][0].loadFromFile("data/images/������.png");
	tallcard[8][0].loadFromFile("data/images/��Ӱ����.png");

	tallcard[6][1].loadFromFile("data/images/������ʿ.d.png");
	tallcard[7][1].loadFromFile("data/images/������.d.png");
	tallcard[8][1].loadFromFile("data/images/��Ӱ����.d.png");

	cards[0].setTextures(tallcard[0][0], tallcard[0][1]);
	cards[1].setTextures(tallcard[1][0], tallcard[1][1]);
	cards[2].setTextures(tallcard[2][0], tallcard[2][1]);
	cards[3].setTextures(tallcard[3][0], tallcard[3][1]);
	cards[4].setTextures(tallcard[4][0], tallcard[4][1]);
	cards[5].setTextures(tallcard[5][0], tallcard[5][1]);
	cards[6].setTextures(tallcard[6][0], tallcard[6][1]);
	cards[7].setTextures(tallcard[7][0], tallcard[7][1]);
	cards[8].setTextures(tallcard[8][0], tallcard[8][1]);

	cards[0].init(card::cardType::Attack);
	cards[1].init(card::cardType::Choas);
	cards[2].init(card::cardType::Revenge);
	cards[3].init(card::cardType::Defense);
	cards[4].init(card::cardType::Thorn);
	cards[5].init(card::cardType::Stone);
	cards[6].init(card::cardType::Spectral);
	cards[7].init(card::cardType::Soul);
	cards[8].init(card::cardType::Abyssal);
}
void Game::loadMusic() {
	gameStartMusic.setLoop(true);			//��������ѭ��
	fightMusic.setLoop(true);
	switch (gameSceneState) {
	case SCENE_START:
		fightMusic.stop();
		if (startMusicState) {			//���ֿ���
			gameStartMusic.play();
		}
		else {
			gameStartMusic.stop();
		}break;
	case SCENE_FIGHT:
		gameStartMusic.stop();
		if (fightMusicState) {			//���ֿ���
			fightMusic.play();
		}
		else {
			fightMusic.stop();
		}break;
	default:
		break;
	}
}

void Game::loadCharacter() {

	tStone[0].loadFromFile("data/images/���ʯ���.1��ת.png");
	tSpectral[0].loadFromFile("data/images/���������ʿ.1��ת.png");
	tThorn[0].loadFromFile("data/images/����.png");
	tRevenge[0].loadFromFile("data/images/����.png");

	tStone[1].loadFromFile("data/images/���ʯ���.png");
	tSpectral[1].loadFromFile("data/images/���������ʿ.png");
	tThorn[1].loadFromFile("data/images/����.png");
	tRevenge[1].loadFromFile("data/images/����.png");

	tHp.loadFromFile("data/images/Ѫ��.png");
	tMp.loadFromFile("data/images/����.png");
	tExtraHp.loadFromFile("data/images/�ʹ�.png");
	tDefense.loadFromFile("data/images/����.png");

	spStone[0].setTexture(tStone[0]);
	spSpectral[0].setTexture(tSpectral[0]);
	spThorn[0].setTexture(tThorn[0]);
	spRvenge[0].setTexture(tRevenge[0]);

	spStone[1].setTexture(tStone[1]);
	spSpectral[1].setTexture(tSpectral[1]);
	spThorn[1].setTexture(tThorn[1]);
	spRvenge[1].setTexture(tRevenge[1]);

	player.tCharacter.loadFromFile("data/images/����1.png");
	player.setTexture(player.tCharacter);

	enemy.tCharacter.loadFromFile("data/images/����2.png");
	enemy.setTexture(enemy.tCharacter);

	player.LoadSpriteAttribute(tHp, tMp, tDefense, tExtraHp);
	enemy.LoadSpriteAttribute(tHp, tMp, tDefense, tExtraHp);
}

void Game::input(Vector2i mousePosition, Event event) {

	Vector2i cardOffset={10,0};
	
	backToMenuBtn.checkMouse(mousePosition, event, {0,0});


	if (backToMenuBtn.btnstate == button::btnState::release||((player.callcardState > 0 || enemy.callcardState > 0)&&!Turnover)) {
		gameSceneState = SCENE_START;
		startMusicState = true;
		fightMusicState = false;
		backToMenuBtn.btnstate = button::btnState::normal;
		loadMusic();
	}
	
	Btn.checkMouse(mousePosition, event, {0,0});
	if (Btn.btnstate == button::btnState::release) {
		changeTurn = true;
		delayTimer.restart();
	}

	if (changeTurn) {
		Turnover = true;

		if (playerTurn && player.firstTurn) {
			player.firstTurn = false;
		}
		else if (!playerTurn && enemy.firstTurn) enemy.firstTurn = false;
		else {
			if (playerTurn)player.mp > 8 ? player.mp = 10 : player.mp += 2;
			else enemy.mp > 8 ? enemy.mp = 10 : enemy.mp += 2;
		}

		if (playerTurn) {
			player.getHurted = false;
			enemy.thornState = false;
		}
		else {
			enemy.getHurted = false;
			player.thornState = false;
		}

		playerTurn = !playerTurn;
		changeTurn = false;
		if (player.handcardMax != player.handcardnums || enemy.handcardMax != enemy.handcardnums)
			getcardstate = true;
	}

	if (playerTurn) {
		for (int i = 0; i < player.handcardnums; i++) {
			if (i == player.handcardnums - 1) {
				cardOffset.x = 0; cardOffset.y = 0;
			}
			if (player.handcards[i].cardstate == card::cardState::handPool)
				player.handcards[i].checkMouse(mousePosition, event, cardOffset);
		}

		for (int i = 0; i < player.handcardnums; i++) {
			if (player.handcards[i].btnstate == button::btnState::release) {
				player.getEffect(mousePosition, i, &enemy);
				player.discard(mousePosition, i, spDiscardPlayer);
			}

		}
		if (player.callcardState < 0) {
			hint.setText(player.callcardState);
			player.callcardState = 0;
		}
	}
	else {

		cardOffset = { 10,0 };

		for (int i = 0; i < enemy.handcardnums; i++) {
			if (i == enemy.handcardnums - 1) {
				cardOffset.x = 0; cardOffset.y = 0;
			}
			if (enemy.handcards[i].cardstate == card::cardState::handPool)
				enemy.handcards[i].checkMouse(mousePosition, event, cardOffset);
		}

		for (int i = 0; i < enemy.handcardnums; i++) {
			if (enemy.handcards[i].btnstate == button::btnState::release) {
				enemy.getEffect(mousePosition, i, &player);
				enemy.discard(mousePosition, i, spDiscardEnemy);
			}
		}
		if (enemy.callcardState < 0) {
			hint.setText(enemy.callcardState);
			enemy.callcardState = 0;
		}
	}
	if (player.callcardState > 0 || enemy.callcardState > 0) {
		Turnover = true;
		delayTimer.restart();
	}
}

void Game::Input() {
	Event event;
	Vector2i mousePosition = Mouse::getPosition(window);
	while (window.pollEvent(event)) {				//�����¼�
		if (event.type == Event::Closed) {
			window.close();							//�رռ��رմ���
			gameQuit = true;
		}
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape) {
			window.close();							//��esc���رմ���
			gameQuit = true;
		}
		switch (gameSceneState) {
			case SCENE_START:
				startInput(mousePosition, event); break;
			case SCENE_FIGHT:
				if(!Turnover) input(mousePosition, event);break;
			default:
				break;
		}
	}
}

void Game::startInput(Vector2i mousePosition, Event event) {
	Vector2i cardOffset = { 0,0 };
	
	startBtn.checkMouse(mousePosition, event, cardOffset);
	if (startBtn.btnstate == button::btnState::release) {
		gameSceneState = SCENE_FIGHT;
		startMusicState = false;
		fightMusicState = true;
		startBtn.btnstate = button::btnState::normal;
		loadMusic();
		GameInit();
	}
}

RectangleShape createDarkMask(sf::Vector2u windowSize) {
	sf::RectangleShape mask;
	mask.setSize(sf::Vector2f(windowSize.x, windowSize.y));
	mask.setFillColor(Color(0, 0, 0, 150));
	return mask;
}

RectangleShape createHighlight(
	float x, float y,
	float width, float height,
	sf::Color color = sf::Color(255, 255, 255, 100))
{
	sf::RectangleShape highlight;
	highlight.setPosition(x, y);
	highlight.setSize(sf::Vector2f(width, height));
	highlight.setFillColor(color);
	return highlight;
}

void Game::Draw() {
	switch (gameSceneState) {
		case SCENE_START :
			drawStart();
			break;
		case SCENE_FIGHT :
			draw();
			break;
		default:
			break;
	}
}
void Game::drawCharacter() {

	enemy.setPosition(1200, 200);
	player.setPosition(100, 200);
	window.draw(player);
	window.draw(enemy);
	int pos = 0;
	if(enemy.callcardState <= 0 && player.callcardState <= 0){
		if (player.StoneState) {
			spStone[0].setPosition(360, 440);
			window.draw(spStone[0]);
		}
		else if (player.SpectralState) {
			spSpectral[0].setPosition(350, 400);
			window.draw(spSpectral[0]);
		}
		
		if (player.thornState) {
			spThorn[0].setPosition(20+50*pos, 200);
			window.draw(spThorn[0]);
			pos++;
		}
		if (player.getHurted) {
			spRvenge[0].setPosition(20+50*pos, 200);
			window.draw(spRvenge[0]);
		}
	}

	for (int i = 0; i < player.hp; i++) {
		player.spHp[i].setPosition(20 + i * 20, 100);
		window.draw(player.spHp[i]);
	}
	for (int i = 0; i < player.extraHp; i++) {
		player.spExtraHp[i].setPosition(20 + (i + player.hp) * 20, 100);
		window.draw(player.spExtraHp[i]);
	}
	for (int i = 0; i < player.mp; i++) {
		player.spMp[i].setPosition(15 + i * 20, 130);
		window.draw(player.spMp[i]);
	}
	for (int i = 0; i < player.defense; i++) {
		player.spDefense[i].setPosition( 15+ i * 20, 160);
		window.draw(player.spDefense[i]);
	}
	pos = 0;
	if (enemy.callcardState <= 0 && player.callcardState <= 0) {
		if (enemy.StoneState) {
			spStone[1].setPosition(1050, 440);
			window.draw(spStone[1]);
		}
		else if (enemy.SpectralState) {
			spSpectral[1].setPosition(1010, 400);
			window.draw(spSpectral[1]);
		}

		if (enemy.thornState) {
			spThorn[1].setPosition(1530 - 50 * pos, 200);
			window.draw(spThorn[1]);
			pos++;
		}

		if (enemy.getHurted) {
			spRvenge[1].setPosition(1530 - 50 * pos, 200);
			window.draw(spRvenge[1]);
		}
	}

	for (int i = 0; i < enemy.hp; i++) {
		enemy.spHp[i].setPosition(1550 - i * 20, 100);
		window.draw(enemy.spHp[i]);
	}
	for (int i = 0; i < enemy.extraHp; i++) {
		enemy.spExtraHp[i].setPosition(1550 -  (i + enemy.hp) * 20, 100);
		window.draw(enemy.spExtraHp[i]);
	}
	for (int i = 0; i < enemy.mp; i++) {
		enemy.spMp[i].setPosition(1550 - i * 20, 130);
		window.draw(enemy.spMp[i]);
	}
	for (int i = 0; i < enemy.defense; i++) {
		enemy.spDefense[i].setPosition(1550 -  i * 20, 160);
		window.draw(enemy.spDefense[i]);
	}

}

void Game::draw() {
	window.clear();

	spPlayerBoard.setTexture(tBoard);
	spEnemyBoard.setTexture(tBoard);
	spPlayerBoard.setPosition(0, 600);
	spEnemyBoard.setPosition(950, 600);
	spBackground.setPosition(0, 0);


	spDiscardPlayer.setPosition(0, 500);
	spDiscardEnemy.setPosition(1520, 500);


	window.draw(spBackground);
	window.draw(spPlayerBoard);
	window.draw(spEnemyBoard);

	if (playerTurn) {
		auto playerMask = createHighlight(0, 0, 650, 900);
		window.draw(playerMask);
	}

	else {
		auto enemyMask = createHighlight(950, 0, 650, 900);
		window.draw(enemyMask);
	}

	Btn.setPosition(657, 670);
	backToMenuBtn.setPosition(657, 800);
	window.draw(Btn);
	window.draw(backToMenuBtn);

	window.draw(spDiscardPlayer);
	window.draw(spDiscardEnemy);

	drawCharacter();

	drawcard();

	drawText();
	
	window.display();
}
void Game::drawStart() {		
	window.clear();	
	spStartBackground.setPosition(0, 0);
	startBtn.setPosition(windowWidth / 2 - startBtn.getTexture()->getSize().x / 2 - 10, windowHeight / 2 - startBtn.getTexture()->getSize().y / 2 + 200);
	window.draw(spStartBackground);
	window.draw(startBtn);
	window.display();						
}


void Game::drawText() {
	hint.showHint(&window);

	ossClock.str("");
	ossClock << fixed << setprecision(0) << elapsed;
	clock.setString("Time: " + ossClock.str() + "/10");
	clock.setPosition(700, 0);
	window.draw(clock);

	if (Turnover&&(player.callcardState>0||enemy.callcardState>0)) {
		auto mask = createDarkMask(window.getSize());
		window.draw(mask);

		dialog.setPosition(
			(window.getSize().x - dialog.getSize().x) / 2,
			(window.getSize().y - dialog.getSize().y) / 2
		);
		if(player.callcardState == 3||enemy.callcardState == 3)
			OverText.setString(L"���غ�������ˣ�");
		else if (player.callcardState == 2 || enemy.callcardState == 2)
			OverText.setString(L"���غ����Ӯ�ˣ�");
		else if (player.callcardState == 1 || enemy.callcardState == 1)
			OverText.setString(L"ͬ���ھ���");

		OverText.setPosition(
			dialog.getPosition().x + (dialog.getSize().x - pauseText.getLocalBounds().width) / 2,
			dialog.getPosition().y + 50
		);
		
		window.draw(dialog);
		window.draw(OverText);
	}
	else if (Turnover) {
		auto mask = createDarkMask(window.getSize());
		window.draw(mask);

		dialog.setPosition(
			(window.getSize().x - dialog.getSize().x) / 2,
			(window.getSize().y - dialog.getSize().y) / 2
		);
		pauseText.setPosition(
			dialog.getPosition().x + (dialog.getSize().x - pauseText.getLocalBounds().width) / 2,
			dialog.getPosition().y + 50
		);

		window.draw(dialog);
		window.draw(pauseText);
	}
}

void Game::drawcard() {
	if (getcardstate) {
		enemy.getCards(cards, sizeof(cards) / sizeof(cards[0]));
		player.getCards(cards, sizeof(cards) / sizeof(cards[0]));
		getcardstate = false;
	}

	int pos = 0;
		for (int i = 0; i < enemy.handcardnums; i++) {
			if (enemy.handcards[i].cardstate == card::cardState::handPool) {
				if (enemy.handcards[i].btnstate == enemy.handcards[i].click&&!playerTurn) {
					enemy.handcards[i].move(Mouse::getPosition(window));
					topi = i;
				}
				else {
					enemy.handcards[i].SetTexture(button::btnState::normal);
					enemy.handcards[i].setPosition(1050 + pos * 140, 650);
					enemy.handcards[i].originPosition = enemy.handcards[i].getPosition();
					enemy.handcards[i].originMousePosition = Mouse::getPosition(window);
				}
				window.draw(enemy.handcards[i]); pos++;
			}
		}
		if (enemy.handcards[topi].cardstate == card::cardState::handPool) window.draw(enemy.handcards[topi]);
		topi = enemy.handcardnums - 1;
	pos = 0;
		for (int i = 0; i < player.handcardnums; i++) {
			if (player.handcards[i].cardstate == card::cardState::handPool) {
				if (player.handcards[i].btnstate == player.handcards[i].click&&playerTurn) {
					player.handcards[i].move(Mouse::getPosition(window));
					topi = i;
				}
				else {
					player.handcards[i].SetTexture(button::btnState::normal);
					player.handcards[i].setPosition(100 + pos * 140, 650);
					player.handcards[i].originPosition = player.handcards[i].getPosition();
					player.handcards[i].originMousePosition = Mouse::getPosition(window);
				}
				window.draw(player.handcards[i]); pos++;
			}
		}
		if (player.handcards[topi].cardstate == card::cardState::handPool) window.draw(player.handcards[topi]);
		topi = player.handcardnums - 1;
}

void Game::drawLoading() {
	anLoading.setPosition(550, 250);
	anLoading.play();

	window.draw(anLoading);
	window.display();
}

void Game::run() {
	do {
		initial();
		while (window.isOpen()) {
			Draw();
			Input();
			updateTimerLogic();
		}
	} while (!gameQuit);
}

void Game::initRun() {
	initialLoading();
	std::thread thLoad(&Game::loadMediaData, this);
	while (!isLoaded.load(std::memory_order_acquire))
		drawLoading();
	if (thLoad.joinable()) thLoad.join();
}

void Game::updateTimerLogic() {
	threshold = 10.0f;
	if (Turnover) {
		elapsed = 0.0f;
		timer.restart();
		delayED = delayTimer.getElapsedTime().asSeconds();
	}
	else elapsed = timer.getElapsedTime().asSeconds();

	if (delayED >= 1.0f) {
		Turnover = false;
		delayED = 0.0f;
	}

	if (elapsed >= threshold) {
		changeTurn = true;
		delayTimer.restart();
	}
	
}

void Game::GameInit() {
	timer.restart();
	player.reset();
	enemy.reset();
	Turnover = gameOver = gameQuit = false;
	getcardstate = true;
	firstTurn = playerTurn = true;
	secondTurn = false;
	changeTurn = false;
}
int WinMain() {
	Game game;
	srand((unsigned)time(NULL));
	game.initRun();
	game.run();
	return 0;
}
