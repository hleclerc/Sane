#pragma once

#include "../System/TypeConfig.h"
class IiValue;

/**
  In inst KuSI64 (where ressources are replace by indices)
*/
class IiKuSI64 {
public:
    IiKuSI64() : uv( 0 ) {}
    ~IiKuSI64();

    bool     is_known() const { return uv == 0; }

    IiValue *uv;
    SI64     kv; ///< known value (is uv == 0)
};
