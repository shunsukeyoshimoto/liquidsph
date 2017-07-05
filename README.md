SPH method: Compressible Viscous Liquid
====

Overview

This porject is for learning how to implement Smoothed-particle hydrodynamics (SPH) for liquid simulation in C language. Let's fill in the code at TODO.

## Text
[See here](https://github.com/yoshimoto56/liquidsph/blob/master/text/SPH_text_en.pdf)

## Demo
[![Liquid SPH](https://img.youtube.com/vi/Qe9LbExZ1tc/0.jpg)](https://www.youtube.com/watch?v=Qe9LbExZ1tc "Liquid SPH")

Command Key - when main window is active

    q:quit

    r:Start simulation

    i:Reset paticle position

    s:Save simulation result

    n:Stop saving

## Requirement

- LIB: math, glut, OpenGL, OpenMP
- SPH Parameter Data PATH: ../data/param.ini
- SPH Initial Particle Data PATH: ../data/bunny.stl
- SPH Container Data PATH: ../data/container.stl
- Export Data PATH: ../data/dst

## Compile command

    $ gcc main.c SPH.c Mesh.c GLTool.c MathTool.c -fopenmp -lglut -lGL -lGLU -lm -o sph

    $ ./sph ../data/bunny.stl

## Licence

[MIT](https://github.com/tcnksm/tool/blob/master/LICENCE)

## Author

[yoshimoto56](https://github.com/yoshimoto56)
