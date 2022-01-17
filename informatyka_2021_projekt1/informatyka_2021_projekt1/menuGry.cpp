//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <string>
//#include <random>
//#include <math.h>
//#include <vector>
////#include "silnik.cpp"
//#pragma warning(disable:4996)
//
//#define MAX_LICZBA_POZIOMOW 4
//#define LICZBA_POZ 3
//#define LICZBA_WYB_ATR 4
//#define LICZBA_CZOLGOW 3
//
//void Opoznienie(int opoznienie)
//{
//	sf::Clock zegar;
//	sf::Time czas;
//	while (1)
//	{
//		czas = zegar.getElapsedTime();
//		if (czas.asMilliseconds() > opoznienie)
//		{
//			zegar.restart();
//			break;
//		}
//
//	}
//}
//class Menu
//{
//
//private:
//	sf::Font font;
//	sf::Text header[MAX_LICZBA_POZIOMOW];
//	sf::Text menu[MAX_LICZBA_POZIOMOW];//maksymalna liczba poziomow
//	sf::Text menu1[LICZBA_WYB_ATR];//Menu dla wyboru atrybutów playera
//	int wyborCzolgu[LICZBA_CZOLGOW];//Dom wyboru czog³gu
//	sf::Text opisTank[LICZBA_CZOLGOW];
//	sf::Text wyborPoz[LICZBA_POZ];
//	sf::Text nazwaGracza;//do przechowywania nazwy gracza
//	int poziomMenu;
//	int selectedItem = 0;
//	int selectedItem2 = 0;
//	int selectCzolg = 0;
//	int selectPoziom = 0;
//	int itm = 0;
//	sf::Sprite Tank[LICZBA_CZOLGOW];
//	sf::Texture Tank1txt;
//	sf::Texture Tank2txt;
//	sf::Texture Tank3txt;
//
//
//public:
//	Menu(float width, float height);
//	~Menu() {};
//	void przesunG();//przesun do gory
//	void przesunD();//przesun w dol
//	void przesunGora();
//	void przesunDol();
//	int getSelectedItem(int);//zwroc poziom menu
//	void draw(sf::RenderWindow& window, int);//rysuj menu w oknie
//	void podajNazweGracza(sf::Event, sf::RenderWindow&);
//	//void wybierzLP(char);
//	void setPoziomMenu(int n);
//	void kontynujGre();
//	void zwrotSetPly(int* Poziom, int* Czolg, std::string* NazwaPly);
//	int przesunMenu(sf::Event event, sf::RenderWindow& window, sf::Text tabWyb[], int rozTab, int kierunek);
//	sf::Text* zwrocTab(int id);
//
//};
//
//
//Menu::Menu(float width, float height)
//{	//laduj czcionke
//	if (!font.loadFromFile("CSStamps.ttf"))
//	{
//		return;
//	}
//	//
//
//	//rysowanie elementow menu
//	header[0].setFont(font);
//	header[0].setString("TANK 2021");
//	header[0].setFillColor(sf::Color::White);
//	header[0].setPosition(sf::Vector2f(250, 10));
//	header[0].setCharacterSize(60);
//
//	header[1].setFont(font);
//	header[1].setString("nowa gra:");
//	header[1].setFillColor(sf::Color::White);
//	header[1].setPosition(sf::Vector2f(250, 10));
//	header[1].setCharacterSize(60);
//
//	header[2].setFont(font);
//	header[2].setString("kontynuj gre:");
//	header[2].setFillColor(sf::Color::White);
//	header[2].setPosition(sf::Vector2f(250, 10));
//	header[2].setCharacterSize(60);
//
//	header[3].setFont(font);
//	header[3].setString("tablica wynikow:");
//	header[3].setFillColor(sf::Color::White);
//	header[3].setPosition(sf::Vector2f(250, 10));
//	header[3].setCharacterSize(60);
//
//	menu[0].setFont(font);
//	menu[0].setFillColor(sf::Color::Red);
//	menu[0].setString("NOWA GRA");
//	menu[0].setPosition(sf::Vector2f(50, 100));
//	menu[1].setFont(font);
//	menu[1].setFillColor(sf::Color::White);
//	menu[1].setString("KONTYNUUJ GRE");
//	menu[1].setPosition(sf::Vector2f(50, 150));
//	menu[2].setFont(font);
//	menu[2].setFillColor(sf::Color::White);
//	menu[2].setString("OSTATNIE WYNIKI");
//	menu[2].setPosition(sf::Vector2f(50, 200));
//	menu[3].setFont(font);
//	menu[3].setFillColor(sf::Color::White);
//	menu[3].setString("WYJSCIE");
//	menu[3].setPosition(sf::Vector2f(50, 250));
//
//	//Wyœwietlanie menu wyboru czo³gu
//	Tank1txt.loadFromFile("teksturaPlayer1.png");
//	Tank[0].setTexture(Tank1txt);
//	Tank[0].setPosition(200, 265);
//	Tank[0].setOrigin(25, 25);
//	Tank[0].setScale(2, 2);
//	Tank[0].setColor(sf::Color(255, 255, 255, 128));//Przezroczysty
//
//	Tank2txt.loadFromFile("teksturaPlayer2.png");
//	Tank[1].setTexture(Tank2txt);
//	Tank[1].setPosition(400, 265);
//	Tank[1].setOrigin(25, 25);
//	Tank[1].setScale(2, 2);
//	Tank[1].setColor(sf::Color(255, 255, 255, 128));
//
//	Tank3txt.loadFromFile("teksturaPlayer3.png");
//	Tank[2].setTexture(Tank3txt);
//	Tank[2].setPosition(600, 265);
//	Tank[2].setOrigin(25, 25);
//	Tank[2].setScale(2, 2);
//	Tank[2].setColor(sf::Color(255, 255, 255, 128));
//	//opisy
//	opisTank[0].setFont(font);
//	opisTank[0].setString("R4 'MAUSE'\nPancerz **\nUzbrojenie ***\nSzybkosc *****");
//	opisTank[0].setFillColor(sf::Color::White);
//	opisTank[0].setPosition(sf::Vector2f(150, 320));
//	opisTank[0].setCharacterSize(18);
//
//	opisTank[1].setFont(font);
//	opisTank[1].setString("R8 'OTIS'\nPancerz ***\nUzbrojenie ***\nSzybkosc ***");
//	opisTank[1].setFillColor(sf::Color::White);
//	opisTank[1].setPosition(sf::Vector2f(350, 320));
//	opisTank[1].setCharacterSize(18);
//
//	opisTank[2].setFont(font);
//	opisTank[2].setString("R12 'BIG-RAT'\nPancerz *****\nUzbrojenie ***\nSzybkosc **");
//	opisTank[2].setFillColor(sf::Color::White);
//	opisTank[2].setPosition(sf::Vector2f(550, 320));
//	opisTank[2].setCharacterSize(18);
//
//	//WYBÓR POZIOMU 
//	wyborPoz[0].setFont(font);
//	wyborPoz[0].setFillColor(sf::Color::White);
//	wyborPoz[0].setString("POZIOM 1");
//	wyborPoz[0].setPosition(sf::Vector2f(50, 450));
//
//	wyborPoz[1].setFont(font);
//	wyborPoz[1].setFillColor(sf::Color::White);
//	wyborPoz[1].setString("POZIOM 2");
//	wyborPoz[1].setPosition(sf::Vector2f(250, 450));
//
//	wyborPoz[2].setFont(font);
//	wyborPoz[2].setFillColor(sf::Color::White);
//	wyborPoz[2].setString("POZIOM 3");
//	wyborPoz[2].setPosition(sf::Vector2f(450, 450));
//
//	//POZIOM PIERWSZY MENU
//	menu1[0].setFont(font);
//	menu1[0].setFillColor(sf::Color::Red);
//	menu1[0].setString("PODAJ NAZWE GRACZA:");
//	menu1[0].setPosition(sf::Vector2f(50, 100));
//	menu1[1].setFont(font);
//	menu1[1].setFillColor(sf::Color::White);
//	menu1[1].setString("WYBIERZ CZO£G:");
//	menu1[1].setPosition(sf::Vector2f(50, 150));
//	menu1[2].setFont(font);
//	menu1[2].setFillColor(sf::Color::White);
//	menu1[2].setString("POZIOM ROZGRYWKI:");
//	menu1[2].setPosition(sf::Vector2f(50, 400));
//	menu1[3].setFont(font);
//	menu1[3].setFillColor(sf::Color::White);
//	menu1[3].setString("<ROZPOCZNIJ GRE>");
//	menu1[3].setPosition(sf::Vector2f(50, 500));
//
//	//MENU KONTYNUJ Gre
//
//
//
//}
////rysowanie menu w biezacym oknie
//void Menu::draw(sf::RenderWindow& window, int poziomMenu)
//{
//
//	if (poziomMenu == 0) {
//		window.draw(header[0]);
//		for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
//		{
//			window.draw(menu[i]);
//		}
//	}
//	else if (poziomMenu == 1) {
//		window.draw(header[1]);
//		window.draw(nazwaGracza);
//		for (int i = 0; i < LICZBA_CZOLGOW; i++) {
//			window.draw(Tank[i]);
//			if (selectCzolg == 0)
//				window.draw(opisTank[0]);
//			if (selectCzolg == 1)
//				window.draw(opisTank[1]);
//			if (selectCzolg == 2)
//				window.draw(opisTank[2]);
//		}
//		for (int i = 0; i < LICZBA_POZ; i++)
//			window.draw(wyborPoz[i]);
//		for (int i = 0; i < LICZBA_WYB_ATR; i++)
//			window.draw(menu1[i]);
//	}
//	else if (poziomMenu == 2) {
//		window.draw(header[2]);
//	}
//	else if (poziomMenu == 3) {
//		window.draw(header[3]);
//	}
//}
//void Menu::kontynujGre() {
//
//}
//
//void Menu::podajNazweGracza(sf::Event event, sf::RenderWindow& window) {
//	sf::Text nazwaGraczaTemp;
//	if (itm == 0) {
//		bool flaga = false;
//		//std::cout << "PODAJ NAZWE" << std::endl;
//		if (event.type == sf::Event::TextEntered && selectedItem2 == 0)
//			if (std::isprint(static_cast <wchar_t>(event.text.unicode), std::locale())) {
//				nazwaGraczaTemp.setString(nazwaGracza.getString());
//				nazwaGracza.setString(nazwaGracza.getString() + event.text.unicode);
//				flaga = true;
//			}
//		nazwaGracza.setFont(font);
//		nazwaGracza.setFillColor(sf::Color::Green);
//		nazwaGracza.setPosition(sf::Vector2f(300, 100));
//		//window.draw(nazwaGracza);
//		Opoznienie(100);
//	}
//}
//int Menu::getSelectedItem(int i) {
//	if (i == 0)
//		return selectedItem;
//	if (i == 1)
//		//return selectedItem2;
//		return itm+1;
//	if (i == 2)
//		return selectedItem2;
//
//}
//void Menu::setPoziomMenu(int n) {
//	poziomMenu = n;
//}
//
//int Menu::przesunMenu(sf::Event event,sf::RenderWindow& window, sf::Text tabWyb[], int rozTab, int kierunek) {
//	while (window.pollEvent(event)) {//kierunek = 1 -> gora/dol
//		if (event.type == sf::Event::KeyPressed) {
//			//Opoznienie(100);
//			if (event.key.code == sf::Keyboard::Down) {
//				//std::cout << "PRZESUNIECIE MENU:" << kierunek <<"wybrana: "<< itm<< std::endl;
//				if (itm >= 0 && itm < rozTab)
//					tabWyb[itm].setFillColor(sf::Color::White);
//				tabWyb[itm].setStyle(sf::Text::Regular);
//				itm++;
//				if (itm >= rozTab)
//					itm = 0;
//				tabWyb[itm].setFillColor(sf::Color::Red);
//				tabWyb[itm].setStyle(sf::Text::Bold);
//			}
//			else if (event.key.code == sf::Keyboard::Up) {
//				if (itm >= 0 && itm < rozTab)
//					tabWyb[itm].setFillColor(sf::Color::White);
//				tabWyb[itm].setStyle(sf::Text::Regular);
//				itm--;
//				if (itm < 0)
//					itm = rozTab - 1;
//				tabWyb[itm].setFillColor(sf::Color::Red);
//				tabWyb[itm].setStyle(sf::Text::Bold);
//			}
//			else if (itm == 1) {
//			 if (event.key.code == sf::Keyboard::Left) {
//				Tank[selectCzolg].setColor(sf::Color(255, 255, 255, 128));
//				Tank[selectCzolg].setScale(2, 2);
//				--selectCzolg;
//				if (selectCzolg < 0)
//					selectCzolg = LICZBA_CZOLGOW - 1;
//				Tank[selectCzolg].setColor(sf::Color(255, 255, 255, 255));
//				Tank[selectCzolg].setScale(2.5, 2.5);
//
//			}
//			else if (event.key.code == sf::Keyboard::Right) {
//				Tank[selectCzolg].setColor(sf::Color(255, 255, 255, 128));
//				Tank[selectCzolg].setScale(2, 2);
//				++selectCzolg;
//				if (selectCzolg >= LICZBA_CZOLGOW)
//					selectCzolg = 0;
//				Tank[selectCzolg].setColor(sf::Color(255, 255, 255, 255));
//				Tank[selectCzolg].setScale(2.5, 2.5);
//			}
//			}
//			else if (itm == 2) {
//				if (event.key.code == sf::Keyboard::Left) {
//					//wyborPoz[LICZBA_POZ]
//					wyborPoz[selectPoziom].setFillColor(sf::Color::White);
//					wyborPoz[selectPoziom].setStyle(sf::Text::Regular);
//					--selectPoziom;
//					if (selectPoziom < 0)
//						selectPoziom = LICZBA_POZ - 1;
//					wyborPoz[selectPoziom].setFillColor(sf::Color::Green);
//					wyborPoz[selectPoziom].setStyle(sf::Text::Bold);
//
//				}
//				else if (event.key.code == sf::Keyboard::Right) {
//					wyborPoz[selectPoziom].setFillColor(sf::Color::White);
//					wyborPoz[selectPoziom].setStyle(sf::Text::Regular);
//					++selectPoziom;
//					if (selectPoziom >= LICZBA_POZ)
//						selectPoziom = 0;
//					wyborPoz[selectPoziom].setFillColor(sf::Color::Green);
//					wyborPoz[selectPoziom].setStyle(sf::Text::Bold);
//				}
//			}
//			else if (event.key.code == sf::Keyboard::Enter) {//zwrocenie wybranego elementu poprzez Enter
//				std::cout << "Select tank: " << selectCzolg << "Select poziom: " << selectPoziom << std::endl;
//				return (itm + 1);
//			}
//		}
//	}
//}
//void Menu::zwrotSetPly(int* Poziom, int* Czolg, std::string* NazwaPly) {
//	*Poziom = selectPoziom+1;
//	*Czolg = selectCzolg+1;
//	*NazwaPly = std::string(nazwaGracza.getString());
//
//}
//sf::Text* Menu::zwrocTab(int id) {
//	if (id == 1)
//		return menu;
//	if(id == 2)
//		return menu1;
//	if (id == 3)
//		return opisTank;
//
//}
//
//int main()
//{
//	int menu_selected_flag = 0;
//	int menu1_select = 0;
//	int poziomGry=0;
//	int wybranyCzolg=0;
//	bool startGry=false;
//	sf::Text nazwaGracza;
//	std::string nazwaPly;
//	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML demo");// utworz okno
//	Menu menu(window.getSize().x, window.getSize().y);
//	while (window.isOpen())
//	{
//		//std::cout << "Menu_select"<< menu_selected_flag <<"Menu_select_(1)"<< menu.getSelectedItem(1) <<"Select itheam:" << menu.getSelectedItem(2)<< std::endl;
//		sf::Event event;
//		window.clear();
//		if (menu_selected_flag == 0) {
//			menu_selected_flag = menu.przesunMenu(event, window, menu.zwrocTab(1), MAX_LICZBA_POZIOMOW, 1);
//			menu.draw(window, 0);
//		}
//		if (menu_selected_flag == 1) {
//			menu1_select = menu.przesunMenu(event, window, menu.zwrocTab(2), LICZBA_WYB_ATR, 1);
//			menu.podajNazweGracza(event, window);
//			menu.draw(window, 1);
//			if (menu1_select == 4) {
//				menu.zwrotSetPly(&poziomGry, &wybranyCzolg, &nazwaPly);
//				std::cout << "nowa gre: Poziom:" <<poziomGry<< " Wybrany czolg: " << wybranyCzolg <<" Nazwa gracza: " << nazwaPly << std::endl;
//				startGry = true;
//			}
//				
//		}
//		if (menu_selected_flag == 2) {
//			menu.draw(window, 2);
//			std::cout << "kontynuj gre" << std::endl;
//		}
//		//akcja dla kontynuuacji gry
//		if (menu_selected_flag == 3) {
//			menu.draw(window, 3);
//		}
//		//akcja dla tablicy wyników
//		if (menu_selected_flag == 4)
//			window.close();
//
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//				
//			
//			if (event.type == sf::Event::KeyPressed)
//			{
//				
//				if (event.key.code == sf::Keyboard::Escape)
//				{
//					window.clear();
//					menu.setPoziomMenu(0);
//					std::cout << "Cofnij\n";
//					menu_selected_flag = 0;
//				}
//			}
//
//
//		}
//		//START GRY:
//		if (startGry == true) {
//			std::cout << "Gra dzia³aa\n";
//
//
//		}
//
//		
//		window.display();
//	}
//
//	return 0;
//}