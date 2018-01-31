#pragma once

class Variable;
class KuSI64;
class Type;


Variable make_UninitializedData(TypeInSane *type, const KuSI64 &size, const KuSI64 &alig );
