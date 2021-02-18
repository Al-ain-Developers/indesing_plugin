//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ISplitterControlData.h $
//  
//  Owner: Brendan O'Shea
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
#ifndef _ISplitterControlData_
#define _ISplitterControlData_

#include "IPMUnknown.h"
#include "widgetid.h"

/** Interface used in conjunction with the kSplitterWidgetBoss object.
		This interface keeps track of the various widgets controlled by the splitter.
*/
class ISplitterControlData : public IPMUnknown
	{				
	public:
		enum { kDefaultIID = IID_ISPLITTERCONTROLDATA };	
	
		// Get & Set the widget ids of the widgets controlled by this splitter:
		/** Get the number of widgets controlled by this splitter */
		virtual int32		GetNumberOfControlledWidgets() = 0;
	
		/** Get the nth widget controlled by this splitter */
		virtual WidgetID	GetNthControlledWidget(int32 index) = 0;
		/** Set the nth widget controlled by this splitter */
		virtual void		SetNthControlledWidget(int32 index, WidgetID id) = 0;

		/** Get the minimum size of the nth widget controlled by this splitter */
		virtual int32		GetNthMinimumSize(int32 index) = 0;
		/** Set the minimum size of the nth widget controlled by this splitter */
		virtual void		SetNthMinimumSize(int32 index, int32 minSize) = 0;

		/** Get the snap closed size of the nth widget controlled by this splitter */
		virtual int32		GetNthSnapClosedPoint(int32 index) = 0;
		/** Set the snap closed size of the nth widget controlled by this splitter */
		virtual void		SetNthSnapClosedPoint(int32 index, int32 snapPoint) = 0;

		/** Remove the nth widget controlled by this splitter */
		virtual void		RemoveNthControlledWidget(int32 index) = 0;
		/** Add the nth widget controlled by this splitter */
		virtual void		AddNthControlledWidget(int32 index, WidgetID id, int32 minimumSize, int32 snapClosedSize) = 0;
				
		/** Get the orientation of the splitter.
			@return kTrue if the splitter divides top-to-bottom; kFalse otherwise
		*/
		virtual bool16	IsVertical() = 0;

		/** Get the rectangle this splitter will be constrained to */
		virtual PMRect	GetOverallBoundingRect() = 0;
		
	};
	
#endif // _ISplitterControlData_
