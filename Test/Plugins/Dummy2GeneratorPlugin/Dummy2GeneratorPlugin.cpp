//
// Created by nicolasrobert on 3/24/15.
//

#include "Dummy2GeneratorPlugin.h"

#include "Dummy2Generator.h"


Dummy2GeneratorPlugin::Dummy2GeneratorPlugin():
    m_dummyGenerator(AddExtension<Dummy2GeneratorImpl>())
{

}

CREATE_PLUGIN_INSTANCE(Dummy2GeneratorPlugin);

