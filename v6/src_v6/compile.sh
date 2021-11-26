#!/bin/bash

g++ -std=c++0x main.cpp particle.cpp field_Triangular3s.cpp force.cpp verlet.cpp integrate.cpp file.cpp input.cpp mdsea.cpp output.cpp -o mdt.out