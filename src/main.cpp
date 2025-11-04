/*******************************************************************************
 * @file main.cpp
 * @author Roberto Enrique Castro Beltran
 * @date 2025-11-02
 * @version 1.0.0
 * @changelog
 * - v1.0.0: Initial implementation
 * @brief ...
 *
 * @details
 * ...
 *
 */


/******************************************************************************
 * Cpp Includes
 */
#include <iostream>
#include <string>
#include <vector>

#include "m_wazuh_arg_parser.h"
#include "m_wazuh_delimited_serializer.h"

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
 * Constants and macros definitions
 */
constexpr char kAppName[] = "serializer";
constexpr char kAppDescription[] = "Wazuh Application for text field serialization and deserialization";

constexpr char kHelpOption[]    = "help";
constexpr char kHelpDescription[] = "Show help information";

constexpr char kModeOption[]    = "mode";
constexpr char kModeDescription[] = "Mode: serialize or deserialize";

constexpr char kDelimiterOption[]    = "delimiter";
constexpr char kDelimiterDescription[] = "Delimiter character";


/******************************************************************************
 * Implementation of public functions / methods
 */

/**
 * @brief Main entry point of the application
 */
int main (int argc, char* argv[]) {

  WAZUH::ArgParser arg_parser (kAppName, kAppDescription);

  arg_parser.AddOption (kHelpOption, "h",
                        WAZUH::ArgRequirement::kOptional,
                        kHelpDescription);

  arg_parser.AddOption (kModeOption, "m",
                        WAZUH::ArgRequirement::kMandatory,
                        kModeDescription);

  arg_parser.AddOption (kDelimiterOption, "d",
                        WAZUH::ArgRequirement::kOptional,
                        kDelimiterDescription,
                        ",");

  try {

    arg_parser.Parse (argc, argv);

    std::string mode = arg_parser[kModeOption];
    char delimiter = arg_parser[kDelimiterOption][0];

    WAZUH::DelimitedSerializer delimited_serializer (delimiter);

    if ("serialize" == mode) {

      std::string serialized = delimited_serializer.Serialize (std::cin);

      std::cout << serialized << std::endl;

    } else if ("deserialize" == mode) {

      std::string deserialized = delimited_serializer.Deserialize (std::cin);

      std::cout << deserialized;

    } else {

      std::cerr << "Invalid mode. Use 'serialize' or 'deserialize'." << std::endl;
      return 1;

    }

  } catch (const WAZUH::arg_parser_error& e) {

    std::cerr << e.what() << std::endl;
    return 1;

  }

  return 0;

}

/******************************************************************************
 * Implementation of protected functions / methods
 */


/******************************************************************************
 * Implementation of private functions / methods
 */
