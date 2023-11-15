#include <iostream>
#include <string>
#include <vector>
#include <regex>

class Felhasznalo {
private:
    std::string felhasznalonev;
    std::string email;
    std::string jelszo;

public:
    Felhasznalo(const std::string& felhasznalonev, const std::string& email, const std::string& jelszo)
        : felhasznalonev(felhasznalonev), email(email), jelszo(jelszo) {}

    const std::string& getFelhasznalonev() const { return felhasznalonev; }
    const std::string& getEmail() const { return email; }
    const std::string& getJelszo() const { return jelszo; }
};

class Regisztracio {
private:
    std::vector<Felhasznalo> felhasznalok;
    int bejelentkezesiProbak;

public:
    Regisztracio() : bejelentkezesiProbak(0) {}

    bool vanElyenFelhasznalonev(const std::string& felhasznalonev) {
        for (const Felhasznalo& felhasznalo : felhasznalok) {
            if (felhasznalo.getFelhasznalonev() == felhasznalonev) {
                return true;
            }
        }
        return false;
    }

    bool ervenyesEmail(const std::string& email) {
        // Implementálja az e-mail ellenőrzési logikát itt
        // True értékkel térjen vissza, ha az e-mail formátuma érvényes, egyébként false-szal
         // E-mail ellenőrzési reguláris kifejezés
        std::string emailRegex = R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}\b)";
        std::regex reg(emailRegex);

        if (std::regex_match(email, reg)) {
            return true;
        }
        return false;
    }

    void felhasznaloRegisztracio() {
        std::string felhasznalonev, email, jelszo;

        std::cout << "Adja meg a felhasználónevet: ";
        std::cin >> felhasznalonev;

        if (vanElyenFelhasznalonev(felhasznalonev)) {
            std::cout << "Ez a felhasználónév már foglalt." << std::endl;
            return;
        }

        std::cout << "Adja meg az e-mail címet: ";
        std::cin >> email;

        if (!ervenyesEmail(email)) {
            std::cout << "Helytelen e-mail formátum." << std::endl;
            return;
        }

        std::cout << "Adja meg a jelszót: ";
        std::cin >> jelszo;

        if (felhasznalok.size() < 3) {
            felhasznalok.emplace_back(felhasznalonev, email, jelszo);
            std::cout << "Sikeres regisztráció." << std::endl;
        }
        else {
            std::cout << "A regisztráció jelenleg nem lehetséges." << std::endl;
        }
    }

    bool bejelentkezes() {
        std::string felhasznalonev, jelszo;

        std::cout << "Adja meg a felhasználónevet: ";
        std::cin >> felhasznalonev;
        std::cout << "Adja meg a jelszót: ";
        std::cin >> jelszo;

        for (const Felhasznalo& felhasznalo : felhasznalok) {
            if (felhasznalo.getFelhasznalonev() == felhasznalonev && felhasznalo.getJelszo() == jelszo) {
                std::cout << "Sikeres bejelentkezés." << std::endl;
                bejelentkezesiProbak = 0;  // Nullázza a bejelentkezési próbákat
                return true;
            }
        }

        std::cout << "Hibás felhasználónév vagy jelszó." << std::endl;
        bejelentkezesiProbak++;

        if (bejelentkezesiProbak >= 3) {
            std::cout << "Túl sok bejelentkezési próbálkozás. Kilépés." << std::endl;
            exit(0);
        }

        return false;
    }

    void adminMód() {
        // Implementálja az admin mód logikáját a felhasználói adatok megjelenítéséhez
        std::cout << "Admin mód aktiválva. Felhasználók adatai:" << std::endl;
        for (const Felhasznalo& felhasznalo : felhasznalok) {
            std::cout << "Felhasználónév: " << felhasznalo.getFelhasznalonev() << std::endl;
            std::cout << "E-mail: " << felhasznalo.getEmail() << std::endl;
            std::cout << "-------------------" << std::endl;
        }

    }
};

int main() {
    Regisztracio regisztraciosRendszer;

    while (true) {
        char valasztas;
        std::cout << "Adja meg 'r'-t regisztrációhoz, 'b'-t bejelentkezéshez, 'a'-t az admin módhoz vagy 'q'-t a kilépéshez: ";
        std::cin >> valasztas;

        switch (valasztas) {
        case 'r':
            regisztraciosRendszer.felhasznaloRegisztracio();
            break;
        case 'b':
            if (regisztraciosRendszer.bejelentkezes()) {
                // Engedélyezze a hozzáférést vagy cselekedeteket a bejelentkezett felhasználónak
            }
            break;
        case 'a':
            regisztraciosRendszer.adminMód();
            break;
        case 'q':
            exit(0);
        default:
            std::cout << "Érvénytelen választás. Próbálja újra." << std::endl;
        }
    }

    return 0;
}
