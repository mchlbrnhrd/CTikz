/**
 * @file
 * @brief Exception class
 * @author Michael Bernhard
 *
 * usage:\n
 * \code
 * try{
 *   //...
 *   throw CException("exception...");
 *   //...
 * } catch(CException e) {
 *   std::cout << e.what();
 * }
 * \endcode
 *
 */
/*
 * File:   CException.hpp
 * Author: Michael Bernhard
 *
 * Created on 18. November 2017
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
 *   } catch(CException e) {
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
    CException(const std::string& error_msg);
    CException(const std::stringstream& error_msg);
    CException(const std::ostringstream& error_msg);
    virtual ~CException() throw ();
    const char* what() const throw ();

    static void myTerminate() {
        std::cout << "unhandled CException" << std::endl;
        exit(1);
    };
private:
    std::string m_error_msg;

};

#endif	/* _CEXCEPTION_HPP */

