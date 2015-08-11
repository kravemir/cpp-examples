# libglobals

Simple example about runtime linkage possibilities. Example shows that you can link variables almost the same way you can link functions.

You can use it to share constants/tables between libraries and application, ie. vtable in C++.

## Task
1. Create shared library *libglobals* which will provide globals to applications, also it will provide function that prints and edits globals.
2. Create program *useglobals*, which uses library, modifies globals and calls function from library.

##Usage
Simply compile and run:

    make run

