#include    <stdio.h>    
#include    <stdlib.h>
#include    <windows.h>

// #include<mmsystem.h>
// #pragma comment(lib, "WINMM.LIB")
//PlaySound(TEXT("Data\\1.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
// 失败的播放wav音效




void toxy(int x,int y)    
{
	COORD pos={x,y};
	HANDLE Out=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Out,pos);
}

int main(int argc, char const *argv[])
{
    
int i=0,j=0;
int x=1,y=10;
int velocity_x=1,velocity_y=1;
int left=1,right=80,top=1,bottom=20;

int q,w,e,r;

while (1)
{
    

    system("cls");

    // {
    //     for ( q = 0; q < right; q++)
    //     {
    //         printf("_");
    //     }
    //     for (w=0;w<bottom;w++)
    //     {
    //         printf("|");
    //         for ( e = 0; e < right; e++)
    //         {
    //         printf(" ");
    //         }
    //         printf("|\n");
    //     }
    //     for ( r = 0; r < right; r++)
    //     {
    //         printf("_");
    //     }
        
    //     toxy(0, 0);
    // }//奇怪的边框

    x=x+velocity_x;
    y=y+velocity_y;

    for ( i = 0; i < x; i++)
    {
    printf ("\n");
    }
    
//printf ("|");//配合边框

    for ( j = 0; j < y; j++)
    {
    printf(" ");
    }
    printf ("^V^");
    

    _sleep(30);
    
    if ((x==top)||(x==bottom))
    {
        velocity_x=-velocity_x;
        printf ("\a");
    }
    if ((y==left)||(y==right))
    {
        velocity_y=-velocity_y;
        printf ("\a");
    }
  
    
}

}