#include "class.h"

class Map {
private:
    const int size = 10;
    vector <vector <int> > map;
    Snake snake;
public:

    void createMap()
    {
        map = vector <vector <int> > (size, vector <int> (size));
        for(int i = 0;i < size; ++i)
        {
            for(int j = 0;j < size; ++j)
            {
                if(i == 0 || j == 0 || i == size-1 || j == size - 1)
                    map[i][j] = BORDER;
                else
                    map[i][j] = EMPTY;
            }
        }
    }
    void showMap()
    {
        system("cls");
        for(int i = 0;i < size; ++i)
        {
            for(int j = 0;j < size; ++j)
            {
                if(map[i][j] == BORDER)
                {
                    setColor(0, 3);
                    cout << "# ";
                    setColor(0, 15);
                }
                if(map[i][j] == EMPTY)
                {
                    cout << "  ";
                }
                if(map[i][j] == SNAKE)
                {
                    setColor(0, 1);
                    cout << "o ";
                    setColor(0, 15);
                }

                if(map[i][j] == FRUIT)
                {
                    setColor(0, 2);
                    cout << "0 ";
                    setColor(0, 15);
                }
            }
            std::cout << '\n';
        }
    }
    void createFruit()
    {
        int x, y;
        do {
            x = rand() % (size-2) + 1;
            y = rand() % (size-2) + 1;
        } while(map[x][y] == SNAKE || map[x][y] == FRUIT);
        map[x][y] = FRUIT;
    }

    void changeMap()
    {
        bool newTail = false;
        pair <int, int> lostPair = snake.getCoord(snake.getSize()-1);
        int lostX = lostPair.second, lostY = lostPair.first;
        char lostRule = snake.getRule(snake.getSize()-1);
        for(int i = snake.getSize()-1; i>=0;--i)
        {
            char rule = snake.getRule(i);
            if(rule == 'W')
                snake.deqCoordFir(i);
            else if(rule == 'S')
                snake.inqCoordFir(i);
            else if(rule == 'D')
                snake.inqCoordSec(i);
            else if(rule == 'A')
                snake.deqCoordSec(i);

            pair <int, int> coord = snake.getCoord(i);
            int first = coord.first, second = coord.second;

            if(i > 0){snake.changeRuler(i, snake.getRule(i-1));}
            if(i == 0 && (map[first][second] == SNAKE ||map[first][second] == BORDER))
            {
                cout << "game over";
                snake.eraseSnake();
                eraseMap();
                Sleep(2000);
                exit(1);
            }
            if(i == 0 && map[first][second] == FRUIT)
            {
                snake.pushInRuler(lostRule);
                snake.pushInCoords(lostPair);
                snake.inqSize();
                createFruit();
                newTail = true;
            }
            map[first][second] = SNAKE;
        }
        if(!newTail) map[lostY][lostX] = EMPTY;
    }
    void eraseMap()
    {
        for(int i = 0;i < size; ++i)
            map[i].erase(map[i].begin(), map[i].end());
        map.erase(map.begin(), map.end());
    }
    void play()
    {
        snake.initSnake();
        for(int i = 0;i < snake.getSize(); ++i)
        {
            pair <int, int> coord = snake.getCoord(i);
            map[coord.first][coord.second] = SNAKE;
        }
        showMap();
        while (true) {
            auto start_time = high_resolution_clock::now();
            int ch = 0;
            bool key_pressed = false;

            while (duration_cast<milliseconds>(high_resolution_clock::now() - start_time).count() < 600) {
                if (_kbhit()) {
                    ch = _getch();
                    key_pressed = true;
                    break;
                }
            }
            if (!key_pressed) {
                changeMap();
                showMap();
                continue;
            }
            char lastDirection = 'D';
            if (ch == 224 || ch == 0) {
                int arrow_code = _getch();
                char rule = snake.getRule(0);
                switch (arrow_code) {
                    case 72:
                        // Код стрелки вверх
                        if (rule == 'S') { continue; }
                        lastDirection = 'W';
                        break;
                    case 80:
                        // Код стрелки вниз
                        if (rule == 'W') { continue; }
                        lastDirection = 'S';
                        break;
                    case 77:
                        // Код стрелки вправо
                        if (rule == 'A') { continue; }
                        lastDirection = 'D';
                        break;
                    case 75:
                        // Код стрелки влево
                        if (rule == 'D') { continue; }
                        lastDirection = 'A';
                        break;
                    default:
                        continue;
                }
                snake.changeRuler(0, lastDirection);
                Sleep(400);
                changeMap();
                showMap();
            }
        }
    }
    static void setColor(int background, int text)
    {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
    }
};

int main() {
    unsigned seed = time(nullptr);
    srand(seed);
 Map myMap;
 myMap.createMap();
 myMap.createFruit();
 myMap.showMap();
 myMap.play();
}
