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
  int type;//显示种类闪烁 黑点 空白
  struct Eblock *next;
}eB, *peB;

struct eDir{
  int x;//x方向
  int y; //y方向
};

int dot_num, width, height;
peB eb0 ,eb_p,eb_n,eb_tmp;

peB insert_one_eB(peB p,peB n, double x, double y, int type){
 peB tmp = (peB)malloc(sizeof(eB));
 tmp->x = x;
 tmp->y = y;
 tmp->type= type;
 tmp->next = n;
 tmp->pre = p;
 return tmp; 
}

int init_eB(void){
	dot_num = (int)(B*B/(R*2*2*R));//屏幕上点数
    width = height = (int)(B*(2*R));
	peB all_dot[dot_num];
    eb0 = insert_one_eB(NULL,NULL, R, R, 0);
    eb_p = eb0;
    for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
    		//printf("i:%d,j:%d", i, j);
		if(i==0 && j==0){
           printf("i j k");
			continue;
		}
            eb_tmp = insert_one_eB(eb_p,NULL,(2*i+1)*R,(2*j+1)*R,(int)(i%2));
            eb_p->next = eb_tmp;
            eb_p = eb_tmp;
		}
    }
    eb_p->next = eb0; 
    return 0;
}
