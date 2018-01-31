#pragma once

#include "../System/Stream.h"
class TypeInSane;

/**
*/
class Reg {
public:
    Reg( TypeInSane *type, int num );

    virtual void write_to_stream( std::ostream &os ) const;

    TypeInSane  *type;
    int          num;
};
