# 3 Boyutlu Goruntu Dosyaları Project

**Table of Content:**

1. [What Is This Project](#what-is-this-project)
1. [What Lineer Algebra Calculations Can It Do](#what-lineer-algebra-calculations-can-it-do)

## What Is This Project

This C project reads through given .nkt files and does [a few lineer algebra calculations](#what-lineer-algebra-calculations-can-it-do). The .nkt files can contain 3d point coordinates and 3d point coordinates with RGB infos. And these coordinates can also be coded in binary. The program will reader the files header and warns the user if any point in the list has some errors (for example: an RGB point missing one of its color values).

## What Lineer Algebra Calculations Can It Do

1.  Two Closest/Furthest Points:\
    This function finds two closest and furthest points and return their values.

2.  Cube:\
    This function returns the edge point values of the smallest cube that contains all the points in the point list.

3.  Sphere:\
    This function takes the center coordinates and radius of a sphere and returns the list of points that's within this given sphere.

4.  Mean of Distance:\
    This function returns the mean of all the distances between points.
