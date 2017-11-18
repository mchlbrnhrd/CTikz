/**
 * @file
 * @brief Exception class
 * @author Michael Bernhard
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
/*
 * File:   CException.cpp
 * Author: Michael Bernhard
 *
 * Created on 18. November 2017
 */


#include "CException.hpp"
#include <string>
#include <sstream>

CException::CException() {
    std::set_terminate(myTerminate);
    m_error_msg = "default exception";
}

CException::CException(const std::string& error_msg) {
    std::set_terminate(myTerminate);
    m_error_msg = error_msg;
}

CException::CException(const std::stringstream& error_msg) {
    std::set_terminate(myTerminate);
    m_error_msg = error_msg.str();
}

CException::CException(const std::ostringstream& error_msg) {
    std::set_terminate(myTerminate);
    m_error_msg = error_msg.str();
}

CException::~CException() throw () {
}

const char* CException::what() const throw () {
    return m_error_msg.c_str();
}
