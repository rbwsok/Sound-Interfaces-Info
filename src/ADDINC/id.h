#ifndef _PRODUCTMANID_H_
#define _PRODUCTMANID_H_

struct MANID
{
 int code;
 char *name;
};

struct PRODUCTID
{
 int mcode;
 int pcode;
 char *name;
};

extern MANID ManID[];
extern PRODUCTID ProdID[];
char* GetManString(int n);
char* GetProductString(int m, int p);

#endif
