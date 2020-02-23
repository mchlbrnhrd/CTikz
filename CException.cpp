/**
 * @file CException.cpp
 * @brief Exception class
 * @author Michael Bernhard
 *
 * Created on 18. November 2017
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


#include "CException.hpp"
#include <string>
#include <sstream>

CException::CException() {
    std::set_terminate(myTerminate);
    m_errorMsg_s = "default exception";
}

CException::CException(const std::string& f_errorMsg_s) {
    std::set_terminate(myTerminate);
    m_errorMsg_s = f_errorMsg_s;
}

CException::CException(const std::stringstream& f_errorMsg_ss) {
    std::set_terminate(myTerminate);
    m_errorMsg_s = f_errorMsg_ss.str();
}

CException::CException(const std::ostringstream& f_errorMsg_ss) {
    std::set_terminate(myTerminate);
    m_errorMsg_s = f_errorMsg_ss.str();
}

CException::~CException() throw () {
}

const char* CException::what() const throw () {
    return m_errorMsg_s.c_str();
}
