#ifndef MENUNAVIGATOR_H
#define MENUNAVIGATOR_H

struct MenuNavigator
{
    int numRows;
    int rowDistance;
    int atRow;

    MenuNavigator(int numRows = 1, int rowDistance = 60, int atRow = 0)
        : numRows(numRows),
          rowDistance(rowDistance),
          atRow(atRow)
    {
    }
};

#endif