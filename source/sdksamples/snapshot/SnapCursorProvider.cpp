//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/SnapCursorProvider.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

#include "SnapID.h"
#include "CToolCursorProvider.h"

/** SnapCursorProvider
	implements a cursor provider for toolbox SnapShot tool.
  
	
	@ingroup snapshot
*/
class SnapCursorProvider : public CToolCursorProvider
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		SnapCursorProvider( IPMUnknown* boss ) 
			: CToolCursorProvider(boss) {}

		/** 
			Destructor.
		*/
		~SnapCursorProvider() {}

		/**
			It is called when mouse enters a region assigned to this provider. 
			It returns the CursorSpec describing the cursor to be displayed. 
			Default behavior: returns kCrsrPointer.
		*/		
		virtual CursorSpec	GetCursor(IControlView* viewUnderMouse, const SysPoint globalMouse, ICursorMgr::eCursorModifierState modifiers) const;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(SnapCursorProvider, kSnapCursorProviderImpl )


/* GetCursor
*/
CursorSpec SnapCursorProvider::GetCursor(IControlView* viewUnderMouse, const SysPoint globalMouse, ICursorMgr::eCursorModifierState modifiers) const
{
	CursorSpec defaultCursor = CToolCursorProvider::GetCursor(viewUnderMouse, globalMouse, modifiers);
	if (defaultCursor.GetID() != kCrsrNone)
		return defaultCursor;

	return CursorSpec(kSnapPluginID, kCursorSnapResourceID);
}

// End, SnapCursorProvider.cpp.


