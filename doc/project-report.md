---
title: "BSc IN S5 / Advanced C programming / Morphing"
author: [Pacien TRAN-GIRARD, Adam NAILI]
date: 2018-01-09
...

# Project description

The goal of this project is to develop a graphical application capable of generating morphing animations given two
images and constraint parameters.

Being part of the "Advanced C programming" course at [UPEM](http://www.u-pem.fr/), this application has been entirely
written in C and makes use of the C standard library and the university's graphical application wrapper library. 

## Licensing

This work is licensed under the terms of the
[Creative Commons BY-NC-SA 4.0 license](https://creativecommons.org/licenses/by-nc-sa/4.0/) by its authors:
Pacien TRAN-GIRARD and Adam NAILI.

Build-time and run-time dependencies of this program are licensed under their own respective terms.

## Credits

This report has been generated using the [Eisvogel template](https://github.com/Wandmalfarbe/pandoc-latex-template),
licensed under the BSD 3-Clause License.

\newpage

# Compilation and usage

## Building the project

The different parts of the project can be built using the make targets listed in `topics/Build.txt`.

Compilation of the program requires gcc (>=6.3), libc (>=2.24) and libMLV (=2.0.2).

Natural Docs (=1.51) and Pandoc are needed to generate the HTML API documentation and the project PDF report
respectively.

The whole build process has been tested and is known to work on Debian 9.

## Running the program

The executable binary file resulting from the compilation of the project accepts two arguments: the base and the target
images. Accepted file formats are ICO, CUR, BMP, PNM, XPM, LBM, PCX, GIF, JPEG, PNG, TGA, TIFF, and XV. Both base and
target images must have the same dimension.

The graphical interface of the application lets the user define constraint points on the two images, as well as define
parameters such as the number of desired frames and visualise the morphing animation.

The program has been tested on Debian 9 and is known to run correctly on this platform.

## Additional features

The program supports pairs of pictures of variable sizes.

## Bugs

Incorrect Delaunay triangulations may be generated with large images of 10k² pixels or more, due to possible 64-bits
integer overflows during the computation of such triangulations.

Known bugs in the MLV library may prevent the graphical user interface from working correctly on Windows and MacOS.

\newpage

# Implementation details

## Considerations

### API and documentation

Auxiliary functions have been kept module-private to avoid context pollution in the absence of namespaces.
Exported functions and data types have been prefixed and documented properly.

Natural Docs has been selected as the documentation generator for this projects for its simplicity.

Some MLV library functions have been partly wrapped to ensure the coherence with the internally defined types. 

### Unit testing

_"Sir, the testing?"_, Caroline reminds.
Almost all utility, logic and mathematical functions have been covered by automatic unit tests to reduce the risk of
small-but-yet-critical mistakes and regressions during the development. Graphical unit tests requiring human validation
have also been written in order to test the graphical user interface at the component level.

Assertions have also been used within the module implementations, enforcing pre- and post-conditions inside functions.

## Modules

The application has been broken down into several sub-modules, each of which responsible for a well-defined and
semantically related set of tasks, with little or no coupling between each of those parts.

Following an object-oriented-like paradigm, APIs of said modules are centered around struct data type.
Furthermore, the number of exposed functions has been kept minimal to ensure the containment of the implementations.

The development of the underlying logic and the graphical interface has been delegated respectively to Pacien and Adam.

\newpage

### Common

The common module contains utility functions for memory management and error handling, as well as common generic
geometric and time type definitions meant to be used by the other modules, while not being semantically tied to them.

### Morpher

The morpher module holds the type definitions and functions related to a morphing, that is an abstract set of mapping
constraints represented as a triangulation of a rectangle.

The underlying triangulation maintains the Delaunay criteria and the positive orientation of the triangle vertices in
the decreasing-y plane throughout the addition of new constraint point mappings.

A neighbourhood graph and a linked list of those subsections are also kept up to date, respectively allowing a faster
triangle lookup from arbitrarily given coordinates and a simple way of traversing all the triangles.

### Painter

The painter module provides functions to apply a previously constructed morphing to a base and a target image,
generating a morphed image as the output.

A per-triangle rasterisation algorithm has been implemented instead of the suggested per-pixel triangle lookup for
performance reasons, as the whole process was meant to run in a single thread on the CPU, not benefiting the massive
parallelisation possibility that a GPU would have offered.

The colour of each pixel resulting from the rasterisation is interpolated taking care of the compression applied to the
RBGa vectors from the two base images: each component is square-rooted back to its raw value before blending.

\newpage

### GUI

The Graphical User Interface is designed with a modular component-based architecture. That architecture implies an
Object-Oriented Programming's vision. Thanks to that, the application is very flexible for adding components and
placing them. The components created are groups, buttons, and picture frames that are all based on a common structure
called Component. Groups federate Components of any type and place them by a margin management.

Thanks to a click handler and a printing function stored inside Components, it is possible to perform the actions on 
click or to paint the component without knowing what is stored inside the group. The group is a component that handles 
clicks and is able to paint itself by using the click handler and the painter function of the Component contained inside
its list.  In other words, it delegates to the Components the action to perform. 

It also wraps some libMLV low level functions to create basic application features that can be used to create coherent 
state for the application and components. The rendering process is done by computing intermediate morphing between each 
frame combined with a time. By this implementation, the application is not using MLV_Animation.

\newpage

# References

1. [MLV Library reference manual](http://www-igm.univ-mlv.fr/~boussica/mlv/api/French/html/index.html), A. Boussicault and M. Zipstein, September 2015
1. [Natural Docs 1.x reference manual](https://web.archive.org/web/20170504223714/http://www.naturaldocs.org:80/documenting/reference.html), Greg Valure, May 2017 
1. [Barycentric coordinate system](https://en.wikipedia.org/w/index.php?title=Barycentric_coordinate_system&oldid=816475141), Wikipedia contributors, December 2017
1. [Delaunay triangulation](https://en.wikipedia.org/w/index.php?title=Delaunay_triangulation&oldid=817290072), Wikipedia contributors, December 2017
1. [Computer Color is Broken](https://www.youtube.com/watch?v=LKnqECcg6Gw), Minute Physics, March 2015
1. [Software Rasterization Algorithms for Filling Triangles](http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html), Sunshine, May 2012
