<h1>

<p align="center">
    <img src="/images/data-structures-icon.svg"
         alt="Data Structures icon"
         align="center" height="80" height="80">
    <br>Data Structures
</p>

</h1>

<p align="center">Data Structures in C</p>

This repository provides educational implementations of three basic data
structures in the C programming language:

1) Vector (dynamic array),
3) A hash map, 
2) and a set.

### Purpose

The primary purpose is to serve as a learning resource for those interested in
understanding how these fundamental data structures can be implemented in a
low-level language like C.

### Repo Structure

Each data structure is implemented in a separate header file with an associated
`#define` directive to include the implementation in a source file. These data
structures are deliberately simplified for clarity and educational value. The
implementations are accompanied by assert statements for basic error checking
to facilitate debugging and learning.

For detailed usage, refer to the comments at the beginning of each header file.
These comments provide an overview of the data structure, instructions for how
to integrate it into a project, and example code.

### Vector (Dynamic Array)

The [`vec.h`](/vec.h) file contains a minimal implementation of a dynamic
array, also known as a vector. It allows for the storage and manipulation of an
array of integers with the ability to dynamically resize itself.

### Set

The [`set.h`](/set.h) file provides a basic set implementation using an
internal dynamic array to store unique elements. This data structure offers
operations such as creation, destruction, addition, and membership checking.

### Contributing

While this repository is primarily for education, contributions for
improvements or additional educational material are welcome. Please feel free
to fork the repository, make changes, and submit a pull request.

### License

This package is provided under BSD-2-Clause license. See [LICENSE](/LICENSE)
file for details.
