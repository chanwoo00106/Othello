#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

//�ܼ� â�� ũ��� ������ �����ϴ� �Լ�
void SetConsoleView()
{
    system("mode con:cols=100 lines=25");
    system("title Google Dinosaurs. By BlockDMask");
}

//Ŀ���� ��ġ�� x, y�� �̵��ϴ� �Լ�
void GotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//Ű������ �Է��� �ް�, �Էµ� Ű�� ���� ��ȯ�ϴ� �Լ�
int GetKeyDown()
{
    if (_kbhit() != 0)
    {
        return _getch();
    }
    return 0;
}

void DrawDino(int dinoY)
{
    GotoXY(0, dinoY);
    static int legFlag = 1;
    printf("        $$$$$$$ \n");
    printf("       $$ $$$$$$\n");
    printf("       $$$$$$$$$\n");
    printf("$      $$$      \n");
    printf("$$     $$$$$$$  \n");
    printf("$$$   $$$$$     \n");
    printf(" $$  $$$$$$$$$$ \n");
    printf(" $$$$$$$$$$$    \n");
    printf("  $$$$$$$$$$    \n");
    printf("    $$$$$$$$    \n");
    printf("     $$$$$$     \n");
    if (legFlag)
    {
        printf("     $    $$$    \n");
        printf("     $$          ");
        legFlag = 0;
    }
    else
    {
        printf("     $$$  $     \n");
        printf("          $$    ");
        legFlag = 1;
    }
}

void DrawTree(int treeX)
{
    GotoXY(treeX, TREE_BOTTOM_Y);
    printf("$$$$");
    GotoXY(treeX, TREE_BOTTOM_Y + 1);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 2);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 3);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 4);
    printf(" $$ ");
}

int main(void)
{
    SetConsoleView();
    
    int isJumping = 0;
    int isBottom = 1;
    const int gravity = 3; // js�� ���� ������ const

    int dinoY = DINO_BOTTOM_Y;
    int treeX = TREE_BOTTOM_X;

    while (1)
    {
        //zŰ�� ���Ȱ�, �ٴ��� �ƴҶ��� ��������.
        if (GetKeyDown() == 'z' && isBottom)
        {
            isJumping = 1;
            isBottom = 0;
        }

        //������ = y����
        //������ = y����
        if (isJumping)
        {
            dinoY -= gravity;
        }
        else
        {
            dinoY += gravity;
        }

        //Y�� ����ؼ� �����ϴ°� �������� �ٴ��� ����.
        //Y�� �����Ѵٴ� ���� ������ �Ʒ��� �����´ٴ� ��.
        if (dinoY >= DINO_BOTTOM_Y)
        {
            dinoY = DINO_BOTTOM_Y;
            isBottom = 1;
        }

        //������ �� ���� ������ ������ ���� ��Ȳ
        if (dinoY <= 3)
        {
            isJumping = 0;
        }

        //������ �������� ������ �ϰ�(x�� ��������)
        //������ ��ġ�� ���� �����ΰ��� �ٽ� �ʱ� ��ġ�� ��ȯ
        treeX -= 2;
        if (treeX <= 0)
        {
            treeX = TREE_BOTTOM_X;
        }

        DrawDino(dinoY);    //draw dino
        DrawTree(treeX);    //draw tree
        Sleep(80);
        system("cls");    //clear
    }
    system("pause");
    return 0;
}