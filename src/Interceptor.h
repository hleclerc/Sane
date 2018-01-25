#pragma once

#include "Ref.h"
#include <map>

/**
*/
class Interceptor {
public:
    struct ValueChange {
        Ressource o; ///< old value
        Ressource n; ///< new value
    };
    struct Break {
        size_t nb_l; ///< 2 * ( nb_loops - 1 ) + is_a_break
        size_t date;
        Value  cond;
    };

    using MapRVC = std::map<RcPtr<Ref>,ValueChange>;

    void       run( const std::function<void()> &func );

    PI64       inter_date;
    MapRVC     mod_refs;
    Vec<Break> breaks;
};

