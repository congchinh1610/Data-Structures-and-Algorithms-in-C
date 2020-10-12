#include<stdio.h>
#include<conio.h>

struct SinhVien {
  int maSV;
  char hoTen[25];
  float dLT, dTH, dT, dTB;
};

struct Node {
  SV info;
  struct Node *next;
};

struct Stack {
  Node *top;
};

void init(Stack &s) {
  s.top = NULL;
}

void isEmpty(Stack s) {
  if(s.top == NULL)
    return 0;
  else
    return 1;
}



int main() {


}
