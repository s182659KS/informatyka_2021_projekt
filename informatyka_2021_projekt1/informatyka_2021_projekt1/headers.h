#pragma once
#ifndef headers_h
#define headers_h

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#define MAX_LICZBA_POZIOMOW 4
#define LICZBA_POZ 3
#define LICZBA_WYB_ATR 4
#define LICZBA_CZOLGOW 3

typedef struct {
	std::string nick;
	int punkty;

}wynikiGry;

typedef struct {
	unsigned int indeks;//indeks sprite
	std::string nick;
	int wybCzolg;
	int xGracz;
	int yGracz;
	int punkty;
	int pociski;
	int pancerz;
	float speed;
	int iloscEnemy;

}stanGry;

void zapisGry(stanGry graczSave, int id_save, int getTank, float graczPozx, float graczPozy, std::string nick_save, int pkt_save, int pck_save, int pan_save, float spd_save, int ilEne_save);
void odczytGry(stanGry graczSave, int id_save, int* setTank, float* graczPozx, float* graczPozy, std::string* nick_save, int* pkt_save, int* pck_save, int* pan_save, float* spd_save, int* ilEne_save);
void Opoznienie(int opoznienie);
class Interfejs{
private:
	sf::Font font;
	sf::Text koniecGryW;
	sf::Text koniecGryP;
	sf::RectangleShape menuAkcji;
	sf::Vector2f rozOknaMenu;
	sf::Text help[3];
	sf::Text menuEsc[3];
	int itm;//iterator dla wyboru
//interfejs wyswietlany w trakcie gry
	sf::Text parametrGracz[3];
public:
	Interfejs(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window, sf::Event& event, int opcja);
	int wybor(sf::Event event, sf::RenderWindow& window);
	void getStanPly(sf::RenderWindow& window, int punkty, int pociski, int pancerz);
	int zwrotWybor();

};
class Player {//klasa dla gracza
private:
	sf::Texture plrtxt;//tekstura dla gracza
	sf::Sprite plrtank;//duszek dla gracza
	sf::Sprite* pocisk;//duszek dla pocisku
	sf::Texture pocisktxt;//tekstura dla pocisku
	sf::Vector2f* kierPoc;
	//parametry dla gracza
	float pancerz;
	int punkty;
	int pociski;
	sf::Vector2f pozycja;//wspolrzedne gracza
	float speed;//predkoœæ bota
	//dla pocisków:
	int iloscPociskow;
	int reload;
	bool flagaStrzal;
	int czasPrzel;
	//dla wygranej lub pora¿ki
	bool wygrana;
public:
	bool flaga_wygranej;
	Player();
	Player(int punktySet, int pociskiSet, float pancerzSet, float speedSet, int setCzolg);
	void draw(sf::RenderWindow& window);
	float ruch(sf::RenderWindow& window, float speedPly, bool pauza);
	sf::Sprite strzal(sf::RenderWindow& window);
	bool przelPoc(int czasPrzel);
	void trafieniePocisk(sf::Sprite ply, sf::Sprite* pociski, sf::Sprite* obiektOto, int SizeTab);
	void zderzenieObj(sf::Sprite* obiektOto, int rozmiarTab);
	float brodzenie(sf::Sprite* Woda, int iloscObj);
	bool Win(sf::Sprite orzel);
	int zwrocStanPly(int id);
	int* zwrocPanc();
	int* zwrocPunkty();
	void setTxtCzolg(int setCzolg);
	sf::Vector2f zwrocPoz();
	sf::Sprite* zwrocPocisk();
	sf::Sprite* zwrocPPocisk();
	sf::Sprite zwrocSprite();
	sf::Sprite* zwrocPSprite();
	void setPoz(int x, int y);
	int ruchPoc;
};
class Menu
{

private:
	sf::Font font;
	sf::Text header[MAX_LICZBA_POZIOMOW];
	sf::Text menu[MAX_LICZBA_POZIOMOW];//maksymalna liczba poziomow
	sf::Text menu1[LICZBA_WYB_ATR];//Menu dla wyboru atrybutów playera
	int wyborCzolgu[LICZBA_CZOLGOW];//Dom wyboru czog³gu
	sf::Text opisTank[LICZBA_CZOLGOW];
	sf::Text wyborPoz[LICZBA_POZ];
	sf::Text nazwaGracza;//do przechowywania nazwy gracza
	//dla listy wyników
	sf::Text* players;//dane tekstowe do wyswietlenia
	wynikiGry* player_char;//wyniki graczy
	int Np;
	//
	int poziomMenu;
	int selectedItem = 0;
	int selectedItem2 = 0;
	int selectCzolg = 0;
	int selectPoziom = 0;
	int itm = 0;
	sf::Sprite Tank[LICZBA_CZOLGOW];
	sf::Texture Tank1txt;
	sf::Texture Tank2txt;
	sf::Texture Tank3txt;



public:
	Menu(float width, float height);
	~Menu() {};
	int getSelectedItem(int);//zwroc poziom menu
	void draw(sf::RenderWindow& window, int);//rysuj menu w oknie
	void podajNazweGracza(sf::Event, sf::RenderWindow&);
	void setPoziomMenu(int n);
	void zwrotSetPly(int* Poziom, int* Czolg, std::string* NazwaPly);
	int przesunMenu(sf::Event event, sf::RenderWindow& window, sf::Text tabWyb[], int rozTab, int kierunek);
	sf::Text* zwrocTab(int id);
	void tablicaWynikZapis(int punkty, std::string nazwaGracz);
	void sortujListe();
	void tablicaWynikOdczyt(int N);
	void ladujListeWyn();
	void drawLista(sf::RenderWindow& window);

};
//Dla wroga 
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
	float speed;
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
	int ruchBot, rotBot;//iloœæ kroków do przodu oraz k¹t obrotu
	int n;
public:
	bool flaga_wygranej;
	Enemy();
	void ruch_bot(sf::RenderWindow& window);
	void strzalBot(sf::Sprite ply, sf::RenderWindow& window, sf::Sprite orzel);
	void trafieniePocisk(sf::Sprite ply, char typ, sf::Sprite* pociski, sf::Sprite* obiektOto, int SizeTab, int* pancerzP);
	bool trafiPoc(sf::Sprite* pocisk, int id, int* punkty);
	void zderzeniaBot();
	void draw(sf::RenderWindow& window);
	sf::Sprite* zwroctabSprite();
	sf::Sprite zwrocSprite(int id);
	sf::Sprite* zwrocPoc();
	void zderzenieObj(sf::Sprite* mapaGry, int rozmiarTab);
	bool WinEne(sf::Sprite orzel);
};	

//Obiekty Otoczena
class ObjSrd {//elementy otoczenia
	sf::Sprite orzel[2];
	sf::Sprite** mapaGry;//dynamiczna dwuwymiarowa
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
	int O = 0, P = 0, R = 0, S = 0;//zmienne rozmiarów tablic dynamicznych
public:
	ObjSrd(int N);
	sf::Vector2f kierKol(sf::Sprite plr_poz);
	sf::Sprite zwrocOrla(int id);
	sf::Sprite* ZwrocMapeGry(int mat);
	int zwrocRozTab(int mat);
	void trafiPoc(sf::Sprite* pocisk);
	void draw(sf::RenderWindow& window, int matOto);
};
#endif