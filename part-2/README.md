# Write to a File

Reading from a file opens up new pathways for us to write more sophisticated and insteresting programs. Writing to a file enables us to have our programs communicate with people and with other programs.

Imagine that your instructor wishes to have a mechanisim to remind students about deadlines. Your instructor could write a file with the name of the assignment and the date it's due, one entry per line. Then a program can look at who has turned in their work and who hasn't and generate a file with all the students who forgot to submit their assignment. Another program could use that list to send a message on Canvas. Writing files helps us track and connect pieces of information.

In this exercise, we prompt the computer user to enter a secret message from the keyboard. Our program shall take that message (as a `string`) and write it into a file.

Last time we used [`ifstream`](https://en.cppreference.com/w/cpp/io/basic_ifstream) to create an input file stream. This time we shall use [`ofstream`](https://en.cppreference.com/w/cpp/io/basic_ofstream) to create an output file stream. The `ofstream` object is defined in the same `fstream` header file as `ifstream`.

Where as reading from a file implies that the file must exist first in order for it to be read from, writing to a file does not have this requirement. If the file doesn't exist, then we will create a new file. However, if the file already exists, we have to be careful.

For our purposes, we'll just truncate (delete) the file. This is the path of least resistance yet it is a dangerous path becuase you could accidentally delete an important file. Be careful and remember to use git prudently to track your work.

To declare an `ofstream`, it is just like declaring an `ifstream`. Writing to an `ofstream` is like writing to `cout` (because `cout` is an `ofstream`).

```c++
ofstream output_file_stream("my_output_file.txt");
output_file_stream << "Hello World\n";
output_file_stream.close();
```

The code above will create an `ofstream` variable named `output_file_stream`. The variable `output_file_stream` is intialized to open the file `"my_output_file.txt"`. If the file doesn't exist, it will be created. If it already exists then it will be deleted and recreated (truncated). Using the insertion operator `<<` write the strings `"Hello World\n"` to the `output_file_stream`. Finally, we close the `output_file_stream` because we are done working with it.

The other challenge of this exercise is reading a whole line of text from the keyboard into a variable. If you think about it, so far we've never worked with a whole line. We always limited ourselves to just a word or a number. Reading in a line of text is a little different and we'll use the function (not the method) [`getline()`](https://en.cppreference.com/w/cpp/string/basic_string/getline).

The function [`getline()`](https://en.cppreference.com/w/cpp/string/basic_string/getline) is part of the `string` header file and it can be used to read a line of text from any input stream.

Let's imagine we want to prompt someone to enter their favorite movie title. Then we would first print a message to the terminal using `cout`, declare a `string` variable to store the movie title, and then use `getline()` to copy the data from the terminal's keyboard to the `string` variable.

```c++
  cout << "What's your favorite movie? ";
  string their_favorite_movie;
  getline(cin, their_favorite_movie, '\n');
```

In the last line, `getline()` shall read the values from `cin` up to but not including the `\n` letter and save the input into the `string` variable `their_favorite_movie`.

## Requirements

Using `ofstream`, write a message to a file that is specified on the command line. Read the message the computer user wishes to save by line using the `getline()` function.

If there are any errors, print an error message and exit.

Using the inline documentation, implement the following functions.

* `void ErrorMessage(const string&message);`

The program takes one command line arguments other than the program's name:

1. `argv[1]` is the path to the input file

Do not use the method (member function) `getline()`. Use the function [`getline()`](https://en.cppreference.com/w/cpp/string/basic_string/getline) which is part of the `string` header.

Close any file streams that you open and report any errors encountered.

To compile your program, you use the `make` command. A Makefile is provided for this exercise.

The Makefile has the following targets:
  
* all: builds the project
* clean: removes object and dependency files
* spotless: removes everything the clean target removes and all binaries
* doc: generate HTML documentation from the source code using Doxygen
* format: outputs a [`diff`](https://en.wikipedia.org/wiki/Diff) showing where your formatting differes from the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html)
* tidy: output of the [linter](https://en.wikipedia.org/wiki/Lint_(software)) to give you tips on how to improve your code
* headercheck: check to make sure your files have the appropriate header

## Inline Documentation
The project is thoroughly documented inline using the [Doxygen](https://en.wikipedia.org/wiki/Doxygen) format. The documentation establishes a framework for you to follow so that you can implement all the details of the program. To generate HTML formatted documents to view on your computer use the make target `doc`. For example:

```
$ ls
Doxyfile	Makefile	README.md	find_min.cc
$ make doc
set -e; clang++ -MM -g -Wall -pipe -std=c++14  find_min.cc \
	| sed 's/\(find_min\)\.o[ :]*/\1.o find_min.d : /g' > find_min.d; \
	[ -s find_min.d ] || rm -f find_min.d
doxygen Doxyfile
$ ls
Doxyfile	README.md	find_min.cc
Makefile	doc/		find_min.d
```

The inline documentation is saved in `doc/html`. To view the documentation, use the command `gio open doc/html/index.html` which will open the index file in your web browser.

If the `doxygen` command is not available, for instance when you use `make doc` the output looks like:

```
$ make doc
set -e; clang++ -MM -g -Wall -pipe -std=c++14  find_min.cc \
	| sed 's/\(find_min\)\.o[ :]*/\1.o find_min.d : /g' > find_min.d; \
	[ -s find_min.d ] || rm -f find_min.d
doxygen Doxyfile
make: doxygen: No such file or directory
make: *** [doc] Error 1
```

Then you can install `doxygen` using the command `sudo apt install doxygen doxygen-latex graphviz`.

## Don't Forget

Please remember that:

- You need to put a header in every file.
- You need to follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
- Remove the `TODO` comments.

## Testing Your Code

Computers only ever do exactly what they are told, exactly the way they are told it, and never anything else. Testing is an important process to writing a program. You need to test for the program to behave correctly and test that the program behaves incorrectly in a predictable way.

As programmers we have to remember that there are a lot of ways that we can write the wrong program and only one to a few ways to write the correct program. We have to be aware of [cognitive biases](https://en.wikipedia.org/wiki/List_of_cognitive_biases) that we may exercise that lead us to believe we have correctly completed our program. That belief may be incorrect and our software may have errors. [Errors in software](https://www.wired.com/2005/11/historys-worst-software-bugs/) may lead to loss of [life](https://www.nytimes.com/2019/03/14/business/boeing-737-software-update.html), [property](https://en.wikipedia.org/wiki/Mariner_1), [reputation](https://en.wikipedia.org/wiki/Pentium_FDIV_bug), or [all of the above](https://en.wikipedia.org/wiki/2009%E2%80%9311_Toyota_vehicle_recalls).

### Test strategy

Start simple, and work your way up. Good tests are specific, cover a broad range of fundamentally different possibilities, can identify issues quickly, easily, and directly, without need for much set up, and can almost be diagnosed by inspection if the code fails to execute the test correctly.

## Example Output

Please ensure your program's output is identical to the example below.

```
$ make
set -e; clang++ -MM -g -Wall -pipe -std=c++14  write_to_file.cc \
	| sed 's/\(write_to_file\)\.o[ :]*/\1.o write_to_file.d : /g' > write_to_file.d; \
	[ -s write_to_file.d ] || rm -f write_to_file.d
clang++ -g -Wall -pipe -std=c++14  -c write_to_file.cc
clang++ -g -Wall -pipe -std=c++14 -o write_to_file write_to_file.o 
$ ./write_to_file 
Please provide a path to a file.
There was an error. Exiting.
$ ./write_to_file my_darkest_secret.txt
What's a secret message that you'd like to write into a file?
Type your message out and when you're done press return or enter.
I don't like chocolate ice cream.
Your secret message was saved into my_darkest_secret.txt!
$ ls
Doxyfile		my_darkest_secret.txt	write_to_file.d
Makefile		write_to_file*		write_to_file.o
README.md		write_to_file.cc
$ ./write_to_file another_secret.txt
What's a secret message that you'd like to write into a file?
Type your message out and when you're done press return or enter.
I've only time traveled twice and I didn't like it.
Your secret message was saved into another_secret.txt!
$ ls
Doxyfile		another_secret.txt	write_to_file.cc
Makefile		my_darkest_secret.txt	write_to_file.d
README.md		write_to_file*		write_to_file.o
```

