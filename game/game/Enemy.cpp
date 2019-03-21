#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "Enemy.h"
#include "map.h"
#include "global.h"
using namespace std;
using namespace sf;

Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){
	if (name == "EasyEnemy"){
		
		
		sprite.setTextureRect(IntRect(331, 135, w, h));
		
		direction = rand() % (3); //����������� �������� ����� ����� ��������� �������
			//����� ��������� ��������� �����
			speed = 0.1;//���� ��������.���� ������ ������ ���������
			dx = speed;
		}
	}
void Enemy::checkCollisionWithMap(float Dx, float Dy)//�-��� �������� ������������ � ������
	{
		
	for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			
		if (TileMap[i][j] == '0')//���� ������� - ������ �����
			{
			if (Dy > 0) { y = i * 32 - h;  dy = -0.1; 
					direction = rand() % (4); //����������� �������� �����
						}//�� Y 
			if (Dy < 0) { y = i * 32 + 32; dy = 0.1;  
					direction = rand() % (4);//����������� �������� ����� 
						}//������������ � �������� ������ 
			if (Dx > 0) { x = j * 32 - w; dx = -0.1;  
					direction = rand() % (4);//����������� �������� ����� 
						}//� ������ ����� �����
					if (Dx < 0) { x = j * 32 + 32; dx = 0.1;  
					direction = rand() % (4); //����������� �������� �����
						}// � ����� ����� �����
				}
			}
	}

	void Enemy::update(float time)
	{
		if (name == "EasyEnemy"){//��� ��������� � ����� ������ ������ ����� �����

		if (life) {//���������, ��� �� �����
		switch (direction)//�������� ��������� �������� � ����������� �� ���������
		{
		case right:{
			dx=speed;
			dy=0;
			CurrentFrame += 0.005*time;// ���������� �������� �� �� ������� ������� ������ ������, ����� ������� �� ��������� ����
			
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((331+33 * int(CurrentFrame)), 199, 32, 32)); 			
			
			break;
			}
         case left:{//��������� ���� �����
			dx = -speed;
			dy=0;
		CurrentFrame += 0.005*time;
		// ���������� �������� �� �� ������� ������� ������ ������, ����� ������� �� ��������� ����

			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((331+33 * int(CurrentFrame)), 232, 32, 32)); // ����������� �� ������ �����
			
			break;
			}
		case up:{//���� �����
			dx = 0;
			dy = -speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((331+33 * int(CurrentFrame)), 133, 32, 32));			
			
			break;
			}
		case down:{//���� ����
			dx = 0;
			dy = speed;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 8) CurrentFrame -= 8; 
			sprite.setTextureRect(IntRect((331+33 * int(CurrentFrame)), 166 , 32, 32)); 				
			
			break;
			}
				  if (speed=0) state=stay;
		case stay:{//�����
			dy = speed;
			dx = speed;
			break;
			}

		}
		}

		x += dx*time; //�������� �� �X�
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �

		y += dy*time; //�������� �� �Y�
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y

		sprite.setPosition(x, y); //������ � ������� (x, y).

		if (health <= 0){ life = false; }//���� ������ ������ 0, ���� ����� 0, �� �������
		}
		};
	