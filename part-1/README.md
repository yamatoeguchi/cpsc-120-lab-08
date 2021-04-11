# Read From a File

Working with data in the computer's memory is a good starting point. We've done that with a variety of different types (int, float, string) and some different containers (array, vector). The next challenge for us to over come is how to read and write from [files](https://en.wikipedia.org/wiki/Computer_file).

Reading from files is a great leap forward. Writing programs that can read from a file means that you are no longer limited to what a human can enter at the computer's console. Reading from a file means that you can make use of much more interesting data sources. The smallest and most portable computer can store Gigabytes of data. That is a lot of space to store files (and database)!

A file is just an abstraction of some information that is stored in your computer's [file system](https://en.wikipedia.org/wiki/File_system). It's an address of sorts to help you, the programmer, locate a resource that has been stored in your computer's file system.

You can think of a path to a file kind of like a [URL](https://en.wikipedia.org/wiki/URL) to a website. If you have the right path, your computer can open up the file and read it. (And if you think about it a little bit you may ask yourself if you can read from a file, then how hard can it be to read from a website?).

The first thing we need is an abstraction of what a file is. For the programmer, a file is a stream. A stream not in the sense of a flowing body of water but a sequence that streams by. More like a train which has a beginning, middle, and end. Given a stream in C++, we want to have operations to read from it and move forward and backwards.

For starters, let's focus on opening up a file and reading it line by line. (Remember a line is terminated by the '\n' letter.)

C++ has a special type called [`ifstream`](https://en.cppreference.com/w/cpp/io/basic_ifstream) which is defined in the `fstream` header file. If we have the name of a file such as `"words_that_start_with_m.txt"`, then we can open and minupulate the file with the following code:

```c++
ifstream input_file("words_that_start_with_m.txt");
```

The variable `input_file` is of type `ifstream` or input file stream. It is a C++ object which is allocated and initialized with the file path `"words_that_start_with_m.txt"`. From here, we can perform operations such as checking to see if the file was succssefully opened or read a line of text from the file.

To read from a input file stream line by line, we need to think of it as copying the line from the file on disk to a temporary buffer in RAM. In other words, we will ask the input file stream for a line (a `string`) and then assign that line to a `string` variable. Once we have it as a `string` variable we can print it to the terminal.

We can extract a line of text from a file stream using [`getline()`](https://en.cppreference.com/w/cpp/io/basic_istream/getline). Our strategy is to first declare a `string` variable, resize the string variable to hold the longest line we expect to encounter, and then use `getline()` to copy the line from the file stream into the variable. Let's assume the variable `input_file` successfully opened `"words_that_start_with_m.txt"` and the first line of the contains the line "muffins and mittens".

```c++
const int kMaxLineLength = 100;
string line_buffer;
line_buffer.resize(kMaxLineLength);
input_file.getline(&line_buffer[0], kMaxLineLength, '\n');
cout << line_buffer << "\n";
input_file.close();
```

The above passage of code will print out "muffins and mittens". If you open something, like a file, you must close it.

If `kMaxLineLength` is set to be very small, then `getline()` will generate
an error. Make sure to handle errors early and carefully to avoid any crashes and bugs.


## Requirements

Using `ifstream`, read the contents of a file that is specified on the command line and print the contents to the terminal. Read the contents of the file line by line using the `getline()` method of the `ifstream` class.

If there are any errors, print an error message and exit.

Use the files 01_words.txt, 02_words.txt, 03_words.txt, 04_words.txt to help you validate that your program works as expected. Sample output is provided below.

Using the inline documentation, implement the following functions.

* `void ErrorMessage(const string&message);`

The program takes one command line arguments other than the program's name:

1. `argv[1]` is the path to the input file

Do not use the function `getline()`, use the member function (method) that belongs to the `ifstream` class as demonstrated in lab.

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
set -e; clang++ -MM -g -Wall -pipe -std=c++14  read_from_file.cc \
	| sed 's/\(read_from_file\)\.o[ :]*/\1.o read_from_file.d : /g' > read_from_file.d; \
	[ -s read_from_file.d ] || rm -f read_from_file.d
clang++ -g -Wall -pipe -std=c++14  -c read_from_file.cc
clang++ -g -Wall -pipe -std=c++14 -o read_from_file read_from_file.o 
$ ./read_from_file 
Please provide a path to a file.
There was an error. Exiting.
$ ./read_from_file nonexistantfile.txt
Could not open the file nonexistantfile.txt!
There was an error. Exiting.
$ ./read_from_file 01_words.txt 
wittering
postdiastolic
pipkinet
candleball
unwax
unquiescent
wavingly
megadyne
shirtlike
whank
escopette
neuropathy
envassal
prosector
clotter
proctological
Moorish
superheterodyne
unvillaged
equiarticulate
End of file reached successfully!
$ ./read_from_file 02_words.txt 
sprew
periligamentous
overhover
maltolte
Phyllis
arboral
coaxial
Kiangan
Nereidiformia
defraudation
stereostatic
unshakeably
tardigradous
chocard
pensy
intersectional
phymatosis
stereometer
sherifa
cooter
End of file reached successfully!
$ ./read_from_file 03_words.txt 
unnatural
nonchargeable
gallic
taenioid
subbrachyskelic
fallway
soldierlike
notopteroid
forelive
paraphrase
touser
pennywort
webwork
galactopoiesis
ferineness
earhole
pseudoantique
site
horme
wheyeyness
End of file reached successfully!
$ ./read_from_file 04_words.txt 
The next line has 99 x letters
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
The next line has 100 x letters and an extra message
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
Encountered something crazy! Long line?
There was an error. Exiting.
```

