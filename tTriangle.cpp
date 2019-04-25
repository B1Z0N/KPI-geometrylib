#include "geometry.hpp"

tTriangle::tTriangle(const tPoint &A, const tPoint &B, const tPoint &C, char const *NewName)
    : tNamed(NewName)
{
  fA = A;
  fB = B;
  fC = C;
  assert(correct());
}

tTriangle::tTriangle(double Ax, double Ay, double Az,
                     double Bx, double By, double Bz,
                     double Cx, double Cy, double Cz, char const *NewName) 
                     : tNamed(NewName), fA(Ax, Ay, Az), fB(Bx, By, Bz), fC(Cx, Cy, Cz)
{
  assert(correct());
}
tTriangle::tTriangle(const tTriangle &T)
    : tNamed(T)
{
  fA = T.GetA();
  fB = T.GetB();
  fC = T.GetC();
}

int tTriangle::correct() const
{
  if (Square() < eps)
    return 0;
  else
    return 1;
}

double tTriangle::Square() const
{
  tVector AB(fA, fB), AC(fA, fC), v = AB * AC;
  return (v.Norm() / 2);
}

tPoint tTriangle::GetA() const
{
  return fA;
}
void tTriangle::SetA(const tPoint &P)
{
  fA = P;
  assert(correct());
}

tPoint tTriangle::GetB() const
{
  return fB;
}
void tTriangle::SetB(const tPoint &P)
{
  fB = P;
  assert(correct());
}

tPoint tTriangle::GetC() const
{
  return fC;
}
void tTriangle::SetC(const tPoint &P)
{
  fC = P;
  assert(correct());
}

tTriangle &tTriangle::operator=(const tTriangle &T)
{
  fA = T.GetA();
  fB = T.GetB();
  fC = T.GetC();
  return *this;
}

int operator==(const tTriangle &T1, const tTriangle &T2)
{
  if ((T1.GetA() == T2.GetA()) && (T1.GetA() == T2.GetA()) && (T1.GetA() == T2.GetA()))
    return 1;
  else
    return 0;
}

ostream &operator<<(ostream &output, const tTriangle &T)
{
  output << "Triangle: \nA: " << T.GetA() << "B: " << T.GetB() << "C: " << T.GetC();

  return output;
}

istream &operator>>(istream &input, tTriangle &T)
{
  tPoint P1, P2, P3;
  cout << "Enter triangle(3 points): \n";
  cin >> P1 >> P2 >> P3;
  tTriangle Tr(P1, P2, P3);
  T = Tr;
}