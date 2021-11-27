# simulating-Langevin-dynamics
This is a Langevin dynamics simulation designed for Tiwary's research group at University of Maryland since 2017, in order to study the dynamics and exploration of stochastic movement in configuration space. 

The algorithm is based on the verlet algorithm proposed in the paper "Accurate sampling using Langevin dynamics", Giovanni Bussi and Michele Parrinello, Phys. Rev. E 75, 056707 (2007).

# The most up-to-date version
`./v6/`

# How to use
```
(1) sh compile.sh produce executable file mdt.out

(2) ./mdt.out to perform simulation.

(tested on mac os)
```

# More dimensions
It is possible to add more dimension while not supported and implemented in this version. To add one more dimension in z-direction at least the following steps need to be done.
```
(1) Add f[2] in force.cpp. 

(2) All f_x, f_y, and f_z in force.cpp need to have three arguments: qq1->x[0], qq1->x[1], qq1->x[2]

(3) Add new definitions of fx, fy, and fz (with three double-type inputs) in field.hpp

(4) Modify f_x and f_y settings in field.cpp. Add settings for f_z in field.cpp

(5) In insript.txt, dimension=3. Add one more number for gamma along z-dimension.

(6) Specify initial z positions and z velocities in configuration file.

(6) Specify initial z positions and z velocities in configuration file.
```

# Theory
This theory is a detail explanation of integration which combines the author's understanding and the orginal work published by Giovanni Bussi and Michele Parrinello, Phys. Rev. E 75, 056707 (2007).
[Theory.pdf](/Theory.pdf)

<img src="https://user-images.githubusercontent.com/22850008/143543063-1fe100ce-7523-496d-8949-e4bb5ee9e420.png" width="400">
