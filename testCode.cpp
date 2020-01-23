// Test code for Matrix and Vector classes
// Sergio Herrera 
// 23/Jan/2020

#include <iostream>
#include <iomanip>

#include "matrix.hpp"
#include "vector.hpp"

using namespace std;

int main()
{
   std::cout << "Hello World!! \t This is a test code: \n" ;

   Matrix<int> A(3,2);
   Matrix<int> B(2,3);
   Matrix<int> C(2,3);

   A.fill(7);
   B.fill(5);
   C.fill(3);

   Matrix<int> D = C + B;  // Addition
   Matrix<int> Z = A * B;  // Dot product

   std::cout << "D= \n" << D << endl;
   std::cout << "Z= \n" << Z << endl;

   //Vectors must be unidimensional in either dimension
   Vector<int> a(3,1);  
   Vector<int> b(1,3);

   a.fill(3);
   b.fill(5);

   std::cout << "a= \n" << a << endl;
   std::cout << "b= \n" << b << endl;

   Vector<int> c = (3 * a);   //Scalar x Vector multiplication

   Vector<int> d = B * a;     //Matrix x Vector multiplication

   std::cout << "c= \n" << c << endl;
   std::cout << "d= \n" << d << endl;

   //We can instantiate other types using the generic classes
   Matrix<double> DouV (3,1);
   DouV.fill(3.1415926535);
   std::cout << std::fixed << std::setprecision(10);
   std::cout << "(double)Vector= \n" << DouV << endl;
   
   //The class also supports casting among different types
   Matrix<int> IntV = DouV; //Cast double to int
   std::cout << "(int)Vector= \n" << IntV << endl;

   Matrix<float> FloV = IntV; //Cast int to float
   std::cout << "(float)Vector= \n" << FloV << endl;
   
   return 0;
}


