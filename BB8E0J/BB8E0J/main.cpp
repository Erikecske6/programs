//BB8E0J _ Grozev Erik Plamenov

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <ctime>

//#define fileName "adatok.csv"


using namespace std;

class felhasznalo {
	string email;
	string felhasznalonev;
	string jelszo;

public:
	felhasznalo() { email = "en@gmail.com"; felhasznalonev = "erikecske"; jelszo = "666"; }
	felhasznalo(string email, string felhasznalonev, string jelszo){ 
		this->email = email;
		this->felhasznalonev = felhasznalonev;
		this->jelszo = jelszo;
	}

	string getEmail() { return email; }
	string setEmail(string email) { this->email = email; }

	string getFelhasz() { return felhasznalonev; }
	string setFelhasz(string felhasznalonev) { this->felhasznalonev = felhasznalonev; }

	string getJelszo() { return jelszo; }
	string setJelszo(string jelszo) { this->jelszo = jelszo; }
};

class nevek {
	static int szam;
	felhasznalo** nev;
	static int maxszam;

public:
	nevek() { nev = new felhasznalo * [szam];}

	static int getSzam() { return szam; }
	static int getMax() { return maxszam; }

	void regisztracio() {
		string felhasznalonev; string email; string jelszo;
		cout << "Adj felhasznalonevet: "; cin >> felhasznalonev; cout << endl;
		int a = 0;
		for (int i = 0; i < szam; i++) {
			if (nev[i]->getFelhasz() == felhasznalonev) {
				cout << "Ez a felhasznalonev mar foglalt" << endl;
				a = 1;
			}
		}
		if (a != 1) {
			int helyese = 0;
			cout << "Adj emailt:"; cin >> email; cout << endl;
			for (int i = 0; i < szam; i++) {
				//előtte megnézni, hogy jo-e a formatum ??
				//strchr(nev[i]->getEmail(), '@');

				if (nev[i]->getEmail() == email) {
					cout << "Ez az e-mail mar foglalt" << endl;
				}
				
				cout << "Adj jelszot:"; cin >> jelszo; cout << endl;
				nev[szam] = new felhasznalo(email, felhasznalonev, jelszo);

				szam++;
			}
		}
	}

	void belepes() {
		string email; string jelszo;
		cout << "Adj emailt:"; cin >> email; cout << endl;
		cout << "Adj jelszot:"; cin >> jelszo; cout << endl;
		int joe = 0;

		for (int i = 0; i < szam; i++) {
			if (nev[i]->getEmail() == email && nev[i]->getJelszo() == jelszo) {
				joe = 1;
			}
		}
		if (joe == 1) cout << "Sikeres bejelentkezes." << endl;
		else cout << "Ez a felhasznalonev es jelszoparositas helytelen." << endl;
	}

	void admin() {
		for (int i = 0; i < szam; i++) {
			string jelszo;
			//string email;
			
			jelszo = sizeof(nev[i]->getJelszo())*'*';

			//email vége csillagozva kene
			cout << nev[i]->getFelhasz() << ' ' << nev[i]->getEmail() /*email*/ << ' ' << jelszo << endl;
		}

	}

	~nevek() {
		for (int i = 0; i < szam; i++) delete nev[i];
		delete nev;
	}
};

int nevek::szam = 0;
int nevek::maxszam = 3;

int  main() {
	
	nevek uj;

	cout << "Valassz opciot: " << endl;
	char c = 'h';
	
	

	while (c != 'q') {
		cin >> c;
		switch (c) {
		case 'r': {
			if (uj.getSzam() == uj.getMax()) {
				cout << "Regisztracio atmenetileg nem lehetseges." << endl;
			}
			else {
				uj.regisztracio();
			}
			break;
		}
		case 'b': {
			uj.belepes();
			break;
		}
		case 'a': {
			uj.admin();
			break;
		}
		default: cout << "Nincs ilyen muvelet" << endl;
		}
	}

	return 0;
}