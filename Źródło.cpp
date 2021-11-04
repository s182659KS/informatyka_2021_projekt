/*
Temat projektu: Gra akcji Tank2021 (replika gry Tank1990)
Zakres projektu:Gra jednoosobowa polegaj¹ca na zniszczeniu bazy wroga znajduj¹cej siê po drugiej stronie planszy
równoczeœnie broni¹c swojej przed czo³gami wroga (boty sterowane algorytmem), na planszy znajduj¹ siê ró¿nego rodzaju
przeszkody, z ró¿nych materia³ów. Gracz mo¿e sterowaæ czo³giem za pomocom strza³ek i strzelaæ. Traci punkt pancerza
za ka¿dym trafieniem. Punkty zdobywamy poprzez liczbe zniszczonych przeciwników i czas rozrywki. Gra bêdzie mia³a kilka poziomów, ró¿ni¹cych siê poziomem trudnoœci rozgrywki.
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
	sf::CircleShape tank;//czo³g
public:
	void ruch();
};
class Enemy {//klasa dla botów -  przeciwników

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
	tankPlayer.setRotation(45);//ustawienie pocz¹tkowe kwadratu
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