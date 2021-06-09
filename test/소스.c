#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

//콘솔 창의 크기와 제목을 지정하는 함수
void SetConsoleView()
{
    system("mode con:cols=100 lines=25");
    system("title Google Dinosaurs. By BlockDMask");
}

//커서의 위치를 x, y로 이동하는 함수
void GotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//키보드의 입력을 받고, 입력된 키의 값을 반환하는 함수
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
    const int gravity = 3; // js와 같은 개념의 const

    int dinoY = DINO_BOTTOM_Y;
    int treeX = TREE_BOTTOM_X;

    while (1)
    {
        //z키가 눌렸고, 바닥이 아닐때만 점프가능.
        if (GetKeyDown() == 'z' && isBottom)
        {
            isJumping = 1;
            isBottom = 0;
        }

        //점프중 = y감소
        //점프끝 = y증가
        if (isJumping)
        {
            dinoY -= gravity;
        }
        else
        {
            dinoY += gravity;
        }

        //Y가 계속해서 증가하는걸 막기위해 바닥을 지정.
        //Y가 증가한다는 것은 공룡이 아래로 내려온다는 뜻.
        if (dinoY >= DINO_BOTTOM_Y)
        {
            dinoY = DINO_BOTTOM_Y;
            isBottom = 1;
        }

        //점프의 맨 위를 찍으면 점프가 끝난 상황
        if (dinoY <= 3)
        {
            isJumping = 0;
        }

        //나무가 왼쪽으로 가도록 하고(x의 음수방향)
        //나무의 위치가 왼쪽 끝으로가면 다시 초기 위치로 소환
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