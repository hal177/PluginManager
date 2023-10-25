#ifndef DUMMYGENERATORPLUGIN_H_8817B948_9744_4778_83CF_730F6E67BC08
#define DUMMYGENERATORPLUGIN_H_8817B948_9744_4778_83CF_730F6E67BC08

//
// Created by nicolasrobert on 3/24/15.
//

#include "StdPluginLib.h"
#include "IPluginLib.h"

#include <memory>

class Dummy2GeneratorImpl;

class Dummy2GeneratorPlugin : public plugin::StdPluginLib
{
public:
    Dummy2GeneratorPlugin();
private:
    std::shared_ptr<Dummy2GeneratorImpl> m_dummyGenerator;
};

#endif // DUMMYGENERATORPLUGIN_H_8817B948_9744_4778_83CF_730F6E67BC08

