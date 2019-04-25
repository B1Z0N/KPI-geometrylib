#include "geometry.hpp"

tLine::tLine(double newa, double newb, double newc,
             double newn, double newm, double newp, char *NewName) : tNamed(NewName), fSource(newa, newb, newc), fDir(newn, newm, newp)
{
  assert(correct());
}

tLine::tLine(const tPoint& S, const tVector& D, char *NewName) : tNamed(NewName), fSource(S), fDir(D)
{
  assert(correct());
}

tLine::tLine(const tPlane& v1, const tPlane& v2, char *NewName)
  :tNamed(NewName)
{
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

tLine::tLine(const tLine& P)
  :tNamed(P)
{
  fSource = P.GSource();
  fDir = P.GDir();
}

tLine::tLine(const tPoint &M, const tPlane &P)
  :tNamed()
{
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

int tLine::correct() const
{
  if (fDir.Norm() < eps)
    return 0;
  else
    return 1;
}

double tLine::Sx() const
{
  return fSource.x();
}

double tLine::Sy() const
{
  return fSource.y();
}

double tLine::Sz() const
{
  return fSource.z();
}

double tLine::Dx() const
{
  return fDir.x();
}

double tLine::Dy() const
{
  return fDir.y();
}

double tLine::Dz() const
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

tVector tLine::GDir() const
{
  return fDir;
}

tPoint tLine::GSource() const
{
  return fSource;
}

void tLine::SetSource(const tPoint &M)
{

  fSource = M;
}

void tLine::SetDir(const tVector &P)
{
  assert((P.Norm() > eps));
  fDir = P;
}

double tLine::DistToPoint(const tPoint &M) const
{
  tVector v;
  tVector t(M, fSource);
  double d;
  v = t * fDir;
  d = v.Norm() / fDir.Norm();
  return d;
}

int tLine::HasPoint(const tPoint &M) const
{
  if (DistToPoint(M) < eps)
    return 1;
  else
    return 0;
}

int tLine::LinePar(const tLine &L) const
{
  int f = 0;
  tVector v = fDir * L.fDir;
  if ((v.x() < eps) && (v.y() < eps) && (v.z() < eps))
    f = 1;
  return f;
}

tLine &tLine::operator=(const tLine &P)
{
  fSource = P.GSource();
  fDir = P.GDir();
  return *this;
}

int operator==(const tLine &L1, const tLine &L2)
{
  if ((L1.LinePar(L2)) && (L1.HasPoint(L2.GSource())))
    return 1;
  else
    return 0;
}

ostream &operator<<(ostream &output, const tLine &P)
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

tPoint LineCutPlane(const tLine& l, const tPlane& p)
{
    double t, z;
    z = p.A() * l.Dx() + p.B() * l.Dy() + p.C() * l.Dz();
    assert(z > eps);
    t = (-p.D() - p.A() * l.Sx() - p.B() * l.Sy() - p.C() * l.Sz()) / z;
    tPoint T(l.Dx() * t + l.Sx(), l.Dy() * t + l.Sy(), l.Dz() * t + l.Sz());
    return T;
}

tPoint ProjectPointToPlane(const tPoint &M, const tPlane &P)
{
    tLine l(M, P);
    tPoint T{LineCutPlane(l, P)};
    return T;
}