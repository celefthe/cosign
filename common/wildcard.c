/*
 * Copyright (c) 2004 Regents of The University of Michigan.
 * All Rights Reserved.  See LICENSE.
 */

#include <stdlib.h>
#include <ctype.h>

#include "wildcard.h"

    int
wildcard( char *wild, char *p, int sensitive )
{
    int		min, max;
    int		i;

    for (;;) {
	switch ( *wild ) {
	case '*' :
	    wild++;

	    if ( *wild == '\0' ) {
		return( 1 );
	    }
	    for ( i = 0; p[ i ] != '\0'; i++ ) {
		if ( wildcard( wild, &p[ i ], sensitive )) {
		    return( 1 );
		}
	    }
	    return( 0 );

	case '<' :
	    wild++;

	    if ( ! isdigit( (int)*wild )) {
		return( 0 );
	    }
	    min = atoi( wild );
	    while ( isdigit( (int)*wild )) wild++;

	    if ( *wild++ != '-' ) {
		return( 0 );
	    }

	    if ( ! isdigit( (int)*wild )) {
		return( 0 );
	    }
	    max = atoi( wild );
	    while ( isdigit( (int)*wild )) wild++;

	    if ( *wild++ != '>' ) {
		return( 0 );
	    }

	    if ( ! isdigit( (int)*p )) {
		return( 0 );
	    }
	    i = atoi( p );
	    while ( isdigit( (int)*p )) p++;

	    if (( i < min ) || ( i > max )) {
		return( 0 );
	    }
	    break;

	case '\\' :
	    wild++;
	default :
	    if ( sensitive ) {
		if ( *wild != *p ) {
		    return( 0 );
		}
	    } else {
		if ( tolower(*wild) != tolower(*p) ) {
		    return( 0 );
		}
	    }
	    if ( *wild == '\0' ) {
		return( 1 );
	    }
	    wild++, p++;
	}
    }
}

    int
is_wildcard( char *p )
{
    for ( ; *p != '\0'; p++ ) {
	switch ( *p ) {
	case '*':
	case '<':
	    return( 1 );
	
	case '\\':
	    p++;
	default:
	    break;
	}
    }

    return( 0 );
}
