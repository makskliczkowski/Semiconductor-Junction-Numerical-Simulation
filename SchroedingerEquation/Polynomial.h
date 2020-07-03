#pragma once
#include <iostream>
#include <math.h>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <exception>
#include <vector>
using std::vector;
//typedef enum { READ_ERROR, READ_INT, READ_STRING } readValue_t;
//readValue_t getIntOrString(string txt, unsigned int& n, string& s);
//namespace PolynomialNamespace {
class Polynomial
    {
    private:
        int degree; //degree
        std::vector<double> coefficients; //Polynomial coeff
    public:
        unsigned int degree2;
        Polynomial();
        Polynomial(int n);
        ~Polynomial();
        //----------setters-----------------------------------
        void setCoefficient(int i, double value);//sets value on ith position
        //----------getters----------------------
        double getCoefficient(int i);
        int getDegree();
        double getValue(double x); //value for x
        //----------methods and operators-----------------------------
        float operator [](const int& d); //gets given coefficient at d position

        double operator () (const double& d);//also gets value

        Polynomial& operator = (const Polynomial& a);

        Polynomial& operator -();

        //-------------friends---------------------------------------


        friend Polynomial operator + (const Polynomial& a, const Polynomial& b);//sum

        friend Polynomial operator - (const Polynomial& a, const Polynomial& b);//difference

        friend Polynomial operator * (const Polynomial& b, const double& a); //multiplying by constant

        /*00000000000000000000000000000000000000000000000000000000templete000000000000000000000000000000*/
        /*template<typename D> Polynomial & operator *(const D &a)
        {
            Polynomial c(1);
            c = *this;
            for(int i = 0; i <= c.degree; i++)
            {
                c.coefficients[i]= (a * c.coefficients[i]);
            }
            return c;
        }*/
        /*template<typename T> friend Polynomial operator *(const Polynomial& b, const T& a)
        {
            Polynomial c(1);
            c = b;
            for (int i = 0; i <= b.degree; i++)
            {
                c.coefficients[i] = (a * c.coefficients[i]);
            }
            return c;
        }

        /*0000000000000000000000000000000000000000000000000000000000000*/
        friend Polynomial operator * (const Polynomial & a, const Polynomial & b);

        

    };
    //std::istream& operator >> (istream& in, Polynomial& a);
    //std::ostream& operator << (ostream& out, Polynomial& w); //writing to ostream

//}