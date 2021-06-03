#!/usr/bin/env python3
# Written in May 2021 by Brenton Horne
import plotTools as ptls
import matplotlib.pyplot as plt

def interp(dfEul, dfMEul, dfRK4, dfRKF45):
    t = dfRKF45.t
    uEul = ptls.spline(dfEul.t, dfEul.u, t)
    duEul = ptls.spline(dfEul.t, dfEul.du, t)
    uMEul = ptls.spline(dfMEul.t, dfMEul.u, t)
    duMEul = ptls.spline(dfMEul.t, dfMEul.du, t)
    uRK4 = ptls.spline(dfRK4.t, dfRK4.u, t)
    duRK4 = ptls.spline(dfRK4.t, dfRK4.du, t)

    return t, uEul, duEul, uMEul, duMEul, uRK4, duRK4

def main():
    with open('ODE_prob.txt', 'r') as file:
        prob = file.read().replace('\n', '')

    # Import data from CSV file
    N, tol, dfEul, dfMEul, dfRK4, dfRKF45 = ptls.importData("ODE")
    
    # Interpolate to get solutions on the same grid (RKF45's grid)
    t, uEul, duEul, uMEul, duMEul, uRK4, duRK4 = interp(dfEul, dfMEul, dfRK4, dfRKF45)

    # Plot Euler method solution
    plt.figure(1)
    plt.plot(t, uEul, label="u")
    plt.plot(t, duEul, label="$\\frac{du}{dt}$")
    plt.title("Euler solution to {} (N={})".format(prob, N))
    plt.legend()
    plt.savefig("{}/Figure_1:_Euler_solution_to_{}.png".format(prob, prob))

    # Plot Modified Euler method solution
    plt.figure(2)
    plt.plot(t, uMEul, label="u")
    plt.plot(t, duMEul, label="$\\frac{du}{dt}$")
    plt.title("Modified Euler solution to {} (N={})".format(prob, N))
    plt.legend()
    plt.savefig("{}/Figure_2:_Modified_Euler_solution_to_{}.png".format(prob,
    prob))

    # Plot Runge-Kutta fourth-order method solution
    plt.figure(3)
    plt.plot(t, uRK4, label="u")
    plt.plot(t, duRK4, label="$\\frac{du}{dt}$")
    plt.title("Runge-Kutta fourth order solution to {} (N={})".format(prob, N))
    plt.legend()
    plt.savefig("{}/Figure_3:_RK4_solution_to_{}.png".format(prob,
    prob))

    # Plot RKF45 solution
    plt.figure(4)
    plt.plot(t, dfRKF45.u, label="u")
    plt.plot(t, dfRKF45.du, label="$\\frac{du}{dt}$")
    plt.legend()
    plt.title("RKF45 solution to {} (tol={})".format(prob, tol))
    plt.savefig("{}/Figure_4:_RKF45_solution_to_{}.png".format(prob, prob))

    # Plot u values from three different methods against each other to get
    # some feeling for errors in the various methods
    plt.figure(5)
    plt.plot(t, uEul, label='u (Euler)')
    plt.plot(t, uMEul, label='u (Modified Euler)')
    plt.plot(t, uRK4, label='u (RK4)')
    plt.plot(t, dfRKF45.u, label="u (RKF45)")
    plt.legend()
    plt.title("Comparison of u solutions to {} from four different numerical schemes \n(N={}, tol={})".format(prob, N, tol))
    plt.savefig("{}/Figure_5:_u_value_approximations_{}.png".format(prob, 
    prob))

    # Phase plot du against u
    plt.figure(6)
    plt.plot(uEul, duEul, label="Euler")
    plt.plot(uMEul, duMEul, label="Modified Euler")
    plt.plot(uRK4, duRK4, label="Runge-Kutta 4th order")
    plt.plot(dfRKF45.u, dfRKF45.du, label="Runge-Kutta-Fehlberg 4(5)th order")
    plt.legend()
    plt.title("Comparison of u solutions to {} from four different numerical schemes \n(N={}, tol={})".format(prob, N, tol))
    plt.savefig("{}/Figure_6:_du_value_approximations_{}.png".format(prob, prob))

if __name__ == "__main__":
    main()