#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "player.h"// ���������� ��������� � �������
#include "map.h"
#include "global.h"
#include "View.h"
#include "Entity.h"

using namespace std;
  int main()
  {
//������ ����
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();// �������� ����� �����������
	sf::RenderWindow window(sf::VideoMode(640, 700, desktop.bitsPerPixel), "TANKZZZ");// ������������� ������ ���� � ����� �����������
	view.reset(sf::FloatRect(0, 0, 640, 700));
	//camera.reset(sf::FloatRect(0,0,640,550));
	Font font;//����� 
	Font death_font;
	death_font.loadFromFile("CHILLER.ttf");
    font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������
Text text("", font, 20);//������� ������ �����. ������ ������(� ��������);
//��� ������ ����� (�� ������)
text.setColor(Color::Red);//��������� ����� � �������.
text.setStyle(Text::Bold);//������ �����.

Text death_text("", death_font, 40);
death_text.setColor(Color::Black);
death_text.setStyle(Text::Bold);


	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/tank.png");//��������� ���� ��� �����

	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	Image expl_image;
	expl_image.loadFromFile("images/tank.png" );//��������� �����������

    expl_image.createMaskFromColor(Color(0, 0, 0));// ������� ����� ���

	Texture expl;
	expl.loadFromImage(expl_image); // ��������� ����������� � ��������

	Sprite s_expl;
	s_expl.setTexture(expl);
	


	float CurrentExplFrame= 0;
	float CurrentFrame = 0;//������ ������� ����
	Clock clock;
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ���� 
	int gameTime = 0;
	Image heroImage;
	
	heroImage.loadFromFile("images/hero.png");
	heroImage.createMaskFromColor(Color(255, 255, 255));
	Player p(heroImage,50,50, 32.0, 32.0,"Player1");
	

	int createObjectForMapTimer = 0;
	int ret = 0;
	while (window.isOpen())// ���� ���� ������� �����
	{
		
		float time = clock.getElapsedTime().asMicroseconds();// ����� ����� � �������������
		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		clock.restart();// ���������� ��������
		time = time / 800;// ������������� �������� ����
		
		createObjectForMapTimer += time;//���������� ������
		if (createObjectForMapTimer>400){
			
			if (p.MaxObj<3)
			{
				p.MaxObj+=1;
			    ret=p.MaxObj;
			randomMapGenerate();//���������  ������
	        createObjectForMapTimer = 0;//�������� ������
			}
			else {
				createObjectForMapTimer = 0;
			}
			cout << ret;
		}
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)// ���� �� ���� ������ ������� ���� ������������
				window.close();
		} // ��

		
		
		
		    p.update(time);
			



		//	cameramap(time);
			//window.setView(camera);

			//�������� ����������� ������ � �������
//���� ����������� ���������, �� "health = 0", ����� ��������������� � 
//��������� ��������� "you are lose"


	
			window.clear();// ������ ����
		                 

		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
		if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(133, 100, 32, 32)); //����
				//��������� ������ ������, �� ������ 1-� ���������
		if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(300, 0, 32, 32));//����
				//��������� ������ s, �� ������ 2� ���������
		if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 102, 32, 32));//����
				//��������� ������ 0, �� ������ 3� ���������
		if ((TileMap[i][j] == 't')) s_map.setTextureRect(IntRect(299, 101, 30, 30));//����
				//��������� ������ 0, �� ������ 3� ���������
			s_map.setPosition(j * 32, i * 32);//������������ ���������� � �����.

			
			

			window.draw(s_map);//������ ���������� �� �����
			
			}

		
	std::ostringstream playerHealthString, gameTimeString;//�������� ���������� �������� � �������
playerHealthString << p.health; gameTimeString << gameTime;//��������� ������
text.setString("��������: " + playerHealthString.str() + "\n����� ����: " + gameTimeString.str());//������ ������ ������
text.setPosition(view.getCenter().x-200, view.getCenter().y-250);//������ ������� ������
window.draw(text);//������ ���� �����
if (p.state!=5)
{
	getplayercoor(p.GetPlayerCoordinateX(),p.GetPlayerCoordinateY());
}
window.setView(view);
window.draw(p.sprite);	
window.display();
		if (p.life==false) 
		{    
		
			CurrentExplFrame += 0.001*time;// ���������� �������� �� �� ������� ������� ������ ������, ����� ������� �� ��������� ����

			if (CurrentExplFrame > 3) CurrentExplFrame -= 3; 
			s_expl.setTextureRect(IntRect((1+33 * int(CurrentExplFrame)), 1, 32, 32)); // ����������� �� ������ �����
			s_expl.setPosition(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
			death_text.setString("LOL YOU DIED LOL LOL YOU DIED ");//������ ������ ������
        death_text.setPosition(view.getCenter().x-180, view.getCenter().y-100);//������ ������� ������
        window.draw(death_text);//������ ���� �����
		
			window.draw(p.sprite);
			window.draw(s_expl);
			window.display();
			 
		
		}
	}
window.clear();
	return 0;
	}