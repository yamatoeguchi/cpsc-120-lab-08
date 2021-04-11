
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

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
  // TODO: Write the body of this function
}

/// Entry point to the read_from_file program
/// \remark Must have 1 argument. The argument is a path to a file. In the
/// simpliest case, it can be the name of a file in the same directory
/// as the program.
int main(int argc, char* argv[]) {
  if (argc < 2) {
    ErrorMessage("Please provide a path to a file.");
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
  // Let's set a hard limit to how long lines can be in this program.
  // Setting the limit to 100 letters is more than reasonable. Should
  // our program encounter a line with more than 100 letters then the
  // input routine will experience a fatal error and stop.
  const int kMaxLineLength = 100;

  // While there are lines remaining in input_file_stream to be read,
  // copy the current line into line_buffer. Each line can be no longer
  // than kMaxLineLength and each line ends with a '\n' letter.
  // https://en.cppreference.com/w/cpp/io/basic_istream/getline
  //
  // &line_buffer[0] is a fancy way to tell getline where to store
  // the data because this is an old-fashioned way of reading from
  // a file and it is backwards compatible with C.

  // TODO: Write a loop to read and print out the contents of the input
  // file.
  // To read from a file, we will read it one line at a time. We shall
  // hold the line that we're reading in string variable. Note that unlike
  // a string stream, a string is non-mutable. Every time we pass through
  // the while loop below, a new string is created (not changed).
  // https://en.cppreference.com/w/cpp/string/basic_string
  string line_buffer;
  // Let's make sure that the string is as long as our maximum line length.
  // https://en.cppreference.com/w/cpp/string/basic_string/resize
  line_buffer.resize(kMaxLineLength);
  // Read the line from the input_file_stream and store the read line
  // into the variable line_buffer.
  input_file_stream.getline(&line_buffer[0], kMaxLineLength, '\n');
  

  // We're done reading the file because we got to the end of the file or
  // there was an error condition. Let's check to see what happened.
  if (input_file_stream.bad()) {
    ErrorMessage("I/O error while reading");
    exit(1);
  } else if (input_file_stream.eof()) {
    cout << "End of file reached successfully!\n";
  } else if (input_file_stream.fail()) {
    ErrorMessage("Encountered something crazy! Long line?");
    exit(1);
  }

  // When you open something, close it!
  // This is a very important habit to develop.
  input_file_stream.close();

  return 0;
}
