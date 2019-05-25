# SINGLE_MD
<<<<<<< HEAD
This is a demonstration of the molecular dynamics simulation of single/noninteracting particle based on Verlet algorithm, in which more than one noninteracting particle is possible. It was designed for Tiwary's group at University of Maryland since 2017, in order to study the dynamics and exploration of stochastic movement in configuration space.
=======
This is a demonstration of the molecular dynamics simulation of single/noninteracting particle based on Verlet algorithm, in which more than one noninteracting particle is possible. It was designed for Tiwary's group at University of Maryland since 2017, in order to study the dynamics and exploration of stochastic movement in configuration space. 
>>>>>>> 29419bc932406edc53827bfd23ed5ff0a7b3b8ef

The algorithm is based on the verlet algorithm proposed in the paper "Accurate sampling using Langevin dynamics", Giovanni Bussi and Michele Parrinello, Phys. Rev. E 75, 056707 (2007).

To add one more dimension in z-direction:

<<<<<<< HEAD
(1) Add f[2] in force.cpp.
=======
(1) Add f[2] in force.cpp. 
>>>>>>> 29419bc932406edc53827bfd23ed5ff0a7b3b8ef

(2) All f_x, f_y, and f_z in force.cpp need to have three arguments: qq1->x[0], qq1->x[1], qq1->x[2]

(3) Add new definitions of fx, fy, and fz (with three double-type inputs) in field.hpp

(4) Modify f_x and f_y settings in field.cpp. Add settings for f_z in field.cpp

<<<<<<< HEAD
(5) In insript.txt, dimension=3, add one more value for gamma in z-direction.
=======
(5) In insript.txt, dimension=3

(6) Specify initial z positions and z velocities in configuration file.
>>>>>>> 29419bc932406edc53827bfd23ed5ff0a7b3b8ef

(6) Specify initial z positions and z velocities in configuration file.