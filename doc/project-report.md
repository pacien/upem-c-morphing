---
title: "BSc IN S5 / Advanced C programming / Morphing"
author: [Pacien TRAN-GIRARD, Adam NAILI]
date: 2017-12-28
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

---

# Compilation and usage

## Building the project

The different parts of the project can be built using the make targets listed in `topics/Build.txt`.

Compilation of the program requires gcc (>=6.3), libc (>=2.24) and libMLV (=2.0.2).

Natural Docs (=1.51) and Pandoc are needed to generate the HTML API documentation and the project PDF report
respectively.

The whole build process has been tested and is known to work on Debian 9.

## Running the program

The executable binary file resulting from the compilation of the project accepts two arguments: the base and the target
images. Accepted file formats are ICO, CUR, BMP, PNM, XPM, LBM, PCX, GIF, JPEG, PNG, TGA, TIFF, and XV.

The graphical interface of the application let the user define constraint points on the two images, as well as define
parameters such as the number of desired frames and visualise the morphing animation.

The program has been tested on Debian 9. Known bugs in the MLV library may prevent it from running correctly on other
Linux distributions and operating systems.

---

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

The application has been broken down into several sub-modules, each of which responsible for a well defined and
semantically related set of tasks, with little or no coupling between each of those parts.

Following an object-oriented-like paradigm, APIs of said modules are centered around struct data type.
Furthermore, the number of exposed functions has been kept minimal to ensure the containment of the implementations.

### Common

### Morpher

### Painter

### GUI

## Additional features

---

# References

1. [MLV Library reference manual](http://www-igm.univ-mlv.fr/~boussica/mlv/api/French/html/index.html), A. Boussicault and M. Zipstein, September 2015
1. [Natural Docs 1.x reference manual](https://web.archive.org/web/20170504223714/http://www.naturaldocs.org:80/documenting/reference.html), Greg Valure, May 2017 
1. [Barycentric coordinate system](https://en.wikipedia.org/w/index.php?title=Barycentric_coordinate_system&oldid=816475141), Wikipedia contributors, December 2017
1. [Delaunay triangulation](https://en.wikipedia.org/w/index.php?title=Delaunay_triangulation&oldid=817290072), Wikipedia contributors, December 2017
1. [Computer Color is Broken](https://www.youtube.com/watch?v=LKnqECcg6Gw), Minute Physics, March 2015
1. [Software Rasterization Algorithms for Filling Triangles](http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html), Sunshine, May 2012
