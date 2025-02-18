//
// Created by intak on 18.02.2025.
//

#ifndef SNAKE_CLASS_H
#define SNAKE_CLASS_H
#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;
const int SNAKE = 3;
const int BORDER = 2;
const int FRUIT = 1;
const int EMPTY = 0;


class Snake
{
private:
    int size;
    const int startX = 4;
    const int startY = 4;
    vector <char> ruler;
    vector <pair <int, int>> coords;
public:
    void initSnake()
    {
        size = 3;
        ruler = vector<char> (size);
        coords = vector <pair<int, int>> (size);
        for(int i = 0;i < size; ++i)
        {
            ruler[i] = 'D';
            coords[i].second = startX - i;
            coords[i].first = startY;
        }
    }
    char getRule(int i)
    {
        return ruler[i];
    }
    void changeRuler(int i, char x)
    {
        ruler[i] = x;
    }
    void pushInRuler(char x)
    {
        ruler.push_back(x);
    }
    pair <int, int> getCoord(int i)
    {
        return coords[i];
    }
    void pushInCoords(pair <int, int> coord)
    {
        coords.emplace_back(coord);
    }
    int getSize()
    {
        return size;
    }
    void inqSize()
    {
        size++;
    }
    void inqCoordFir(int i)
    {
        coords[i].first++;
    }
    void deqCoordFir(int i)
    {
        coords[i].first--;
    }
    void inqCoordSec(int i)
    {
        coords[i].second++;
    }
    void deqCoordSec(int i)
    {
        coords[i].second--;
    }
    void eraseSnake()
    {
        ruler.erase(ruler.begin(), ruler.end());
        coords.erase(coords.begin(), coords.end());
    }
};

#endif //SNAKE_CLASS_H
