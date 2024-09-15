# Brainfuck

## Introduction
*"Brainfuck is an esoteric programming language created in 1993 by Swiss student Urban Müller"*.
This is the official description of Brainfuck on [Wikipedia](https://en.wikipedia.org/wiki/Brainfuck).
I've decided to implement my own interpreter for this language just for the sake of learning and creating stuff.

## Gettng started:
### Rules:
Brainfuck consists of some simple to remember, but hard to master rules that we need to follow when writing programs in this language:
- Everything is based on a *n-size array of characters*, which acts as our *stack*;
- We have a pointer/cursor (however you want to call it) which we use to move on the stack;
- Everything is made our of 8 characters. Every other character from ASCII is treated as comment;

### Commands:
| **Command** 	| **Descrition** | **Equivalent** |
|-|-|-|
|	**+**			| **Increment** the current value 									| `stack[pointer]++` 						|
| **-**			| **Decrement** the current value 									| `stack[pointer]--` 						|
| **<**			| Move the pointer to the **left**									| `pointer++`										|
| **>**			| Move the pointer to the **right** 								| `pointer--`										|
| **[**			| **Beginning** of the loop													| `while(stack[pointer]) {` 		|
| **]**			| **End** of the loop																| `}`														|
| **.**			| **Print** the current value to stdout 						| `putchar(stack[pointer]);`		|
| **,**			| Set the current value to the **input** from stdin | `stack[pointer] = getchar();` |

## Setup:
- Clone this repo:
```console
$ git@github.com:itsYakub/Brainfuck.git
$ cd Brainfuck
```
- Create a build directory:
```console
$ mkdir bin
$ cd bin
```
- Use [CMake]() to build the interpreter:
```console
$ cmake ..
$ cmake --build .
```
- Run the interpreter with the file you want to run:
```console
$ ./brainfuck {path/to/file}.bf
```

## Credits:
- http://aminet.net/search?query=brainfuck
- https://gist.github.com/rdebath/0ca09ec0fdcf3f82478f
- https://en.wikipedia.org/wiki/Brainfuck

## Licence
This repository is under the [MIT Licence](./LICENCE).
