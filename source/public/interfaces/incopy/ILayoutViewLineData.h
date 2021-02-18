//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ILayoutViewLineData.h $
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
#ifndef __ILayoutViewLineData__
#define __ILayoutViewLineData__

#include "IPMUnknown.h"

#include "WritingModeID.h"
#include "UIDRef.h"

class IDataBase;

/** 
	This interface is added to each wax line in layout view to give it an id to associate with a corresponding
	text line in the galley view. This enables the two views to be kept in sync. The method FindIndexOfLineWithID()
	in ITextLines can be used to locate a line in the galley view corresponding to a waxline in layout view.
	Note this only applies to galley view. Story view does not need to know this information and it is not maintained.
*/
class ILayoutViewLineData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ILAYOUTVIEWLINEDATA };
		
		/**
			Used internally DO NOT CALL.
			@param docDB - document database.
			@return none
		**/
		virtual void GenerateNewLineID(IDataBase *docDB) = 0;
		
		/**
			Get a line id for this wax line
			@return line id value
		**/
		virtual uint32 GetLineID() = 0;
		
		/**
			Used internally DO NOT CALL.
			@return none
		**/
		virtual void InvalidateID() = 0;
		
		/**
			Directly set a waxline id. Needed for undo support in CS3 and beyond.
			@param id value to set line date to
			@return none
		**/
		virtual void SetLineID(uint32 id) = 0;
};

#endif 		// __ILayoutViewLineData__