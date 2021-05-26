#!/usr/bin/env python3
# Written in May 2021 by Brenton Horne
import matplotlib.pyplot as plt
import pandas as pd

# Import data from CSV file
dfEuler = pd.read_csv(r"Example3_Euler.csv")
dfModEuler = pd.read_csv(r"Example3_ModEuler.csv")
dfRK4 = pd.read_csv(r"Example3_RK4.csv")
dfAdapt = pd.read_csv(r"Example3_RKF45.csv")

# Plot Euler method solution in phase space
plt.figure(1)
plt.plot(dfEuler.theta, dfEuler.thetaDot)
plt.savefig("Figure_1:_Euler_solution_to_simple_pendulum.svg")

# Plot Modified Euler method solution in phase space
plt.figure(2)
plt.plot(dfModEuler.theta, dfModEuler.thetaDot)
plt.savefig("Figure_2:_Modified_Euler_solution_to_simple_pendulum.svg")

# Plot Runge-Kutta fourth-order method solution in phase space
plt.figure(3)
plt.plot(dfRK4.theta, dfRK4.thetaDot)
plt.savefig("Figure_3:_RK4_solution_to_simple_pendulum.svg")

# Plot theta values from three different methods against each other to get
# some feeling for errors in the various methods
plt.figure(4)
plt.plot(dfEuler.t, dfEuler.theta, label='x (Euler)')
plt.plot(dfModEuler.t, dfModEuler.theta, label='x (Modified Euler)')
plt.plot(dfRK4.t, dfRK4.theta, label='x (RK4)')
plt.plot(dfAdapt.t, dfAdapt.theta, label="x (RKF45)")
plt.legend()
plt.savefig("Figure_4:_theta_values_obtained_with_four_different_numerical_schemes.svg")

# Plot RKF45 solution
plt.figure(5)
plt.plot(dfAdapt.theta, dfAdapt.thetaDot)
plt.savefig("Figure_5:_RKF45_solution_to_simple_pendulum.svg")