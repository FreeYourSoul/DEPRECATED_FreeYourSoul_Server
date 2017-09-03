//
// Created by FyS on 23/05/17.
//

#ifndef FREESOULS_MESSAGE_HH
#define FREESOULS_MESSAGE_HH

#include <boost/dynamic_bitset.hpp>
#include <zconf.h>

namespace fys {
    namespace network {

        enum { MESSAGE_BUFFER_SIZE = 100 };

        union BitConvert {
            unsigned int integer;
            unsigned short tBytes[2];
            unsigned char byte[4];
        };

        class Message {
        public:
            using uptr = std::unique_ptr<Message>;
            using ptr = std::shared_ptr<Message>;
            using wptr = std::weak_ptr<Message>;

            ~Message();
            Message();
            Message(u_char rawMessage[]);

            const u_char *getRawMessage() const;
            u_short getOpCode() const;

            std::string &byteToString(std::string &toFill);
            u_int byteToInt();

        private:
            void loadOpCode();

        private:
            u_int _index;
            u_char _rawMessage[MESSAGE_BUFFER_SIZE];
            u_short _opCode;

        };

    }
}


#endif //FREESOULS_MESSAGE_HH
