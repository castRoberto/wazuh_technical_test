/*******************************************************************************
 * @file m_wazuh_delimited_serializer.h
 * @author Roberto Enrique Castro Beltran
 * @date 2025-11-03
 * @version 1.0.0
 * @brief Header for Wazuh Serializer module
 *
 * @details
 * This file contains the declarations for the WAZUH::Serializer class.
 * It provides methods for serializing and deserializing text fields using
 * a specified delimiter.
 *
 ******************************************************************************/

#ifndef _M_WAZUH_SERIALIZER_H_
#define _M_WAZUH_SERIALIZER_H_


/******************************************************************************
* Cpp Includes
*/
#include "i_wazuh_serializer.h"

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

class DelimitedSerializer : public IWazuhSerializer {

  private:

    char _delimiter;

  public:

    /**
     * @brief Constructor with delimiter
     * @param delimiter Delimiter character
     */
    explicit DelimitedSerializer (char delimiter);

    /**
     * @brief Serialize input stream into a delimited string
     * @param input Input stream
     * @return Serialized string
     */
    std::string Serialize (std::istream& input) const override;

    /**
     * @brief Deserialize input stream from a delimited string
     * @param input Input stream
     * @return Deserialized string
     */
    std::string Deserialize (std::istream& input) const override;

  private:

    std::string EscapeField (const std::string& field) const;

};


} /* namespace WAZUH */


#endif /* _M_WAZUH_SERIALIZER_H_ */
