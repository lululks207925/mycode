
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define WIDTH 42
#define HEIGHT 22
#define SCREEN_H (HEIGHT + 3)
#define MAX_SNAKE ((WIDTH - 2) * (HEIGHT - 2))

#define GREEN (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define DARK_GREEN FOREGROUND_GREEN
#define RED (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define CYAN (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)

// 游戏画面
static CHAR_INFO screen[WIDTH * SCREEN_H];

// 蛇的身体坐标
int snakeX[MAX_SNAKE];
int snakeY[MAX_SNAKE];

int length;
int dx, dy;
int foodX, foodY;
int score;
int gameOver;
int win;
int paused;

// 绘制一个字符
void put(int x, int y, char c, WORD color)
{
    if (x < 0 || x >= WIDTH ||
        y < 0 || y >= SCREEN_H)
        return;

    int index = y * WIDTH + x;

    screen[index].Char.AsciiChar = c;
    screen[index].Attributes = color;
}

// 绘制文字
void drawText(int x, int y, const char *s, WORD color)
{
    for (int i = 0; s[i] != '\0'; i++)
        put(x + i, y, s[i], color);
}

// 判断某个位置是否有蛇
int isSnake(int x, int y)
{
    for (int i = 0; i < length; i++)
    {
        if (snakeX[i] == x && snakeY[i] == y)
            return 1;
    }

    return 0;
}

// 随机生成食物
void createFood(void)
{
    do
    {
        foodX = 1 + rand() % (WIDTH - 2);
        foodY = 1 + rand() % (HEIGHT - 2);
    }
    while (isSnake(foodX, foodY));
}

// 开始新游戏
void newGame(void)
{
    length = 3;

    for (int i = 0; i < length; i++)
    {
        snakeX[i] = WIDTH / 2 - i;
        snakeY[i] = HEIGHT / 2;
    }

    // 初始向右移动
    dx = 1;
    dy = 0;

    score = 0;
    gameOver = 0;
    win = 0;
    paused = 0;

    createFood();
}

// 更新蛇的位置
void moveSnake(void)
{
    int newX = snakeX[0] + dx;
    int newY = snakeY[0] + dy;

    // 判断是否撞墙
    if (newX <= 0 || newX >= WIDTH - 1 ||
        newY <= 0 || newY >= HEIGHT - 1)
    {
        gameOver = 1;
        return;
    }

    // 判断是否吃到食物
    int eating = (newX == foodX && newY == foodY);

    // 不吃食物时，允许走到即将离开的尾巴位置
    int limit = length - (eating ? 0 : 1);

    // 判断是否撞到自己
    for (int i = 0; i < limit; i++)
    {
        if (snakeX[i] == newX && snakeY[i] == newY)
        {
            gameOver = 1;
            return;
        }
    }

    // 吃到食物，身体增长
    if (eating)
        length++;

    // 身体跟随头部移动
    for (int i = length - 1; i > 0; i--)
    {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // 更新蛇头
    snakeX[0] = newX;
    snakeY[0] = newY;

    if (eating)
    {
        score += 10;

        if (length >= MAX_SNAKE)
        {
            win = 1;
            gameOver = 1;
        }
        else
        {
            createFood();
        }
    }
}

// 绘制整个游戏画面
// 返回1表示终端大小足够
int drawGame(HANDLE h)
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    if (!GetConsoleScreenBufferInfo(h, &info))
        return 0;

    int visibleW = info.srWindow.Right -
                   info.srWindow.Left + 1;

    int visibleH = info.srWindow.Bottom -
                   info.srWindow.Top + 1;

    if (visibleW <= 0 || visibleH <= 0)
        return 0;

    // 清空画面
    for (int i = 0; i < WIDTH * SCREEN_H; i++)
    {
        screen[i].Char.AsciiChar = ' ';
        screen[i].Attributes = 0;
    }

    int ready = visibleW >= WIDTH &&
                visibleH >= SCREEN_H;

    if (!ready)
    {
        drawText(0, 0,
            "Please maximize the VS Code terminal.",
            WHITE);

        drawText(0, 1,
            "Need at least 42 columns x 25 rows.",
            GREEN);

        drawText(0, 2,
            "Press Q or ESC to exit.",
            CYAN);
    }
    else
    {
        // 绘制上下墙壁
        for (int x = 0; x < WIDTH; x++)
        {
            put(x, 0, '#', CYAN);
            put(x, HEIGHT - 1, '#', CYAN);
        }

        // 绘制左右墙壁
        for (int y = 0; y < HEIGHT; y++)
        {
            put(0, y, '#', CYAN);
            put(WIDTH - 1, y, '#', CYAN);
        }

        // 绘制食物
        if (!win)
            put(foodX, foodY, '*', RED);

        // 绘制蛇的身体
        for (int i = length - 1; i >= 0; i--)
        {
            if (i == 0)
                put(snakeX[i], snakeY[i], '@', GREEN);
            else
                put(snakeX[i], snakeY[i], 'o',
                    DARK_GREEN);
        }

        // 计算速度
        int delay = 155 - (score / 10) * 4;
        if (delay < 65)
            delay = 65;

        char status[80];

        snprintf(status, sizeof(status),
            "SCORE: %d  LENGTH: %d  SPEED: %dms",
            score, length, delay);

        drawText(0, HEIGHT, status, WHITE);

        drawText(0, HEIGHT + 1,
            "WASD/Arrows: Move | P: Pause | Q: Quit",
            CYAN);

        if (win)
        {
            drawText(0, HEIGHT + 2,
                "YOU WIN! Press R to play again.",
                GREEN);
        }
        else if (gameOver)
        {
            drawText(0, HEIGHT + 2,
                "GAME OVER! Press R to restart.",
                RED);
        }
        else if (paused)
        {
            drawText(0, HEIGHT + 2,
                "PAUSED. Press P to continue.",
                WHITE);
        }
        else
        {
            drawText(0, HEIGHT + 2,
                "R: Restart | Eat * | Avoid walls",
                GREEN);
        }
    }

    // 将画面一次性输出到终端
    COORD bufferSize = {
        (SHORT)WIDTH,
        (SHORT)SCREEN_H
    };

    COORD origin = {0, 0};

    int outW = visibleW < WIDTH ? visibleW : WIDTH;
    int outH = visibleH < SCREEN_H ? visibleH : SCREEN_H;

    SMALL_RECT region = {
        info.srWindow.Left,
        info.srWindow.Top,
        (SHORT)(info.srWindow.Left + outW - 1),
        (SHORT)(info.srWindow.Top + outH - 1)
    };

    if (!WriteConsoleOutputA(
        h, screen, bufferSize, origin, &region))
        return 0;

    return ready;
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

    // 隐藏光标
    CONSOLE_CURSOR_INFO cursor = oldCursor;
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(h, &cursor);

    srand((unsigned int)time(NULL));

    newGame();
    system("cls");

    int quit = 0;

    // 游戏主循环
    while (!quit)
    {
        int changed = 0;

        // 检测键盘输入
        while (_kbhit())
        {
            int key = _getch();

            // 将方向键转成WASD
            if (key == 0 || key == 224)
            {
                int arrow = _getch();

                if (arrow == 72) key = 'w';
                else if (arrow == 80) key = 's';
                else if (arrow == 75) key = 'a';
                else if (arrow == 77) key = 'd';
                else key = 0;
            }

            if (key == 27 || key == 'q' || key == 'Q')
            {
                quit = 1;
                break;
            }

            // 暂停游戏
            if (key == 'p' || key == 'P')
            {
                if (!gameOver)
                    paused = !paused;
            }

            // 重新开始
            if (key == 'r' || key == 'R')
            {
                newGame();
                changed = 0;
            }

            if (!gameOver && !paused && !changed)
            {
                int newDX = dx;
                int newDY = dy;

                if (key == 'w' || key == 'W')
                {
                    newDX = 0;
                    newDY = -1;
                }
                else if (key == 's' || key == 'S')
                {
                    newDX = 0;
                    newDY = 1;
                }
                else if (key == 'a' || key == 'A')
                {
                    newDX = -1;
                    newDY = 0;
                }
                else if (key == 'd' || key == 'D')
                {
                    newDX = 1;
                    newDY = 0;
                }
                else
                {
                    continue;
                }

                // 禁止直接反向移动
                if (newDX != -dx || newDY != -dy)
                {
                    dx = newDX;
                    dy = newDY;
                    changed = 1;
                }
            }
        }

        if (quit)
            break;

        int ready = drawGame(h);

        // 游戏正常运行时移动蛇
        if (ready && !paused && !gameOver)
            moveSnake();

        // 分数越高，速度越快
        int delay = 155 - (score / 10) * 4;

        if (delay < 65)
            delay = 65;

        if (paused || gameOver || !ready)
            delay = 80;

        Sleep(delay);
    }

    // 恢复控制台设置
    SetConsoleTextAttribute(h, oldColor);
    SetConsoleCursorInfo(h, &oldCursor);

    system("cls");
    printf("Thanks for playing Snake!\n");
    printf("Final score: %d\n", score);

    return 0;
}
