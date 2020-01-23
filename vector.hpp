// Generic Vector 2D C++ code
// Inherits from Matrix Class
// Sergio Herrera 
// 23/Jan/2020

#include "matrix.hpp"

#ifndef DEF_VECTOR
#define DEF_VECTOR

template <typename T>
class Vector : public Matrix<T>{
   private:
      void checkIFVector(int rows, int cols);

   public:
      Vector<T> (): Matrix<T>(){}
      Vector<T> (int rows, int cols);
      Vector<T> (Matrix<T> M);
};

template <typename T>
Vector<T>::Vector(int rows, int cols){
   checkIFVector(rows,cols);
      this->rows = rows;
      this->cols = cols;
      this->data = std::vector<std::vector<T> >(rows, std::vector<T>(cols));
}

template <typename T>
Vector<T>::Vector(Matrix<T> M){
   checkIFVector(M.getRows(),M.getCols());
      this->rows = M.getRows();
      this->cols = M.getCols();
      this->data = M.getData();
}

template <typename T>
void Vector<T>::checkIFVector(int rows, int cols){
   if(!(rows==1 || cols==1))
           throw std::invalid_argument("\n[!]The dimension values do not correspond to a vector!.");
}

#endif // DEF_VECTOR
