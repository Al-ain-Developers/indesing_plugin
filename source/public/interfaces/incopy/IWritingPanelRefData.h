//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IWritingPanelRefData.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IWritingPanelRefData__
#define __IWritingPanelRefData__

#include "IPMUnknown.h"

#include "IWritingPanelRefData.h"

/** 
	This is no longer used although it is still available as of 4.x. It simply stores a UID reference variable
	for later retrieval Recommend using IUIDData instead if you would like to store an uid reference.
	Likely to recommend REMOVAL of this interface in the 5.x timeframe.
*/
class IWritingPanelRefData : public IPMUnknown
{
	public:
		
		/**
			Get stored UID reference
			@return uid reference.
		**/
		virtual UIDRef &GetWritingPanelRef() = 0;
		
		/**
			Save UID reference
			@param writingPanelRef - reference to store
			@return none.
		**/
		virtual void SetWritingPanelRef(UIDRef &writingPanelRef) = 0;
};

#endif 		// __IWritingPanelRefData__