#include "hintText.h"
hintText::hintText() {
	textFont.loadFromFile("data/Fonts/SourceHanSansCN-ExtraLight.ttf");
}
void hintText::setText(int type) {				
	hint.setFont(textFont);
	hint.setCharacterSize(40);
	switch (type) {
	case 0: break;
	case -1:
		hint.setString(L"魔力不足，不可使用！");
		break;
	case -2:
		hint.setString(L"本回合不可攻击对手！");
		break;
	case -3:
		hint.setString(L"您已有随从！");
		break;
	case 1:
		//hint.setString(L"同归于尽！！");
		break;
	case 2:
		//hint.setString(L"本回合玩家赢了！");
		break;
	case 3:
		//hint.setString(L"本回合玩家输了！");
		break;
	
	}
	hint.setPosition(600, 400);
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	hint.setFillColor(color);
	isShow = true;
	clock.restart();
}
void hintText::showHint(RenderWindow* window) {						
	if (isShow) {
		if (clock.getElapsedTime().asMilliseconds() > 500) {
			color.a = 255 - (clock.getElapsedTime().asMilliseconds() - 500) / 10;
			hint.setFillColor(color);
		}
		if (clock.getElapsedTime().asMilliseconds() < 3050) {
			window->draw(hint);
		}
		else {
			isShow = false;
		}
	}
}
