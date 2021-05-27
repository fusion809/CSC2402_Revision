#!/usr/bin/env python3
# Written in May 2021 by Brenton Horne
import plotTools as ptls
import matplotlib.pyplot as plt

def interp(dfEul, dfMEul, dfRK4, dfRKF45):
    t = dfRKF45.t
    xEul = ptls.spline(dfEul.t, dfEul.x, t)
    yEul = ptls.spline(dfEul.t, dfEul.y, t)
    zEul = ptls.spline(dfEul.t, dfEul.z, t)
    xMEul = ptls.spline(dfMEul.t, dfMEul.x, t)
    yMEul = ptls.spline(dfMEul.t, dfMEul.y, t)
    zMEul = ptls.spline(dfMEul.t, dfMEul.z, t)
    xRK4 = ptls.spline(dfRK4.t, dfRK4.x, t)
    yRK4 = ptls.spline(dfRK4.t, dfRK4.y, t)
    zRK4 = ptls.spline(dfRK4.t, dfRK4.z, t)

    return t, xEul, yEul, zEul, xMEul, yMEul, zMEul, xRK4, yRK4, zRK4

def main():
    with open('ODE_prob.txt', 'r') as file:
        prob = file.read().replace('\n', '')

    # Import data from CSV file
    N, tol, dfEul, dfMEul, dfRK4, dfRKF45 = ptls.importData("ODE")
    
    # Interpolate to get solutions on the same grid (RKF45's grid)
    t, xEul, yEul, zEul, xMEul, yMEul, zMEul, xRK4, yRK4, zRK4 = interp(dfEul, dfMEul, dfRK4, dfRKF45)

    # Plot Euler method solution in 3D
    plt.figure(1)
    axEuler = plt.axes(projection='3d')
    axEuler.plot3D(xEul, yEul, zEul)
    plt.title("Euler solution to {} (N={})".format(prob, N))
    plt.savefig("{}/Figure_1:_Euler_solution_to_{}.svg".format(prob, prob))

    # Plot Modified Euler method solution in 3D
    plt.figure(2)
    axModEuler = plt.axes(projection='3d')
    axModEuler.plot3D(xMEul, yMEul, zMEul)
    plt.title("Modified Euler solution to {} (N={})".format(prob, N))
    plt.savefig("{}/Figure_2:_Modified_Euler_solution_to_{}.svg".format(prob,
    prob))

    # Plot Runge-Kutta fourth-order method solution in 3D
    plt.figure(3)
    axRK4 = plt.axes(projection='3d')
    axRK4.plot3D(xRK4, yRK4, zRK4)
    plt.title("RK4 solution to {} (N={})".format(prob, N))
    plt.savefig("{}/Figure_3:_RK4_solution_to_{}.svg".format(prob, prob))

    # Plot x values from three different methods against each other to get
    # some feeling for errors in the various methods
    plt.figure(4)
    plt.plot(t, xEul, label='x (Euler)')
    plt.plot(t, xMEul, label='x (Modified Euler)')
    plt.plot(t, xRK4, label='x (RK4)')
    plt.plot(t, dfRKF45.x, label="x (RKF45)")
    plt.legend()
    plt.title("Comparison of x solutions to {} from four different numerical schemes \n(N={}, tol={})".format(prob, N, tol))
    plt.savefig("{}/Figure_4:_x_value_approximations_{}.svg".format(prob, 
    prob))

    # Plot RKF45 solution
    plt.figure(5)
    axRKF45 = plt.axes(projection='3d')
    axRKF45.plot3D(dfRKF45.x, dfRKF45.y, dfRKF45.z)
    plt.title("RKF45 solution to {} (tol={})".format(prob, tol))
    plt.savefig("{}/Figure_5:_RKF45_solution_to_{}.svg".format(prob, prob))
    # plt.show()

if __name__ == "__main__":
    main()