#include<stdio.h>
#include<conio.h>
#include<string.h>

struct SinhVien {
  int maSV;
  char hoTen[25], lop[10];
  float dLT, dTH, dT, dTB;
};

struct NodeSV {
  SinhVien info;
  struct NodeSV *next;
};

struct List {
  NodeSV *Head, *Tail;
};

List ListSV;

void taoDS(List &Q) {
  Q.Head = Q.Tail = NULL;
};

NodeSV *getNodeSV(SinhVien x) {
  NodeSV *p = new NodeSV();
  if(p != NULL) {
    p->info = x;
    p->next = NULL;
  }
  else {
    printf("Ko thanh cong");
  }

  return p;
}

void chenCuoi(List &Q, NodeSV *p) {
  if(Q.Head == NULL) {
    Q.Head = p;
    Q.Tail = Q.Head;
  }
  else {
    Q.Tail->next = p;
    Q.Tail = p;
  }
}

void chenDau(List &Q, NodeSV *p) {
  if(Q.Head == NULL) {
    Q.Head = p;
    Q.Head = Q.Tail;
  }
  else {
    p->next = Q.Head;
    Q.Head = p;
  }
}

void nhap(SinhVien &x) {
  printf("\nMa: ");
  scanf("%d", &x.maSV);
  printf("Ho ten: ");
  fflush(stdin);
  gets(x.hoTen);
  printf("Lop: ");
  fflush(stdin);
  gets(x.lop);
  printf("Diem LT - Diem TH - Diem Thi: ");
  scanf("%f%f%f", &x.dLT, &x.dTH, &x.dT);
  x.dTB = (x.dLT + x.dTH + x.dT) / 3;
}

void in(SinhVien x) {
  printf("\n%4d", x.maSV);
  printf("%20s", x.hoTen);
  printf("%7s", x.lop);
  printf("%7.1f%7.1f%7.1f%7.1f", x.dLT, x.dTH, x.dT, x.dTB);
}

void nhapDS(List &Q) {
  int n;
  NodeSV *p;
  SinhVien x;
  printf("Nhap so SV: ");
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    nhap(x);
    p = getNodeSV(x);
    chenCuoi(Q, p);
  }
}

void inDS(List Q) {
  NodeSV *p;
  if(Q.Head != NULL) {
    printf("%4s%20s%7s%7s%7s%7s%7s", "Ma", "Ten", "Lop", "DLT", "DTH", "DT", "DTB");
    for(p = Q.Head; p != NULL; p = p->next) {
      in(p->info);
    }
  }
  else
    printf("Ko co du lieu");

}

void nhapDau(List &Q) {
  NodeSV *p;
  SinhVien x;
  nhap(x);
  p = getNodeSV(x);
  chenDau(Q, p);
}

void chenSau(List &Q) {
  int ma;
  NodeSV *p, *sv;
  SinhVien x;
  printf("Nhap ma sv can chen sau: ");
  scanf("%d", &ma);
  for(p = Q.Head; p != NULL; p = p->next) {
    if(p->info.maSV == ma) {
      nhap(x);
      sv = getNodeSV(x);
      sv->next = p->next;
      p->next = sv;
      if(p == Q.Tail)
        Q.Tail = p;
    }
  }
}

int xoaSV(List &Q) {
  NodeSV *p = Q.Head, *q = NULL;
  while(p != NULL) {
    if(p->info.dTB < 3.5)
      break;
    q = p;
    p = p->next;
  }
  if(p == NULL)
    return 0;

  if(q != NULL) {
    if(p = Q.Tail)
      Q.Tail = q;
    q->next = p->next;
    delete p;
  }
  else {
    Q.Head = p->next;
    if(Q.Head == NULL)
      Q.Tail == NULL;
  }
  return 1;
}

static void menu() {
  printf("\n1. Nhap ds n sinh vien");
  printf("\n2. Nhap 1 sv vao dau ds");
  printf("\n3. Chen 1 sv vao sau 1 sv");
  printf("\n4. Xoa cac sinh vien co dtb < 3.5");
  printf("\n5. In ds");
}

void run() {
  int chon;

  do {
    menu();
    printf("\nNhap lua chon: ");
    scanf("%d", &chon);
    switch(chon) {
      case 1:
        nhapDS(ListSV);
        break;
      case 2:
        nhapDau(ListSV);
        break;
      case 3:
        chenSau(ListSV);
        break;
      case 4:
        if(xoaSV(ListSV) == 1)
          printf("Da xong");
        else
          printf("Ko co sv co diem < 3.5");
        break;
      case 5:
        inDS(ListSV);
        break;
      default: break;
    }
  } while(chon);

}

int main() {

  run();

}

