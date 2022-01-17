
/*
Temat projektu: Gra akcji Tank2021 (replika gry Tank1990)
Zakres projektu:Gra jednoosobowa polegaj¹ca na zniszczeniu bazy wroga znajduj¹cej siê po drugiej stronie planszy
równoczeœnie broni¹c swojej przed czo³gami wroga (boty sterowane algorytmem), na planszy znajduj¹ siê ró¿nego rodzaju
przeszkody, z ró¿nych materia³ów. Gracz mo¿e sterowaæ czo³giem za pomocom strza³ek i strzelaæ (klawisz W). Traci punkt pancerza
za ka¿dym trafieniem przez przeciwnika. Punkty zdobywamy poprzez liczbe zniszczonych przeciwników i czas rozrywki.
Gra bêdzie mia³a kilka poziomów, ró¿ni¹cych siê poziomem trudnoœci rozgrywki.
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <math.h>
#include <vector>
#include "headers.h"





void tablicaWynikow() {


}
void zapisGry(stanGry graczSave,int id_save, int getTank, float graczPozx, float graczPozy, std::string nick_save, int pkt_save, int pck_save, int pan_save, float spd_save, int ilEne_save)
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
		//if(id_save==1)
		//fp = fopen("saveGame1.dat", "wb");
		//if (id_save == 2)
		//	fp = fopen("saveGame2.dat", "wb");
		//if (id_save == 3)
		//	fp = fopen("saveGame3.dat", "wb");
		fwrite(&graczSave, sizeof(stanGry), 1, fp);
		fclose(fp);
	
}
		

void odczytGry(stanGry graczSave, int id_save,int* setTank, float* graczPozx, float* graczPozy,std::string* nick_save, int* pkt_save, int* pck_save, int* pan_save, float* spd_save, int* ilEne_save)
{
	FILE* fp;
	std::cout << "Odczyt!\n";
	//read_flag = 1;
	fp = fopen("saveGame1.dat", "rb");
	/*if (id_save == 1)
		fp = fopen("saveGame1.dat", "rb");
	if (id_save == 2)
		fp = fopen("saveGame2.dat", "rb");
	if (id_save == 3)
		fp = fopen("saveGame3.dat", "rb");*/
	fread(&graczSave, sizeof(stanGry), 1, fp);
	fclose(fp); 

	//->setPosition(graczSave.xGracz, graczSave.yGracz);
	//*gracz =sf::Vector2f(graczSave.xGracz, graczSave.yGracz);
	*graczPozx = graczSave.xGracz;
	*graczPozx = graczSave.yGracz;
	*nick_save = graczSave.nick;
	*pkt_save = graczSave.punkty;
	*pck_save = graczSave.pociski;
	*pan_save = graczSave.pancerz;
	*spd_save = graczSave.speed;
	*ilEne_save = graczSave.iloscEnemy;

}

int main()
{

	//ZMIENNNE MENU
	int menu_selected_flag = 0;
	int menu1_select = 0;
	int poziomGry = 0;
	int wybranyCzolg = 0;
	bool startGry = false;
	bool flagaKonstruktora = false;
	sf::RenderWindow window(sf::VideoMode(800, 600), "TANK 2021");
	sf::Vector2u size = window.getSize();
	sf::Text nazwaGracza;
	std::string nazwaPly;
	Menu menu(window.getSize().x, window.getSize().y);
	//DO zApisu
	int iloscSave=3;
	stanGry *gracz_save = new stanGry[iloscSave];
	//ZMIENNE ROZGRYWKI
	int E = 3;//LICZBA WROGOW
	bool wygrana;
	bool przegrana=false;

	bool pauza;
	int flagaMenuGry;
	unsigned int width = size.x;
	unsigned int hight = size.y;
	//wartoœci startowe
	int punktySet;
	float speedSet;
	int pociskiSet;
	int pancerzSet;
	Interfejs if1(window);


	while (window.isOpen()&& startGry == false)
	{
		sf::Event event;
		//Pêtla menu
			window.clear();
			if (menu_selected_flag == 0) {
				menu_selected_flag = menu.przesunMenu(event, window, menu.zwrocTab(1), MAX_LICZBA_POZIOMOW, 1);
				menu.draw(window, 0);
			}
			//std::cout << "menu select flag" << menu_selected_flag <<std::endl;
			else if (menu_selected_flag == 1) {
				std::cout << "menu select flag " << menu_selected_flag << std::endl;
				menu1_select = menu.przesunMenu(event, window, menu.zwrocTab(2), LICZBA_WYB_ATR, 1);
				menu.podajNazweGracza(event, window);
				menu.draw(window, 1);
				if (menu1_select == 4) {
					menu.zwrotSetPly(&poziomGry, &wybranyCzolg, &nazwaPly);
					std::cout << "nowa gre: Poziom:" << poziomGry << " Wybrany czolg: " << wybranyCzolg << " Nazwa gracza: " << nazwaPly << std::endl;
					//USTAWIENE ROZGRYWKI
					punktySet=0;
					if (poziomGry == 1) {
						pociskiSet=60;
						E = 3;
					}
					else if (poziomGry == 2) {
						pociskiSet=50;
						E = 6;
					}
					else if (poziomGry == 3) {
						pociskiSet=40;
						E = 9;
					}
					if (wybranyCzolg == 1) {
						speedSet = 1.5;
						pancerzSet = 200;
					}
					else if (wybranyCzolg == 2) {
						speedSet = 1;
						pancerzSet = 150;
					}
					else if (wybranyCzolg == 3) {
						speedSet = 0.5;
						pancerzSet = 100;
					}
					startGry = true;
				}

			}
			else if (menu_selected_flag == 2) {
				std::cout << "kontynuj gre" << std::endl;
				menu.draw(window, 2);
				startGry = true;
				
			}
			//akcja dla kontynuuacji gry
			else if (menu_selected_flag == 3) {
				std::cout << "tablica wynikow" << std::endl;
				menu.tablicaWynikOdczyt(3);
				//menu.ladujListeWyn();
				menu.draw(window, 3);
			}
			//akcja dla tablicy wyników
			else if (menu_selected_flag == 4) {
				std::cout << "Wychodze" << std::endl;
				window.close();
			}
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();


				if (event.type == sf::Event::KeyPressed)
				{

					if (event.key.code == sf::Keyboard::Escape)
					{
						window.clear();
						menu.setPoziomMenu(0);
						std::cout << "Cofnij\n";
						menu_selected_flag = 0;
					}
				}
			}
		window.display();
	}
	Player p1(punktySet, pociskiSet, pancerzSet, speedSet, wybranyCzolg);//punkty, pociski, pancerz, prêdkoœæ
	Enemy* e1;
	ObjSrd s1(200);
	e1 = new Enemy[E];
	if (menu_selected_flag == 2) {
		delete[] e1;
		float x=20, y=20;
		odczytGry(gracz_save[0], 1,&wybranyCzolg, &x, &y, &nazwaPly, &punktySet, &pociskiSet, &pancerzSet, &speedSet, &E);
		Player p2(punktySet, pociskiSet, pancerzSet, speedSet, wybranyCzolg);
		std::cout << "ilosc wrogow: " << E << std::endl;
		std::cout << "pociski : " << pociskiSet << std::endl;
		std::cout << "pancerz: " << pancerzSet << std::endl;
		std::cout << "czolg: " << wybranyCzolg << std::endl;
		std::cout << "punkty: " << punktySet << std::endl;
		std::cout << "x: " << x << "y: " <<y<< std::endl;
		p1 = p2;
		e1 = new Enemy[E];
		p1.setTxtCzolg(wybranyCzolg);
		//p1.setPoz(x, y);

	}
	
	pauza = false;
		/////////////////////////////////////////////////PÊTLA GRY////////////////////////////////////////////////////////////////////
	while (window.isOpen()&& startGry == true)
	{
		sf::Event event;
		if (startGry == true) {

			//Tu pêtle 
			if (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.key.code == sf::Keyboard::F1) {
					std::cout << "PAUZA\n";
					pauza = true;
					flagaMenuGry = 1;
					Opoznienie(200);
				}
				if (event.key.code == sf::Keyboard::Escape) {
					pauza = true;
					flagaMenuGry = 2;
				}
				if(event.key.code == sf::Keyboard::Enter&& flagaMenuGry ==1)
				{
					pauza = false;
				}
				if (event.key.code == sf::Keyboard::Enter && flagaMenuGry == 2)
				{
					if(if1.zwrotWybor() ==1)
						pauza = false;
					if (if1.zwrotWybor() == 2)
						zapisGry(gracz_save[0], 1, wybranyCzolg, p1.zwrocPoz().x, p1.zwrocPoz().x, nazwaPly, p1.zwrocStanPly(2), p1.zwrocStanPly(3), p1.zwrocStanPly(1), speedSet, E);
						std::cout << "Zapis" << std::endl;

					if (if1.zwrotWybor() == 3)
						startGry = false;
				}
			}

			window.clear();
			p1.ruch(window, p1.brodzenie(s1.ZwrocMapeGry(2), s1.zwrocRozTab(2)), pauza);
			s1.draw(window, 2);//WODA
			p1.zderzenieObj(s1.ZwrocMapeGry(0), s1.zwrocRozTab(0));
			p1.zderzenieObj(s1.ZwrocMapeGry(1), s1.zwrocRozTab(1));

			for (int k = 0; k < E; k++) {//PÊTLA OBS£UGUJ¥CA PRZECIWNIKÓW
				if (e1[k].trafiPoc(p1.zwrocPocisk(), k, p1.zwrocPunkty()) == false && pauza == false) {//test dla nieruchomego zestrzelonego bota
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
				e1[k].trafieniePocisk(e1[k].zwrocSprite(k), 'W', e1[k].zwrocPoc(), s1.ZwrocMapeGry(0), s1.zwrocRozTab(0), p1.zwrocPanc());
				e1[k].trafieniePocisk(e1[k].zwrocSprite(k), 'W', e1[k].zwrocPoc(), s1.ZwrocMapeGry(1), s1.zwrocRozTab(1), p1.zwrocPanc());
				e1[k].trafieniePocisk(p1.zwrocSprite(), 'G', e1[k].zwrocPoc(), s1.ZwrocMapeGry(1), s1.zwrocRozTab(1), p1.zwrocPanc());//COŒ TU NIE GRA ALE DZiA£A - MA OBS£UGIWAC ZDERZENIE POCISKU Z PLAYEREM
				p1.trafieniePocisk(p1.zwrocSprite(), p1.zwrocPPocisk(), e1[k].zwroctabSprite(), 1);
				//przegrana = e1[k].Win(s1.zwrocOrla(1));
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
			if1.getStanPly(window, p1.zwrocStanPly(2), p1.zwrocStanPly(3), p1.zwrocStanPly(1));
			if (pauza == true) {
				if (flagaMenuGry == 1)
					if1.draw(window, event, 1);
				if (flagaMenuGry == 2) {
					if1.draw(window, event, 2);
					std::cout << "Wybor:" << if1.wybor(event, window) << std::endl;
				}
			}
			wygrana = p1.Win(s1.zwrocOrla(0));

			if (wygrana == true) {
				std::cout << "WYGRANA" << std::endl;
				pauza == true;
				menu.tablicaWynikZapis(p1.zwrocStanPly(2),nazwaPly);


				//if1.draw(window, event, 3);
			}
			else if (przegrana == true) {
				//if1.draw(window, event, 4);
			}
			
		}
		window.display();
	}

	return 0;
}
