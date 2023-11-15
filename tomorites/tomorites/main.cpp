#include <iostream>
#include <string>

using namespace std;

class SzovegMuveletek {
private:
    string szoveg1;
    string szoveg2;

public:
    SzovegMuveletek(string s1, string s2) : szoveg1(s1), szoveg2(s2) {}

    
    string leghosszabbAzonosResz() {
        int hossz1 = szoveg1.length();
        int hossz2 = szoveg2.length();

        // Táblázat létrehozása a közös részek hosszának tárolásához
        int** dp = new int* [hossz1 + 1];
        for (int i = 0; i <= hossz1; ++i) {
            dp[i] = new int[hossz2 + 1];
        }

        // Töltse fel a táblázatot nullákkal
        for (int i = 0; i <= hossz1; ++i) {
            for (int j = 0; j <= hossz2; ++j) {
                dp[i][j] = 0;
            }
        }

        // Dinamikus programozás: megtaláljuk a leghosszabb közös részt
        int maxHossz = 0;
        int maxHosszIndex = 0;
        for (int i = 1; i <= hossz1; ++i) {
            for (int j = 1; j <= hossz2; ++j) {
                if (szoveg1[i - 1] == szoveg2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;

                    if (dp[i][j] > maxHossz) {
                        maxHossz = dp[i][j];
                        maxHosszIndex = i;
                    }
                }
            }
        }

        // Felszabadítjuk a memóriát
        for (int i = 0; i <= hossz1; ++i) {
            delete[] dp[i];
        }
        delete[] dp;

        // Visszatérés a leghosszabb közös részszel
        return szoveg1.substr(maxHosszIndex - maxHossz, maxHossz);
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

    SzovegMuveletek ha("malom", "halom");
    cout << "Leghosszabb azonos resz: " << ha.leghosszabbAzonosResz() << endl;

    SzovegMuveletek sm2("maaaalommmmm", "bbba");  //csak az első szót tömöríti
    cout << "Tomoritett szoveg: " << sm2.tomorites() << endl;

    return 0;
}
