// Yamato Eguchi
// CPSC 120-01
// 2021-04-09
// yamatoe1227@gmail.com
// @yamatoeguchi
//
// Lab 08-02
//
// This is my write to file assignment
// 

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
  cout << message << "\n";
  cout << "There was an error. Exiting.\n";
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
  string argv_one_output_file_name = string(argv[1]);

  // An ofstream is a an output file stream. It is used to open
  // files for writing. On the line below an output file stream is
  // allocated and initialized with the path defined in the variable
  // argv_one_output_file_name. If the program has permission to write
  // to the path, then the program will create the file if it doesn't
  // exist and if it does exist the file will be truncated (destroyed)
  // before being written to.
  // https://en.cppreference.com/w/cpp/io/basic_ofstream
  ofstream output_file_stream(argv_one_output_file_name);
  // Check to ensure that the file was opened successfully. If the file
  // doesn't exist or the program doesn't have permission to write the
  // file then the operation to open the file would have failed.
  if (!output_file_stream.is_open()) {
    // An output string stream is an object that defines a string that
    // can be changed while the program is running. Here, the string
    // is initialized with an error message and then the file name is
    // appended once the program is running.
    // https://en.cppreference.com/w/cpp/io/basic_stringstream/basic_stringstream
    ostringstream message_buffer("Could not open the file ", ios_base::ate);
    // String streams can use the same operators as cout and cin.
    message_buffer << argv_one_output_file_name << "!";
    // Convert the string stream to a string before passing it to
    // ErrorMessage().
    ErrorMessage(message_buffer.str());
    exit(1);
  }

  string secret_message;

  cout << "What's a secret message that you'd like to write into a file?\n";
  cout << "Type your message out and when you're done ";
  cout << "press return or enter.\n";

  // TODO: Read the secret message from the keyboard and save it to
  // secret_message
  getline(cin, secret_message);

  // TODO: Write the secret message to the output file.
  output_file_stream << secret_message << "\n";

  if (output_file_stream.bad()) {
    ErrorMessage("I/O error while reading");
    exit(1);
  } else if (output_file_stream.fail()) {
    ErrorMessage("Encountered something crazy! Long line?");
    exit(1);
  }

  cout << "Your secret message was saved into " << argv_one_output_file_name
       << "!\n";

  // When you open something, close it!
  // This is a very important habit to develop.
  output_file_stream.close();

  return 0;
}
