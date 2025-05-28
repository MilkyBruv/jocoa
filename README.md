<p align="center">
  <img src="https://github.com/MilkyBruv/jocoa/blob/main/res/jocoaTitle.png"/>
</p>

<br/>

<p align="center">
<img alt="Static Badge" src="https://img.shields.io/badge/version-0.2.1-blue">
<img alt="Static Badge" src="https://img.shields.io/badge/license-MIT-green">
<img alt="" src="https://img.shields.io/badge/Linux-FCC624?logo=linux&logoColor=black">
<img alt="" src="https://custom-icon-badges.demolab.com/badge/Windows-0078D6?logo=windows11&logoColor=white">

</p>

<br/>

**Jocoa** is a Java project management tool for the command-line. It requires a single `jocoa.json` file to be preset to compile, execute, build, and package a Java project. This tool supports dependencies, natives, testing, runnable projects, and library projects in a simple way to aid developers create quick, lightweight projects with very little setup needed.

Jocoa aims to fill the need of a simple, lightweight, yet reliable project management tool for Java, that requires very little adaptation for existing projects.

## Features

- Quick and easy to install
- Beginner-friendly and easy to use
- Relies on one single, small JSON file
- Lightweight and simple
- Easily adapatable for existing projects using other project management tools
- Releases for Windows and Linux, with only the need of G++ or Clang++ to setup, no CMake.

## Commands
- `help` - Displays information on how to use Jocoa
- `new` - Creates new Jocoa project
- `info` - Displays current project and system information
- `run` - Compiles and executes current project
    - `-no-search` - Compiles and executes without searching for new source files or dependencies
- `build` - Compiles current project as .jar
    - `-no-search` - Compiles without searching for new source files or dependencies
    - `-fat` - Compiles project and all dependencies into one .jar
- `search` - Searches for new source files or dependencies, and appends them to `jocoa.json`
- `clean` - Cleans current project of compilation files

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

Installation for both Linux and Windows is very similar, simply install G++ or Clang++, clone the repository, then compile the project with the Makefile

### Linux

#### Prerequisites
```
$ sudo apt-get install g++
```
Or
```
$ sudo apt-get install clang
```

Cloning and compiling
```
$ git clone https://github.com/MilkyBruv/jocoa
cd jocoa
```
For G++
```
$ make glinux
```
Or for Clang++
```
$ make clinux
```

### Windows

#### Prerequisites

Install G++ and/or Clang++ with [MinGW MSYS2](https://www.msys2.org/)

```
> git clone https://github.com/MilkyBruv/jocoa
cd jocoa
```
For G++
```
$ make gwin
```
Or for Clang++
```
$ make cwin
```
