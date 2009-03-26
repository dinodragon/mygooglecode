/**************************************************
    解迷宫问题

                 程序设计：杨飞
				 http://yangfei.vicp.cc
***************************************************/

#include <stdio.h>
#define M 12

int mark[M][M],top=0,t=0;

struct{int x;
       int y;
       int z;
       }s[(M-1)*(M-1)];

int move[4][2]={0,1,1,0,0,-1,-1,0};

int maze[M][M]={1,1,1,1,1,1,1,1,1,1,1,1,
                1,0,0,0,0,0,1,1,0,0,0,1,
                1,1,0,0,0,1,1,0,1,1,1,1,
                1,0,1,1,0,0,0,0,1,1,1,1,
                1,1,1,0,0,1,1,1,0,1,1,1,
                1,1,1,0,1,0,0,1,0,1,1,1,
                1,0,0,0,1,0,1,1,1,0,1,1,
                1,0,1,1,1,0,0,0,1,1,1,1,
                1,0,0,1,1,0,1,0,0,1,1,1,
                1,1,0,0,0,0,1,1,0,1,1,1,
                1,0,0,1,1,1,1,0,0,0,0,1,
                1,1,1,1,1,1,1,1,1,1,1,1,
                };
void fun(int i,int j,int k)
     {
       if(i+move[k][0]==M-2&&j+move[k][1]==M-1)
        {for(t=0;t<top;t++)
          printf("X:%d\tY:%d\t->:%d\n",s[t].x,s[t].y,s[t].z);
          return;
         }
      if(maze[i+move[k][0]][j+move[k][1]]==0&&mark[i+move[k][0]][j+move[k][1]]==0)
       {s[top].x=i;
        s[top].y=j;
        s[top].z=k;
         ++top;
        mark[i][j]=1;
        fun(i+move[k][0],j+move[k][1],0);
        }
          else if(k<3) fun(i,j,k+1);
            else if(top==0)  printf("Wrong away!\n");
                   else{--top;
                        fun(s[top-1].x,s[top-1].y,s[top-1].z);}
        }
void main()
{int i=1,j=1,k=0;
 fun(i,j,k);
}