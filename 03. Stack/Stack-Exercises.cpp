#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct SinhVien {
  int maSV;
  char hoTen[25];
  float dLT, dTH, dT, dTB;
};

struct Node {
  SinhVien info;
  struct Node *next;
};

struct Stack {
  Node *top;
};

void init(Stack &s) {
  s.top = NULL;
}

int isEmpty(Stack s) {
  if(s.top == NULL)
    return 0;
  else
    return 1;
}

Node *getNode(SinhVien x) {
  Node *p = new Node();
  if(p != NULL) {
    p->info = x;
    p->next = NULL;
  }
  else {
    printf("Ko thanh cong");
  }

  return p;
}

void push(Stack &s, SinhVien x) {
  Node *p = new Node();
  if(p == NULL) {
    printf("ko cap phat dc");
    exit(1);
  }
  p->info = x;
  p->next = s.top;
  s.top = p;
}

void nhap(SinhVien &x) {
  printf("\nMa: ");
  scanf("%d", &x.maSV);
  printf("Ho ten: ");
  fflush(stdin);
  gets(x.hoTen);
  printf("Diem LT - Diem TH - Diem Thi: ");
  scanf("%f%f%f", &x.dLT, &x.dTH, &x.dT);
  x.dTB = (x.dLT + x.dTH + x.dT) / 3;
}

void in(SinhVien x) {
  printf("\n%4d", x.maSV);
  printf("%20s", x.hoTen);
  printf("%7.1f%7.1f%7.1f%7.1f", x.dLT, x.dTH, x.dT, x.dTB);
}



int main() {


}
