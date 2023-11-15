#include <iostream>
#include <ctime>
#include <string>  //string
#include <sstream> //strinstream

using namespace std;

class Code {
	static int szamolo;
	string text;
	mutable int seed; //AI / neurális háló
	string code;
	inline bool Identical() const {
		return text == code;
	}
public:
	Code() = delete;
	Code(string text, int seed = 42) :text{ text }, seed{ seed } {
		szamolo++;
		srand(seed);
		code = this->text;
	}

	void Shuffle(int times = 10) {
		for (int i = 0; i < times; i++) {
			int rand1 = rand() % code.size(); //0 - code hossza között
			int rand2 = rand() % code.size();
			char tmp = code[rand1];
			code[rand1] = code[rand2];
			code[rand2] = tmp;
		}
		cout << "Coded message: " << code << endl;
	}

	void CeasarCode(int push) {
		int first = 'a', last = 'z';
		for (int i = 0; i < code.size(); i++) {
			int letter = code.at(i);
			letter -= first;
			letter += push;
			if (letter < 1)
				letter += last - first + 1; //negatív irány
			letter %= last - first + 1;  //pozitív irány
			letter += first;
			code.at(i) = letter;
		}
		cout << "Coded message: " << code << endl;
	}

	//Üzenetet ad vissza és CSAK a seed-et tudja módosítani
	const char* ChangeSeed() const{  //minden meghívott fgv-nek és változónak const kell, hogy legyen
		if (Identical()) {
			seed = rand() % 1000;
			srand(seed);
			return "New seed: " + seed;
		}
		return "Old seed remainded.";
	}

	inline void SetOriginal() {
		code = text;  // csk statikus adatokat tartalmazhat
	}

	int PeldanySzam() {
		return szamolo;
	}

	~Code() { // destruktor
		szamolo--;
	}
};

int Code::szamolo = 0;


int main() {
	/*
	const char* message = "fasza";
	string message1 = "palacsintahollóevőrákoskutyagömbölydedkétlapostenyerűcsínytalanbetyár";  //"...\0" operátor túlterhelés
	
	setlocale(LC_ALL, "hun"); //ékezet
	cout << message1 << endl;

	string message2;
	message2.assign("Hello Belló!");
	cout << message2 << endl;  // << túlterhelés

	cout << message[0] << endl;  //tömbként [] túlterhelés
	cout << message1.at(0) << endl; //tagfüggvény

	string szo1 = "cica";
	string szo2 = "mica";
	cout << szo1 << szo2 << endl;
	cout << szo1 + szo2 << endl;  //op. túlterhelés
	szo1 += szo2; //op. túlterhelés
	cout << szo1 << endl;
	szo1.append(szo2);
	cout << szo1 << endl;

	//Törés
	cout << "Törlés előtt: " << szo1.empty() << endl;
	cout << "Hossz: " << szo1.length() << endl;
	cout << "Nagysága: " << szo1.size() << endl;
	szo1.erase();  //egészet törli
	cout << "Törlés után: " << szo1.empty() << endl;
	cout << "Hossz: " << szo1.length() << endl;
	cout << "Nagysága: " << szo1.size() << endl;

	szo1.assign("cica");
	szo1.erase(3, 1);  //3. betűtől 1 hosszan töröl ki
	cout << szo1 << endl;

	//Összehasonlítás
	szo1.assign("cica");
	szo2.assign("bica");
	cout << szo1 << " == " << szo2 << " ? "<<(szo1 == szo2) << endl;  //op. túlterhelés
	cout << szo1 << " == " << szo2 << " ? "<<szo1.compare(szo2) << endl; //0->azonos, -1->szo1 előbb van az abc-ben, 1->szo2 előbb van abc-ben

	string szo = "MogiRobiRobot"; //tanszéki meme
	cout << szo.substr(4, 4) << endl; //új stringet hoz léttre -> new -> heapen allokál   (lassú->view)

	cout << "R helye: " << szo.find("R") << endl;
	cout << "obi helye: " << szo.find("obi") << endl;
	cout << "kutya helye: " << szo.find("kutya") << endl;
	cout << string::npos << endl;
	if (szo.find("kutya") == string::npos)
		cout << szo << "nem tartalmaz kutyát :(" << endl;

	cout << szo.substr(szo.find("Robi")) << endl; // ha nincs 2. argumentum végig kiírja a szót a substr
	
	cout << szo.insert(szo.find("Robi"), "Tanszék") << endl;

	cout << szo.replace(szo.find("Robi"), 4, "Sanyi") << endl;

	const char* szo_tomb = szo.c_str();

	char* szo_tomb2 = new char[100];
	szo.copy(szo_tomb2, szo.length(), 2);
	szo_tomb2[szo.length() - 2] = '\0'; // = 0;
	cout << szo_tomb2 << endl;
	
	cout << endl;
	cout << "Adj meg egy számot bazmeg! ";
	string szam;
	cin >> szam; //egy szót olvas be a konzolról
	cout << szam + szam << endl;
	int szamI = stoi(szam);
	cout << szamI + szamI << endl;

	cout << "Adj meg egy tört számot! Megbassza! ";
	cin >> szam;
	cout << szam + szam << endl;
	float szamf = stof(szam);  //stod + double
	cout << szamf + szamf << endl;

	string sor;
	cin.ignore();  //töröl mindenr a cinből
	cout << "Egész sor beolvasása: ";
	getline(cin, sor);
	cout << sor;

	int count = 0;
	stringstream ss(sor);
	string word;
	while (ss >> word)
		count++;
	cout << "Szavak száma: " << count << "." << endl;
	*/

	Code kod("aaaz");
	kod.Shuffle();
	kod.SetOriginal();
	kod.CeasarCode(1);
	cout << kod.ChangeSeed() << endl;
	Code kod2("zaa");
	cout << kod2.PeldanySzam() << endl;
	       //Code::PeldanySzam()
	//delete[] szo_tomb2;
	return 0;
}