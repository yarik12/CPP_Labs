#include <iostream>
#include <string>
using namespace std;

struct Athlete {
    string surname, sport;
    int points;
    Athlete* next;
};

void add(Athlete*& head, const string& name, const string& sport, int points) {
    Athlete* node=new Athlete{name,sport,points,nullptr};
    if (!head) { head=node; return; }
    Athlete* lastSame=nullptr;
    for (Athlete* p=head;p;p=p->next) if (p->sport==sport) lastSame=p;
    if (lastSame) { node->next=lastSame->next; lastSame->next=node; }
    else { Athlete* p=head; while(p->next) p=p->next; p->next=node; }
}
int main() {
    Athlete* head=nullptr;
    int n; cout << "Number of athletes: "; cin >> n;
    if (!cin || n<0) return 1;
    for(int i=0;i<n;++i) {
        string name,sport; int points;
        cout << "Surname: "; cin >> name;
        cout << "Sport: "; cin >> sport;
        cout << "Points: "; cin >> points;
        if (!cin) return 1;
        add(head,name,sport,points);
    }
    cout << "\nAthletes grouped by sport:\n";
    for(Athlete* p=head;p;p=p->next) cout << p->surname << " | " << p->sport << " | " << p->points << '\n';
    while(head) { Athlete* p=head; head=head->next; delete p; }
}
