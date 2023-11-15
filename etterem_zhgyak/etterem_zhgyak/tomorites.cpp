#include <iostream>
#include <string>

using namespace std;

class SzovegMuveletek {
private:
    string szoveg1;
    string szoveg2;

public:
    SzovegMuveletek(const string& s1, const string& s2) : szoveg1(s1), szoveg2(s2) {}

    string leghosszabbAzonosResz() {
        string leghosszabbAzonos;
        size_t hossz = min(szoveg1.length(), szoveg2.length());

        for (size_t i = 0; i < hossz; i++) {
            if (szoveg1[i] == szoveg2[i]) {
                leghosszabbAzonos += szoveg1[i];
            }
            else {
                break;
            }
        }

        return leghosszabbAzonos;
    }

    string tomorites() {
        string tomoritettSzoveg;
        size_t hossz = szoveg1.length();

        for (size_t i = 0; i < hossz; i++) {
            char aktChar = szoveg1[i];
            size_t count = 1;

            // Számoljuk az egymást követő előfordulásokat
            while (i < hossz - 1 && szoveg1[i] == szoveg1[i + 1]) {
                count++;
                i++;
            }

            // Ha egymást követő előfordulások több mint egy, akkor adjuk hozzá a tömörített szöveghez a számot is
            if (count > 1) {
                tomoritettSzoveg += aktChar;
                tomoritettSzoveg += to_string(count);
            }
            else {
                tomoritettSzoveg += aktChar;
            }
        }

        return tomoritettSzoveg;
    }
};

int main() {
    SzovegMuveletek sm("alma", "almafa");
    cout << "Leghosszabb azonos resz: " << sm.leghosszabbAzonosResz() << endl;

    SzovegMuveletek sm2("aaab", "malom");
    cout << "Tomorített szoveg: " << sm2.tomorites() << endl;

    return 0;
}
