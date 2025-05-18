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
		hint.setString(L"ħ�����㣬����ʹ�ã�");
		break;
	case -2:
		hint.setString(L"���غϲ��ɹ������֣�");
		break;
	case -3:
		hint.setString(L"��������ӣ�");
		break;
	case 1:
		//hint.setString(L"ͬ���ھ�����");
		break;
	case 2:
		//hint.setString(L"���غ����Ӯ�ˣ�");
		break;
	case 3:
		//hint.setString(L"���غ�������ˣ�");
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
