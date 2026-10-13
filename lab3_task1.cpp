#include <iostream>
#include <new>
#include <algorithm>
using namespace std;

class Vector {
    long* data = nullptr;
    int size = 0, error = 0;
    static int count;
public:
    Vector() : Vector(1, 0) {}
    explicit Vector(int n) : Vector(n, 0) {
        if (!error) for (int i = 0; i < size; ++i) data[i] = i;
    }
    Vector(int n, long value) {
        ++count;
        if (n <= 0) { error = 3; return; }
        data = new(nothrow) long[n];
        if (!data) { error = 1; return; }
        size = n;
        fill(data, data + size, value);
    }
    Vector(const Vector& other) : Vector(other.size > 0 ? other.size : 1, 0) {
        if (other.size == 0) { delete[] data; data = nullptr; size = 0; error = other.error; }
        else if (!error) copy(other.data, other.data + size, data);
    }
    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;
        long* temp = other.size ? new(nothrow) long[other.size] : nullptr;
        if (other.size && !temp) { error = 1; return *this; }
        if (temp) copy(other.data, other.data + other.size, temp);
        delete[] data; data = temp; size = other.size; error = other.error;
        return *this;
    }
    ~Vector() { delete[] data; --count; }
    void set(int i, long value = 0) {
        if (i < 0 || i >= size) { error = 2; return; }
        data[i] = value; error = 0;
    }
    long get(int i) {
        if (i < 0 || i >= size) { error = 2; return 0; }
        error = 0; return data[i];
    }
    int getError() const { return error; }
    static int objects() { return count; }
    void print() const {
        for (int i = 0; i < size; ++i) cout << data[i] << ' ';
        cout << "(error=" << error << ")\n";
    }
    Vector operator+(long x) const { Vector r(*this); for (int i=0;i<r.size;++i) r.data[i]+=x; return r; }
    Vector operator-(long x) const { Vector r(*this); for (int i=0;i<r.size;++i) r.data[i]-=x; return r; }
    Vector operator*(long x) const { Vector r(*this); for (int i=0;i<r.size;++i) r.data[i]*=x; return r; }
    bool operator==(const Vector& b) const {
        if (size != b.size) return false;
        for (int i=0;i<size;++i) if (data[i]!=b.data[i]) return false;
        return true;
    }
    bool operator<(const Vector& b) const {
        int n = min(size, b.size);
        for (int i=0;i<n;++i) if (data[i]!=b.data[i]) return data[i]<b.data[i];
        return size < b.size;
    }
    bool operator>(const Vector& b) const { return b < *this; }
};
int Vector::count = 0;

int main() {
    Vector a, b(5), c(3, 7);
    a.print(); b.print(); c.print();
    b.set(2, 20); b.print();
    cout << "b[2]=" << b.get(2) << '\n';
    (b + 10).print(); (b - 2).print(); (b * 3).print();
    cout << "b==c: " << (b==c) << ", b<c: " << (b<c) << ", b>c: " << (b>c) << '\n';
    b.set(99); cout << "Out-of-range error: " << b.getError() << '\n';
    cout << "Objects alive: " << Vector::objects() << '\n';
}
