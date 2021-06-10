# Programs written as part of CSC2402 revision
These programs were written as part of revision for USQ's CSC2402 subject. The Python scripts are just for plotting data generated by the C++ programs.

I use an executable shell script called compile located at /usr/local/bin on my system to compile and execute the C++ files in this directory. It has the contents:

```bash
#!/usr/bin/env bash
g++ -g -std=c++11 -I . $1 -o ${1/.cpp/.out} && \
        chmod +x ${1/.cpp/.out}; ./${1/.cpp/.out}
```

and is called using:

```bash
compile filename.cpp
```

for example:

```bash
compile EarthOrbit.cpp
```

.