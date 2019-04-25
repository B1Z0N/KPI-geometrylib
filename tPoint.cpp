#include "geometry.hpp"

tPoint::tPoint(double newx, double newy, double newz, char *NewName)
    : tNamed(NewName)
{
    fx = newx;
    fy = newy;
    fz = newz;
}

tPoint::tPoint(const tPoint &p)
    : tNamed(p)
{ // copying constructor
    fx = p.x();
    fy = p.y();
    fz = p.z();
}

tPoint Cut3Planes(tPlane &a, tPlane &b, tPlane &c)
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

tPoint LineCutPlane(tLine l, tPlane p)
{
    double t, z;
    z = p.A() * l.Dx() + p.B() * l.Dy() + p.C() * l.Dz();
    assert(z > eps);
    t = (-p.D() - p.A() * l.Sx() - p.B() * l.Sy() - p.C() * l.Sz()) / z;
    tPoint T(l.Dx() * t + l.Sx(), l.Dy() * t + l.Sy(), l.Dz() * t + l.Sz());
    return T;
}

tPoint ProjectPointToPlane(tPoint &M, tPlane &P)
{
    tLine l(M, P);
    tPoint T{LineCutPlane(l, P)};
    return T;
}

double tPoint::x() const
{
    return fx;
}

double tPoint::y() const
{
    return fy;
}

double tPoint::z() const
{
    return fz;
}

void tPoint::SetX(double t)
{
    fx = t;
}

void tPoint::SetY(double t)
{
    fy = t;
}

void tPoint::SetZ(double t)
{
    fz = t;
}

double tPoint::DistTo(const tPoint &P) const
{
    return sqrt(pow(fx - P.x(), 2) +
                pow(fy - P.y(), 2) +
                pow(fz - P.z(), 2));
}

void tPoint::Move(const tPoint &P)
{
    fx = fx + P.x();
    fy = fy + P.y();
    fz = fz + P.z();
}

void tPoint::TurnXPoint(double phi)
{
    if ((phi < -Pi) || (phi > Pi))
        NormAngle(phi);

    fx = fx;
    double yNew = fy * cos(phi) - fz * sin(phi);
    fz = fy * sin(phi) + fz * cos(phi);
    fy = yNew;
}

void tPoint::TurnYPoint(double phi)
{
    if ((phi < -Pi) || (phi > Pi))
        NormAngle(phi);

    fy = fy;
    double xNew = fx * cos(phi) + fz * sin(phi);
    fz = -fx * sin(phi) + fz * cos(phi);
    fx = xNew;
}

void tPoint::TurnZPoint(double phi)
{
    if ((phi < -Pi) || (phi > Pi))
        NormAngle(phi);

    fz = fz;
    double xNew = fx * cos(phi) - fy * sin(phi);
    fy = fx * sin(phi) + fy * cos(phi);
    fx = xNew;
}

tPoint &tPoint::operator=(const tPoint &p)
{
    this->tNamed::operator=(p);

    this->fx = p.x();
    this->fy = p.y();
    this->fz = p.z();

    return *this;
}

int operator==(const tPoint &p, const tPoint &q)
{
    double dx = p.x() - q.x(),
           dy = p.y() - q.y(),
           dz = p.z() - q.z(),
           r = -1;
    r =
        (fabs(dx) < eps) &&
        (fabs(dy) < eps) &&
        (fabs(dz) < eps);
    return r;
}

ostream &operator<<(ostream &output, const tPoint &P)
{
    output << "Point: X: " << P.x() << " Y: " << P.y() << " Z: " << P.z() << endl;
    return output;
}

istream &operator>>(istream &input, tPoint &P)
{
    double t;
    cout << "Enter a point: ";
    cin >> t;
    P.SetX(t);
    cin >> t;
    P.SetY(t);
    cin >> t;
    P.SetZ(t);
}