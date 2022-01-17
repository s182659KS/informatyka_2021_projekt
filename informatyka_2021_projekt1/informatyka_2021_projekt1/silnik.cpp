#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <math.h>
#include <vector>
#include "headers.h"
#pragma warning(disable:4996)

float pi = 3.14159;

//ZAPIS STANU GRY
void zapisGry(stanGry graczSave, int id_save, int getTank, float graczPozx, float graczPozy, std::string nick_save, int pkt_save, int pck_save, int pan_save, float spd_save, int ilEne_save)
{
	graczSave.wybCzolg = getTank;
	graczSave.xGracz = graczPozx;
	graczSave.yGracz = graczPozy;
	graczSave.nick = nick_save;
	graczSave.punkty = pkt_save;
	graczSave.pociski = pck_save;
	graczSave.pancerz = pan_save;
	graczSave.speed = spd_save;
	graczSave.iloscEnemy = ilEne_save;
	FILE* fp;
	std::cout << "Zapis stanu!\n";
	fp = fopen("saveGame1.dat", "wb");
	if (id_save == 2)
		fp = fopen("saveGame2.dat", "wb");
	if (id_save == 3)
		fp = fopen("saveGame3.dat", "wb");
	fwrite(&graczSave, sizeof(stanGry), 1, fp);
	fclose(fp);

}
//ODCZYT STANU GRY
void odczytGry(stanGry graczSave, int id_save, int* setTank, float* graczPozx, float* graczPozy, std::string* nick_save, int* pkt_save, int* pck_save, int* pan_save, float* spd_save, int* ilEne_save)
{
	FILE* fp;
	std::cout << "Odczyt!\n";
	fp = fopen("saveGame1.dat", "rb");
	if (id_save == 2)
		fp = fopen("saveGame2.dat", "rb");
	if (id_save == 3)
		fp = fopen("saveGame3.dat", "rb");
	fread(&graczSave, sizeof(stanGry), 1, fp);
	fclose(fp);

	*graczPozx = graczSave.xGracz;
	*graczPozx = graczSave.yGracz;
	*nick_save = graczSave.nick;
	*pkt_save = graczSave.punkty;
	*pck_save = graczSave.pociski;
	*pan_save = graczSave.pancerz;
	*spd_save = graczSave.speed;
	*ilEne_save = graczSave.iloscEnemy;
	*setTank = graczSave.wybCzolg;

}

//GENERATOR OPUZNIEN
void Opoznienie(int opoznienie)//o dan¹ liczbê sekund
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
//PORÓWNANIE DLA FUNKCI QSORT
int porownaj(const void* left, const void* right) {
	const wynikiGry* a = (const wynikiGry*)left;
	const wynikiGry* b = (const wynikiGry*)right;
	if (a->punkty > b->punkty) {
		return -1;
	}
	else if (a->punkty < b->punkty) {
		return 1;
	}
	else {
		return 0;
	}
}

//MENU

Menu::Menu(float width, float height)
{	//laduj czcionke
	if (!font.loadFromFile("CSStamps.ttf"))
	{
		return;
	}
	//

	//rysowanie elementow menu
	header[0].setFont(font);
	header[0].setString("TANK 2021");
	header[0].setFillColor(sf::Color::White);
	header[0].setPosition(sf::Vector2f(250, 10));
	header[0].setCharacterSize(60);

	header[1].setFont(font);
	header[1].setString("nowa gra:");
	header[1].setFillColor(sf::Color::White);
	header[1].setPosition(sf::Vector2f(250, 10));
	header[1].setCharacterSize(60);

	header[2].setFont(font);
	header[2].setString("kontynuj gre:");
	header[2].setFillColor(sf::Color::White);
	header[2].setPosition(sf::Vector2f(250, 10));
	header[2].setCharacterSize(60);

	header[3].setFont(font);
	header[3].setString("tablica wynikow:");
	header[3].setFillColor(sf::Color::White);
	header[3].setPosition(sf::Vector2f(250, 10));
	header[3].setCharacterSize(60);

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("NOWA GRA");
	menu[0].setPosition(sf::Vector2f(50, 100));
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("KONTYNUUJ GRE");
	menu[1].setPosition(sf::Vector2f(50, 150));
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("OSTATNIE WYNIKI");
	menu[2].setPosition(sf::Vector2f(50, 200));
	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("WYJSCIE");
	menu[3].setPosition(sf::Vector2f(50, 250));

	//Wyœwietlanie menu wyboru czo³gu
	Tank1txt.loadFromFile("teksturaPlayer1.png");
	Tank[0].setTexture(Tank1txt);
	Tank[0].setPosition(200, 265);
	Tank[0].setOrigin(25, 25);
	Tank[0].setScale(2, 2);
	Tank[0].setColor(sf::Color(255, 255, 255, 128));//Przezroczysty

	Tank2txt.loadFromFile("teksturaPlayer2.png");
	Tank[1].setTexture(Tank2txt);
	Tank[1].setPosition(400, 265);
	Tank[1].setOrigin(25, 25);
	Tank[1].setScale(2, 2);
	Tank[1].setColor(sf::Color(255, 255, 255, 128));

	Tank3txt.loadFromFile("teksturaPlayer3.png");
	Tank[2].setTexture(Tank3txt);
	Tank[2].setPosition(600, 265);
	Tank[2].setOrigin(25, 25);
	Tank[2].setScale(2, 2);
	Tank[2].setColor(sf::Color(255, 255, 255, 128));
	//opisy
	opisTank[0].setFont(font);
	opisTank[0].setString("R4 'MAUSE'\nPancerz **\nUzbrojenie ***\nSzybkosc *****");
	opisTank[0].setFillColor(sf::Color::White);
	opisTank[0].setPosition(sf::Vector2f(150, 320));
	opisTank[0].setCharacterSize(18);

	opisTank[1].setFont(font);
	opisTank[1].setString("R8 'OTIS'\nPancerz ***\nUzbrojenie ***\nSzybkosc ***");
	opisTank[1].setFillColor(sf::Color::White);
	opisTank[1].setPosition(sf::Vector2f(350, 320));
	opisTank[1].setCharacterSize(18);

	opisTank[2].setFont(font);
	opisTank[2].setString("R12 'BIG-RAT'\nPancerz *****\nUzbrojenie ***\nSzybkosc **");
	opisTank[2].setFillColor(sf::Color::White);
	opisTank[2].setPosition(sf::Vector2f(550, 320));
	opisTank[2].setCharacterSize(18);

	//WYBÓR POZIOMU 
	wyborPoz[0].setFont(font);
	wyborPoz[0].setFillColor(sf::Color::White);
	wyborPoz[0].setString("POZIOM 1");
	wyborPoz[0].setPosition(sf::Vector2f(50, 450));

	wyborPoz[1].setFont(font);
	wyborPoz[1].setFillColor(sf::Color::White);
	wyborPoz[1].setString("POZIOM 2");
	wyborPoz[1].setPosition(sf::Vector2f(250, 450));

	wyborPoz[2].setFont(font);
	wyborPoz[2].setFillColor(sf::Color::White);
	wyborPoz[2].setString("POZIOM 3");
	wyborPoz[2].setPosition(sf::Vector2f(450, 450));

	//POZIOM PIERWSZY MENU
	menu1[0].setFont(font);
	menu1[0].setFillColor(sf::Color::Red);
	menu1[0].setString("PODAJ NAZWE GRACZA:");
	menu1[0].setPosition(sf::Vector2f(50, 100));
	menu1[1].setFont(font);
	menu1[1].setFillColor(sf::Color::White);
	menu1[1].setString("WYBIERZ CZO£G:");
	menu1[1].setPosition(sf::Vector2f(50, 150));
	menu1[2].setFont(font);
	menu1[2].setFillColor(sf::Color::White);
	menu1[2].setString("POZIOM ROZGRYWKI:");
	menu1[2].setPosition(sf::Vector2f(50, 400));
	menu1[3].setFont(font);
	menu1[3].setFillColor(sf::Color::White);
	menu1[3].setString("<ROZPOCZNIJ GRE>");
	menu1[3].setPosition(sf::Vector2f(50, 500));

}
//rysowanie menu w biezacym oknie
void Menu::draw(sf::RenderWindow& window, int poziomMenu)
{

	if (poziomMenu == 0) {
		window.draw(header[0]);
		for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
		{
			window.draw(menu[i]);
		}
	}
	else if (poziomMenu == 1) {
		window.draw(header[1]);
		window.draw(nazwaGracza);
		for (int i = 0; i < LICZBA_CZOLGOW; i++) {
			window.draw(Tank[i]);
			if (selectCzolg == 0)
				window.draw(opisTank[0]);
			if (selectCzolg == 1)
				window.draw(opisTank[1]);
			if (selectCzolg == 2)
				window.draw(opisTank[2]);
		}
		for (int i = 0; i < LICZBA_POZ; i++)
			window.draw(wyborPoz[i]);
		for (int i = 0; i < LICZBA_WYB_ATR; i++)
			window.draw(menu1[i]);
	}
	else if (poziomMenu == 2) {
		window.draw(header[2]);
	}
	else if (poziomMenu == 3) {
		window.draw(header[3]);
		for (int i = 0; i < Np; i++)
		{
			window.draw(players[i]);
		}
	}
}
//ZAPIS TABLICY WYNIKÓW
void Menu::tablicaWynikZapis(int punkty, std::string nazwaGracz ) {
	wynikiGry listaGraczy;
	listaGraczy.punkty = punkty;
	listaGraczy.nick = nazwaGracz;
	FILE* fp;
	fp = fopen("gracze.dat", "a+b");
	fwrite(&listaGraczy, sizeof(wynikiGry), 1, fp);
	std::cout << "Zapis do listy graczy" << std::endl;
	fclose(fp);
}
//SORTOWANIE WYNIKÓW
void Menu::sortujListe()
{
	qsort(player_char, Np, sizeof(wynikiGry), porownaj);
}
//ODCZYT Z PLIKU WYNIKÓW
void Menu::tablicaWynikOdczyt(int N) {
	//stanGry listaGraczyOdczyt[10];
	FILE* fp = fopen("gracze.dat", "r+b");
	unsigned int rozmiar_plik = 0, ile_graczy = 0;
	fseek(fp, 0, SEEK_END);//na ostatni bajt
	rozmiar_plik = ftell(fp);//czytaj indeks ostatniego bajtu
	ile_graczy = rozmiar_plik / sizeof(wynikiGry);
	Np = ile_graczy;
	if (ile_graczy > N)
		Np = N;
	//std::cout <<"liczbaSaveow: " << ile_graczy<< std::endl;

	players = new sf::Text[Np];
	player_char = new wynikiGry[Np];

	rewind(fp);//czytaj od poczatku
	fread(player_char, sizeof(wynikiGry), Np, fp);
	fclose(fp);

}
//PRYGOTOWNIE TABLICY WYNIKOW
void Menu::ladujListeWyn()
{
	std::string tmp_tekst;
	for (int i = 0; i < Np; i++)
	{
		players[i].setFont(font);
		players[i].setCharacterSize(30);
		players[i].setFillColor(sf::Color::Green);
		players[i].setPosition(100, 100 + i * 50);

		tmp_tekst = std::to_string(i+1);
		tmp_tekst += ". Nick: ";
		tmp_tekst += player_char[i].nick;
		tmp_tekst += "  Punkty: " + std::to_string(player_char[i].punkty);
		players[i].setString(tmp_tekst);
	}
}
void Menu::drawLista(sf::RenderWindow& window)
{
	for (int i = 0; i < Np; i++)
	{
		window.draw(players[i]);
	}
}
void Menu::podajNazweGracza(sf::Event event, sf::RenderWindow& window) {
	sf::Text nazwaGraczaTemp;
	if (itm == 0) {
		bool flaga = false;
		//std::cout << "PODAJ NAZWE" << std::endl;
		if (event.type == sf::Event::TextEntered && selectedItem2 == 0)
			if (std::isprint(static_cast <wchar_t>(event.text.unicode), std::locale())) {
				nazwaGraczaTemp.setString(nazwaGracza.getString());
				nazwaGracza.setString(nazwaGracza.getString() + event.text.unicode);
				flaga = true;
			}
		nazwaGracza.setFont(font);
		nazwaGracza.setFillColor(sf::Color::Green);
		nazwaGracza.setPosition(sf::Vector2f(300, 100));
		window.draw(nazwaGracza);
		Opoznienie(150);
	}
}
//ZWROT WYBORU DLA MENU G£ÓWNEGO
int Menu::getSelectedItem(int i) {
	if (i == 0)
		return selectedItem;
	if (i == 1)
		return itm + 1;
	if (i == 2)
		return selectedItem2;

}
void Menu::setPoziomMenu(int n) {
	poziomMenu = n;
}

int Menu::przesunMenu(sf::Event event, sf::RenderWindow& window, sf::Text tabWyb[], int rozTab, int kierunek) {
	while (window.pollEvent(event)) {//kierunek = 1 -> gora/dol
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Down) {
				if (itm >= 0 && itm < rozTab)
					tabWyb[itm].setFillColor(sf::Color::White);
				tabWyb[itm].setStyle(sf::Text::Regular);
				itm++;
				if (itm >= rozTab)
					itm = 0;
				tabWyb[itm].setFillColor(sf::Color::Red);
				tabWyb[itm].setStyle(sf::Text::Bold);
			}
			else if (event.key.code == sf::Keyboard::Up) {
				if (itm >= 0 && itm < rozTab)
					tabWyb[itm].setFillColor(sf::Color::White);
				tabWyb[itm].setStyle(sf::Text::Regular);
				itm--;
				if (itm < 0)
					itm = rozTab - 1;
				tabWyb[itm].setFillColor(sf::Color::Red);
				tabWyb[itm].setStyle(sf::Text::Bold);
			}
			else if (itm == 1) {
				if (event.key.code == sf::Keyboard::Left) {
					Tank[selectCzolg].setColor(sf::Color(255, 255, 255, 128));
					Tank[selectCzolg].setScale(2, 2);
					--selectCzolg;
					if (selectCzolg < 0)
						selectCzolg = LICZBA_CZOLGOW - 1;
					Tank[selectCzolg].setColor(sf::Color(255, 255, 255, 255));
					Tank[selectCzolg].setScale(2.5, 2.5);

				}
				else if (event.key.code == sf::Keyboard::Right) {
					Tank[selectCzolg].setColor(sf::Color(255, 255, 255, 128));
					Tank[selectCzolg].setScale(2, 2);
					++selectCzolg;
					if (selectCzolg >= LICZBA_CZOLGOW)
						selectCzolg = 0;
					Tank[selectCzolg].setColor(sf::Color(255, 255, 255, 255));
					Tank[selectCzolg].setScale(2.5, 2.5);
				}
			}
			else if (itm == 2) {
				if (event.key.code == sf::Keyboard::Left) {
					wyborPoz[selectPoziom].setFillColor(sf::Color::White);
					wyborPoz[selectPoziom].setStyle(sf::Text::Regular);
					--selectPoziom;
					if (selectPoziom < 0)
						selectPoziom = LICZBA_POZ - 1;
					wyborPoz[selectPoziom].setFillColor(sf::Color::Green);
					wyborPoz[selectPoziom].setStyle(sf::Text::Bold);

				}
				else if (event.key.code == sf::Keyboard::Right) {
					wyborPoz[selectPoziom].setFillColor(sf::Color::White);
					wyborPoz[selectPoziom].setStyle(sf::Text::Regular);
					++selectPoziom;
					if (selectPoziom >= LICZBA_POZ)
						selectPoziom = 0;
					wyborPoz[selectPoziom].setFillColor(sf::Color::Green);
					wyborPoz[selectPoziom].setStyle(sf::Text::Bold);
				}
			}
			 if (event.key.code == sf::Keyboard::Enter) {//zwrocenie wybranego elementu poprzez Enter
				
				return (itm + 1);
			}
		}
	}
}
void Menu::zwrotSetPly(int* Poziom, int* Czolg, std::string* NazwaPly) {
	*Poziom = selectPoziom + 1;
	*Czolg = selectCzolg + 1;
	*NazwaPly = std::string(nazwaGracza.getString());

}
sf::Text* Menu::zwrocTab(int id) {
	if (id == 1)
		return menu;
	if (id == 2)
		return menu1;
	if (id == 3)
		return opisTank;

}



	Interfejs::Interfejs(sf::RenderWindow& window) {
		//laduj czcionke

		if (!font.loadFromFile("CSStamps.ttf"))
		{
			return;
		}
		koniecGryW.setFont(font);
		koniecGryW.setString("-WYGRANA-");
		koniecGryW.setOutlineThickness(2);
		koniecGryW.setOutlineColor(sf::Color::Red);
		koniecGryW.setFillColor(sf::Color::White);
		koniecGryW.setPosition(sf::Vector2f(window.getSize().x / 2-150, window.getSize().y / 2-30));
		koniecGryW.setCharacterSize(80);

		koniecGryP.setFont(font);
		koniecGryP.setString("KONIEC GRY");
		koniecGryW.setOutlineThickness(2);
		koniecGryW.setOutlineColor(sf::Color::Red);
		koniecGryP.setFillColor(sf::Color::White);
		koniecGryP.setPosition(sf::Vector2f(window.getSize().x / 2 - 150, window.getSize().y / 2 - 30));
		koniecGryP.setCharacterSize(80);


		//Wyœwietlenie menu rozgrywki
		rozOknaMenu.x = 400;
		rozOknaMenu.y = 400;
		menuAkcji.setSize(rozOknaMenu);
		menuAkcji.setOrigin(rozOknaMenu.x / 2, rozOknaMenu.y / 2);
		menuAkcji.setPosition(window.getSize().x / 2, window.getSize().y / 2);
		menuAkcji.setOutlineThickness(5);
		menuAkcji.setOutlineColor(sf::Color::Red);
		menuAkcji.setFillColor(sf::Color::Black);

		//tekst help-u
		for (int i = 0; i < 3; i++) {
			help[i].setFont(font);
			help[i].setFillColor(sf::Color::White);
		}

		help[0].setString("HELP");
		help[0].setPosition((window.getSize().x / 2) - rozOknaMenu.x / 2 + 20, window.getSize().y / 2 - rozOknaMenu.y / 2 + 25);
		help[0].setCharacterSize(40);
		help[1].setString("W grze wcielasz siê w dowódce czolgu.\nTwoim zadaniem jest zniszczenie bazy wroga,\nzanim on zniszczy twoja baze\nSterowanie:\n<Up> - jazda do przodu\n<Down> - jazda wstecz\n<Left> - Obrót w lewo\n<Right> - obrót w prawo\n<W> - wystrzal");
		help[1].setPosition((window.getSize().x / 2) - rozOknaMenu.x / 2 + 20, menuAkcji.getPosition().y - 100);
		help[1].setCharacterSize(20);
		help[2].setString("Aby konynuowac gre nacisnij: <Enter>");
		help[2].setPosition((window.getSize().x / 2) - rozOknaMenu.x / 2 + 15, window.getSize().y / 2 + rozOknaMenu.y / 2 - 25);
		help[2].setCharacterSize(20);

		//menu wyjœcia
		for (int i = 0; i < 3; i++) {
			menuEsc[i].setFont(font);
			menuEsc[i].setFillColor(sf::Color::White);
			menuEsc[i].setCharacterSize(40);
		}
		menuEsc[0].setString("KONTYNUJ");
		menuEsc[0].setPosition(menuAkcji.getPosition().x - 100, menuAkcji.getPosition().y - menuAkcji.getSize().y / 4 - 40);
		menuEsc[1].setString("ZAPISZ GRE");
		menuEsc[1].setPosition(menuAkcji.getPosition().x - 100, menuAkcji.getPosition().y - 40);
		menuEsc[2].setString("WYJDZ Z GRY");
		menuEsc[2].setPosition(menuAkcji.getPosition().x - 100, menuAkcji.getPosition().y + menuAkcji.getSize().y / 4 - 40);
		//parametry rozgrywki
		for (int i = 0; i < 3; i++) {
			parametrGracz[i].setFont(font);
			parametrGracz[i].setFillColor(sf::Color::White);
			parametrGracz[i].setCharacterSize(20);
		}
		parametrGracz[0].setPosition(20,5);
		parametrGracz[1].setPosition(140,5);
		parametrGracz[2].setPosition(window.getSize().x-100, 5);

	}
	//RYSOWANIE INTERFEJSU
	void Interfejs::draw(sf::RenderWindow& window, sf::Event& event, int opcja){

			//window.draw(menuAkcji);
			if (opcja == 1) {//menu helup
				window.draw(menuAkcji);
				for (int i = 0; i < 3; i++)
					window.draw(help[i]);
			}
			if (opcja == 2) {//menu wyjœcia
				window.draw(menuAkcji);
				for (int i = 0; i < 3; i++)
					window.draw(menuEsc[i]);
			}
			if (opcja == 3) {//napis wygranej
				window.draw(koniecGryW);
			}
			if (opcja == 4) {//napis przegranej
				window.draw(koniecGryP);
			}
	}
	//WYBÓR W MENU PODCZAS GRY
	int Interfejs::wybor(sf::Event event, sf::RenderWindow& window) {
		while (window.pollEvent(event)) {
			if (event.key.code == sf::Keyboard::Down) {
				if (itm >= 0 && itm < 3)
					menuEsc[itm].setFillColor(sf::Color::White);
				menuEsc[itm].setStyle(sf::Text::Regular);
				itm++;
				if (itm >= 3)
					itm = 0;
				menuEsc[itm].setFillColor(sf::Color::Red);
				menuEsc[itm].setStyle(sf::Text::Bold);
			}
			else if (event.key.code == sf::Keyboard::Up) {
				if (itm >= 0 && itm < 3)
					menuEsc[itm].setFillColor(sf::Color::White);
				menuEsc[itm].setStyle(sf::Text::Regular);
				itm--;
				if (itm < 0)
					itm = 2;
				menuEsc[itm].setFillColor(sf::Color::Red);
				menuEsc[itm].setStyle(sf::Text::Bold);
			}
			else if (event.key.code == sf::Keyboard::Enter) {
				
				return (itm+1);
			}
		}
	}
	//ZWRACA WYBRANY ELEMENT
	int Interfejs::zwrotWybor() {
		return (itm + 1);
	}
	//PONIERA I WYŒWIETLA PARAMETRY ROZGRYWKI
	void Interfejs::getStanPly(sf::RenderWindow& window, int punkty, int pociski, int pancerz) {
		std::string punktyStr;
		std::string pociskiStr;
		std::string pancerzStr;
		punktyStr = std::to_string(punkty);
		pociskiStr = std::to_string(pociski);
		pancerzStr = std::to_string(pancerz);
		parametrGracz[0].setString("Pancerz:" + pancerzStr);
		parametrGracz[1].setString("Pociski:" + pociskiStr);
		parametrGracz[2].setString("Punkty:" + punktyStr);
		for (int i = 0; i < 3; i++)
			window.draw(parametrGracz[i]);

	}

	//OBS£UGA GRACZA

	Player::Player() {}
	Player::Player(int punktySet, int pociskiSet, float pancerzSet, float speedSet, int setCzolg) {
		iloscPociskow = 1;
		flaga_wygranej = false;
		punkty = punktySet;
		pociski = pociskiSet;
		pancerz = pancerzSet;
		speed = speedSet;
		pozycja.x = 200;
		pozycja.y = 550;
		if(setCzolg==1)
			plrtxt.loadFromFile("teksturaPlayer1.png");
		if (setCzolg == 2)
			plrtxt.loadFromFile("teksturaPlayer2.png");
		if (setCzolg == 3)
			plrtxt.loadFromFile("teksturaPlayer3.png");
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
	float Player::ruch(sf::RenderWindow& window, float speedPly, bool pauza) {//sterowanie pojazdem gracza
		float rotacja;
		rotacja = plrtank.getRotation() - 90;
		if (!pauza == true) {
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
		}
		return rotacja;
	}
	sf::Sprite Player::strzal(sf::RenderWindow& window) {//metoda dla pocisku
		flagaStrzal = przelPoc(200);
		pocisktxt.loadFromFile("pocisktxt.png");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && flagaStrzal == true && pociski > 0) {
			pociski--;
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
	void Player::trafieniePocisk(sf::Sprite ply, sf::Sprite* pociski, sf::Sprite* obiektOto, int SizeTab) {//PRZEBUDOWA
		for (int i = 0; i < SizeTab; i++) {
			for (int j = 0; j < iloscPociskow; j++) {
				if (abs(pociski[j].getPosition().x - obiektOto[i].getPosition().x) < 18 && abs(pociski[j].getPosition().y - obiektOto[i].getPosition().y) < 18) {
					//pocisk[j].getGlobalBounds().intersects(obiektOto[i].getGlobalBounds()) //pocisk[j].getPosition().x - obiektOto[i].getPosition().x) < 25 && abs(pocisk[j].getPosition().y - obiektOto[i].getPosition().y) < 25
					pociski[j].setPosition(-200, -100);//ply.getPosition()
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
	float Player::brodzenie(sf::Sprite* Woda, int iloscObj) {//TO NIE CHCE DZIA£AÆ
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
			if (pocisk[0].getGlobalBounds().intersects(orzel.getGlobalBounds())) {
				wygrana = true;
			}
		return wygrana;
	}
	int Player::zwrocStanPly(int id) {
		if (id == 1)
			return int(pancerz);
		if (id == 2)
			return punkty;
		if (id == 3)
			return pociski;
	}
	void Player::setTxtCzolg(int setCzolg) {
		if (setCzolg == 1)
			plrtxt.loadFromFile("teksturaPlayer1.png");
		if (setCzolg == 2)
			plrtxt.loadFromFile("teksturaPlayer2.png");
		if (setCzolg == 3)
			plrtxt.loadFromFile("teksturaPlayer3.png");
		plrtank.setTexture(plrtxt);
	}
	void Player::setPoz(int x, int y) {
		plrtank.setPosition(x, y);
	}
	int* Player::zwrocPanc() {
		return &pociski;
	}
	int* Player::zwrocPunkty() {
		return &punkty;
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

	//Dla wroga

	Enemy::Enemy() {
		N = 1;
		n = 0;
		speed = 1;
		ruchBot = 300;//ilosc kroków bota
		rotBot = 90;//k¹t obrotu
		pancerzEnemy = 100;
		enemy = new sf::Sprite[N];
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distX(10, 15);//losowa pozycja botów w osi X
		std::uniform_int_distribution<> distY(1, 2);// losowa pozycja botów w osi Y
		enmtxt.loadFromFile("teksturaPrzeciwnik.png");
		for (int i = 0; i < N; i++) {
			enemy[i].setTexture(enmtxt);
			enemy[i].setPosition(distX(gen) * 50 - 25, distY(gen) * 60 - 30);
			enemy[i].setOrigin(25, 30);//œrodek sprita
		}
		//dla pociskow
		iloscPociskow = 1;
		zestrzelony = false;
		pocisk = new sf::Sprite[iloscPociskow];
		kierPoc = new sf::Vector2f[iloscPociskow];

	}
	void Enemy::ruch_bot(sf::RenderWindow& window) {
		float rotacja;
		for (int i = 0; i < N; i++) {
			rotacja = enemy[i].getRotation() - 90;//ustawienie w³aœciwej orietacji pojazdu
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
	void Enemy::strzalBot(sf::Sprite ply, sf::RenderWindow& window, sf::Sprite orzel) {
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
			if ((cel <= 10 || celNaOrla <= 10) && flagaStrzal == true && iloscPociskow > 0) {
				for (int j = 0; j < iloscPociskow; j++) {////auto& i:pocisk

					pocisk[j].setTexture(pocisktxt);
					pocisk[j].setPosition(enemy[i].getPosition());
					pocisk[j].setOrigin(2, 2);
					kierPoc[j].x = cos((enemy[i].getRotation() - 90) * pi / 180);
					kierPoc[j].y = sin((enemy[i].getRotation() - 90) * pi / 180);
					flagaStrzal = false;
					ruchPoc = 1;
				}

			}
			for (int i = 0; i < iloscPociskow; i++) {
				if (ruchPoc == 1) {
					pocisk[i].move(4 * kierPoc[i].x, 4 * kierPoc[i].y);
					window.draw(pocisk[i]);
				}

			}

		}
	}
	//obs³uga wystrzelonych przez bota pocisków
	void Enemy::trafieniePocisk(sf::Sprite ply, char typ, sf::Sprite* pociski, sf::Sprite* obiektOto, int SizeTab, int* pancerzP) {//PRZEBUDOWA typ - dla okreœlenia typu
		for (int j = 0; j < iloscPociskow; j++) {
			for (int i = 0; i < SizeTab; i++) {
				if (typ == 'W' && abs(pociski[j].getPosition().x - obiektOto[i].getPosition().x) < 18 && abs(pociski[j].getPosition().y - obiektOto[i].getPosition().y) < 18) {
					pociski[j].setPosition(-200, -100);//umieszczenie pocisku poza obszarem planszy
					//std::cout << "BOT trafiono obiekt oto " << i << std::endl;
					ruchPoc = 0;
				}
				if (typ == 'G' && abs(pociski[j].getPosition().x - ply.getPosition().x) < 20 && abs(pociski[j].getPosition().y - ply.getPosition().y) < 20) {
					pociski[j].setPosition(-200, -100);
					*pancerzP--;
					//std::cout << "PLEYER trafiony przez " << j << std::endl;
					ruchPoc = 0;
				}
			}


		}

	}
	//trafienie przez pocisk
	bool Enemy::trafiPoc(sf::Sprite* pocisk, int id, int* punkty) {//traienie przez pocisk
		idBot = id;
		for (int i = 0; i < N; i++) {
			if (pocisk[0].getGlobalBounds().intersects(enemy[i].getGlobalBounds())) {
				//std::cout << "Trafiony enemy " << id << "PANCERZ " << pancerzEnemy << std::endl;
				*punkty = *punkty + 5;//gdy trafiony +5p
				//TUTAJ PROCEDURA OBS£UGI TRAFIEÑ BOTÓW
				pancerzEnemy = pancerzEnemy - 1;//-1 do pancerza
				if (pancerzEnemy <= 0) {
					enmtxt.loadFromFile("teksturaPrzeciwnikKaput.png");
					enemy[i].setTexture(enmtxt);
					*punkty = *punkty + 100;//gdy zestrzelony +100p
					zestrzelony = true;
				}
			}
		}
		return zestrzelony;
	}
	//POCISKI LEPIEJ ZROBIC NA WEKTORACH/KONTENERACH
	//sf::Sprite strzal(sf::RenderWindow& window) {//metoda dla pocisku
	//	//std::vector<sf::Sprite> pocisk
	void Enemy::zderzeniaBot() {//zderzenia pomiêdzy botami - ZBENDNE PRZY POJEDYÑCZYCH OBIEKTACH
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (enemy[i].getGlobalBounds().intersects(enemy[j].getGlobalBounds())) {
					if (enemy[i].getPosition().x < enemy[j].getPosition().x) {
						enemy[i].setPosition(enemy[i].getPosition().x - 1, enemy[i].getPosition().y);
						enemy[i].rotate(2);
					}
					if (enemy[i].getPosition().x > enemy[j].getPosition().x) {
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
	bool Enemy::WinEne(sf::Sprite orzel) {
		bool wygrana;
		if (pocisk[0].getGlobalBounds().intersects(orzel.getGlobalBounds())) {
			wygrana = true;
		}
		return wygrana;
	}
	void Enemy::draw(sf::RenderWindow& window) {
		for (int i = 0; i < N; i++) {
			window.draw(enemy[i]);
		}
	}
	sf::Sprite* Enemy::zwroctabSprite() {
		return enemy;
	}
	sf::Sprite Enemy::zwrocSprite(int id)  {
		return enemy[id];
	}
	sf::Sprite* Enemy::zwrocPoc() {
		return pocisk;
	}
	//ZDERZENIA NA PODSTAWIE ODLEG£OŒCI:
	//abs(enemy[i].getPosition().x - mapaGry[j].getPosition().x) < 40 && abs(enemy[i].getPosition().y - mapaGry[j].getPosition().y) < 40
	//ZDERENIA NA PODSTAWIE NACHODZENIA PIXELI:
	//enemy[i].getGlobalBounds().intersects(mapaGry[j].getGlobalBounds())
	void Enemy::zderzenieObj(sf::Sprite* mapaGry, int rozmiarTab) {//pobiera kierunek kolizji i steruje spritem
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


	//OBIEKTY OTOCZENIA
	ObjSrd::ObjSrd(int N) {
		//sprawdzanie iloœci elementów
		n = N;
		orzeltex.loadFromFile("orzel.png");
		orzel[0].setTexture(orzeltex);
		orzel[0].setPosition(405, 15);//ustawienie pozycji or³a przeciwnika
		orzel[0].setOrigin(15, 15);
		orzel[1].setTexture(orzeltex);
		orzel[1].setPosition(405, 585);//ustawienie pozycji or³a gracza
		orzel[1].setOrigin(15, 15);
		fp = fopen("mapa1.txt", "rb");
		if (!fopen("mapa1.txt", "rb"))
			std::cout << "nie otwarto pliku\n";
		for (int l = 0; l < N; l++) {
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

		}
		std::fclose(fp);
		std::cout << O << "," << P << "," << R << "," << S << std::endl;//drukowanie elementów danego typu
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

	}
	sf::Vector2f ObjSrd::kierKol(sf::Sprite plr_poz) {//iteracja po wszystkich utworzonych obiektach ototczenia , w poszukwaniu kolizji
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
	sf::Sprite ObjSrd::zwrocOrla(int id) {//ZWRACA SPRITE OR£A ABY SPRAWDZIÆ WYGRAN¥
		return orzel[id];
	}
	sf::Sprite* ObjSrd::ZwrocMapeGry(int mat) {
		return &mapaGry[mat][0];
	}
	int ObjSrd::zwrocRozTab(int mat) {
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
	void ObjSrd::trafiPoc(sf::Sprite* pocisk) {//PRZYDA£A BY SIE FUNKCJA ZWRACANIA ILOSCI POCISKÓW
		for (int i = 0; i < O; i++) {
			if (pocisk[0].getGlobalBounds().intersects(mapaGry[0][i].getGlobalBounds())) {
				//std::cout << "Trafiony otoczenie typu cegla " << i << " ma jeszcze " << mapaDes[0][i] << " wytrzymalosci" << std::endl;
				--mapaDes[0][i];
				if (mapaDes[0][i] == 0)
					mapaGry[0][i].setPosition(-100, -100);//tymczasowe przeniesienie poza plansze
				//AKCJA DLA ZDERZENIA POCISKU Z CEG£¥
			}
		}
		for (int i = 0; i < P; i++) {
			if (pocisk[0].getGlobalBounds().intersects(mapaGry[1][i].getGlobalBounds())) {
				////std::cout << "Trafiony otoczenie typu skala " << i << " ma jeszcze " << mapaDes[1][i] << " wytrzymalosci" << std::endl;
				--mapaDes[1][i];
				if (mapaDes[1][i] == 0)
					mapaGry[1][i].setPosition(-100, -100);//tymczasowe przeniesienie poza plansze
				//AKCJA DLA ZDERZENIA POCISKU ZE SKA£¥
			}
		}
	}
	//void generacja(int poziom) {//generatior rozmieszczenia elementów
	//	int const N = 50;//tymczasowo, domyœlnie dynamiczna alokacja pam.
	//	if (poziom == 1)
	//		int const N = 50;
	//	else if (poziom == 2)
	//		int const N = 75;
	//	else if (poziom == 3)
	//		int const N = 100;
	//	std::mt19937 gen(rd());
	//	std::uniform_int_distribution<> distX(1, 27);
	//	std::uniform_int_distribution<> distY(1, 20);
	//	int tabB[N][2];
	//	fp = fopen("mapa1.txt", "w+b");
	//	for (int k = 0; k <= N; k++) {
	//		int j = distX(gen);
	//		int i = distY(gen);
	//		tabB[k][1] = (j * 30);
	//		tabB[k][2] = (i * 30);
	//		std::cout << tabB[k][1] << "," << tabB[k][2] << std::endl;
	//		fwrite(&tabB[k][1], sizeof(tabB[0][0]), 1, fp);
	//		fwrite(&tabB[k][2], sizeof(tabB[0][0]), 1, fp);
	//	}
	//}
	void ObjSrd::draw(sf::RenderWindow& window, int matOto) {
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
			if (LiczbaEle == O) {
				window.draw(mapaGry[0][i]);
			}
			if (LiczbaEle == P) {
				window.draw(mapaGry[1][i]);
			}
			if (LiczbaEle == R) {
				window.draw(mapaGry[2][i]);
			}
			if (LiczbaEle == S) {
				window.draw(mapaGry[3][i]);
			}
		}
	}