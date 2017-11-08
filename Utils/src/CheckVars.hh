//
// Created by FyS on 13/07/17.
//

#ifndef FREESOULS_CHECKVARS_HH
#define FREESOULS_CHECKVARS_HH

#include <string>

namespace fys {
    namespace utils {

        class Var {

        public:
            template <typename T, typename...Args>
            static bool check(const T &type, Args...vars) {
                return check(type) && check(vars...);
            }

            template <typename T>
            static bool check(T var) {
                return checkVar(var);
            }

        private:

            template <typename T>
            static bool checkVar(T &) {
                return false;
            }

            static bool checkVar(int var) {
                return (var != -1);
            }

            static bool checkVar(std::string &var) {
                return !var.empty();
            }


        };

    }
}

#endif //FREESOULS_CHECKVARS_HH
