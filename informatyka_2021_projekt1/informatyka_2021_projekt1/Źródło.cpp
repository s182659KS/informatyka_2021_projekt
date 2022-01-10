
/*
Temat projektu: Gra akcji Tank2021 (replika gry Tank1990)
Zakres projektu:Gra jednoosobowa polegaj¹ca na zniszczeniu bazy wroga znajduj¹cej siê po drugiej stronie planszy
równoczeœnie broni¹c swojej przed czo³gami wroga (boty sterowane algorytmem), na planszy znajduj¹ siê ró¿nego rodzaju
przeszkody, z ró¿nych materia³ów. Gracz mo¿e sterowaæ czo³giem za pomocom strza³ek i strzelaæ (klawisz W). Traci punkt pancerza
za ka¿dym trafieniem przez przeciwnika. Punkty zdobywamy poprzez liczbe zniszczonych przeciwników i czas rozrywki.
Gra bêdzie mia³a kilka poziomów, ró¿ni¹cych siê poziomem trudnoœci rozgrywki.
*/


#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <math.h>
#include <vector>
#include "silnik.cpp"
#pragma warning(disable:4996)
	

class Interfejs{
private:
	sf::Font font;
	sf::Text koniecGry;
public:
	Interfejs() {
		//laduj czcionke
		if (!font.loadFromFile("CSStamps.ttf"))
		{
			return;
		}
		koniecGry.setFont(font);
		koniecGry.setString("KONIEC GRY");
		koniecGry.setFillColor(sf::Color::White);
		koniecGry.setPosition(sf::Vector2f(250, 10));
		koniecGry.setCharacterSize(60);


	}
	void draw(sf::RenderWindow& window){
		window.draw(koniecGry);
	}

};
float pi = 3.14159;

//GRACZ
class Player {//klasa dla gracza
private:
	sf::Texture plrtxt;//tekstura dla gracza
	sf::Sprite plrtank;//duszek dla gracza
	sf::Sprite* pocisk;//duszek dla pocisku
	sf::Texture pocisktxt;//tekstura dla pocisku
	sf::Vector2f* kierPoc;
	float pancerz;
	sf::Vector2f pozycja;//wspolrzedne gracza
	float kierunekX = 0;
	float kierunekY = 0;
	float speed;//predkoœæ bota
	//dla pocisków:
	int iloscPociskow;

	int reload;
	bool flagaStrzal;
	int czasPrzel;
	//dla wygranej lub pora¿ki
	bool wygrana;
public:
	Player();
	void draw(sf::RenderWindow& window);
	float ruch(sf::RenderWindow& window, float speedPly);
	sf::Sprite strzal(sf::RenderWindow& window);
	bool przelPoc(int czasPrzel);
	void trafieniePocisk(sf::Sprite ply, sf::Sprite* pociski, sf::Sprite* obiektOto, int SizeTab);
	void zderzenieObj(sf::Sprite* obiektOto, int rozmiarTab);
	float brodzenie(sf::Sprite* Woda, int iloscObj);
	bool Win(sf::Sprite orzel);
	sf::Vector2f zwrocPoz();
	sf::Sprite* zwrocPocisk();
	sf::Sprite* zwrocPPocisk();
	sf::Sprite zwrocSprite();
	sf::Sprite* zwrocPSprite();
	int ruchPoc;
};


	Player::Player() {
		iloscPociskow = 1;
		//speed = 1;
		pozycja.x = 200;
		pozycja.y = 550;
		plrtxt.loadFromFile("teksturaPlayer.png");
		plrtank.setTexture(plrtxt);
		plrtank.setPosition(pozycja);
		plrtank.setOrigin(25, 30);//œrodek sprita
		pocisk = new sf::Sprite[iloscPociskow];
		kierPoc = new sf::Vector2f[iloscPociskow];

	}
	void Player::draw(sf::RenderWindow& window) {
		//window.draw(pocisk);
		window.draw(plrtank);

	}
	float Player::ruch(sf::RenderWindow& window, float speedPly) {//sterowanie pojazdem gracza
		float rotacja;
		float pi = 3.14159;
		rotacja = plrtank.getRotation() - 90;
		//g³owne sterowanie
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			plrtank.move(speedPly * cos(rotacja * pi / 180), speedPly * sin(rotacja * pi / 180));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			plrtank.move(speedPly * -cos(rotacja * pi / 180), speedPly * -sin(rotacja * pi / 180));
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
	sf::Sprite Player::strzal(sf::RenderWindow& window) {//metoda dla pocisku
		flagaStrzal = przelPoc(200);
		pocisktxt.loadFromFile("pocisktxt.png");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)&&flagaStrzal==true) {
			for (int i = 0; i < iloscPociskow; i++) {
				ruchPoc = 1;
				//pocisk[i].setColor(sf::Color::White);
				pocisk[i].setTexture(pocisktxt);
				pocisk[i].setPosition(plrtank.getPosition());
				pocisk[i].setOrigin(2, 2);
				kierPoc[i].x = cos((plrtank.getRotation() - 90) * pi / 180);
				kierPoc[i].y = sin((plrtank.getRotation() - 90) * pi / 180);
				flagaStrzal = false;
				return pocisk[i];
			}
			fflush(stdin);
			
		}
		for (int i = 0; i < iloscPociskow; i++) {
			//std::cout << "drukuj" << kierPoc.x<< std::endl;
			if (ruchPoc == 1) {
				pocisk[i].move(3 * kierPoc[i].x, 3 * kierPoc[i].y);
				window.draw(pocisk[i]);
			}
			
		}
		
	}
	bool Player::przelPoc(int czasPrzel) {//metoda do prze³adowania pocisku
		//czasPrzel = 200;
		if (reload < czasPrzel && flagaStrzal == false) {
			reload++;
			return false;
		}
		else if (reload == czasPrzel)
			reload = 0; 
		return true;
	}

void Player::trafieniePocisk(sf::Sprite ply, sf::Sprite* pociski,sf::Sprite* obiektOto,int SizeTab ) {//PRZEBUDOWA
	for (int i = 0; i < SizeTab; i++) {
		for (int j = 0; j < iloscPociskow; j++) {
			if (abs(pociski[j].getPosition().x - obiektOto[i].getPosition().x) < 18 && abs(pociski[j].getPosition().y - obiektOto[i].getPosition().y) < 18) {
				//pocisk[j].getGlobalBounds().intersects(obiektOto[i].getGlobalBounds()) //pocisk[j].getPosition().x - obiektOto[i].getPosition().x) < 25 && abs(pocisk[j].getPosition().y - obiektOto[i].getPosition().y) < 25
				pociski[j].setPosition(-200,-100);//ply.getPosition()
				std::cout << "trafiono obiekt oto " << i << std::endl;
				ruchPoc = 0;
			}
		}
	}

}

	void Player::zderzenieObj(sf::Sprite* obiektOto, int rozmiarTab) {//W TYPIE OBIEKTU WYBIERAMY CZY OBIEKT JEST ELEMENTEM OTOCZENIA CZY WROGIEM
		for (int i = 0; i < rozmiarTab; i++) {
			if (abs(plrtank.getPosition().x - obiektOto[i].getPosition().x) < 40 && abs(plrtank.getPosition().y - obiektOto[i].getPosition().y) < 40) {
				if (plrtank.getPosition().x < obiektOto[i].getPosition().x)
					plrtank.setPosition(plrtank.getPosition().x - 1, plrtank.getPosition().y);
				if (plrtank.getPosition().x > obiektOto[i].getPosition().x)
					plrtank.setPosition(plrtank.getPosition().x + 1, plrtank.getPosition().y);
				if (plrtank.getPosition().y < obiektOto[i].getPosition().y)
					plrtank.setPosition(plrtank.getPosition().x, plrtank.getPosition().y - 1);
				if (plrtank.getPosition().y > obiektOto[i].getPosition().y)
					plrtank.setPosition(plrtank.getPosition().x, plrtank.getPosition().y + 1);
				if (rozmiarTab == 1)//TYLKO WTEDY MAMY ZDERZENIE Z WROGIEM (CHYBA ¯E ZMIENIMY ILOŒÆ ELEMENTÓW OBIEKTU)
					pancerz = pancerz - 0.5;
				//UTRATA PANCERZA PRZY ZDERZENIU 
			}
		}
	}
	float Player::brodzenie(sf::Sprite* Woda, int iloscObj){//TO NIE CHCE DZIA£AÆ
		for (int o = 0; o < iloscObj; o++) {
			if (plrtank.getGlobalBounds().intersects(Woda[o].getGlobalBounds())) {
				speed = 0.5;
			}
			else {
				speed = 1;
			}
					
		}
		return speed;
	}

	bool Player::Win(sf::Sprite orzel) {
		//METODA DLA WYGRANEJ
		for (int i = 0; i < iloscPociskow; i++)
			if (pocisk[i].getGlobalBounds().intersects(orzel.getGlobalBounds())) {
				wygrana = true;
				return wygrana;
			}
			else
				wygrana = false;
		return wygrana;
	}

	sf::Vector2f Player::zwrocPoz() {

		return plrtank.getPosition();
	}
	sf::Sprite* Player::zwrocPocisk() {
			return pocisk;
		
	}
	sf::Sprite* Player::zwrocPPocisk() {
		return pocisk;
	}
	sf::Sprite Player::zwrocSprite() {
		return plrtank;
	}
	sf::Sprite* Player::zwrocPSprite() {
		return &plrtank;
	}



//PRZECIWNICY dziedzicz¹ niektóre metody po graczu
class Enemy :public Player {//klasa dla botów -  przeciwników
private:
	int idBot;
	sf::Texture enmtxt;//tekstura
	sf::Sprite* enemy;//tablica obiektow
	sf::Vector2f poz;
	int N;//liczba obiektow graf
	std::random_device rd;//randomizacja po³o¿enia 
	int pancerzEnemy;
	bool zestrzelony;
	//OBS£UGA POCISKOW
	sf::Sprite* pocisk;//duszek dla pocisku
	sf::Texture pocisktxt;//tekstura dla pocisku
	sf::Vector2f* kierPoc;
	int iloscPociskow;

	int reload;
	bool flagaStrzal;
	int czasPrzel;
	int rotMem;
	int ruchPoc;
	//zmienne sterowania botów
	int ruchBot, rotBot;//
	int n;
public:
	

	Enemy() {
		N = 1; 
		n = 0;
		ruchBot = 300;
		rotBot = 90;
		pancerzEnemy = 100;
		enemy = new sf::Sprite[N];
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distX(1, 7);
		std::uniform_int_distribution<> distY(1, 2);
		enmtxt.loadFromFile("teksturaPrzeciwnik.png");
		for (int i = 0; i < N; i++) {
			enemy[i].setTexture(enmtxt);
			enemy[i].setPosition(distX(gen)*50-25,distY(gen) * 60 - 30);
			enemy[i].setOrigin(25, 30);//œrodek sprita
		}
		//dla pociskow
		iloscPociskow = 1;
		zestrzelony = false;
		pocisk = new sf::Sprite[iloscPociskow];
		kierPoc = new sf::Vector2f[iloscPociskow];

	}
	~Enemy() {
		delete[] enemy;
	}

	void ruch_bot(sf::RenderWindow& window) {
		float speed = 1;
		float rotacja;
		for (int i = 0; i < N; i++) {
			rotacja = enemy[i].getRotation() - 90;
			n++;//liczba kroków cyklu 
			if (n <= rotBot) {//cykl obrotu
				enemy[i].rotate(rotMem);
			}
			if (rotBot < n < (rotBot + ruchBot)) {//cykl ruchu
				enemy[i].move(speed * cos(rotacja * pi / 180), speed * sin(rotacja * pi / 180));
			}
			if (n > (rotBot + ruchBot)) {//cykl losowania nowej pozycji
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> rotGen(-1, 1);//tu trzenba pokombinowac
				rotMem = rotGen(gen);//losowanie nowego kierunku
				n = 0;
			}
			//ograniczenie do okna
			if (enemy[i].getPosition().x <= 0) {
				enemy[i].move(1, 0);
				enemy[i].rotate(2);
			}
			if (enemy[i].getPosition().x >= window.getSize().x) {
				enemy[i].move(-1, 0);
				enemy[i].rotate(2);
			}
			if (enemy[i].getPosition().y <= 0) {
				enemy[i].move(0, 1);
				enemy[i].rotate(2);
			}
			if (enemy[i].getPosition().y >= window.getSize().y) {
				enemy[i].move(0, -1);
				enemy[i].rotate(2);
			}
		}
	}

	void strzalBot(sf::Sprite ply, sf::RenderWindow& window, sf::Sprite orzel) {
		flagaStrzal = przelPoc(200);//czas w cyklach
		pocisktxt.loadFromFile("pocisktxt.png");
		for (int i = 0; i < N; i++) {
			int wzaPoz = 0;
			int wzaPoz1 = 0;
			int botToOrzel = 0;
			int rotEne = int(enemy[i].getRotation());
			wzaPoz1 = (acos((enemy[i].getPosition().y - ply.getPosition().y) / sqrt(pow(enemy[i].getPosition().x - ply.getPosition().x, 2) + pow(enemy[i].getPosition().y - ply.getPosition().y, 2)))) * 180 / pi;
			botToOrzel = (acos((enemy[i].getPosition().y - orzel.getPosition().y) / sqrt(pow(enemy[i].getPosition().x - orzel.getPosition().x, 2) + pow(enemy[i].getPosition().y - orzel.getPosition().y, 2)))) * 180 / pi;
			if (ply.getPosition().x - enemy[i].getPosition().x < 0)//TAK ABY BY£O ZGODNE Z OBROTEM BOTA
				wzaPoz = 360 - wzaPoz1;
			else
				wzaPoz = wzaPoz1;
			if (orzel.getPosition().x - enemy[i].getPosition().x < 0)
				botToOrzel = 360 - botToOrzel;
			int cel = abs(rotEne - wzaPoz);
			int celNaOrla = abs(rotEne - botToOrzel);
			if ((cel <= 10 ||celNaOrla <=10 ) && flagaStrzal == true && iloscPociskow > 0) {
				for (int j = 0; j < iloscPociskow; j++) {////auto& i:pocisk
					
					pocisk[j].setTexture(pocisktxt);
					pocisk[j].setPosition(enemy[i].getPosition());
					pocisk[j].setOrigin(2, 2);
					kierPoc[j].x = cos((enemy[i].getRotation() - 90) * pi / 180);
					kierPoc[j].y = sin((enemy[i].getRotation() - 90) * pi / 180);
					flagaStrzal = false;
					ruchPoc = 1;
					//return pocisk[i];
				}

			}
			for (int i = 0; i < iloscPociskow; i++) {
				//std::cout << "drukuj" << kierPoc.x<< std::endl;
				if (ruchPoc == 1) {
					pocisk[i].move(4 * kierPoc[i].x, 4 * kierPoc[i].y);
					window.draw(pocisk[i]);
				}

			}

		}
	}
	//obs³uga wystrzelonych przez bota pocisków
	void trafieniePocisk(sf::Sprite ply,char typ, sf::Sprite* pociski, sf::Sprite* obiektOto, int SizeTab) {//PRZEBUDOWA typ - dla okreœlenia typu
		for (int j = 0; j < iloscPociskow; j++) {
			for (int i = 0; i < SizeTab; i++) {
				if (typ == 'W' && abs(pociski[j].getPosition().x - obiektOto[i].getPosition().x) < 18 && abs(pociski[j].getPosition().y - obiektOto[i].getPosition().y) < 18) {
					pociski[j].setPosition(-200, -100);//umieszczenie pocisku poza obszarem planszy
					std::cout << "BOT trafiono obiekt oto " << i << std::endl;
					ruchPoc = 0;
				}
				if (typ == 'G' && abs(pociski[j].getPosition().x - ply.getPosition().x) < 20 && abs(pociski[j].getPosition().y - ply.getPosition().y) < 20) {
					pociski[j].setPosition(-200, -100);
					std::cout << "PLEYER trafiony przez " << j << std::endl;
					ruchPoc = 0;
				}
			}
			

		}

	}
	//trafienie przez pocisk
	bool trafiPoc(sf::Sprite* pocisk,int id) {//traienie przez pocisk
		idBot = id;
		for (int i = 0; i < N; i++) {
			if (pocisk[0].getGlobalBounds().intersects(enemy[i].getGlobalBounds())) {
				std::cout << "Trafiony enemy " << id <<"pancerz"<<pancerzEnemy<< std::endl;
				//TUTAJ PROCEDURA OBS£UGI TRAFIEÑ BOTÓW
				pancerzEnemy = pancerzEnemy - 1;//-5 do pancerza
				if (pancerzEnemy <= 0) {
					std::cout << "Wrog zestrzelony " << id << std::endl;
					enmtxt.loadFromFile("teksturaPrzeciwnikKaput.png");
					enemy[i].setTexture(enmtxt);
					zestrzelony = true;	
				}
			}
		}
		return zestrzelony;
	}
	//POCISKI LEPIEJ ZROBIC NA WEKTORACH/KONTENERACH
	//sf::Sprite strzal(sf::RenderWindow& window) {//metoda dla pocisku
	//	//std::vector<sf::Sprite> pocisk

	void zderzeniaBot() {//zderzenia pomiêdzy botami - ZBENDNE PRZY POJEDYÑCZYCH OBIEKTACH
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (enemy[i].getGlobalBounds().intersects(enemy[j].getGlobalBounds())) {
					if (enemy[i].getPosition().x < enemy[j].getPosition().x) {
						enemy[i].setPosition(enemy[i].getPosition().x - 1, enemy[i].getPosition().y);
						enemy[i].rotate(2);
					}
					if (enemy[i].getPosition().x > enemy[j].getPosition().x ) {
						enemy[i].setPosition(enemy[i].getPosition().x + 1, enemy[i].getPosition().y);
						enemy[i].rotate(-2);
					}
					if (enemy[i].getPosition().y < enemy[j].getPosition().y) {
						enemy[i].setPosition(enemy[i].getPosition().x, enemy[i].getPosition().y - 1);
						enemy[i].rotate(2);
					}
					if (enemy[i].getPosition().y > enemy[j].getPosition().y) {
						enemy[i].setPosition(enemy[i].getPosition().x, enemy[i].getPosition().y + 1);
						enemy[i].rotate(-2);
					}
				}
			}
		}
	}

	
	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < N; i++) {
			window.draw(enemy[i]);
		}
	}
	sf::Sprite* zwroctabSprite() {
			return enemy;
	}
	sf::Sprite zwrocSprite(int id) {
		return enemy[id];
	}
	sf::Sprite* zwrocPoc() {
		return pocisk;
	}
	//ZDERZENIA NA PODSTAWIE ODLEG£OŒCI:
	//abs(enemy[i].getPosition().x - mapaGry[j].getPosition().x) < 40 && abs(enemy[i].getPosition().y - mapaGry[j].getPosition().y) < 40
	//ZDERENIA NA PODSTAWIE NACHODZENIA PIXELI:
	//enemy[i].getGlobalBounds().intersects(mapaGry[j].getGlobalBounds())
	void zderzenieObj(sf::Sprite* mapaGry,int rozmiarTab) {//pobiera kierunek kolizji i steruje spritem
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < rozmiarTab; j++) {
				if (abs(enemy[i].getPosition().x - mapaGry[j].getPosition().x) < 42 && abs(enemy[i].getPosition().y - mapaGry[j].getPosition().y) < 42) {
					if (enemy[i].getPosition().x < mapaGry[j].getPosition().x) {
						enemy[i].setPosition(enemy[i].getPosition().x - 1, enemy[i].getPosition().y);
						enemy[i].rotate(2);
					}
					if (enemy[i].getPosition().x > mapaGry[j].getPosition().x) {
						enemy[i].setPosition(enemy[i].getPosition().x + 1, enemy[i].getPosition().y);
						enemy[i].rotate(-2);
					}
					if (enemy[i].getPosition().y < mapaGry[j].getPosition().y) {
						enemy[i].setPosition(enemy[i].getPosition().x, enemy[i].getPosition().y - 1);
						enemy[i].rotate(2);
					}
					if (enemy[i].getPosition().y > mapaGry[j].getPosition().y) {
						enemy[i].setPosition(enemy[i].getPosition().x, enemy[i].getPosition().y + 1);
						enemy[i].rotate(-2);
					}
				}
			}
		}
	}

};

//OTOCZENIE
class ObjSrd {//elementy otoczenia
	//sf::Sprite* wall;
	//sf::Sprite* rock;
	//sf::Sprite* bush;
	//sf::Sprite* water;
	sf::Sprite orzel[2];
	sf::Sprite ** mapaGry;//dynamiczna dwuwymiarowa
	sf::Texture walltex;
	sf::Texture rocktex;
	sf::Texture bushtex;
	sf::Texture watertex;
	sf::Texture orzeltex;
	FILE* fp;
	sf::Vector2f pozycja;
	std::random_device rd;
	int kierunek;
	int mapa[200][3];//tablica przechowuj¹ca pozycj
	int** mapaDes;
	int material;//rodzaj materia³u
	int n;//przechowuje iloœæ elementów tablicy
	int O=0, P=0, R=0, S=0;//zmienne rozmiarów tablic dynamicznych
public:
	
	ObjSrd(int N) {
		//sprawdzanie iloœci elementów
		n = N;
		orzeltex.loadFromFile("orzel.png");
		orzel[0].setTexture(orzeltex);
		orzel[0].setPosition(405,15);//ustawienie pozycji or³a przeciwnika
		orzel[0].setOrigin(15, 15);
		orzel[1].setTexture(orzeltex);
		orzel[1].setPosition(405, 585);//ustawienie pozycji or³a gracza
		orzel[1].setOrigin(15, 15);
		fp = fopen("mapa1.txt", "rb");
		if (!fopen("mapa1.txt", "rb"))
			std::cout << "nie otwarto pliku\n";
		for (int l= 0; l < N; l++) {
			fread(&mapa[l][0], sizeof(mapa), 1, fp);
			fread(&mapa[l][1], sizeof(mapa), 1, fp);
			fread(&mapa[l][2], sizeof(mapa), 1, fp);
			if (mapa[l][2] == 1)
				O++;
			if (mapa[l][2] == 2)
				P++;
			if (mapa[l][2] == 3)
				R++;
			if (mapa[l][2] == 4)
				S++;
			//if (feof(fp) != 0)//jezeli koniec pliku to break
			//	break;
			
		}
		std::fclose(fp);
		std::cout << O << "," << P << "," << R << "," << S << std::endl;
		walltex.loadFromFile("cegla.png");
		rocktex.loadFromFile("rock.png");
		bushtex.loadFromFile("bush.png");
		watertex.loadFromFile("water.png");
		mapaDes = new int* [2];//tablica dynamiczna dla destrukcji obiektów otoczneia
		mapaDes[0] = new int[O];
		mapaDes[1] = new int[P];
		mapaGry = new sf::Sprite * [4];//tablica dyn. dla gry
		mapaGry[0] = new  sf::Sprite[O];
		mapaGry[1] = new  sf::Sprite[P];
		mapaGry[2] = new  sf::Sprite[R];
		mapaGry[3] = new  sf::Sprite[S];
	//nadawanie otoczeniu wytrzyma³oœci
		for (int i = 0; i < O; i++) {
			mapaDes[0][i] = 3;
		}
		for (int i = 0; i < P; i++) {
			mapaDes[1][i] = 5;
		}

		fp = fopen("mapa1.txt", "rb");
		int o = 0, p = 0, r = 0, s = 0;
		if (!fopen("mapa1.txt", "rb"))
			std::cout << "nie otwarto pliku\n";
		for (int i = 0; i < N; i++) {
			if (mapa[i][2] == 0)
				break;
			fread(&mapa[i][0], sizeof(mapa), 1, fp);
			pozycja.x = mapa[i][0];
			fread(&mapa[i][1], sizeof(mapa), 1, fp);
			pozycja.y = mapa[i][1];
			fread(&mapa[i][2], sizeof(mapa), 1, fp);
			material = mapa[i][2];
			//std::cout << mapa[i][0] << " " << mapa[i][1] << " " << mapa[i][2] << std::endl;

			if (mapa[i][2] == 1)
			{
				//std::cout << "cegla" << std::endl;
				mapaGry[0][o].setTexture(walltex);
				mapaGry[0][o].setPosition(sf::Vector2f(pozycja.x, pozycja.y));//ustawienie pozycji poczatkowej
				mapaGry[0][o].setOrigin(15, 15);
				o++;
			}
			if (mapa[i][2] == 2)
			{
				//std::cout << "kamien" << std::endl;
				mapaGry[1][p].setTexture(rocktex);//nalozenie tekstury
				mapaGry[1][p].setPosition(sf::Vector2f(pozycja.x, pozycja.y));//ustawienie pozycji poczatkowej
				mapaGry[1][p].setOrigin(15, 15);
				p++;
			}
			if (mapa[i][2] == 3)
			{
				//std::cout << "woda" << std::endl;
				mapaGry[2][r].setTexture(watertex);//nalozenie tekstury
				mapaGry[2][r].setPosition(sf::Vector2f(pozycja.x, pozycja.y));//ustawienie pozycji poczatkowej
				mapaGry[2][r].setOrigin(15, 15);
				r++;
			}
			if (mapa[i][2] == 4)
			{
				//std::cout << "kszok" << s << std::endl;
				mapaGry[3][s].setTexture(bushtex);//nalozenie tekstury
				mapaGry[3][s].setPosition(sf::Vector2f(pozycja.x, pozycja.y));//ustawienie pozycji poczatkowej
				mapaGry[3][s].setOrigin(15, 15);
				s++;
			}

		}
		std::fclose(fp);
		std::cout << o << "," << p << "," << r << "," << s << std::endl;

	}

	 sf::Vector2f kierKol(sf::Sprite plr_poz) {//iteracja po wszystkich utworzonych obiektach ototczenia , w poszukwaniu kolizji
		 sf::Vector2f kierunek;
		for (int i = 0; i < n; i++) {
			if ((abs(mapa[i][0] - plr_poz.getPosition().x) < 40 && abs(mapa[i][1] - plr_poz.getPosition().y) < 40) && (mapa[i][2] == 1 || mapa[i][2] == 2))
			{
				kierunek = { 0,0 };
				if (plr_poz.getPosition().x < mapa[i][0])//dla podjazdu pleyera z lewej
				{
					 kierunek.x = -1;
				}
				else if (plr_poz.getPosition().x > mapa[i][0])//dla podjazdu pleyera z prawje
				{
					 kierunek.x = 1;
				}
				if (plr_poz.getPosition().y < mapa[i][1])//dla podjazdu pleyera od gory
				{
					 kierunek.y = -1;
				}
				else if (plr_poz.getPosition().y > mapa[i][1])//dla podjazdu pleyera od dolu
				{
					 kierunek.y = 1;
				}
			return kierunek;	
			}
			
		}
	}
	 sf::Sprite zwrocOrla(int id) {//ZWRACA SPRITE OR£A ABY SPRAWDZIÆ WYGRAN¥
		 return orzel[id];
	 }

	 sf::Sprite* ZwrocMapeGry(int mat) {
		 return &mapaGry[mat][0];
	 }
	 int zwrocRozTab(int mat) {
		 if (mat == 0) {
			 return O;
		 }
		 if (mat == 1) {
			 return P;
		 }
		 if (mat == 2) {
			 return R;
		 }
		 if (mat == 3) {
			 return S;
		 }
	 }
	 void trafiPoc(sf::Sprite* pocisk) {//PRZYDA£A BY SIE FUNKCJA ZWRACANIA ILOSCI POCISKÓW
		 for (int i = 0; i < O; i++) {
			 if (pocisk[0].getGlobalBounds().intersects(mapaGry[0][i].getGlobalBounds())) {
				 std::cout << "Trafiony otoczenie typu cegla " << i << " ma jeszcze " << mapaDes[0][i]<< " wytrzymalosci" << std::endl;
				 --mapaDes[0][i];
				 if (mapaDes[0][i] == 0)
					 mapaGry[0][i].setPosition(-100, -100);//tymczasowe przeniesienie poza plansze
				 //AKCJA DLA ZDERZENIA POCISKU Z CEG£¥
			 }
		 }
		 for (int i = 0; i < P; i++) {
			 if (pocisk[0].getGlobalBounds().intersects(mapaGry[1][i].getGlobalBounds())) {
				 std::cout << "Trafiony otoczenie typu skala " << i << " ma jeszcze " << mapaDes[1][i] << " wytrzymalosci" << std::endl;
				 --mapaDes[1][i];
				 if (mapaDes[1][i] == 0)
					 mapaGry[1][i].setPosition(-100, -100);//tymczasowe przeniesienie poza plansze
				 //AKCJA DLA ZDERZENIA POCISKU ZE SKA£¥
			 }
		 }
	 }
	void generacja(int poziom) {//generatior rozmieszczenia elementów
		int const N = 50;//tymczasowo, domyœlnie dynamiczna alokacja pam.
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
	void draw(sf::RenderWindow& window, int matOto) {
		window.draw(orzel[0]);
		window.draw(orzel[1]);
		int LiczbaEle;
		if (matOto == 0)
			LiczbaEle = O;
		if (matOto == 1)
			LiczbaEle = P;
		if (matOto == 2)
			LiczbaEle = R;
		if (matOto == 3)
			LiczbaEle = S;
		//int o = 0, p = 0, r = 0, s = 0;//zmienne pomocnicze
		for (int i = 0; i < LiczbaEle; i++)
		{
			if (LiczbaEle == O){
				window.draw(mapaGry[0][i]);
			}
			if (LiczbaEle == P){
				window.draw(mapaGry[1][i]);
			}
			if (LiczbaEle == R){
				window.draw(mapaGry[2][i]);
			}
			if (LiczbaEle == S){
				window.draw(mapaGry[3][i]);
			}
		}
	}
};
void Opoznienie(int opoznienie)
{
	sf::Clock zegar;
	sf::Time czas;
	while (1)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie)
		{
			zegar.restart();
			break;
		}

	}
}
int main()
{
	int E = 3;//LICZBA WROGOW
	bool wygrana;
	bool przegrana;
	sf::RenderWindow window(sf::VideoMode(800, 600), "TANK 2021");
	sf::Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int hight = size.y;
	Interfejs if1;
	Player p1;
	Enemy* e1;
	ObjSrd s1(200);
	e1 = new Enemy[E];
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}
		window.clear();
		p1.ruch(window, p1.brodzenie(s1.ZwrocMapeGry(2), s1.zwrocRozTab(2)));
		s1.draw(window, 2);//WODA
		p1.zderzenieObj(s1.ZwrocMapeGry(0), s1.zwrocRozTab(0));
		p1.zderzenieObj(s1.ZwrocMapeGry(1), s1.zwrocRozTab(1));

		for (int k = 0; k < E; k++) {//PÊTLA OBS£UGUJ¥CA PRZECIWNIKÓW
			if (e1[k].trafiPoc(p1.zwrocPocisk(), k) == false) {//test dla nieruchomego zestrzelonego bota
				e1[k].ruch_bot(window);
				e1[k].strzalBot(p1.zwrocSprite(), window, s1.zwrocOrla(1));
			}
			e1[k].zderzenieObj(s1.ZwrocMapeGry(0), s1.zwrocRozTab(0));//stabilne dla cegiel
			e1[k].zderzenieObj(s1.ZwrocMapeGry(1), s1.zwrocRozTab(1));//stabilne dla kamieni
			e1[k].zderzenieObj(p1.zwrocPSprite(), 1);
			//PENTLA DLA ZDEREÑ POMIÊDZY BOTAMI
			for (int l = 0; l < E; l++) {
				e1[k].zderzenieObj(e1[l].zwroctabSprite(), 1);
			}
			s1.trafiPoc(e1[k].zwrocPoc());
			p1.zderzenieObj(e1[k].zwroctabSprite(), 1);
			e1[k].trafieniePocisk(e1[k].zwrocSprite(k),'W', e1[k].zwrocPoc(), s1.ZwrocMapeGry(0), s1.zwrocRozTab(0));
			e1[k].trafieniePocisk(e1[k].zwrocSprite(k),'W', e1[k].zwrocPoc(), s1.ZwrocMapeGry(1), s1.zwrocRozTab(1));
			e1[k].trafieniePocisk(p1.zwrocSprite(),'G', e1[k].zwrocPoc(), s1.ZwrocMapeGry(1), s1.zwrocRozTab(1));//COŒ TU NIE GRA ALE DZiA£A - MA OBS£UGIWAC ZDERZENIE POCISKU Z PLAYEREM
			p1.trafieniePocisk(p1.zwrocSprite(), p1.zwrocPPocisk(), e1[k].zwroctabSprite(), 1);
			przegrana = e1[k].Win(s1.zwrocOrla(1));
			e1[k].draw(window);
		}

		p1.trafieniePocisk(p1.zwrocSprite(), p1.zwrocPPocisk(), s1.ZwrocMapeGry(0), s1.zwrocRozTab(0));
		p1.trafieniePocisk(p1.zwrocSprite(), p1.zwrocPPocisk(), s1.ZwrocMapeGry(1), s1.zwrocRozTab(1));
		p1.strzal(window);
		s1.draw(window, 0);//rysowanie cegiel
		s1.draw(window, 1);//rysowanie kamienia
		s1.trafiPoc(p1.zwrocPocisk());//obs³uga trafienia obiektów otoczenia
		p1.draw(window);
		s1.draw(window, 3);//rysowanie zaroœli
		wygrana = p1.Win(s1.zwrocOrla(0));
		Opoznienie(1);
		if (wygrana == true) {
			std::cout << "WYGRALES GRE\n";
			//while(1)
			do
			if1.draw(window);
			while (event.key.code == sf::Keyboard::Enter);
		}
		else if (przegrana == true)
			std::cout << "PRZEGRALES GRE\n";
		window.display();
	}

	return 0;
}
