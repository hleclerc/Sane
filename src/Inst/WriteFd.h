#pragma once

class Variable;

void make_WriteFd( const Variable &fd, const Variable &ptr, const Variable &len );
void make_WriteFd( const Variable &fd, const Variable &val );
