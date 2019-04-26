// Uses tLine, tPoint, tPlane, tNamed

#include "../kpigeometry.hpp"

/*
    English:
        The task:
        
        Through point A (4, 0, -1) draw a line so that
        she crossed two lines:
        1)  (x-1)/2 = (y+3)/4 = (z-5)/3     (denote m)
        2)  x/5 = (y-2)/-1 =(z+1)/2         (denote n)

        Solution:

        Find two planes: the first passes through A and m,
        the second is through A and n. Then the intersection of these planes
        will be the desired line.
    
    Русский:
        Задание:
        
        Через точку A(4, 0, -1) провести прямую так, чтобы
        она пересекала две данные прямые:
        1)  (x-1)/2 = (y+3)/4 = (z-5)/3     (обозначим m)
        2)  x/5 = (y-2)/-1 =(z+1)/2         (обозначим n)

        Решение:

        Найдем две плоскости: первая проходит через A и m, 
        вторая - через A и n. Тогда пересечение этих плоскостей
        и будет искомая прямая.
*/

typedef struct Answer {
    // (x-Sx)/Dx = (y-Sy)/Dy = (z-Sz)/Dz
    double Sx, Sy, Sz; 
    double Dx, Dy, Dz;
} Answer;

const Answer a {4, 0, -1, -78, -222, -348}; 
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

int main()
{
    tPoint A(4, 0, -1);

    tPoint b1 {1, -3, 5};
    tPoint b2 {3, 1, 8};

    tPoint c1 {0, 2, -1};
    tPoint c2 {5, 1, 1};

    tPlane pl1 {A, b1, b2};
    tPlane pl2 {A, c1, c2};

    cout << pl1;
    cout << pl2;
    
    tLine result {pl1, pl2};    

    cout << result;
 
    assert( check_answer(a, result) );

    return 0;
}