// RungeGutta.hh

#ifndef RUNGE_GUTTA_HH
#define RUNGE_GUTTA_HH

// Interpolation function for double precision values.
void interpolate_double(double angle[], double ai, double an, double n);

// Function prototypes for the ODE right-hand side functions.
double f(double x, double y, double z);
double g(double x, double y, double z);

// Runge-Kutta 4th order integration function.
double runge_kutta_4(double x, double y, double *z, double h);

// Internal helper functions.
static inline double pow2(double x) { return x * x; }
static inline double pow3(double x) { return pow2(x) * x; }

#endif // RUNGE_GUTTA_HH
