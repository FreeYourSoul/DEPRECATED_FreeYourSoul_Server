/* 
 * File:   Authenticator.cpp
 * Author: fys
 * 
 * Created on October 14, 2015, 10:04 AM
 */

#include "Authenticator.hpp"

Authenticator::~Authenticator()
{
}

Authenticator::Authenticator()
{
  auth.fill(getEmptyLogin());
  nextConnection = 0;
}

Login Authenticator::getEmptyLogin() const
{
  return getArrayFromString("");
}

Login Authenticator::getArrayFromString(const std::string& login) const
{
    Login tmp;

    for (unsigned int i = 0 ; i < login.size() ; ++i)
      tmp[i] = login.at(i);
    return (tmp);
}

void Authenticator::freeConnection(const int id)
{
  auth.at(id) = getEmptyLogin();
  freedConnection.push(id);
}

int Authenticator::addConnection(const std::string& login)
{
  int ret;
  
  if (!freedConnection.empty())
  {
    ret = freedConnection.top();
    freedConnection.pop();
  }
  else if (nextConnection > -1 && (nextConnection + 1) < MAX_CLIENT)
    ret = nextConnection++;
  else
    ret = -1;
  if (ret != -1)
    auth.at(ret) = getArrayFromString(login);
  return (ret);
}

bool Authenticator::isValidUser(const int id, const std::string& login) const
{
  if (id < MAX_CLIENT && !login.empty() && login.size() <= MAX_CLIENT_PSEUDO)
      return (Authenticator::getArrayFromString(login) == auth.at(id));
  return (false);
}
