// Yamato Eguchi
// CPSC 120-01
// 2021-04-09
// yamatoe1227@csu.fullerton.edu
// @yamatoeguchi
//
// Lab 08-03
//
// This is my play animation assignment
//

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

using namespace std;

/// ErrorMessage prints out \p message first and then prints the standard
/// message
/// \code
/// "There was an error. Exiting.\n".
/// \endcode
///
/// \param message The programmer defined string that specifies the current
/// error.
void ErrorMessage(const string& message) {
  // Write the body of this function
  cout << message << "\n";
  cout << "There was an error. Exiting.\n";
}

/// Entry point to the read_from_file program
/// \remark Must have 1 argument. The argument is a path to a file. In the
/// simpliest case, it can be the name of a file in the same directory
/// as the program.
int main(int argc, char* argv[]) {
  if (argc < 2) {
    ErrorMessage("Please provide a path to a file and a playback speed.");
    exit(1);
  }
  string argv_one_input_file_name = string(argv[1]);

  // An ifstream is a an input file stream. It is used to open
  // files for reading. On the line below an input file stream is
  // allocated and initialized with the path defined in the variable
  // argv_one_input_file_name. If argv_one_input_file_name does not
  // exist, then the variable input_file_stream will be in an undefined
  // state.
  // https://en.cppreference.com/w/cpp/io/basic_ifstream
  ifstream input_file_stream(argv_one_input_file_name);
  // Check to ensure that the file was opened successfully. If the file
  // doesn't exist or the program doesn't have permission to read the
  // file then the operation to open the file would have failed.
  if (!input_file_stream.is_open()) {
    // An output string stream is an object that defines a string that
    // can be changed while the program is running. Here, the string
    // is initialized with an error message and then the file name is
    // appended once the program is running.
    // https://en.cppreference.com/w/cpp/io/basic_stringstream/basic_stringstream
    ostringstream message_buffer("Could not open the file ", ios_base::ate);
    // String streams can use the same operators as cout and cin.
    message_buffer << argv_one_input_file_name << "!";
    // Convert the string stream to a string before passing it to
    // ErrorMessage().
    ErrorMessage(message_buffer.str());
    exit(1);
  }

  // This is one of the few times in this class where we will use a char
  // type. In order to make the animation work, we must copy a letter out
  // of the input file into a variable, then print the letter to the
  // terminal. We repeat this process until we reach the end of the file.
  // To mimic the performance of a terminal from the 1980s and 1990s, we
  // cause the program to stop for 10,000 microseconds after every
  // iteration of the loop.
  char letter;
  while (input_file_stream.get(letter)) {
      cout << letter;
      this_thread::sleep_for(10000us);
  }

  // Write a loop to read one letter from the input file and then
  // immediately print it out. Then sleep for a short period of time to
  // slow down your computer.

  // Example...
  // Sleep for 10,000 microseconds - adjust this if your computer is
  // too fast or too slow. The bigger the number the slower the program
  // will run. The smaller the number, the faster the program will run.
  // this_thread::sleep_for((10000us));

  // We're done reading the file because we got to the end of the file or
  // there was an error condition. Let's check to see what happened.
  if (input_file_stream.bad()) {
    ErrorMessage("I/O error while reading");
    exit(1);
  } else if (input_file_stream.eof()) {
    cout << "\nEnd of file reached successfully!\n";
  } else if (input_file_stream.fail()) {
    ErrorMessage("Encountered something crazy! Long line?");
    exit(1);
  }

  // When you open something, close it!
  // This is a very important habit to develop.
  input_file_stream.close();

  return 0;
}
