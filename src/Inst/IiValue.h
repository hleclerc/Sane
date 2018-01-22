#pragma once

#include "IiRessource.h"
#include "IiKuSI64.h"
class Type;

/**
  In inst Value (where ressources are replace by indices)
*/
class IiValue {
public:
    IiRessource ressource;
    IiKuSI64    offset;
    IiKuSI64    length;
    Type       *type;
};
