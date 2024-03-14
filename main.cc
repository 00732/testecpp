#include <iomanip>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include "RungeKutta.hh"
#include "physical_constants.hh"

const int NumSolarMass = 3;
const int NumPoints = 1000;
const int J = 2;
const double G = GRAVITATIONAL_CONSTANT;
const double c = SPEED_OF_LIGHT;
const double SolarMass = SOLAR_MASS;

double f(double x, double y, double z)
{
    return z;  // differential equation: dy/dx=f(x,y,z)
}

double g(double x, double y, double z)
{
    double rS = (2.0 * G * NumSolarMass * SolarMass) / (c * c);
    double kappa = (3.0 / 2.0) * rS;
    return( kappa * (y * y) - y );  // differential equation: dz/dx=g(x,y,z)
}

double calculate_period(double r)
{
    double rS = (2.0 * G * NumSolarMass * SolarMass) / (c * c);
    return 2.0 * M_PI * sqrt(r * r * r / (6.0 * G * NumSolarMass * SolarMass));
}

void runge_kutta_4(double x0, double y0, double z0, double h, double *y, double *z)
{
    double k1, k2, k3, k4;
    k1 = h * f(x0, y0, z0);
    k2 = h * f(x0 + h / 2.0, y0 + k1 / 2.0, z0 + h * (*z) / 2.0);
    k3 = h * f(x0 + h / 2.0, y0 + k2 / 2.0, z0 + h * (*z) / 2.0);
    k4 = h * f(x0 + h, y0 + k3, z0 + h * (*z));
    *y += (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
    *z += (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <radius>" << endl;
        return 1;
    }

    double r_phi0[3] = {1.499, 1.500, 1.501};
    double k[3] = {1.5, 1.0, 1.1};
    string fig[3] = {"fig01-si", "fig02-si", "fig03-si"};

    double radius = stod(argv[1]);
    double period = calculate_period(radius);

    double phi0 = 0.0;
    double rS = (2.0 * G * NumSolarMass * SolarMass) / (c * c);
    double var0 = 1.0 / (r_phi0[J] * rS);

    double *phi_range = new double[NumPoints];
    interpolate_double(phi_range, phi0, (2.0 * M_PI * period / NumPoints), NumPoints);

    double z0, xmax, h;
    double xn, yn, *zn;

    z0 = 0;
    xmax = NumPoints;
    h = phi_range[1] - phi_range[0];

    string strtmp = fig[J] + ".dat";
    ofstream fp(strtmp);

    if (!fp.is_open()) {
       
