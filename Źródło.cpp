/*
Temat projektu: Gra akcji Tank2021 (replika gry Tank1990)
Zakres projektu:Gra jednoosobowa polegaj�ca na zniszczeniu bazy wroga znajduj�cej si� po drugiej stronie planszy
r�wnocze�nie broni�c swojej przed czo�gami wroga (boty sterowane algorytmem), na planszy znajduj� si� r�nego rodzaju
przeszkody, z r�nych materia��w. Gracz mo�e sterowa� czo�giem za pomocom strza�ek i strzela�. Traci punkt pancerza
za ka�dym trafieniem. Punkty zdobywamy poprzez liczbe zniszczonych przeciwnik�w i czas rozrywki. Gra b�dzie mia�a kilka poziom�w, r�ni�cych si� poziomem trudno�ci rozgrywki.
*/


#include <SFML/Graphics.hpp>
#include <iostream>
class Player {//klasa dla gracza
private:
	int pancerz;
	int pociski;
	sf::Vector2f pozycja;//wspolrzedne
	float xVel = 10;//predkosc w poziomie
	float yVel = 10;//predkosc w pionie
	sf::CircleShape tank;//czo�g
public:
	void ruch();
};
class Enemy {//klasa dla bot�w -  przeciwnik�w

};
class ObjSrd {//elementy otoczenia

};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "TANK 2021");
	sf::Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int hight = size.y;
	float posPlayerx = 400.f, posPlayery = 500.f;
	std::cout << "szerokosc= " << width << "\n";
	std::cout << "wysokosc= " << hight << "\n";
	sf::CircleShape tankPlayer(40.f, 4);
	tankPlayer.setFillColor(sf::Color::Green);
	tankPlayer.setPosition(posPlayerx, posPlayery);
	tankPlayer.setRotation(45);//ustawienie pocz�tkowe kwadratu
	tankPlayer.setOrigin(40, 40);
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				tankPlayer.move(0, 1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				tankPlayer.move(0, -1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				tankPlayer.rotate(-1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				tankPlayer.rotate(1);
			posPlayerx = tankPlayer.getPosition().x;
			posPlayery = tankPlayer.getPosition().y;
			std::cout << "Pozycja Playera x:" << posPlayerx << "\n" << "Pozycja Playera y:" << posPlayery << "\n";
		}
		window.clear();
		window.draw(tankPlayer);
		window.display();
	}
	return 0;
}