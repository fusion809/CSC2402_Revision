#!/usr/bin/env python3
# Written in May 2021 by Brenton Horne
import matplotlib.pyplot as plt
import pandas as pd

with open('ODE_prob.txt', 'r') as file:
    prob = file.read().replace('\n', '')

# Import data from CSV file
dfEuler = pd.read_csv(r"ODE_Euler.csv")
dfModEuler = pd.read_csv(r"ODE_ModEuler.csv")
dfRK4 = pd.read_csv(r"ODE_RK4.csv")
dfAdapt = pd.read_csv(r"ODE_RKF45.csv")

# Plot Euler method solution in 3D
figEuler = plt.figure(1)
axEuler = plt.axes(projection='3d')
axEuler.plot3D(dfEuler.x, dfEuler.y, dfEuler.z)
plt.savefig("Figure_1:_Euler_solution_to_{}.svg".format(prob))

# Plot Modified Euler method solution in 3D
figModEuler = plt.figure(2)
axModEuler = plt.axes(projection='3d')
axModEuler.plot3D(dfModEuler.x, dfModEuler.y, dfModEuler.z)
plt.savefig("Figure_2:_Modified_Euler_solution_to_{}.svg".format(prob))

# Plot Runge-Kutta fourth-order method solution in 3D
figRK4 = plt.figure(3)
axRK4 = plt.axes(projection='3d')
axRK4.plot3D(dfRK4.x, dfRK4.y, dfRK4.z)
plt.savefig("Figure_3:_RK4_solution_to_{}.svg".format(prob))

# Plot x values from three different methods against each other to get
# some feeling for errors in the various methods
plt.figure(4)
plt.plot(dfEuler.t, dfEuler.x, label='x (Euler)')
plt.plot(dfModEuler.t, dfModEuler.x, label='x (Modified Euler)')
plt.plot(dfRK4.t, dfRK4.x, label='x (RK4)')
plt.plot(dfAdapt.t, dfAdapt.x, label="x (RKF45)")
plt.legend()
plt.savefig("Figure_4:_x_value_approximations_{}.svg".format(prob))

# Plot RKF45 solution
figRKF45 = plt.figure(5)
axRKF45 = plt.axes(projection='3d')
axRKF45.plot3D(dfAdapt.x, dfAdapt.y, dfAdapt.z)
plt.savefig("Figure_5:_RKF45_solution_to_{}.svg".format(prob))
# plt.show()