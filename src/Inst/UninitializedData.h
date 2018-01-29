#pragma once

class Variable;
class KuSI64;
class Type;


Variable make_UninitializedData( Type *type, const KuSI64 &size, const KuSI64 &alig );
