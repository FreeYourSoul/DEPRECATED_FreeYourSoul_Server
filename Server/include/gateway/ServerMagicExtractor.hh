//
// Created by FyS on 27/01/18.
//

#ifndef FREESOULS_SERVERMAGICEXTRACTOR_HH
#define FREESOULS_SERVERMAGICEXTRACTOR_HH

#include <string>

namespace fys::gateway {

    /**
     * \brief Splitting class for server magic password & positionId of the server
     *
     * This class implement the logic of Magic password for server, the last characters represents the positionId,
     * the others represents the magic code that has to be checked by the authentication server to agree with the
     * server authentication.
     */
    class ServerMagicExtractor {
    public:
        explicit ServerMagicExtractor(const std::string&);

        const std::string &getMagic() const;

        const std::string &getPositionId() const;

    private:
        std::string _magic;
        std::string _positionId;
    };

}


#endif //FREESOULS_SERVERMAGICEXTRACTOR_HH
