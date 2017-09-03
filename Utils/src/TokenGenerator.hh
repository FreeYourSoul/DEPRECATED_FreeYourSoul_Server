//
// Created by FyS on 03/09/17.
//

#ifndef FREESOULS_TOKENGENERATOR_HH
#define FREESOULS_TOKENGENERATOR_HH

#include <boost/uuid/random_generator.hpp>

namespace fys {
    namespace utils {

        class TokenGenerator {
        public:
            ~TokenGenerator();
            TokenGenerator();

        private:
            boost::uuids::random_generator generator;
        };

    }
}


#endif //FREESOULS_TOKENGENERATOR_HH
