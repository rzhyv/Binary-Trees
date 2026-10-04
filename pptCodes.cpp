//EXPRESSION TREES - trees that represents arithmetic / logical expressions
//leaf nodes usually contain operands (numbers / variables)
//Internal nodes normally contain operators (+, -, *, /)
//The root is the main operator of the expression
//Makes the hierarchical expression of an expression explicit
#include <iostream>
#include <string>
#define MAX 5
using namespace std;

//EXPRESSION NOTATIONS
//INFIX: A + B ((2*3)+5) - root is inside
//PREFIX: + AB  (+*235) - root is in front
//POSTFIX: AB + (23*5+) - root is at the end

struct Node{
  int data;
  Node *left;
  Node *right;
  Node(int x):data(x), left(NULL), right(NULL){}
};

class TreeStack{ //for tree
  private:
    Node *stack[MAX];
    int top;
  public:
    TreeStack(){
      top = MAX;
    }
    void push(Node *n);
    Node *pop(Node *n); //when deleting in tree, we always return a node
    int Top();
    bool isEmpty();
};

void TreeStack::push(Node *n){
  top--;
  stack[top]=n;
}

Node *TreeStack::pop(Node *n){ //not actually deleting, it's passing the value "somewhere else" where it is needed
  if(top==-1){
    return NULL;
  }
  return stack[top++];
}

int TreeStack::Top(){
  return top = MAX-1;
}

bool TreeStack::isEmpty(){
  return top == MAX;
}

class Stack{
  private:
    char ops[MAX]; //char because tree includes operators not just integers.
    int top;
  public:
    Tree(){
      top=MAX;ops[ops--];
    }

    void push(char x){
      ops[ops--] = x;
    }

    char pop(){
      if(top==MAX){
        return NULL;
      }
      ops[top++];
    }

    char peek(){ //checks which num top is currently at??
      if(top==-1){
        return '0';
      }
      return ops[top];
    }
    bool treeEmpty(){
      return top==MAX;
    }
    //OPERATOR CHECKER
    bool isOperator(char c){
      return c == '+' || c == '-' ||
      c == '*' || c == '/';
    }

    //PRECEDENCE
    int precedence(char c){
      if(c=='+'||c=='-'){
        return 1;
      }
      if(c=='*'||c=='/'){
        return 1;
      }
      return 0;
    }
    //CREATING SUBTREE
    void createSubtree(TreeStack &nodes, char op){
      Node *right = nodes.pop();
      Node *left = nodes.pop();

      Node *newNode = new Node(op);

      newNode->left=left;
      newNode->right=right;

      nodes.push(newNode);
    }
    //creating the ecpression tree
    Node *createExpTree(string expression){
      TreeStack nodes;
      Stack operators;

      for(int i=0; i < expressions.length(); i++){
        char c = expression[i];

        if(c==''){
          continue;
        }

        if(!isOperator(c) && c != '(' && c!= ')'){
          Node *newNode = new Node (c);
          nodes.push(newNode);
        }
        else if(c=='('){
          nodes.push(c);
        }
        else if(c==')'){
          while(!operators.isEmpty() && operator.peek() != '('){
            char op = operators.pop();
            createSubtree(nodes, op);
          }
          operators.push(c);
        }
      }
      while(!operators.isEmpty()){
        char op = operators.pop();
        createSubtree(nodes, op);
      }
      return nodes.pop();
    }

    //evaluating exp tree
    double evaluate(Node *root){
      if(root==NULL){
        return 0;
      }

      if(!isOperator(root->data)){
        return root->data - '0';
      }

      double leftValue = evaluate(root->left);
      double rightValue = evaluate(root->right);

      switch(root->data){
        case '+':
          return leftValue + rightValue;
        case '-':
          return leftValue - rightValue;
        case '*':
          return leftValue * rightValue;
        case '/':
          return leftValue / rightValue;
      }
      return 0;
    }

    void display(Node *root, int space=0){
      if(root==NULL){
        return;
      }
      space+=5;

      display(root->right, space);
      cout << endl;

      for(int i=5; i<space;i++){
        cout << " ";
        cout << root->data << endl;
        display(root->left, space);
      }
    }

    void preorder(Node *root){
      if(root==NULL){
        return;
      }
      cout << root->data << " ";
      preorder(root->left);
      preorder(root->right);
    }

    void inorder(Node *root){
      if(root==NULL){
        return
      }
      inorder(root->left);
      cout << root->data << " ";
      inorder(root->right);
    }

    void postorder(Node *root){
      if(root==NULL){
        return
      }
      postorder(root->left);
      postorder(root->right);
      cout << root->data << " ";
    }
};

int main(){
  string expressions;
  Stack s;
  TreeStack ts;

  cout << "Enter expression: ";
  cin.ignore();
  getline(cin, expressions);

  Node *root = new Node(expression);

  cout << "\nExpression Tree:" << endl;
  s.display(root);

  cout << "Preorder: ";
  s.preorder(root);

  cout << "Inorder: ";
  s.inorder(root);

  cout << "Postorder: ";
  s.Postorder(root);

  cout << "\n\nResult: " << evaluate(root);
  cout << endl;
  return 0;
}