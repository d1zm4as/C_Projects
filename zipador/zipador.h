/* zipador.h */
#pragma once
#define _GNU_SOURCE
#define $c (char *)
#define $i (int)
#define $v (void *)
#define $8 (int8 *)
#define $6 (int16)
#define $2 (int32)
#define $4 (int64)
#define alloc(x) malloc($i(x))
#define destroy(x) free ((x))
#define ralloc(x,y) realloc((x),$i(y))
#define show(x) _Generic((x), \
amtlist*: showamtlist) \
(#x, (amtlist*)(x))


#define Blocksize 0xffff
#define Maxcap ((0xffffffff/8)-Blocksize-1)


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
// #include <birchutils.h>

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;

struct s_amtentry
{
    int32 block;
    int32 amt;
};

typedef struct s_amtentry amtentry;

struct s_amtlist
{
    int32 capacity;
    int32 lenght;
    amtentry data[];
};

typedef struct s_amtlist amtlist;

// construtores

amtlist *mkamtlist(void);

bool amtadd(amtlist*,amtentry);
bool increase(amtlist** );
void showamtlist(const char*,amtlist*);
void zero(int8*, int32);

int main(void);
