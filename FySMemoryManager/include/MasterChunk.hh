//
// Created by FyS on 07/01/17.
//

#ifndef FREESOULS_MASTERCHUNK_HH
#define FREESOULS_MASTERCHUNK_HH

#include <list>
#include "Chunk.hh"

class MasterChunk {

    ~MasterChunk();
    MasterChunk(const int);

public:
    static MasterChunk *getInstance(const int);

    Chunk   *getAvailableChunk();

private:
    void    addChunk();

private:
    std::list<Chunk*> *chunks;
    int sizeObj;

};

static MasterChunk *instance;

#endif //FREESOULS_MASTERCHUNK_HH