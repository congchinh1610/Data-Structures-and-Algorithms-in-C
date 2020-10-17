#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <fstream>

typedef struct NODESach
{
    int soLuong;
    float giaTien;
    char tenSach[50], tacGia[30], maSach[30];
} sach;
typedef struct STACKsach
{
    NODESach data;
    STACKsach *next;
} StackS;

typedef struct NODEHoaDon
{
    int soSP, sl[100], gia[100], mannagerSP[30], tongTien;
    char maNV[30], maKH[30], maHD[30], date[30];
} hoadon;
typedef struct STACKhoadon
{
    hoadon data;
    STACKhoadon *next;
} StackHD;
void initSach(StackS *&top)
{
    top = NULL;
};

void initHD(StackHD *&top)
{
    top = NULL;
};

// CHUONG TRINH QUAN LY SACH
void nhapS(sach &S)
{
    printf("\nNhap ten sach: ");
    fflush(stdin);
    scanf("%[^\n]s", &S.tenSach);
    printf("Nhap ma sach: ");
    fflush(stdin);
    scanf("%[^\n]s", &S.maSach);
    printf("Nhap tac gia: ");
    fflush(stdin);
    scanf("%[^\n]", &S.tacGia);
    printf("Nhap so luong: ");
    scanf("%d", &S.soLuong);
    printf("Nhap gia sach: ");
    scanf("%f", &S.giaTien);
}

StackS *createNode(sach S)
{
    StackS *new_node;
    new_node = (StackS *) malloc(sizeof(StackS));
    new_node->data=S;
    new_node->next=NULL;
    return new_node;
}

bool isEmptyS(StackS *top)
{
    return !top;
}

//nhap
void pushS(StackS *&top, StackS *createTop)
{

    if (top == NULL)
    {
        top = createTop;

    }
    else
    {
        createTop->next = top;
        top = createTop;
    }
}

void popS(StackS *&top)
{
    if (top == NULL)
        printf("\nKhong co gia tri trong danh sach");
    else
    {
        StackS *q = top;
        top = top->next;
        free(q);
    }
}

//nhap
void nhapDSS(StackS *&top, sach &S)
{
    int n;

    do
    {
        printf("\nNhap vao so quyen sach: ");
        scanf("%d", &n);
    }
    while (n <= 0);
    for (int i = 0; i < n; i++)
    {
        printf("\nNhap thong tin sach %d", i + 1);
        nhapS(S);
        pushS(top, createNode(S));
    }
}

//xuat
void xuatSach(StackS *top)
{
    StackS *p;
    p = top;

    printf("\n%30s%10s%25s%10s%15s", "Ten Sach", "Ma Sach", "Tac Gia", "So Luong", "Gia Tien");
    while (p != NULL)
    {
        printf("\n%30s%10s%25s%10d%15.0f", p->data.tenSach, p->data.maSach, p->data.tacGia, p->data.soLuong,
               p->data.giaTien);
        p = p->next;
    }
}

void xuat500(StackS *top)
{
    StackS *p;
    p = top;
    printf("\nDanh sach quyen sach gia tren 500: ");
    printf("\n%30s%10s%25s%10s%15s", "Ten Sach", "Ma Sach", "Tac Gia", "So Luong", "Gia Tien");
    while (p != NULL)
    {
        if (p->data.giaTien > 500)
        {
            printf("\n%30s%10s%25s%10d%15.0f", p->data.tenSach, p->data.maSach, p->data.tacGia, p->data.soLuong,
                   p->data.giaTien);

        }
        p = p->next;
    }
}

//tim kiem
void searchMa(StackS *top)
{
    char ma[50];
    printf("\nNhap ma sach can tim: ");
    fflush(stdin);
    scanf("%[^\n]s", &ma);
    StackS *p = top;
    printf("\n%30s%10s%25s%10s%15s", "Ten Sach", "Ma Sach", "Tac Gia", "So Luong", "Gia Tien");
    while (p != NULL)
    {
        if (strcmp(ma, p->data.maSach) == 0)
        {
            printf("\n%30s%10s%25s%10d%15.0f", p->data.tenSach, p->data.maSach, p->data.tacGia, p->data.soLuong,
                   p->data.giaTien);
        }
        p = p->next;
    }

}

//dem
void thongKeSL(StackS *top)
{
    StackS *p = top;
    int i = 0, n;
    printf("\nNhap so luong sach can kiem tra: ");
    scanf("%d", &n);

    while (p != NULL)
    {
        if (p->data.soLuong > n)
            i++;
        p = p->next;
    }
    if (i == 0)
    {
        printf("Khong co cuon sach nao co so luong tren %d.", n);
    }
    else
    {
        printf("So quyen sach co so luong lon hon %d la: %d", n, i);
    }
}

void delRear(StackS *&top)
{
    sach X;
    StackS  *q;
    initSach(q);
    if (isEmptyS(top))
        printf("\nKhong ton tai gia tri trong danh sach");
    else if (top->next == NULL)
    {
        top = NULL;
    }
    else
    {
        while (top != NULL)
        {
            X=top->data;
            pushS(q, createNode(X));
            popS(top);
        }
        popS(q);
        while (q != NULL)
        {
            X=q->data;
            pushS(top, createNode(X));
            popS(q);
        }
    }
}

int sizeS(StackS *top)
{
    int i = 0;
    StackS *p = top;
    while (p != NULL)
    {
        i++;
        p = p->next;
    }
    return i;
}

void delMid(StackS *&top)
{
    StackS *q;
    sach S;
    initSach(q);
    int k;
    do
    {
        printf("\nNhap vi tri can xoa: ");
        scanf("%d", &k);
    }
    while (k < 1 || k > sizeS(top));
    if (top == NULL)
    {
        printf("\nDanh sach khong co gia tri");
    }
    else if (top->next == NULL)
    {
        top = NULL;
        free(top);
    }
    else
    {
        int z = 0;
        while (top!=NULL)
        {
            z++;
            S = top->data;
            pushS(q, createNode(S));
            if (z == k)
            {
                popS(q);
            }
            popS(top);

        }
        while (q != NULL)
        {
            S=q->data;
            pushS(top, createNode(S));
            popS(q);
        }
    }

}
void sortTenSach(StackS *&top)
{
    sach S;
    StackS *tmpStack;
    initSach(tmpStack);
    while (!isEmptyS(top))
    {
        S = top->data;
        popS(top);
        while (!isEmptyS(tmpStack) && strcmp(tmpStack->data.tenSach, S.tenSach)<0)
        {
            pushS(top, createNode(tmpStack->data));
            popS(tmpStack);
        }
        pushS(tmpStack, createNode(S));
    }
    top = tmpStack;

}

void fileWrite(StackS *top, char *&fileName)
{
    StackS *x, *y;
    initSach(x);
    initSach(y);
    sach S;
    if (strcmp(fileName, "sach.txt") != 0)
    {
        printf("\nNhap ten file can nhap(*.txt): ");
        fflush(stdin);
        scanf("%s", fileName);
        strcat(fileName, ".txt");
    }
    FILE *f;
    f = fopen(fileName, "ab");
    y = top;
    while (y!=NULL)
    {
        S=y->data;
        pushS(x, createNode(S));
        popS(y);
    }
    if (x == NULL)
    {
        printf("\nDanh sach chua co gia tri, nhap truoc khi luu file!");
    }
    if (f == NULL)
    {
        printf("\nLoi khi mo tep");
        exit(1);
    }
    else
    {
        while (x != NULL)
        {
            fwrite(&x->data, sizeof(x->data), 1, f);
            x = x->next;
        }

        fclose(f);
        printf("\nDa luu vao file \"%s\"!", fileName);
    }
}

void fileRead(StackS *&top, char *fileName)
{
    FILE *f;
    initSach(top);
    if (strcmp(fileName, "sach.txt") != 0)
    {
        printf("\nNhap ten file(*.txt): ");
        fflush(stdin);
        scanf("%s", fileName);
        strcat(fileName, ".txt");
    }
    StackS *p;
    sach sa;
    f = fopen(fileName, "rb");
    if (f == NULL)
    {
        printf("\nMo file bi loi!");
    }
    else
    {
        while (fread(&sa, sizeof(sa), 1, f) == 1)
        {
            p = (StackS *) malloc(sizeof(StackS));
            p->data = sa;
            p->next = NULL;
            pushS(top, p);
        }
        fclose(f);
    }
}

void easeFile(char *fileName)
{
    FILE *f;
    if (strcmp(fileName, "sach.txt") != 0)
    {
        printf("\nNhap ten file can lam sach(*.txt): ");
        fflush(stdin);
        scanf("%s", fileName);
        strcat(fileName, ".txt");
    }
    f = fopen(fileName, "w");
    fclose(f);

}

//// chuong trinh quan ly hoa don
void nhapHD(hoadon &hd)
{
    printf("\nNhap ma hoa don: ");
    fflush(stdin);
    scanf("%[^\n]s", &hd.maHD);
    printf("Nhap ngay lap hoa don: ");
    fflush(stdin);
    scanf("%[^\n]s", &hd.date);
    printf("Nhap ma khach hang mua: ");
    fflush(stdin);
    scanf("%[^\n]s", &hd.maKH);
    printf("Nhap ma nhan vien ban: ");
    fflush(stdin);
    scanf("%[^\n]s", &hd.maNV);
    printf("Nhap so luong sach mua: ");
    scanf("%d", &hd.soSP);
    for(int i=0; i<hd.soSP; i++)
    {
        printf("\n-----------------------");
        printf("\nNhap thong tin quyen sach %d", i+1);
        printf("\nNhap ma sach(so): ");
        scanf("%d", &hd.mannagerSP[i]);
        printf("Nhap so luong sach: ");
        scanf("%d", &hd.sl[i]);
        printf("Nhap gia thanh sach: ");
        scanf("%d", &hd.gia[i]);
        hd.tongTien += hd.sl[i]*hd.gia[i];
    }
}

StackHD *createNodeHD(hoadon hd)
{
    StackHD *new_node;
    new_node = (StackHD *) malloc(sizeof(StackHD));
    new_node->data=hd;
    new_node->next=NULL;
    return new_node;
}

bool isEmptyHD(StackHD *top)
{
    return !top;
}

//nhap
void pushHD(StackHD *&top, StackHD *createTop)
{

    if (top == NULL)
    {
        top = createTop;

    }
    else
    {
        createTop->next=top;
        top = createTop;
    }
}

void popHD(StackHD *&top)
{
    if (top == NULL)
        printf("\nKhong co gia tri trong danh sach");
    else
    {
        StackHD *q = top;
        top = top->next;
        free(q);
    }
}

//nhap
void nhapDSS(StackHD *&top, hoadon &hd)
{
    int n;

    do
    {
        printf("\nNhap vao so hoa don: ");
        scanf("%d", &n);
    }
    while (n <= 0);
    for (int i = 0; i < n; i++)
    {
        printf("\n---------------------------------------");
        printf("\nNhap thong tin hoa don %d", i + 1);
        nhapHD(hd);
        pushHD(top, createNodeHD(hd));
    }
}

//xuat
void xuatHD(StackHD *top)
{
    StackHD *p;
    p = top;
    int i=0;

    while (!isEmptyHD(p))
    {
        i++;
        printf("\nTHONG TIN HOA DON THU %d", i);
        printf("\n%10s%15s%15s%15s", "Ma HD","Ngay lap", "Ma KH", "Ma NV");
        printf("\n%10s%15s%15s%15s", p->data.maHD,p->data.date, p->data.maKH, p->data.maNV);
        printf("\nThong tin hang hoa trong hoa don");
        printf("\n%10s%15s%15s%15s", "So TT", "Ma Sach", "So Luong", "Tong Tien");
        int z=0;
        while (z<p->data.soSP)
        {
            printf("\n%10d%15d%15d%15d",z+1, p->data.mannagerSP[z], p->data.sl[z], p->data.tongTien);
            z++;
        }
        p = p->next;
    }
}

void xuat800HD(StackHD *hd)
{
    StackHD *p;
    p = hd;
    printf("\nDanh sach hoa don co tong tien tren 800: ");
    int i=0;
    while (p != NULL)
    {
        if(p->data.tongTien>800)
        {
            i++;
            printf("\nThong tin hoa don thu %d", i);
            printf("\n---------------------------------------");
            printf("\n%10s%15s%15s%15s", "Ma HD","Ngay lap", "Ma KH", "Ma NV");
            printf("\n%10s%15s%15s%15s", p->data.maHD, p->data.date, p->data.maKH, p->data.maNV);

            printf("\nThong tin hang hoa trong hoa don");
            printf("\n%10s%15s%15s%15s", "So TT", "Ma Sach", "So Luong", "Tong Tien");
            int z=0;
            while (z<p->data.soSP)
            {
                printf("\n%10d%15d%15d%15d",z+1, p->data.mannagerSP[z], p->data.sl[z], p->data.tongTien);
                z++;
            }
        }
        p = p->next;
    }
}
void searchMaHD(StackHD *hd)
{
    char ma[50];
    printf("\nNhap ma hoa don can tim: ");
    fflush(stdin);
    scanf("%[^\n]s", &ma);
    StackHD *p = hd;
    printf("\nThong tin hoa don tu ma %s", ma);
    while (p != NULL)
    {
        if(strcmp(p->data.maHD, ma)==0)
        {
            printf("\n%10s%15s%15s%15s", "Ma HD","Ngay lap", "Ma KH", "Ma NV");
            printf("\n%10s%15s%15s%15s", p->data.maHD, p->data.date, p->data.maKH, p->data.maNV);
            printf("\nThong tin hang hoa trong hoa don");
            printf("\n%10s%15s%15s%15s", "So TT", "Ma Sach", "So Luong", "Tong Tien");
            int z=0;
            while (z<p->data.soSP)
            {
                printf("\n%10d%15d%15d%15d",z+1, p->data.mannagerSP[z], p->data.sl[z], p->data.tongTien);
                z++;
            }
        }
        p = p->next;
    }

}

//dem
void thongKeHD(StackHD *top)
{
    StackHD *p = top;
    int i = 0, n;
    printf("\nNhap tong tien can kiem tra: ");
    scanf("%d", &n);

    while (p != NULL)
    {
        if (p->data.tongTien > n)
            i++;
        p = p->next;
    }
    if (i == 0)
    {
        printf("Khong co hoa don nao co so luong tren %d.", n);
    }
    else
    {
        printf("So hoa don co so luong lon hon %d la: %d", n, i);
    }
}


void delRearHD(StackHD *&top)
{
    hoadon X;
    StackHD  *q;
    initHD(q);
    if (isEmptyHD(top))
        printf("\nKhong ton tai gia tri trong danh sach");
    else if (top->next == NULL)
    {
        top = NULL;
    }
    else
    {
        while (top != NULL)
        {
            X=top->data;
            pushHD(q, createNodeHD(X));
            popHD(top);
        }
        popHD(q);
        while (q != NULL)
        {
            X=q->data;
            pushHD(top, createNodeHD(X));
            popHD(q);
        }
    }
}

int sizeHD(StackHD *top)
{
    int i = 0;
    StackHD *p = top;
    while (p != NULL)
    {
        i++;
        p = p->next;
    }
    return i;
}

void delMidHD(StackHD *&top)
{
    StackHD *q;
    hoadon hd;
    initHD(q);
    int k;
    do
    {
        printf("\nNhap vi tri can xoa: ");
        scanf("%d", &k);
    }
    while (k < 1 || k > sizeHD(top));
    if (top == NULL)
    {
        printf("\nDanh sach khong co gia tri");
    }
    else if (top->next == NULL)
    {
        top = NULL;
        free(top);
    }
    else
    {
        int z = 0;
        while (top!=NULL)
        {
            z++;
            hd = top->data;
            pushHD(q, createNodeHD(hd));
            if (z == k)
            {
                popHD(q);
            }
            popHD(top);

        }
        while (q != NULL)
        {
            hd=q->data;
            pushHD(top, createNodeHD(hd));
            popHD(q);
        }
    }

}
void sortmaHD(StackHD *&top)
{
    hoadon hd;
    StackHD *tmpStack;
    initHD(tmpStack);
    while (!isEmptyHD(top))
    {
        hd = top->data;
        popHD(top);
        while (!isEmptyHD(tmpStack) && strcmp(tmpStack->data.maHD, hd.maHD)<0)
        {
            pushHD(top, createNodeHD(tmpStack->data));
            popHD(tmpStack);
        }
        pushHD(tmpStack, createNodeHD(hd));
    }
    top = tmpStack;

}

void fileWriteHD(StackHD *top, char *&fileName)
{
    StackHD *x, *y;
    initHD(x);
    initHD(y);
    hoadon hd;
    if (strcmp(fileName, "hoadon.txt") != 0)
    {
        printf("\nNhap ten file(*.txt): ");
        fflush(stdin);
        scanf("%s", fileName);
        strcat(fileName, ".txt");
    }
    FILE *f;
    f = fopen(fileName, "ab");
    y = top;
    while (y!=NULL)
    {
        hd=y->data;
        pushHD(x, createNodeHD(hd));
        popHD(y);
    }
    if (x == NULL)
    {
        printf("\nDanh sach chua co gia tri, nhap truoc khi luu file!");
    }
    if (f == NULL)
    {
        printf("\nLoi khi mo tep");
        exit(1);
    }
    else
    {
        while (x != NULL)
        {
            fwrite(&x->data, sizeof(x->data), 1, f);
            x = x->next;
        }

        fclose(f);
        printf("\nDa luu vao file \"%s\"!", fileName);
    }
}

void fileReadHD(StackHD *&top, char *fileName)
{
    FILE *f;
    initHD(top);
    if (strcmp(fileName, "hoadon.txt") != 0)
    {
        printf("\nNhap ten file(*.txt): ");
        fflush(stdin);
        scanf("%s", fileName);
        strcat(fileName, ".txt");
    }
    StackHD *p;
    hoadon ha;
    f = fopen(fileName, "rb");
    if (f == NULL)
    {
        printf("\nMo file bi loi!");
    }
    else
    {
        while (fread(&ha, sizeof(ha), 1, f) == 1)
        {
            p = (StackHD *) malloc(sizeof(StackHD));
            p->data = ha;
            p->next = NULL;
            pushHD(top, p);
        }
        fclose(f);
    }
}

void easeFileHD(char *fileName)
{
    FILE *f;
    if (strcmp(fileName, "sach.txt") != 0)
    {
        printf("\nNhap ten file can lam sach(*.txt): ");
        fflush(stdin);
        scanf("%s", fileName);
        strcat(fileName, ".txt");
    }
    f = fopen(fileName, "w");
    fclose(f);

}
void menuHD()
{
    StackHD *top;
    hoadon S;
    char *fileNameHD;
    fileNameHD = (char *) malloc(30);
    initHD(top);
    int key = 99;
    while (key != 0)
    {
        system("CLS");
        printf("%*s\n", 40, "****************************************************");
        printf("\n%s", "***       CHUONG TRINH QUAN LY HOA DON            ***");
        printf("\n%s", "***      1.Nhap hoa don vao danh sach             ***");
        printf("\n%s", "***      2.Hien danh sach tu file                 ***");
        printf("\n%s", "***      3.Hien danh hoa don tong tien >800       ***");
        printf("\n%s", "***      4.Tim kiem hoa don theo ma hoa don       ***");
        printf("\n%s", "***      5.Thong ke hoa don co tong tien >X       ***");
        printf("\n%s", "***      6.Xoa thong tin hoa don dau danh sach    ***");
        printf("\n%s", "***      7.Xoa thong tin hoa don cuoi danh sach   ***");
        printf("\n%s", "***      8.Xoa thong tin hoa don vi tri bat ky    ***");
        printf("\n%s", "***      9.Sap xep theo ma hoa don                ***");
        printf("\n%s", "***      10.Tong so hoa don trong cua hang        ***");
        printf("\n%s", "***      11.Lam sach du lieu trong file           ***");
        printf("\n%s", "***      0.Thoat khoi chuong trinh                ***");
        printf("\n%s", "***      Nhap lua chon cua ban:");
        scanf("%d", &key);
        switch (key)
        {
            case 1:
                initHD(top);
                nhapDSS(top, S);
                fileWriteHD(top, fileNameHD);
                printf("\n");
                system("PAUSE");
                break;
            case 2:
                initHD(top);
                fileReadHD(top, fileNameHD);
                printf("\nDanh sach hoa don tu file: ");
                xuatHD(top);
                printf("\n");
                system("PAUSE");
                break;
            case 3:
                fileReadHD(top, fileNameHD);
                xuat800HD(top);
                printf("\n");
                system("PAUSE");
                break;
            case 4:
                fileReadHD(top, fileNameHD);
                searchMaHD(top);
                printf("\n");
                system("PAUSE");
                break;
            case 5:
                fileReadHD(top, fileNameHD);
                thongKeHD(top);
                printf("\n");
                system("PAUSE");
                break;
            case 6:
                fileReadHD(top, fileNameHD);
                popHD(top);
                printf("\nDanh sach vua xoa dau danh sach!");
                xuatHD(top);
                printf("\n");
                system("PAUSE");
                break;
            case 7:
                fileReadHD(top, fileNameHD);
                delRearHD(top);
                printf("\nDanh sach vua xoa cuoi danh sach!");
                xuatHD(top);
                printf("\n");
                system("PAUSE");
                break;
            case 8:
                fileReadHD(top, fileNameHD);
                delMidHD(top);
                xuatHD(top);
                printf("\n");
                system("PAUSE");
                break;
            case 9:
                fileReadHD(top, fileNameHD);
                sortmaHD(top);
                xuatHD(top);
                printf("\n");
                system("PAUSE");
                break;

            case 10:
                fileReadHD(top, fileNameHD);
                printf("\nTong so hoa don la: %d", sizeHD(top));
                printf("\n");
                system("PAUSE");
                break;
            case 11:
                fileReadHD(top, fileNameHD);
                easeFileHD(fileNameHD);
                printf("\nLam sach thanh cong!");
                printf("\n");
                system("PAUSE");
                break;
            case 0:
                break;
            default:
                printf("\nBan nhap sai, xin vui long nhap lai!");
                printf("\n");
                system("PAUSE");
                break;
        }

    }
}

void menuSACH()
{
    StackS *top;
    sach S;
    char *fileName;
    fileName = (char *) malloc(30);
    initSach(top);
    int key = 99;
    while (key != 0)
    {
        system("CLS");
        printf("%*s\n", 40, "****************************************************");
        printf("\n%s", "***       CHUONG TRINH QUAN LY SACH               ***");
        printf("\n%s", "***      1.Nhap sach vao dau danh sach            ***");
        printf("\n%s", "***      2.Hien danh sach tu file                 ***");
        printf("\n%s", "***      3.Hien danh sach cuon sach gia >500      ***");
        printf("\n%s", "***      4.Tim kiem sach theo ma sach             ***");
        printf("\n%s", "***      5.Thong ke so dau sach gia lon hon X     ***");
        printf("\n%s", "***      6.Xoa thong tin sach o dau danh sach     ***");
        printf("\n%s", "***      7.Xoa thong tin sach o cuoi danh sach    ***");
        printf("\n%s", "***      8.Xoa thong tin sach o vi tri bat ky     ***");
        printf("\n%s", "***      9.Sap xep theo ten sach                  ***");
        printf("\n%s", "***      10.Tong so dau sach trong cua hang       ***");
        printf("\n%s", "***      11.Lam sach du lieu trong file           ***");
        printf("\n%s", "***      0.Thoat khoi chuong trinh                ***");
        printf("\n%s", "***      Nhap lua chon cua ban:");
        scanf("%d", &key);
        switch (key)
        {
            case 1:
                initSach(top);
                nhapDSS(top, S);
                fileWrite(top, fileName);
                printf("\n");
                system("PAUSE");
                break;
            case 2:
                fileRead(top, fileName);
                printf("\nDanh sach quyen sach tu file: ");
                xuatSach(top);
                printf("\n");
                system("PAUSE");
                break;
            case 3:
                fileRead(top, fileName);
                xuat500(top);
                printf("\n");
                system("PAUSE");
                break;
            case 4:
                fileRead(top, fileName);
                searchMa(top);
                printf("\n");
                system("PAUSE");
                break;
            case 5:
                fileRead(top, fileName);
                thongKeSL(top);
                printf("\n");
                system("PAUSE");
                break;
            case 6:
                fileRead(top, fileName);
                popS(top);
                printf("\nDanh sach vua xoa dau danh sach!");
                xuatSach(top);
                printf("\n");
                system("PAUSE");
                break;
            case 7:
                fileRead(top, fileName);
                delRear(top);
                printf("\nDanh sach vua xoa cuoi danh sach!");
                xuatSach(top);
                printf("\n");
                system("PAUSE");
                break;
            case 8:
                fileRead(top, fileName);
                delMid(top);
                xuatSach(top);
                printf("\n");
                system("PAUSE");
                break;
            case 9:
                fileRead(top, fileName);
                sortTenSach(top);
                xuatSach(top);
                printf("\n");
                system("PAUSE");
                break;

            case 10:
                fileRead(top, fileName);
                printf("\nTong so sach trong cua hang la: %d", sizeS(top));
                printf("\n");
                system("PAUSE");
                break;
            case 11:
                fileRead(top, fileName);
                easeFile(fileName);
                printf("\nLam sach thanh cong!");
                printf("\n");
                system("PAUSE");
                break;
            case 0:
                break;
            default:
                printf("\nBan nhap sai, xin vui long nhap lai!");
                printf("\n");
                system("PAUSE");
                break;
        }

    }
}

int main()
{
    int x;
    while (true)
    {
        system("CLS");
        printf("%*s\n", 40, "****************************************************");
        printf("\n%s", "***          CHUONG TRINH QUAN LY BAN SACH        ***");
        printf("\n%s", "================== Thuat toan Stack =================");
        printf("\n%s", "***          1.Quan ly sach trong cua hang        ***");
        printf("\n%s", "***          2.Quan ly hoa don                    ***");
        printf("\n%s", "***          0.Thoat khoi chuong trinh            ***");
        printf("\n%s", "***          Nhap lua chon cua ban:");
        scanf("%d", &x);
        switch (x)
        {
            case 1:
                menuSACH();
                printf("\n");
                system("PAUSE");
                break;
            case 2:
                menuHD();
                printf("\n");
                system("PAUSE");
                break;
            case 0:
                exit(0);
                break;
            default:
                printf("\nBan nhap sai, xin vui long nhap lai!");
                printf("\n");
                system("PAUSE");
                break;
        }
    }
    return 0;
}

