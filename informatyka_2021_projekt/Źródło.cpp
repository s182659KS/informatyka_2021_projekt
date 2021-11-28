/*
Temat projektu: Gra akcji Tank2021 (replika gry Tank1990)
Zakres projektu:Gra jednoosobowa polegaj�ca na zniszczeniu bazy wroga znajduj�cej si� po drugiej stronie planszy
r�wnocze�nie broni�c swojej przed czo�gami wroga (boty sterowane algorytmem), na planszy znajduj� si� r�nego rodzaju
przeszkody, z r�nych materia��w. Gracz mo�e sterowa� czo�giem za pomocom strza�ek i strzela�. Traci punkt pancerza
za ka�dym trafieniem. Punkty zdobywamy poprzez liczbe zniszczonych przeciwnik�w i czas rozrywki. Gra b�dzie mia�a kilka poziom�w, r�ni�cych si� poziomem trudno�ci rozgrywki.
*/


#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <math.h>
#pragma warning(disable:4996)
//GRACZ
class Player {//klasa dla gracza
private:
	sf::Texture plrtxt;//tekstura dla gracza
	sf::Sprite plrtank;//duszek dla gracza
	sf::IntRect ksztalt;//kszta�t sprit'a
	int pociski;
	float pancerz;
	sf::Vector2f pozycja;//wspolrzedne gracza
	float xVel = 10;//predkosc w poziomie
	float yVel = 10;//predkosc w pionie
	//sf::CircleShape tank;//czo�g
public:
	Player() {
		pozycja.x = 400;
		pozycja.y = 550;
		sf::IntRect ksztalt (200, 0, 50, 50);//niedzia�a tak
		plrtxt.loadFromFile("teksturaPlayer.png");
		plrtank.setTexture(plrtxt);
		plrtank.setPosition(pozycja);
		plrtank.setOrigin(25, 30);//�rodek sprita

		
	}
	void draw(sf::RenderWindow& window) {
			window.draw(plrtank);
	}
	float ruch(sf::RenderWindow& window) {//sterowanie pojazdem gracza
		float rotacja;
		float pi = 3.14159;
		rotacja = plrtank.getRotation()-90;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			plrtank.move(cos(rotacja*pi/180), sin(rotacja * pi / 180));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			plrtank.move(-cos(rotacja * pi / 180), -sin(rotacja * pi / 180));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			plrtank.rotate(-1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			plrtank.rotate(1);
		if(plrtank.getPosition().x <= 0)
			plrtank.move(1, 0);
		if (plrtank.getPosition().x >= window.getSize().x)
			plrtank.move(-1, 0);
		if (plrtank.getPosition().y <= 0)
			plrtank.move(0, 1);
		if (plrtank.getPosition().y >= window.getSize().y)
			plrtank.move(0, -1);
		//std::cout << "Rotacja:" << rotacja << std::endl;
		
		return rotacja;
	}
	int zderzenie() {//domy�lnie b�dzie pobiera� rozmaiar okna

	}
};
//PRZECIWNICY
class Enemy {//klasa dla bot�w -  przeciwnik�w
private:
	sf::Texture enmtxt;//tekstura
	sf::Sprite* enemy;//tablica obiektow
	int N;//liczba obiektow graf
	std::random_device rd;//randomizacja po�o�enia 
};

//OTOCZENIE
class ObjSrd {//elementy otoczenia
	sf::Sprite* wall;
	sf::Texture walltex;
	FILE* fp;
	int mapa[50][2];//tablica przechowuj�ca pozycje
	sf::Vector2f pozycja;
	std::random_device rd;
	

public:
	int n = 50;
	ObjSrd(int N) {
		walltex.loadFromFile("cegla.png");
		wall = new sf::Sprite[N];
		fp = fopen("mapa1.txt", "rb");
		for (int i = 0; i < N; i++) {
			fread(&mapa[i][1], sizeof(mapa), 1, fp);
			pozycja.x = mapa[i][1];
			fread(&mapa[i][2], sizeof(mapa), 1, fp);
			pozycja.y = mapa[i][2];
			std::cout << mapa[i][1] << " " << mapa[i][2] << std::endl;
			wall[i].setTexture(walltex);//nalozenie tekstury
			wall[i].setPosition(sf::Vector2f(pozycja.x, pozycja.y));//ustawienie pozycji poczatkowej
		}
		std::fclose(fp);
	}
		

	void generacja(int poziom) {//generatior rozmieszczenia element�w
		int const N = 50;//tymczasowo, domy�lnie dynamiczna alokacja pam.
		if (poziom == 1)
			int const N = 50;
		else if(poziom == 2)
			int const N = 75;
		else if (poziom == 3)
			int const N = 100;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distX(1, 27);
		std::uniform_int_distribution<> distY(1, 20);
		int tabB[N][2];
		fp = fopen("mapa1.txt", "w+b");
		for (int k = 0; k <= N; k++) {
			int j = distX(gen);
			int i = distY(gen);
			tabB[k][1] = (j * 30)-15;
			tabB[k][2] = (i * 30)-15;
			std::cout << tabB[k][1] << "," << tabB[k][2] << std::endl;
			fwrite(&tabB[k][1], sizeof(tabB[0][0]), 1, fp);
			fwrite(&tabB[k][2], sizeof(tabB[0][0]), 1, fp);
		}
	}
	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < n; i++)
		{
			//std::cout << "dzia�a";
			window.draw(wall[i]);
		}
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "TANK 2021");
	sf::Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int hight = size.y;
	Player p1;
	ObjSrd s1(50);
	while (window.isOpen())
	{
	
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
		}
		window.clear();
		p1.ruch(window); 
		s1.draw(window);
		p1.draw(window);
		window.display();
	}
	return 0;
}
