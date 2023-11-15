#include <iostream>
#include <string>
#include <ctime>

using namespace std;

template<class T>
struct Point2D {
//public
	T x, y;
	Point2D() {
		x = 0; y = 0;
	}
	Point2D(T x, T y) : x{x}, y{y} {}

	//+,-, +=, <<, >>
	//Nem lehet tulterhelni -> ?, ::
	//tagfgv. -> classshoz tartozik Pont2D.Print()
	//hozzáfér z adattagokhoz, de külső fgv. Print(Pont2DA)
	friend ostream& operator<<(ostream& os, const Point2D& z) {  //nem másolunk, hanem módosítjuk az eredeti példányt
		os << "2d" << endl;
		os << "x: " << z.x << "\ty: " << z.y << endl;
		return os;
	}

	//Postfix++
	Point2D operator++(int) {
		Point2D tmp = *this;
		x++; y++;
		return tmp;
	}

	//++Prefix
};

class Point3D { //kompozíció
	Point2D<int> p;
	int z;
public:
	Point3D() {
		p = Point2D<int>();
		z = 0;
	}
	Point3D(Point2D<int> xy, int z) : p{ xy }, z{ z } {}

	void Print() {
		cout << "3D" << endl;
		cout << p << "\tz:" << z << endl;
	}

	void Move() {
		p++;
		z++;
	}

	~Point3D() { cout << "3D  point is destroyed. MUHAHAHAHA !!!!!" << endl; }
};

class Circle { //aggregáció
	Point2D<int>* o;
	int r;
public:
	Circle() = delete;
	Circle(Point2D<int>*o, int r) {
		this->o = o;
		this->r = r;
	}
	void Print() {
		cout << "Circle" << endl;
		cout << *o << r << endl;
	}
	void Move() { *(o)++; }
	~Circle() { cout << "Circle is destroyed"; }
};

enum class Color { Black, Blue, Red };

class Shape {
protected:  //örökölt tagok látják(public),  kívülről nem lehet hozzáférni
	Color color;
	double area;
public:
	Shape() {
		color = Color(rand() % 3);
		area = (double)rand() / RAND_MAX * 30; //0 - 30 között
	}
	Shape(double area) {
		color = Color(rand() % 3);
		this->area = area;
	}

	Color GetColor() { return color; }
	double GetArea() { return area; }
	void GetType() { cout << "Shape" << endl; }
	~Shape(){}
};

class Rectangle /*leszármazott*/ : public Shape { //ős
	double a, b;
public:
	Rectangle() = delete;
	Rectangle(double a, double b) : a{a}, b{b} , Shape(a*b){}

	void GetType() override {  //nem csinál semmit, csakjelez, ha nincs vituális példány
		cout << "Rectangle" << endl; 
	}
	void Print() { cout << GetArea() << '\t' << int(GetColor()) << endl; }
	double GetA() { return a; }
	void Draw() {
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				cout << "#";
			}
		}
	}
};

//Absztarkt class -> Csak virtuális tagjai vannak
//Interface class -> Nincs tárolt változó ÉS csak pure virtuális fgv.-ket tartalmaz
class Drawable {
public:
	virtual void Draw() = 0;  //pure  (tisztán) virtuális fgv
							  //kötelezi az utódot, hogy írják meg túlterhelését -> egyébként error
};

class Square : public Rectangle, public Drawable  //többszörös öröklődés
{
	double a, b;
public:
	Square() = delete;
	Square(double a) : Rectangle(a, a) {}

	void GetType() override   //nem csinál semmit, csakjelez, ha nincs vituális példány
	{
		cout << "Square" << endl;
	}
	void Print() { cout << GetArea() << '\t' << int(GetColor()) << endl; }
	double GetA() { return a; }
	void Draw() {
		for (int i = 0; i < GetA(); i++) {
			for (int j = 0; j < GetA(); j++) {
				cout << "#";
			}
		}
	}
};

int main() {
	

	Point2D<int> p;
	cout << p++ << endl;
	cout << p << endl;

	{
		Point3D terPont(p, 5);
		terPont.Print();
		terPont.Move();
		terPont.Print();
	}
	cout << "===================" << endl;
	cout << p << endl;
	cout << "===================" << endl;

	srand(time(nullptr));

	Shape alakzat;
	alakzat.GetType();
	cout << "============" << endl;
	Rectangle teglalap(10, 2);
	cout << teglalap.GetArea() << '\t' << int(alakzat.GetColor()) << endl;
	teglalap.Print();  //teglalap egy tagfgv.
	teglalap.GetType();  //
	cout << "===========" << endl;
	

	Shape** alakzatok = new Shape * [3];
	alakzatok[0] = new Shape;
	alakzatok[1] = new Rectangle(2, 3);
	alakzatok[2] = new Square(6);

	for (int i = 0; i < 3; i++) {
		alakzatok[i]->GetType();
	}

	for (int i = 0; i < 3; i++) delete alakzatok[i];
	delete[] alakzatok;

	//castolás
	//static_cast -> enged fel és lefelé konverziót
	//dynamic_cast -> csak utódot enged őssé, egyébként nullptr
	Rectangle** teglalapok = new Rectangle * [3];
	teglalapok[0] = dynamic_cast<Rectangle*> (new Shape);
	teglalapok[1] = new Rectangle(2, 3);
	teglalapok[2] = static_cast<Rectangle*>(new Square(5));

	for(int i= 0; i < 3; i++) {
		cout << teglalapok[i] << endl;
		if (teglalapok[i])
			teglalapok[i]->GetType();
	}
	

	return 0;
}