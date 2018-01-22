#pragma once

#include "IiRessource.h"
#include "IiKuSI64.h"

/**
  In inst ressource with offset
*/
class IiRessourceWithOffset {
public:
    IiRessource ressource; ///<
    IiKuSI64    offset;    ///<
};
