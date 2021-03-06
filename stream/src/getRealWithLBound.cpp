#include <exception>

#include "utility/stream.hpp"

/** 
 * @param is A stream which a real number is to be extracted.
 * @param[in] name The name of the variable to be read from stream. Used when
 *                 logging information before throwing an exception. 
 * @param[in] bound The (inclusive) lower of real values that may be read 
 *                  without throwing an exception. 
 * @param[out] found Records whether a value could read from stream. If EOF is
 *                   encountered before a value can be read, **found** is set to
 *                   false. Otherwise, **found** is set to true.
 * @result When found and not in error, the real number value read from the input
 *         stream **in**. Otherwise, returns zero.
 *
 * @details 
 * This function should be used when the next string in a stream is required 
 * to be an real number value, but may not exist. If a string cannot be extracted 
 * from the stream (end of file), the **found** flag is set to false and zero is 
 * returned. Otherwise the **found** flag is set to true. If a string is extracted 
 * and isn't a real number value or is less than the **bound** argument, this method 
 * records an error via the logger specifying the variable name (see the **name** 
 * argument) and error type and throws an exception.
 */
double 
utility::stream::getRealWithLBound( std::istream& is, 
				    const std::string& name, 
				    const double bound, 
				    bool& found ){
  const double realNumber = utility::stream::getRealNumber(is, name, found);
  if ( found && 
       (realNumber < bound) ) {
    LOG(ERROR) << name << " argument must be greater than or equal to " << bound;
    throw std::exception();
  }
  return realNumber;
}

/** 
 * @param is A stream which a real number is to be extracted.
 * @param[in] name The name of the variable to be read from stream. Used when
 *                 logging information before throwing an exception. 
 * @param[in] bound The (inclusive) lower of real values that may be read 
 *                  without throwing an exception. 
 * @result When found and not in error, the real number value read from the input
 *         stream **in**. Otherwise, returns zero.
 *
 * @details 
 * This function should be used when the next string in a stream is required 
 * to be an real number value. If a string cannot be extracted from the stream 
 * (end of file), if the string is extracted and isn't an real number value or is
 * less than the *bound* argument, this method records an error via the logger 
 * specifying the variable name (see the *name* argument) and error type and 
 * throws an exception.
 */
double
utility::stream::getRealWithLBound( std::istream& is, 
				    const std::string& name, 
				    const double bound ){
  bool found;
  const double realNumber = utility::stream::getRealWithLBound(is, name, 
							       bound, found);
  if ( !found ){
    LOG(ERROR) << name << " argument could not be read from input.";
    throw std::exception();
  } 
  return realNumber;
}
