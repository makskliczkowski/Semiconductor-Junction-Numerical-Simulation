using namespace std;
#include "Polynomial.h"

//using namespace PolynomialNamespace;

//----------------------CONSTRUCTORS And Destructor--------------------------------
Polynomial::Polynomial()
{
    this->degree = 5;
    this->degree2 = 5;
    for (int i = 0; i <= this->degree; i++) {
        coefficients.push_back(0);
    }
}

Polynomial::Polynomial(int n)
{
    //wyj[0] = "ujemny stopien";
    //wyj[1] = "stopien niecalkowity";
    //wyj[2] = "nie moze byc litera";
    //wyj[3] = "poza tablica";
    if (n < 0)
    {
        fprintf(stderr, "Erro in %s line %d\n", __FILE__, __LINE__);
    }
    int b = n;
    if ((b - n) != 0)
    {
        fprintf(stderr, "Erro in %s line %d\n", __FILE__, __LINE__);
    }
    this->degree = n;
    this->degree2 = n;
    for (int i = 0; i <= this->degree; i++) {
        coefficients.push_back(0);
    }
}

Polynomial::~Polynomial()
{
    coefficients.clear();
}

//----------------------setters----------------------------------------------------
void Polynomial::setCoefficient(int i, double value)// na itej pozycji ustawia wartoœæ
{
    if (isalpha(i))
    {
        fprintf(stderr, "Blad w %s w linii %d\n", __FILE__, __LINE__);
    }
    if (i < 0 || i > this->degree)
    {
        fprintf(stderr, "Blad w %s w linii %d\n", __FILE__, __LINE__);
    }
    this->coefficients[i] = value;
}
//------------------------getters---------------------------------------------------
double Polynomial::getCoefficient(int i)
{
    if (i < 0 || i > this->degree)
    {
        fprintf(stderr, "Blad w %s w linii %d\n", __FILE__, __LINE__);
    }
    return this->coefficients[i];
}

int Polynomial::getDegree()
{
    return this->degree;
}

double Polynomial::getValue(double x) //value for given x
{
    double suma;
    suma = coefficients[0];
    for (int j = 1; j <= this->degree; j++)
    {
        suma = suma + pow(x, j) * (coefficients[j]);
    }
    return suma;
}
//-------------------------methods and inside operators--------------------------

float Polynomial::operator[](const int& d)
{
        if (d < 0 || d> this->degree2)
        {
            throw "Out of range\n";
        }
        return this->coefficients[d];
}

double Polynomial::operator()(const double& d)
{
        if (isalpha(d))
        {
            throw "Cannot give you a letter!:C\n";
        }
        return this->getValue(d);
}

Polynomial& Polynomial::operator=(const Polynomial& a)
{

    this->coefficients.clear();
    this->degree = a.degree;
    this->degree2 = a.degree;
    this->coefficients = a.coefficients;
    return *this;
}

Polynomial& Polynomial::operator-()
{
    for (int i = 0; i <= degree; i++)
    {
        this->coefficients[i] = -(this->coefficients[i]);
    }
    return (*this);
}




//-------------------------friends-----------------------
/*ostream & operator<<(ostream& out, Polynomial& w)
{
    out << w.getCoefficient(0) << " + " << w.getCoefficient(1) << "x + ";
    for (unsigned int i = 2; i <= w.getDegree(); i++)
    {
        out << w.getCoefficient(i) << "x^" << i << " + ";
    }
    out << " 0" << endl;

    return out;
}
*/
Polynomial operator+(const Polynomial& a, const Polynomial& b)
{
        Polynomial d(1);
        if (a.degree <= b.degree)
        {
            d = b;
            for (int i = 0; i <= a.degree; i++)
            {
                d.coefficients[i] = (a.coefficients[i]) + (b.coefficients[i]);
            }
        }
        else
        {
            d = a;
            for (int i = 0; i <= b.degree; i++)
            {
                d.coefficients[i] = a.coefficients[i] + b.coefficients[i];
            }
        }
        return d;
}

Polynomial operator-(const Polynomial& a, const Polynomial& b)
{
    Polynomial e(1);
    if (a.degree <= b.degree)
    {
        e = b;
        for (int i = 0; i <= a.degree; i++)
        {
            e.coefficients[i] = a.coefficients[i] - b.coefficients[i];
        }
    }
    else
    {
        e = a;
        for (int i = 0; i <= b.degree; i++)
        {
            e.coefficients[i] = a.coefficients[i] - b.coefficients[i];
        }
    }
    return (e);
}

Polynomial operator*(const Polynomial& b, const double& a)
{
    if (isalpha(a))
    {
        throw "Not letter!!\n";
    }
    Polynomial c(1);
    c = b;
    for (int i = 0; i <= b.degree; i++)
    {
        c.coefficients[i] = (a * (c.coefficients[i]));
    }
    return (c);
}

Polynomial operator*(const Polynomial& a, const Polynomial& b)
{
    Polynomial w(a.degree + b.degree);
    for (int k = 0; k <= a.degree + b.degree; k++)
    {
        w.coefficients[k] = 0;
    }
    for (int i = 0; i <= a.degree; i++)
    {
        for (int j = 0; j <= b.degree; j++)
        {
            w.coefficients[i + j] += a.coefficients[i] * b.coefficients[j];
        }
    }
    return w;
}

/*istream &  operator>>(istream& in, Polynomial& a)
{
    string d;
    cout << "Polynomial coefficients are?\n";
    for (int i = 0; i < (a.getDegree() + 1); i++)
    {
        cin >> d;
        float g;
        g = atof(d.c_str());
        a.setCoefficient(i, g);
    }
    return in;
}
*/
