//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IStateListData.h $
//  
//  Owner: mitch
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
#ifndef __IStateListData__
#define __IStateListData__

#include "IPMUnknown.h"
#include "FormFieldID.h"
#include "FormFieldTypes.h"

/** Used as a parameter interface for command bosses that
    take a list of appearance states as input or output.
*/
class IStateListData : public IPMUnknown
{
  public:
   enum { kDefaultIID = IID_ISTATELISTDATA };

   /** Add a new state to the list, unless the state is already in the list.
	   @param state - the new state to be added
   */
   virtual void Append(Form::AppearanceState state) = 0;

   /** Get the nth state.
	   @param n is the position of the state in the list that you want (must be less than Length)
	   @return the nth state. (if n is out of range, kStateInvalid)
   */
   virtual Form::AppearanceState Get(uint32 n) const = 0;

   /** @return the number of states in the list
   */
   virtual uint32 Length() const = 0;

   /** Clear the list.
	*/
   virtual void Clear() = 0;

};



#endif // __IStateListData__
