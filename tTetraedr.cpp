#include "geometry.hpp"

tTetraedr::tTetraedr(tPoint &V1, tPoint &V2, tPoint &V3, tPoint &S, char *NewName) : fT(V1, V2, V3), fS(S)
{
  tNamed::tNamed(NewName);
  assert(correct());
}

tTetraedr::tTetraedr(tTriangle &N, tPoint &S, char *NewName) : fT(N), fS(S)
{
  tNamed::tNamed(NewName);
  assert(correct());
}

tTetraedr::tTetraedr(double ax, double ay, double az,
                     double bx, double by, double bz,
                     double cx, double cy, double cz,
                     double sx, double sy, double sz, char *NewName) : fT(ax, ay, az, bx, by, bz, cx, cy, cz),
                                                                       fS(sx, sy, sz)
{
  tNamed::tNamed(NewName);
  assert(correct());
}

tTetraedr::tTetraedr(tTetraedr &T)
{

  tNamed::tNamed(T);
  fT = T.GetT();
  fS = T.GetS();
}

tTetraedr::tTetraedr(tPlane &P1, tPlane &P2, tPlane &P3, tPlane &P4, char *NewName)
{
  tNamed::tNamed(NewName);
  tPoint S = Cut3Planes(P1, P2, P3), A = Cut3Planes(P1, P2, P4), B = Cut3Planes(P1, P3, P4), C = Cut3Planes(P2, P3, P4);
  tTriangle T(A, B, C);
  fT = T;
  fS = S;
  assert(correct());
}

int tTetraedr::correct()
{
  if (Volume() < eps)
    return 0;
  else
    return 1;
}

double tTetraedr::Volume()
{
  double Vol;
  tPlane P(fT.GetA(), fT.GetB(), fT.GetC());
  Vol = (1.0 / 3) * fT.Square() * P.DistToPoint(fS);
  return Vol;
}

tPoint tTetraedr::GetS()
{
  return fS;
}

void tTetraedr::SetS(tPoint &P)
{
  fS = P;
  assert(correct());
}

tTriangle tTetraedr::GetT()
{
  return fT;
}
void tTetraedr::SetT(tTriangle &T)
{
  fT = T;
  assert(correct());
}

tTetraedr &tTetraedr::operator=(tTetraedr &T)
{

  fT = T.GetT();
  fS = T.GetS();

  return *this;
}

int operator==(tTetraedr &T1, tTetraedr &T2)
{
  if ((T1.GetT() == T2.GetT()) && (T1.GetS() == T2.GetS()))
    return 1;
  else
    return 0;
}

ostream &operator<<(ostream &output, tTetraedr &T)
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