//write [assignment operator, constructor] x [copy, move]
//fix conversion of string constant to char *
//change int to bool
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
    tNamed(char *NewName = ""); // default constructor by name
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
    tPoint(double newx = 0, double newy = 0, double newz = 0, char *NewName = "");
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
    friend int operator==(const tPoint &, const tPoint &);

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
    tVector(double newx, double newy, double newz, char *NewName = "");
    tVector(const tVector &); // copying constructor

    tVector(const tPoint &, const tPoint &);

    double Norm() const; // norm (length) of vector
    tVector Normalize() const;
    void Normalize();

    tVector &operator=(const tVector &);
    friend int operator==(const tVector &, const tVector &);

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
    tPlane(double newA = 0, double newB = 0, double newC = 1, double newD = 0, char *NewName = "a Plane");
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

    int correct() const;
    void Normalize();
    tPlane Normalize() const;

    int HasPoint(const tPoint &) const;       //check point on membership of plane
    double DistToPoint(const tPoint &) const; //distance from plane to point

    tPlane &operator=(const tPlane &);
    friend int operator==(const tPlane &, const tPlane &);

    friend ostream &operator<<(ostream &, const tPlane &);
    friend istream &operator>>(istream &, tPlane &);
};
tPoint Cut3Planes(tPlane &a, tPlane &b, tPlane &c); // creating point as intersect of 3 planes
//---------------------------------------------------------------------------

//----------------------------LINE-------------------------------------------

class tLine : public tNamed
{
private:
    tPoint fSource;
    tVector fDir;

public:
    tLine(double newa = 0, double newb = 0, double newc = 0,
          double newn = 1, double newm = 0, double newp = 0, char *NewName = "a Line");
    tLine(tPoint S, tVector D, char *NewName = "a Line");
    tLine(tPlane v1, tPlane v2, char *NewName = "a Line"); //creating line as intersect of 2 planes
    tLine(const tLine &);                                  //copying constructor
    tLine(tPoint &, tPlane &);                             //perpendikular

    void setnew(double, double, double,
                double, double, double); //set new values of fields

    int correct();

    tVector &GDir();
    tPoint &GSource();

    double Sx();
    void SetSx(double);
    double Dx();
    void SetDx(double);
    double Sy();
    void SetSy(double);
    double Dy();
    void SetDy(double);
    double Sz();
    void SetSz(double);
    double Dz();
    void SetDz(double);

    void SetSource(tPoint &);
    void SetDir(tVector &);

    int HasPoint(tPoint &);       //check point on membership of line
    double DistToPoint(tPoint &); //distance from line to point
    int LinePar(tLine &);         //testing on parallel lines

    tLine &operator=(tLine &);
    friend int operator==(tLine, tLine);

    friend ostream &operator<<(ostream &, tLine &);
    friend istream &operator>>(istream &, tLine &);
};
tPoint LineCutPlane(tLine l, tPlane p); //creating point as intersect of plane & line
tPoint ProjectPointToPlane(tPoint &M, tPlane &P);
//----------------------------------------------------------------------------

//--------------------------TRIANGLE-----------------------------------------

class tTriangle : public tNamed
{

private:
    tPoint fA, fB, fC;

public:
    tTriangle(double Ax = 0, double Ay = 0, double Az = 0,
              double Bx = 1, double By = 0, double Bz = 0,
              double Cx = 0, double Cy = 1, double Cz = 0, char *NewName = "a Triangle");
    tTriangle(tPoint &A, tPoint &B, tPoint &C, char *NewName = "a Triangle");
    tTriangle(const tTriangle &T); //copying constructor
    int correct();

    tPoint &GetA();
    void SetA(tPoint &);
    tPoint &GetB();
    void SetB(tPoint &);
    tPoint &GetC();
    void SetC(tPoint &);

    double Square(); //square of triangle

    tTriangle &operator=(tTriangle &);
    friend int operator==(tTriangle &, tTriangle &);

    friend ostream &operator<<(ostream &, tTriangle &);
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
    tTetraedr(tPoint &V1, tPoint &V2, tPoint &V3,
              tPoint &S, char *NewName = "a Tetraedr");
    tTetraedr(tPlane &, tPlane &, tPlane &, tPlane &,
              char *NewName = "a Tetraedr"); //tetraedr creating as intersection of 4 planes
    tTetraedr(tTriangle &, tPoint &, char *NewName = "a Tetraedr");
    tTetraedr(double ax = 0, double ay = 0, double az = 0,
              double bx = 1, double by = 0, double bz = 0,
              double cx = 0, double cy = 1, double cz = 0,
              double sx = 0, double sy = 0, double sz = 1, char *NewName = "a Tetraedr");
    tTetraedr(const tTetraedr &); //copying constructor

    int correct();

    tPoint GetS();
    void SetS(tPoint &);
    tTriangle GetT();
    void SetT(tTriangle &);

    double Volume(); //volume of tetraedr

    tTetraedr &operator=(tTetraedr &);
    friend int operator==(tTetraedr &, tTetraedr &);

    friend ostream &operator<<(ostream &, tTetraedr &);
    friend istream &operator>>(istream &, tTetraedr &);
};

#endif