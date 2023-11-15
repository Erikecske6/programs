#include "Sort.hpp"

//==================== FÜGGVÉNY++ ==============================
// ref &
//header
//template
//default
//overload
//rekurzio

int Factor(int n){
	int szam = 1;
	if (n > 1)
		for (int i = 1; i <= n; i++) 
			szam *= i;
	return szam;
}

//Két fontos szabály!!!
//                  -meg kell hívni a fgv-nek önmagát
//                  -egy ponton ki kell lépni

int FactorRekurzio(int n) {
	try {
		if (n == 0) return 1;
		else return n * FactorRekurzio(n - 1);
	}
	catch (int e) {
		cout << "Hiba van! Kódja:" << e << endl;
	}
}

int infLoop(int n) {
	return infLoop(n);
}

template<typename T>
void Print(T* array, int length = 100, const char* message = ""); //default több változó

template <typename T>
void Print(T value, const char* message = ""); //overload - túlterhelés

bool isPrime(int n, int i = 2) {
	if (n <= 2)
		return (n == 2) ? true : false;
	else if (n % i == 0)
		return false;
	else if (i > sqrt(n))
		return true;

	return isPrime(n, i + 1);
}

int main() {
	
	cout << "Hello MOGI"<<endl;
	cout << "5! = "<<Factor(5)<<endl;
	cout << "5! = "<<FactorRekurzio(5)<<endl;
	//infLoop(5);

	time_t ido;
	time(&ido);
	srand((unsigned int)ido);
	int* tomb = new int[100];
	for (int i = 0; i < 100; i++)
		tomb[i] = rand() % 1001; //0-1000 -ig szamokat
	int* masolat = copyToNew(tomb);

	bubbleSort(masolat, 100);
	Print(masolat, 100, "Helo");

	Print(Sum(masolat));
	int* osszeg = Sum(masolat, tomb);
	Print(osszeg);

	cout << "Prím?" << endl;
	Print(isPrime(6));

	delete[] tomb;
	delete[] masolat;
	delete[] osszeg;

	return 0;
//#include "Bracket.hpp"
}

template<typename T>
void Print(T* array, int length, const char* message)
{
	cout << message << endl;
	cout << "Tomb elemei: " << endl;
	for (int i = 0; i < length;i++) {
		cout<<array[i]<<endl;
	}
}

template<typename T>
void Print(T value, const char* message)
{
	cout << message << endl;
	cout << value << endl;
}
