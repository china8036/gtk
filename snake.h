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

int dot_num, width, height;
peB eb0 ,eb_p,eb_n,eb_tmp;

peB insert_one_eB(peB p,peB n, double x, double y){
 peB tmp = (peB)malloc(sizeof(eB));
 tmp->x = x;
 tmp->y = y;
 tmp->next = n;
 tmp->pre = p;
 return tmp; 
}

int init_eB(void){
	dot_num = (int)(B*B/(R*2*2*R));//屏幕上点数
    width = height = (int)(B*(2*R));
	peB all_dot[dot_num];
    eb0 = (peB)malloc(sizeof(eB));
    eb0->x = R;
    eb0->y = R;
    eb_p = eb0;
    for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
    		//printf("i:%d,j:%d", i, j);
            eb_tmp = insert_one_eB(eb_p,NULL,(2*i+1)*R,(2*j+1)*R);
            eb_p->next = eb_tmp;
            eb_p = eb_tmp;
		}
    }
    eb_p->next = eb0; 
    return 0;
}
