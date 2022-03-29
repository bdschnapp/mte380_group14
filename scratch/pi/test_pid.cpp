#include <iostream>
#include <vector>
#include "../../pid.hpp"
#include <fstream>

/* Xr is a unit step input that starts at t = 1 */
void populate_xr(std::vector<float> &xr);

/* This uses the discretization of the transfer function 1/(s+1) to compute the new value */
float transfer_function(const float Ts, const float Tc, const float prev_u, const float prev_y);

int main()
{
    /* Ts is the time discretization and Tc is the time constant */
    constexpr float Ts = 0.01, Tc = 1;
    constexpr auto SAMPLES = 1000;

    /*
     * xr is reference trajectory which is a unit step that starts after 1 sec
     * e is the error (ie. xr - y)
     * u is the output of the controller
     * y is the output
     */
    std::vector<float> xr(SAMPLES), e(SAMPLES, 0.0f), u(SAMPLES, 0.0f), y(SAMPLES, 0.0f);

    populate_xr(xr);

    /* These are terrible gains but they're good for showing that the PID controller with anti-windup works */
    constexpr float Kp = 3, Ki = 30, min_sat = 0, max_sat = 2;

    controllers::PID controller(Kp, Ki, min_sat, max_sat);

    for (uint16_t i = 1; i < SAMPLES; i++)
    {
        e[i] = xr[i] - y[i - 1];
        u[i] = controller.compute(e[i], Ts);
        y[i] = transfer_function(Ts, Tc, u[i - 1], y[i - 1]);
    }

    std::ofstream fout("test_pid.txt");
    for (uint16_t i = 0; i < SAMPLES; i++)
    {
        fout << xr[i] << " " << e[i] << " " << u[i] << " " << y[i] << " " << std::endl;
    }
}

void populate_xr(std::vector<float> &xr)
{
    for (uint16_t i = 0; i < xr.size(); ++i)
    {
        xr[i] = i < 100 ? 0 : 1;
    }
}

float transfer_function(const float Ts, const float Tc, const float prev_u, const float prev_y)
{
    return (1.0f / (Ts + Tc)) * (Ts * prev_u + Tc * prev_y);
}