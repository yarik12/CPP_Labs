#include <iostream>
#include <cstring>
using namespace std;

class String {
    char* data;
public:
    String() : String("") {}
    String(const char* s) {
        if (!s) s="";
        data = new char[strlen(s)+1];
        strcpy(data,s);
    }
    String(const String& s) : String(s.data) {}
    ~String() { delete[] data; }
    String& operator=(const String& s) {
        if (this != &s) {
            char* p = new char[strlen(s.data)+1];
            strcpy(p,s.data); delete[] data; data=p;
        }
        return *this;
    }
    int compare(const String& s) const { return strcmp(data,s.data); }
    int find(const String& s) const {
        const char* p=strstr(data,s.data);
        return p ? static_cast<int>(p-data) : -1;
    }
    size_t length() const { return strlen(data); }
    void show() const { cout << data << '\n'; }
};

int main() {
    String a("Hello world"), b("world"), c(a), d;
    d=b;
    cout << "a: "; a.show();
    cout << "Copy: "; c.show();
    cout << "Assigned: "; d.show();
    cout << "Length: " << a.length() << '\n';
    cout << "Substring position: " << a.find(b) << '\n';
    cout << "Compare a and b: " << a.compare(b) << '\n';
}
