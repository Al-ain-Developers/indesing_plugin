//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DataExchangeHandlerEntry.h $
//  
//  Owner: Dave Burnard
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
//  Handler entry used by clipboard and drag drop
//  
//========================================================================================

#pragma once
#ifndef __DataExchangeHandlerEntry__
#define __DataExchangeHandlerEntry__

#include "PMFlavorTypes.h"

#include "HelperInterface.h"

//========================================================================================
// Class DataExchangeHandlerEntry
//========================================================================================
/** Entry used by CDataExchangeController to maintain an internal list of all data exchange handlers.
		This class is defined in public/includes only because another public header (CDataExchangeController.h) includes it.

		@see CDataExchangeController
*/
class DataExchangeHandlerEntry
{
	// ----- Constructors/desctructors
	public:
		typedef base_type data_type;
		DataExchangeHandlerEntry();
		DataExchangeHandlerEntry(const DataExchangeHandlerEntry& other);
		DataExchangeHandlerEntry(PMFlavor type, ClassID handlerClassId, UID handlerId);

	// ----- Operators
	public:
		DataExchangeHandlerEntry& operator=(const DataExchangeHandlerEntry& other);
		bool16 operator==(const DataExchangeHandlerEntry& other) const;

	// ----- Accessors
	public:
		void					SetHandlerId(UID uid);
		void					SetFlavor(PMFlavor f);
		
		PMFlavor			GetFlavor() const;
		ClassID				GetHandlerClassId() const;
		UID					GetHandlerId() const;

	// ----- Object state
	private:
		PMFlavor					fFlavor;
		ClassID						fHandlerClassId;
		UID							fHandlerId;
}; 


//----------------------------------------------------------------------------------------
// DataExchangeHandlerEntry constructor
//----------------------------------------------------------------------------------------
inline DataExchangeHandlerEntry::DataExchangeHandlerEntry() :
	fFlavor(0),
	fHandlerClassId(kInvalidClass),
	fHandlerId(kInvalidUID)
{
}

inline DataExchangeHandlerEntry::DataExchangeHandlerEntry(const DataExchangeHandlerEntry& other) :
	fFlavor(other.fFlavor),
	fHandlerClassId(other.fHandlerClassId),
	fHandlerId(other.fHandlerId)
{
}

inline DataExchangeHandlerEntry::DataExchangeHandlerEntry(PMFlavor type, ClassID handlerClassId, UID handlerId = kInvalidUID) :
	fFlavor(type),
	fHandlerClassId(handlerClassId),
	fHandlerId(handlerId)
{
}

//----------------------------------------------------------------------------------------
// operator=
//----------------------------------------------------------------------------------------
inline DataExchangeHandlerEntry& DataExchangeHandlerEntry::operator=(const DataExchangeHandlerEntry& other)
{
	if (this != &other)
	{		
		fFlavor = other.fFlavor;
		fHandlerClassId = other.fHandlerClassId;
		fHandlerId = other.fHandlerId;
	}
	
	return *this;
}

//----------------------------------------------------------------------------------------
// operator==
//----------------------------------------------------------------------------------------
inline bool16 DataExchangeHandlerEntry::operator==(const DataExchangeHandlerEntry& other) const
{
	return fFlavor == other.fFlavor && fHandlerClassId == other.fHandlerClassId && fHandlerId == other.fHandlerId;
}

//----------------------------------------------------------------------------------------
// SetHandlerId
//----------------------------------------------------------------------------------------
inline void DataExchangeHandlerEntry::SetHandlerId(UID uid)
{
	fHandlerId = uid;
}

//----------------------------------------------------------------------------------------
// GetFlavor
//----------------------------------------------------------------------------------------
inline PMFlavor DataExchangeHandlerEntry::GetFlavor() const
{
	return fFlavor;
}

//----------------------------------------------------------------------------------------
// SetFlavor
//----------------------------------------------------------------------------------------
inline void DataExchangeHandlerEntry::SetFlavor(PMFlavor f)
{
	fFlavor = f;
}

//----------------------------------------------------------------------------------------
// GetHandlerId
//----------------------------------------------------------------------------------------
inline ClassID DataExchangeHandlerEntry::GetHandlerClassId() const
{
	return fHandlerClassId;
}

//----------------------------------------------------------------------------------------
// GetHandlerId
//----------------------------------------------------------------------------------------
inline UID DataExchangeHandlerEntry::GetHandlerId() const
{
	return fHandlerId;
}

#endif
