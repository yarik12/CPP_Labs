#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Product {
    string name, manufacturer;
    double price = 0;
    int shelfLife = 0, quantity = 0;
public:
    void set(const string& n, const string& m, double p, int s, int q) {
        name = n; manufacturer = m; price = p; shelfLife = s; quantity = q;
    }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getShelfLife() const { return shelfLife; }
    void show() const {
        cout << name << " | " << manufacturer << " | " << price
             << " RUB | " << shelfLife << " days | " << quantity << " pcs\n";
    }
};

int main() {
    int n;
    cout << "Number of products: "; cin >> n;
    if (!cin || n < 0) return 1;
    vector<Product> products(n);
    for (int i = 0; i < n; ++i) {
        string name, maker;
        double price; int shelf, count;
        cout << "Product " << i + 1 << " (name, manufacturer, price, shelf life, quantity):\n";
        cin >> ws; getline(cin, name);
        getline(cin, maker);
        cin >> price >> shelf >> count;
        if (!cin || price < 0 || shelf < 0 || count < 0) return 1;
        products[i].set(name, maker, price, shelf, count);
    }
    string target; double limit; int days;
    cout << "Search name: "; cin >> ws; getline(cin, target);
    cout << "a) Matching name:\n";
    for (const auto& p : products) if (p.getName() == target) p.show();
    cout << "Maximum price: "; cin >> limit;
    cout << "b) Matching name and price:\n";
    for (const auto& p : products) if (p.getName() == target && p.getPrice() <= limit) p.show();
    cout << "Shelf life threshold (days): "; cin >> days;
    cout << "c) Longer shelf life:\n";
    for (const auto& p : products) if (p.getShelfLife() > days) p.show();
}
