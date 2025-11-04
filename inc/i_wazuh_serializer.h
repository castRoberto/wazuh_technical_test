/*******************************************************************************
 * @file i_wazuh_serializer.h
 * @author Roberto Enrique Castro Beltran
 * @date 2025-11-03
 * @version 1.0.0
 * @brief Interface for Wazuh Serializer module
 *
 * @details
 * This file contains the interface declarations for the WAZUH::Serializer class.
 *
 ******************************************************************************/

#ifndef _I_WAZUH_SERIALIZER_H_
#define _I_WAZUH_SERIALIZER_H_


/******************************************************************************
* Cpp Includes
*/
#include <string>

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
 * @interface IWazuhSerializer
 * @brief Interface for Wazuh Serializer
 */
class IWazuhSerializer {

  public:

    virtual ~IWazuhSerializer () = default;

    /**
     * @brief Obtain fields from input stream and serialize
     * @param input Input stream
     * @return Serialized string
     */
    virtual std::string Serialize(std::istream& input) const = 0;

    /**
     * @brief Deserialize input stream into fields
     * @param input Input stream
     * @return Deserialized string
     */
    virtual std::string Deserialize(std::istream& input) const = 0;

};


} /* namespace WAZUH */

#endif /* _I_WAZUH_SERIALIZER_H_ */
