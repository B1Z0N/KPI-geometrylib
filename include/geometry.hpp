#ifndef __GEOMETRY_LIB_INCLUSION_MACRO
#define __GEOMETRY_LIB_INCLUSION_MACRO

/** @brief Library for working with geometric objects
 *  @detailed Классы: 
 *  point, line, plane, vector, triangle, tetrahedron.
 *  
 *  @author Written by Samarin M. Updated by Fedurko N. A.
 *  @date April 2019
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
/// @brief 2x2 matrix determinant
double Deter2(double a, double b,
              double c, double d);
/// @brief 3x3 matrix determinant
double Deter3(double a, double b, double c,
              double d, double e, double f,
              double g, double h, double i);
/// @brief 4x4 matrix determinant
double Deter4(double a, double b, double c, double d,
              double e, double f, double g, double h,
              double i, double j, double k, double l,
              double m, double n, double o, double p);

//---------------------------tNamed-------------------------------------

/// Common base class for all other classes
class tNamed
{
private:
    /// Shape name
    char *fName;
    /// Name length
    int fNameLength;

public:
    /// Constructor by name
    tNamed(char const *NewName = "");
    tNamed(const tNamed &x);
    ~tNamed();

    const char *Name() const;
    char *Name();
    int NameLength() const;

    tNamed &operator=(const tNamed &);
};

/// Return the sign of the number
char sign(double);

//----------------------------------------------------------------------------

//-----------------------------POINT-----------------------------------------
/// Point class
class tPoint : public tNamed
{

private:
    /// Coordinates
    double fx, fy, fz;

public:
    /// Three point and name constructor
    tPoint(double newx = 0, double newy = 0, double newz = 0, char const *NewName = "");
    tPoint(const tPoint &);
    double x() const;
    void SetX(double t);
    double y() const;
    void SetY(double t);
    double z() const;
    void SetZ(double t);

    /// Distance to another point
    double DistTo(const tPoint &P) const;

    /// Move point
    void Move(const tPoint &P);
    /// Rotate point in YoZ plane
    void TurnXPoint(double phi);
    /// Rotate point in XoZ plane
    void TurnYPoint(double phi);
    /// Rotate a point in the XoY plane
    void TurnZPoint(double phi);

    tPoint &operator=(const tPoint &);
    friend bool operator==(const tPoint &, const tPoint &);

    friend ostream &operator<<(ostream &, const tPoint &);
    friend istream &operator>>(istream &, tPoint &);
};

//---------------------------------------------------------------------------

//--------------------------------VECTOR-------------------------------------
/// Class vector
class tVector : public tPoint
{

public:
    /// Error class when the vector was set by two equal points
    class SinglePointError {};

    tVector();
    /// Vector constructor via point coordinates (the first point is zero)
    tVector(double newx, double newy, double newz, char const *NewName = "");
    tVector(const tVector &);

    /// Vector by two points
    tVector(const tPoint &, const tPoint &);

    /// Norm (length) of vector
    double Norm() const;
    /// Normalization of a vector (for constant vectors)
    /// @return normalized vector
    tVector Normalize() const;
    /// Normalization of a vector
    void Normalize();

    tVector &operator=(const tVector &);
    friend bool operator==(const tVector &, const tVector &);

    /// Scalar multiplication on the right
    friend tVector &operator*(const tVector &, double);
    // And on the left
    friend tVector &operator*(double, const tVector &);

    /// Sum of vectors
    friend tVector &operator+(const tVector &, const tVector &);
    /// Vectors difference
    friend tVector &operator-(const tVector &, const tVector &); 
    /// Vector product of vectors
    friend tVector &operator*(const tVector &, const tVector &);

    tVector &operator*=(double);
    tVector &operator+=(const tVector &);
    tVector &operator-=(const tVector &);
    tVector &operator*=(const tVector &);

    friend ostream &operator<<(ostream &, const tVector &);
    friend istream &operator>>(istream &, tVector &);
    /// Dot product of vectors
    friend double operator,(const tVector &, const tVector &); 
};

//---------------------------------------------------------------------------

//----------------------------PLANE------------------------------------------

/// Plane class
class tPlane : public tNamed
{

private:
    /// Fields of plane equation
    double fA, fB, fC, fD;

public:
    /// Constructor by fields
    tPlane(double newA = 0, double newB = 0, double newC = 1, double newD = 0, char const *NewName = "a Plane");
    tPlane(const tPlane &);

    /// Constructor by three points
    tPlane(const tPoint &, const tPoint &, const tPoint &);

    double A() const;
    void setA(double);
    double B() const;
    void setB(double);
    double C() const;
    void setC(double);
    double D() const;
    void setD(double);

    /// Set new fields values
    void setnew(double, double, double, double);

    /// Check if the coefficients in the equation are not too small
    /// (internal function)
    bool correct() const;
    /// Normalization of the plane
    void Normalize();
    /// Normalization of the plane (for constant planes)
    /// @return normalized plane
    tPlane Normalize() const;

    /// Check whether the point is on the plane
    bool HasPoint(const tPoint &) const;
    /// Find the distance from the point to the plane
    double DistToPoint(const tPoint &) const;

    tPlane &operator=(const tPlane &);
    friend bool operator==(const tPlane &, const tPlane &);

    friend ostream &operator<<(ostream &, const tPlane &);
    friend istream &operator>>(istream &, tPlane &);
};

/// Find the intersection point of three planes
tPoint Cut3Planes(const tPlane &a, const tPlane &b, const tPlane &c);
/// Find the projection of the point on the plane
tPoint ProjectPointToPlane(const tPoint &M, const tPlane &P);
//---------------------------------------------------------------------------

//----------------------------LINE-------------------------------------------

/// Line class
class tLine : public tNamed
{
private:
    /// Точка через которую она проходит
    tPoint fSource;
    /// Direction Vector
    tVector fDir;

public:
    /** @brief Constructor by fields
     *  @detailed Equation of a line in 3d:
     *  (x-a)/n = (x-b)/m = (x-c)/p
     * 
     *  Enter the fields in this order:
     *  a, b, c (up first), n, m, p (then down)
     */
    tLine(double newa = 0, double newb = 0, double newc = 0,
          double newn = 1, double newm = 0, double newp = 0, char const *NewName = "a Line");
    /// Constructor by two points and name
    tLine(const tPoint& A, const tPoint& B, char const * NewName = "a Line");
    /// Constructor by point, direction vector and name
    tLine(const tPoint& S, const tVector& D, char const *NewName = "a Line");
    /// Constructor by the intersection of two planes and the name
    tLine(const tPlane& v1, const tPlane& v2, char const *NewName = "a Line");
    tLine(const tLine &);
    /// Constructor of the line as a perpendicular point to the plane
    tLine(const tPoint &, const tPlane &);

    /// Set new fields values
    void setnew(double, double, double,
                double, double, double);

    /// Check if the coefficients in the equation are not too small
    /// (internal function)
    bool correct() const;

    /// Get direction vector
    tVector GDir() const;
    /// Get starting point
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

    /// Set the starting point
    void SetSource(const tPoint &);
    /// Set Direction Vector  
    void SetDir(const tVector &);

    /// Check whether the point is on the line
    bool HasPoint(const tPoint &) const;
    /// Find the distance from point to line
    double DistToPoint(const tPoint &) const;
    /// Check lines for parallelism
    bool LinePar(const tLine &) const;

    tLine &operator=(const tLine &);
    friend bool operator==(const tLine&, const tLine&);

    friend ostream &operator<<(ostream &, const tLine &);
    friend istream &operator>>(istream &, tLine &);
};
/// Find the intersection point of a line and a plane
tPoint LineCutPlane(const tLine& l, const tPlane& p);
//----------------------------------------------------------------------------

//--------------------------TRIANGLE-----------------------------------------

/// Triangle class
class tTriangle : public tNamed
{

private:
    /// Vertex coordinates
    tPoint fA, fB, fC;

public:
    /// Constructor by vertices coordinates and name
    tTriangle(double Ax = 0, double Ay = 0, double Az = 0,
              double Bx = 1, double By = 0, double Bz = 0,
              double Cx = 0, double Cy = 1, double Cz = 0, char const*NewName = "a Triangle");
    /// Three-point constructor (vertices)
    tTriangle(const tPoint &A, const tPoint &B, const tPoint &C, char const *NewName = "a Triangle");
    tTriangle(const tTriangle &T);
    /// Check if the coefficients in the equation are not too small
    /// (internal function)
    bool correct() const;

    tPoint GetA() const;
    void SetA(const tPoint &);
    tPoint GetB() const;
    void SetB(const tPoint &);
    tPoint GetC() const;
    void SetC(const tPoint &);

    /// Square of triangle
    double Square() const; 

    tTriangle &operator=(const tTriangle &);
    friend bool operator==(const tTriangle &, const tTriangle &);

    friend ostream &operator<<(ostream &, const tTriangle &);
    friend istream &operator>>(istream &, tTriangle &);
};

//---------------------------------------------------------------------------

//-----------------------------TETRAEDR--------------------------------------
/// class of the Tetrahedron - triangle pyramid
class tTetraedr : public tNamed
{
private:
    /// Triangle as a base of tetrahedron
    tTriangle fT;
    /// Fourth vertice, above the base
    tPoint fS;

public:
    /// Constructor by four vertices and a name
    tTetraedr(const tPoint &V1, const tPoint &V2, const tPoint &V3,
              const tPoint &S, char const *NewName = "a Tetraedr");
    /// Constructor by four planes and name
    tTetraedr(const tPlane &, const tPlane &, const tPlane &, const tPlane &,
              char const *NewName = "a Tetraedr");
    ///  Constructor by triangle(base), point(4th vertice) and a name
    tTetraedr(const tTriangle &, const tPoint &, char const *NewName = "a Tetraedr");
    /// Four-point coordinates and name constructor
    tTetraedr(double ax = 0, double ay = 0, double az = 0,
              double bx = 1, double by = 0, double bz = 0,
              double cx = 0, double cy = 1, double cz = 0,
              double sx = 0, double sy = 0, double sz = 1, char const *NewName = "a Tetraedr");
    tTetraedr(const tTetraedr &);
    /// Check if the coefficients in the equation are not too small
    /// (internal function) 
    bool correct() const;

    tPoint GetS() const;
    void SetS(const tPoint &);
    tTriangle GetT() const;
    void SetT(const tTriangle &);

    /// Tetrahedron volume
    double Volume() const;

    tTetraedr &operator=(const tTetraedr &);
    friend bool operator==(const tTetraedr &, const tTetraedr &);

    friend ostream &operator<<(ostream &, const tTetraedr &);
    friend istream &operator>>(istream &, tTetraedr &);
};

#endif