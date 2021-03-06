// $Id$ 	
/** \file driver.h Declaration of the parser::Driver class. */

#ifndef DRIVER_H_
#define DRIVER_H_

#include <string>
#include <vector>
// forward declaration

class ParserContext;

/** The parser namespace is used to encapsulate the three parser classes
 * parser::Parser, parser::Scanner and parser::Driver */
namespace parser {

/** The Driver class brings together all components. It creates an instance of
 * the Parser and Scanner classes and connects them. Then the input stream is
 * fed into the scanner object and the parser gets it's token
 * sequence. Furthermore the driver object is available in the grammar rules as
 * a parameter. Therefore the driver class contains a reference to the
 * structure into which the parsed data is saved. */
class Driver {
 public:
  /// construct a new parser driver context
  Driver();

  /// enable debug output in the flex scanner
  bool trace_scanning;

  /// enable debug output in the bison parser
  bool trace_parsing;

  /// stream name (file or input stream) used for error messages.
  std::string streamname;

  /** Invoke the scanner and parser for a stream.
   * @param in	input stream
   * @param sname	stream name for error messages
   * @return		true if successfully parsed
   */
  bool parse_stream(ParserContext & ctx, std::istream& in,
                    const std::string& sname = "stream input");

  /** Invoke the scanner and parser on an input string.
   * @param input	input string
   * @param sname	stream name for error messages
   * @return		true if successfully parsed
   */
  bool parse_string(ParserContext & ctx, const std::string& input,
                    const std::string& sname = "string stream");

  /** Invoke the scanner and parser on a file. Use parse_stream with a
   * std::ifstream if detection of file reading errors is required.
   * @param filename	input file name
   * @return		true if successfully parsed
   */
  bool parse_file(ParserContext & ctx, const std::string& filename);

  // To demonstrate pure handling of parse errors, instead of
  // simply dumping them on the standard error output, we will pass
  // them to the driver using the following two member functions.

  /** Error handling with associated line number. This can be modified to
   * output the error e.g. to a dialog box. */
  void error(const class location& l, const std::string& m);

  /** General error handling. This can be modified to output the error
   * e.g. to a dialog box. */
  void error(const std::string& m);

  /** Pointer to the current lexer instance, this is used to connect the
   * parser to the scanner. It is used in the yylex macro. */
  class Scanner* lexer;

  /** Reference to the calculator context filled during parsing of the
   * expressions. */
  const std::string & ErrorMessage() { return error_message_; }
private:
  std::string input_;

  std::string error_message_;
};

}  // namespace parser

#endif // DRIVER_H_
