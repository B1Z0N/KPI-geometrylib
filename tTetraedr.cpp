#include "geometry.hpp"

tTetraedr::tTetraedr(const tPoint &V1, const tPoint &V2, const tPoint &V3, const tPoint &S, char *NewName)
    : tNamed(NewName), fT(V1, V2, V3), fS(S)
{
  assert(correct());
}

tTetraedr::tTetraedr(const tTriangle &N, const tPoint &S, char *NewName)
    : tNamed(NewName), fT(N), fS(S)
{
  assert(correct());
}

tTetraedr::tTetraedr(double ax, double ay, double az,
                     double bx, double by, double bz,
                     double cx, double cy, double cz,
                     double sx, double sy, double sz, char *NewName) 
                     : tNamed(NewName), fT(ax, ay, az, bx, by, bz, cx, cy, cz), fS(sx, sy, sz)
{
  assert(correct());
}

tTetraedr::tTetraedr(const tTetraedr &T)
  :tNamed(T)
{
  fT = T.GetT();
  fS = T.GetS();
}

tTetraedr::tTetraedr(const tPlane &P1, const tPlane &P2, const tPlane &P3, const tPlane &P4, char *NewName)
  :tNamed(NewName)
{
  tPoint S = Cut3Planes(P1, P2, P3), A = Cut3Planes(P1, P2, P4), B = Cut3Planes(P1, P3, P4), C = Cut3Planes(P2, P3, P4);
  tTriangle T(A, B, C);
  fT = T;
  fS = S;
  assert(correct());
}

int tTetraedr::correct() const
{
  if (Volume() < eps)
    return 0;
  else
    return 1;
}

double tTetraedr::Volume() const
{
  double Vol;
  tPlane P(fT.GetA(), fT.GetB(), fT.GetC());
  Vol = (1.0 / 3) * fT.Square() * P.DistToPoint(fS);
  return Vol;
}

tPoint tTetraedr::GetS() const
{
  return fS;
}

void tTetraedr::SetS(const tPoint &P)
{
  fS = P;
  assert(correct());
}

tTriangle tTetraedr::GetT() const
{
  return fT;
}
void tTetraedr::SetT(const tTriangle &T)
{
  fT = T;
  assert(correct());
}

tTetraedr &tTetraedr::operator=(const tTetraedr &T)
{

  fT = T.GetT();
  fS = T.GetS();

  return *this;
}

int operator==(const tTetraedr &T1, const tTetraedr &T2)
{
  if ((T1.GetT() == T2.GetT()) && (T1.GetS() == T2.GetS()))
    return 1;
  else
    return 0;
}

ostream &operator<<(ostream &output, const tTetraedr &T)
{
  output << "Tetraedr: \nBase:" << T.GetT() << "Pik: " << T.GetS();
  return output;
}

istream &operator>>(istream &input, tTetraedr &Tet)
{
  tPoint p;
  tTriangle T;
  cout << "Enter tetraedr(triangle of basis & poiunt of pik): \n";
  cin >> T;
  cin >> p;
  tTetraedr j(T, p);
  Tet = j;
}