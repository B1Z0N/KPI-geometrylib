#include "geometry.hpp"

tTriangle::tTriangle(tPoint &A, tPoint &B, tPoint &C, char *NewName)
{
  tNamed::tNamed(NewName);
  fA = A;
  fB = B;
  fC = C;
  assert(correct());
}

tTriangle::tTriangle(double Ax, double Ay, double Az,
                     double Bx, double By, double Bz,
                     double Cx, double Cy, double Cz, char *NewName) : fA(Ax, Ay, Az), fB(Bx, By, Bz), fC(Cx, Cy, Cz)
{
  tNamed::tNamed(NewName);
  assert(correct());
}
tTriangle::tTriangle(tTriangle &T)
{
  tNamed::tNamed(T);
  fA = T.GetA();
  fB = T.GetB();
  fC = T.GetC();
}

int tTriangle::correct()
{
  if (Square() < eps)
    return 0;
  else
    return 1;
}

double tTriangle::Square()
{
  tVector AB(fA, fB), AC(fA, fC), v = AB * AC;
  return (v.Norm() / 2);
}

tPoint &tTriangle::GetA()
{
  return fA;
}
void tTriangle::SetA(tPoint &P)
{
  fA = P;
  assert(correct());
}

tPoint &tTriangle::GetB()
{
  return fB;
}
void tTriangle::SetB(tPoint &P)
{
  fB = P;
  assert(correct());
}

tPoint &tTriangle::GetC()
{
  return fC;
}
void tTriangle::SetC(tPoint &P)
{
  fC = P;
  assert(correct());
}

tTriangle &tTriangle::operator=(tTriangle &T)
{
  fA = T.GetA();
  fB = T.GetB();
  fC = T.GetC();
  return *this;
}

int operator==(tTriangle &T1, tTriangle &T2)
{
  if ((T1.GetA() == T2.GetA()) && (T1.GetA() == T2.GetA()) && (T1.GetA() == T2.GetA()))
    return 1;
  else
    return 0;
}

ostream &operator<<(ostream &output, tTriangle &T)
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