#include "geometry.hpp"

int main()
{
    tPoint A(4, 0, -1);

    tPoint b1 {1, -3, 5};
    tPoint b2 {3, 1, 8};

    tPoint c1 {0, 2, -1};
    tPoint c2 {5, 1, 1};

    // tLine m(1, -3, 5, 2, 4, 3);
    // tLine n(0, 2, -1, 5, -1, 2);

    tPlane pl1 {A, b1, b2};
    tPlane pl2 {A, c1, c2};

    cout << pl1;
    cout << pl2;
    
    tLine result {pl1, pl2};    

    cout << result;

    return 0;
}