#pragma once

class TypeInSane;
class Variable;
class Value;

Variable make_Conv( const Value &orig, TypeInSane *target_type );
