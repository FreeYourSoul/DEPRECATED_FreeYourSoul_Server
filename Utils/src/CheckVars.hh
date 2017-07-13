//
// Created by FyS on 13/07/17.
//

#ifndef FREESOULS_CHECKVARS_HH
#define FREESOULS_CHECKVARS_HH

#include <string>

namespace fys {
    namespace utils {

        template <typename T, typename...Args>
        bool checkVars(std::string &type, Args...vars) {
            if (type.empty())
                return false;
            return checkVars(vars);
        }

        template <typename T>
        bool checkVars(T var) {
            return checkVar(var);
        }

        template <std::string>
        bool checkVar(std::string &var) {
            return !var.empty();
        }

        template <int>
        bool checkVar(int var) {
            return (var != -1);
        }

        template <typename T>
        bool checkVar(std::string &var) {
            return false;
        }

    }
}

#endif //FREESOULS_CHECKVARS_HH
