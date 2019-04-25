#include "geometry.hpp"

tLine::tLine(double newa, double newb, double newc,
             double newn, double newm, double newp, char *NewName) : fSource(newa, newb, newc), fDir(newn, newm, newp)
{
  tNamed::tNamed(NewName);
  assert(correct());
}

tLine::tLine(tPoint S, tVector D, char *NewName) : fSource(S), fDir(D)
{
  tNamed::tNamed(NewName);
  assert(correct());
}

tLine::tLine(tPlane v1, tPlane v2, char *NewName)
{
  tNamed::tNamed(NewName);
  fDir.SetX(v1.B() * v2.C() - v1.C() * v2.B());
  fDir.SetY(-(v1.A() * v2.C() - v1.C() * v2.A()));
  fDir.SetZ(v1.A() * v2.B() - v1.B() * v2.A());
  if ((v1.A() * v2.B() - v2.A() * v1.B()) > eps)
  {
    fSource.SetX((v2.D() * v1.B() - v1.D() * v2.B()) / ((v1.A() * v2.B() - v2.A() * v1.B())));
    fSource.SetY((v2.D() * v1.A() - v1.D() * v2.A()) / ((-v1.A() * v2.B() + v2.A() * v1.B())));
    fSource.SetZ(0);
  }
  else if ((v1.A() * v2.C() - v2.A() * v1.C()) > eps)
  {
    fSource.SetX((v2.D() * v1.C() - v1.D() * v2.C()) / ((v1.A() * v2.C() - v2.A() * v1.C())));
    fSource.SetZ((v2.D() * v1.A() - v1.D() * v2.A()) / ((-v1.A() * v2.C() + v2.A() * v1.C())));
    fSource.SetY(0);
  }
  else
  {
    fSource.SetY((v2.D() * v1.C() - v1.D() * v2.C()) / ((v1.B() * v2.C() - v2.B() * v1.C())));
    fSource.SetZ((v2.D() * v1.B() - v1.D() * v2.B()) / ((-v1.B() * v2.C() + v2.B() * v1.C())));
    fSource.SetX(0);
  }
  assert(correct());
}

tLine::tLine(tLine &P)
{
  tNamed::tNamed(P);
  fSource = P.GSource();
  fDir = P.GDir();
}

tLine::tLine(tPoint &M, tPlane &P)
{
  tNamed::tNamed();
  fSource = M;
  fDir.SetX(P.A());
  fDir.SetY(P.B());
  fDir.SetZ(P.C());
}

void tLine::setnew(double newa, double newb, double newc, double newn,
                   double newm, double newp)
{
  fSource.SetX(newa);
  fSource.SetY(newb);
  fSource.SetZ(newc);
  fDir.SetX(newn);
  fDir.SetY(newm);
  fDir.SetZ(newp);
  assert(correct());
}

int tLine::correct()
{
  if (fDir.Norm() < eps)
    return 0;
  else
    return 1;
}

double tLine::Sx()
{
  return fSource.x();
}

double tLine::Sy()
{
  return fSource.y();
}

double tLine::Sz()
{
  return fSource.z();
}

double tLine::Dx()
{
  return fDir.x();
}

double tLine::Dy()
{
  return fDir.y();
}

double tLine::Dz()
{
  return fDir.z();
}

void tLine::SetSx(double t)
{
  fSource.SetX(t);
}

void tLine::SetSy(double t)
{
  fSource.SetY(t);
}

void tLine::SetSz(double t)
{
  fSource.SetZ(t);
}

void tLine::SetDx(double t)
{
  fDir.SetX(t);
  assert(correct());
}
void tLine::SetDy(double t)
{
  fDir.SetY(t);
  assert(correct());
}

void tLine::SetDz(double t)
{
  fDir.SetZ(t);
  assert(correct());
}

tVector &tLine::GDir()
{
  return fDir;
}

tPoint &tLine::GSource()
{
  return fSource;
}

void tLine::SetSource(tPoint &M)
{

  fSource = M;
}

void tLine::SetDir(tVector &P)
{
  assert((P.Norm() > eps));
  fDir = P;
}

double tLine::DistToPoint(tPoint &M)
{
  tVector v;
  tVector t(M, fSource);
  double d;
  v = t * fDir;
  d = v.Norm() / fDir.Norm();
  return d;
}

int tLine::HasPoint(tPoint &M)
{
  if (DistToPoint(M) < eps)
    return 1;
  else
    return 0;
}

int tLine::LinePar(tLine &L)
{
  int f = 0;
  tVector v = fDir * L.fDir;
  if ((v.x() < eps) && (v.y() < eps) && (v.z() < eps))
    f = 1;
  return f;
}

tLine &tLine::operator=(tLine &P)
{
  fSource = P.GSource();
  fDir = P.GDir();
  return *this;
}

int operator==(tLine &L1, tLine &L2)
{
  if ((L1.LinePar(L2)) && (L1.HasPoint(L2.GSource())))
    return 1;
  else
    return 0;
}

ostream &operator<<(ostream &output, tLine &P)
{
  output << "Line: (x- (" << P.GSource().x() << ") )/(" << P.GDir().x() << ") = (y-(" << P.GSource().y() << ") )/(" << P.GDir().y() << ") = (z-(" << P.GSource().z() << ") )/(" << P.GDir().z() << ")" << endl;
  return output;
}

istream &operator>>(istream &input, tLine &P)
{
  tPoint t;
  tVector v;
  cout << "Enter line(source & dir): \n";
  cin >> t;
  P.SetSource(t);
  cin >> v;
  P.SetDir(v);
  assert(P.correct());
}