#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

const int SNAKE = 3;
const int BORDER = 2;
const int FRUIT = 1;
const int EMPTY = 0;


class Map {
private:
    int size = 10;
    int snakeSize = 3;
    int snakeX = 4;
    int snakeY = 4;
    vector <vector <int> > map;
    vector <char> ruler;
    vector <pair <int, int> > coords;
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
        int lostX = coords[snakeSize-1].second, lostY = coords[snakeSize-1].first;
        char lostRule = ruler[snakeSize-1];
        for(int i = snakeSize-1; i>=0;--i)
        {
            if(ruler[i] == 'W')
                coords[i].first--;
            else if(ruler[i] == 'S')
                coords[i].first++;
            else if(ruler[i] == 'D')
                coords[i].second++;
            else if(ruler[i] == 'A')
                coords[i].second--;
            if(i > 0){ruler[i] = ruler[i - 1];}
            if(i == 0 && (map[coords[i].first][coords[i].second] == SNAKE ||map[coords[i].first][coords[i].second] == BORDER))
            {
                cout << "game over";
                Sleep(2000);
                exit(1);
            }
            if(i == 0 && map[coords[i].first][coords[i].second] == FRUIT)
            {
                ruler.push_back(lostRule);
                coords.emplace_back(lostY, lostX);
                snakeSize++;
                createFruit();
                newTail = true;
            }
            map[coords[i].first][coords[i].second] = SNAKE;
        }
        if(!newTail) map[lostY][lostX] = EMPTY;
    }
    void play()
    {
        ruler = vector <char> (snakeSize);
        coords = vector <pair <int, int> > (snakeSize);
        for(int i = 0;i < snakeSize; ++i)
        {
            ruler[i] = 'D';
            coords[i].second = snakeX - i;
            coords[i].first = snakeY;
            map[coords[i].first][coords[i].second] = SNAKE;
        }
        showMap();
        while(true)
        {
            int ch = _getch();
            long int time1 = time(nullptr);
            Sleep(1);
            if(ch == 224 || ch == 0)
            {
                switch(getch())
                {
                    case 72:
                        // Код стрелки вверх
                        if(ruler[0] == 'S'){continue;}
                        ruler[0] = 'W';
                        break;
                    case 80:
                        // Код стрелки вниз
                        if(ruler[0] == 'W'){continue;}
                        ruler[0] = 'S';
                        break;
                    case 77:
                        // Код стрелки вправо
                        if(ruler[0] == 'A'){continue;}
                        ruler[0] = 'D';
                        break;
                    case 75:
                        // Код стрелки влево
                        if(ruler[0] == 'D'){continue;}
                        ruler[0] = 'A';
                        break;
                    default:
                        continue;
                }
            }

            Sleep(100);
            changeMap();
            showMap();
        }

    }
    static void setColor(int background, int text)
    {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
    }
};

int main() {
 Map myMap;
 myMap.createMap();
 myMap.createFruit();
 myMap.showMap();
 myMap.play();
}
