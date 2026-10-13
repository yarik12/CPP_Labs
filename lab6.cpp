#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct File {
    string name, date; // YYYY-MM-DD
    int accesses;
    File* next;
};

bool validDate(const string& d) {
    if (d.size()!=10 || d[4]!='-' || d[7]!='-') return false;
    for (int i=0;i<10;++i) if (i!=4 && i!=7 && (d[i]<'0'||d[i]>'9')) return false;
    int y=stoi(d.substr(0,4)), m=stoi(d.substr(5,2)), day=stoi(d.substr(8,2));
    if (y<1 || m<1 || m>12) return false;
    int days[]={31,28+(y%4==0 && (y%100!=0 || y%400==0)),31,30,31,30,31,31,30,31,30,31};
    return day>=1 && day<=days[m-1];
}
int readInt(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin>>x && x>=0) return x;
        cout << "Invalid number\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
}
string readDate() {
    string d;
    do { cout << "Date (YYYY-MM-DD): "; cin >> d;
         if (!validDate(d)) cout << "Invalid date\n";
    } while (!validDate(d));
    return d;
}
File* makeFile() {
    File* p=new File;
    cout << "File name: "; cin >> p->name;
    p->date=readDate(); p->accesses=readInt("Access count: "); p->next=nullptr;
    return p;
}
File* findFile(File* head, const string& name) {
    for (File* p=head;p;p=p->next) if (p->name==name) return p;
    return nullptr;
}
void show(File* head) {
    if (!head) cout << "Catalog is empty\n";
    for (File* p=head;p;p=p->next)
        cout << p->name << " | " << p->date << " | " << p->accesses << '\n';
}
void clear(File*& head) {
    while (head) { File* p=head; head=head->next; delete p; }
}
int main() {
    File* head=nullptr;
    while (true) {
        cout << "\n1 Initial catalog  2 Insert before  3 Insert after\n"
                "4 Show  5 Delete older than date  6 Most accessed  0 Exit\n";
        int choice=readInt("Choice: ");
        if (choice==0) break;
        if (choice==1) {
            clear(head);
            int n=readInt("File count: ");
            File** tail=&head;
            for (int i=0;i<n;++i) { *tail=makeFile(); tail=&((*tail)->next); }
        } else if (choice==2 || choice==3) {
            string target; cout << "Target file name: "; cin >> target;
            File* found=findFile(head,target);
            if (!found) { cout << "File not found\n"; continue; }
            File* p=makeFile();
            if (choice==3) { p->next=found->next; found->next=p; }
            else if (head==found) { p->next=head; head=p; }
            else {
                File* prev=head;
                while (prev->next!=found) prev=prev->next;
                p->next=found; prev->next=p;
            }
        } else if (choice==4) show(head);
        else if (choice==5) {
            string date=readDate();
            while (head && head->date<date) { File* p=head; head=head->next; delete p; }
            for (File* p=head;p && p->next;) {
                if (p->next->date<date) { File* q=p->next; p->next=q->next; delete q; }
                else p=p->next;
            }
        } else if (choice==6) {
            if (!head) { cout << "Catalog is empty\n"; continue; }
            File* best=head;
            for (File* p=head->next;p;p=p->next) if (p->accesses>best->accesses) best=p;
            cout << best->name << " | " << best->date << " | " << best->accesses << '\n';
        } else cout << "Unknown command\n";
    }
    clear(head);
}
