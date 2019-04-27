#ifndef __GEOMETRY_LIB_INCLUSION_MACRO
#define __GEOMETRY_LIB_INCLUSION_MACRO

/** @brief Библиотека для работы с геометрическими обьектами.
 *  @detailed Классы: 
 *  точка, прямая, плоскость, вектор, треугольник, тетраэдр.
 *  
 *  @author Написано Самариным М. С. Обновлено Федурком Н. А.
 *  @date Апрель 2019
 */

#include <memory>
#include <iostream>
#include <math.h>
#include <string.h>
#include <assert.h>

using namespace std;

const double eps = 1e-8,
             PI = M_PI,
             pi = M_PI,
             Pi = M_PI;

void NormAngle(double &phi);
/// @brief Определитель матрицы 2х2
double Deter2(double a, double b,
              double c, double d);
/// @brief Определитель матрицы 3х3
double Deter3(double a, double b, double c,
              double d, double e, double f,
              double g, double h, double i);
/// @brief Определитель матрицы 4х4
double Deter4(double a, double b, double c, double d,
              double e, double f, double g, double h,
              double i, double j, double k, double l,
              double m, double n, double o, double p);

//---------------------------tNamed-------------------------------------

/// Общий базовый класс для всех остальных классов
class tNamed
{
private:
    /// Имя фигуры
    char *fName;
    /// Длинна имени
    int fNameLength;

public:
    /// Конструктор по имени
    tNamed(char const *NewName = "");
    tNamed(const tNamed &x);
    ~tNamed();

    const char *Name() const;
    char *Name();
    int NameLength() const;

    tNamed &operator=(const tNamed &);
};

/// Возвратить знак числа
char sign(double);

//----------------------------------------------------------------------------

//-----------------------------POINT-----------------------------------------
/// Класс точки
class tPoint : public tNamed
{

private:
    /// Координаты
    double fx, fy, fz;

public:
    /// Конструктор по трем точкам и имени
    tPoint(double newx = 0, double newy = 0, double newz = 0, char const *NewName = "");
    tPoint(const tPoint &);
    double x() const;
    void SetX(double t);
    double y() const;
    void SetY(double t);
    double z() const;
    void SetZ(double t);

    /// Расстоаяние до другой точки
    double DistTo(const tPoint &P) const; //distance to other point

    /// Переместить точку
    void Move(const tPoint &P);
    /// Повернуть точку в плоскости YoZ
    void TurnXPoint(double phi);
    /// Повернуть точку в плоскости XoZ
    void TurnYPoint(double phi);
    /// Повернуть точку в плоскости XoY
    void TurnZPoint(double phi);

    tPoint &operator=(const tPoint &);
    friend bool operator==(const tPoint &, const tPoint &);

    friend ostream &operator<<(ostream &, const tPoint &);
    friend istream &operator>>(istream &, tPoint &);
};

//---------------------------------------------------------------------------

//--------------------------------VECTOR-------------------------------------
/// Класс вектора
class tVector : public tPoint
{

public:
    /// Класс ошибки, когда вектор задали двумя равными точками
    class SinglePointError {};

    tVector();
    /// Конструктор вектора через координаты точки (первая точка берется нуль)
    tVector(double newx, double newy, double newz, char const *NewName = "");
    tVector(const tVector &);

    /// Вектор через две точки
    tVector(const tPoint &, const tPoint &);

    /// Норма(длинна) вектора
    double Norm() const;
    /// Нормировка вектора (для константых векторов)
    /// @return нормированый вектор
    tVector Normalize() const;
    /// Нормировка вектора
    void Normalize();

    tVector &operator=(const tVector &);
    friend bool operator==(const tVector &, const tVector &);

    /// Умножение на скаляр справа
    friend tVector &operator*(const tVector &, double);
    // И слева
    friend tVector &operator*(double, const tVector &);

    /// Сумма векторов
    friend tVector &operator+(const tVector &, const tVector &);
    /// Разница векторов
    friend tVector &operator-(const tVector &, const tVector &); 
    /// Вектороное произведение векторов
    friend tVector &operator*(const tVector &, const tVector &);

    tVector &operator*=(double);
    tVector &operator+=(const tVector &);
    tVector &operator-=(const tVector &);
    tVector &operator*=(const tVector &);

    friend ostream &operator<<(ostream &, const tVector &);
    friend istream &operator>>(istream &, tVector &);
    /// Скалярное произведение векторов
    friend double operator,(const tVector &, const tVector &); 
};

//---------------------------------------------------------------------------

//----------------------------PLANE------------------------------------------

/// Класс плоскости
class tPlane : public tNamed
{

private:
    /// Коефициенты уравнения плоскости
    double fA, fB, fC, fD;

public:
    /// Конструктор по коефициентам
    tPlane(double newA = 0, double newB = 0, double newC = 1, double newD = 0, char const *NewName = "a Plane");
    tPlane(const tPlane &);

    /// Конструктор через три точки
    tPlane(const tPoint &, const tPoint &, const tPoint &);

    double A() const;
    void setA(double);
    double B() const;
    void setB(double);
    double C() const;
    void setC(double);
    double D() const;
    void setD(double);

    /// Установить новые значения коефициентов
    void setnew(double, double, double, double);

    /// Проверить, не слишком ли малы коефициенты в уравнении
    /// (внутренняя функция) 
    bool correct() const;
    /// Нормировка плоскости
    void Normalize();
    /// Нормировка плоскости (для константых плоскостей)
    /// @return нормированую плоскость
    tPlane Normalize() const;

    /// Проверить принадлежит ли точка плоскости
    bool HasPoint(const tPoint &) const;
    /// Найти расстояние от точки до плоскости
    double DistToPoint(const tPoint &) const;

    tPlane &operator=(const tPlane &);
    friend bool operator==(const tPlane &, const tPlane &);

    friend ostream &operator<<(ostream &, const tPlane &);
    friend istream &operator>>(istream &, tPlane &);
};

/// Найти точку пересечения трех плоскостей
tPoint Cut3Planes(const tPlane &a, const tPlane &b, const tPlane &c);
/// Найти проекцию точки на плоскость
tPoint ProjectPointToPlane(const tPoint &M, const tPlane &P);
//---------------------------------------------------------------------------

//----------------------------LINE-------------------------------------------

/// Класс прямой линии
class tLine : public tNamed
{
private:
    /// Точка через которую она проходит
    tPoint fSource;
    /// Вектор направления
    tVector fDir;

public:
    /** @brief Конструктор через коефициенты 
     *  @detailed Уравнение прямой в пространстве:
     *  (x-a)/n = (x-b)/m = (x-c)/p
     * 
     *  Ввести коефициенты в таком порядке:
     *  a, b, c (сначала верхние), n, m, p (потом нижние)
     */
    tLine(double newa = 0, double newb = 0, double newc = 0,
          double newn = 1, double newm = 0, double newp = 0, char const *NewName = "a Line");
    /// Конструктор через две точки и имя
    tLine(const tPoint& A, const tPoint& B, char const * NewName = "a Line");
    /// Конструктор через точку, вектор направления и имя
    tLine(const tPoint& S, const tVector& D, char const *NewName = "a Line");
    /// Конструктор чере пересечение двух плоскостей и имя
    tLine(const tPlane& v1, const tPlane& v2, char const *NewName = "a Line");
    tLine(const tLine &);
    /// Конструктор прямой как перпендикуляр точки к плоскости
    tLine(const tPoint &, const tPlane &);

    /// Установить новые значения коефициентов
    void setnew(double, double, double,
                double, double, double);

    /// Проверить, не слишком ли малы коефициенты в уравнении
    /// (внутренняя функция) 
    bool correct() const;

    /// Получить вектор направления
    tVector GDir() const;
    /// Получить начальную точку
    tPoint GSource() const;

    double Sx() const;
    void SetSx(double);
    double Dx() const;
    void SetDx(double);
    double Sy() const;
    void SetSy(double);
    double Dy() const;
    void SetDy(double);
    double Sz() const;
    void SetSz(double);
    double Dz() const;
    void SetDz(double);

    /// Установить начальную точку
    void SetSource(const tPoint &);
    /// Установить вектор направления    
    void SetDir(const tVector &);

    /// Проверить принадлежит ли точка прямой
    bool HasPoint(const tPoint &) const;
    /// Найти расстояние от точки к прямой
    double DistToPoint(const tPoint &) const;
    /// Проверить прямые на паралельность
    bool LinePar(const tLine &) const;

    tLine &operator=(const tLine &);
    friend bool operator==(const tLine&, const tLine&);

    friend ostream &operator<<(ostream &, const tLine &);
    friend istream &operator>>(istream &, tLine &);
};
/// Найти точку пересечения прямой и плоскости
tPoint LineCutPlane(const tLine& l, const tPlane& p);
//----------------------------------------------------------------------------

//--------------------------TRIANGLE-----------------------------------------

/// Класс треугольника
class tTriangle : public tNamed
{

private:
    /// Координаты вершин
    tPoint fA, fB, fC;

public:
    /// Конструктор по координатам вершин и имени
    tTriangle(double Ax = 0, double Ay = 0, double Az = 0,
              double Bx = 1, double By = 0, double Bz = 0,
              double Cx = 0, double Cy = 1, double Cz = 0, char const*NewName = "a Triangle");
    /// Конструктор по трем точкам(вершинам)
    tTriangle(const tPoint &A, const tPoint &B, const tPoint &C, char const *NewName = "a Triangle");
    tTriangle(const tTriangle &T);
    /// Проверить, не слишком ли малы коефициенты в уравнении
    /// (внутренняя функция) 
    bool correct() const;

    tPoint GetA() const;
    void SetA(const tPoint &);
    tPoint GetB() const;
    void SetB(const tPoint &);
    tPoint GetC() const;
    void SetC(const tPoint &);

    /// Найти площадь треугольника
    double Square() const; //square of triangle

    tTriangle &operator=(const tTriangle &);
    friend bool operator==(const tTriangle &, const tTriangle &);

    friend ostream &operator<<(ostream &, const tTriangle &);
    friend istream &operator>>(istream &, tTriangle &);
};

//---------------------------------------------------------------------------

//-----------------------------TETRAEDR--------------------------------------
/// Класс тетраэдра - трегуольной пирамиды
class tTetraedr : public tNamed
{
private:
    /// Треугольник основы
    tTriangle fT;
    /// Четвертая вершина(над основой)
    tPoint fS;

public:
    /// Конструктор по четырем точкам и имени
    tTetraedr(const tPoint &V1, const tPoint &V2, const tPoint &V3,
              const tPoint &S, char const *NewName = "a Tetraedr");
    /// Конструктор по четырем плоскостям и  имени
    tTetraedr(const tPlane &, const tPlane &, const tPlane &, const tPlane &,
              char const *NewName = "a Tetraedr");
    /// Конструктор по треугольнику(основе) и точке(четвертой вершине) и имени
    tTetraedr(const tTriangle &, const tPoint &, char const *NewName = "a Tetraedr");
    /// Конструктор по координатам четырех точек и имени
    tTetraedr(double ax = 0, double ay = 0, double az = 0,
              double bx = 1, double by = 0, double bz = 0,
              double cx = 0, double cy = 1, double cz = 0,
              double sx = 0, double sy = 0, double sz = 1, char const *NewName = "a Tetraedr");
    tTetraedr(const tTetraedr &);
    /// Проверить, не слишком ли малы коефициенты в уравнении
    /// (внутренняя функция) 
    bool correct() const;

    tPoint GetS() const;
    void SetS(const tPoint &);
    tTriangle GetT() const;
    void SetT(const tTriangle &);

    /// Объём тетраэдра
    double Volume() const;

    tTetraedr &operator=(const tTetraedr &);
    friend bool operator==(const tTetraedr &, const tTetraedr &);

    friend ostream &operator<<(ostream &, const tTetraedr &);
    friend istream &operator>>(istream &, tTetraedr &);
};

#endif