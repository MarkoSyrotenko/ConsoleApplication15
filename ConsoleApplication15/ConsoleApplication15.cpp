#include <iostream>
#include <string>
using namespace std;

class Point
{
    int x;
    int y;
public:
    Point()
    {
        x = y = 0;
    }
    Point(int x1, int y1)
    {
        x = x1;
        y = y1;
    }
    void Output()
    {
        cout << x << ", " << y << endl;
    }

    Point operator + (Point& obj)
    {
        Point res;
        res.x = this->x + obj.x;
        res.y = this->y + obj.y;
        return res;
    }
    Point operator - (Point& obj)
    {
        Point res;
        res.x = this->x - obj.x;
        res.y = this->y - obj.y;
        return res;
    }
    Point operator * (Point& obj)
    {
        Point res;
        res.x = this->x * obj.x;
        res.y = this->y * obj.y;
        return res;
    }

    Point operator += (Point& obj)
    {
        this->x += obj.x;
        this->y += obj.y;
        return *this;
    }
    Point operator -= (Point& obj)
    {
        this->x -= obj.x;
        this->y -= obj.y;
        return *this;
    }
    Point operator *= (Point& obj)
    {
        this->x *= obj.x;
        this->y *= obj.y;
        return *this;
    }

    Point operator + (int a)
    {
        Point res;
        res.x = this->x + a;
        res.y = this->y + a;
        return res;
    }
    Point operator - (int a)
    {
        Point res;
        res.x = this->x - a;
        res.y = this->y - a;
        return res;
    }
    Point operator * (int a)
    {
        Point res;
        res.x = this->x * a;
        res.y = this->y * a;
        return res;
    }
    friend ostream& operator << (ostream& os, Point& obj)
    {
        os << obj.x << ", " << obj.y;
        return os;
    }
    friend istream& operator >> (istream& is, Point& obj)
    {
        cout << "x: ";
        is >> obj.x;
        cout << "y: ";
        is >> obj.y;
        return is;
    }
};

template <class T = int>
class matrix
{
    T** p;
    int row, col;
public:
    matrix()
    {
        row = 3;
        col = 3;
        p = new T * [row];
        for (int i = 0; i < row; i++)
        {
            p[i] = new T[col];
        }
    }
    matrix(int a, int b)
    {
        row = a;
        col = b;
        p = new T * [row];
        for (int i = 0; i < row; i++)
        {
            p[i] = new T[col];
        }
    }
    matrix(const matrix& obj)
    {
        row = obj.row;
        col = obj.col;
        p = new T * [row];
        for (int i = 0; i < row; i++)
        {
            p[i] = new T[col];
            for (int j = 0; j < col; j++)
            {
                p[i][j] = obj.p[i][j];
            }
        }
    }
    matrix(matrix&& obj)
    {
        row = obj.row;
        col = obj.col;
        p = obj.p;
        obj.p = nullptr;
    }
    ~matrix()
    {
        if (p != nullptr)
        {
            for (int i = 0; i < row; i++)
            {
                delete[] p[i];
            }
            delete[] p;
        }
    }

    matrix& operator = (const matrix& obj)
    {
        if (p != nullptr)
        {
            for (int i = 0; i < row; i++)
            {
                delete[] p[i];
            }
            delete[] p;
        }
        row = obj.row;
        col = obj.col;
        p = new T * [row];
        for (int i = 0; i < row; i++)
        {
            p[i] = new T[col];
            for (int j = 0; j < col; j++)
            {
                p[i][j] = obj.p[i][j];
            }
        }
        return this;
    }
    matrix& operator = (matrix&& obj)
    {
        row = obj.row;
        col = obj.col;
        p = obj.p;
        obj.p = nullptr;
        return this;
    }

    matrix& operator ++()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                p[i][j]++;
            }
        }
        return this;
    }
    matrix operator ++(int)
    {
        matrix temp(*this);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                p[i][j]++;
            }
        }
        return temp;
    }

    matrix& operator --()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                p[i][j]--;
            }
        }
        return this;
    }
    matrix operator --(int)
    {
        matrix temp(*this);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                p[i][j]--;
            }
        }
        return temp;
    }

    matrix operator + (const matrix& obj)
    {
        matrix temp(*this);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                temp.p[i][j] += obj.p[i][j];
            }
        }
        return temp;
    }
    matrix operator * (const matrix& obj)
    {
        matrix<T> temp(row, obj.col);
        if (col == obj.row)
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < obj.col; j++)
                {
                    T n = 0;
                    for (int k = 0; k < col; k++)
                    {
                        n += p[i][k] * obj.p[k][j];
                    }
                    temp.p[i][j] = n;
                }
            }
        return temp;
    }

    T& operator () (int a, int b)
    {
        return p[a][b];
    }

    friend ostream& operator << (ostream& os, matrix& obj)
    {
        for (int i = 0; i < obj.row; i++)
        {
            for (int j = 0; j < obj.col; j++)
            {
                os << obj.p[i][j] << "\t";
            }
            os << "\n";
        }
        os << "\n";
        return os;
    }
    friend istream& operator >> (istream& is, matrix& obj)
    {
        for (int i = 0; i < obj.row; i++)
        {
            for (int j = 0; j < obj.col; j++)
            {
                is >> obj.p[i][j];
            }
        }
        return is;
    }

    void init()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                p[i][j] = rand() % 5;
            }
        }
    }

    T getMin()
    {
        T n = p[0][0];
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (p[i][j] < n)
                    n = p[i][j];
            }
        }
        return n;
    }
    T getMax()
    {
        T n = p[0][0];
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (p[i][j] > n)
                    n = p[i][j];
            }
        }
        return n;
    }
};

int main()
{
    srand(time(0));
    matrix<int> obj1(3, 4);
    matrix<int> obj2(4, 3);
    obj1.init();
    obj2.init();
    matrix<int> obj3 = obj1 * obj2;
    cout << obj1;
    cout << obj2;
    cout << obj3;
    matrix<int> obj4(3, 3);
    obj4.init();
    cout << obj4;
    matrix<int> obj5 = obj3 + obj4;
    cout << obj5;

    cout << "Min: " << obj5.getMin() << endl;
    cout << "Max: " << obj5.getMax() << endl << endl;;

    matrix<Point> obj6(2, 2);
    cin >> obj6;
    cout << obj6;
    matrix<Point> obj7(2, 2);
    cin >> obj7;
    cout << obj7;
    matrix<Point> obj8 = obj6 + obj7;
    cout << obj8;
}
