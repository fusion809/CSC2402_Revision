# Written in May 2021 by Brenton Horne
import matplotlib.pyplot as plt
import pandas as pd
import scipy.interpolate as sci

# Import data from CSV file
def importData(str):
    # File names
    EulStr = str + "_Euler.csv"
    MEulStr = str + "_ModEuler.csv"
    RK4Str = str + "_RK4.csv"
    RKF45Str = str + "_RKF45.csv"
    tolStr = str + "_tolerance.txt"

    # Data frames    
    dfEul = pd.read_csv(EulStr)
    dfMEul = pd.read_csv(MEulStr)
    dfRK4 = pd.read_csv(RK4Str)
    dfRKF45 = pd.read_csv(RKF45Str)
    with open(tolStr, 'r') as file:
        tol = file.read().replace('\n', '')

    # Step number
    N = len(dfEul.t) - 1

    return N, tol, dfEul, dfMEul, dfRK4, dfRKF45

def spline(x0, y0, xp):
    tck = sci.splrep(x0, y0)
    yp = sci.splev(xp, tck)

    return yp