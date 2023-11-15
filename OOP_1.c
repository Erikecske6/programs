#include <stdio.h>
#include <math.h>
#include <stdlib.h> //malloc

#include <iostream> //kiiras
#include <iomanip> //kiiras dekor
#include <cmath>

using namespace std;

//saját névtér
namespace MOGI {
    const char* targy = "MOGI";
    namespace IPA {
        const char* targy = "C";
    }
    namespace OOP {
        const char* targy = "C++";
    }
}
namespace MM {
    const char* targy = "MM";s
}

void swap(int a, int b);
void swapP(int *a, int *b);
void swapR(int &a, &int b);

int main() {
    /*
    printf("Hello MOGII\n");

    int a,b;
    printf("a= ");
    scanf_s("%d", &a);
    printf("b= ");
    scanf_s("%d", &b);

    double c = (double)a / b;
    printf("a/b = %05.2lf\n", c);
    */
    //========== C++ bev =============

    std::cout << "Hello World!" << std::endl; //endline
    cout << "Hello" <<MOGI::targy <<endl;
    cout << "Hello" <<MM::targy <<endl;
    cout << "Hello" <<MOGI::IPA::targy <<endl;
    cout << "Hello" <<MOGI::OOP::targy <<endl;


    double szam = 156454.654;
    cout.precision(5);
    cout << "szam" << szam << endl;
    cout << "fixed: " << fixed << szam << '\t' << 2000.0 << '\t' << 2000 << endl;
    cout << "tudomanyos\t" << scientific << szam << endl;

    cout << setfill('0');
    cout.width(6); cout << left << -7 << '\n';
    cout.width(6); cout << internal << -7 << '\n';
    cout.width(6); cout << right << -7 << '\n';

    //Számrendszerek
    cou << "oct\thex\tdec" << endl;
    cout << oct << 15 << '\t' << endl;
    cout << showbase;
    cout << noshowbase;

    //Elojelek
    cout << 




    int szam1 = 6, szam2= 8;
    swapP(&szam1, &szam2);


    //Referencia
    int& copíszam1 = szam1; //alias
    cout << szam1 << endl;
    szam1++;
    cout << copyszam1 << endl;
    copyszam1++;
    cout << szam1 << endl;

    //Pointer
    //C-ben
    int* p = NULL;
    int* tomb = (int*)malloc(10 * sozeof(int));
    p = (int*)malloc(sizeof(int));
    for (int i = 0; i<10; i++){
        tomb[i] = i;
    }
    *p = tomb[0];
    free(tomb);
    free(p);


    //C++
    p = nullptr;
    tomb = new int[10];
    p = new int;
    for (int i = 0; i < 10; i++)
        tomb[i] = i;
    *p = tomb[0]
    delete p;
    delete[] tomb; //kulon tombre

    //igaz-hamis
    bool prim = false;
    prim = true;
    cout << true << endl; //!0 a true
    cout << false << endl; //0 a false

    if (5)
        cout << "Ez igaz" << endl;
    
    cout << "szam1 = " << endl;
    cin >> szam1;
    cout << szam1 << endl;
}


void swap(int a, int b){
    int tmp = a;
    a = b;
    b = tmp;
    cout << "a= " << a << '\t' << "b= " << b << endl;
};
void swapP(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
    cout << "a= " << *a << "b = " << *b <<endl;
};
void swapR(int &a, &int b){

};