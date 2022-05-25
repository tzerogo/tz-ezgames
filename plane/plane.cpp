#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h> //不用回车

#include <time.h>

int main(int argc, char const *argv[])
{
    int i = 0, j = 0;
    int x = 10;
    int y = 5;
    char input;
    int isFire = 0;
    int ny = 0;
    int isKilled = 0;
    int score = 0;
    clock_t start, stop;
    double s=1;
    double speed=0;

    start = clock();

    srand((unsigned)time(0));
    ny = rand() % x + 2;

    while (1)
    {
        system("cls");

        if (isKilled == 1)
        {
            ny = rand() % x + 2;
            isKilled = 0;
        }
        {
            for (i = 0; i < ny; i++)
            {
                printf(" ");
            }
            printf("+\n");
        }

        if (isFire == 0)
        {
            for (i = 0; i < x; i++)
            {
                printf("\n");
            }
        }
        else
        {
            for (i = 0; i < x; i++)
            {
                for (j = 0; j < y; j++)
                {
                    printf(" ");
                }
                printf(" |\n"); // fire
            }

            if (y + 1 == ny)
            {
                isKilled = 1;
                score++;
                printf("\a");
            }

            isFire = 0;
        }

        { // plane structure
            for (j = 0; j < y; j++)
            {
                printf(" ");
            }
            printf(" ^\n");
            for (j = 0; j < y; j++)
            {
                printf(" ");
            }
            printf("/W\\");
            printf("\n");
            for (j = 0; j < y; j++)
            {
                printf(" ");
            }

            printf(" V\n");
        }

        { //得分
            stop = clock();
            s = (stop - start) / CLK_TCK;
            speed=score / s*100;
            printf("\n\n\n\n\n");
            printf(" Score:%d \n", score);
            printf(" Time:%.2lfs\n", s);
            printf(" Speed:%.2lf%%\n", speed);

            printf("\n\n\n");
            if (speed>70) 
            {
                printf("   You Are so Fast!\n");
            }
            if (speed>=45&&speed<=70)
            {
                printf ("   Keep It.\n");
            }
            if (speed<45)
            {
                printf("   Too Slow!\n");
            }
            if (score>99&&score<110) 
            {
                printf ("\n\n");
                printf ("   You have a lot of perseverance.\n");
            }
        }

        input = getch();
        if (input == 's')
        {
            x++;
        }
        if (input == 'w')
        {
            x--;
        }
        if (input == 'a')
        {
            y--;
        }
        if (input == 'd')
        {
            y++;
        }
        if (input == ' ')
        {
            isFire = 1;
        }
    }

    Sleep(5000);
    return 0;
}
