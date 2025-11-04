/*******************************************************************************
 * @file m_wazuh_delimited_serializer.cpp
 * @author Roberto Enrique Castro Beltran
 * @date 2025-11-03
 * @version 1.0.0
 * @changelog
 * - v1.0.0: Initial implementation
 * @brief Delimited Serializer implementation
 *
 * @details
 * This file contains the implementation of the WAZUH::DelimitedSerializer class.
 * It provides methods for serializing and deserializing text fields using
 * a specified delimiter.
 */


/******************************************************************************
 * Cpp Includes
 */
#include "m_wazuh_delimited_serializer.h"

#include <vector>
#include <iostream>


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
 * Implementation of public functions / methods
 */

 DelimitedSerializer::DelimitedSerializer
 (char delimiter) : _delimiter {delimiter} {

}

/**
* @brief Serialize method
*/
std::string DelimitedSerializer::Serialize (std::istream& input) const {

 std::vector<std::string> fields;
 std::string line;
 std::string serialized;

 // Read lines from input until EOF
 while (std::getline (input, line)) {

   fields.push_back(line);

 }

 // Serialize all fields with the specified delimiter
 bool first = true;
 for (const auto& field : fields) {

   if (!first) { serialized += _delimiter; }
   else { first = false; }

   serialized += EscapeField (field);

 }

 return serialized;

}


/**
 * @brief Deserialize method
 */
std::string DelimitedSerializer::Deserialize (std::istream& input) const {

  std::string line;
  std::string deserialized = "";

  // Read the serialized line
  if (std::getline (input, line)) {

    std::vector<std::string> fields;
    std::string current_field;

    for (size_t i = 0; i < line.length (); ++i) {

      if (line[i] == '\\' && i + 1 < line.length ()) {

        // Handle escaped characters
        char next = line[i + 1];
        if (next == '\\') {

          current_field += '\\';
          ++i; // Skip next character

        } else if (next == 'n') {

          current_field += '\n';
          ++i; // Skip next character

        } else if (next == _delimiter) {

          current_field += _delimiter;
          ++i; // Skip next character

        } else {

          // Unknown escape sequence, treat as literal
          current_field += line[i];

        }

      } else if (line[i] == _delimiter) {

        // Found unescaped delimiter, end current field
        fields.push_back (current_field);
        current_field.clear ();

      } else {

        current_field += line[i];

      }

    }

    // Add the last field
    fields.push_back (current_field);

    // Output each field on a separate line
    for (const auto& field : fields) {

      deserialized += field + "\n";

    }

  }

  return deserialized;

}


/******************************************************************************
 * Implementation of protected functions / methods
 */


/******************************************************************************
 * Implementation of private functions / methods
 */


/**
 * @brief Escape a field by escaping delimiters and special characters
 */
std::string DelimitedSerializer::EscapeField (const std::string& field) const {

  std::string escaped;

  for (char c : field) {

    switch (c) {

      case '\\':

        escaped += "\\\\";
        break;

      case '\n':

        escaped += "\\n";
        break;

      case '\r':

        break;

      default:

        if (c == _delimiter) {

          escaped += '\\';
          escaped += c;

        } else {

          escaped += c;

        }

    }

  }

  return escaped;

}

} /* namespace WAZUH */
