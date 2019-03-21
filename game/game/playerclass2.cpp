#include "stdafx.h"
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Player.h"
#include "map.h"
#include <iostream>
#include "global.h"

//playerclass2.cpp
using namespace std;
using namespace sf;


Player::Player(Image &image, float X, float Y, int W, int H, std::string Name): Entity(image,X,Y,W,H,Name)
{ 
	
	MaxObj=0;
	state=stay;
	if (name=="Player1"){
	sprite.setTextureRect(IntRect(33, 0, w, h)); //������������� ��� �������
	/*
	File = F; //��� �����
	w = W; h = H; //������ � ������ �������
	dir=DIR; speed=SPEED;
	health = 100;
	MaxObj=0;
	x=50;
	y=50;
		//���������������� ���������� ����� � ������������
	life = true;//���������������� ���������� ���������� �����
	image.loadFromFile("images/" + File);//��������� �����������
    image.createMaskFromColor(Color(255, 255, 255));// ������� ����� ���
	texture.loadFromImage(image); // ��������� ����������� � ��������
	sprite.setTexture(texture); //�������� ������ ���������
	sprite.setTextureRect(IntRect(33, 0, w, h)); //������������� ��� �������
	*/
}
}
void Player::control()
{
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				state = left;
				speed = 0.08;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				state = right;
				speed = 0.08;
			}

			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				state = up;
				speed = 0.08;
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				state = down;
				speed = 0.08;
			}
		}
void Player::update(float time) //������� ��������� ������� ������. ��������� � ���� float time -
	//����� SFML, ���������� ���� �������� ����������, ����� ��������� ��������.
{
	if (life) {//���������, ��� �� �����
		control();//������� ���������� ����������
		switch (state)//��� �������� ��������� �������� � ����������� �� ���������
		{
		case right:{
			dx=speed;
			dy=0;
			CurrentFrame += 0.005*time;// ���������� �������� �� �� ������� ������� ������ ������, ����� ������� �� ��������� ����
			
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 66, 32, 32)); 			
			//getplayercoor(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}
         case left:{//��������� ���� �����
			dx = -speed;
			dy=0;
			CurrentFrame += 0.005*time;// ���������� �������� �� �� ������� ������� ������ ������, ����� ������� �� ��������� ����

			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 99, 32, 32)); // ����������� �� ������ �����
			//getplayercoor(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}
		case up:{//���� �����
			dx = 0;
			dy = -speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 0, 32, 32));			
			//getplayercoor(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}
		case down:{//���� ����
			dx = 0;
			dy = speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((33 * int(CurrentFrame)), 33, 32, 32)); 				
			//getplayercoor(GetPlayerCoordinateX(),GetPlayerCoordinateY());
			break;
			}

		
		case stay:
			 {//�����
				 
			dy = speed;
			dx = speed;
			break;
			}

		}

        x += dx*time; //�������� �� �X�
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �

		y += dy*time; //�������� �� �Y�
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y
		
		
		speed = 0;    //�������� ��������, ����� �������� �����������.
		
		//��������� - �����
		
		sprite.setPosition(x, y); //������������ ������ � ����� ������� (x, y).

		if (health <= 0){ life = false; }//���� ������ ������ 0, ���� ����� 0, �� ������� 
		}
	}

 float Player::GetPlayerCoordinateX()
 {
	 return x;
 }
  float Player::GetPlayerCoordinateY()
 {
	 return y;
 }
void Player::interactionWithMap()
{
	for (int i = y / 32; i < (y + h) / 32; i++)
		for (int j = x / 32; j<(x + w) / 32; j++){
			if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� �0�
					//(�����), �� ��������� "����������� ��������" ���������:
		{
			if (dy>0) {//���� �� ��� ����,
			y = i * 32 - h;//�� �������� (-h) ���������� �y� ���������. 
				//������� �������� ���������� �i� ������ ���������� �� ����� � 
				//����� �������� �� ������ ������� ���������.
			}
			if (dy<0){
			y = i * 32 + 32;//���������� � ��������� �����.	
			}
			if (dx>0){
			x = j * 32 - w;//���� ���� ������, �� ���������� �x� ����� 
							//����� (������ 0) ����� ������ ���������
			}
			if (dx < 0){
			x = j * 32 + 32; //���������� ���� �����
			}
		}	
			if (TileMap[i][j] == 's') { //���� ������ ����� 's' (������)
				health -= 40;
				MaxObj-= 1;
				TileMap[i][j] = ' ';//������� ������
			}
	}

}

void Player::checkCollisionWithMap(float Dx, float Dy)	{
for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
	for (int j = x / 32; j<(x + w) / 32; j++)
	{
		if (TileMap[i][j] == '0')//���� ������� ������ �����
		{
		if (Dy > 0) { y = i * 32 - h;  dy = 0; }//�� Y 
		if (Dy < 0) { y = i * 32 + 32; dy = 0; }//������������ � �������� ������ �����
		if (Dx > 0) { x = j * 32 - w; dx = 0; }//� ������ ����� �����
		if (Dx < 0) { x = j * 32 + 32; dx = 0; }// � ����� ����� �����
		}	
		if (TileMap[i][j] == 's') {
			health -= 40; //���� ����� ������, ���������� playerScore=playerScore+1;
			TileMap[i][j] = ' ';
		}
		
	}
};




