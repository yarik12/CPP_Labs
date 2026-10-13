#include <iostream>
#include <new>
#include <algorithm>
using namespace std;

class Matrix {
    long* data = nullptr;
    int rows = 0, cols = 0, error = 0;
public:
    Matrix() : Matrix(1, 1) {}
    explicit Matrix(int n) : Matrix(n, n) {}
    Matrix(int r, int c) {
        if (r <= 0 || c <= 0) { error = 3; return; }
        data = new(nothrow) long[r * c]();
        if (!data) { error = 1; return; }
        rows = r; cols = c;
    }
    Matrix(const Matrix& m) : Matrix(m.rows ? m.rows : 1, m.cols ? m.cols : 1) {
        if (!m.data) { delete[] data; data = nullptr; rows = cols = 0; error = m.error; }
        else if (!error) copy(m.data, m.data + rows * cols, data);
    }
    Matrix& operator=(const Matrix& m) {
        if (this == &m) return *this;
        long* p = m.data ? new(nothrow) long[m.rows * m.cols] : nullptr;
        if (m.data && !p) { error = 1; return *this; }
        if (p) copy(m.data, m.data + m.rows * m.cols, p);
        delete[] data; data = p; rows = m.rows; cols = m.cols; error = m.error;
        return *this;
    }
    ~Matrix() { delete[] data; }
    long get(int i, int j) {
        if (i < 0 || j < 0 || i >= rows || j >= cols) { error = 2; return 0; }
        error = 0; return data[i * cols + j];
    }
    long* address(int i, int j) {
        if (i < 0 || j < 0 || i >= rows || j >= cols) { error = 2; return nullptr; }
        error = 0; return &data[i * cols + j];
    }
    int getError() const { return error; }
    void print() const {
        if (!data) { cout << "Matrix error: " << error << '\n'; return; }
        for (int i=0;i<rows;++i) {
            for (int j=0;j<cols;++j) cout << data[i*cols+j] << ' ';
            cout << '\n';
        }
    }
    Matrix operator+(const Matrix& b) const {
        if (!data || !b.data || rows!=b.rows || cols!=b.cols) return Matrix(0, 0); // error 3
        Matrix r(rows, cols);
        if (r.data) for(int i=0;i<rows*cols;++i) r.data[i]=data[i]+b.data[i];
        return r;
    }
    Matrix operator-(const Matrix& b) const {
        if (!data || !b.data || rows!=b.rows || cols!=b.cols) return Matrix(0, 0);
        Matrix r(rows, cols);
        if (r.data) for(int i=0;i<rows*cols;++i) r.data[i]=data[i]-b.data[i];
        return r;
    }
    Matrix operator*(long x) const {
        if (!data) return Matrix(0, 0);
        Matrix r(rows, cols);
        if (r.data) for(int i=0;i<rows*cols;++i) r.data[i]=data[i]*x;
        return r;
    }
    Matrix operator*(const Matrix& b) const {
        if (!data || !b.data || cols!=b.rows) return Matrix(0, 0);
        Matrix r(rows, b.cols);
        if (r.data) for(int i=0;i<rows;++i)
            for(int j=0;j<b.cols;++j)
                for(int k=0;k<cols;++k) r.data[i*b.cols+j]+=data[i*cols+k]*b.data[k*b.cols+j];
        return r;
    }
};

int main() {
    Matrix a(2,2), b(2,2);
    *a.address(0,0)=1; *a.address(0,1)=2;
    *a.address(1,0)=3; *a.address(1,1)=4;
    *b.address(0,0)=5; *b.address(0,1)=6;
    *b.address(1,0)=7; *b.address(1,1)=8;
    cout << "A:\n"; a.print();
    cout << "A+B:\n"; (a+b).print();
    cout << "A-B:\n"; (a-b).print();
    cout << "A*B:\n"; (a*b).print();
    cout << "A*3:\n"; (a*3L).print();
    a.get(10,10); cout << "Out-of-range error: " << a.getError() << '\n';
    Matrix c(3,3); Matrix bad = a+c;
    cout << "Dimension error: " << bad.getError() << '\n';
}
