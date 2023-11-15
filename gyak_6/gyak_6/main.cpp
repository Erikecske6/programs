#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <ctime>

#define fileName "adatok.csv"

using namespace std;


class meroberendezes {
	string id;
	float homerseklet;
	int paratartalom;
	static int szam;
	string idGen() {
		stringstream streamID;
		for (int i = 0; i < 5; i++)
			streamID << rand() % 10; //15678
		//string +=
		//int szam = szam*10+rand()%10
		string id;
		streamID >> id;
		return id;
	}

public:
	meroberendezes(): homerseklet(10), paratartalom(10) {}

	meroberendezes(int id, float homerseklet, int paratartalom, int szam) {
		this->id = id;
		this->homerseklet = homerseklet;
		this->paratartalom = paratartalom;
		this->szam = szam;
	};
	string getId() {
		return id;
	};
	void setId(string id) {
		this->id = id;
	}
	float getHom() {
		return homerseklet;
	}
	void setHome(float homerseklet) {
		this->homerseklet = homerseklet;
	}
	int getPar() {
		return paratartalom;
	}
	int setPar(int paratartalom) {
		this->paratartalom = paratartalom;
	}
	static int getSzam() {
		return szam;
	}
	static void setSzam() {
		szam++;
	}

	void meres() {
		paratartalom = rand() % (50 - 30 + 1) + 30;  //50 és 30 között
		homerseklet = (float)(rand() % (250 - 200 + 1) + 200) / 10.0;  //20-25 között 0.1 pontosan generál
	}

	~meroberendezes() {
		szam--;
	}
};

class kozpont {
	fstream file;
	int kapacitas;
	meroberendezes** eszkoz;   //** al jobb, FONTOS class típusú tom**-al

public:
	kozpont(int kapacitas) {
		this->kapacitas = kapacitas;
		eszkoz = new meroberendezes * [kapacitas];
	}
	void Print() {
		cout << meroberendezes::getSzam() << endl;
	}

	void hozzaadas() {
		if(meroberendezes::getSzam() >= kapacitas){
			cout << "A kozpont betelt! :(" << endl;
			return;
		}
		eszkoz[meroberendezes::getSzam()] = new meroberendezes();
		meroberendezes::setSzam();
	}

	void listazas() {
		file.open(fileName, ios::out);
		if (!file.is_open())
		{
			cout << "Nem sikerult megnyitni a " << fileName << " nevu fajlt." << endl;
			return;
		}
		
		for (int i = 0; i < meroberendezes::getSzam(); i++) {
			eszkoz[i]->meres();
			file << "Id: #" << eszkoz[i]->getId() << endl;
			file << "Homerseklet: " << eszkoz[i]->getHom() << endl;
			file << "Paratartalom: " << eszkoz[i]->getPar() << endl;
		}
		
		/*for (int i = 0; i < meroberendezes::getSzam(); i++) {
			for (int j = 0; j < 10; j++)
				file << meroberendezes::getId() << " ; " << meroberendezes::getHom() << " ; "
				<< meroberendezes::getPar() << endl;
			file.seekp(-1, ios::cur);
			file << endl;
		}*/
		file.close();
	}

	~kozpont() {
		for (int i = 0; i < meroberendezes::getSzam(); i++)
			delete eszkoz[i];
		delete eszkoz;
	}
};

int meroberendezes::szam = 0;


int main() {
	
	srand(time(nullptr));
	kozpont k(20);
	meroberendezes blabla();
	k.Print();
	cout << "Valasszon opciot: " << endl;
	char c = 'h';

	while (c != 'q'){
		cin >> c;
		switch (c) {
		case 'h':{
			cout << "Hozzaadas" << endl;
			k.hozzaadas();
			break;
		}
		case 'm': {
			cout << "Listazza az eredmenyeket " << endl;
			k.listazas();
			break;
		}
		case 'q':
			break;
		default:
			cout << "Nincs ilyen opcio" << endl;
		}
	}


	return 0;
}