//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SchemaBasedIterator.h $
//  
//  Owner: Steve Pellegrin
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Adobe patent application tracking # P409, entitled 'Schema-based file Conversion',
//  inventors: Robin Briggs, Steve Pellegrin
//  
//========================================================================================

#pragma once
#if !defined(__SchemaBasedIterator__)
#define __SchemaBasedIterator__

// ----- Includes -----

#include "CContentIterator.h"


class IPMStream;
namespace Schemas
{
	class Schema;
}
class SchemaBasedIterator;


#ifdef PUBLIC_BUILD
#pragma export on
#endif


//________________________________________________________________________________________
//	SchemaBasedReadIterator
//________________________________________________________________________________________


/**
   This class supports IContentReadIterator in cases when the Class
   or Implementation's data can be described by a schema.
 */

class PUBLIC_DECL SchemaBasedReadIterator : public CContentReadIterator
{
public:
	/** Constructor
	    @param schema IN A const reference to a Schema object that describes the
	    Class or Implementation data.
	    @param s IN An input stream that contains the data.
	*/
	SchemaBasedReadIterator(const Schemas::Schema &schema, IPMStream *s);
	
	/** Destructor
	*/
	virtual ~SchemaBasedReadIterator();

private:
	SchemaBasedIterator	*fIterator;
};


//________________________________________________________________________________________
//	SchemaBasedWriteIterator
//________________________________________________________________________________________

/**
   This class supports IContentWriteIterator in cases when the Class
   or Implementation's data can be described by a schema.
 */

class PUBLIC_DECL SchemaBasedWriteIterator : public CContentWriteIterator
{
public:
	/** Constructor
	    @param s IN An output stream that will contain the data after conversion.
	*/
	SchemaBasedWriteIterator(IPMStream *s);
	
	/** Destructor
	*/
	virtual ~SchemaBasedWriteIterator();

private:
	SchemaBasedIterator	*fIterator;
};


#ifdef PUBLIC_BUILD
#pragma export off
#endif


#endif	// __SchemaBasedIterator__