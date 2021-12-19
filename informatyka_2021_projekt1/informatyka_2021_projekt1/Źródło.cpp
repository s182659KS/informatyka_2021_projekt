
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
	sf::Sprite pocisk;//duszek dla pocisku
	sf::Texture pocisktxt;//tekstura dla pocisku
	int pociski;
	float pancerz;
	sf::Vector2f pozycja;//wspolrzedne gracza
	float xVel = 10;//predkosc w poziomie
	float yVel = 10;//predkosc w pionie
	//sf::CircleShape tank;//czo�g
public:
	float pi = 3.14159;
	Player() {
		pozycja.x = 400;
		pozycja.y = 550;
		sf::IntRect ksztalt(200, 0, 50, 50);//niedzia�a tak
		plrtxt.loadFromFile("teksturaPlayer.png");
		plrtank.setTexture(plrtxt);
		plrtank.setPosition(pozycja);
		plrtank.setOrigin(25, 30);//�rodek sprita


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
		//kolizja z obiektem ->dzia�a
		//if (plrtank.getGlobalBounds().intersects(obiektOto.getGlobalBounds())) {
		//	//std::cout << "myd�o\n";
		//	if (plrtank.getPosition().x < obiektOto.getPosition().x)
		//		plrtank.setPosition(plrtank.getPosition().x - 1, plrtank.getPosition().y);
		//	if (plrtank.getPosition().x > obiektOto.getPosition().x)
		//		plrtank.setPosition(plrtank.getPosition().x + 1, plrtank.getPosition().y);
		//	if (plrtank.getPosition().y < obiektOto.getPosition().y)
		//		plrtank.setPosition(plrtank.getPosition().x, plrtank.getPosition().y - 1);
		//	if (plrtank.getPosition().y > obiektOto.getPosition().y)
		//		plrtank.setPosition(plrtank.getPosition().x, plrtank.getPosition().y + 1);
		//}
		//g�owne sterowanie
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			plrtank.move(speed * cos(rotacja * pi / 180), speed * sin(rotacja * pi / 180));
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			pocisktxt.loadFromFile("pocisktxt.png");
			pocisk.setTexture(pocisktxt);
			pocisk.setPosition(plrtank.getPosition());
			pocisk.setOrigin(2, 2);
			kierunekx = cos((plrtank.getRotation() - 90) * pi / 180);
			kieruneky = sin((plrtank.getRotation() - 90) * pi / 180);

		}
		pocisk.move(2 * kierunekx, 2 * kieruneky);
	}



	void zderzenieObj(sf::Sprite obiektOto) {
		if (plrtank.getGlobalBounds().intersects(obiektOto.getGlobalBounds())) {
			//std::cout << "myd�o\n";
			if (plrtank.getPosition().x < obiektOto.getPosition().x)
				plrtank.setPosition(plrtank.getPosition().x - 1, plrtank.getPosition().y);
			if (plrtank.getPosition().x > obiektOto.getPosition().x)
				plrtank.setPosition(plrtank.getPosition().x + 1, plrtank.getPosition().y);
			if (plrtank.getPosition().y < obiektOto.getPosition().y)
				plrtank.setPosition(plrtank.getPosition().x, plrtank.getPosition().y - 1);
			if (plrtank.getPosition().y > obiektOto.getPosition().y)
				plrtank.setPosition(plrtank.getPosition().x, plrtank.getPosition().y + 1);
		}
	}

	sf::Vector2f zwrocPoz() {
		return plrtank.getPosition();
	}

	sf::Sprite zwrocSprite() {
		return plrtank;
	}

};
//PRZECIWNICY dziedzicz� niekt�re metody po graczu
class Enemy :public Player {//klasa dla bot�w -  przeciwnik�w
private:
	sf::Texture enmtxt;//tekstura
	sf::Sprite enemy;//tablica obiektow
	sf::Vector2f poz;
	int N;//liczba obiektow graf
	std::random_device rd;//randomizacja po�o�enia 

public:
	int n = 0;
	int rotMem = 0;
	//zmienne sterowania bot�w
	int ruchBot=300 , katBot=90;
	Enemy() {
		poz.x = 400;
		poz.y = 50;
		enmtxt.loadFromFile("teksturaPrzeciwnik.png");
		enemy.setTexture(enmtxt);
		enemy.setPosition(poz);
		enemy.setOrigin(25, 30);//�rodek sprita


	}

	void ruch_bot(sf::RenderWindow& window) {
		float speed = 0.4;
		float pi = 3.14159;
		float rotacja;
		rotacja = enemy.getRotation() - 90;
		std::mt19937 gen(rd());
		n++;
		if(n <= katBot) {
			enemy.rotate(rotMem);
		}
		if(katBot<n<(katBot+ruchBot)) {
		enemy.move(speed * cos(rotacja * pi / 180), speed * sin(rotacja * pi / 180));
		}
		if(n>(katBot + ruchBot)) {
			std::uniform_int_distribution<> rotGen(-1, 1);//tu trzenba pokombinowac
			rotMem = rotGen(gen);
			n = 0;
		}
		//std::cout << n<<"  " << (n * rotMem) * pi / 180 << std::endl;
		//ograniczenie do okna
		if (enemy.getPosition().x <= 0){
			enemy.move(1, 0);
			enemy.rotate(1);
		}
		if (enemy.getPosition().x >= window.getSize().x){
			enemy.move(-1, 0);
			enemy.rotate(1);
		}
		if (enemy.getPosition().y <= 0){
			enemy.move(0, 1);
			enemy.rotate(1);
		}
		if (enemy.getPosition().y >= window.getSize().y){
			enemy.move(0, -1);
			enemy.rotate(1);
		}
	}
	void draw(sf::RenderWindow& window) {
		window.draw(enemy);

	}
	sf::Vector2f zwrocPoz() {
		return enemy.getPosition();
	}

	void zderzenieObj(sf::Sprite obiektOto) {
		if (enemy.getGlobalBounds().intersects(obiektOto.getGlobalBounds())) {
			//std::cout << "myd�o\n";
			if (enemy.getPosition().x < obiektOto.getPosition().x) {
					enemy.setPosition(enemy.getPosition().x - 1, enemy.getPosition().y);
					enemy.rotate(1);
				}
			if (enemy.getPosition().x > obiektOto.getPosition().x){
				enemy.setPosition(enemy.getPosition().x + 1, enemy.getPosition().y);
				enemy.rotate(-1);
			}
			if (enemy.getPosition().y < obiektOto.getPosition().y){
				enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y - 1);
				enemy.rotate(1);
			}
			if (enemy.getPosition().y > obiektOto.getPosition().y){
				enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y + 1);
				enemy.rotate(-1);
			}
		}
	}

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
			wall[i].setOrigin(15, 15);
		}
		std::fclose(fp);
	}

	sf::Sprite sprawdzKol(sf::Vector2f plr_poz, int N) {//iteracja po wszystkich utworzonych obiektach ototczenia , w poszukwaniu kolizji
		int i = 0;
		for (i = 0; i < N; i++) {
			if (abs(wall[i].getPosition().x - plr_poz.x) < 40 && abs(wall[i].getPosition().y - plr_poz.y) < 40) {
				std::cout << "kolizja z " << i << std::endl;//kolizja z obiektem 
				return wall[i];// zwaracanie pozycj� 
				//return i;
			}

		}
		//return i;

	}


	void generacja(int poziom) {//generatior rozmieszczenia element�w
		int const N = 50;//tymczasowo, domy�lnie dynamiczna alokacja pam.
		if (poziom == 1)
			int const N = 50;
		else if (poziom == 2)
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
	Enemy e1;
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
		e1.ruch_bot(window);
		e1.zderzenieObj(s1.sprawdzKol(e1.zwrocPoz(), 50));
		e1.draw(window);
		p1.zderzenieObj(s1.sprawdzKol(p1.zwrocPoz(), 50));
		s1.draw(window);
		p1.draw(window);

		window.display();
	}
	return 0;
}
