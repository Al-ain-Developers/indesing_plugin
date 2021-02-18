//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ICmdCollection.h $
//  
//  Owner: Roey Horns
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
//========================================================================================

#pragma once
#ifndef __ICmdCollection__
#define __ICmdCollection__

#include "IPMUnknown.h"
#include "CommandID.h"

class ICommand;
/**
	Interface for managing collections of commands.
*/
class ICmdCollection : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICMDCOLLECTION };
	
		/** Add the command to the collection.
			NOTE: This interface takes ownership of the reference on addThis!!
		*/
		virtual void Append(ICommand *addThis) = 0;
		/** Add the command to the collection.
			NOTE: This interface takes ownership of the reference on addThis!!
		*/
		virtual void Prepend(ICommand *addThis) = 0;
		
		/** Return the number of sub commands.
		*/
		virtual int32 Length() const = 0;
		
		/** Return a pointer to the n'th sub command.
		*/
		virtual ICommand *GetNthCommand(int32 i) = 0;
		
		/** Make sure that there is enough space for the requested number of items.
		*/
		virtual bool8 Preallocate(int32 newLen) = 0;

		/** Clears the list.
		*/
		virtual void 		Clear() = 0;
};

#endif // __ICmdCollection__
