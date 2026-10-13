#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int value;
    Node* left=nullptr;
    Node* right=nullptr;
};
void inorder(Node* p) { // left, root, right
    if (!p) return;
    inorder(p->left); cout << p->value << ' '; inorder(p->right);
}
void preorder(Node* p) { // root, left, right
    if (!p) return;
    cout << p->value << ' '; preorder(p->left); preorder(p->right);
}
void postorder(Node* p) { // left, right, root
    if (!p) return;
    postorder(p->left); postorder(p->right); cout << p->value << ' ';
}
int main() {
    int n; cout << "Number of nodes: "; cin >> n;
    if (!cin || n<0) return 1;
    vector<Node*> nodes;
    for (int i=0;i<n;++i) {
        int x; cout << "Value " << i+1 << ": "; cin >> x;
        if (!cin) { for(Node* p:nodes) delete p; return 1; }
        nodes.push_back(new Node{x});
    }
    for (int i=0;i<n;++i) {
        if (2*i+1<n) nodes[i]->left=nodes[2*i+1];
        if (2*i+2<n) nodes[i]->right=nodes[2*i+2];
    }
    Node* root=n ? nodes[0] : nullptr;
    cout << "Inorder (symmetric): "; inorder(root);
    cout << "\nPreorder (root-left-right): "; preorder(root);
    cout << "\nPostorder (left-right-root): "; postorder(root);
    cout << '\n';
    for(Node* p:nodes) delete p;
}
