#ifndef DUMMY2GENERATOR_H_
#define DUMMY2GENERATOR_H_
// Created by nicolasrobert on 3/24/15.

#include "Interfaces/INumberGenerator.h"

class Dummy2GeneratorImpl : public plugin::interfaces::INumberGenerator
{
public:
    int GetNumber() override;
};

#endif // DUMMY2GENERATOR_H_

