#pragma once

class CanoVal;

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

CanoVal min       ( const CanoVal &a, const CanoVal &b );
CanoVal max       ( const CanoVal &a, const CanoVal &b );
