# README
This is a demonstration of simulation of Langevin dynamics based on Verlet algorithm. It was designed for Tiwary's research group at University of Maryland since 2017, in order to study the dynamics and exploration of stochastic movement in configuration space. 

The algorithm is based on the verlet algorithm proposed in the paper "Accurate sampling using Langevin dynamics", Giovanni Bussi and Michele Parrinello, Phys. Rev. E 75, 056707 (2007).

To add one more dimension in z-direction:

(1) Add f[2] in force.cpp. 

(2) All f_x, f_y, and f_z in force.cpp need to have three arguments: qq1->x[0], qq1->x[1], qq1->x[2]

(3) Add new definitions of fx, fy, and fz (with three double-type inputs) in field.hpp

(4) Modify f_x and f_y settings in field.cpp. Add settings for f_z in field.cpp

(5) In insript.txt, dimension=3. Add one more number for gamma along z-dimension.

(6) Specify initial z positions and z velocities in configuration file.

(6) Specify initial z positions and z velocities in configuration file.


# How to use

(1) sh compile.sh produce executable file mdt.out

(2) ./mdt.out to perform simulation.

(tested on mac os)
