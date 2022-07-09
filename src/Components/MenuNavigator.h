#ifndef MENUNAVIGATOR_H
#define MENUNAVIGATOR_H

struct MenuNavigator
{
    int numRows;
    int rowDistance;
    int atRow;

    MenuNavigator(int numRows, int rowDistance = 100, int atRow = 0)
        : numRows(numRows),
          rowDistance(rowDistance),
          atRow(atRow)
    {
    }
};

#endif