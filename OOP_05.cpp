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
	// F�jlkezel�s sorrendje: (Eml�keztet�)
	// - F�jl elnevez�se (l�terhoz�sa)
	// - F�jl megnyit�sa
	// - F�jl �r�sa/olvas�sa
	// - F�jl bez�r�sa
	// 
	// Ha nem z�rjuk be, az adat a streamben ragad, nem ker�l a f�jlba!
	// 
	//ofstream, csak kimeneti stream
	//az egyes flageket ezt k�vet�en, �ket | jellel elv�lasztva kell megadni
	//hol tal�lkoztunk ezzel a jel�l�ssel? Igen! A bitvar�zsn�l!
	//Akkor m�g is volt �rtelme foglalkozni vele! (Lesz is m�g sok.)

	//Flagek:
	//       ios::in - beolvas�s
	//       ios::out - ki�r�s
	//       ios::binary - bin�ris f�jl beolvas�s
	//       ios::ate - a kimeneti kurzor a f�jl v�g�n kezd�dik (at end)
	//       ios::app - hozz�f�z (append)
	//       ios::trunc - t�rli a f�jl el�z� tartalm�t (truncate) 
	ofstream kimenet("szoveg.txt", ios::out | ios::trunc);
	if (!kimenet.is_open()) //f�jl nyitva? �rdemes mindig ellen�rizni. 
		return -1;
	kimenet << "HELLO WORLD!" << endl; //lehet �rni mostanra m�r megszokott << oper�torral
	kimenet << "HELLO MOGI!" << endl;
	kimenet << 42 << endl;
	kimenet.close(); //f�jl bez�r�sa

	//Ha csak beolvasni szeretn�nk
	ifstream bemenet("szoveg.txt", ios::in);
	string text;
	//bemenet >> text;
	while (bemenet.eof()) //end of file f�ggv�ny
	{
		getline(bemenet, text);
		cout << text << endl;
	}
	bemenet.close();


	//fstream, enged inputot �s outputot is!
	fstream iostream("szoveg.txt", ios::in | ios::out | ios::app);
	//Seekp be�ll�tja, hogy a k�vetkez� karaktert milyen poz�ci�b�l �RJON KI.
	//argumentumai: (abszol�t poz�ci�, a f�jl kezdet�t�l sz�molva)
	//				(offset relat�van a "way"-t�l (negat�v is lehet), "way")
	//         way:
	//				ios::beg - stream eleje
	//              ios::cur - jelen poz�ci�
	//              ios::end - f�jl v�ge 
	//Seekg egyezik Seekp-vel, csak BEOLVAS�SRA haszn�lhatjuk.
	iostream << "HELLO MOGI" << endl;
	iostream << "HeLLO" << endl;
	iostream.seekg(0, ios::beg);
	getline(iostream, text);
	cout << text << endl;
	iostream.close();
	//Append el�g �rdekesen tud m�k�dni. Force-olja a ki�r�st, hogy mindig az utols� sor ut�nra
	//ker�lj�n a ki�rand� sz�veg. Helyette az input-ouput haszn�lat�t javaslom.
	//Itt arra kell figyelni, hogy ha a sz�veg v�g�re szeretn�nk �rni, akkor azt be kell �ll�tani.
	//A f�jl elej�t�l kezd.

	iostream.open("szoveg.txt", ios::in | ios::out); //A default is ez. Ekkor is megmarad az adat!
	iostream << "HELLO MOGI";
	iostream.seekp(0, ios::beg);
	//flush: ahogy azt tapasztaltuk is m�r el�z� t�rgyb�l, close n�lk�l a
	//f�jlba nem ker�l bele az adat. Ennek az oka, hogy a streamben marad �s
	//el lesz t�rolva a bufferben. Close �rja ki ezt a f�jlba.
	//Hogy id� k�zben is lehessen ki�rni, ezzel biztos�tva azt is pl.
	//hogy a read �s write buffer megegyezik, hogy flush-olni kell az adatot-
	iostream << "HALLO" << flush; //std::flush seg�ts�g�vel.
	iostream.flush(); //vagy tagf�ggv�nnyel
	iostream.seekg(0, ios::beg);
	iostream >> text;
	cout << text << endl;
	iostream >> text;
	cout << text << endl;
	iostream.seekp(0, ios::end);
	iostream << "END" << endl;
	iostream.close();

	//Hiba kezel�s
	//Vannak k�l�nb�z� hiba bitjei a streamnek, amikkel lehet vizsg�lni a hib�kat
	//fail(): logikai hiba van nagyes�llyel a k�dban: pl. csak inputra nyitottuk meg
	//a f�jlt, mi pedig akarunk �rni �s olvasni is.
	//bad(): nagy hiba van, a stream megszakadt
	//eof(): v�ge a f�jlnak
	//good(): a fentiek egyike sem igaz, minden rendben van.
	//clear(): ha a hib�t tudjuk kezelni, akkor ezt k�vet�en
	//         vissza kell billenetni a bitet, hogy tudjuk folytatni a vizsg�l�d�st.
	//         clear vissza�ll�tja a "minden rendben" �llapotot.
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

//Gyakorl� feladat:
//- K�sz�tsen egy oszt�lyt, mely t�rolja �s elemzi a hooke.csv f�jl adatait. (felt�ltve a kidolgozott k�d mell�)
//- K�sz�tse el a beolvas�s f�ggv�nyt a f�jl alapj�n. Hagyja az els� sort figyelmen k�v�l.
//- �rja ki, hogy h�ny m�r�si adat �rhet� el egy rug�hoz.
//- Sz�molja ki a korrel�ci�t az adatok k�z�tt (statisztik�b�l tanultak alapj�n)
//- Sz�molja ki az �tlagos k�l�nbs�get a m�r�sek k�z�tt.
//- Sz�molja ki az adatsor terjedelm�t.
//- Sz�molja ki minden egyes m�r�si pontban a k rug�merevs�get (F = k*x), majd abb�l egy �tlagot.
