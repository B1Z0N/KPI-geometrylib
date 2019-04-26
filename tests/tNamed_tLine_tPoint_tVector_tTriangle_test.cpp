#include "../kpigeometry.hpp"

/*
    English:
        The task:
        
        Given the vertices of the triangle A (4, 1, -2), B (2, 0, 0),
        C (-2, 3, -5) find its area.

        Solution:

        We solve this in three ways and compare the answers:
        1. By hand, on a piece of paper
        2. Find the height, with it and the third side find the area
        3. We use the theorem ... embedded in the square function of the class tTriangle
    
    Русский:
        Задание:
        
        Дано вершины треугольника A(4, 1, -2), B(2, 0, 0), 
        C(-2, 3, -5). Найти его площадь.

        Решение:

        Решим тремя способами и сравним ответы:
        1. Самостоятельно, на листочке
        2. Найдем высоту и через нее и третью сторону найдем площадь
        3. Используем теорему ... встроеную в функцию площади класса tTriangle

*/

const double square_by_human = 10.3078; 
// our answer (was solved by human)
// наш ответ (решено вручную)

double square_by_tTriangle(const tTriangle& tr)
{
    return tr.Square();
}

double square_by_height(const tPoint& A, const tPoint& B, const tPoint& C)
{
    tLine tl (A, B);
    double height = tl.DistToPoint(C);
    double side = A.DistTo(B);

    return side * height / 2; 
}

double inline myabs(double arg)
{
    return arg >= 0 ? arg : -arg;
}

bool approx_equal(double a, double b)
{
    return myabs(a - b) < 1e-3;
}

bool check_for_equality(const tPoint& A, const tPoint& B, const tPoint& C)
{
    const double a = square_by_height(A, B, C);
    const double b = square_by_tTriangle(tTriangle(A, B, C));
    const double c = square_by_human;

    cout << a << '\n' << b << '\n' << c << '\n';

    return (approx_equal(a, b) &&
            approx_equal(a, c) &&
            approx_equal(c, b));
}

int main()
{
    tPoint A (4, 1, -2), B(2, 0, 0), C(-2, 3, -5);
 
    assert(check_for_equality(A, B, C));

    return 0;
}