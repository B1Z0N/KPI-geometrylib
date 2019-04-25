#include "geometry.hpp"

void NormAngle(double &phi)
{
    phi -= ceil(phi / (2 * Pi)) * 2 * Pi;
}

tNamed::tNamed(char *NewName)
{

    char *N = NewName;

    fNameLength = 0;
    while (*N != '\0')
    {
        fNameLength++;
        N++;
    }

    fName = new char[fNameLength + 1];
    for (int j = 0; j <= fNameLength; j++)
        fName[j] = NewName[j];
}

tNamed::tNamed(const tNamed &x)
{ // copying constructor

    if ((fName = (char *)malloc((x.fNameLength + 1) * sizeof(char))) == NULL)
    {
        cerr << "No memory for " << x.fNameLength + 1 << "symbols to copy " << x.fName << "." << endl;
    }
    else
    {
        fNameLength = x.fNameLength;
        for (unsigned long j = 0; j <= fNameLength; j++)
            fName[j] = x.fName[j];
    }
}

tNamed::~tNamed()
{
    fNameLength = 0;
}

char *tNamed::Name() const
{
    return fName;
}

int tNamed::NameLength() const
{
    return fNameLength;
}

tNamed &tNamed::operator=(const tNamed &x)
{

    if (fName)
        delete fName;

    if ((fName = (char *)malloc((x.fNameLength + 1) * sizeof(char))) == NULL)
    {
        cerr << "No memory for " << x.fNameLength + 1 << "symbols to copy " << x.fName << "." << endl;
    }
    else
    {
        fNameLength = x.fNameLength;
        for (unsigned long j = 0; j <= fNameLength; j++)
            fName[j] = x.fName[j];
    }
    return *this;
}

char sign(double x)
{
    if (x >= 0)
        return '+';
    else
        return '-';
}
// TODO3: make variadic templates solution
double Deter2(double a, double b, double c, double d)
{
    return (a * d - c * b);
}

double Deter3(double a, double b, double c, double d, double e, double f, double g,
              double h, double i)
{
    return (a * Deter2(e, f, h, i) - b * Deter2(d, f, g, i) + c * Deter2(d, e, g, h));
}

double Deter4(double a, double b, double c, double d, double e,
              double f, double g, double h, double i, double j, double k,
              double l, double m, double n, double o, double p)
{
    return (a * Deter3(f, g, h, j, k, l, n, o, p) - b * Deter3(e, g, h, i, k, l, m, o, p) + c * Deter3(e, f, h, i, j, l, m, n, p) - d * Deter3(e, f, g, i, j, k, m, n, o));
}