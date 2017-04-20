//
// Created by FyS on 07/01/17.
//

#include <list>
#include "../include/MasterChunk.hh"

MasterChunk::~MasterChunk() {}

MasterChunk::MasterChunk(const int sizeObj) {
    this->sizeObj = sizeObj;
    this->chunks = new std::list<Chunk*>();
}

MasterChunk *MasterChunk::getInstance(const int sizeObj) {
    if (!instance)
        instance = new MasterChunk(sizeObj);
    return instance;
}
