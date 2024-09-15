// ------------------------------------------------------------------------------
// Brainfuck
// ------------------------------------------------------------------------------
// Implementation:
//		@itsYakub: https://github.com/itsYakub
// Based on the original implementation:
// 		Author: Urban Müller
// 		Source: http://aminet.net/dev/lang/brainfuck-2.lha
// ------------------------------------------------------------------------------
// Sources:
// - http://aminet.net/search?query=brainfuck
// - https://gist.github.com/rdebath/0ca09ec0fdcf3f82478f
// - https://en.wikipedia.org/wiki/Brainfuck
// ------------------------------------------------------------------------------
// LICENCE:
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
// ------------------------------------------------------------------------------

/* SECTION: Includes */

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

/* SECTION: Macro definitions */
#ifndef global
	#define global static
#endif

/* SECTION: Global variables */
global int 	program_pointer = 0;
global int	program_loop = 0;
global char program_stack[30000] = { 0 };

/* SECTION: Function declarations */
static int 		ft_file_open(const char* path);
static int		ft_file_len(int fd);
static char* 	ft_file_parse(int fd);
static int 		ft_interpreter(char* str);

int main(int argc, const char* argv[]) {
	char* 	fbuf;
	int 	fd = 0;

	if(argc != 2) {
		errno = EINVAL;
		fprintf(stderr, "[ ERR ]: %s\n", strerror(errno));

		return 1;
	}

	if(!(fd = ft_file_open(argv[1]))) {
		fprintf(stderr, "[ ERR ]: %s\n", strerror(errno));

		return 1;
	}

	fbuf = ft_file_parse(fd);
	ft_interpreter(fbuf);

	free(fbuf);
	close(fd);

	return 0;
}

/* SECTION: Function definitions */

static int 		ft_file_open(const char* path) {
	int res = open(path, O_RDONLY);
	return res;
}

static int		ft_file_len(int fd) {
	int res = 0;
	char c;
	while(read(fd, &c, 1) > 0) {
		res++;
	}
	lseek(fd, 0, SEEK_SET);
	return res;
}

static char* 	ft_file_parse(int fd) {
	int 	len = ft_file_len(fd);
	char* 	res = (char*) malloc(len * sizeof(char));
	if(!res)
		return NULL;

	if(!read(fd, res, len)) {
		fprintf(stderr, "[ ERR ]: %s\n", strerror(errno));

		free(res);
		return NULL;
	}

	return res;
}

static int 		ft_interpreter(char* str) {
	if(!str)
		return 0;

	while(*str) {
		switch (*str++) {
			/* Arithmetic operations */
			case '+': { program_stack[program_pointer]++; } break;
			case '-': { program_stack[program_pointer]--; } break;

			/* Standard input and output */
			case '.': { putchar(program_stack[program_pointer]); 	fflush(stdout); } break;
			case ',': { *str = getchar(); 							fflush(stdout); } break;

			/* Stack manipulation */
			case '<': { program_pointer--; } break;
			case '>': { program_pointer++; } break;

			/* Loops */
			case '[': {
				// Firstly, let's create a variable scpy,
				// which is the pointer to the initial string position.
				// We'll pass it to the argument of a recursive call to ft_interpreter,
				// which will start at the beginning of the loop and process it,
				// until the value of the current pointer is equal to, or less than 0.
				char* scpy = str;

				// Secondly, we set the value of a program_loop int/boolean to 1, which means that
				// we are inside the loop. We'll increment it when we find nested loop inside the main loop,
				// or decrement it if we go away from the nested, or the main loop itself.
				program_loop = 1;
				while (program_loop && *str) {
					program_loop += *str == '[', program_loop -= *str == ']';
					str++;
					// Don't forget to increment the str pointer, because when we finish the loop
					// we'll process the rest of the code after the loop.
				}

				if(!program_loop) {
					str[-1] = 0;
					while(program_stack[program_pointer]) {
						ft_interpreter(scpy);
					}
					str[-1] = ']';
					break;
				}
		 	}
			case  ']': { printf("[ ERR ]: Unbalanced bracket\n"); return 1; }
			default: { } break;
		}

		if(program_pointer < 0) 			program_pointer = 29999;
		else if(program_pointer >= 30000) 	program_pointer = 0;
	}

	return 1;
}
