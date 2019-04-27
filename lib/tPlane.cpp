#include "../include/geometry.hpp"


tPlane::tPlane(double newA, double newB, double newC, double newD, char const *NewName)
    : tNamed(NewName)
{
  fA = newA;
  fB = newB;
  fC = newC;
  fD = newD;
  assert(correct());
}

tPlane::tPlane(const tPlane &p)
    : tNamed(p)
{
  fA = p.A();
  fB = p.B();
  fC = p.C();
  fD = p.D();
}

tPlane::tPlane(const tPoint &P1, const tPoint &P2, const tPoint &P3)
{
  assert(!((P1 == P2) || (P2 == P3) || (P1 == P3)));
  tVector *P12 = new tVector(P1, P2),
          *P13 = new tVector(P1, P3),
          *P = new tVector;
  *P = (*P12) * (*P13);
  if (!(P->Norm() < eps))
  {
    fA = P->x();
    fB = P->y();
    fC = P->z();
    fD = -fA * P3.x() - fB * P3.y() - fC * P3.z();
    assert(correct());
  }
}

double tPlane::A() const
{
  return fA;
}

double tPlane::B() const
{
  return fB;
}

double tPlane::C() const
{
  return fC;
}

double tPlane::D() const
{
  return fD;
}

void tPlane::setA(double newA)
{
  fA = newA;
  assert(correct());
}

void tPlane::setB(double newB)
{
  fB = newB;
  assert(correct());
}

void tPlane::setC(double newC)
{
  fC = newC;
  assert(correct());
}

void tPlane::setD(double newD)
{
  fD = newD;
  assert(correct());
}

void tPlane::setnew(double newA, double newB, double newC, double newD)
{
  fA = newA;
  fB = newB;
  fC = newC;
  fD = newD;
  assert(correct());
}

bool tPlane::correct() const
{
  return !(
      (fabs(A()) < eps) &&
      (fabs(B()) < eps) &&
      (fabs(C()) < eps));
}

tPlane tPlane::Normalize() const
{
  double norm = sqrt(pow(A(), 2) + pow(B(), 2) + pow(C(), 2));
  int sign;
  tPlane t;

  if (fabs(A()) > eps)
  {
    sign = A() / fabs(A());
    t = tPlane(sign * A() / norm,
               sign * B() / norm,
               sign * C() / norm,
               sign * D() / norm);
  }
  else // A==0
      if (fabs(B()) > eps)
  {
    sign = B() / fabs(B());
    t = tPlane(0, sign * B() / norm, sign * C() / norm, sign * D() / norm);
  }
  else // (A==0)&&(B==0)
      if (fabs(C()) > eps)
  {
    sign = C() / fabs(C());
    t = tPlane(0, 0, sign * C() / norm, sign * D() / norm);
  }
  else // (A==0)&&(B==0)&&(C==0) - impossible for correct plane!
    assert(0);

  return t;
}

void tPlane::Normalize()
{
  const tPlane t{*this};
  tPlane(t.Normalize());
}
double tPlane::DistToPoint(const tPoint &p) const
{
  tPlane P(*this);
  P.Normalize();
  return fabs(P.A() * p.x() + P.B() * p.y() + P.C() * p.z() + P.D());
}
bool tPlane::HasPoint(const tPoint &p) const
{
  return (DistToPoint(p) < eps);
}

tPlane &tPlane::operator=(const tPlane &p)
{
  this->tNamed::operator=(p);

  this->fA = p.A();
  this->fB = p.B();
  this->fC = p.C();
  this->fD = p.D();

  return *this;
}

bool operator==(const tPlane &pl1, const tPlane &pl2)
{
  tPlane p = pl1.Normalize();
  tPlane q = pl2.Normalize();
  return (fabs(p.A() - q.A()) < eps) &&
         (fabs(p.B() - q.B()) < eps) &&
         (fabs(p.C() - q.C()) < eps) &&
         (fabs(p.D() - q.D()) < eps);
}

ostream &operator<<(ostream &output, const tPlane &P)
{
  output << "Plane: (" << P.A() << ")*x"
         << "+(" << P.B() << ")*y"
         << "+(" << P.C() << ")*z"
         << "+(" << P.D() << ")=0 " << endl;
  return output;
}

istream &operator>>(istream &input, tPlane &P)
{
  double t;
  cout << "Enter plane :";
  cin >> t;
  P.setA(t);
  cin >> t;
  P.setB(t);
  cin >> t;
  P.setC(t);
  cin >> t;
  P.setD(t);
}

tPoint Cut3Planes(const tPlane &a, const tPlane &b, const tPlane &c)
{
  double Det, DetX, DetY, DetZ, MNorm;
  if ((a.correct()) && (b.correct()) && (c.correct()))
  {
    Det = Deter3(a.A(), a.B(), a.C(), b.A(), b.B(), b.C(),
                 c.A(), c.B(), c.C());
    MNorm = fabs(a.A()) + fabs(a.B()) + fabs(a.C()) + fabs(b.A()) + fabs(b.C()) + fabs(c.A()) + fabs(c.B()) + fabs(c.C());
    assert((fabs(Det) / MNorm) > eps);
    DetX = Deter3(a.D(), a.B(), a.C(), b.D(), b.B(), b.C(),
                  c.D(), c.B(), c.C());
    DetY = Deter3(a.A(), a.D(), a.C(), b.A(), b.D(), b.C(),
                  c.A(), c.D(), c.C());
    DetZ = Deter3(a.A(), a.B(), a.D(), b.A(), b.B(), b.D(),
                  c.A(), c.B(), c.D());
    tPoint T(-DetX / Det, -DetY / Det, -DetZ / Det);
    return T;
  }
}

tPoint ProjectPointToPlane(const tPoint &M, const tPlane &P)
{
    tLine l(M, P);
    tPoint T{LineCutPlane(l, P)};
    return T;
}
