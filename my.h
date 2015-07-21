#include<stdio.h>
#include<stdlib.h>
#include "sys/malloc.h"
#define R 4
#define B 360
//链表用于存储蛇的每个元素
typedef struct eBlock
{
  struct Eblock *pre;
  double x;
  double y;
  struct Eblock *next;
}eB, *peB;
struct eDir{
  int x;//x方向
  int y; //y方向
};
peB eb[10];
int init_eB(void){
eb[0] = (peB)malloc(sizeof(eB));
eb[1] = (peB)malloc(sizeof(eB));
eb[2] = (peB)malloc(sizeof(eB));
eb[0]->x = 100;
eb[0]->y = 200;
eb[0]->next = eb[1];
eb[1]->pre = eb[0];
eb[1]->x = 108;
eb[1]->y = 200;
eb[2]->x = 200;
eb[2]->y = 210;
eb[1]->next = eb[2];
eb[2]->pre = eb[1];
eb[2]->next = eb[0];
return 0;
}
