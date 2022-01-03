
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
#include <vector>
#pragma warning(disable:4996)
//GRACZ
class Player {//klasa dla gracza
private:
	sf::Texture plrtxt;//tekstura dla gracza
	sf::Sprite plrtank;//duszek dla gracza
	sf::Sprite* pocisk;//duszek dla pocisku
	sf::Texture pocisktxt;//tekstura dla pocisku
	sf::Vector2f *kierPoc;
	float pancerz;
	sf::Vector2f pozycja;//wspolrzedne gracza
	float kierunekX = 0;
	float kierunekY = 0;
	//dla pocisków:
	int iloscPociskow;
	int ruchPoc;
	int reload;
	bool flagaStrzal;
	int czasPrzel;
public:
	float pi = 3.14159;
	int M = 1;
	Player() {
		iloscPociskow = 3;
		pozycja.x = 200;
		pozycja.y = 550;
		plrtxt.loadFromFile("teksturaPlayer.png");
		plrtank.setTexture(plrtxt);
		plrtank.setPosition(pozycja);
		plrtank.setOrigin(25, 30);//œrodek sprita
		pocisk = new sf::Sprite[iloscPociskow];
		kierPoc = new sf::Vector2f[iloscPociskow];

	}
	void draw(sf::RenderWindow& window) {
		//window.draw(pocisk);
		window.draw(plrtank);

	}
	float ruch(sf::RenderWindow& window) {//sterowanie pojazdem gracza
		float rotacja;
		float pi = 3.14159;
		rotacja = plrtank.getRotation() - 90;
		float speed = 0.4;
		//g³owne sterowanie
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
	sf::Sprite strzal(sf::RenderWindow& window) {//metoda dla pocisku
		flagaStrzal = przelPoc();
		pocisktxt.loadFromFile("pocisktxt.png");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)&&flagaStrzal==true) {
			for (int i = 0; i < iloscPociskow; i++) {
				ruchPoc = 1;
				pocisk[i].setColor(sf::Color::White);
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
				pocisk[i].move(4 * kierPoc[i].x, 4 * kierPoc[i].y);
				window.draw(pocisk[i]);
			}
			
		}
		
	}
	bool przelPoc() {//metoda do prze³adowania pocisku
		czasPrzel = 200;
		if (reload < czasPrzel && flagaStrzal == false) {
			reload++;
			return false;
		}
		else if (reload == czasPrzel)
			reload = 0; 
		return true;
	}

void trafieniePocisk(sf::Sprite* obiektOto,int SizeTab ) {
	for (int i = 0; i < SizeTab; i++) {
		for (int j = 0; j < iloscPociskow; j++) {
			if (abs(pocisk[j].getPosition().x - obiektOto[i].getPosition().x) < 18 && abs(pocisk[j].getPosition().y - obiektOto[i].getPosition().y) < 18) {
				//pocisk[j].getGlobalBounds().intersects(obiektOto[i].getGlobalBounds())
				pocisk[j].setPosition(plrtank.getPosition());
				ruchPoc = 0;
			}
		}
	}

}

	void detZderzenie(sf::Vector2f kierunek) {
			plrtank.move(kierunek);
	}
	void zderzenieObj(sf::Sprite* obiektOto, int rozmarTab) {
		for (int i = 0; i < rozmarTab; i++) {
			if (abs(plrtank.getPosition().x - obiektOto[i].getPosition().x) < 42 && abs(plrtank.getPosition().y - obiektOto[i].getPosition().y) < 42) {
				if (plrtank.getPosition().x < obiektOto[i].getPosition().x)
					plrtank.setPosition(plrtank.getPosition().x - 1, plrtank.getPosition().y);
				if (plrtank.getPosition().x > obiektOto[i].getPosition().x)
					plrtank.setPosition(plrtank.getPosition().x + 1, plrtank.getPosition().y);
				if (plrtank.getPosition().y < obiektOto[i].getPosition().y)
					plrtank.setPosition(plrtank.getPosition().x, plrtank.getPosition().y - 1);
				if (plrtank.getPosition().y > obiektOto[i].getPosition().y)
					plrtank.setPosition(plrtank.getPosition().x, plrtank.getPosition().y + 1);
			}
		}
		/*if (plrtank.getGlobalBounds().intersects(obiektOto.getGlobalBounds())&&(mat==1||mat==2)) {
			if (plrtank.getPosition().x < obiektOto.getPosition().x)
				plrtank.setPosition(plrtank.getPosition().x - 1, plrtank.getPosition().y);
			if (plrtank.getPosition().x > obiektOto.getPosition().x)
				plrtank.setPosition(plrtank.getPosition().x + 1, plrtank.getPosition().y);
			if (plrtank.getPosition().y < obiektOto.getPosition().y)
				plrtank.setPosition(plrtank.getPosition().x, plrtank.getPosition().y - 1);
			if (plrtank.getPosition().y > obiektOto.getPosition().y)
				plrtank.setPosition(plrtank.getPosition().x, plrtank.getPosition().y + 1);
		}*/
	}

	sf::Vector2f zwrocPoz() {

		return plrtank.getPosition();
	}
	sf::Sprite zwrocPocisk() {
		for (int i = 0; i < iloscPociskow; i++) {
			return pocisk[i];
		}
	}
	sf::Sprite zwrocSprite() {
		return plrtank;
	}
	sf::Sprite* zwrocPSprite() {
		return &plrtank;
	}

};

class pociski {
	sf::Sprite pocisk;//duszek dla pocisku
	sf::Texture pocisktxt;//tekstura dla pocisku
	int IloscPocisk;
	float pi = 3.14159;
	float kierunekx;
	float kieruneky;
public:
	pociski() {
		pocisktxt.loadFromFile("pocisktxt.png");
		pocisk.setTexture(pocisktxt);
		pocisk.setOrigin(2, 2);
	}
	~pociski() {
		std::cout << "dekonstruktor\n";
		delete this;
	}
	void strzal(sf::Sprite Ply, sf::RenderWindow& window) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			pocisk.setPosition(Ply.getPosition());
			kierunekx = cos((Ply.getRotation() - 90) * pi / 180);
			kieruneky = sin((Ply.getRotation() - 90) * pi / 180);
			//std::cout << "jestem\n";
		}
		pocisk.move(2 * kierunekx, 2 * kieruneky);
		window.draw(pocisk);

	}
	bool trafienie(sf::Sprite trafionyObj) {
		if (pocisk.getGlobalBounds().intersects(trafionyObj.getGlobalBounds())) {
			std::cout << "trafiono\n";
			return true;
		}
		else {
			return false;
		}
	}
	sf::Vector2f zwrocPoz() {
		return pocisk.getPosition();
	}
	sf::Sprite zwrocSprite() {
		return pocisk;
	}
};

//PRZECIWNICY dziedzicz¹ niektóre metody po graczu
class Enemy :public Player {//klasa dla botów -  przeciwników
private:
	sf::Texture enmtxt;//tekstura
	sf::Sprite* enemy;//tablica obiektow
	sf::Vector2f poz;
	int N;//liczba obiektow graf
	std::random_device rd;//randomizacja po³o¿enia 

public:
	int n = 0;
	int rotMem = 0;
	//zmienne sterowania botów
	int ruchBot = 300, katBot = 90;
	Enemy(int N1) {
		N = N1;
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
	}

	void ruch_bot(sf::RenderWindow& window) {
		float speed = 0.4;
		float pi = 3.14159;
		float rotacja;
		for (int i = 0; i < N; i++) {
			rotacja = enemy[i].getRotation() - 90;
			n++;
			if (n <= katBot) {
				enemy[i].rotate(rotMem);
			}
			if (katBot < n < (katBot + ruchBot)) {
				enemy[i].move(speed * cos(rotacja * pi / 180), speed * sin(rotacja * pi / 180));
			}
			if (n > (katBot + ruchBot)) {
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> rotGen(-1, 1);//tu trzenba pokombinowac
				rotMem = rotGen(gen);
				n = 0;
			}
			//ograniczenie do okna
			if (enemy[i].getPosition().x <= 0) {
				enemy[i].move(1, 0);
				//enemy[i].rotate(2);
			}
			if (enemy[i].getPosition().x >= window.getSize().x) {
				enemy[i].move(-1, 0);
				//enemy[i].rotate(2);
			}
			if (enemy[i].getPosition().y <= 0) {
				enemy[i].move(0, 1);
				//enemy[i].rotate(2);
			}
			if (enemy[i].getPosition().y >= window.getSize().y) {
				enemy[i].move(0, -1);
				//enemy[i].rotate(2);
			}
		}
	}

	void strzalBot(sf::Sprite ply) {
		for (int i = 0; i < N; i++) {
			int celNaPly; //= (atan((enemy[i].getPosition().x - ply.getPosition().x) / (enemy[i].getPosition().y - ply.getPosition().y)))*180/pi;
			celNaPly=(asin((enemy[i].getPosition().x-ply.getPosition().x)/sqrt(pow(enemy[i].getPosition().x - ply.getPosition().x,2)+pow(enemy[i].getPosition().y - ply.getPosition().y,2)))) * 180 / pi;
			int rotEne = (int(enemy[i].getRotation())%180)+90;///180) * pi;
			int cel = rotEne - celNaPly;
			//std::cout << "wzaje pol: " << celNaPly << std::endl;
			//std::cout << "enemy rot: " << rotEne << std::endl;
			//std::system("cls");
			//std::cout << "suma: " << cel << std::endl;//dzia³a
			if(cel==90)
				std::cout << "strzalll" << std::endl;




		}

	}
	void zderzeniaBot(sf::Sprite sriteGracz) {
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
	void trafiPoc(sf::Sprite pocisk) {
		for (int i = 0; i < N; i++) {
			if (pocisk.getGlobalBounds().intersects(enemy[i].getGlobalBounds())) {
				std::cout << "Trafiony enemy " << i << std::endl;
				//TUTAJ PROCEDURA OBS£UGI TRAFIEÑ BOTÓW






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
	sf::Sprite* wall;
	sf::Sprite* rock;
	sf::Sprite* bush;
	sf::Sprite* water;
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
		orzel[0].setPosition(405,15);//ustawienie pozycji poczatkowej
		orzel[0].setOrigin(15, 15);
		orzel[1].setTexture(orzeltex);
		orzel[1].setPosition(405, 585);//ustawienie pozycji poczatkowej
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
		wall = new sf::Sprite[N];
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
	void niszczOto() {


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

	 sf::Sprite* ZwrocMapeGry(int mat) {
		 return &mapaGry[mat][0];
	 }
	 void zwrotKolSprite(sf::Sprite SprEnemyTab[]) {//TUTAJ MO¯NA DODAÆ 
		for (int i = 0; i < O; i++) {
			for (int j=0; j < 10; j++) {
				if (SprEnemyTab[j].getGlobalBounds().intersects(mapaGry[0][i].getGlobalBounds()))
					std::cout << "kolizja bota "<<j<<" z "<<i<<std::endl;
				SprEnemyTab[j].setPosition(SprEnemyTab[j].getPosition().x-1, SprEnemyTab[j].getPosition().y);
				}
		}
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
	 void trafiPoc(sf::Sprite pocisk) {
		 for (int i = 0; i < O; i++) {
			 if (pocisk.getGlobalBounds().intersects(mapaGry[0][i].getGlobalBounds())) {
				 //std::cout << "Trafiony otoczenie typu cegla " << i << " ma jeszcze " << mapaDes[0][i]<< " wytrzymalosci" << std::endl;
				 --mapaDes[0][i];
				 if (mapaDes[0][i] == 0)
					 mapaGry[0][i].setPosition(-100, -100);//tymczasowe przeniesienie poza plansze
				 delete  *mapaGry[0][i];
				 //AKCJA DLA ZDERZENIA POCISKU Z CEG£¥
			 }
		 }
		 for (int i = 0; i < P; i++) {
			 if (pocisk.getGlobalBounds().intersects(mapaGry[1][i].getGlobalBounds())) {
				 std::cout << "Trafiony otoczenie typu skala " << i << " ma jeszcze " << mapaDes[1][i] << " wytrzymalosci" << std::endl;
				 --mapaDes[1][i];
				 if (mapaDes[1][i] == 0)
					 mapaGry[1][i].setPosition(-100, -100);//tymczasowe przeniesienie poza plansze
				 //AKCJA DLA ZDERZENIA POCISKU ZE SKA£¥
			 }
		 }
	 }
	//metoda czy trafioona - sprawdza czy obiekt zosta³ trafiony pociskiem
	void czyTrafiony(sf::Sprite pocisk, int N) {
		for (int j = 0; j < N; j++)
			if (pocisk.getGlobalBounds().intersects(wall[j].getGlobalBounds())) {
				wall[j].setPosition(1000, 1000);//przeniesienie elementu poza plansze
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
	sf::RenderWindow window(sf::VideoMode(800, 600), "TANK 2021");
	sf::Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int hight = size.y;
	Player p1;
	Enemy e1(1);
	ObjSrd s1(200);
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
		s1.draw(window,2);
		//p1.detZderzenie(s1.kierKol(p1.zwrocSprite()));
		p1.zderzenieObj(s1.ZwrocMapeGry(0), s1.zwrocRozTab(0));//m¿na urzyæ funkcji zwracaj¹cej rozmiar tab
		p1.zderzenieObj(s1.ZwrocMapeGry(1), s1.zwrocRozTab(1));
		p1.zderzenieObj(e1.zwroctabSprite(), 2);
		e1.ruch_bot(window);
		e1.zderzenieObj(s1.ZwrocMapeGry(0), s1.zwrocRozTab(0));//stabilne dla cegiel
		e1.zderzenieObj(s1.ZwrocMapeGry(1), s1.zwrocRozTab(1));//stabilne dla kamieni
		e1.zderzenieObj(p1.zwrocPSprite(), 1);
		e1.zderzeniaBot(p1.zwrocSprite());
		p1.trafieniePocisk(s1.ZwrocMapeGry(0),s1.zwrocRozTab(0));
		p1.trafieniePocisk(s1.ZwrocMapeGry(1),s1.zwrocRozTab(1));
		p1.trafieniePocisk(e1.zwroctabSprite(), 10);
			//if (po.trafienie(e1[i].zwrocSprite()) == true)
		////po.strzal(p1.zwrocSprite(), window);
		////s1.czyTrafiony(po.zwrocSprite(), 50);
		p1.strzal(window);
		s1.draw(window,0);//rysowanie cegiel
		s1.draw(window,1);//rysowanie kamienia
		e1.trafiPoc(p1.zwrocPocisk());
		s1.trafiPoc(p1.zwrocPocisk());
		e1.strzalBot(p1.zwrocSprite());
		p1.draw(window);
		e1.draw(window);
		s1.draw(window,3);//rysowanie zaroœli
		window.display();
		Opoznienie(1);
	}
	return 0;
}
