#pragma once

#include "Value.h"
#include <map>

/**
*/
class RessourceMap {
public:
    using MVR = std::map<Value,Ressource>;

    RessourceMap();
    ~RessourceMap();

    void        get_linked_refs( const Ref *ref, const KuSI64 &offset, const KuSI64 &length, const std::function<void(Ref *)> &cb );

    //    void        get_prs_on_file_content( const Value &fd, const std::function<void( Rss * )> &cb );
    //    void        get_prs_on_file_cursor ( const Value &fd, const std::function<void( Rss * )> &cb );

    //    void        visit                  ( std::function<void( Rss *rs )> visitor );

private:
    MVR         file_cursors; ///< fd => ressource (representation of the file cursor)
    Ressource  *file_content;
};


