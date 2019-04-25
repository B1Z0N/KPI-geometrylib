#include "geometry.hpp"

tPoint::tPoint(double newx, double newy, double newz, char const *NewName)
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