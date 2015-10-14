/* 
 * File:   Authenticator.hpp
 * Author: fys
 *
 * Created on October 14, 2015, 10:03 AM
 */

#ifndef AUTHENTICATOR_HPP
#define	AUTHENTICATOR_HPP

#include <array>
#include <stack>
#include <string>

#define MAX_CLIENT 10000
#define MAX_CLIENT_PSEUDO   8

typedef std::array<char, MAX_CLIENT_PSEUDO> Login;

class Authenticator
{
public:
    ~Authenticator();
    Authenticator();
    
    bool isValidUser(const int id, const std::string& login) const;

    int addConnection(const std::string& login);
    void freeConnection(const int id);
    
private:
    Login getArrayFromString(const std::string& login) const;
    Login getEmptyLogin() const;
    
private:
    std::array<Login, MAX_CLIENT >  auth;
    std::stack<int> freedConnection;
    int nextConnection;

};

#endif	/* AUTHENTICATOR_HPP */

