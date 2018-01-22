#pragma once

#include "Value.h"
#include <map>

/**
*/
class RessourceMap {
public:
    using MVR = std::map<Value,RcPtr<Ref>>;

    RessourceMap();
    ~RessourceMap();

    void       get_linked_refs  ( const Ref *ref, const KuSI64 &offset, const KuSI64 &length, const std::function<void(Ref *)> &cb );

    void       on_file_content  ( const Value &fd, const std::function<void(Ref *)> &cb );
    void       on_file_cursor   ( const Value &fd, const std::function<void(Ref *)> &cb );

    void       visit_ext_changes( const std::function<void(Ref *)> &visitor );

private:
    MVR        file_cursors; ///< fd => ressource (representation of the file cursor)
    RcPtr<Ref> file_content;
};


