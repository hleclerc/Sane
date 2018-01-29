#pragma once

class CanoVal;

CanoVal make_CanoAdd       ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoSub       ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoMul       ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoDiv       ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoDivInt   ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoMod       ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoInf       ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoSup       ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoInfEqu    ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoSupEqu    ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoEqu       ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoNotEqu    ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoOrLogical ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoAndLogical( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoOrBitwise ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoAndBitwise( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoXorBitwise( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoShiftRight( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoShiftLeft ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoMin       ( const CanoVal &a, const CanoVal &b );
CanoVal make_CanoMax       ( const CanoVal &a, const CanoVal &b );

CanoVal operator+ ( const CanoVal &a, const CanoVal &b );
CanoVal operator- ( const CanoVal &a, const CanoVal &b );
CanoVal operator* ( const CanoVal &a, const CanoVal &b );
CanoVal operator/ ( const CanoVal &a, const CanoVal &b );

CanoVal operator% ( const CanoVal &a, const CanoVal &b );
CanoVal operator< ( const CanoVal &a, const CanoVal &b );
CanoVal operator> ( const CanoVal &a, const CanoVal &b );
CanoVal operator<=( const CanoVal &a, const CanoVal &b );
CanoVal operator>=( const CanoVal &a, const CanoVal &b );
CanoVal operator==( const CanoVal &a, const CanoVal &b );
CanoVal operator!=( const CanoVal &a, const CanoVal &b );
CanoVal operator||( const CanoVal &a, const CanoVal &b );
CanoVal operator&&( const CanoVal &a, const CanoVal &b );
CanoVal operator| ( const CanoVal &a, const CanoVal &b );
CanoVal operator& ( const CanoVal &a, const CanoVal &b );
CanoVal operator^ ( const CanoVal &a, const CanoVal &b );
CanoVal operator<<( const CanoVal &a, const CanoVal &b );
CanoVal operator>>( const CanoVal &a, const CanoVal &b );
CanoVal min       ( const CanoVal &a, const CanoVal &b );
CanoVal max       ( const CanoVal &a, const CanoVal &b );
