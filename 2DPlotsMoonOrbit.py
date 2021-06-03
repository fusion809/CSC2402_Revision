#!/usr/bin/env python3
# Written in May 2021 by Brenton Horne
import plotTools as ptls
import matplotlib.pyplot as plt
import numpy as np

def interp(dfEul, dfMEul, dfRK4, dfRKF45):
    t = dfRKF45.t
    rEul = ptls.spline(dfEul.t, dfEul.r, t)
    drEul = ptls.spline(dfEul.t, dfEul.dr, t)
    thetEul = ptls.spline(dfEul.t, dfEul.theta, t)
    rMEul = ptls.spline(dfMEul.t, dfMEul.r, t)
    drMEul = ptls.spline(dfMEul.t, dfMEul.dr, t)
    thetMEul = ptls.spline(dfMEul.t, dfMEul.theta, t)
    rRK4 = ptls.spline(dfRK4.t, dfRK4.r, t)
    drRK4 = ptls.spline(dfRK4.t, dfRK4.dr, t)
    thetRK4 = ptls.spline(dfRK4.t, dfRK4.theta, t)

    return t, rEul, drEul, thetEul, rMEul, drMEul, thetMEul, rRK4, drRK4, thetRK4

def main():
    with open('ODE_prob.txt', 'r') as file:
        prob = file.read().replace('\n', '')

    # Import data from CSV file
    N, tol, dfEul, dfMEul, dfRK4, dfRKF45 = ptls.importData("ODE")
    
    # Interpolate to get solutions on the same grid (RKF45's grid)
    t, rEul, drEul, thetEul, rMEul, drMEul, thetMEul, rRK4, drRK4, thetRK4 = interp(dfEul, dfMEul, dfRK4, dfRKF45)

    # x and y coordinates computed from r and theta values obtained using
    # the four numerical schemes. 
    xEul = rEul*np.cos(thetEul)
    yEul = rEul*np.sin(thetEul)
    xMEul = rMEul*np.cos(thetMEul)
    yMEul = rMEul*np.sin(thetMEul)
    xRK4 = rRK4*np.cos(thetRK4)
    yRK4 = rRK4*np.sin(thetRK4)
    xRKF45 = dfRKF45.r*np.cos(dfRKF45.theta)
    yRKF45 = dfRKF45.r*np.sin(dfRKF45.theta)

    # Plot y against x for the four methods
    plt.figure(1)
    plt.plot(xEul, yEul, label="Euler")
    plt.plot(xMEul, yMEul, label="Modified Euler")
    plt.plot(xRK4, yRK4, label="Runge-Kutta 4th order")
    plt.plot(xRKF45, yRKF45, label="Runge-Kutta-Fehlberg 4(5)th order")
    plt.legend()
    plt.xlabel("$x$ (metres)")
    plt.ylabel("$y$ (metres)")
    plt.title("2D trajectory of the moon")
    plt.savefig("{}/Figure_1:_y_value_approximations_against_x_{}.png".format(prob, prob))

    # Plot r values from four different methods against each other to get
    # some feeling for errors in the various methods
    plt.figure(2)
    plt.plot(t, rEul, label='Euler')
    plt.plot(t, rMEul, label='Modified Euler')
    plt.plot(t, rRK4, label='Runge-Kutta 4th order')
    plt.plot(t, dfRKF45.r, label="Runge-Kutta-Fehlberg 4(5)th order")
    plt.legend()
    plt.xlabel("$t$ (seconds)")
    plt.ylabel("$r$ (metres)")
    plt.title("Comparison of r solutions to {} from four different numerical schemes \n(N={}, tol={})".format(prob, N, tol))
    plt.savefig("{}/Figure_2:_r_value_approximations_{}.png".format(prob, 
    prob))

    # Plot dr values from the four different methods
    plt.figure(3)
    plt.plot(t, drEul, label='Euler')
    plt.plot(t, drMEul, label='Modified Euler')
    plt.plot(t, drRK4, label='Runge-Kutta 4th order')
    plt.plot(t, dfRKF45.dr, label="Runge-Kutta-Fehlberg 4(5)th order")
    plt.legend()
    plt.xlabel("$t$ (seconds)")
    plt.ylabel("$\\frac{dr}{dt}$ (metres per second)")
    plt.title("Comparison of dr/dt solutions to {} from four different numerical schemes \n(N={}, tol={})".format(prob, N, tol))
    plt.savefig("{}/Figure_3:_dr_value_approximations_{}.png".format(prob, 
    prob))

    # Plot theta values from the four different methods
    plt.figure(4)
    plt.plot(t, thetEul, label='Euler')
    plt.plot(t, thetMEul, label='Modified Euler')
    plt.plot(t, thetRK4, label='Runge-Kutta 4th order')
    plt.plot(t, dfRKF45.theta, label="Runge-Kutta-Fehlberg 4(5)th order")
    plt.legend()
    plt.xlabel("$t$ (seconds)")
    plt.ylabel("$\\theta$ (radians)")
    plt.title("Comparison of $\\theta$ solutions to {} from four different numerical schemes \n(N={}, tol={})".format(prob, N, tol))
    plt.savefig("{}/Figure_4:_theta_value_approximations_{}.png".format(prob, 
    prob))

    # Phase plot dr against r
    plt.figure(5)
    plt.plot(rEul, drEul, label="Euler")
    plt.plot(rMEul, drMEul, label="Modified Euler")
    plt.plot(rRK4, drRK4, label="Runge-Kutta 4th order")
    plt.plot(dfRKF45.r, dfRKF45.dr, label="Runge-Kutta-Fehlberg 4(5)th order")
    plt.xlabel("$r$ (metres)")
    plt.ylabel("$\\frac{dr}{dt}$ (metres per second)")
    plt.legend()
    plt.title("Phase plots of dr/dt against r for various numerical schemes \n(N={}, tol={})".format(prob, N, tol))
    plt.savefig("{}/Figure_5:_dr_value_approximations_{}.png".format(prob, prob))

if __name__ == "__main__":
    main()