#include <iostream>
using namespace std;

class Complex {
    double re, im;
public:
    Complex(double r=0, double i=0) : re(r), im(i) {}
    Complex operator+(Complex b) const { return {re+b.re, im+b.im}; }
    Complex operator-(Complex b) const { return {re-b.re, im-b.im}; }
    Complex operator*(Complex b) const { return {re*b.re-im*b.im, re*b.im+im*b.re}; }
    Complex operator/(Complex b) const {
        double d=b.re*b.re+b.im*b.im;
        if (d==0) { cout << "Division by zero\n"; return {}; }
        return {(re*b.re+im*b.im)/d, (im*b.re-re*b.im)/d};
    }
    Complex(const Complex&) = default;
    Complex& operator=(const Complex& b) { re=b.re; im=b.im; return *this; }
    Complex& operator+=(Complex b) { *this=*this+b; return *this; }
    Complex& operator-=(Complex b) { *this=*this-b; return *this; }
    Complex& operator*=(Complex b) { *this=*this*b; return *this; }
    Complex& operator/=(Complex b) { *this=*this/b; return *this; }
    bool operator==(Complex b) const { return re==b.re && im==b.im; }
    bool operator!=(Complex b) const { return !(*this==b); }
    friend Complex operator+(Complex a) { return a; }
    friend Complex operator-(Complex a) { return {-a.re,-a.im}; }
    friend ostream& operator<<(ostream& out, const Complex& a) {
        return out << a.re << (a.im<0 ? " - " : " + ") << (a.im<0 ? -a.im : a.im) << 'i';
    }
    friend istream& operator>>(istream& in, Complex& a) { return in >> a.re >> a.im; }
};

Complex operator+(double x, const Complex& a) { return Complex(x) + a; }
Complex operator-(double x, const Complex& a) { return Complex(x) - a; }

int main() {
    Complex a(3,2), b(1,4);
    cout << "a=" << a << ", b=" << b << '\n';
    cout << "a+b=" << a+b << "\na-b=" << a-b << '\n';
    cout << "a*b=" << a*b << "\na/b=" << a/b << '\n';
    cout << "a+5=" << a+5.0 << "\n5+a=" << 5.0+a << '\n';
    cout << "a-5=" << a-5.0 << "\n5-a=" << 5.0-a << '\n';
    cout << "-a=" << -a << '\n';
    a += b; cout << "a+=b: " << a << '\n';
}
