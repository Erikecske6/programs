#include <iostream>
#include <string>

//using namespace std;


class Etel {
private:
    std::string nev;
    int ar;
    static int szam;

public:
    Etel() : nev("hamburger"), ar(590) {
        szam++;
    }

    Etel(std::string nev, int ar) : nev(nev), ar(ar) {
        szam++;
    }

    std::string getNev() const {
        return nev;
    }

    void setNev(const std::string& nev) {
        this->nev = nev;
    }

    int getAr() const {
        return ar;
    }

    void setAr(int ar) {
        this->ar = ar;
    }

    static int getSzam() {
        return szam;
    }
};

int Etel::szam = 0;

class Etterem {
private:
    int egyenleg;
    static const int etel_max = 10;
    Etel etelek[etel_max];
    int etelCount;

public:
    Etterem() : egyenleg(1000), etelCount(0) {}

    int getEgyenleg() const {
        return egyenleg;
    }

    void menu_hozaad(const Etel& etel) {
        if (etelCount < etel_max) {
            etelek[etelCount] = etel;
            etelCount++;
        }
    }

    void rendel(const std::string& nev) {
        for (int i = 0; i < etelCount; i++) {
            if (etelek[i].getNev() == nev) {
                std::cout << "Rendelt etel: " << etelek[i].getNev() << ", ar: " << etelek[i].getAr() << std::endl;
                egyenleg += etelek[i].getAr();
                return;
            }
        }
        std::cout << "Nincs ilyen etel a menuben: " << nev << std::endl;
    }

    void reklamas(const std::string& nev) {
        for (int i = 0; i < etelCount; i++) {
            if (etelek[i].getNev() == nev) {
                std::cout << "Reklam: " << etelek[i].getNev() << " - " << etelek[i].getAr() << " Ft visszakapva." << std::endl;
                egyenleg -= etelek[i].getAr();
                return;
            }
        }
        std::cout << "Nincs ilyen etel a menuben: " << nev << std::endl;
    }
};

int main() {
    Etel etel1("Pizza", 890);
    Etel etel2("Sor", 350);

    Etterem etterem;
    etterem.menu_hozaad(etel1);
    etterem.menu_hozaad(etel2);

    std::cout << "Etelek szama: " << Etel::getSzam() << std::endl;
    std::cout << "Egyenleg: " << etterem.getEgyenleg() << " Ft" << std::endl;

    etterem.rendel("Pizza");
    etterem.rendel("Sor");
    etterem.rendel("Burger");

    etterem.reklamas("Pizza");

    std::cout << "Egyenleg: " << etterem.getEgyenleg() << " Ft" << std::endl;

    return 0;
}
