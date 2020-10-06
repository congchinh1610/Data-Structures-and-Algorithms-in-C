#include<stdio.h>
#include<conio.h>
#include<string.h>

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
  DNodeNV *Headm *Tail;
};

DList DListNV;

void init(DList &DQ) {
  DQ.Head = DQ.Tail = NULL;
}

DNodeNV *getNodeNV(NV x) {
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





int main() {
	printf("Hello world\n");
	return 0;
}
