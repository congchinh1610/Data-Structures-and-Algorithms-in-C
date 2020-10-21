#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <stdio.h>

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



/*****************/
int main() {
  printf("Linked list teaching management");
}
