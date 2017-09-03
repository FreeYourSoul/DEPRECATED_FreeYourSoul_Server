//
// Created by FyS on 03/09/17.
//

#ifndef FREESOULS_RESPONSEMESSAGE_HH
#define FREESOULS_RESPONSEMESSAGE_HH


#include <string>
#include <zconf.h>
#include <vector>
#include <Message.hh>

namespace fys {
    namespace network {

        class ResponseMessage {
        public:
            ~ResponseMessage();
            ResponseMessage();

            const Message::uptr generateResponse();

            u_short get_opCode() const;
            const std::vector<char> &get_token() const;
            const std::vector<std::string> &get_listStrings() const;
            const std::vector<int> &get_listIntegers() const;
            void set_opCode(u_short _opCode);
            void set_token(const std::vector<char> &_token);

        private:
            u_short _opCode;
            std::vector<char> _token;
            std::vector<std::string> _listStrings;
            std::vector<int> _listIntegers;
        };

    }
}

#endif //FREESOULS_RESPONSEMESSAGE_HH
