
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define MAX_W 320
#define MAX_H 120

static CHAR_INFO screen[MAX_W * MAX_H];

int head[MAX_W];
int length[MAX_W];
int speed[MAX_W];

int main(void)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO info;
    CONSOLE_CURSOR_INFO oldCursor;

    if (h == INVALID_HANDLE_VALUE ||
        !GetConsoleScreenBufferInfo(h, &info) ||
        !GetConsoleCursorInfo(h, &oldCursor))
    {
        printf("Console initialization failed.\n");
        return 1;
    }

    WORD oldColor = info.wAttributes;

    CONSOLE_CURSOR_INFO cursor = oldCursor;
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(h, &cursor);

    srand((unsigned int)time(NULL));

    const char symbols[] =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // 自定义隐藏文字
    const char *message = "HELLO WORLD";

    int frame = 0;

    // 初始化数字雨
    for (int x = 0; x < MAX_W; x++)
    {
        head[x] = rand() % 50 - 20;
        length[x] = 10 + rand() % 22;
        speed[x] = 1 + rand() % 3;
    }

    while (1)
    {
        // 按ESC退出
        if (_kbhit())
        {
            if (_getch() == 27)
                break;
        }

        if (!GetConsoleScreenBufferInfo(h, &info))
            break;

        int w = info.srWindow.Right -
                info.srWindow.Left + 1;

        int ht = info.srWindow.Bottom -
                 info.srWindow.Top + 1;

        if (w > MAX_W) w = MAX_W;
        if (ht > MAX_H) ht = MAX_H;

        if (w <= 0 || ht <= 1)
            break;

        // 清空画面
        for (int i = 0; i < w * ht; i++)
        {
            screen[i].Char.AsciiChar = ' ';
            screen[i].Attributes = 0;
        }

        // 绘制数字雨
        for (int x = 0; x < w; x++)
        {
            for (int k = 0; k < length[x]; k++)
            {
                int y = head[x] - k;

                if (y < 0 || y >= ht)
                    continue;

                int index = y * w + x;

                int r = rand() %
                    (sizeof(symbols) - 1);

                screen[index].Char.AsciiChar =
                    symbols[r];

                // 头部亮白色
                if (k == 0)
                {
                    screen[index].Attributes =
                        FOREGROUND_RED |
                        FOREGROUND_GREEN |
                        FOREGROUND_BLUE |
                        FOREGROUND_INTENSITY;
                }
                // 前段亮绿色
                else if (k < length[x] / 2)
                {
                    screen[index].Attributes =
                        FOREGROUND_GREEN |
                        FOREGROUND_INTENSITY;
                }
                // 后段暗绿色
                else
                {
                    screen[index].Attributes =
                        FOREGROUND_GREEN;
                }
            }

            // 不同列使用不同速度
            if (frame % speed[x] == 0)
                head[x]++;

            // 数字流重新出现
            if (head[x] - length[x] > ht)
            {
                head[x] = -(rand() % (ht + 10));
                length[x] = 10 + rand() % 22;
                speed[x] = 1 + rand() % 3;
            }
        }

        // 神秘文字循环出现
        int phase = frame % 240;
        int msgLen = (int)strlen(message);

        if (phase >= 45 && phase < 195 &&
            w >= msgLen + 8 && ht >= 8)
        {
            int centerY = ht / 2;
            int startX = (w - msgLen) / 2;

            // 清出中央文字区域
            for (int y = centerY - 1;
                 y <= centerY + 1; y++)
            {
                for (int x = startX - 3;
                     x < startX + msgLen + 3; x++)
                {
                    int index = y * w + x;

                    screen[index].Char.AsciiChar =
                        (y == centerY) ? ' ' : '=';

                    screen[index].Attributes =
                        FOREGROUND_GREEN;
                }
            }

            // 逐字显示隐藏文字
            int show = (phase - 45) / 5 + 1;

            if (show > msgLen)
                show = msgLen;

            for (int i = 0; i < show; i++)
            {
                int index = centerY * w + startX + i;

                screen[index].Char.AsciiChar =
                    message[i];

                screen[index].Attributes =
                    FOREGROUND_RED |
                    FOREGROUND_GREEN |
                    FOREGROUND_BLUE |
                    FOREGROUND_INTENSITY;
            }
        }

        // 底部状态提示
        const char *hint =
            " MATRIX 2.0 | ESC TO EXIT ";

        for (int i = 0; hint[i] && i < w; i++)
        {
            int index = (ht - 1) * w + i;

            screen[index].Char.AsciiChar = hint[i];
            screen[index].Attributes =
                FOREGROUND_GREEN |
                FOREGROUND_INTENSITY;
        }

        // 刷新终端画面
        COORD size = {
            (SHORT)w, (SHORT)ht
        };

        COORD origin = {0, 0};

        SMALL_RECT region = {
            info.srWindow.Left,
            info.srWindow.Top,
            (SHORT)(info.srWindow.Left + w - 1),
            (SHORT)(info.srWindow.Top + ht - 1)
        };

        WriteConsoleOutputA(
            h, screen, size, origin, &region
        );

        frame++;

        // 控制动画速度
        Sleep(50);
    }

    // 恢复终端原来的设置
    SetConsoleTextAttribute(h, oldColor);
    SetConsoleCursorInfo(h, &oldCursor);

    system("cls");
    printf("Matrix 2.0 stopped.\n");

    return 0;
}
