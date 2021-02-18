//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/preflight/IPreflightUIUtils.h $
//  
//  Owner: SusanCL
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
//  Purpose:	Utility functions for Preflight UI Plug-In.
//  
//========================================================================================

#ifndef __PreflightUIUtils__
#define __PreflightUIUtils__

#include "IPMUnknown.h"

#include "PackageAndPreflightUIID.h"

class IDocumentPresentation;


class IPreflightUIUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTUIUTILS };

	/**	Add a preflight UI status widget to the specified document layout window.
		@param layoutPres is the document presentation to add the preflight status widget to.
		@param docRef is the document UIDRef associated with the document layout window.
		@param exccludePopup is true if the associated popup menu should be excluded.
	*/
	virtual void AddPreflightStatusWidget (IDocumentPresentation* layoutPres, const UIDRef& docRef, bool16 excludePopup = kFalse) = 0;
};

#endif	//	__PreflightUIUtils__