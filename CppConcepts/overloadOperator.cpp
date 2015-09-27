#include <iostream>
using namespace std;
class Complex
{
public:
	Complex( double re = 0.0, double im = 0.0 )
	{
		real = re;
		image = im;
	}

	void print( )
	{
		cout << "Real = " << real << '\t'
		     << "Image = " << image << endl;
	}
	double real, image;
};

Complex operator +( Complex x, Complex y )
{
	Complex t;
	t.real = x.real + y.real;
	t.image = x.image + y.image;

	return t;
}

int main( )
{
	Complex c1( 1.0, 1.0 ), c2( 2.0, 3.0 );
	Complex sum = c1 + c2;
	// Alternative
	//Complex sum = operator+( c1, c2 );
	sum.print( );
	return 0;
}
