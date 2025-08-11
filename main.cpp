#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>

using namespace std;

const int width = 20;  // 地图宽度
const int height = 20; // 地图高度

struct Point {
    int x, y;
};

vector<Point> snake; // 蛇的身体
Point food;          // 食物位置
int score = 0;       // 分数
char direction = 'R'; // 初始方向：右

void drawMap() {
    system("cls");
    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                cout << "#"; // 边界
            }
            else {
                bool isSnake = false;
                for (const auto& segment : snake) {
                    if (segment.x == j && segment.y == i) {
                        cout << "O"; // 蛇的身体
                        isSnake = true;
                        break;
                    }
                }
                if (food.x == j && food.y == i) {
                    cout << "*"; // 食物
                }
                else if (!isSnake) {
                    cout << " "; // 空白
                }
            }
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

void generateFood() {
    srand(time(0));
    while (true) {
        food.x = rand() % (width - 2) + 1;
        food.y = rand() % (height - 2) + 1;
        bool onSnake = false;
        for (const auto& segment : snake) {
            if (segment.x == food.x && segment.y == food.y) {
                onSnake = true;
                break;
            }
        }
        if (!onSnake) break;
    }
}

void moveSnake() {
    Point newHead = snake[0];
    if (direction == 'U') newHead.y--;
    else if (direction == 'D') newHead.y++;
    else if (direction == 'L') newHead.x--;
    else if (direction == 'R') newHead.x++;

    // 检查撞墙或撞自己
    if (newHead.x == 0 || newHead.x == width - 1 || newHead.y == 0 || newHead.y == height - 1) {
        cout << "Game Over! You hit the wall!" << endl;
        exit(0);
    }
    for (const auto& segment : snake) {
        if (newHead.x == segment.x && newHead.y == segment.y) {
            cout << "Game Over! You hit yourself!" << endl;
            exit(0);
        }
    }

    // 吃到食物
    if (newHead.x == food.x && newHead.y == food.y) {
        score += 10;
        snake.push_back(snake.back()); // 增加蛇的长度
        generateFood();
    }

    // 移动蛇
    for (int i = snake.size() - 1; i > 0; i--) {
        snake[i] = snake[i-1];
    }
    snake[0] = newHead;
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        if ((key == 'w' || key == 'W') && direction != 'D') direction = 'U';
        else if ((key == 's' || key == 'S') && direction != 'U') direction = 'D';
        else if ((key == 'a' || key == 'A') && direction != 'R') direction = 'L';
        else if ((key == 'd' || key == 'D') && direction != 'L') direction = 'R';
    }
}

int main() {
    // 初始化蛇
    snake.push_back({ width / 2, height / 2 });
    generateFood();

    while (true) {
        drawMap();
        input();
        moveSnake();
        Sleep(100); // 控制游戏速度
    }

    return 0;
}