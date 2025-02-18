//
// Created by intak on 18.02.2025.
//

#include "functions.h"
void setColor(int background, int text)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}