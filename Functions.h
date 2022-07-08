#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <conio.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define Sprint 15
using namespace std;
bool GO;
const int W = 40;
const int H = 20;
int x, y, FOODX, FOODY, score;
int TX[100], TY[100];
int nT;
bool END = false;
int speed = 50;
enum ED
{
    STOP = 0,

    LEFT,
    RIGHT,
    UP,
    DOWN
};

ED dir;

void border()
{
    for (int i = 0; i < W + 2; i++)
        cout << "#";
    cout << endl;
}
void HBorder()
{
    for (int i = 0; i < W / 2; i++)
        cout << "#";
    cout << endl;
}
void SetGame()
{
    GO = false;
    dir = STOP;
    x = W / 2;
    y = H / 2;
    FOODX = rand() % W;
    FOODY = rand() % H;
    score = 0;
}
void GAmeOVer()
{
    border();
    cout << "               Game Over" << endl;
    border();
}

void windowSize()
{
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);

    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 334, 550, TRUE);
    system("color 73");
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

    short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
    short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

    short scrBufferWidth = scrBufferInfo.dwSize.X;
    short scrBufferHeight = scrBufferInfo.dwSize.Y;

    COORD newSize;
    newSize.X = scrBufferWidth;
    newSize.Y = winHeight;
    int Status = SetConsoleScreenBufferSize(hOut, newSize);
    if (Status == 0)
    {
        cout << "SetConsoleScreenBufferSize() failed! Reason : " << GetLastError() << endl;
        exit(Status);
    }

    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
    cout << "Screen Buffer Size : " << scrBufferInfo.dwSize.X << " x " << scrBufferInfo.dwSize.Y << endl;
}

void Start()
{
    system("cls");
    border();
    if (x >= W - 1)
    {
        system("cls");
        GAmeOVer();
        speed = 1000;
        cout << "         Press [R] to Restart " << endl;
    }
    else
    {
        cout << "                    Score:" << score << endl;
        cout << "  Press [G] to slow down " << endl;
        cout << "  Press [F] to speed up " << endl;
        cout << "  Press [R] to Restart " << endl;
        cout << "  Press [Any arrow] to start" << endl;
        cout << " " << endl;
    }
    border();
    for (int i = 0; i < W + 2; i++)
        cout << "_";
    cout << endl;

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            string head = "V";
            if (j == 0)
                cout << "*";
            if (i == y && j == x)
            {
                cout << head;
            }
            else if (i == FOODY && j == FOODX)
                cout << "0";
            else
            {
                bool print = false;
                for (int k = 0; k < nT; k++)
                {
                    if (TX[k] == j && TY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == W - 1)
                cout << "*";
        }
        cout << endl;
    }

    for (int i = 0; i < W + 2; i++)
        cout << "_";
    cout << endl;
    // Timer();
}

void Physics()
{
    int prevX = TX[0];
    int prevY = TY[0];
    int prev2X, prev2Y;
    TX[0] = x;
    TY[0] = y;
    for (int i = 1; i < nT; i++)
    {
        prev2X = TX[i];
        prev2Y = TY[i];
        TX[i] = prevX;
        TY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x >= W - 1)
    {
        GAmeOVer();
    }

    if (x < 0)
        x = W - 1;
    if (y >= H)
        y = 0;
    else if (y < 0)
        y = H - 1;

    for (int i = 0; i < nT; i++)
        if (TX[i] == x && TY[i] == y)
            GO = false;

    if (x == FOODX && y == FOODY)
    {
        score += 10;
        FOODX = rand() % W;
        FOODY = rand() % H;
        nT++;
    }
}

void Move()
{

    if (_kbhit())
    {
        switch (_getch())
        {
        case KEY_UP:
            dir = UP;
            break;
        case KEY_DOWN:
            dir = DOWN;
            break;
        case KEY_LEFT:
            dir = LEFT;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case 'f':
            system("color 84");
            speed = 0;
            break;
        case 'r':
            speed = 50;
            windowSize();
            SetGame();
            while (!GO)
            {
                Start();
                Move();
                Physics();
                Sleep(speed);
            }
            break;
        case 'g':
            system("color 73");
            speed = 50;
            break;
        }
    }
}

void Game()
{
    windowSize();
    SetGame();
    while (!GO)
    {
        Start();
        Move();
        Physics();
        Sleep(speed);
    }
}

#endif
