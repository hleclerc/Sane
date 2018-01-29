#pragma once

class Variable;
class Value;
class Type;

Variable make_Conv( const Value &orig, Type *target_type );
