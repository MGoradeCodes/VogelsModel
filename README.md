# FibonacciPattern - Vogel's Model

A mathematical visualization of natural patterns using C++ and OpenGL.

## Overview

This project explores Vogel's Model, a mathematical model used to represent the arrangement of seeds in flowers, particularly sunflowers.

The model generates points around a central origin using the Golden Angle, producing a spiral-like distribution that resembles patterns found in nature.

## Features

- Procedural generation of seed positions.
- Golden Angle-based distribution.
- Adjustable number of seeds.
- Mathematical positioning using polar coordinates.
- Real-time visualization using OpenGL.

## Mathematical Foundation

Vogel's Model uses two equations to determine the position of each seed.

**Angular position:**

$$
\theta_n = n \times 137.5^\circ
$$

**Radial distance:**

$$
r_n = c\sqrt{n}
$$

Where:
- \(n\) is the seed index.
- \(c\) is a scaling constant.
- \(137.5^\circ\) is the approximate Golden Angle.

The polar coordinates are converted into Cartesian coordinates:

$$
x_n = r_n\cos(\theta_n)
$$

$$
y_n = r_n\sin(\theta_n)
$$

Together, these equations produce the characteristic distribution of seeds.

## Technologies Used

- C++
- OpenGL
- GLFW
- GLAD
- GLM

## Project Scope

This project explores the relationship between mathematics and naturally occurring patterns.

It demonstrates:
- Polar and Cartesian coordinate systems.
- The Golden Angle.
- Square roots and radial scaling.
- Procedural generation.
- Mathematical modelling through computer graphics.

## Status

Completed as an educational programming experiment.
