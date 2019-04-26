// Uses tLine, tPoint, tPlane, tNamed

#include "../kpigeometry.hpp"

/*
    English:
        The task:
        
        Find equation of a line, that goes through point P (1, 0, 7) 
        parallel to the plane A: 3x-y + 2z-15 = 0, so that it 
        intersects the line m: (x-1) / 4 = (y-3) / 2 = z / 1

        Solution:

        Find the equation of the plane passing through P and parallel to A,
        denote it by B. Next we find the intersection of B and m -point L.
        Through two points P and L we draw a line - our answer. 
    Русский:
        Задание:
        
        Через точку P(1, 0, 7) паралельно плоскости A: 3x-y+2z-15=0 провести
        прямую так, чтобы она пересекала прямую m: (x-1)/4 = (y-3)/2 = z/1

        Решение:

        Найдем уравнение плоскости проходящей через P и паралельной A,
        обозначим её B. Далее найдем пересечение B и m -точку L.
        Через две точки P и L проведем прямую - решение.

*/

typedef struct Answer {
    // (x-Sx)/Dx = (y-Sy)/Dy = (z-Sz)/Dz
    double Sx, Sy, Sz; 
    double Dx, Dy, Dz;
} Answer;

const Answer SOLUTION {1, 0, 6, 5, 5.5, -4.75}; 
// our answer (was solved by human)
// наш ответ (решено вручную)

bool check_answer(const Answer& ans, const tLine& tl)
{
    return (
        (ans.Sx == tl.Sx()) &&
        (ans.Sy == tl.Sy()) &&
        (ans.Sz == tl.Sz()) &&
        (ans.Dx == tl.Dx()) &&
        (ans.Dy == tl.Dy()) &&
        (ans.Dz == tl.Dz()) 
    );
}

tPlane get_parallel(const tPoint& poi, const tPlane& pl)
//  Get plane, parallel to this plane and going through point 
//  Получить плоскость паралельную даной и проходящую через точку
{
    const double newD = - (pl.A() * poi.x() + pl.B() * poi.y() + pl.C() * poi.z() + pl.D()) + pl.D();

    return tPlane(pl.A(), pl.B(), pl.C(), newD);
}

tLine solve_problem(const tPoint& P, const tPlane& A, const tLine& m)
{
    tPlane B = get_parallel(P, A);
    tPoint L = LineCutPlane(m, B);

    tLine answer (P, L);

    return answer;
}

tLine enter_line()
{
    cout << "Enter line by equation in this order:\n";
    cout << "(x-a1)/a4 = (y-a2)/a5 = (z-a3)/a6\n";
    double a1, a2, a3, a4, a5, a6;

    cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6;

    return tLine(a1, a2, a3, a4, a5, a6);
}

int main()
{
    tPoint P(1, 0, 6);
    tPlane A(3, -1, 2, -15);
    tLine m(1, 3, 0, 4, 2, 1);

    assert(check_answer(SOLUTION, solve_problem(P, A, m)));

    int x = 1;
    while(true)
    {
        cout << "Press 1 to continue, press 0 to stop:\n";
        cin >> x;
        if (!x) break;

        cin >> P;
        cin >> A;
        m = enter_line();

        cout << solve_problem(P, A, m);
    }

    return 0;
}