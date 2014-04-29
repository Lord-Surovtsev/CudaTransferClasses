#include <iostream>
using namespace std;

#include "Point3D.h"


void CallKernel(Point3D* h_points, const int count);

void PrintPoints(Point3D* points, const int count)
{
    for (int i = 0; i < count; i++)
    {
        Point3D& p = points[i];
        cout << "i " << i
             << ": " << p._x
             << " " << p._y
             << " " << p._z
             << endl;
    }
}

int main(int argc, char* argv[])
{
    cout << "starting" << endl;
    int count = 100;

    Point3D* points = new Point3D[count];

    for (int i = 0; i < count; i++)
    {
        Point3D& p = points[i];
        p._x = i;
        p._y = 10;
        p._z = count - i;
    }

    cout << "before kernel calling" << endl;
    PrintPoints(points, count);

    CallKernel(points, count);

    cout << "after that" << endl;
    PrintPoints(points, count);

    delete[] points;
    return 0;
}

