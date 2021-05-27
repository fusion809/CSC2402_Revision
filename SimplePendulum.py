#!/usr/bin/env python3
# Written in May 2021 by Brenton Horne
import plotTools as ptls
import matplotlib.pyplot as plt

# Get t from dfRKF45 and interpolate all other theta and theta dot to these 
# points
def interp(dfEul, dfMEul, dfRK4, dfRKF45):
    t = dfRKF45.t
    thetaEul = ptls.spline(dfEul.t, dfEul.theta, t)
    dthetaEul = ptls.spline(dfEul.t, dfEul.thetaDot, t)
    thetaMEul = ptls.spline(dfMEul.t, dfMEul.theta, t)
    dthetaMEul = ptls.spline(dfMEul.t, dfMEul.thetaDot, t)
    thetaRK4 = ptls.spline(dfRK4.t, dfRK4.theta, t)
    dthetaRK4 = ptls.spline(dfRK4.t, dfRK4.thetaDot, t)

    return t, thetaEul, dthetaEul, thetaMEul, dthetaMEul, thetaRK4, dthetaRK4

def main():
    N, tol, dfEul, dfMEul, dfRK4, dfRKF45 = ptls.importData("ODE")
    t, thetaEul, dthetaEul, thetaMEul, dthetaMEul, thetaRK4, dthetaRK4 = interp(dfEul, dfMEul, dfRK4, dfRKF45)

    # Plots
    plt.close('all')

    # Plot Eul method solution in phase space
    plt.figure(1)
    plt.plot(thetaEul, dthetaEul)
    plt.xlabel("$\\theta$")
    plt.ylabel("$\\frac{d\\theta}{dt}$")
    plt.title("Phase plot for interpolated Euler solution (N={})".format(N))
    plt.savefig("SimplePendulum/Figure_1:_Euler_solution_to_simple_pendulum.png")

    # Plot Modified Eul method solution in phase space
    plt.figure(2)
    plt.plot(thetaMEul, dthetaMEul)
    plt.xlabel("$\\theta$")
    plt.ylabel("$\\frac{d\\theta}{dt}$")
    plt.title("Phase plot for interpolated Modified Euler solution (N={})".format(N))
    plt.savefig("SimplePendulum/Figure_2:_Modified_Euler_solution_to_simple_pendulum.png")

    # Plot Runge-Kutta fourth-order method solution in phase space
    plt.figure(3)
    plt.plot(thetaRK4, dthetaRK4)
    plt.xlabel("$\\theta$")
    plt.ylabel("$\\frac{d\\theta}{dt}$")
    plt.title("Phase plot for interpolated RK4 solution (N={})".format(N))
    plt.savefig("SimplePendulum/Figure_3:_RK4_solution_to_simple_pendulum.png")

    # Phase plot RKF45 solution
    plt.figure(4)
    plt.plot(dfRKF45.theta, dfRKF45.thetaDot)
    plt.xlabel("$\\theta$")
    plt.ylabel("$\\frac{d\\theta}{dt}$")
    plt.title("Phase plot for RKF45 solution (tol={})".format(tol))
    plt.savefig("SimplePendulum/Figure_4:_RKF45_solution_to_simple_pendulum.png")

    # Plot theta values from three different methods against each other to get
    # some feeling for errors in the various methods
    plt.figure(5)
    plt.plot(t, thetaEul, label='$\\theta$ (Euler)')
    plt.plot(t, thetaMEul, label='$\\theta$ (Modified Euler)')
    plt.plot(t, thetaRK4, label='$\\theta$ (RK4)')
    plt.plot(t, dfRKF45.theta, label="$\\theta$ (RKF45)")
    plt.legend()
    plt.title("$\\theta$ approximations obtained using four different numerical schemes (N={}, tol={})".format(N, tol))
    plt.savefig("SimplePendulum/Figure_5:_theta_values_obtained_with_four_different_numerical_schemes.png")

    # Compare theta dot for the four different methods
    plt.figure(6)
    plt.plot(t, dthetaEul, label='$\\dot{\\theta}$ (Euler)')
    plt.plot(t, dthetaMEul, label="$\\dot{\\theta}$ (Modified Euler)")
    plt.plot(t, dthetaRK4, label="$\\dot{\\theta}$ (RK4)")
    plt.plot(t, dfRKF45.thetaDot, label="$\\dot{\\theta}$ (RKF45)")
    plt.legend()
    plt.title("$\\theta$ dot approximations obtained using four different numerical schemes (N={}, tol={})".format(N, tol))
    plt.savefig("SimplePendulum/Figure_6:_theta_dot_values_comparison.png")

if __name__ == "__main__":
    main()