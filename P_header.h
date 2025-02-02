#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct ArrayTable {
char name[10];
int dim; 
char size1[10];
char size2[10];
};
struct ArrayTable AT[20];


struct ParseTable {
char oper[10]; 
char lhs[10]; 
char rhs1[10];
char rhs2[10]; 
};
struct ParseTable PT;

int P_dot;
int P_sum;
int P_aver;
int aCount=0;