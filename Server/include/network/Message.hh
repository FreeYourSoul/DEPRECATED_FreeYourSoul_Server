//
// Created by FyS on 23/05/17.
//

#ifndef FREESOULS_MESSAGE_HH
#define FREESOULS_MESSAGE_HH

#include <boost/dynamic_bitset.hpp>

#define BUFFER_SIZE 100

namespace fys {
    namespace network {

        union BitToInt {
            unsigned int integer;
            unsigned char byte[4];
        };

        class Message {
        public:
            ~Message();
            Message();
            Message(unsigned char rawMessage[]);

        private:
            unsigned int byteToInt(unsigned int index);
            unsigned char *intToChar(unsigned int toConvert);

        private:
            unsigned char _rawMessage[BUFFER_SIZE];
        };

    }
}


#endif //FREESOULS_MESSAGE_HH
