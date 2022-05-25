#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int high, width;
int myplane_x, myplane_y;
int bullet_x, bullet_y;
int enemy_x, enemy_y;
int choice, decelerate = 10;
int score = 0;

char myplane_shape='本',enemy_shape='敌',bullet_shape='|';

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
    CONSOLE_CURSOR_INFO cursor_info={1,0};//第二个值为0表示隐藏光标
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}


void startup()
{
    high = 25;
    width = 30;

    myplane_x = high / 2;
    myplane_y = width / 2;

    bullet_x = -1; //初始不显示
    bullet_y = myplane_y;

    enemy_x = 0;
    enemy_y = width / 2;
}

void show()
{
    int i, j;

    gotoxy (0,0);

    for (i = 0; i < high; i++) //双循环遍历位置，放置符号
    {
        for (j = 0; j < width; j++)
        {
            if ((i == myplane_x) && (j == myplane_y))
            {
                printf("%c",myplane_shape);
            }
            else if ((i == bullet_x) && (j == bullet_y))
            {
                printf("%c",bullet_shape);
            }
            else if ((i == enemy_x) && (j == enemy_y))
            {
                printf("%c",enemy_shape);
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n\n  Score: %d\n", score);
}

void updateWithInout() //与输入you关
{
    char input;
    if (kbhit())
    {
        input = getch();

        if (input == 'a')
        {
            myplane_y--;
        }
        if (input == 'd')
        {
            myplane_y++;
        }
        if (input == 'w')
        {
            myplane_x--;
        }
        if (input == 's')
        {
            myplane_x++;
        }

        if ((bullet_x == -1) && (input == ' ')) //不让子弹吸回来
        {
            bullet_x = myplane_x - 1;
            bullet_y = myplane_y;
        }
    }
}

void updateWithoutInput() //与输入wu关
{
    if ((bullet_x == enemy_x) && (bullet_y == enemy_y)) //
    {
        score++;
        enemy_x = 0;
        enemy_y = rand() % width;
        bullet_x = -1;
    }
    if ((myplane_x == enemy_x) && (myplane_y == enemy_y)) //
    {
        score-=10;
        enemy_x = 0;
        enemy_y = rand() % width;
    }

    if (bullet_x > -1)
    {
        bullet_x--;
    }

    static int ten2one = 0; //多次调用才判定一次敌机状态  静态变量函数结束也存在
    if (ten2one < decelerate)
        ten2one++;
    if (ten2one == decelerate)
    {
        if (enemy_x > high)
        {
            enemy_x = 0;
            enemy_y = rand() % width;
        }
        else
        {
            enemy_x++;
        }
        ten2one = 0;
    }

    // Sleep (decelerate); //导致整个游戏的操作都变慢
}

void choosespeed();

int main(int argc, char const *argv[])
{
    //system("color F0");
    HideCursor();

    //choosespeed(); //选择难度，即敌机行驶速度

    startup();

    while (1)
    {
        show();
        updateWithoutInput();
        updateWithInout();
    }
    return 0;
}

void choosespeed()
{
    printf("choose enemy speed:\n");
    printf("1:noob  2:norme  3:master\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        decelerate = 10;
        break;

    case 2:
        decelerate = 5;
        break;

    case 3:
        decelerate = 0;
        break;

    default:
        printf("?");
        break;
    }
}

//复杂形状
//积分增加 敌机速度增加
//敌机数量
//ESC暂停
//防止飞机出界
//击中多次才击毁
//爆炸特效
