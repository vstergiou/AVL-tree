
//Implementation of AVL Tree

#include "AVL.hpp"

//--------------Node Constructors and Functions----------------------------

AVL::Node::Node(const string& e, Node* parent, Node* left, Node* right){
   this->setLeft(left);
   this->setRight(right);
   this->setParent(parent);
   this->setElement(e);
}
AVL::Node::Node(){
   this->setLeft(nullptr);
   this->setRight(nullptr);
   this->setParent(nullptr);
   this->setElement("");
   this->setHeight(1);
}

//SET METHODS
void AVL::Node::setLeft(Node* left){
  this->left = left;
}

void AVL::Node::setRight(Node* right){
  this->right = right;
}

void AVL::Node::setParent(Node* parent){
  this->parent = parent;
}

void AVL::Node::setElement(string e){
  this->element = e;
}

void AVL::Node::setHeight(int h){
  this->height = h;
}

//GET METHODS
AVL::Node* AVL::Node::getLeft() const{
  return this->left;
}

AVL::Node* AVL::Node::getRight() const{
  return this->right;
}

AVL::Node* AVL::Node::getParent() const{
  return this->parent;
}

int AVL::Node::getHeight() const{
  if (this == nullptr)
    return 0;
  return this->height;
}

string AVL::Node::getElement() const {
  if (this == nullptr)
    return "";
  return this->element;
}

//Other methods

bool AVL::Node::isLeft() const{
  if (this->isRoot()) return false;

  return (this == this->getParent()->getLeft());
}

bool AVL::Node::isRight() const{
  if (this->isRoot()) return false;

  return (this == this->getParent()->getRight());
}

bool AVL::Node::isRoot() const{
  if (this->getParent() == nullptr)
    return true;
  return false;
}

int AVL::Node::leftChildHeight() const{
  if(this->getLeft() != nullptr)
    return (this->getLeft()->getHeight());
  else
    return 0;
}

int AVL::Node::rightChildHeight() const{
  if(this->getRight() != nullptr)
    return (this->getRight()->getHeight());
  else
    return 0;
}

bool AVL::Node::isBalanced(){
    int balance = (this->leftChildHeight()) - (this->rightChildHeight());
    return ((-1<=balance)&&(balance<=1));
}

void AVL::Node::preorder_node(Node* root,ostream& out){
   if (root == nullptr)
       return;
   out<< root->getElement() << " ";
   preorder_node(root->getLeft(),out);
   preorder_node(root->getRight(),out);

}

int AVL::Node::updateHeight(){
  int node_height = 0;
  if (this != nullptr){
    int left_height = this->getLeft()->updateHeight();
    int right_height = this->getRight()->updateHeight();

    if(left_height > right_height)
      node_height = left_height+1;
    else
      node_height = right_height+1;

    this->setHeight(node_height);
  }
  return node_height;
}

void AVL::Node::preorder_for_stack(Node* node,stack<Node*>* stack){
  if (node == nullptr)
      return;

  stack->push(node);
  preorder_for_stack(node->getLeft(),stack);
  preorder_for_stack(node->getRight(),stack);

}



//-------------------AVL-------------------------
AVL::AVL(){
  root = nullptr;
  size = 0;
}

AVL::AVL(const AVL& avltree){
  root = nullptr;
  size = 0;
  string *str = new string[avltree.size];
  int i = 0;
  preorder_to_string(avltree.root,str,i);
  for (int j=0;j<i;j++){
    this->add(str[j]);
    size++;
  }
}

bool AVL::add(string e){
  if (this->contains(e))
    return false;
  root = insert_to_tree(root, e);
  size++;
  return true;
}

bool AVL::rmv(string e){

  if(this->contains(e)){
    this->root = delete_from_tree(this->root,e);
    size--;
    return true;
  }
  return false;
}

bool AVL::contains(string item){
  Node* node = findNode(item,this->root);

  if (node->getElement() == item)
    return true;
  else
    return false;
}

void AVL::print2DotFile(const char *filename){
 ofstream myfile;
 myfile.open(filename);
 myfile << "digraph AVL {\n";
 myfile <<  "fontcolor=\"navy\";\n";
 myfile <<  "fontsize=20;\n";
 myfile <<  "labelloc=\"t\";\n";
 myfile <<  "label=\"Michalis Charatzoglou\nAVL Tree\"\n";

 char* str = (char*)malloc(sizeof(char)*4096);
 dot(root,1,str,myfile);
 free(str);
 myfile << "}";
}

void AVL::pre_order(std::ostream& out){
  preorder(this->root,out);
}

void AVL::preorder_to_string(Node* temp,string *&output,int &i){
  if (temp == nullptr)
    return;
  stack<Node *> nodeStack;
  nodeStack.push(temp);

  while (nodeStack.empty() == false){

    struct Node *node = nodeStack.top();
    output[i] = node->getElement();
    i++;
    nodeStack.pop();
    if (node->getRight())
    nodeStack.push(node->getRight());
    if (node->getLeft())
    nodeStack.push(node->getLeft());
  }
}

stack<AVL::Node*> AVL::stack_creator(Node * temp) const{
  stack<Node*> nodeStack;
  stack<Node*> tempStack;

  if (temp == nullptr)
     return nodeStack;

  temp->preorder_for_stack(temp,&nodeStack);

  while(!nodeStack.empty()){
    tempStack.push(nodeStack.top());
    nodeStack.pop();
  }
  return tempStack;
}

AVL::Node* AVL::findNode(string key, Node* node){

  if(node == nullptr)
    return nullptr;
  string temp = node->getElement();
  if(std::string(key) < std::string(temp)){

    if (node->getLeft() == nullptr)
      return node;
    else
      return findNode(key,node->getLeft());
  }
  else if (std::string(key) == std::string(temp))
    return node;
  else{
    if (node->getRight() == nullptr)
      return node;
    else
      return findNode(key,node->getRight());
  }

}

AVL::Node* AVL::insert_to_tree(Node* node,string key){
  if (node == nullptr)
    return (new Node(key,nullptr,nullptr,nullptr));
  if(string(key) < string(node->getElement()))
    node->setLeft(insert_to_tree(node->getLeft(),key));
  else if (string(key) > string(node->getElement()))
    node->setRight(insert_to_tree(node->getRight(),key));
  else
    return node;

  node->setHeight(max(node->getLeft()->updateHeight(),node->getRight()->updateHeight()) + 1);

  int balance = balance_tree(node);
  if (balance > 1 && string(key) < string(node->getLeft()->getElement()))
      return single_right_rotate(node);


  if (balance < -1 && string(key) > string(node->getRight()->getElement()))
      return single_left_rotate(node);

  if (balance > 1 && string(key) > string(node->getLeft()->getElement())){
      node->setLeft(single_left_rotate(node->getLeft()));
      return single_right_rotate(node);
  }

  if (balance < -1 && string(key) < string(node->getRight()->getElement()))  {
      node->setRight(single_right_rotate(node->getRight()));
      return single_left_rotate(node);
  }

  return node;
}

AVL::Node* AVL::delete_from_tree(Node* node,string value){
  if (node == nullptr)
      return node;

  if (std::string(value) < std::string(node->getElement()))
      node->setLeft(delete_from_tree(node->getLeft(), value));

  else if (std::string(value) > std::string(node->getElement()))
      node->setRight(delete_from_tree(node->getRight(),value));

  else{
    if((node->getLeft() == nullptr) || (node->getRight() == nullptr)){

      Node *temp;

      if (node->getLeft() == nullptr)
        temp = node->getRight();
      else
        temp = node->getLeft();

      if(temp == nullptr){
        temp = node;
        node = nullptr;
      }
      else
        *node = *temp;

      free(temp);
    }
    else{

      Node* iterate = node->getRight();
      while (iterate->getLeft() != nullptr)
          iterate = iterate->getLeft();

      Node* temp = iterate;

      node->setElement(temp->getElement());
      node->setRight(delete_from_tree(node->getRight(),temp->getElement()));
    }
  }

  if (node == nullptr)
    return node;
  if(node->getLeft()->getHeight() > node->getRight()->getHeight())
    node->setHeight(1 + node->getLeft()->getHeight());
  else
    node->setHeight(1 + node->getRight()->getHeight());

  int balancer = balance_tree(node);

  if ((balancer > 1) && (balance_tree(node->getLeft()) >= 0))
    return single_right_rotate(node);

  if ((balancer > 1) && (balance_tree(node->getLeft()) < 0)){
    node->setLeft(single_left_rotate(node->getLeft()));
    return single_right_rotate(node);
  }
  if((balancer < -1) && balance_tree(node->getRight()) <= 0){
    return single_left_rotate(node);
  }
  if((balancer < -1) && balance_tree(node->getRight()) > 0){
    node->setRight(single_right_rotate(node->getRight()));
    return single_left_rotate(node);
  }
  return node;
}

int AVL::balance_tree(Node *node)  {
    if (node == nullptr)
        return 0;
    return node->getLeft()->getHeight() - node->getRight()->getHeight();
}

AVL::Node* AVL::single_right_rotate(Node *node_b){
    Node* node = node_b->getLeft();
    Node* node_c = node->getRight();
    node->setRight(node_b);
    node_b->setLeft(node_c);
    node_b->setHeight(max(node_b->getLeft()->getHeight(), node_b->getRight()->getHeight()) + 1);
    node->setHeight(max(node->getLeft()->getHeight(), node->getRight()->getHeight()) + 1);
    return node;
}
AVL::Node* AVL::single_left_rotate(Node *node){
    Node *node_b = node->getRight();
    Node *node_c = node_b->getLeft();
    node_b->setLeft(node);
    node->setRight(node_c);
    node->setHeight(max(node->getLeft()->getHeight(), node->getRight()->getHeight()) + 1);
    node_b->setHeight(max(node_b->getLeft()->getHeight(), node_b->getRight()->getHeight()) + 1);
    return node_b;
}

AVL::Iterator AVL::begin() const{
  Iterator item;
  item.nodeStack = stack_creator(this->root);
  return item;
}

AVL::Iterator::Iterator(){}

AVL::Iterator::Iterator(const Iterator& iter){
  this->nodeStack = iter.nodeStack;
}

AVL::Iterator AVL::end() const{
  Iterator iter = this->begin();
  while(!iter.nodeStack.empty())
    iter.nodeStack.pop();
  return iter;
}


void AVL::preorder(Node* tree,ostream& out){
   if (tree == nullptr)
       return;
   out<< tree->getElement() << " ";
   preorder(tree->getLeft(),out);
   preorder(tree->getRight(),out);
}

string AVL::dot(Node* node,int position,char* stringBuilder,ofstream& file){

 sprintf(stringBuilder, "%d [label=\"%s\", shape=circle, color=black];\n",position,(node->getElement()).c_str());
 file << stringBuilder;
 int left = 2*position;
 if((node->getLeft()) != nullptr){
   sprintf(stringBuilder, "%d -> %d;\n",position,left);
   file << stringBuilder;
   dot(node->getLeft(),left,stringBuilder,file);
 }
 int right = left + 1;
 if((node->getRight()) != nullptr){
   sprintf(stringBuilder, "%d -> %d;\n",position,right);
   file << stringBuilder;
   dot(node->getRight(),right,stringBuilder,file);
 }
 return stringBuilder;
}

//-----------------------OPERATORS-------------------------

std::ostream& operator<<(std::ostream& out, const AVL& tree){
  tree.root->preorder_node(tree.root,out);
  return out;
}
AVL& AVL::operator =(const AVL& avl){
  this->root = nullptr;
  this->size = 0;
  string *str = new string[avl.size];
  int i = 0;
  preorder_to_string(avl.root,str,i);
  for (int j=0;j<i;j++){
    this->add(str[j]);
  }
  return *this;
}
AVL AVL::operator +(const AVL& avl){
  AVL newTree(*this);

  string *str = new string[avl.size];
  int i = 0;
  preorder_to_string(avl.root,str,i);
  for (int j=0;j<i;j++){
    newTree.add(str[j]);
  }
  return newTree;
}
AVL& AVL::operator+=(const AVL& avl){

  string *str = new string[avl.size];
  int i = 0;
  preorder_to_string(avl.root,str,i);
  for (int j=0;j<i;j++){
    this->add(str[j]);
  }
  return *this;
}
AVL& AVL::operator+=(const string& e){
  this->add(e);
  return *this;
}

AVL& AVL::operator-=(const string& e){
  this->rmv(e);
  return *this;
}

AVL AVL::operator +(const string& e){
  AVL newTree(*this);
  newTree.add(e);
  return newTree;
}
AVL AVL::operator -(const string& e){
  AVL newTree(*this);
  newTree.rmv(e);
  return newTree;
}

AVL::Iterator& AVL::Iterator::operator++(){
  this->nodeStack.pop();
  return *this;
}

AVL::Iterator AVL::Iterator::operator++(int a){
  Iterator iter = *this;
  this->nodeStack.pop();
  return iter;
}
string AVL::Iterator::operator*(){
  return this->nodeStack.top()->getElement();
}

bool AVL::Iterator::operator!=(Iterator it){
  if(this->nodeStack.size() != it.nodeStack.size())
    return true;
  return false;
}

bool AVL::Iterator::operator==(Iterator it){
  if(this->nodeStack.size() == it.nodeStack.size())
    return true;
  return false;
}
