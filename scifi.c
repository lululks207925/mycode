
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define MAX_W 160
#define MAX_H 55

#define GREEN FOREGROUND_GREEN
#define LGREEN (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define RED (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define CYAN (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define YELLOW (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)

static CHAR_INFO screen[MAX_W * MAX_H];
static int W, H;

// 在坐标位置绘制字符
void put(int x, int y, char c, WORD color)
{
    if (x < 0 || x >= W || y < 0 || y >= H)
        return;

    int index = y * W + x;

    screen[index].Char.AsciiChar = c;
    screen[index].Attributes = color;
}

// 绘制文字
void text(int x, int y, const char *s, WORD color)
{
    for (int i = 0; s[i] != '\0'; i++)
        put(x + i, y, s[i], color);
}

// 绘制矩形框
void box(int x, int y, int w, int h, WORD color)
{
    if (w < 2 || h < 2)
        return;

    for (int i = 0; i < w; i++)
    {
        put(x + i, y, '-', color);
        put(x + i, y + h - 1, '-', color);
    }

    for (int i = 0; i < h; i++)
    {
        put(x, y + i, '|', color);
        put(x + w - 1, y + i, '|', color);
    }

    put(x, y, '+', color);
    put(x + w - 1, y, '+', color);
    put(x, y + h - 1, '+', color);
    put(x + w - 1, y + h - 1, '+', color);
}

// 动态能量进度条
void bar(int x, int y, int len, int percent, WORD color)
{
    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;

    for (int i = 0; i < len; i++)
    {
        if (i * 100 < len * percent)
            put(x + i, y, '#', color);
        else
            put(x + i, y, '.', GREEN);
    }
}

int main(void)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO info;
    CONSOLE_CURSOR_INFO oldCursor;

    if (h == INVALID_HANDLE_VALUE ||
        !GetConsoleScreenBufferInfo(h, &info) ||
        !GetConsoleCursorInfo(h, &oldCursor))
    {
        printf("Windows console required.\n");
        return 1;
    }

    WORD oldColor = info.wAttributes;

    CONSOLE_CURSOR_INFO cursor = oldCursor;
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(h, &cursor);

    srand((unsigned int)time(NULL));

    unsigned int frame = 0;
    int paused = 0;

    const char hex[] = "0123456789ABCDEF";

    const char *logs[] = {
        "Virtual core initialized.",
        "Synthetic data channel connected.",
        "Monitoring simulated signals.",
        "Reactor energy synchronized.",
        "Visual matrix refreshed.",
        "Checking fictional security layer.",
        "Simulation telemetry updated.",
        "Processing holographic information.",
        "WARNING: Simulated signal anomaly.",
        "Display interference detected.",
        "Recovering visual channel.",
        "System simulation continuing."
    };

    int logCount = sizeof(logs) / sizeof(logs[0]);

    // 主动画循环
    while (1)
    {
        // 键盘操作
        if (_kbhit())
        {
            int key = _getch();

            if (key == 27)
                break;

            if (key == ' ')
                paused = !paused;

            if (key == 'r' || key == 'R')
                frame = 0;
        }

        if (!GetConsoleScreenBufferInfo(h, &info))
            break;

        W = info.srWindow.Right -
            info.srWindow.Left + 1;

        H = info.srWindow.Bottom -
            info.srWindow.Top + 1;

        if (W > MAX_W) W = MAX_W;
        if (H > MAX_H) H = MAX_H;

        if (W < 2 || H < 2)
            break;

        // 清除上一帧
        for (int i = 0; i < W * H; i++)
        {
            screen[i].Char.AsciiChar = ' ';
            screen[i].Attributes = 0;
        }

        // 每220帧循环一次警戒状态
        int cycle = frame % 220;

        // 模拟红色警戒
        int alert = (cycle >= 90 && cycle < 145);

        // 警报灯闪烁
        int flash = (frame / 5) % 2;

        // 短暂屏幕故障
        int glitch = (cycle >= 90 && cycle < 97) ||
                     (frame % 155 < 5);

        WORD mainColor = alert ? RED : GREEN;
        WORD brightColor = alert ? RED : LGREEN;

        // 绘制外边框
        box(0, 0, W, H, mainColor);

        if (W < 72 || H < 28)
        {
            text(2, 3,
                "Please enlarge your terminal.",
                YELLOW);

            text(2, 5,
                "Recommended: 90 x 32 or larger.",
                GREEN);

            text(2, 7,
                "Press ESC to exit.",
                WHITE);
        }
        else
        {
            char line[160];

            // =========================
            // 顶部标题与警报灯
            // =========================

            text(3, 1,
                "AURORA 3.0 // COMMAND CENTER",
                CYAN);

            if (alert)
            {
                put(W - 27, 1,
                    flash ? '*' : 'O', RED);

                if (flash)
                    text(W - 24, 1,
                        "[!! RED ALERT !!]", RED);
            }
            else
            {
                put(W - 27, 1,
                    flash ? '*' : 'o', LGREEN);

                text(W - 24, 1,
                    "[ SYSTEM ONLINE ]", LGREEN);
            }

            text(3, 2,
                "FUTURISTIC VISUAL SIMULATION",
                GREEN);

            for (int x = 1; x < W - 1; x++)
                put(x, 3, '=', mainColor);

            // =========================
            // 计算界面布局
            // =========================

            int topY = 5;
            int panelH = H - 15;

            int leftX = 2;
            int leftW = (W - 7) / 2;

            int rightX = leftX + leftW + 2;
            int rightW = W - rightX - 2;

            // =========================
            // 左侧核心数据矩阵
            // =========================

            box(leftX, topY,
                leftW, panelH, mainColor);

            text(leftX + 2, topY + 1,
                "[ CORE DATA MATRIX ]", CYAN);

            text(leftX + 2, topY + 2,
                "STREAM: ACTIVE", brightColor);

            for (int y = topY + 3;
                 y < topY + panelH - 4; y++)
            {
                for (int x = leftX + 2;
                     x < leftX + leftW - 2; x++)
                {
                    unsigned int v =
                        (unsigned int)(x * 17 + y * 31)
                        + (frame / 2) * (1 + x % 4);

                    char c = hex[v % 16];

                    WORD color = GREEN;

                    if (v % 17 == 0)
                        color = WHITE;
                    else if (v % 3 == 0)
                        color = LGREEN;

                    // 警戒状态下部分字符变红
                    if (alert && v % 5 == 0)
                        color = RED;

                    put(x, y, c, color);
                }
            }

            // 循环能量加载进度
            int progress = (frame % 180) * 100 / 179;

            snprintf(line, sizeof(line),
                "CORE CHARGING: %3d%%", progress);

            text(leftX + 2,
                topY + panelH - 3,
                line, brightColor);

            bar(leftX + 2,
                topY + panelH - 2,
                leftW - 4, progress, brightColor);

            // =========================
            // 右侧虚拟系统监控
            // =========================

            box(rightX, topY,
                rightW, panelH, mainColor);

            text(rightX + 2, topY + 1,
                "[ SYSTEM MONITOR ]", CYAN);

            int power = 65 + (frame / 4) % 35;
            int signal = 75 + (frame / 6) % 25;
            int nodes = 100 + (frame / 3) % 900;
            int shield = alert
                ? 30 + (frame % 20)
                : 85 + (frame % 15);

            snprintf(line, sizeof(line),
                "REACTOR POWER : %3d%%", power);
            text(rightX + 2, topY + 3,
                line, LGREEN);

            snprintf(line, sizeof(line),
                "SIGNAL LEVEL  : %3d%%", signal);
            text(rightX + 2, topY + 4,
                line, LGREEN);

            snprintf(line, sizeof(line),
                "VIRTUAL NODES: %4d", nodes);
            text(rightX + 2, topY + 5,
                line, WHITE);

            text(rightX + 2, topY + 6,
                "MODE: VISUAL SIMULATION",
                CYAN);

            if (alert)
            {
                if (flash)
                    text(rightX + 2, topY + 7,
                        "!!! CRITICAL WARNING !!!",
                        RED);
            }
            else
            {
                text(rightX + 2, topY + 7,
                    "SYSTEM STATUS: NOMINAL",
                    LGREEN);
            }

            snprintf(line, sizeof(line),
                "SHIELD INTEGRITY: %d%%", shield);

            text(rightX + 2, topY + 9,
                line, brightColor);

            bar(rightX + 2, topY + 10,
                rightW - 4, shield, brightColor);

            // 动态扫描信号
            int traceLen = rightW - 4;

            for (int i = 0; i < traceLen; i++)
            {
                char c = ((i + frame / 3) % 13 < 6)
                       ? '.' : '-';

                WORD color = GREEN;

                if (i == (frame / 2) % traceLen)
                {
                    c = '|';
                    color = WHITE;
                }

                put(rightX + 2 + i,
                    topY + 11, c, color);
            }

            // =========================
            // 底部系统日志
            // =========================

            int logY = H - 9;
            int logH = 6;

            box(2, logY, W - 4,
                logH, mainColor);

            text(4, logY + 1,
                "[ SYSTEM EVENT LOG // SIMULATION ]",
                CYAN);

            for (int i = 0; i < 3; i++)
            {
                int index = (frame / 16 + i)
                          % logCount;

                snprintf(line, sizeof(line),
                    "[T+%04u] %s",
                    frame / 4 + i,
                    logs[index]);

                text(4, logY + 2 + i,
                    line,
                    alert && i == 2 ? RED : GREEN);
            }

            // =========================
            // 屏幕故障特效
            // =========================

            if (glitch)
            {
                // 随机生成干扰字符
                for (int i = 0; i < W / 2; i++)
                {
                    int x = 3 + rand() % (W - 6);
                    int y = 5 + rand() % (H - 10);

                    char c = hex[rand() % 16];

                    put(x, y, c,
                        rand() % 2 ? RED : WHITE);
                }

                // 中央故障提示
                int warningX = (W - 27) / 2;
                int warningY = H / 2;

                text(warningX, warningY,
                    "!!! SIGNAL INTERFERENCE !!!",
                    RED);
            }

            // =========================
            // 底部操作栏
            // =========================

            for (int x = 1; x < W - 1; x++)
                put(x, H - 3, '=', mainColor);

            if (paused)
            {
                text(3, H - 2,
                    "PAUSED | SPACE: RESUME | ESC: EXIT",
                    YELLOW);
            }
            else
            {
                text(3, H - 2,
                    "SPACE: PAUSE | R: RESTART | ESC: EXIT",
                    brightColor);
            }

            text(W - 22, H - 2,
                "SIMULATION MODE ONLY",
                GREEN);
        }

        // =========================
        // 更新终端画面
        // =========================

        COORD size = {
            (SHORT)W, (SHORT)H
        };

        COORD origin = {0, 0};

        SMALL_RECT region = {
            info.srWindow.Left,
            info.srWindow.Top,
            (SHORT)(info.srWindow.Left + W - 1),
            (SHORT)(info.srWindow.Top + H - 1)
        };

        if (!WriteConsoleOutputA(
            h, screen, size, origin, &region))
            break;

        if (!paused)
            frame++;

        Sleep(50);
    }

    // 恢复终端设置
    SetConsoleTextAttribute(h, oldColor);
    SetConsoleCursorInfo(h, &oldCursor);

    system("cls");

    printf("AURORA 3.0 simulation ended.\n");

    return 0;
}
