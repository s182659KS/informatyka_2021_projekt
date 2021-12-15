
/*
Temat projektu: Gra akcji Tank2021 (replika gry Tank1990)
Zakres projektu:Gra jednoosobowa polegaj¹ca na zniszczeniu bazy wroga znajduj¹cej siê po drugiej stronie planszy
równoczeœnie broni¹c swojej przed czo³gami wroga (boty sterowane algorytmem), na planszy znajduj¹ siê ró¿nego rodzaju
przeszkody, z ró¿nych materia³ów. Gracz mo¿e sterowaæ czo³giem za pomocom strza³ek i strzelaæ. Traci punkt pancerza
za ka¿dym trafieniem. Punkty zdobywamy poprzez liczbe zniszczonych przeciwników i czas rozrywki. Gra bêdzie mia³a kilka poziomów, ró¿ni¹cych siê poziomem trudnoœci rozgrywki.
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
	sf::Sprite pocisk;//duszek dla pocisku
	sf::Texture pocisktxt;//tekstura dla pocisku
	int pociski;
	float pancerz;
	sf::Vector2f pozycja;//wspolrzedne gracza
	float xVel = 10;//predkosc w poziomie
	float yVel = 10;//predkosc w pionie
	//sf::CircleShape tank;//czo³g
public:
	float pi = 3.14159;
	Player() {
		pozycja.x = 400;
		pozycja.y = 550;
		sf::IntRect ksztalt (200, 0, 50, 50);//niedzia³a tak
		plrtxt.loadFromFile("teksturaPlayer.png");
		plrtank.setTexture(plrtxt);
		plrtank.setPosition(pozycja);
		plrtank.setOrigin(25, 30);//œrodek sprita

		
	}
	void draw(sf::RenderWindow& window) {
		window.draw(pocisk);
		window.draw(plrtank);
			
	}
	float ruch(sf::RenderWindow& window, sf::Sprite obiektOto) {//sterowanie pojazdem gracza
		float rotacja;
		float pi = 3.14159;
		rotacja = plrtank.getRotation() - 90;
		float speed = 0.4;
		//kolizja z obiektem ->dzia³a
		if (plrtank.getGlobalBounds().intersects(obiektOto.getGlobalBounds())) {
			//std::cout << "myd³o\n";
			if(plrtank.getPosition().x<obiektOto.getPosition().x)
				plrtank.setPosition(plrtank.getPosition().x - 1, plrtank.getPosition().y);
			if(plrtank.getPosition().x > obiektOto.getPosition().x)
				plrtank.setPosition(plrtank.getPosition().x + 1, plrtank.getPosition().y);
			if (plrtank.getPosition().y < obiektOto.getPosition().y)
				plrtank.setPosition(plrtank.getPosition().x, plrtank.getPosition().y - 1);
			if (plrtank.getPosition().y > obiektOto.getPosition().y)
				plrtank.setPosition(plrtank.getPosition().x, plrtank.getPosition().y + 1);
		}
		//g³owne sterowanie
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			plrtank.move(speed* cos(rotacja * pi / 180), speed * sin(rotacja * pi / 180));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			plrtank.move(speed * -cos(rotacja * pi / 180), speed * -sin(rotacja * pi / 180));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			plrtank.rotate(-1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			plrtank.rotate(1);
		//ograniczenie do okna
		if (plrtank.getPosition().x <= 0)
			plrtank.move(1, 0);
		if (plrtank.getPosition().x >= window.getSize().x)
			plrtank.move(-1, 0);
		if (plrtank.getPosition().y <= 0)
			plrtank.move(0, 1);
		if (plrtank.getPosition().y >= window.getSize().y)
			plrtank.move(0, -1);
		return rotacja;
	}
	void strzal() {//metoda dla pocisku
		float kierunekx;
		float kieruneky;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			pocisktxt.loadFromFile("pocisktxt.png");
			pocisk.setTexture(pocisktxt);
			pocisk.setPosition(plrtank.getPosition());
			pocisk.setOrigin(2, 2);
			kierunekx = cos((plrtank.getRotation() - 90) * pi / 180);
			kieruneky = sin((plrtank.getRotation() - 90) * pi / 180);
			
		}
		pocisk.move(2 * kierunekx, 2 * kieruneky);
	}



	void zderzenieWall(sf::Sprite obiektOto) {
	
	}

	sf::Vector2f zwrocPoz() {
		return plrtank.getPosition();
	}

	void zderzenieWall(sf::Vector2f objCol) {
	
	}

};
//PRZECIWNICY dziedzicz¹ niektóre metody po graczu
class Enemy:public Player {//klasa dla botów -  przeciwników
private:
	sf::Texture enmtxt;//tekstura
	sf::Sprite* enemy;//tablica obiektow
	int N;//liczba obiektow graf
	std::random_device rd;//randomizacja po³o¿enia 
};

//OTOCZENIE
class ObjSrd {//elementy otoczenia
	sf::Sprite* wall;
	sf::Texture walltex;
	FILE* fp;
	int mapa[50][2];//tablica przechowuj¹ca pozycje
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
			wall[i].setOrigin(15, 15);
		}
		std::fclose(fp);
	}

	sf::Sprite sprawdzKol(sf::Vector2f plr_poz, int N) {//iteracja po wszystkich utworzonych obiektach ototczenia , w poszukwaniu kolizji
		int i = 0;
		for (i = 0; i < N; i++) {
			if (abs(wall[i].getPosition().x - plr_poz.x)<40 && abs(wall[i].getPosition().y - plr_poz.y)<40) {
				std::cout << "kolizja z " << i << std::endl;//kolizja z obiektem 
				return wall[i];// zwaracanie pozycjê 
				//return i;
			}

		}
		//return i;

	}
		

	void generacja(int poziom) {//generatior rozmieszczenia elementów
		int const N = 50;//tymczasowo, domyœlnie dynamiczna alokacja pam.
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
			tabB[k][1] = (j * 30);
			tabB[k][2] = (i * 30);
			std::cout << tabB[k][1] << "," << tabB[k][2] << std::endl;
			fwrite(&tabB[k][1], sizeof(tabB[0][0]), 1, fp);
			fwrite(&tabB[k][2], sizeof(tabB[0][0]), 1, fp);
		}
	}
	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < n; i++)
		{
			//std::cout << "dzia³a";
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
		p1.ruch(window, s1.sprawdzKol(p1.zwrocPoz(), 50));
		p1.strzal();
		p1.zderzenieWall(s1.sprawdzKol(p1.zwrocPoz(), 50));
		s1.draw(window);
		p1.draw(window);
		
		window.display();
	}
	return 0;
}
