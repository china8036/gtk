#include<stdio.h>
#include<stdlib.h>
#include "sys/malloc.h"

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
peB eb0,eb1;
int init_eB(void){
eb0 = (peB)malloc(sizeof(eB));
eb1 = (peB)malloc(sizeof(eB));
eb0->x = 100;
eb0->y = 200;
eb0->next = eb1;
eb1->pre = eb0;
eb1->x = 108;
eb1->y = 200;
return 0;
}
