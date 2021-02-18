//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IStringListData.h $
//  
//  Owner: Yeming Liu
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
#ifndef __ISTRINGLISTDATA__
#define __ISTRINGLISTDATA__

#include "IPMUnknown.h"
#include "CommandID.h"
#include "K2Vector.h"

class PMString;

/**  Data interface for storing a list of strings.
	@ingroup arch_coredata 
*/
class IStringListData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISTRINGLISTDATA };

		/** Set the value of the list of strings.
			@param newList - the list of strings that will be the new value
		*/
		virtual void SetStringList(const K2Vector<PMString>& newList) = 0;

		/** Return the value of the list.
			@return the list of strings 
		*/
		virtual const K2Vector<PMString>& GetStringList() = 0;
    
        /** Adds the input string to the list of strings.
            @param inString - the input string to add to the list of strings
        */
        virtual void Add(const PMString &inString) = 0;

        /** Checks whether the given string exists in the list
            @param inString - the input string to check in the existing list of strings
            @return kTrue - if the input string is present in the existing strings, kFalse otherwise
         */
        virtual bool16 Contains(const PMString& inString) = 0;

        /** Clears the list of strings kept internally
        */
        virtual void Clear(void) = 0;
    
    
};

#endif // __ISTRINGLISTDATA__
