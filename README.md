# SINGLE_MD
This is a demonstration of the molecular dynamics simulation of single/noninteracting particle based on Verlet algorithm, in which more than one noninteracting particle is possible. It was designed for Tiwary's group at University of Maryland since 2017, in order to study the dynamics and exploration of stochastic movement in configuration space. 

The algorithm is based on the verlet algorithm proposed in the paper "Accurate sampling using Langevin dynamics", Giovanni Bussi and Michele Parrinello, Phys. Rev. E 75, 056707 (2007).

To add one more dimension in z-direction:
(1) Add fz in field object and force object.
(2) Specify initial z positions and z velocities in configuration file.


