#pragma once

class KuSI64;
class Ref;

/// assign src[ off_src .. off_src + len ] to dst[ off_dst .. off_dst + len ]
void make_Memcpy( Ref *dst, Ref *src, const KuSI64 &off_dst, const KuSI64 &off_src, const KuSI64 &len );
