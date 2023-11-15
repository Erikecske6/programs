// 1.ora.cpp : include, kiiratás, pointerek, beolvasás

#include <iostream> //kell -->  ebben vannak az alapvetõ fv-ek amiket használunk
#include <cmath>    //math.h helyett
#include <ctime>    //time.h helyett
#include <iomanip>  //kiiratáskor kell majd --> formázáshoz

using namespace std;    //iostream-ben lévõ fv-ek feloldása (elhagyható az 'std::')
//hátrány: más header fájl-ból van ugyanolyan nevû fv

void csere(int* a, int* b);
void csere(int& a, int& b); //lehet ugyanaz a név ha más típusú adatokat kér be: fv túlterhelés

time_t ido = time(NULL); //ido

int main()
{
    std::cout << "Hello World!\n";  //std = standard
    // :: a hatókör operátor --> mutatja, hogy a cout hova tartozik
    //fel lehet oldani
    cout << "Hello\n";

    //kiiratás: cout << szöveg;

    int a = 15;
    cout << "Int szam: ";
    cout << "a = " << a << endl;    //endl = \n
    //láncolható
    double b = 123.456789;
    cout << "Double szam : ";
    cout << "b: " << b << endl; //6 számjegyik írja ki, végét levágja (nincs kerekítés)
    //automatikusan tudja hogy int/double --> asszerint írja ki

    printf("a=%i \n", a); //régi módszer is mûködik

    //formázás: <iomanip>
    cout << endl;
    cout << "Sima kiiratas: " << "b: " << b << "\t" << "a: " << a << endl;
    cout << "setw(x) " << "b: " << setw(10) << b << "\t" << "a: " << setw(3) << a << endl; //kiírás szélességét állítja be (mekkora helyet foglal el)
    //közvetlen utána jövõre hat
    cout << "setw(x) " << "b: " << setw(30) << b << "\t" << "a: " << setw(20) << a << endl;
    cout << "balra rendezes " << "b: " << left << setw(15) << b << "\t" << "a: " << setw(3) << a << endl; //alapvetõen jobbra rendezi
    //mindenre hat ami utána jön --> vissza jobbra: right, középre: internal
    cout << "setfill(' ') " << "b: " << setfill('*') << setw(15) << b << "\t" << "a: " << setfill(' ') << setw(3) << a << endl; //üres helyek kitöltése
    //mindenre hat ami utána jön
    cout << "setprecision(x) " << "b: " << setprecision(4) << setw(15) << b << "\t" << "a: " << setw(3) << a << endl; //lebegõpontos számok pontosságát állítja be
    cout << "setprecision(x) " << "b: " << setprecision(9) << setw(15) << b << "\t" << "a: " << setw(3) << a << endl; //mindenre hat ami utána jön
    cout << "szamrendszer " << "a:  hex: " << hex << setw(3) << a << " dec:" << dec << a << endl; //számrendszer beállítása (úgy marad)
    cout << "fixed " << "b: " << setw(15) << fixed << b << endl; //9 tizedes pontosság (úgy marad)
    cout << "scientific " << "b: " << setw(15) << scientific << b << endl; //normálalak (úgy marad)
    cout.unsetf(std::ios::floatfield); //fixed, scientific visszaállítása
    cout << "visszaallitva " << "b: " << b << endl;
    cout << "elojel: " << showpos << b << endl; //pozitív számoknál van + (úgy marad)
    cout << noshowpos << endl << endl;

    //adat bekérés cin >> mibe;

    int c;
    cout << "Int szam: ";
    cin >> c;
    cout << c << endl << endl;

    //char - int

    char betu = 65;
    cout << "Betu: " << betu << endl; //char-ként írja ki = A
    int betu2 = 'A';
    cout << "Betu2: " << betu2 << endl; //hiába adtunk meg betût --> int-ként írja ki, mivel az a típusa
    char betu3 = 'B';
    cout << "Betu3: " << betu3 << endl;


    //ékezetek

    setlocale(LC_ALL, "hun");
    cout << "áéíóúõû" << endl; //õ,û nem mindig mûködik

    //igaz-hamis

    bool l = true; //true vagy false (false lehet 0 is)
    cout << "Boolean: " << l << endl;
    l = 0;
    cout << "Boolean: " << l << endl;
    cout << endl << endl;

    //random szám

        //1
    srand((unsigned int)time(NULL));
    double rand1 = (double)(rand() % (11) + 10); //10-tõl 20-ig random egész
    cout << "rand1: " << rand1 << endl;
    //2
    srand((unsigned int)ido);
    double rand2 = (double)(rand() % (21)) / 2.0; //0-tól, 20-ig, 0.5-ével
    cout << "rand2: " << rand2 << endl;



    //pointer


    int i = 50; //sima változó
    int* p; //p pointer
    p = &i; //a p pointer az i változóra mutat
    *p = 42; //*p annak az értéke, amire a p mutat --> i változó értékének beállítása
    cout << "i= " << i << "\t" << "*p= " << *p << endl;

    //tömbök
    srand((unsigned int)time(NULL)); //random számhoz, tömb feltöltésnél
    //régi módszer
    double* t = (double*)malloc(sizeof(double) * 10); //helyfoglalás: malloc
    cout << "t: \t";
    if (t != NULL) //ha nem tud memoriat lefoglalni --> nullpointerrel tér vissza
    {
        for (int i = 0; i < 10; i++)
        {
            *(t + i) = (double)(rand() % 21) / 2.0;
            //*t --> 0.indexûre mutat
            //*(t+i) mindig az egyel többedik indexûre mutat
            //random szám: 0-10-ig, 0.5-ös léptékkel
            cout << t[i] << " ";
        }
    } //feltöltés
    free(t); //törlés
    cout << endl;

    //új módszer
    double* t2 = new double; //1 double adat létrehozása
    double* t3 = new double[10]; //elõzõvel megegyezik: 10 adatos tömb
    //létraohzás: new típus [helyek száma];
    cout << "t3: \t";
    for (int i = 0; i < 10; i++)
    {
        *(t3 + i) = (double)(rand() % 21) / 2.0;
        cout << t3[i] << " ";
    }
    delete[]t3; //törlés
    delete t2;
    cout << endl;

    //2D-s tömb --> pl egy 3x3-as mátrix
    int** T = new int* [3]; //olyan tömb, amiben 3 int* van
    for (int i = 0; i < 3; i++)
    {
        T[i] = new int[3]; //ettõl lesz 2D: a tömb 1-1 eleméhez egy másik tömb tartozik
        //minden int*-hoz egy olyan tömböt csinál amiben 3 int van
    }
    for (int i = 0; i < 3; i++) //feltöltés --> egységmátrix
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == j) //fõátló
                T[i][j] = 1;
            else
                T[i][j] = 0;
            cout << T[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < 3; i++) //törlés
    {
        delete[]T[i]; //belül lévõ tömbök törlése
    }
    delete[]T; //külsõ tömb törlése
    cout << endl << endl;

    //referencia

    int vált = 12;
    int* pointer = &vált; //a változóra mutat
    int& ref = vált; //adott változóhoz kötõdik  --> meg kell adni hogy melyik változóé
    //együtt változnak
    //a vált. nevû változó másik neve: ref (ugyanaz a cím, típus)

    cout << "Változó: " << vált << "  ref: " << ref << endl;
    vált++;
    cout << "Változó: " << vált << "  ref: " << ref << endl;

    //csere
    int sz1 = 10; int sz2 = 20;
    cout << "Szam1: " << sz1 << "  Szam2: " << sz2 << endl;
    //pointer szerint: C-ben
    csere(&sz1, &sz2);
    cout << "Szam1: " << sz1 << "  Szam2: " << sz2 << endl;
    //referencia szerint
    csere(sz1, sz2);
    cout << "Szam1: " << sz1 << "  Szam2: " << sz2 << endl;


}

//pointer szerinti csere
void csere(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
//referencia szerinti csere
void csere(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
