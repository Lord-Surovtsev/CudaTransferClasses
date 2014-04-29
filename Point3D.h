#ifndef POINT3D_H
#define POINT3D_H

class Point3D
{
public:
    float _x;
    float _y;
    float _z;

public:
    Point3D()
    {
        _x = 0;
        _y = 0;
        _z = 0;
    }

    Point3D(float x, float y, float z)
    {
        _x = x;
        _y = y;
        _z = z;
    }

    virtual ~Point3D()
    {

    }
};

#endif // POINT3D_H
