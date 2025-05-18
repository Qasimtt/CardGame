#include "button.h"

void button::setTextures(Texture _tNormal, Texture _tClick) {
	tNormal = _tNormal;
	tClick = _tClick;
	setTexture(tNormal);
}
void button::checkMouse(Vector2i mouse, Event event, Vector2i cardOffset) {
	if ((mouse.x > getPosition().x && mouse.x < getPosition().x + getTexture()->getSize().x-cardOffset.x) &&
		(mouse.y > getPosition().y && mouse.y < getPosition().y + getTexture()->getSize().y-cardOffset.y)) {
		if (event.type == Event::EventType::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			btnstate = click;
			SetTexture(btnstate);
		}
		else if (event.type == Event::EventType::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
			if (btnstate == click) btnstate = release;
			SetTexture(btnstate);
		}
		else {
			if(btnstate!=click) btnstate = hover;
			SetTexture(btnstate);
		}
	}
	else {																											//����ڰ�ť��Χ��
		if (event.type == Event::EventType::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {			//�ڷ�Χ���ͷ�������
			btnstate = normal;
			SetTexture(btnstate);																							//�ع�NORMAL״̬
		}
		else {	
			btnstate = normal;
			SetTexture(normal);																							//�����ͱ���ԭ�� ���簴ס���ŵ�ʱ��
		}
	}
}

void button::SetTexture(btnState btnstate) {
	switch (btnstate) {
	case 0:
	case 2:
	case 3:
		setTexture(tNormal); break;
	case 1:
		setTexture(tClick); break;
	default:
		break;
	}
}
