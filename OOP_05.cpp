#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <sstream>

using namespace std;

class Statistics {
	fstream file;
	string fileName;
	int* data, maxSize, idx;
	double avg, std;
	template <typename T>
	void Split(T* array, string line, char delimiter = ';')
	{
		stringstream crop;
		int var;
		while (line.find(delimiter) != string::npos)
		{
			crop.clear();
			crop << line.substr(0, line.find(delimiter));
			line = line.substr(line.find(delimiter) + 1);
			if (idx < maxSize)
				crop >> array[idx++];
			else return;
		}
		crop.clear();
		crop << line;
		if (idx < maxSize)
			crop >> array[idx++];
	}
	void Avg()
	{
		avg = 0;
		for (int i = 0; i < idx; i++)
			avg += data[i];
		avg /= (idx + 1);
	}
	void Std()
	{
		std = 0;
		for (int i = 0; i < idx; i++)
			std += pow(data[i] - avg, 2);
		std = sqrt(std / idx);
	}
public:
	Statistics(int maxSize = 100, string fileName = "adatok.csv")
	{
		this->fileName = fileName;
		this->maxSize = maxSize;
		data = new int[maxSize];
		avg = 0.0;
		std = 0.0;
		idx = 0;
	}
	void GenerateDatas()
	{
		file.open(fileName, ios::out);
		if (!file.is_open())
		{
			cout << "Nem sikerult megnyitni a " << fileName << " nevu fajlt." << endl;
			return;
		}
		for (int i = 0; i < maxSize / 10; i++) {
			for (int j = 0; j < 10; j++)
				file << rand() % 1001 << ";";
			file.seekp(-1, ios::cur);
			file << endl;
		}
		for (int i = 0; i < maxSize % 10; i++)
			file << rand() % 1001;
		file.close();
	}
	void ReadDatas()
	{
		file.open(fileName, ios::in);
		if (!file.is_open())
		{
			cout << "Nem sikerult megnyitni a " << fileName << " nevu fajlt." << endl;
			return;
		}
		while (!file.eof())
		{
			string line;
			getline(file, line);
			Split(data, line);
		}
		file.close();
		Avg();
		Std();
	}
	void PrintDatas()
	{
		for (int i = 0; i < idx / 10; i++)
		{
			for (int j = 0; j < 10; j++)
				cout << data[10 * i + j] << ";";
			cout << endl;
		}
		for (int j = 0; j < idx % 10; j++)
			cout << data[(idx / 10) * 10 + j] << ";";
		cout << endl;
	}
	void PrintStat()
	{
		cout << "Atlag: " << avg << endl;
		cout << "Szoras: " << std << endl;
	}

	~Statistics()
	{
		delete[] data;
	}
};

int main()
{
	//========================== FILE++ ===========================
	// 
	// Fájlkezelés sorrendje: (Emlékeztetõ)
	// - Fájl elnevezése (léterhozása)
	// - Fájl megnyitása
	// - Fájl írása/olvasása
	// - Fájl bezárása
	// 
	// Ha nem zárjuk be, az adat a streamben ragad, nem kerül a fájlba!
	// 
	//ofstream, csak kimeneti stream
	//az egyes flageket ezt követõen, õket | jellel elválasztva kell megadni
	//hol találkoztunk ezzel a jelöléssel? Igen! A bitvarázsnál!
	//Akkor még is volt értelme foglalkozni vele! (Lesz is még sok.)

	//Flagek:
	//       ios::in - beolvasás
	//       ios::out - kiírás
	//       ios::binary - bináris fájl beolvasás
	//       ios::ate - a kimeneti kurzor a fájl végén kezdõdik (at end)
	//       ios::app - hozzáfûz (append)
	//       ios::trunc - törli a fájl elõzõ tartalmát (truncate) 
	ofstream kimenet("szoveg.txt", ios::out | ios::trunc);
	if (!kimenet.is_open()) //fájl nyitva? Érdemes mindig ellenõrizni. 
		return -1;
	kimenet << "HELLO WORLD!" << endl; //lehet írni mostanra már megszokott << operátorral
	kimenet << "HELLO MOGI!" << endl;
	kimenet << 42 << endl;
	kimenet.close(); //fájl bezárása

	//Ha csak beolvasni szeretnénk
	ifstream bemenet("szoveg.txt", ios::in);
	string text;
	//bemenet >> text;
	while (bemenet.eof()) //end of file függvény
	{
		getline(bemenet, text);
		cout << text << endl;
	}
	bemenet.close();


	//fstream, enged inputot és outputot is!
	fstream iostream("szoveg.txt", ios::in | ios::out | ios::app);
	//Seekp beállítja, hogy a következõ karaktert milyen pozícióból ÍRJON KI.
	//argumentumai: (abszolút pozíció, a fájl kezdetétõl számolva)
	//				(offset relatívan a "way"-tól (negatív is lehet), "way")
	//         way:
	//				ios::beg - stream eleje
	//              ios::cur - jelen pozíció
	//              ios::end - fájl vége 
	//Seekg egyezik Seekp-vel, csak BEOLVASÁSRA használhatjuk.
	iostream << "HELLO MOGI" << endl;
	iostream << "HeLLO" << endl;
	iostream.seekg(0, ios::beg);
	getline(iostream, text);
	cout << text << endl;
	iostream.close();
	//Append elég érdekesen tud mûködni. Force-olja a kiírást, hogy mindig az utolsó sor utánra
	//kerüljön a kiírandó szöveg. Helyette az input-ouput használatát javaslom.
	//Itt arra kell figyelni, hogy ha a szöveg végére szeretnénk írni, akkor azt be kell állítani.
	//A fájl elejétõl kezd.

	iostream.open("szoveg.txt", ios::in | ios::out); //A default is ez. Ekkor is megmarad az adat!
	iostream << "HELLO MOGI";
	iostream.seekp(0, ios::beg);
	//flush: ahogy azt tapasztaltuk is már elõzõ tárgyból, close nélkül a
	//fájlba nem kerül bele az adat. Ennek az oka, hogy a streamben marad és
	//el lesz tárolva a bufferben. Close írja ki ezt a fájlba.
	//Hogy idõ közben is lehessen kiírni, ezzel biztosítva azt is pl.
	//hogy a read és write buffer megegyezik, hogy flush-olni kell az adatot-
	iostream << "HALLO" << flush; //std::flush segítségével.
	iostream.flush(); //vagy tagfüggvénnyel
	iostream.seekg(0, ios::beg);
	iostream >> text;
	cout << text << endl;
	iostream >> text;
	cout << text << endl;
	iostream.seekp(0, ios::end);
	iostream << "END" << endl;
	iostream.close();

	//Hiba kezelés
	//Vannak különbözõ hiba bitjei a streamnek, amikkel lehet vizsgálni a hibákat
	//fail(): logikai hiba van nagyeséllyel a kódban: pl. csak inputra nyitottuk meg
	//a fájlt, mi pedig akarunk írni és olvasni is.
	//bad(): nagy hiba van, a stream megszakadt
	//eof(): vége a fájlnak
	//good(): a fentiek egyike sem igaz, minden rendben van.
	//clear(): ha a hibát tudjuk kezelni, akkor ezt követõen
	//         vissza kell billenetni a bitet, hogy tudjuk folytatni a vizsgálódást.
	//         clear visszaállítja a "minden rendben" állapotot.
	iostream.open("szoveg.txt", ios::in);
	iostream << "Ez itt rossz sor" << endl;
	if (iostream.fail())
	{
		cout << "Hiba tortent a fajl irasakor. Olvasasra nyitottuk csak meg." << endl;
		iostream.clear();
	}
	else if (iostream.bad())
	{
		cout << "Nagy hiba tortent!" << endl;
		return -1;
	}
	getline(iostream, text);
	cout << text << " sor sikeresen beolvasva." << endl;
	iostream.close();

	srand(time(0));
	Statistics stat(100);
	stat.GenerateDatas();
	stat.ReadDatas();
	stat.PrintDatas();
	stat.PrintStat();
	return 0;
}

//Gyakorló feladat:
//- Készítsen egy osztályt, mely tárolja és elemzi a hooke.csv fájl adatait. (feltöltve a kidolgozott kód mellé)
//- Készítse el a beolvasás függvényt a fájl alapján. Hagyja az elsõ sort figyelmen kívül.
//- Írja ki, hogy hány mérési adat érhetõ el egy rugóhoz.
//- Számolja ki a korrelációt az adatok között (statisztikából tanultak alapján)
//- Számolja ki az átlagos különbséget a mérések között.
//- Számolja ki az adatsor terjedelmét.
//- Számolja ki minden egyes mérési pontban a k rugómerevséget (F = k*x), majd abból egy átlagot.
