#include <iostream>
#include <ctime>

using namespace std;

enum Actions {Nothing, Learn, Train, WeaponUp, Fight};

enum class Weapons {Empty, Stick, Rock, Sword, Bow, Crossbow};

//Objektumok
struct Teglalap {  //deafut public
	int a, b;
	int terulet() {
		return a * b;
	}
};

class Stickman { //deafault private
	static int genNum;  //nem példányhoz, hanem egész objektumhoz csatlakozik
	int power, defense, index;
	double health;
	Weapons* weapon;
	int weaponNum, weaponMax;

public:
	//konstruktor
	Stickman()
	{
		index = ++genNum;
		power = 1;
		defense = 1;
		weaponNum = 0;
		weaponMax = 5;
		weapon = new Weapons[weaponMax];
		weapon[weaponNum++] = Weapons::Empty;
		//weaponNum++;
	}

	Stickman(double health)
	{
		index = ++genNum;
		power = 1;
		defense = 1;
		this->health = health;
		weaponNum = 0;
		weaponMax = 5;
		weapon = new Weapons[weaponMax];
		weapon[weaponNum++] = Weapons::Empty;
		//weaponNum++;
	}

	Stickman(int power, int defense) : power{power}, defense{defense}
	{
		index = ++genNum;
		power = 1;
		defense = 1;
		this->health = health;
		weaponNum = 0;
		weaponMax = 5;
		weapon = new Weapons[weaponMax];
		weapon[weaponNum++] = Weapons::Empty;
		//weaponNum++;
	}

	//Ha nekünk van tömbünk a class-ban, kell copy (másoló) konstruktor
	Stickman(const Stickman& s) {
		cout << "masolo" << endl;
		this->power = s.power;
		defense = s.defense;
		health = s.health;
		index = s.index;
		weaponMax = s.weaponMax;
		weaponNum = s.weaponNum;
		weapon = new Weapons[weaponMax];
		for (int i = 0; i < weaponNum; i++)
			weapon[i] = s.weapon[i];
	}


	//tagfüggvény
	inline void Printstats() {
		cout << index << ". character: " << health << endl;
		cout << "Stats: " << power << '\t' << defense << endl;
	}

	//Getter
	inline double GetHealth() {
		return health;
	}
	
	//Setter
	inline void SetPower(int power) {
		this->power = power;
	}

	void PickUpWeapon();

	//destruktor
	~Stickman() {
		cout << index << ". character: Game Over" << endl;
		delete[] weapon;
	}

};

int Stickman::genNum = 0;


int main() {

	//példány(osítás) (instance)
	Teglalap t1;
	t1.a = 6;
	t1.b = 36;
	//cout << t1.terulet() << endl;

	srand(time(0));

	Stickman hero;  //default
	Stickman hero2 = double(rand() % 11); //egy argumentumos konstruktor
	Stickman hero3(1 + rand() % 10, 1 + rand() % 10);

	hero.Printstats();
	hero2.Printstats();
	hero3.Printstats();

	Stickman* enemy = new Stickman(1000.0);
	enemy->SetPower(15);
	
	Stickman* hero_array = new Stickman[4];

	//placement new
	//Nem heap-en allokál, nem kell delete
	//new hová_másoljon_(memria cím) mit?
	new (&hero_array[0]) Stickman(hero);
	new (&hero_array[1]) Stickman(hero2);
	new (&hero_array[2]) Stickman(hero3);
	new (&hero_array[3]) Stickman(hero3);

	hero_array[0].GetHealth();

	//mindent beezár: Ctrl + M + O
	//mindent nyit: Ctrl + M + P


	delete enemy;
	delete[] hero_array;


	return 0;
}

void Stickman::PickUpWeapon()
{
	if (weaponNum + 1 >= weaponMax)
		return;
	Weapons newWeapon = Weapons(rand() % 6);
	cout << index << " character: ";
	weapon[weaponNum++] = newWeapon;
	switch (newWeapon) {
	case Weapons::Stick:
		cout << "Stick" << endl;
		break;
	case Weapons::Sword:
		cout << "Sword" << endl;
		break;
	case Weapons::Bow:
		cout << "Bow" << endl;
		break;
	case Weapons::Crossbow:
		cout << "Crossbow" << endl;
		break;
	default:
		cout << "Nothing" << endl;
	}
}