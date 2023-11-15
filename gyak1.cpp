// 1.ora.cpp : include, kiirat�s, pointerek, beolvas�s

#include <iostream> //kell -->  ebben vannak az alapvet� fv-ek amiket haszn�lunk
#include <cmath>    //math.h helyett
#include <ctime>    //time.h helyett
#include <iomanip>  //kiirat�skor kell majd --> form�z�shoz

using namespace std;    //iostream-ben l�v� fv-ek felold�sa (elhagyhat� az 'std::')
//h�tr�ny: m�s header f�jl-b�l van ugyanolyan nev� fv

void csere(int* a, int* b);
void csere(int& a, int& b); //lehet ugyanaz a n�v ha m�s t�pus� adatokat k�r be: fv t�lterhel�s

time_t ido = time(NULL); //ido

int main()
{
    std::cout << "Hello World!\n";  //std = standard
    // :: a hat�k�r oper�tor --> mutatja, hogy a cout hova tartozik
    //fel lehet oldani
    cout << "Hello\n";

    //kiirat�s: cout << sz�veg;

    int a = 15;
    cout << "Int szam: ";
    cout << "a = " << a << endl;    //endl = \n
    //l�ncolhat�
    double b = 123.456789;
    cout << "Double szam : ";
    cout << "b: " << b << endl; //6 sz�mjegyik �rja ki, v�g�t lev�gja (nincs kerek�t�s)
    //automatikusan tudja hogy int/double --> asszerint �rja ki

    printf("a=%i \n", a); //r�gi m�dszer is m�k�dik

    //form�z�s: <iomanip>
    cout << endl;
    cout << "Sima kiiratas: " << "b: " << b << "\t" << "a: " << a << endl;
    cout << "setw(x) " << "b: " << setw(10) << b << "\t" << "a: " << setw(3) << a << endl; //ki�r�s sz�less�g�t �ll�tja be (mekkora helyet foglal el)
    //k�zvetlen ut�na j�v�re hat
    cout << "setw(x) " << "b: " << setw(30) << b << "\t" << "a: " << setw(20) << a << endl;
    cout << "balra rendezes " << "b: " << left << setw(15) << b << "\t" << "a: " << setw(3) << a << endl; //alapvet�en jobbra rendezi
    //mindenre hat ami ut�na j�n --> vissza jobbra: right, k�z�pre: internal
    cout << "setfill(' ') " << "b: " << setfill('*') << setw(15) << b << "\t" << "a: " << setfill(' ') << setw(3) << a << endl; //�res helyek kit�lt�se
    //mindenre hat ami ut�na j�n
    cout << "setprecision(x) " << "b: " << setprecision(4) << setw(15) << b << "\t" << "a: " << setw(3) << a << endl; //lebeg�pontos sz�mok pontoss�g�t �ll�tja be
    cout << "setprecision(x) " << "b: " << setprecision(9) << setw(15) << b << "\t" << "a: " << setw(3) << a << endl; //mindenre hat ami ut�na j�n
    cout << "szamrendszer " << "a:  hex: " << hex << setw(3) << a << " dec:" << dec << a << endl; //sz�mrendszer be�ll�t�sa (�gy marad)
    cout << "fixed " << "b: " << setw(15) << fixed << b << endl; //9 tizedes pontoss�g (�gy marad)
    cout << "scientific " << "b: " << setw(15) << scientific << b << endl; //norm�lalak (�gy marad)
    cout.unsetf(std::ios::floatfield); //fixed, scientific vissza�ll�t�sa
    cout << "visszaallitva " << "b: " << b << endl;
    cout << "elojel: " << showpos << b << endl; //pozit�v sz�mokn�l van + (�gy marad)
    cout << noshowpos << endl << endl;

    //adat bek�r�s cin >> mibe;

    int c;
    cout << "Int szam: ";
    cin >> c;
    cout << c << endl << endl;

    //char - int

    char betu = 65;
    cout << "Betu: " << betu << endl; //char-k�nt �rja ki = A
    int betu2 = 'A';
    cout << "Betu2: " << betu2 << endl; //hi�ba adtunk meg bet�t --> int-k�nt �rja ki, mivel az a t�pusa
    char betu3 = 'B';
    cout << "Betu3: " << betu3 << endl;


    //�kezetek

    setlocale(LC_ALL, "hun");
    cout << "�������" << endl; //�,� nem mindig m�k�dik

    //igaz-hamis

    bool l = true; //true vagy false (false lehet 0 is)
    cout << "Boolean: " << l << endl;
    l = 0;
    cout << "Boolean: " << l << endl;
    cout << endl << endl;

    //random sz�m

        //1
    srand((unsigned int)time(NULL));
    double rand1 = (double)(rand() % (11) + 10); //10-t�l 20-ig random eg�sz
    cout << "rand1: " << rand1 << endl;
    //2
    srand((unsigned int)ido);
    double rand2 = (double)(rand() % (21)) / 2.0; //0-t�l, 20-ig, 0.5-�vel
    cout << "rand2: " << rand2 << endl;



    //pointer


    int i = 50; //sima v�ltoz�
    int* p; //p pointer
    p = &i; //a p pointer az i v�ltoz�ra mutat
    *p = 42; //*p annak az �rt�ke, amire a p mutat --> i v�ltoz� �rt�k�nek be�ll�t�sa
    cout << "i= " << i << "\t" << "*p= " << *p << endl;

    //t�mb�k
    srand((unsigned int)time(NULL)); //random sz�mhoz, t�mb felt�lt�sn�l
    //r�gi m�dszer
    double* t = (double*)malloc(sizeof(double) * 10); //helyfoglal�s: malloc
    cout << "t: \t";
    if (t != NULL) //ha nem tud memoriat lefoglalni --> nullpointerrel t�r vissza
    {
        for (int i = 0; i < 10; i++)
        {
            *(t + i) = (double)(rand() % 21) / 2.0;
            //*t --> 0.index�re mutat
            //*(t+i) mindig az egyel t�bbedik index�re mutat
            //random sz�m: 0-10-ig, 0.5-�s l�pt�kkel
            cout << t[i] << " ";
        }
    } //felt�lt�s
    free(t); //t�rl�s
    cout << endl;

    //�j m�dszer
    double* t2 = new double; //1 double adat l�trehoz�sa
    double* t3 = new double[10]; //el�z�vel megegyezik: 10 adatos t�mb
    //l�traohz�s: new t�pus [helyek sz�ma];
    cout << "t3: \t";
    for (int i = 0; i < 10; i++)
    {
        *(t3 + i) = (double)(rand() % 21) / 2.0;
        cout << t3[i] << " ";
    }
    delete[]t3; //t�rl�s
    delete t2;
    cout << endl;

    //2D-s t�mb --> pl egy 3x3-as m�trix
    int** T = new int* [3]; //olyan t�mb, amiben 3 int* van
    for (int i = 0; i < 3; i++)
    {
        T[i] = new int[3]; //ett�l lesz 2D: a t�mb 1-1 elem�hez egy m�sik t�mb tartozik
        //minden int*-hoz egy olyan t�mb�t csin�l amiben 3 int van
    }
    for (int i = 0; i < 3; i++) //felt�lt�s --> egys�gm�trix
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == j) //f��tl�
                T[i][j] = 1;
            else
                T[i][j] = 0;
            cout << T[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < 3; i++) //t�rl�s
    {
        delete[]T[i]; //bel�l l�v� t�mb�k t�rl�se
    }
    delete[]T; //k�ls� t�mb t�rl�se
    cout << endl << endl;

    //referencia

    int v�lt = 12;
    int* pointer = &v�lt; //a v�ltoz�ra mutat
    int& ref = v�lt; //adott v�ltoz�hoz k�t�dik  --> meg kell adni hogy melyik v�ltoz��
    //egy�tt v�ltoznak
    //a v�lt. nev� v�ltoz� m�sik neve: ref (ugyanaz a c�m, t�pus)

    cout << "V�ltoz�: " << v�lt << "  ref: " << ref << endl;
    v�lt++;
    cout << "V�ltoz�: " << v�lt << "  ref: " << ref << endl;

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
