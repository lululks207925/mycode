
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

int main(void)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO oldInfo;
    CONSOLE_CURSOR_INFO oldCursor;

    GetConsoleScreenBufferInfo(h, &oldInfo);
    GetConsoleCursorInfo(h, &oldCursor);

    CONSOLE_CURSOR_INFO hidden = oldCursor;
    hidden.bVisible = FALSE;
    SetConsoleCursorInfo(h, &hidden);

    system("cls");

    // 控制爱心跳动的大小
    double sizes[] = {
        0.90, 0.96, 1.04, 1.12,
        1.06, 0.98, 0.93, 1.00,
        1.08, 1.02, 0.94, 0.90,
        0.90, 0.90, 0.90
    };

    int count = sizeof(sizes) / sizeof(sizes[0]);

    for (int t = 0; ; t++)
    {
        double size = sizes[t % count];

        // 光标回到左上角
        COORD pos = {0, 0};
        SetConsoleCursorPosition(h, pos);

        // 设置为亮红色
        SetConsoleTextAttribute(
            h, FOREGROUND_RED | FOREGROUND_INTENSITY
        );

        printf("          BEATING HEART\n\n");

        for (int row = 0; row < 25; row++)
        {
            for (int col = 0; col < 61; col++)
            {
                double x = (col - 30) / (19.0 * size);
                double y = (12 - row) / (8.0 * size);

                double a = x*x + y*y - 1;

                if (a*a*a - x*x*y*y*y <= 0)
                    printf("*");
                else
                    printf(" ");
            }
            printf("\n");
        }

        printf("\n          I LOVE YOU!       \n");
        printf("       Press ESC to exit.   \n");

        fflush(stdout);

        // 每隔90毫秒刷新画面
        Sleep(90);

        // 按ESC结束动画
        if (_kbhit() && _getch() == 27)
            break;
    }

    // 恢复终端原来的设置
    SetConsoleTextAttribute(h, oldInfo.wAttributes);
    SetConsoleCursorInfo(h, &oldCursor);

    printf("\n");
    return 0;
}
