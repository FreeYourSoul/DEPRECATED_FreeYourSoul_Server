//
// Created by FyS on 23/05/17.
//

#ifndef FREESOULS_MESSAGE_HH
#define FREESOULS_MESSAGE_HH

#include <boost/dynamic_bitset.hpp>

#define BUFFER_SIZE 100

namespace fys {
    namespace network {

        union BitConvert {
            unsigned int integer;
            unsigned short tbytes[2];
            unsigned char byte[4];
        };

        class Message {
        public:
            ~Message();
            Message();
            Message(unsigned char rawMessage[]);

        private:
            void loadOpCode();

            unsigned int byteToInt(unsigned int index);
            unsigned char *intToChar(unsigned int toConvert);

        private:
            unsigned char _rawMessage[BUFFER_SIZE];
            unsigned short _opCode;
        };

    }
}


#endif //FREESOULS_MESSAGE_HH
