//Entity.h
#ifndef Entity_h
#define Entity_h
#include "stdafx.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class Entity {
public:
	enum { left, right, up, down, stay} state;// ��� ������������ - ��������� �������
	float dx, dy, x, y, speed;//�������� ���������� ������ ��� ������� �����
	int w, h, health; //���������� �health�, �������� ����� ������
	bool life; //���������� �life� �����, ����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������ 
	float CurrentFrame;//������ ������� ����
	std::string name;//����� ����� ���� ������, ������ ����� ��������� �� ������
	//������� ����� ���� ���� �������� � update() � ����������� �� �����
	virtual void update(float time)=0;
	Entity(Image &image, float X, float Y, int W, int H, std::string Name);// ����������� Entity
	virtual ~Entity(){ //����������� ����������
	};
	FloatRect getRect(); //�������� ���������� ����� �� � � �
};
#endif