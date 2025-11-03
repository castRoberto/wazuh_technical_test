/*******************************************************************************
 * @file m_wazuh_arg_parser.h
 * @author Roberto Enrique Castro Beltran
 * @date 2025-11-02
 * @version 1.0.0
 * @brief ...
 *
 * @details
 * ...
 *
 ******************************************************************************/

#ifndef _M_WAZUH_ARG_PARSER_H_
#define _M_WAZUH_ARG_PARSER_H_


/******************************************************************************
* Cpp Includes
*/
#include <string>
#include <iostream>
#include <unordered_map>
#include <stdexcept>

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


/******************************************************************************
* Forward declarations
*/


/******************************************************************************
* Class / Interfaces / Structs / Enums / Typedefs / Using declarations
*/

/**
 * @brief Exception class for argument parser errors
 */
class arg_parser_error : public std::runtime_error {
  public:
    explicit arg_parser_error(const std::string& message)
      : std::runtime_error("ArgParser error: " + message) {}
};


/**
 * @brief The requirement level of an argument
 * This enum defines whether an argument is mandatory or optional.
 */
enum class ArgRequirement { kOptional, kMandatory };


/**
 * @brief Structure to hold argument option details
 */
struct ArgOption {
  std::string description;
  std::string value;
  ArgRequirement requirement;
  std::string alias;

  bool operator==(const ArgOption& other) const {
    return description == other.description &&
           value == other.value &&
           requirement == other.requirement;
  }

};

/**
 * @brief Argument parser by Wazuh
 */
class ArgParser {

  public:

    /**
     * @brief Constructor of the ArgParser library
     * @param app_name Name of the application
     * @param app_description Description of the application
     */
    explicit ArgParser (std::string app_name, std::string app_description);

    /**
     * @brief Parse the command line arguments
     * @param argc Argument count
     * @param argv Argument vector
     */
    void Parse (int argc, char* argv[]);

    /**
     * @brief Add an option to the parser
     * @param option The option string (e.g., "-h or --help")
     * @param requirement Whether the option is mandatory or optional
     * @param description Description of the option
     */
    void AddOption (std::string option,
                    std::string alias = "",
                    ArgRequirement requirement = ArgRequirement::kOptional,
                    std::string description = "",
                    std::string default_value = "");

    /**
     * @brief Get the value of an option
     * @param option The option string
     * @return The value associated with the option
     */
    std::string operator[](const std::string& option) const;

  private:

    /**
     * @brief Show header information
     */
    inline void ShowHeader (void) const;

    /**
     * @brief Show help information. Whow to use the application and its options
     */
    inline void ShowHelp (void) const;

    /**
     * @brief Validate the provided arguments against the defined options
     * @param argc Argument count
     * @param argv Argument vector
     * @return true if arguments are valid, false otherwise
     */
    inline bool AreValidArguments (int argc, char* argv[]) const;

    /**
     * @brief Determine if help information should be shown
     * @param argc Argument count
     * @param argv Argument vector
     * @return true if help option is present, false otherwise
     */
    inline bool ShouldShowHelp (int argc, char* argv[]) const;

    /**
     * @brief Get the operation removing '--' or '-' prefixes
     * @param s The input string
     * @return The operation string
     */
    inline std::string GetOption (const std::string& s) const;

  private:

    // Internal data members
    std::string _app_name;
    std::string _app_description;
    std::unordered_map<std::string, ArgOption> _options;

};


} /* namespace WAZUH */

#endif /* _M_WAZUH_ARG_PARSER_H_ */
