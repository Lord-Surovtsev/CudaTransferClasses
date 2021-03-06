#ifndef POINT3D_H
#define POINT3D_H

template <class A>
class Point3D
{
public:
    A _x;
    A _y;
    A _z;

public:
    Point3D(A x = 0, A y = 0, A z = 0)
    {
        _x = x;
        _y = y;
        _z = z;
    }

    Point3D(const Point3D& p)
    {
        this->_x = p._x;
        this->_y = p._y;
        this->_z = p._z;
    }

    ~Point3D()
    {

    }

    Point3D& operator=(const Point3D& other)
    {
        if (this != &other)
        {
            _x = other._x;
            _y = other._y;
            _z = other._z;
        }
        return *this;
    }

    void Print(const char* desription)
    {
        cout << desription << " " << this->_x << " " << this->_y << " " << this->_z << endl;
    }

    void Normalization()
    {
        A sum = this->_x + this->_y + this->_z;
        this->_x /= sum;
        this->_y /= sum;
        this->_z /= sum;
    }

    Point3D& operator +=(const Point3D& other)
    {
        this->_x += other._x;
        this->_y += other._y;
        this->_z += other._z;

        return *this;
    }

    Point3D& operator -=(const Point3D& other)
    {
        this->_x -= other._x;
        this->_y -= other._y;
        this->_z -= other._z;

        return *this;
    }

    Point3D& operator *=(const float coeff)
    {
        this->_x *= coeff;
        this->_y *= coeff;
        this->_z *= coeff;

        return *this;
    }

    Point3D& operator /=(const float coeff)

    {
        this->_x /= coeff;
        this->_y /= coeff;
        this->_z /= coeff;

        return *this;
    }

    Point3D operator /(const float coeff)
    {
        Point3D res(*this);
        res._x /= coeff;
        res._y /= coeff;
        res._z /= coeff;
        return res;
    }

    Point3D operator *(const float coeff)
    {
        Point3D res(*this);
        res._x *= coeff;
        res._y *= coeff;
        res._z *= coeff;
        return res;
    }

    Point3D operator +(const Point3D& other)
    {
        Point3D res;
        res._x = this->_x + other._x;
        res._y = this->_y + other._y;
        res._z = this->_z + other._z;
        return res;
    }

    Point3D operator -(const Point3D& other)
    {
        Point3D res;
        res._x = this->_x - other._x;
        res._y = this->_y - other._y;
        res._z = this->_z - other._z;
        return res;
    }

    static Point3D CrossProduct(const Point3D& a, const Point3D& b)
    {
        return Point3D(
                      a._y * b._z - b._y * a._z
                    , a._z * b._x - a._x * b._z
                    , a._x * b._y - b._x * a._y);
    }

    A DotProduct(const Point3D& other)
    {
        A res =   this->_x * other._x
                + this->_y * other._y
                + this->_z * other._z;
        return res;
    }

    static A Determinant(const Point3D& col1, const Point3D& col2, const Point3D& col3)
    {
        A res;
        res =     col1._x * (col2._y * col3._z - col3._y * col2._z)
                - col2._x * (col1._y * col3._z - col3._y * col1._z)
                + col3._x * (col1._y * col2._z - col2._y * col1._z);
        return res;
    }

    Point3D BarycentricCoordinates(Point3D a, Point3D b, Point3D c)
    {
        Point3D addiotion(0, 0, 0);
        while(1)
        {
            Point3D aN(a._x + addiotion._x, a._y + addiotion._y, a._z + addiotion._z);
            Point3D bN(b._x + addiotion._x, b._y + addiotion._y, b._z + addiotion._z);
            Point3D cN(c._x + addiotion._x, c._y + addiotion._y, c._z + addiotion._z);
            Point3D tN(this->_x + addiotion._x, this->_y + addiotion._y, this->_z + addiotion._z);
            Point3D res;

//            aN.Print("aN");
//            bN.Print("bN");
//            cN.Print("cN");
//            tN.Print("tN");
            float d = this->Determinant(aN, bN, cN);
            if (0 == d)
            {
                addiotion.PlusX(1);
                addiotion.PlusY(1);
                addiotion.PlusZ(1);
                continue;
            }
            float d1 = this->Determinant(tN, bN, cN);
            float d2 = this->Determinant(aN, tN, cN);
            float d3 = this->Determinant(aN, bN, tN);

            res._x = -1 * d1 / d;
            res._y = -1 * d2 / d;
            res._z = -1 * d3 / d;
            A sum = res._x + res._y + res._z;
            res._x /= sum;
            res._y /= sum;
            res._z /= sum;
            return res;
        }
    }

    A getX()
    {
        return _x;
    }

    A getY()
    {
        return _y;
    }

    A getZ()
    {
        return _z;
    }

    void setX(A x)
    {
        _x = x;
    }

    void setY(A y)
    {
        _y = y;
    }

    void setZ(A z)
    {
        _z = z;
    }

    void set(A x, A y, A z)
    {
        _x = x;
        _y = y;
        _z = z;
    }

    void PlusX(const A& x)
    {
        _x += x;
    }

    void PlusY(const A& y)
    {
        _y += y;
    }

    void PlusZ(const A& z)
    {
        _z += z;
    }

    void PlusCorresp(const Point3D& other, float coeff)
    {
        this->_x += other._x * coeff;
        this->_y += other._y * coeff;
        this->_z += other._z * coeff;
    }

    void MinusCorresp(const Point3D& other, float coeff)
    {
        this->_x -= other._x * coeff;
        this->_y -= other._y * coeff;
        this->_z -= other._z * coeff;
    }

    A getSquaredLength()
    {
        return _x * _x + _y * _y + _z * _z;
    }

    A getLength()
    {
        return sqrt(_x * _x + _y * _y + _z * _z);
    }

    Point3D getUnit()
    {
        Point3D res(*this);
        A len = sqrt(_x * _x + _y * _y + _z * _z);
        res._x /= len;
        res._y /= len;
        res._z /= len;

        return res;
    }
};

#endif // POINT3D_H
