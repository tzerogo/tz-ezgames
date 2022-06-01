#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h> //发射子弹的冷却

int height = 25, width = 50;
int myplane_x, myplane_y;
int bullet0_x[25] = {0}, bullet0_y[25] = {0}; //初始不显示
int enemy_x[99] = {0}, enemy_y[99];
int health_x, health_y;
int choice, decelerate = 10, gradual = 0; //游戏难度
int score = 0;
int damage = 0, game = 1, opo = 1, health = 2, creathealth = 0, limit = -21; //受损状态、游戏结束、健康血量显示
int tryagain = 0;                                                            //快速重开
int esc = 1;                                                                 //暂停功能
int enemynum = 1, enemyget = 0;
int bullet0num = 25, bullet0get = 0, order = 0;
int p = 0, q = 0;
clock_t start_t;
double CD = 0.6;
char model[20];
int escape = 0;

char myplane_shape = 'M', enemy_shape = '@', bullet0_shape = '|', health_shape = '$';

void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0}; //第二个值为0表示隐藏光标
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()
{
    myplane_x = height / 2;
    myplane_y = width / 2;

    enemy_y[0] = width / 2;

    health_x = -1;
    health_y = myplane_y;
}

void show()
{
    int i, j;

    gotoxy(0, 0);

    if (score <= 9) //判断敌机数量
    {
        enemynum = 1;
    }
    else
    {
        enemynum = score / 10 + 1;
    }

    for (i = 0; i < height; i++) //双循环遍历位置，放置符号 excellent
    {
        for (j = 0; j < width; j++)
        {

            for (p = 0; p < enemynum; p++)
            {
                if ((i == enemy_x[p]) && (j == enemy_y[p]))
                {
                    enemyget = 1;
                }
            }
            for (p = 0; p < bullet0num; p++)
            {
                if ((i == bullet0_x[p]) && (j == bullet0_y[p]))
                {
                    bullet0get = 1;
                }
            }

            //产生边框

            if (i == 0)
            {
                printf("_");
            }
            else if ((i == height - 1) && (j != 0) && (j != width - 1))
            {
                printf("_");
            }
            else if ((i > 0) && (j == 0))
            {
                printf("|");
            }
            else if ((i > 0) && (j == width - 1))
            {
                printf("|");
            }
            else if (enemyget == 1)
            {
                printf("%c", enemy_shape);
            }
            else if ((i == myplane_x) && (j == myplane_y))
            {
                printf("%c", myplane_shape);
            }
            else if (bullet0get == 1)
            {
                printf("%c", bullet0_shape);
            }

            else if ((i == health_x) && (j == health_y))
            {
                printf("%c", health_shape);
            }
            else
            {
                printf(" ");
            }

            enemyget = 0;
            bullet0get = 0;
        }
        printf("\n");
    }
    printf("\n\n Score:%3d  Health:%2d  Escape:%2d   Model:%s\n", score, health - damage, escape, model);

    if (esc == -1)
    {
        printf("\n--------------------  PAUSE  ---------------------\n\n                ");
        system("pause");
        esc = 1;
        system("cls");
    }
}

void updateWithInout() //与输入有关
{
    char input;
    if (kbhit())
    {
        input = getch();

        if ((input == 'a') && (myplane_y > 1))
        {
            myplane_y--;
        }
        if ((input == 'd') && (myplane_y < width - 2))
        {
            myplane_y++;
        }
        if ((input == 'w') && (myplane_x > 1))
        {
            myplane_x--;
        }
        if ((input == 's') && (myplane_x < height - 2))
        {
            myplane_x++;
        }

        if ((input == ' ') && ((double)(clock() - start_t) / CLOCKS_PER_SEC > CD)) //不让子弹吸回来 （改变
        {
            bullet0_x[order] = myplane_x - 1;
            bullet0_y[order] = myplane_y;
            order++;

            start_t = clock();
        }

        if (input == 0x1b)
        {
            esc = -1;
        }
    }
    if (order == bullet0num)
    {
        order = 0;
    }
}

void updateWithoutInput() //与输入无关
{
    for (p = 0; p < enemynum; p++)
    {

        if ((myplane_x == enemy_x[p]) && (myplane_y == enemy_y[p])) //
        {
            damage++;
            score -= 10;
            enemy_x[p] = 0;
            enemy_y[p] = rand() % (width - 2) + 1;
        }
    }

    for (q = 0; q < bullet0num; q++)
    {
        if ((bullet0_x[q] == health_x) && (bullet0_y[q] == health_y)) //
        {
            creathealth = 0;
            health_x = -1;
            health_y = rand() % (width - 2) + 1;
        }

        if (bullet0_x[q] > -1)
        {
            bullet0_x[q]--;
        }
    }

    for (p = 0; p < enemynum; p++)
    {
        for (q = 0; q < bullet0num; q++)
        {
            if ((bullet0_x[q] == enemy_x[p]) && (bullet0_y[q] == enemy_y[p])) //
            {
                score++;
                // printf("\a");
                enemy_x[p] = 0;
                enemy_y[p] = rand() % (width - 2) + 1;
                bullet0_x[q] = -1;
            }
        }
    }

    if ((myplane_x == health_x) && (myplane_y == health_y)) //
    {
        damage--;
        creathealth = 0;
        health_x = -1;
        health_y = rand() % (width - 2) + 1;
    }

    static int ten2one = 0; //多次调用才判定一次敌机状态  静态变量函数结束也存在
    if (ten2one < decelerate)
        ten2one++;
    if (ten2one == decelerate)
    {
        for (p = 0; p < enemynum; p++)
            if (enemy_x[p] > height)
            {
                enemy_x[p] = 0;
                enemy_y[p] = rand() % (width - 2) + 1;
                escape++;
            }
            else
            {
                enemy_x[p]++;
            }
        ten2one = 0;
    }

    if (limit != score)
    {
        if ((score % 10 == -1) || (score % 10 == 1))
        {
            creathealth = 1;
            limit = score;
        }
    }

    static int nine2one = 0;
    if (creathealth == 1)
    {
        if (nine2one < 10)
            nine2one++;
        if (nine2one == 10)
        {
            if (health_x > height)
            {
                health_x = -1;
                health_y = rand() % (width - 2) + 1;
                creathealth = 0;
            }
            else
            {
                health_x++;
            }
            nine2one = 0;
        }
    }

    switch (damage) //实现血量为1后频闪，血量为0结束游戏
    {
    case 0:
        myplane_shape = 'M';
        break;

    case 1:
        if (opo <= 13) //频闪速度
        {
            myplane_shape = ' ';
            opo++;
        }
        if (opo > 13)
        {
            myplane_shape = 'M';
            opo++;
        }
        if (opo == 26)
        {
            opo = 0;
        }

        break;

    case 2:
        game = 0;
        break;

    default:
        break;
    }

    // Sleep (decelerate); //导致整个游戏的操作都变慢
}

void choosespeed();
void SetSize();

int main(int argc, char const *argv[])
{
    char chCmd[64];
    sprintf(chCmd, "mode con cols=%d lines=%d", width, height + 9);
    system(chCmd); //设置控制台大小

    SetConsoleTitle("Strike the Enemy");
    // system("color F0");
    HideCursor();

    choosespeed(); //选择难度，即敌机行驶速度

    startup();

trytry://此处未放到startup前不造成不好影响,可产生重开与续命区别
    while (game == 1)
    {
        show();
        updateWithoutInput();
        updateWithInout();

        if (gradual == 1) // gradual难度 随积分增加难度增加
        {
            if (score == 0)
            {
                decelerate = 10;
                CD = 0.6;
            }
            else if (score == 5)
            {
                decelerate = 7;
                CD = 0.5;
            }
            else if (score == 10)
            {
                decelerate = 5;
                CD = 0.4;
            }
            else if (score == 100)
            {
                decelerate = 2;
                CD = 0.3;
            }
        }
    }

    printf("\nXXXXXXXXXXXXXXXXXX  Game  Over  XXXXXXXXXXXXXXXXXX\n\n      # want try again? just input '1' \n");
    scanf("%d", &tryagain);
    if (tryagain == 1) //避免重复选择难度，快速重开
    {
        tryagain = 0;
        game = 1;
        damage = 0;
        score = 0;
        system("cls");
        goto trytry;
    }

    return 0;
}

void choosespeed()
{
    printf("\n\n            #Select the Model:\n\n\n");
    printf(" 0:Gradual  1:Noob  2:Common  3:Master  -1:CRAZY  \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                       ");
    scanf("%d", &choice);
    switch (choice)
    {
    case -1:
        CD = -1;
        strcpy(model, "CRAZY");
        break;
    case 0:
        gradual = 1;
        strcpy(model, "Gradual");
        break;
    case 1:
        decelerate = 10;
        CD = 0.3;
        strcpy(model, "Noob");
        break;

    case 2:
        decelerate = 5;
        CD = 0.5;
        strcpy(model, "Common");
        break;

    case 3:
        decelerate = 0;
        CD = 0.7;
        strcpy(model, "Master");
        break;

    default:
        printf("?");
        break;
    }
    system("cls");
}

void SetSize(unsigned uCol, unsigned uLine) //调节控制台大小
{
    char cmd[64];
    sprintf(cmd, "mode con cols=%d lines=%d", uCol, uLine);
    system(cmd);
}