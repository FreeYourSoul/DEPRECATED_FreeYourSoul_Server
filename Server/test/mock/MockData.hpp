//
// Created by FyS on 28/02/18.
//

#ifndef FREESOULS_MOCKDATACLASS_HPP
#define FREESOULS_MOCKDATACLASS_HPP

namespace FSeam {

    struct SessionManagerData {
        uint *addConnection_Ret = nullptr;
        std::string *getConnectionToken_Ret = nullptr;
        std::pair<std::string, ushort> *getConnectionData_Ret = nullptr;
    };

    struct GatewayData {
        bool *isGameServerInstancesHasPositionId_Ret = nullptr;
        fys::gateway::GameServerInstance *getServerForAuthenticatedUser_Ret = nullptr;
    };

}

#endif //FREESOULS_MOCKDATACLASS_HPP
