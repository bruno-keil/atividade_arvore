#include "Splay.h"
#include <iostream>

using namespace std;

Splay::Splay() {
    root = nullptr;
}

Splay::~Splay(){
}

Node::Node(int v) : value(v), parent(nullptr), left(nullptr), right(nullptr){
}
Node::~Node() {
    delete left;
    delete right;
}

bool Splay::procura(int value){
    Node* node = acha(value);
    if(node) {
        splay(node);
        return true;
    }
    return false;
}

void Splay::insert(int value){
    Node* parent = nullptr;
    Node* current = root;

    while(current) {
        parent = current;
        if(value < current->value){
            current = current->left;
        }
        else if(value > current->value){
            current = current->right;
        }
        else
            return;
    }

    Node* node = new Node(value);
    node->parent = parent;

    if(!parent) {
        root = node;
    }
    else if (value < parent->value){
        parent->left = node;
    }
    else
        parent->right = node;

    splay(node);
}

void Splay::remove(int value){
    Node* node = acha(value);

    if(!node){
        return;
    }

    splay(node);

    if(!node->left){
        troca(node, node->right);
    }
    else if(!node->right){
        troca(node, node->left);
    }
    else{
        Node* minRight = achaMin(node->right);
        if(minRight -> parent != node){
            troca(minRight, minRight->right);
            minRight->right = node->right;
            minRight->right->parent = minRight;
        }
        troca(node, minRight);
        minRight->left = node->left;
        minRight->left->parent = minRight;
    }

        node->left = nullptr;
        node->right = nullptr;
        delete node;
}

void Splay::rota(Node* node) {
    Node* parent = node->parent;
    Node* grandparent = parent->parent;

    if(grandparent) {
        if(grandparent->left == parent) {
            grandparent->left = node;
        }
        else   
            grandparent->right = node;
    }

    if(parent->left == node){
        parent->left = node->right;
        if(node -> right) {
            node->right->parent = parent;
        }
        node->right = parent;
    }
    else{
        parent->right = node->left;
        if(node->left){
            node->left->parent = parent;
        }
        node->left = parent;
    }

    node->parent = grandparent;
    parent->parent = node;
}

void Splay::splay(Node* node){
    while(node->parent){
        Node* parent = node->parent;
        Node* grandparent = parent->parent;

        if(!grandparent){
            rota(node);
        }
        else if((grandparent->left) == parent == (parent->left == node)){
            rota(parent);
            rota(node);
        }
        else {
            rota(node);
            rota(node);
        }
    }
    root = node;
}

Node* Splay::acha(int value){
    Node* node = root;
    while(node){
        if(value < node->value){
            node = node->left;
        }
        else if(value > node->value){
            node = node->right;
        }
        else
            return node;
    }
    return nullptr;
}

Node* Splay::achaMin(Node* node){
    while(node->left){
        node = node->left;
    }
    return node;
}

void Splay::troca(Node* u, Node* v){
    if(!u->parent){
        root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else
        u->parent->right = v;
    if(v){
        v->parent = u->parent;
    }
}

void Splay::imprime(Node* node){
    if(node != nullptr){
        imprime(node->left);
        cout << node->value << " " << endl;
        imprime(node->right);
    }
}

Node* Splay::getRoot(){
    return this->root;
}


