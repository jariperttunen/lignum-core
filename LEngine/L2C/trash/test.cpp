#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "ldefs.h"
#include "stdmods.h"

#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif


module A();
module B(int,float);
module C();
module D(int,int);
module E();
module F();
module G();
module H();
module I(int);
module J();
module K();
module L();


FILE* fp;


Start:
{
  fp = fopen("input.txt", "r");
  fputc('A', fp);
  int n=0;
  for (n=0; n<1010; n++)
	printf("%d --> \n", n);
}

End:
{
  fclose(fp);
}


derivation length: 51 - strlen("module and produce");

void Func(Struct* pS)
{
  for (int i=0; i<123; i++)
    pS->arr[i] = 1.0/i;
}

A() >  LBRCT() B(a,b)  RBRCT() :
{
  produce B(a,b) A();
}

A() >   LBRCT() B(a,b) LBRCT() C() RBRCT() RBRCT() :
{
  produce A(n, s) LBRCT() B(a,b)  C() RBRCT();
}

A() > LBRCT() B(a,b) LBRCT() C() RBRCT() F() RBRCT() :
{
  produce A() LBRCT() C() RBRCT() B(a,b) F();
}

A() > LBRCT() RBRCT()  LBRCT() H() I(c) RBRCT()  :
{
  produce  A() I(c) H();
}

A() > LBRCT() B(a,b) RBRCT() LBRCT() H() RBRCT() K():
{
  produce A() LBRCT()B(a,b)RBRCT() LBRCT()H()RBRCT() K() L();
}

A()K() < L():
{
  produce L()I(1);
}

A() LBRCT() B(a,b) LBRCT() C()   < D(c,d):
{
  produce D(c,d) I(1);
}


