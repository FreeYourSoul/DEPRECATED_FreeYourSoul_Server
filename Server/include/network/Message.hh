//
// Created by FyS on 23/05/17.
//

#ifndef FREESOULS_MESSAGE_HH
#define FREESOULS_MESSAGE_HH

#include <boost/dynamic_bitset.hpp>
#include <zconf.h>

namespace fys {
    namespace network {

        static const u_int BUFFER_SIZE = 100;

        union BitConvert {
            unsigned int integer;
            unsigned short tBytes[2];
            unsigned char byte[4];
        };

        class Message {
        public:
            ~Message();
            Message();
            Message(unsigned char rawMessage[]);

            const unsigned char *getRawMessage() const;
            unsigned short getOpCode() const;

            std::string &byteToString(std::string &toFill, const unsigned int size, const unsigned int index) const;
            unsigned int byteToInt(unsigned int index) const;

        private:
            void loadOpCode();

        private:
            unsigned char _rawMessage[BUFFER_SIZE];
            unsigned short _opCode;

        };

    }
}


#endif //FREESOULS_MESSAGE_HH
