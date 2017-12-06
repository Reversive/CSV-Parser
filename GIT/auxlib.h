#ifndef AUXLIB_H
#define AUXLIB_H

#define charToInt(x) (x - '0')
#define MAXLINE 80
#define CZERODIV(X, Y) ((Y != 0) ? (((double)X)/(Y)) : 0.f)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int getline(char line[], int max);

#endif
