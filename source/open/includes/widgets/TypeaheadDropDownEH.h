//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/TypeaheadDropDownEH.h $
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
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __TypeaheadDropDownEH__
#define __TypeaheadDropDownEH__

#include "DVControlEventHandler.h"
#include "PMString.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

/******************************************************************************
 * class - TypeaheadDropDownEH code pulled from now obsolete and deleted WTypeaheadDropDownEH
 ******************************************************************************/
class WIDGET_DECL TypeaheadDropDownEH : public DVControlEventHandler
{
	typedef DVControlEventHandler inherited;
	
public:
	TypeaheadDropDownEH(IPMUnknown *boss);
	virtual ~TypeaheadDropDownEH();
	
	virtual bool16 KeyDown(IEvent* e);
	
	virtual bool16 CanHaveKeyFocus() const;
	
	virtual bool16 WantsTabKeyFocus() const;

protected:
	bool16 HandleTypeAhead(IEvent* e);

	int32 fLastCharTime;

	static const int32 fkTimeOutPeriod;
	static const int32 fkInvalidIndex;

	// Match all the chars typed against the list. If the last typed
	// char doesn't produce a match, ignore it.  -- i.e. typing "cou"
	// will match courier in the list "cat courier dog". Typing "coud"
	// ignores the "d". Nothing else changes.

	PMString fTypedChars;

	bool16	timedOut()
	{
#ifdef WINDOWS
		int32 now = ::GetTickCount();
#endif
#ifdef MACINTOSH
		int32 now = SystemUtils::TickCount() * 10;
#endif

		int32 timeDiff = now - fLastCharTime;
		fLastCharTime = now;

		if (timeDiff > fkTimeOutPeriod)
		{
			TRACEFLOW_OBSOLETE("Old:WidgetBin", "TypeaheadDropDownEH timed-out - clearing state.\n");
			return true;
		}

		return false;
	}
};

#pragma export off

#endif
