#include "geometry.hpp"

tVector::tVector() : tPoint() {}

tVector::tVector(double newx, double newy, double newz, char const *NewName /*  ="" */)
    : tPoint(newx, newy, newz, NewName) {}

tVector::tVector(const tVector &p)
    : tPoint(p) {}

tVector::tVector(const tPoint &P1, const tPoint &P2)
    : tPoint(P2.x() - P1.x(), P2.y() - P1.y(), P2.z() - P1.z())
{
    if (P1 == P2)
        throw SinglePointError{};
}

double operator,(const tVector &A, const tVector &B)
{
    double u;
    u = A.x() * B.x() + A.y() * B.y() + A.z() * B.z();
    return u;
}

double tVector::Norm() const
{
    return sqrt(x() * x() + y() * y() + z() * z());
}

tVector tVector::Normalize() const
{
    double N = Norm();
    tVector t;
    if (N > eps)
    {
        t.SetX(x() / N);
        t.SetY(y() / N);
        t.SetZ(z() / N);
    }

    return t;
}

void tVector::Normalize()
{
    const tVector cthis = *this;
    tVector(cthis.Normalize());
}

tVector &tVector::operator=(const tVector &p)
{
    this->tPoint::operator=(p);

    return *this;
}

int operator==(const tVector &p, const tVector &q)
{
    return static_cast<tPoint>(p) == static_cast<tPoint>(q);
}

tVector &tVector::operator*=(double t)
{
    SetX(x() * t);
    SetY(y() * t);
    SetZ(z() * t);
    return *this;
}

tVector &operator*(const tVector &v, double t)
{
    tVector *r = new tVector(v);
    *r *= t;
    return *r;
}

tVector &operator*(double t, const tVector &v)
{
    tVector *r = new tVector(v);
    *r *= t;
    return *r;
}

tVector &operator+(const tVector &v1, const tVector &v2)
{
    tVector *r = new tVector();
    r->SetX(v1.x() + v2.x());
    r->SetY(v1.y() + v2.y());
    r->SetZ(v1.z() + v2.z());
    return *r;
}

tVector &operator-(const tVector &v1, const tVector &v2)
{
    tVector *r = new tVector();
    r->SetX(v1.x() - v2.x());
    r->SetY(v1.y() - v2.y());
    r->SetZ(v1.z() - v2.z());
    return *r;
}
tVector &tVector::operator+=(const tVector &P)
{
    SetX(x() + P.x());
    SetY(y() + P.y());
    SetZ(z() + P.z());
    return *this;
}

tVector &tVector::operator-=(const tVector &P)
{
    SetX(x() - P.x());
    SetY(y() - P.y());
    SetZ(z() - P.z());
    return *this;
}

tVector &tVector::operator*=(const tVector &P)
{
    tVector N = (*this) * P;
    SetX(N.x());
    SetY(N.y());
    SetZ(N.z());
    return *this;
}

tVector &operator*(const tVector &v1, const tVector &v2)
{
    tVector *r = new tVector();
    r->SetX(v1.y() * v2.z() - v2.y() * v1.z());
    r->SetY(v1.z() * v2.x() - v2.z() * v1.x());
    r->SetZ(v1.x() * v2.y() - v2.x() * v1.y());
    return *r;
}

ostream &operator<<(ostream &output, const tVector &P)
{
    output << "Vector: X: " << P.x() << " Y: " << P.y() << " Z: " << P.z() << endl;
    return output;
}

istream &operator>>(istream &input, tVector &P)
{
    double t;
    cout << "Enter a vector: ";
    cin >> t;
    P.SetX(t);
    cin >> t;
    P.SetY(t);
    cin >> t;
    P.SetZ(t);
}