/*******************************************************************************
 * @file m_wazuh_arg_parser.cpp
 * @author Roberto Enrique Castro Beltran
 * @date 2025-11-02
 * @version 1.0.0
 * @changelog
 * - v1.0.0: Initial implementation
 * @brief Argument parser implementation
 *
 * @details
 * This file contains the implementation of the WAZUH::ArgParser class.
 * Used for parsing command-line arguments.
 *
 */


/******************************************************************************
 * Cpp Includes
 */
#include "m_wazuh_arg_parser.h"


/******************************************************************************
 * C includes
 */
#ifdef __cplusplus
extern "C" {
#endif

  // C headers here

#ifdef __cplusplus
}
#endif


/******************************************************************************
 * Namespace declaration
 */
namespace WAZUH {

/******************************************************************************
* Constants and macros definitions
*/
constexpr char kHelpOption[]    = "--help";
constexpr char kHelpOption_h[]  = "-h";
constexpr char kCommaDelimiter = ',';
constexpr uint8_t kInsufficientArgsCount = 1;


/******************************************************************************
 * Implementation of public functions / methods
 */

/**
 * @brief Constructor of the ArgParser library
 */
ArgParser::ArgParser (std::string app_name, std::string app_description) :
  _app_name {std::move(app_name)},
  _app_description {std::move(app_description)} {
  // Constructor implementation
}

/**
 * @brief Add an option to the parser
 */
void ArgParser::AddOption (std::string option,
                           std::string alias,
                           ArgRequirement requirement,
                           std::string description,
                           std::string default_value) {

  ArgOption arg_option;
  arg_option.description = std::move(description);
  arg_option.alias = std::move(alias);
  arg_option.value = std::move(default_value);
  arg_option.requirement = requirement;

  this->_options[option] = std::move(arg_option);

}

/**
 * @brief Parse the command line arguments
 */
void ArgParser::Parse (int argc, char* argv[]) {

  if (this->ShouldShowHelp (argc, argv) ||
      !this->AreValidArguments (argc, argv)) {

    this->ShowHelp ();

    throw arg_parser_error ("Invalid or insufficient arguments provided.");

  } else {

    for (int i = 1; i < argc; ++i) {

      std::string key = this->GetOption (argv[i]);

      for (const auto& option_pair : this->_options) {

        // Check for alias match
        if (key == option_pair.first ||
            key == option_pair.second.alias) {

          key = option_pair.first;

          this->_options[key].value.clear();

          // If the option requires a value, get the next argument
          if (i + 1 < argc && argv[i + 1][0] != '-') {

            this->_options[key].value = argv[i + 1];
            ++i;  // Skip the next argument as it's a value

          }

          if (this->_options[key].value.empty() &&
              option_pair.second.requirement == ArgRequirement::kMandatory) {

            this->ShowHelp ();

            throw arg_parser_error
                    ("Mandatory option '" + key + "' requires a value.");

          }

          break;
        }

      }

    }

  }

}

/**
 * @brief Get the value of an option
 */
std::string ArgParser::operator[] (const std::string& option) const {

  std::string value = "";

  auto it = this->_options.find(option);

  if (it != this->_options.end()) {
    value = it->second.value;
  }

  return value;

}

/******************************************************************************
 * Implementation of protected functions / methods
 */


/******************************************************************************
 * Implementation of private functions / methods
 */

/**
 * @brief Show header information
 * This function displays the application header information.
 */
void ArgParser::ShowHeader (void) const {

  std::cout << std::endl << this->_app_description << std::endl << std::endl;

}

/**
 * @brief Show help information. Whow to use the application and its options
 */
void ArgParser::ShowHelp (void) const {

  this->ShowHeader ();

  std::string result = "Usage:\n  " +
                       this->_app_name +
                       " [OPTIONS...]\n\n" +
                       "Options:\n";

  for (const auto& option_pair : this->_options) {

    if (!option_pair.second.alias.empty()) {

      result += "-" + option_pair.second.alias + ", ";

    }

    result += "--" + option_pair.first;

    result += "       \t" + option_pair.second.description;

    if (option_pair.second.requirement == ArgRequirement::kMandatory) {

      result += " (Mandatory)";

    } else {

      result += " (Optional)";

    }

    std::cout << result << std::endl;
    result.clear();

  }

  std::cout << std::endl;

}

/**
 * @brief Validate the provided arguments against the defined options
 */
bool ArgParser::AreValidArguments (int argc, char* argv[]) const {

  bool are_valid = true;

  // Check for mandatory options
  for (const auto& option_pair : this->_options) {

    bool found = false;

    if (ArgRequirement::kMandatory == option_pair.second.requirement) {

      for (int i = 1; i < argc; ++i) {

        std::string key = this->GetOption (argv[i]);

        if (key == option_pair.first ||
            key == option_pair.second.alias) {

          found = true;
          break;

        }

      }

      if (!found) {

        are_valid = false;
        break;

      }

    }

  }

  return are_valid;

}

/**
 * @brief Determine if help information should be shown
 */
bool ArgParser::ShouldShowHelp (int argc, char* argv[]) const {

  bool show_help = false;

  if (kInsufficientArgsCount == argc) {

    show_help = true;

  } else {

    for (int i = 1; i < argc; ++i) {

      std::string key = this->GetOption (argv[i]);

      if (kHelpOption_h == key || kHelpOption == key) {
        show_help = true;
        break;
      }

    }

  }

  return show_help;

}

/**
 * @brief Get the operation removing '--' or '-' prefixes
 */
std::string ArgParser::GetOption (const std::string& s) const {

  std::string operation;

  if (s.rfind ("--", 0) == 0) {
    operation = s.substr(2);
  } else if (s.rfind ("-", 0) == 0 && 2 == s.length()) {
    operation = s.substr(1);
  }
  return operation;

}

} /* namespace WAZUH */
