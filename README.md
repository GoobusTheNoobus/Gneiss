# Gneiss Programming Language

A minimal toy programming language written in C++20, containing a
compiler and a bytecode VM.

**This repository is free of LLM-written code**

## Features

* Lexical Analysis (7/7 tests passed)
* Syntactic Analysis (4/4 tests passed)

## Subdirectories

`gneic/` -- Gneiss Compiler  
`gneic/src/` -- GNC source files  
`gneic/include/` -- GNC header files  
`gneic/tests/` -- GNC test files/script

## How to use

To build, Gneiss requires C++20, CMake, and Ninja.

### Cloning:

```bash
git clone https://github.com/GoobusTheNoobus/Gneiss.git
```

### Configuring:

```bash
# Debug
cmake -G Ninja -B <folder> 

# Release
cmake -G Ninja -B <folder> 
```

Replace `<folder>` with whatever folder name you want. A good folder name
should start with `build`. For example, `build-release` or `build-debug`.

### Building:

```bash
cmake --build <folder>
```

This should build the executable `build/gneic/gneic`.