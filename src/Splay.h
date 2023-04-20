#ifndef SPLAY_H
#define SPLAY_H

struct Node {
    int value;
    Node* parent;
    Node* left;
    Node* right;

    Node(int v);
    ~Node();
};

class Splay {
public:
    Splay();
    ~Splay();
    bool procura(int value);
    void insert(int value);
    void remove(int value);
    void imprime(Node* node);
    Node* getRoot();
private:
    Node* root;
    void rota(Node* node);
    void splay(Node* node);
    Node* acha(int value);
    Node* achaMin(Node* node);
    void troca(Node* u, Node* v);
};

#endif