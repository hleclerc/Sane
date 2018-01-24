#pragma once

#include "Inst/CanoVal.h"
#include "Inst/KcSI64.h"
#include "Ref.h"
#include <map>

/**
*/
class RessourceMap {
public:
    using MVR = std::map<RcPtr<CanoInst>,RcPtr<Ref>>;

    RessourceMap();
    ~RessourceMap();

    void       get_linked_refs  ( const Ref *ref, const KcSI64 &offset, const KcSI64 &length, const std::function<void(Ref *)> &cb );

    void       on_file_content  ( const CanoVal &fd, const std::function<void(Ref *)> &cb );
    void       on_file_cursor   ( const CanoVal &fd, const std::function<void(Ref *)> &cb );

    void       visit_ext_changes( const std::function<void(Ref *)> &visitor );

private:
    MVR        file_cursors; ///< fd => ressource (representation of the file cursor)
    RcPtr<Ref> file_content;
};


