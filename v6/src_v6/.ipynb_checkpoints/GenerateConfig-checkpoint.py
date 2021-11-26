#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar  1 15:59:41 2018

@author: lina492375qw1188
"""

import numpy as np
import matplotlib.pyplot as plt

# Read file:
f = open('./inscript.txt','r')
data = []
for line in f:
    data.append([cell for cell in line.split()])

f.close()

# Read lines:
for line in data:
    # Environment:
    if line[0] == 'num_particle':
        num_particle = int(line[1])
    # Verlet:
    elif line[0] == 'beta':
        beta = float(line[1])
    # Lennard-Jones:
    elif line[0] == 'LJ':
        epsilon = float(line[1])
        sigma = float(line[2])
    # Shifted Gauss:
    elif line[0] == 'Shifted' and line[1] == 'Gaussian':
        A0 = 0.3
        A = float(line[2])
        x0 = float(line[3])
        width = float(line[4])
    # Double Well:
    elif line[0] == 'Double' and line[1] == 'Well':
        B = float(line[2])
        a = float(line[3])
        

# Real potential:
def LJ_p(r, epsilon, sigma):
    return 4*epsilon*((sigma/r)**12-(sigma/r)**6)

def SGauss_p(x, A, x0, width):
    return A*np.exp(-(x-x0)**2/(2*width**2))

def DoubleWell(x, B, a):
    return B*(x**2-a)**2

def potential(x, y, epsilon, sigma, A, x0, width, B, a):
    return (LJ_p(x, epsilon, sigma) + SGauss_p(x, A0, 1.75, 0.2) # Pure x part
                                    + SGauss_p(x, A, x0, width)*(y+1) # Perturbation
                                    + B*(y**2-a)**2) # Pure y part

# Creating Probability:
Nsample_x = 200
Nsample_y = 1000
label = np.arange(0,Nsample_x*Nsample_y)
x_sample = np.linspace(0.001, 1.7, Nsample_x)
y_sample = np.linspace(-30, 30, Nsample_y)

coord = [(xi, yi) for xi in x_sample for yi in y_sample]

prob_c = (np.array([np.exp(-beta*potential(row[0], row[1], epsilon, sigma, A, x0, width, B, a)) 
           for row in coord]))
prob_c = prob_c/sum(prob_c)

# Sampling:
l = np.random.choice(label, num_particle, p=prob_c)
c = [coord[li] for li in l]

x = [row[0] for row in c]
y = [row[1] for row in c]
v = [np.sqrt(np.random.exponential(2/beta)) for i in range(num_particle)]
w = [np.sqrt(np.random.exponential(2/beta)) for i in range(num_particle)]

# File output:
m = 0
filename = ('config_beta'+str(beta)+
            'epsln'+str(epsilon)+'sgma'+str(sigma)+
            'A'+str(A)+'x0'+str(x0)+'w'+str(width)+
            'B'+str(B)+'a'+str(a)+'.txt')
with open(filename, "w") as f:
    while m < num_particle:
        f.write(str(x[m])+" "+str(y[m])+" "+str(v[m])+" "+str(w[m])+"\n")
        m += 1
f.close()

# Plot distribution:
plt.scatter(x,y)
plt.show()
        
        
        
        
        
        
        
