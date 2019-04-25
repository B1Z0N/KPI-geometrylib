//write [assignment operator, constructor] x [copy, move]
//virtual functions, like: correct, operator==, operator=, operator>>, operator<<
//namespaces

#ifndef __GEOMETRY_LIB_INCLUSION_MACRO
#define __GEOMETRY_LIB_INCLUSION_MACRO

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
//Determinant
double Deter2(double a, double b,
              double c, double d);
double Deter3(double a, double b, double c,
              double d, double e, double f,
              double g, double h, double i);
double Deter4(double a, double b, double c, double d,
              double e, double f, double g, double h,
              double i, double j, double k, double l,
              double m, double n, double o, double p);

//---------------------------tNamed-------------------------------------

class tNamed
{

private:
    char *fName;
    int fNameLength;

public:
    tNamed(char const *NewName = ""); // default constructor by name
    tNamed(const tNamed &x);    // copying constructor
    ~tNamed();

    char *Name() const;
    int NameLength() const;

    tNamed &operator=(const tNamed &);
};

char sign(double); // Number sign (+ or -)

//----------------------------------------------------------------------------

//-----------------------------POINT-----------------------------------------
class tPoint : public tNamed
{

private:
    double fx, fy, fz;

public:
    tPoint(double newx = 0, double newy = 0, double newz = 0, char const *NewName = "");
    tPoint(const tPoint &); // copying constructor
    double x() const;
    void SetX(double t);
    double y() const;
    void SetY(double t);
    double z() const;
    void SetZ(double t);

    double DistTo(const tPoint &P) const; //distance to other point

    void Move(const tPoint &P);  //moving point
    void TurnXPoint(double phi); //turning point
    void TurnYPoint(double phi);
    void TurnZPoint(double phi);

    tPoint &operator=(const tPoint &);
    friend bool operator==(const tPoint &, const tPoint &);

    friend ostream &operator<<(ostream &, const tPoint &); //output
    friend istream &operator>>(istream &, tPoint &);       //input
};

//---------------------------------------------------------------------------

//--------------------------------VECTOR-------------------------------------
class tVector : public tPoint
{

public:
    class SinglePointError {};

    tVector();
    tVector(double newx, double newy, double newz, char const *NewName = "");
    tVector(const tVector &); // copying constructor

    tVector(const tPoint &, const tPoint &);

    double Norm() const; // norm (length) of vector
    tVector Normalize() const;
    void Normalize();

    tVector &operator=(const tVector &);
    friend bool operator==(const tVector &, const tVector &);

    friend tVector &operator*(const tVector &, double); //mult to scalar
    friend tVector &operator*(double, const tVector &);

    friend tVector &operator+(const tVector &, const tVector &); //sum of vectors
    friend tVector &operator-(const tVector &, const tVector &); //substraction of
    friend tVector &operator*(const tVector &, const tVector &); //vector mult

    tVector &operator*=(double);
    tVector &operator+=(const tVector &);
    tVector &operator-=(const tVector &);
    tVector &operator*=(const tVector &);

    friend ostream &operator<<(ostream &, const tVector &);
    friend istream &operator>>(istream &, tVector &);
    friend double operator,(const tVector &, const tVector &); // scalar mult
};

//---------------------------------------------------------------------------

//----------------------------PLANE------------------------------------------

class tPlane : public tNamed
{

private:
    double fA, fB, fC, fD;

public:
    tPlane(double newA = 0, double newB = 0, double newC = 1, double newD = 0, char const *NewName = "a Plane");
    tPlane(const tPlane &); // copying constructor

    tPlane(const tPoint &, const tPoint &, const tPoint &); // plain via 3 points

    double A() const;
    void setA(double);
    double B() const;
    void setB(double);
    double C() const;
    void setC(double);
    double D() const;
    void setD(double);

    void setnew(double, double, double, double); //set new values of fields

    bool correct() const;
    void Normalize();
    tPlane Normalize() const;

    bool HasPoint(const tPoint &) const;       //check point on membership of plane
    double DistToPoint(const tPoint &) const; //distance from plane to point

    tPlane &operator=(const tPlane &);
    friend bool operator==(const tPlane &, const tPlane &);

    friend ostream &operator<<(ostream &, const tPlane &);
    friend istream &operator>>(istream &, tPlane &);
};
tPoint Cut3Planes(const tPlane &a, const tPlane &b, const tPlane &c); // creating point as intersect of 3 planes
//---------------------------------------------------------------------------

//----------------------------LINE-------------------------------------------

class tLine : public tNamed
{
private:
    tPoint fSource;
    tVector fDir;

public:
    tLine(double newa = 0, double newb = 0, double newc = 0,
          double newn = 1, double newm = 0, double newp = 0, char const *NewName = "a Line");
    tLine(const tPoint& S, const tVector& D, char const *NewName = "a Line");
    tLine(const tPlane& v1, const tPlane& v2, char const *NewName = "a Line"); //creating line as intersect of 2 planes
    tLine(const tLine &);                                  //copying constructor
    tLine(const tPoint &, const tPlane &);                             //perpendikular

    void setnew(double, double, double,
                double, double, double); //set new values of fields

    bool correct() const;

    tVector GDir() const;
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

    void SetSource(const tPoint &);
    void SetDir(const tVector &);

    bool HasPoint(const tPoint &) const;       //check point on membership of line
    double DistToPoint(const tPoint &) const; //distance from line to point
    bool LinePar(const tLine &) const;         //testing on parallel lines

    tLine &operator=(const tLine &);
    friend bool operator==(const tLine&, const tLine&);

    friend ostream &operator<<(ostream &, const tLine &);
    friend istream &operator>>(istream &, tLine &);
};

tPoint LineCutPlane(const tLine& l, const tPlane& p); //creating point as intersect of plane & line
tPoint ProjectPointToPlane(const tPoint &M, const tPlane &P);
//----------------------------------------------------------------------------

//--------------------------TRIANGLE-----------------------------------------

class tTriangle : public tNamed
{

private:
    tPoint fA, fB, fC;

public:
    tTriangle(double Ax = 0, double Ay = 0, double Az = 0,
              double Bx = 1, double By = 0, double Bz = 0,
              double Cx = 0, double Cy = 1, double Cz = 0, char const*NewName = "a Triangle");
    tTriangle(const tPoint &A, const tPoint &B, const tPoint &C, char const *NewName = "a Triangle");
    tTriangle(const tTriangle &T); //copying constructor
    bool correct() const;

    tPoint GetA() const;
    void SetA(const tPoint &);
    tPoint GetB() const;
    void SetB(const tPoint &);
    tPoint GetC() const;
    void SetC(const tPoint &);

    double Square() const; //square of triangle

    tTriangle &operator=(const tTriangle &);
    friend bool operator==(const tTriangle &, const tTriangle &);

    friend ostream &operator<<(ostream &, const tTriangle &);
    friend istream &operator>>(istream &, tTriangle &);
};

//---------------------------------------------------------------------------

//-----------------------------TETRAEDR--------------------------------------
class tTetraedr : public tNamed
{
private:
    tTriangle fT;
    tPoint fS;

public:
    tTetraedr(const tPoint &V1, const tPoint &V2, const tPoint &V3,
              const tPoint &S, char const *NewName = "a Tetraedr");
    tTetraedr(const tPlane &, const tPlane &, const tPlane &, const tPlane &,
              char const *NewName = "a Tetraedr"); //tetraedr creating as intersection of 4 planes
    tTetraedr(const tTriangle &, const tPoint &, char const *NewName = "a Tetraedr");
    tTetraedr(double ax = 0, double ay = 0, double az = 0,
              double bx = 1, double by = 0, double bz = 0,
              double cx = 0, double cy = 1, double cz = 0,
              double sx = 0, double sy = 0, double sz = 1, char const *NewName = "a Tetraedr");
    tTetraedr(const tTetraedr &); //copying constructor

    bool correct() const;

    tPoint GetS() const;
    void SetS(const tPoint &);
    tTriangle GetT() const;
    void SetT(const tTriangle &);

    double Volume() const; //volume of tetraedr

    tTetraedr &operator=(const tTetraedr &);
    friend bool operator==(const tTetraedr &, const tTetraedr &);

    friend ostream &operator<<(ostream &, const tTetraedr &);
    friend istream &operator>>(istream &, tTetraedr &);
};

#endif