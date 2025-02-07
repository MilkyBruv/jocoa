# Jocoa

## Introduction

Programming has been rapidly growing in popularity over the past decades, and more and more younger people are teaching themselves how to code. Java is a very popular language, that many people start with to begin teaching themselves. I myself use it very often, and enjoy doing so. Java needs to be compiled, so tools such as Maven, Gradle, Eclipse, and InteliJ exist to make the development and packing process easier. But due to the size and complexity of these tools, they can be very off-putting to beginners wanting a simple yet intuitive experience learning to program.

## Identification of Problem

Modern Java development tools are very overwhelming and feature-rich for beginners. Having too many features and intergrations and abilities for one program can cause a lot of confusion and frustration for people who are just starting out to code, especially for Java. Java is a very verbose and complex language to begin with, then adding on the extra pain of using such complicated tools makes the development process for beginners very slow and hard. If programmers do not want to use bloated tools such as those listed previously, then they have to resort to the standard Java command line toolset. This toolset is very tedious to get working, and requires many different OS-specific commands to be specifically and perfectly excecuted, even for small programs.

## Solution to Problem

To solve this issue, I created a command line tool to simplify Java projects management, compilation, and packaging. I called it "Jocoa," and it acts almost as a very simplified wrapper for the standard Java command line toolset. It uses beginner-friendly jargen to encourage and help those just starting out to easily get a grasp of how to use the language without having to worry too much about software and tools. It can create projects, manage dependencies, compile and run programs, and package projects. I wanted it to be very flexible and simple to use and adapt to existing projects, so I decided that the entire tool with be managed through a single JSON file. This greatly reduces the size of the project, allowing for only one specific file needed.

### Abilities

