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
		pozycja.x = 200;
		pozycja.y = 200;
		sf::IntRect ksztalt (200, 0, 50, 50);//niedzia�a tak
		plrtxt.loadFromFile("teksturaPlayer.png");
		plrtank.setTexture(plrtxt);
		plrtank.setPosition(pozycja);
		plrtank.setOrigin(25, 30);//�rodek sprita

		
	}
	void draw(sf::RenderWindow& window) {
			window.draw(plrtank);
	}
	float ruch() {//sterowanie pojazdem gracza
		float rotacja;
		float pi = 3.14159;
		int mark = zderzenie();
		rotacja = plrtank.getRotation()-90;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& mark ==1)
			plrtank.move(cos(rotacja*pi/180), sin(rotacja * pi / 180));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mark == 1)
			plrtank.move(-cos(rotacja * pi / 180), -sin(rotacja * pi / 180));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mark == 1)
			plrtank.rotate(-1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mark == 1)
			plrtank.rotate(1);
		std::cout << "Rotacja:" << rotacja << std::endl;
		
		return rotacja;
	}
	int zderzenie() {//domy�lnie b�dzie pobiera� rozmaiar okna
		int marker;
		if (0 <= plrtank.getPosition().x <= 800)
			marker = 1;
		if (0 <= plrtank.getPosition().y <= 600)
			marker = 1;
		else
			marker = 0;
		return marker;
	}
};
class Enemy {//klasa dla bot�w -  przeciwnik�w
private:
	sf::Texture enmtxt;//tekstura
	sf::Sprite* enemy;//tablica obiektow
	int N;//liczba obiektow graf
	std::random_device rd;//randomizacja po�o�enia 
};
class ObjSrd {//elementy otoczenia

};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "TANK 2021");
	sf::Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int hight = size.y;
	Player p1;
	while (window.isOpen())
	{
	
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
		}
		window.clear();
		p1.ruch(); 
		p1.draw(window);
		window.display();
	}
	return 0;
}
