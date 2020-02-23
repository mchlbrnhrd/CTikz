/**
 * @file CException.hpp
 * @brief Exception class
 * @author Michael Bernhard
 *
 * Created on 18. November 2017
 *
 * usage:\n
 * \code
 * try{
 *   //...
 *   throw CException("exception...");
 *   //...
 * } catch(CException& e) {
 *   std::cout << e.what();
 * }
 * \endcode
 *
 */

#ifndef _CEXCEPTION_HPP
#define	_CEXCEPTION_HPP

#include <string>
#include <sstream>
#include <exception>
#include <stdlib.h>
#include <iostream>

/**
 * @brief Exception class
 *
 * usage:\n
 * \code
 * int main() {
 *   try{
 *     //...
 *     throw CException("Exception message...");
 *     //...
 *   } catch(CException& e) {
 *     std::cout << "CException: " << e.what() << std::endl;
 *   } catch (std::exception& e) {
 *     std::cout << "std exception: " << e.what() << std::endl;
 *   } catch (...) {
 *     std::cout << "unknown exception: " << std::endl;
 *   }
 * }
 * \endcode
 *
 */
class CException : public std::exception {
public:
  CException();
  CException(const std::string& f_errorMsg_s);
  CException(const std::stringstream& f_errorMsg_ss);
  CException(const std::ostringstream& f_errorMsg_ss);
  virtual ~CException() throw ();
  const char* what() const throw ();
  
  static void myTerminate() {
    std::cout << "unhandled CException" << std::endl;
    exit(1);
  };
private:
  std::string m_errorMsg_s;
  
};

#endif	/* _CEXCEPTION_HPP */
