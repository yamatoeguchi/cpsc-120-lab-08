# ANSI & ASCII Animation

In the 1980s and 1990s, computers did not have graphics displays. Everything was just text on a screen. And not everyone had fancy, expensive software so everyone used plain text to exchange information.

When you have a computer an no graphics and a burning desire to create some visual art, you may just decide to try your hand at [ASCII art](https://en.wikipedia.org/wiki/ASCII_art).

ASCII stands for American Standard Code for Information Interchange. It is a standards creation body which established in 1963 a 7-bit (not 8-bit!) encoding for 128 different symbols used on [teletype](https://en.wikipedia.org/wiki/Teleprinter) machines and later on early computers. Of the 128 symbols, 95 of the symbols are printable symbols, a-z, A-Z, 0-9, punctuation, etc.

ASCII evolved into ANSI, American National Standards Institute. ANSI created a number of other standards one of which is [ANSI X3.64](https://en.wikipedia.org/wiki/ANSI_escape_code) which is the ANSI escape codes.

With a lot of time, you could create a nice little piece of [art](http://textfiles.com/art/) or even piece together an animation.

What we can do is use our knowledge of reading from a file and printing to a screen to play the animations on our Linux computers. Unfortunately, our modern computers are so fast that the animations do not play correctly so we will have to intentionally slow down our computers by putting them to sleep.

In the C++ standard library there is a `chrono` header file which defines [duration of time](https://en.cppreference.com/w/cpp/chrono/duration) and a `thread` header file which defines a function `sleep_for()` that pauses the program's execution.

If I want to stop my program for 10,000 microseconds (10 milliseconds or 0.01 seconds), then I just need to call `sleep_for()` with that value as a parameter. The `chrono` header file defines how to convert it to microseconds when you place the `us` next to the value 10,000.

```c++
this_thread::sleep_for(10000us);
```

Because the needs of this program is to print the data in the animation input file one letter at a time, we will use the method [get()](https://en.cppreference.com/w/cpp/io/basic_istream/get) to read one character out of the input file stream and then immediately print it to the terminal. Doing this repeatedly in a while loop will display the animation.

```c++
char letter;
while (input_file_stream.get(letter)) {
  cout << letter;
  this_thread::sleep_for(10000us);
}
```

(I've been discouraging the use of `char` types the whole semester and I still discourage it. However for this project it makes sense to use the `char` type because the alternative would make this simple program too complicated.)

If your terminal gets messed up or doesn't behave correctly, try resetting it with the `reset` command. If that doesn't fix the problem, close and open a new terminal window.

## Requirements

Using `ifstream`, read the contents of an ANSI animation file and print it to the terminal one character at a time such that the animation playsback smoothly. Use the `get()` method to read one `char` value from the file at a time and print out the char to the terminal. Use `sleep_for()` to pause execution of your program.

The default delay is 10,000 microseconds however you may adjust the value depending on the performance of your computer.

Using the inline documentation, implement the following functions.

* `void ErrorMessage(const string&message);`

The program takes three command line arguments other than the program's name:

1. `argv[1]` is the path to the input file

To fetch animation files for your use, use the `make fetchfiles` command. The `make spotless` command will delete the files that are downloaded.

To compile your program, you use the `make` command. A Makefile is provided for this exercise.

The Makefile has the following targets:
  
* all: builds the project
* clean: removes object and dependency files
* spotless: removes everything the clean target removes and all binaries
* doc: generate HTML documentation from the source code using Doxygen
* format: outputs a [`diff`](https://en.wikipedia.org/wiki/Diff) showing where your formatting differes from the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html)
* tidy: output of the [linter](https://en.wikipedia.org/wiki/Lint_(software)) to give you tips on how to improve your code
* headercheck: check to make sure your files have the appropriate header
* *fetchfiles*: download sample animation files from textfiles.com

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
$ ls
Doxyfile		README.md		play_animation.cc
Makefile		animation_urls.txt
$ make
set -e; clang++ -MM -g -Wall -pipe -std=c++14  play_animation.cc \
	| sed 's/\(play_animation\)\.o[ :]*/\1.o play_animation.d : /g' > play_animation.d; \
	[ -s play_animation.d ] || rm -f play_animation.d
clang++ -g -Wall -pipe -std=c++14  -c play_animation.cc
clang++ -g -Wall -pipe -std=c++14 -o play_animation play_animation.o 
$ ./play_animation 
Please provide a path to a file and a playback speed.
There was an error. Exiting.
$ make fetchfiles
for i in http://www.textfiles.com/art/bambi.vt http://www.textfiles.com/art/beer.vt http://www.textfiles.com/art/bomb.vt http://www.textfiles.com/art/cartwhee.vt http://www.textfiles.com/art/dont-wor.vt http://www.textfiles.com/art/firework.vt http://www.textfiles.com/art/fireworks.vt http://www.textfiles.com/art/fishy2.vt http://www.textfiles.com/art/glass.vt http://www.textfiles.com/art/globe.vt http://www.textfiles.com/art/juanspla.vt http://www.textfiles.com/art/jumble.vt http://www.textfiles.com/art/nasa.vt http://www.textfiles.com/art/paradise.vt http://www.textfiles.com/art/prey.vt http://www.textfiles.com/art/snowing.vt http://www.textfiles.com/art/tetris.vt http://www.textfiles.com/art/trek.vt http://www.textfiles.com/art/turkey.vt http://www.textfiles.com/art/tv.vt http://www.textfiles.com/art/twilight.vt http://www.textfiles.com/art/valentin.vt http://www.textfiles.com/art/wineglas.vt http://www.textfiles.com/art/xmas.vt; do \
		wget $i; \
	done
--2021-04-20 04:20:12--  http://www.textfiles.com/art/bambi.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 12818 (13K)
Saving to: ‘bambi.vt’

bambi.vt            100%[===================>]  12.52K  --.-KB/s    in 0s      

2021-04-20 04:20:12 (73.6 MB/s) - ‘bambi.vt’ saved [12818/12818]

--2021-04-20 04:20:12--  http://www.textfiles.com/art/beer.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 14415 (14K)
Saving to: ‘beer.vt’

beer.vt             100%[===================>]  14.08K  --.-KB/s    in 0.07s   

2021-04-20 04:20:12 (195 KB/s) - ‘beer.vt’ saved [14415/14415]

--2021-04-20 04:20:12--  http://www.textfiles.com/art/bomb.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 2649 (2.6K)
Saving to: ‘bomb.vt’

bomb.vt             100%[===================>]   2.59K  --.-KB/s    in 0s      

2021-04-20 04:20:12 (120 MB/s) - ‘bomb.vt’ saved [2649/2649]

--2021-04-20 04:20:12--  http://www.textfiles.com/art/cartwhee.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 17418 (17K)
Saving to: ‘cartwhee.vt’

cartwhee.vt         100%[===================>]  17.01K  --.-KB/s    in 0.07s   

2021-04-20 04:20:12 (234 KB/s) - ‘cartwhee.vt’ saved [17418/17418]

--2021-04-20 04:20:12--  http://www.textfiles.com/art/dont-wor.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 15305 (15K)
Saving to: ‘dont-wor.vt’

dont-wor.vt         100%[===================>]  14.95K  --.-KB/s    in 0.07s   

2021-04-20 04:20:13 (206 KB/s) - ‘dont-wor.vt’ saved [15305/15305]

--2021-04-20 04:20:13--  http://www.textfiles.com/art/firework.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 34801 (34K)
Saving to: ‘firework.vt’

firework.vt         100%[===================>]  33.99K  --.-KB/s    in 0.07s   

2021-04-20 04:20:13 (467 KB/s) - ‘firework.vt’ saved [34801/34801]

--2021-04-20 04:20:13--  http://www.textfiles.com/art/fireworks.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 6727 (6.6K)
Saving to: ‘fireworks.vt’

fireworks.vt        100%[===================>]   6.57K  --.-KB/s    in 0s      

2021-04-20 04:20:13 (143 MB/s) - ‘fireworks.vt’ saved [6727/6727]

--2021-04-20 04:20:13--  http://www.textfiles.com/art/fishy2.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 211945 (207K)
Saving to: ‘fishy2.vt’

fishy2.vt           100%[===================>] 206.98K   716KB/s    in 0.3s    

2021-04-20 04:20:13 (716 KB/s) - ‘fishy2.vt’ saved [211945/211945]

--2021-04-20 04:20:13--  http://www.textfiles.com/art/glass.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 11620 (11K)
Saving to: ‘glass.vt’

glass.vt            100%[===================>]  11.35K  --.-KB/s    in 0s      

2021-04-20 04:20:14 (68.4 MB/s) - ‘glass.vt’ saved [11620/11620]

--2021-04-20 04:20:14--  http://www.textfiles.com/art/globe.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 29696 (29K)
Saving to: ‘globe.vt’

globe.vt            100%[===================>]  29.00K  --.-KB/s    in 0.07s   

2021-04-20 04:20:14 (399 KB/s) - ‘globe.vt’ saved [29696/29696]

--2021-04-20 04:20:14--  http://www.textfiles.com/art/juanspla.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 41773 (41K)
Saving to: ‘juanspla.vt’

juanspla.vt         100%[===================>]  40.79K  --.-KB/s    in 0.1s    

2021-04-20 04:20:14 (281 KB/s) - ‘juanspla.vt’ saved [41773/41773]

--2021-04-20 04:20:14--  http://www.textfiles.com/art/jumble.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 28816 (28K)
Saving to: ‘jumble.vt’

jumble.vt           100%[===================>]  28.14K  --.-KB/s    in 0.07s   

2021-04-20 04:20:14 (388 KB/s) - ‘jumble.vt’ saved [28816/28816]

--2021-04-20 04:20:14--  http://www.textfiles.com/art/nasa.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 19159 (19K)
Saving to: ‘nasa.vt’

nasa.vt             100%[===================>]  18.71K  --.-KB/s    in 0.07s   

2021-04-20 04:20:15 (261 KB/s) - ‘nasa.vt’ saved [19159/19159]

--2021-04-20 04:20:15--  http://www.textfiles.com/art/paradise.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 24788 (24K)
Saving to: ‘paradise.vt’

paradise.vt         100%[===================>]  24.21K  --.-KB/s    in 0.07s   

2021-04-20 04:20:15 (334 KB/s) - ‘paradise.vt’ saved [24788/24788]

--2021-04-20 04:20:15--  http://www.textfiles.com/art/prey.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 9010 (8.8K)
Saving to: ‘prey.vt’

prey.vt             100%[===================>]   8.80K  --.-KB/s    in 0s      

2021-04-20 04:20:15 (57.3 MB/s) - ‘prey.vt’ saved [9010/9010]

--2021-04-20 04:20:15--  http://www.textfiles.com/art/snowing.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 10334 (10K)
Saving to: ‘snowing.vt’

snowing.vt          100%[===================>]  10.09K  --.-KB/s    in 0s      

2021-04-20 04:20:15 (52.4 MB/s) - ‘snowing.vt’ saved [10334/10334]

--2021-04-20 04:20:15--  http://www.textfiles.com/art/tetris.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 9176 (9.0K)
Saving to: ‘tetris.vt’

tetris.vt           100%[===================>]   8.96K  --.-KB/s    in 0s      

2021-04-20 04:20:15 (54.7 MB/s) - ‘tetris.vt’ saved [9176/9176]

--2021-04-20 04:20:15--  http://www.textfiles.com/art/trek.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 21075 (21K)
Saving to: ‘trek.vt’

trek.vt             100%[===================>]  20.58K  --.-KB/s    in 0.07s   

2021-04-20 04:20:16 (282 KB/s) - ‘trek.vt’ saved [21075/21075]

--2021-04-20 04:20:16--  http://www.textfiles.com/art/turkey.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 13183 (13K)
Saving to: ‘turkey.vt’

turkey.vt           100%[===================>]  12.87K  --.-KB/s    in 0s      

2021-04-20 04:20:16 (93.8 MB/s) - ‘turkey.vt’ saved [13183/13183]

--2021-04-20 04:20:16--  http://www.textfiles.com/art/tv.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 63909 (62K)
Saving to: ‘tv.vt’

tv.vt               100%[===================>]  62.41K  --.-KB/s    in 0.1s    

2021-04-20 04:20:16 (430 KB/s) - ‘tv.vt’ saved [63909/63909]

--2021-04-20 04:20:16--  http://www.textfiles.com/art/twilight.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 64272 (63K)
Saving to: ‘twilight.vt’

twilight.vt         100%[===================>]  62.77K  --.-KB/s    in 0.1s    

2021-04-20 04:20:16 (431 KB/s) - ‘twilight.vt’ saved [64272/64272]

--2021-04-20 04:20:16--  http://www.textfiles.com/art/valentin.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 3702 (3.6K)
Saving to: ‘valentin.vt’

valentin.vt         100%[===================>]   3.62K  --.-KB/s    in 0s      

2021-04-20 04:20:17 (80.2 MB/s) - ‘valentin.vt’ saved [3702/3702]

--2021-04-20 04:20:17--  http://www.textfiles.com/art/wineglas.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 9749 (9.5K)
Saving to: ‘wineglas.vt’

wineglas.vt         100%[===================>]   9.52K  --.-KB/s    in 0s      

2021-04-20 04:20:17 (47.2 MB/s) - ‘wineglas.vt’ saved [9749/9749]

--2021-04-20 04:20:17--  http://www.textfiles.com/art/xmas.vt
Resolving www.textfiles.com (www.textfiles.com)... 208.86.224.90
Connecting to www.textfiles.com (www.textfiles.com)|208.86.224.90|:80... connected.
HTTP request sent, awaiting response... 200 OK
Length: 45723 (45K)
Saving to: ‘xmas.vt’

xmas.vt             100%[===================>]  44.65K  --.-KB/s    in 0.1s    

2021-04-20 04:20:17 (310 KB/s) - ‘xmas.vt’ saved [45723/45723]

$ ./play_animation xmas.vt 
```

