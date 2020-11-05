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
  printf("%10.0f", x.phuCap);
  printf("%10.1f", x.luong);
}

static void tieuDeGV() {
  printf("\n%4s%25s%15s%15s%7s%10s%10s", "Ma", "Ho ten", "Nam sinh", "Trinh do", "HSL", "Phu cap", "Luong");
}

// nhap, in danh sach giao vien
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
  if(Q.Head == NULL)
    printf("Nhap ds truoc\n");
  else {
    printf("--------------------------------------------------------------------------------------");
    tieuDeGV();
    for(NodeGV *p = Q.Head; p != NULL; p = p->next) {
      inGV(p->info);
    }
    printf("\n--------------------------------------------------------------------------------------\n");
  }
}

// xu li file
char tenFileGV[25] = "giaovien.txt";

void luuFileGV(ListGV Q, FILE *f) {
  NodeGV *p;
  if(Q.Head == NULL) {
    printf("Ds giao vien trong, nhap ds truoc khi luu\n");
    exit(1);
  }
//  printf("Nhap ten file muon luu: ");
//  fflush(stdin);
//  gets(tenFileGV);
  f = fopen(tenFileGV, "wb");
  if(f == NULL)
    printf("Mo tep loi!!!\n");
  else {
    for(p = Q.Head; p != NULL; p = p->next) {
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
    printf("Mo tep loi\n");
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

// tim kiem giao vien theo ma
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

// tong luong
float tongLuongGiaoVien(ListGV Q) {
  float tongLuong = 0;
  for(NodeGV *p = Q.Head; p != NULL; p = p->next) {
    tongLuong += p->info.luong;
  }

  return tongLuong;
}

// thong tin giao vien luong max
NodeGV *luongCaoNhat(ListGV Q) {
  NodeGV *p;
  float luongMax = Q.Head->info.luong;
  for(p = Q.Head; p != NULL; p = p->next) {
    if(p->info.luong > luongMax)
      luongMax = p->info.luong;
  }

  for(p = Q.Head; p != NULL; p = p->next) {
    if(p->info.luong == luongMax)
      return p;
  }

}

// chen giao vien vao sau 1 giao vien theo ma
void chenSauGV(ListGV &Q) {
  int maChen;
  NodeGV *p, *gv;
  GiaoVien x;
  printf("\nNhap thong tin");
  printf("\nMa giao vien can chen sau: ");
  scanf("%d", &maChen);
  for(p = Q.Head; p != NULL; p = p->next) {
    if(p->info.maGV == maChen) {
      nhapGV(x);
      gv = getNodeGV(x);
      gv->next = p->next;
      p->next = gv;
      if(p == Q.Tail)
        Q.Tail = p;
    }
  }
}

// xoa giao vien theo ma
int xoaGV(ListGV &Q) {
  int ma;
  printf("\nMa gv can xoa: ");
  scanf("%d", &ma);
  NodeGV *p = Q.Head, *q = NULL;
  while(p != NULL) {
    if(p->info.maGV == ma)
      break;
    q = p;
    p = p->next;
  }
  if(p == NULL)
    return 0;

  if(q != NULL) {
    if(p == Q.Tail)
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

// sap xep luong tang dan
ListGV sapXepLuongTangDan(ListGV &Q) {
  NodeGV *p, *q;
  GiaoVien tg;
  for(p = Q.Head; p != NULL; p = p->next) {
    for(q = p->next; q != NULL; q = q->next) {
      if(p->info.luong > q->info.luong) {
        tg = p->info;
        p->info = q->info;
        q->info = tg;
      }
    }
  }
  return Q;
}

// in ds gv co luong x -> y
void inTheoLuong(ListGV Q) {
  float x, y;
  int temp = -1;
  printf("x = ");
  scanf("%f", &x);
  printf("\ny = ");
  scanf("%f", &y);
  for(NodeGV *p = Q.Head; p != NULL; p = p->next) {
    if((p->info.luong > x) && (p->info.luong < y)) {
      temp++;
      if(temp == 0) {
        printf("DS giao vien co luong tu %f->%f", x, y);
        tieuDeGV();
      }

      inGV(p->info);
    }
  }
  if(temp == -1)
    printf("\nKo tim thay\n");
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

void chenCuoiMH(ListMH &Q, NodeMH *p) {
  if(Q.Head == NULL) {
    Q.Head = p;
    Q.Tail = Q.Head;
  }
  else {
    Q.Tail->next = p;
    Q.Tail = p;
  }
}

void chenDauMH(ListMH &Q, NodeMH *p) {
  if(Q.Head == NULL) {
    Q.Head = p;
    Q.Head = Q.Tail;
  }
  else {
    p->next = Q.Head;
    Q.Head = p;
  }
}

void nhapMH(MonHoc &x) {
  printf("Ma mon: ");
  scanf("%d", &x.maMon);
  printf("Ten mon: ");
  fflush(stdin);
  gets(x.tenMon);
  printf("So tin chi: ");
  scanf("%d", &x.soTin);
  printf("Giang vien: ");
  fflush(stdin);
  gets(x.giangVien);
  printf("Si so lop: ");
  scanf("%d", &x.siSo);
  x.soTien = x.soTin * 350;
}

void inMH(MonHoc x) {
  printf("\n%4d", x.maMon);
  printf("%25s", x.tenMon);
  printf("%10d", x.soTin);
  printf("%25s", x.giangVien);
  printf("%10d", x.siSo);
  printf("%10d", x.soTien);
}

static void tieuDeMH() {
  printf("\n%4s%25s%10s%25s%10s%10s", "Ma", "Ten mon", "So tin", "Giang vien", "Si so", "So tien");
}

// nhap, in ds mon hoc
void nhapDSMH(ListMH &Q) {
  int n;
  printf("Nhap so mon can them: ");
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    printf("\nNhap thong tin mon thu %d\n\n", i + 1);
    MonHoc x;
    nhapMH(x);
    chenCuoiMH(Q, getNodeMH(x));
  }
}

void inDSMH(ListMH Q) {
  if(Q.Head == NULL)
    printf("Nhap ds truoc\n");
  else {
    printf("--------------------------------------------------------------------------------------");
    tieuDeMH();
    for(NodeMH *p = Q.Head; p != NULL; p = p->next) {
      inMH(p->info);
    }
    printf("\n--------------------------------------------------------------------------------------\n");
  }
}

char tenFileMH[25] = "monhoc.txt";

// xu li file mon hoc
void luuFileMH(ListMH Q, FILE *f) {
  if(Q.Head == NULL) {
    printf("Ds mon hoc trong, nhap ds truoc khi luu\n");
    exit(1);
  }
  f = fopen(tenFileMH, "wb");
  if(f == NULL)
    printf("Mo tep loi!!!\n");
  else {
    for(NodeMH *p = Q.Head; p != NULL; p = p->next) {
      fwrite(&(p->info), sizeof(MonHoc), 1, f);
    }
    fclose(f);
    printf("Luu file %s thanh cong\n", tenFileMH);
  }
}

void docFileMH(ListMH &Q, FILE *f) {
  MonHoc x;
  NodeMH *p;
  f = fopen(tenFileMH, "rb");
  int n = 0;
  if(f == NULL) {
    printf("Mo tep loi\n");
    exit(1);
  }
  Q.Head = Q.Tail = NULL;
  while(fread(&x, sizeof(x), 1, f) == 1) {
    chenCuoiMH(Q, getNodeMH(x));
  }
  fclose(f);
  printf("\nDanh sach giao vien doc tu file %s\n", tenFileMH);
  inDSMH(Q);
}

// tim kiem mon theo ten giag vien
void timKiemMon(ListMH Q) {
  int temp = -1;
  char ten[25];
  printf("Ten giang vien: ");
  fflush(stdin);
  gets(ten);

  for(NodeMH *p = Q.Head; p != NULL; p = p->next) {
    if(strcasecmp(ten, p->info.giangVien) == 0){
      temp++;
      if(temp == 0)
        tieuDeMH();
      inMH(p->info);
    }
  }
  if(temp == -1)
    printf("Ko tim thay gv %s.\n", ten);
}

// thong tin mon co si so cao nhat
void siSoMax(ListMH Q) {
  NodeMH *p;
  int max = Q.Head->info.siSo;
  for(p = Q.Head; p != NULL; p = p->next) {
    if(p->info.siSo > max)
      max = p->info.siSo;
  }

  tieuDeMH();
  for(p = Q.Head; p != NULL; p = p->next) {
    if(p->info.siSo == max)
      inMH(p->info);
  }
}

// chen mon hoc vao sau 1 mon hoc theo ma
void chenSauMH(ListMH &Q) {
  int maChen;
  NodeMH *p, *mh;
  MonHoc x;
  printf("\nNhap thong tin");
  printf("\nMa mon hoc can chen sau: ");
  scanf("%d", &maChen);
  for(p = Q.Head; p != NULL; p = p->next) {
    if(p->info.maMon == maChen) {
      nhapMH(x);
      mh = getNodeMH(x);
      mh->next = p->next;
      p->next = mh;
      if(p == Q.Tail)
        Q.Tail = p;
    }
  }
}

// sap xep mon theo tien
ListMH sapXepTien(ListMH &Q) {
  NodeMH *p, *q;
  MonHoc tg;
  for(p = Q.Head; p != NULL; p = p->next) {
    for(q = p->next; q != NULL; q = q->next) {
      if(p->info.soTien > q->info.soTien) {
        tg = p->info;
        p->info = q->info;
        q->info = tg;
      }
    }
  }
  return Q;
}

// xoa mon hoc theo ten
int xoaMH(ListMH &Q, char ten[25]) {
  NodeMH *p = Q.Head, *q = NULL;
  while(p != NULL) {
    if(strcasecmp(p->info.tenMon, ten) == 0)
      break;
    q = p;
    p = p->next;
  }
  if(p == NULL)
    return 0;

  if(q != NULL) {
    if(p == Q.Tail)
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

// tong so mon, tong so tin
int tongSo(ListMH Q, int chon) {
  int tongMon = 0, tongTin = 0, tongTien = 0;
  NodeMH *p = Q.Head;
  while(p != NULL) {
    tongMon++;
    tongTin += p->info.soTin;
    tongTien += p->info.soTien;
    p = p->next;
  }

  if(chon == 1)
    return tongMon;
  else if(chon == 2)
    return tongTin;
  else
    return tongTien;
}

// ds mon co tin > x
void inMonX(ListMH Q) {
  int x, temp = -1;
  printf("\nx = ");
  scanf("%d", &x);
  for(NodeMH *p = Q.Head; p != NULL; p = p->next) {
    if(p->info.soTin > x) {
      temp++;
      if(temp == 0) {
        printf("DS mon co so tin > %d", x);
        tieuDeMH();
      }
      inMH(p->info);
    }
  }
  if(temp == -1)
    printf("\nKo tim thay\n");
}

static void menuGV() {
  printf("%*s\n", 40, "\n****************************************************");
  printf("\n%s", "***       CHUONG TRINH QUAN LY GIAO VIEN         ***");
  printf("\n%s", "***      1. Nhap danh sach giao vien             ***");
  printf("\n%s", "***      2. Hien danh sach giao vien vua nhap    ***");
  printf("\n%s", "***      3. Cap nhat thong tin vao file          ***");
  printf("\n%s", "***      4. Hien danh sach tu file               ***");
  printf("\n%s", "***      5. Tim kiem theo ma gv                  ***");
  printf("\n%s", "***      6. Tinh tong luong                      ***");
  printf("\n%s", "***      7. Thong tin gv co luong cao nhat       ***");
  printf("\n%s", "***      8. Them gv sau gv co ma la x            ***");
  printf("\n%s", "***      9. Xoa thong tin giao vien theo ma      ***");
  printf("\n%s", "***      10. Sap xep luong tang dan              ***");
  printf("\n%s", "***      11. In gv co luong tu x -> y            ***");
  printf("\n%s", "***      0. Thoat khoi chuong trinh              ***");

}

static void menuMH() {
  printf("%*s\n", 40, "\n****************************************************");
  printf("\n%s", "***       CHUONG TRINH QUAN LY MON HOC           ***");
  printf("\n%s", "***      1. Nhap danh sach mon hoc               ***");
  printf("\n%s", "***      2. Hien danh sach mon hoc vua nhap      ***");
  printf("\n%s", "***      3. Cap nhat thong tin vao file          ***");
  printf("\n%s", "***      4. Hien danh sach tu file               ***");
  printf("\n%s", "***      5. Tim kiem mon theo ten giang vien     ***");
  printf("\n%s", "***      6. Mon co si so cao nhat                ***");
  printf("\n%s", "***      7. Them mh sau mh co ma la x            ***");
  printf("\n%s", "***      8. Sap xep mon theo tien                ***");
  printf("\n%s", "***      9. Xoa thong tin mon hoc theo ten       ***");
  printf("\n%s", "***      10. Tong so mon                         ***");
  printf("\n%s", "***      11. In mh co so tin > x                 ***");
  printf("\n%s", "***      12. Tong so tin                         ***");
  printf("\n%s", "***      13. Tong so tien                        ***");
  printf("\n%s", "***      0. Thoat khoi chuong trinh              ***");
}

void QLGV() {
  FILE *f;
  int chon;

  do {
    system("CLS");
    menuGV();
    printf("\n%s", "\n         > ");
    scanf("%d", &chon);
    switch(chon) {
      case 1:
        nhapDSGV(listGV);
        system("PAUSE");
        break;
      case 2:
        inDSGV(listGV);
        system("PAUSE");
        break;
      case 3:
        luuFileGV(listGV, f);
        system("PAUSE");
        break;
      case 4:
        docFileGV(listGV, f);
        system("PAUSE");
        break;
      case 5:
        timKiemGV(listGV);
        system("PAUSE");
        break;
      case 6:
        printf("\nTong luong = %.1f\n", tongLuongGiaoVien(listGV));
        system("PAUSE");
        break;
      case 7:
        printf("\nThong tin giao vien co luong cao nhat\n");
        tieuDeGV();
        inGV(luongCaoNhat(listGV)->info);
        system("PAUSE");
        break;
      case 8:
        chenSauGV(listGV);
        printf("\nDS sau khi chen:\n");
        inDSGV(listGV);
        system("PAUSE");
        break;
      case 9: {
        if(xoaGV(listGV) == 1) {
          printf("DS giao vien sau khi xoa: \n");
          inDSGV(listGV);
        }
        else
          printf("Ko tim thay");
      }
        system("PAUSE");
        break;
      case 10:
        printf("\nDs da sap xep tang dan theo luong:\n");
        inDSGV(sapXepLuongTangDan(listGV));
        system("PAUSE");
        break;
      case 11:
        printf("\nDs da sap xep tang dan theo luong:\n");
        inTheoLuong(listGV);
        system("PAUSE");
        break;
      default:
        break;
    }
  } while(chon);
}

void QLMH() {
  FILE *f;
  int chon;

  do {
    system("CLS");
    menuMH();
    printf("\n%s", "\n         > ");
    scanf("%d", &chon);
    switch(chon) {
      case 1:
        nhapDSMH(listMH);
        system("PAUSE");
        break;
      case 2:
        inDSMH(listMH);
        system("PAUSE");
        break;
      case 3:
        luuFileMH(listMH, f);
        system("PAUSE");
        break;
      case 4:
        docFileMH(listMH, f);
        system("PAUSE");
        break;
      case 5:
        timKiemMon(listMH);
        system("PAUSE");
        break;
      case 6:
        siSoMax(listMH);
        system("PAUSE");
        break;
      case 7:
        chenSauMH(listMH);
        inDSMH(listMH);
        system("PAUSE");
        break;
      case 8:
        printf("\nDS mon hoc sau khi sap xep theo so tien\n");
        inDSMH(sapXepTien(listMH));
        system("PAUSE");
        break;
      case 9: {
        char tenMon[25];
        printf("\nTen mon can xoa: ");
        fflush(stdin);
        gets(tenMon);
        if(xoaMH(listMH, tenMon) == 1) {
          printf("\nDSMN sau khi xoa\n");
          inDSMH(listMH);
        }
        else
          printf("Ko tim thay\n");
      }
        system("PAUSE");
        break;
      case 10:
        printf("\nTong mon: %d\n", tongSo(listMH, 1));
        system("PAUSE");
        break;
      case 11:
        inMonX(listMH);
        system("PAUSE");
        break;
      case 12:
        printf("\nTong tin: %d\n", tongSo(listMH, 2));
        system("PAUSE");
        break;
      case 13:
        printf("\nTong tien: %d\n", tongSo(listMH, 3));
        system("PAUSE");
        break;
      default:
        break;
    }
  } while(chon);
}


int main() {

  int x;
  while(true) {
    system("CLS");
    printf("%*s\n", 40, "****************************************************");
    printf("\n%s", "***          CHUONG TRINH QUAN LY GIANG DAY GIAO VIEN        ***");
    printf("\n%s", "***          1. Quan ly giao vien                            ***");
    printf("\n%s", "***          2. Quan ly mon hoc                              ***");
    printf("\n%s", "***          0. Thoat khoi chuong trinh                      ***");
    printf("\n%s", "***          Nhap lua chon cua ban: ");
    scanf("%d", &x);
    switch(x) {
      case 1:
        QLGV();
        printf("\n");
        system("PAUSE");
        break;
      case 2:
        QLMH();
        printf("\n");
        system("PAUSE");
        break;
      case 0:
        exit(0);
        break;
      default:
        printf("\n");
        break;
    }
  }

}
