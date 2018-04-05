# FreeYourSoul_Server
MmorpgGame  Server

[Link to the wiki](https://github.com/FreeYourSoul/FreeYourSoul_Server/wiki/FySGateway)

### What is FreeYourSoul Server ?

It is a MMORPG Server of a 2d game.
This server is composed of several different elements. The main one beeing the **Gateway Server**. This server is the entry point of any player. The player is connecting to the gateway server, which request to the **DataServer** (server responsible of the data persistence) to know the spawning position of the player. Thanks to this information the gateway server redirect the player to the correct **WorldServer** (Server responsible of the game movement in a specific part of the MMORPG universe)  
  
WorldServer also has to connect to the gateway server in order to register themselves to it. They also need this connection in order to be notified of the connection of new player to them. they also get notified when another world server connect to the Gateway server and their connections informations are then registered.   
WorldServer are also managing the transition between world servers by notifying the player client to which world server he will have to connect to.

### Configuration File 
The Gateway Server has to be launched by command line.

``
./FreeSouls -c "Configuration File Path"
``

The required flag is the -c, it point on the config file you want to use (config file determine port and others configuration points).
The default file is the one present in the GitHub repo (FreeYourSoul_Server/Server/resource/gateway.ini)
