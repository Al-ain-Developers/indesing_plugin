//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPageTransitionInfo.h $
//  
//  Owner: DBerggren
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
#ifndef __IPageTransitionInfo_h__
#define __IPageTransitionInfo_h__

#include "IPMUnknown.h"
#include "DynamicDocumentsID.h"

/** 
	This is a persistent interface that sits on a kSpreadBoss, and holds the page transition
	information for the spread. Please use IPageTransitionFacade to extract or to change this 
	information. Changes to this interface are notified by the kSetPageTransitionCmdBoss 
	command, which is broadcasted to the document workspace, as well as each spread being 
	changed.

	@see IPageTransitionFacade, IPageTransition
*/
class IPageTransitionInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGETRANSITIONINFO };

	/** 
	 Gets the ClassID of the page transition. 
	
	 @return ClassID			The classID of the page transition applied to the spread. 
								This will return kInvalidClass if there isn't a page transition applied.
	 */
	virtual ClassID GetPageTransitionID() const = 0;

	/** 
	 Gets the direction of the page transition, as defined by the enum in IPageTransition.
	
	 @return uint32				The direction of the page transition, as defined in the enum in IPageTransition.
	 @see IPageTransition
	 */
	virtual uint32 GetDirection() const = 0;

	/** 
	 Gets the duration of the page transition. Setting is in ticks, where there are 60 ticks per second. 
	
	 @return uint32				The duration of the page transition in ticks (60 ticks per second).
	 */
	virtual uint32 GetDuration() const = 0;

	/** 
	 Sets the ClassID of the page transition. Set to kInvalidClass if no page transition applied.
	
	 @param ClassID				The classID of the page transition applied to the spread. 
	 */
	virtual void SetPageTransitionID(const ClassID& classID) = 0;

	/** 
	 Sets the direction of the page transition, as defined by the enum in IPageTransition.
	
	 @param uint32				The direction of the page transition, as defined in the enum in IPageTransition.
	 @see IPageTransition
	 */
	virtual void SetDirection(uint32 direction) = 0;

	/** 
	 Sets the duration of the page transition. 
	
	 @return uint32				The duration of the page transition in ticks (60 ticks per second).
	 */
	virtual void SetDuration(uint32 duration) = 0;

};

//=============================================================================


#endif // __IPageTransitionInfo_h__

//  IPageTransitionInfo.h.
