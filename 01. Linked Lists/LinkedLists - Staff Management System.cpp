#include<stdio.h>
#include<conio.h>
#include<string.h>

struct CanBo {
  int maCB;
  char hoTen[25];
  int tuoi;
  float hsl, pc, tt;
};

struct NodeCB {
  CanBo info;
  struct NodeCB *next;
};

struct List {
  NodeCB *Head, *Tail;
};

List ListCB;

void taoDS(List &Q) {
  Q.Head = Q.Tail = NULL;
};

NodeCB *getNodeCB(CanBo x) {
  NodeCB *p = new NodeCB();
  if(p != NULL) {
    p->info = x;
    p->next = NULL;
  }
  else {
    printf("Ko thanh cong");
  }

  return p;
}

void chenCuoi(List &Q, NodeCB *p) {
  if(Q.Head == NULL) {
    Q.Head = p;
    Q.Tail = Q.Head;
  }
  else {
    Q.Tail->next = p;
    Q.Tail = p;
  }
}

void chenDau(List &Q, NodeCB *p) {
  if(Q.Head == NULL) {
    Q.Head = p;
    Q.Head = Q.Tail;
  }
  else {
    p->next = Q.Head;
    Q.Head = p;
  }
}

void nhap(CanBo &x) {
  printf("Ma: ");
  scanf("%d", &x.maCB);
  printf("Ho ten: ");
  fflush(stdin);
  gets(x.hoTen);
  printf("Tuoi: ");
  scanf("%d", &x.tuoi);
  printf("He so luong: ");
  scanf("%f", &x.hsl);
  printf("Phu cap: ");
  scanf("%f", &x.pc);
  x.tt = x.hsl * 1050 + x.pc;
}

void in(CanBo x) {
  printf("\n%4d", x.maCB);
  printf("%20s", x.hoTen);
  printf("%7d", x.tuoi);
  printf("%7.1f", x.hsl);
  printf("%7.1f", x.pc);
  printf("%10.1f", x.tt);
}

void nhapDS(List &Q) {
  int n;
  NodeCB *p;
  CanBo x;
  printf("Nhap so CB: ");
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    printf("\nNhap CB %d\n", i + 1);
    nhap(x);
    p = getNodeCB(x);
    chenCuoi(Q, p);
  }
}

void inDS(List Q) {
  NodeCB *p;
  if(Q.Head != NULL) {
    printf("%4s%20s%7s%7s%7s%10s", "Ma", "Ten", "Tuoi", "HSL", "PC", "TT");
    for(p = Q.Head; p != NULL; p = p->next) {
      in(p->info);
    }
  }
  else
    printf("Ko co du lieu");
}

void timKiem(List Q) {
  int ma;
  NodeCB *p;
  int temp = 0;
  printf("\nNhap ma cb can tim: ");
  scanf("%d", &ma);
  printf("%4s%20s%7s%7s%7s%10s", "Ma", "Ten", "Tuoi", "HSL", "PC", "TT");
  for(p = Q.Head; p != NULL; p = p->next) {
    if(p->info.maCB == ma) {
        in(p->info);
        temp++;
    }
  }
  if(temp == 0) printf("Ko tim thay");
}

int demCB(List Q) {
  int dem = 0;
  NodeCB *p;
  for(p = Q.Head; p != NULL; p = p->next) {
    if(p->info.tt < 3000 && p->info.tt > 2000) {
        dem++;
    }
  }
  return dem;
}

float tongLuong(List Q) {
  float tong = 0;
  NodeCB *p;
  for(p = Q.Head; p != NULL; p = p->next)
      tong += p->info.tt;

  return tong;
}

void tuoiDuoi20(List Q) {
  NodeCB *p;
  printf("\n%4s%20s%7s%7s%7s%10s", "Ma", "Ten", "Tuoi", "HSL", "PC", "TT");
  for(p = Q.Head; p != NULL; p = p->next) {
    if(p->info.tuoi < 20) {
      in(p->info);
    }
  }
}

void sapXep(List &Q) {
  NodeCB *p, *q;
  CanBo tg;
  for(p = Q.Head; p != NULL; p = p->next) {
    for(q = p->next; q != NULL; q = q->next) {
      if(p->info.tt > q->info.tt) {
        tg = p->info;
        p->info = q->info;
        q->info = tg;
      }
    }
  }
}

void luongCaoNhat(List Q) {
  NodeCB *p;
  float max = Q.Head->info.tt;
  for(p = Q.Head; p != NULL; p = p->next) {
    if(p->info.tt > max)
      max = p->info.tt;
  }
  printf("\nCB co luong cao nhat: ");
  for(p = Q.Head; p != NULL; p = p->next) {
    if(p->info.tt == max)
      printf("%s\n", p->info.hoTen);
  }
}

void chenSau(List &Q) {
  int maChen;
  NodeCB *p, *cb;
  CanBo x;
  printf("Nhap ma cb can chen sau: ");
  scanf("%d", &maChen);
  for(p = Q.Head; p != NULL; p = p->next) {
    if(p->info.maCB == maChen) {
      nhap(x);
      cb = getNodeCB(x);
      cb->next = p->next;
      p->next = cb;
      if(p == Q.Tail)
        Q.Tail = p;
    }
  }
}

static void menu() {
  printf("\n-------------------------------------------");
  printf("\n0. Thoat");
  printf("\n1. Nhap ds cb");
  printf("\n2. In ds");
  printf("\n3. Tim kiem theo ma");
  printf("\n4. Dem so can bo co luong 2000 - 3000");
  printf("\n5. Tong luong");
  printf("\n6. In ds co tuoi < 20");
  printf("\n7. Sap xep luong tang dan");
  printf("\n8. Ten can bo co luong cao nhat");
  printf("\n9. Chen sau can bo co ma la x");
  printf("\n-------------------------------------------\n");
}

void run() {
  int chon;

  do {
    menu();
    printf("\nNhap lua chon: ");
    scanf("%d", &chon);
    switch(chon) {
      case 1:
        nhapDS(ListCB);
        break;
      case 2:
        inDS(ListCB);
        break;
      case 3:
        timKiem(ListCB);
        break;
      case 4:
        printf("\nSo cb co luong 2000 -> 3000 = %d\n", demCB(ListCB));
        break;
      case 5:
        printf("\nTong luong = %.1f\n", tongLuong(ListCB));
        break;
      case 6:
        printf("\nDSCB tuoi < 20");
        tuoiDuoi20(ListCB);
        break;
      case 7:
        sapXep(ListCB);
        printf("\nDS sau khi sx\n");
        inDS(ListCB);
        break;
      case 8:
        luongCaoNhat(ListCB);
        break;
      case 9:
        chenSau(ListCB);
        printf("\nDS sau khi chen\n");
        inDS(ListCB);
        break;

      default: break;
    }
  } while(chon);

}

int main() {

  run();

}

