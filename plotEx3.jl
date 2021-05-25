# using Pkg;
# Pkg.add("CSV");
# Pkg.add("DataFrames");
using CSV;
using DataFrames;

data = CSV.read("Example3.csv", DataFrame);

using PyPlot;
pygui(true);
PyPlot.figure(1)
PyPlot.plot3D(data.xEuler, data.yEuler, data.zEuler);

PyPlot.figure(2)
PyPlot.plot3D(data.xModEuler, data.yModEuler, data.zModEuler);

