#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <stdio.h>

/* Giao vien */
// dinh nghia ds giao vien
struct GiaoVien {
  int maGV, namSinh;
  char tenGV[25], trinhDo[25];
  float hSL, phuCap, luong;
};

struct NodeGV {
  GiaoVien info;
  struct NodeGV *next;
};

struct ListGV {
  NodeGV *Head, *Tail;
};

ListGV listGV;

void initDSGV(ListGV &GV) {
  GV.Head = GV.Tail = NULL;
}

NodeGV *getNodeGV(GiaoVien x) {
  NodeGV *p = new NodeGV();
  if(p != NULL) {
    p->info = x;
    p->next = NULL;
  }
  else {
    printf("Ko thanh cong");
  }

  return p;
}

void chenCuoiGV(ListGV &Q, NodeGV *p) {
  if(Q.Head == NULL) {
    Q.Head = p;
    Q.Tail = Q.Head;
  }
  else {
    Q.Tail->next = p;
    Q.Tail = p;
  }
}

void chenDauGV(ListGV &Q, NodeGV *p) {
  if(Q.Head == NULL) {
    Q.Head = p;
    Q.Head = Q.Tail;
  }
  else {
    p->next = Q.Head;
    Q.Head = p;
  }
}

void nhapGV(GiaoVien &x) {
  printf("Ma gv: ");
  scanf("%d", &x.maGV);
  printf("Ho ten: ");
  fflush(stdin);
  gets(x.tenGV);
  printf("Nam sinh: ");
  scanf("%d", &x.namSinh);
  printf("Trinh do: ");
  fflush(stdin);
  gets(x.trinhDo);
  printf("He so luong: ");
  scanf("%f", &x.hSL);
  printf("Phu cap: ");
  scanf("%f", &x.phuCap);
  x.luong = x.hSL * 3500 + x.phuCap;
}

void inGV(GiaoVien x) {
  printf("\n%4d", x.maGV);
  printf("%25s", x.tenGV);
  printf("%15d", x.namSinh);
  printf("%15s", x.trinhDo);
  printf("%7.1f", x.hSL);
  printf("%10.1f", x.phuCap);
  printf("%10.1f", x.luong);
}

static void tieuDeGV() {
  printf("\n%4s%25s%15s%15s%7s%10s%10s", "Ma", "Ho ten", "Nam sinh", "Trinh do", "HSL", "Phu cap", "Luong");
}

void nhapDSGV(ListGV &Q) {
  int n;
  printf("Nhap so giao vien can them: ");
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    printf("\nNhap thong tin gv thu %d\n\n", i + 1);
    GiaoVien x;
    nhapGV(x);
    chenCuoiGV(Q, getNodeGV(x));
  }
}

void inDSGV(ListGV Q) {
  printf("--------------------------------------------------------------------------------------");
  tieuDeGV();
  for(NodeGV *p = Q.Head; p != NULL; p = p->next) {
    inGV(p->info);
  }
  printf("\n--------------------------------------------------------------------------------------\n");
}

char tenFileGV[20];


void luuFileGV(ListGV Q, FILE *f) {
  if(Q.Head == NULL) {
    printf("Ds giao vien trong, nhap ds truoc khi luu\n");
    exit(1);
  }
  printf("Nhap ten file muon luu: ");
  fflush(stdin);
  gets(tenFileGV);
  f = fopen(tenFileGV, "wb");
  if(f == NULL)
    printf("Mo tep loi!!!\n");
  else {
    for(NodeGV *p; p != NULL; p = p->next) {
      fwrite(&(p->info), sizeof(GiaoVien), 1, f);
    }
    fclose(f);
    printf("Luu file %s thanh cong\n", tenFileGV);
  }
}

void docFileGV(ListGV &Q, FILE *f) {
  GiaoVien x;
  NodeGV *p;
  f = fopen(tenFileGV, "rb");
  int n = 0;
  if(f == NULL) {
    printf("Ko tim thay file\n");
    exit(1);
  }
  Q.Head = Q.Tail = NULL;
  while(fread(&x, sizeof(x), 1, f) == 1) {
    p = getNodeGV(x);
    chenCuoiGV(Q, p);
  }
  fclose(f);
  printf("\nDanh sach giao vien doc tu file %s\n", tenFileGV);
  inDSGV(Q);
}

void timKiemGV(ListGV Q) {
  int ma, temp = -1;
  NodeGV *p;
  printf("Nhap ma giao vien can tim: ");
  scanf("%d", &ma);
  for(p = Q.Head; p != NULL; p = p->next) {
    if(p->info.maGV == ma) {
      temp++;
      if(temp == 0)
        tieuDeGV();
      inGV(p->info);
    }
  }
  if(temp == -1)
    printf("Ko tim thay gv co ma %d.\n", ma);
}

/* Mon hoc */
// dinh nghia ds mon hoc
struct MonHoc {
  int maMon, soTin, siSo, soTien;
  char tenMon[25], giangVien[25];
};

struct NodeMH {
  MonHoc info;
  struct NodeMH *next;
};

struct ListMH {
  NodeMH *Head, *Tail;
};

ListMH listMH;

void initDSMH(ListMH &MH) {
  MH.Head = MH.Tail = NULL;
}

NodeMH *getNodeMH(MonHoc x) {
  NodeMH *p = new NodeMH();
  if(p != NULL) {
    p->info = x;
    p->next = NULL;
  }
  else {
    printf("Ko thanh cong\n");
  }

  return p;
}


/*****************/
int main() {
  FILE *f;


//  GiaoVien x;
//  nhapGV(x);
//  inGV(x);
  nhapDSGV(listGV);
  inDSGV(listGV);
  luuFileGV(listGV, f);
  docFileGV(listGV, f);
  inDSGV(listGV);
  timKiemGV(listGV);
}
