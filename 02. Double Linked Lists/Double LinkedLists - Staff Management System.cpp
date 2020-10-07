#include<stdio.h>
#include<conio.h>
#include<string.h>
#include <stdlib.h>


struct NV {
  int MaNV;
  char HoTen[25], NS[12];
  float TL;
};

struct DNodeNV {
  NV info;
  struct DNodeNV *next, *prev;
};

struct DList {
  DNodeNV *Head, *Tail;
};

DList DListNV;

void init(DList &DQ) {
  DQ.Head = DQ.Tail = NULL;
}

DNodeNV *getDNodeNV(NV x) {
  DNodeNV *p;
  p = new DNodeNV();
  if(p != NULL) {
    p->info = x;
    p->next = NULL;
    p->prev = NULL;
  } else
    printf("Ko du bo nho");

  return p;
}

void chenDau(DList &DQ, DNodeNV *p) {
  if(DQ.Head == NULL) {
    DQ.Head = p;
    DQ.Tail = DQ.Head;
  }
  else {
    p->next = DQ.Head;
    DQ.Head->prev = p;
    DQ.Head = p;
  }
}

void nhap(NV &x) {
  printf("Nhap ma nv: ");
  scanf("%d", &x.MaNV);
  printf("Nhap ho ten: ");
  fflush(stdin);
  gets(x.HoTen);
  printf("Nhap ngay sinh: ");
  fflush(stdin);
  gets(x.NS);
  printf("Nhap tong luong: ");
  scanf("%f", &x.TL);
}

void in(NV x) {
  printf("\n%4d", x.MaNV);
  printf("%20s", x.HoTen);
  printf("%18s", x.NS);
  printf("%12.1f", x.TL);
}

void nhapDS(DList &DQ) {
  int n;
  DNodeNV *p;
  NV x;
  printf("So nv can nhap: ");
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    printf("\nNhap CB %d\n", i + 1);
    nhap(x);
    p = getDNodeNV(x);
    chenDau(DQ, p);
  }
}

static void tieuDe() {
  printf("\n%4s%20s%18s%12s", "Ma", "Ten", "Ngay sinh", "Luong");
}

void inDS(DList DQ) {
  DNodeNV *p;
  if(DQ.Head != NULL) {
    tieuDe();
    for(p = DQ.Head; p != NULL; p = p->next) {
      in(p->info);
    }
  }
  else
    printf("Ko co du lieu");
}

float tongLuong(DList DQ) {
  float tong = 0;
  for(DNodeNV *p = DQ.Head; p != NULL; p = p->next)
    tong += p->info.TL;

  return tong;
}

void xoaCuoi(DList &DQ) {
  DNodeNV *p;
  if(DQ.Tail != NULL) {
    p = DQ.Tail;
    DQ.Tail = DQ.Tail->prev;
    DQ.Tail->next = NULL;
    free(p);
    if(DQ.Head == NULL)
      DQ.Tail = NULL;
  }
}

DNodeNV *luongCaoNhat(DList DQ) {
  DNodeNV *p;
  float max = DQ.Head->info.TL;
  for(p = DQ.Head; p != NULL; p = p->next) {
    if(p->info.TL > max)
      max = p->info.TL;
  }

  for(p = DQ.Head; p != NULL; p = p->next) {
    if(p->info.TL == max)
      return p;
  }
}

void luongTren2M(DList DQ) {
  DNodeNV *p;
  int temp = -1;
  for(p = DQ.Head; p != NULL; p = p->next) {
    if(p->info.TL > 2000000) {
      while(temp) {
        tieuDe();
        in(p->info);
        temp++;
      }
    }
  }
  if(temp == -1)
    printf("\nKo co luong > 2m");
}

void sapXepMaTangDan(DList DQ) {
  DNodeNV *p, *q;
  p = DQ.Head;
  q = p->next;
  while(p != NULL) {
    q = p->next;
    while(q != NULL) {
      if(p->info.MaNV > q->info.MaNV) {
        NV tg = p->info;
        p->info = q->info;
        q->info = tg;
      }
      q = q->next;
    }
    p = p->next;
  }
}

int main() {

	nhapDS(DListNV);
	inDS(DListNV);
	printf("\nTong luong = %.1f", tongLuong(DListNV));

	printf("\nDS sau khi huy nhan vien cuoi\n");
	xoaCuoi(DListNV);
	inDS(DListNV);

	printf("\nCB co luong cao nhat: ");
	tieuDe();
	in(luongCaoNhat(DListNV)->info);

	printf("\nLuong > 2M");
	luongTren2M(DListNV);

	printf("\nDS sau khi sx tang dan theo ma");
  sapXepMaTangDan(DListNV);
  inDS(DListNV);
	return 0;
}
