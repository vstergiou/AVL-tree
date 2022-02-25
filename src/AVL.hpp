
//Implementation of AVL Tree

#ifndef __AVL_HPP_
#define __AVL_HPP_

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <stack>

using namespace std;

class AVL {
private:
  class Node {
    Node* parent, *left, *right;
    int height;
    string element;

  public:
    Node(const string& e, Node* parent, Node* left, Node* right);
    Node();

    Node*  getParent() const;
    Node*  getLeft() const;
    Node*  getRight() const;
    string getElement() const;
    int    getHeight() const;

    void setLeft(Node* );
    void setRight(Node* );
    void setParent(Node* );
    void setElement(string e);
    void setHeight(int h);

    bool isLeft() const;
    bool isRight() const;
    bool isRoot() const;
    int  rightChildHeight() const;
    int  leftChildHeight() const;
    int  updateHeight();
    bool isBalanced();

    void preorder_node(Node* ,ostream&);

    void preorder_for_stack(Node*,stack<Node*>*);


  };
private:

  int   size;
  Node* root;


  public:

    class Iterator {

    public:
      stack<Node*> nodeStack;
      Iterator();
      Iterator(const Iterator& );
      Iterator& operator++();
      Iterator operator++(int a);
      string operator*();
      bool operator!=(Iterator it);
      bool operator==(Iterator it);
    };

  Iterator begin() const;
  Iterator end() const;

  static const int MAX_HEIGHT_DIFF = 1;
  AVL();
  AVL(const AVL& );


  Node* single_right_rotate(Node*);
  Node* single_left_rotate(Node*);

  bool add(string);
  bool rmv(string e);

  Node* insert_to_tree(Node* ,string);
  Node* delete_from_tree(Node*,string);
  Node* balance(Node* );
  bool contains(string e);

  void preorder(Node* ,ostream&);
  void pre_order(std::ostream& out);

  void preorder_to_string(Node*,string *&,int &);

  void print2DotFile(const char *filename);
  string dot(Node*,int,char*,ofstream&);

  Node* findNode(string, Node*);

  int balance_tree(Node *);

  stack<Node*> stack_creator(Node*) const;


  friend std::ostream& operator<<(std::ostream& out, const AVL& tree);
  AVL& operator =(const AVL& avl);
  AVL  operator +(const AVL& avl);
  AVL& operator+=(const AVL& avl);
  AVL& operator+=(const string& e);
  AVL& operator-=(const string& e);
  AVL  operator +(const string& e);
  AVL  operator -(const string& e);
};
#endif
