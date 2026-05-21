<p align="center">
<img alt="jocoa" src="https://codeberg.org/MilkyBruv/jocoa/raw/branch/stable/res/jocoaTitle.png">

<br/>

<img alt="Static Badge" src="https://img.shields.io/badge/version-0.2.2-blue">
<img alt="Static Badge" src="https://img.shields.io/badge/license-MIT-green">
<img alt="" src="https://img.shields.io/badge/Linux-FCC624?logo=linux&logoColor=black">
<img alt="" src="https://custom-icon-badges.demolab.com/badge/Windows-0078D6?logo=windows11&logoColor=white">

</p>

<br/>

**Jocoa** is a Java project management tool for the command-line. It requires a single `jocoa.json` file to be preset to compile, execute, build, and package a Java project. This tool supports dependencies, natives, testing, runnable projects, and library projects in a simple way to aid developers create quick, lightweight projects with very little setup needed.

Jocoa aims to fill the need of a simple, lightweight, yet reliable project management tool for Java, that requires very little adaptation for existing projects.

## Features

- Quick and easy to install.
- Very Beginner-friendly.
- Relies on one single, small JSON file.
- Lightweight and simple.
- Easily adapatable for existing projects using other project management tools.
- Releases for Windows and Linux, with only the need of G++ or Clang++ to setup, no CMake.

## Commands
- `help` - Displays information on how to use Jocoa.
- `new` - Creates new Jocoa project.
- `info` - Displays current project and system information.
- `run` - Compiles and executes current project.
    - `-no-search` - Compiles and executes without searching for new source files or dependencies.
- `build` - Compiles current project as .jar.
    - `-no-search` - Compiles without searching for new source files or dependencies.
    - `-fat` - Compiles project and all dependencies into one .jar.
- `search` - Searches for new source files or dependencies, and appends them to `jocoa.json`.
- `clean` - Cleans current project of compilation files.

## Quick Start

Visit the [installation guide](https://github.com/MilkyBruv/jocoa?tab=readme-ov-file#installation-guide), then proceed.

```
jocoa new
jocoa run
```

And that's it!

## Example Project

### jocoa.json

```json
{
	"name": "BasicProject",
	"type": "runnable",
	"package": "net.User.BasicProject",
	"sourceFiles": [
		"./src/net/User/BasicProject/main/Main.java"
	],
	"dependencies": [
		
	]
}
```

### Main.java

```java
package net.User.BasicProject.main;

public class Main {

	public static void main(String[] args) {

		System.out.println("Hello World!");

	}

}
```

### File tree

```
jocoa.json

bin
lib
└───natives
res
src
└───net
    └───User
        └───BasicProject
            └───main
                    Main.java
```

[Click here](https://github.com/MilkyBruv/jocoa/tree/main/examples) for examples.

## Installation Guide

Installation for both Linux and Windows is very similar, simply install G++ or Clang++, clone the repository, then compile the project with the Makefile.

### Prerequisites

#### Windows
Install G++ and/or Clang++ with [MinGW MSYS2](https://www.msys2.org/)

#### Linux
```
$ sudo apt-get install make
```

Then use either `g++` (default) or `clang++`.

```
$ sudo apt-get install g++
```
Or
```
$ sudo apt-get install clang
```

### Cloning

Clone the repository to wherever you want, `C:/jocoa` and `/home` recommended

```
> git clone https://github.com/MilkyBruv/jocoa
```
```
$ git clone https://github.com/MilkyBruv/jocoa
<<<<<<< HEAD
=======
$ cd jocoa
$ make
>>>>>>> 09a5fcc37d771cda38cf5e45ddac228f92213b35
```

Note that you can clone jocoa to wherever you want, as the build files will be sent to the default path unless specified otherwise (`C:/jocoa` for windows and `/usr/local/bin` for linux).

### Compiling for Windows

Set the `CXX` and `WIN_DEST` or leave them as the default (`CXX=g++`, `WIN_DEST=C:/jocoa`)

**For default build at** `C:/jocoa`
```
<<<<<<< HEAD
C:/jocoa> make
```

**For custom build at** `C:/your/path/jocoa`
```
C:/your/path/jocoa> make WIN_DEST="C:/your/path/jocoa"
```

**NOTE THAT YOU MUST USE EITHER** `/` **OR** `\\` **FOR** `WIN_DEST` **ELSE YOU WILL HAVE ISSUES**

Then add `C:/jocoa` or `C:/your/path/jocoa` to PATH.

### Compiling for Linux

Set the `LINUX_DEST` or leave it as the default (`/usr/local/bin`)

**For default build at** `/usr/local/bin`
```
$ make
```

**For custom build at** `/your/path/jocoa`
```
$ make LINUX_DEST="/your/path/jocoa"
```

### Compiling Notes

The Makefile has a few different arguments you can change to customize the build:
- `CXX`: C++ Compiler, e.g. `g++` (default), `clang++`)
- `SHOW_CXX_WARNINGS`: Can be turned on with `SHOW_CXX_WARNINGS=true` to show any warnings during compilation.
=======
> git clone https://github.com/MilkyBruv/jocoa
> cd jocoa
> make
>>>>>>> 09a5fcc37d771cda38cf5e45ddac228f92213b35
