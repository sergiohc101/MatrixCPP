// Generic Matriz 2D C++ code
// Sergio Herrera 
// 23/Jan/2020

#ifndef DEF_MATRIX
#define DEF_MATRIX

#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>

template <typename T>
class Matrix{
    protected:
        std::vector<std::vector<T> > data;
        int rows;
        int cols;

    public:
        Matrix<T> ();
        Matrix<T> (int rows, int cols);
        Matrix<T> (std::vector<std::vector<T> > const &data);

        template <typename T2>
        Matrix<T> (Matrix<T2> M){ //Casting constructor from other type
            this->rows = M.getRows();
            this->cols = M.getCols();     
            this->data = std::vector<std::vector<T> >(rows, std::vector<T>(cols));               
            for (int i=0 ; i<M.getRows(); i++){
                for (int j=0 ; j<M.getCols() ; j++){
                    this->data[i][j] = static_cast< T >( M.get(i,j) );
                }
            }
        };

        int getRows() const;
        int getCols() const;
        std::vector<std::vector<T> > getData() const;

        Matrix<T> add(const Matrix<T>& m) const;
        Matrix<T> subtract(const Matrix<T>& m) const;
        Matrix<T> dot(const Matrix<T>& m) const;
        Matrix<T> transpose() const;
        Matrix<T> multiply(const T& value) const;
        Matrix<T> divide(const T& value) const;

        Matrix<T> applyFunction(T (*function)(T)) const;
        Matrix<T> subMat(int startH, int startW, int h, int w) const;

        void fill(const T& value);
        void set(int h, int w, const T& value);
        T get(int h, int w) const;

        void print(std::ostream &flux) const;

        bool operator==(const Matrix<T>& m);
        bool operator!=(const Matrix<T>& m);
        Matrix<T> operator+=(const Matrix<T>& m);
        Matrix<T> operator-=(const Matrix<T>& m);
        Matrix<T> operator*=(const Matrix<T>& m);
        Matrix<T> operator*=(const T &m);
        Matrix<T> operator/=(const T &m);
        T& operator()(int y, int x);

};

template <typename T> Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b);
template <typename T> Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b);
template <typename T> Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b);
template <typename T> Matrix<T> operator*(const T &b, const Matrix<T>& a);
template <typename T> Matrix<T> operator/(const Matrix<T>& a, const T &b);
template <typename T> std::ostream& operator<<(std::ostream &out, const Matrix<T>& m);


////////////////
//Constructors
////////////////

template <typename T>
Matrix<T>::Matrix(){
    rows = 0;
    cols = 0;
}

template <typename T>
Matrix<T>::Matrix(int rows, int cols){
    this->rows = rows;
    this->cols = cols;
    this->data = std::vector<std::vector<T> >(rows, std::vector<T>(cols));
}

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T> > const &data){
    if(data.size()==0)
        throw std::invalid_argument("\n[!]Size of data must be greater than 0.");

    this->rows = data.size();
    this->cols = data[0].size();
    this->data = data;
}


////////////////
//Getters
////////////////

template <typename T>
int Matrix<T>::getRows() const{
    return rows;
}

template <typename T>
int Matrix<T>::getCols() const{
    return cols;
}

template <typename T>
std::vector<std::vector<T> > Matrix<T>::getData() const{
    return data;
}


////////////////
//Functions
////////////////

template <typename T>
void Matrix<T>::fill(const T& value){
    for (int i=0 ; i<rows ; i++){
        for (int j=0 ; j<cols ; j++){
            data[i][j] = value;
        }
    }
}

template <typename T>
void Matrix<T>::set(int row, int col, const T& value){
    if(!(row>=0 && row<rows && col>=0 && col<cols))
        throw std::invalid_argument("\n[!]Index out of bounds.");

    data[row][col] = value;
}

template <typename T>
T Matrix<T>::get(int row, int col) const{
    if(!(row>=0 && row<rows && col>=0 && col<cols))
        throw std::invalid_argument("\n[!]Index out of bounds.");

    return data[row][col];
}

template <typename T>
Matrix<T> Matrix<T>::multiply(const T& value) const{
    Matrix result(data);
    for (int i=0 ; i<rows ; i++){
        for (int j=0 ; j<cols ; j++){
            result.data[i][j] *= value;
        }
    }

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::divide(const T& value) const{
    Matrix result(data);
    for (int i=0 ; i<rows ; i++){
        for (int j=0 ; j<cols ; j++){
            result.data[i][j] /= value;
        }
    }

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::add(const Matrix& M) const{
    if(!(rows==M.rows && cols==M.cols))
        throw std::invalid_argument("\n[!]Matrix dimension must be the same.");

    Matrix result(rows, cols);
    for (int i=0 ; i<rows ; i++){
        for (int j=0 ; j<cols ; j++){
            result.data[i][j] = data[i][j] + M.data[i][j];
        }
    }

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::subtract(const Matrix& M) const{
    if(!(rows==M.rows && cols==M.cols))
        throw std::invalid_argument("\n[!]Matrix dimension must be the same.");

    Matrix result(rows, cols);
    for (int i=0 ; i<rows ; i++){
        for (int j=0 ; j<cols ; j++){
            result.data[i][j] = data[i][j] - M.data[i][j];
        }
    }
    return result;
}


template <typename T>
Matrix<T> Matrix<T>::dot(const Matrix& M) const{
    if(!(cols==M.rows))
        throw std::invalid_argument("\n[!]Dot product not compatible.");

    T w=0;
    int mcols = M.cols;

    Matrix<T> result(rows, mcols);
    for (int i=0 ; i<rows ; i++){
        for (int j=0 ; j<mcols ; j++){
            for (int h=0 ; h<cols ; h++){
                w += data[i][h] * M.data[h][j];
            }
            result.data[i][j] = w;
            w=0;
        }
    }

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const{
    Matrix<T> result(cols, rows);

    for (int i=0 ; i<cols ; i++){
        for (int j=0 ; j<rows ; j++){
            result.data[i][j] = data[j][i];
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::applyFunction(T (*function)(T)) const{
    Matrix<T> result(rows, cols);

    for (int i=0 ; i<rows ; i++){
        for (int j=0 ; j<cols ; j++){
            result.data[i][j] = (*function)(data[i][j]);
        }
    }

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::subMat(int startRow, int startCol, int nRows, int nCols) const{
    if(!(startRow>=0 && startRow+nRows<=rows && startCol>=0 && startCol+nCols<=cols))
        throw std::invalid_argument("\n[!]Index out of bounds");

    Matrix<T> result(nRows,nCols);
    for (int i=startRow ; i<startRow+nRows ; i++){
        for (int j=startCol ; j<startCol+nCols ; j++){
            result.data[i-startRow][j-startCol] = data[i][j];
        }
    }
    return result;
}

template <typename T>
void Matrix<T>::print(std::ostream &out) const{
    for (int i=0 ; i<rows ; i++){
        for (int j=0 ; j<cols ; j++){
            out << data[i][j] << " ";
        }
        out << std::endl;
    }
}


////////////////
//Operators
////////////////


template <typename T>
bool Matrix<T>::operator==(const Matrix& M){
    if(rows==M.rows && cols==M.cols){
        for (int i=0 ; i<rows ; i++){
            for (int j=0 ; j<cols ; j++){
                if(data[i][j]!=M.data[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix& M){
    return !operator==(M);
}

template <typename T>
Matrix<T> Matrix<T>::operator+=(const Matrix& M){
    this->data = add(M).data;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-=(const Matrix& M){
    this->data = subtract(M).data;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*=(const Matrix& M){
    this->data = multiply(M).data;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*=(const T &V){
    *this = this->multiply(V);
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator/=(const T &V){
    *this = this->divide(V);
    return *this;
}

template <typename T>
T& Matrix<T>::operator()(int y, int x){
    if(!(y>=0 && y<rows && x>=0 && x<cols))
        throw std::invalid_argument("\n[!]Index out of bounds.");
    return data[y][x];
}

template <typename T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b){
    return a.add(b);
}

template <typename T>
Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b){
    return a.subtract(b);
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b){
    return a.dot(b);
}

template <typename T>
Matrix<T> operator* (const T &b, const Matrix<T>& a){
    return a.multiply(b);
}
template <typename T>
Matrix<T> operator/ (const Matrix<T>& a, const T &b){
    return a.divide(b);
}

template <typename T>
std::ostream& operator<< (std::ostream &out, const Matrix<T> &M){
    M.print(out);
    return out;
}


#endif //DEF_MATRIX


