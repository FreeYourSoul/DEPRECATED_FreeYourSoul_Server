//
// Created by FyS on 21/01/18.
//

#ifndef FREESOULS_FYSMOCK_HPP
#define FREESOULS_FYSMOCK_HPP

#include <boost/range/size.hpp>
#include <map>

namespace fys::testing {

    class Mock {

    public:
        constexpr void addCallFor(const std::string& methodName) const {
            std::size_t numberOfCall = 0;

            if (_called.find(methodName) == _called.end())
                numberOfCall = 0;
            else
                numberOfCall = _called.at(methodName);
            _called[methodName] = ++numberOfCall;
        }

        constexpr std::size_t methodCalled(const std::string& methodName) const {
            if (_called.find(methodName) == _called.end())
                return (0);
            return _called.at(methodName);
        }

    protected:
        std::map<std::string, std::size_t> _called;

    };

}

#endif //FREESOULS_FYSMOCK_HPP
