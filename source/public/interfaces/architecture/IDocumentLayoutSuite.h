//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDocumentLayoutSuite.h $
//  
//  Owner: Michael Martz
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
//  Note:
//  
//========================================================================================

#pragma once
#ifndef _IDocumentLayoutSuite_
	#define _IDocumentLayoutSuite_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "ShuksanID.h"
	#include "ILayoutControlData.h"
//================================================================================================
//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
class IDocumentLayoutSuite : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IDOCUMENTLAYOUTSUITE };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		/**	Notification to the various selection bosses that the layout of the document has changed.
			In particular, this is invoked when a page or spread is added, deleted, or moved. The layoutselection
			uses this to remove items from the selection that are selected but not on the "current" spread. Text
			ignores this, as it is valid to have a text selection on an inactive page.
			@param ILayoutControlData - which layout window we are talking about ("current" spread is per view) 
			@return ErrorCode (currently always kSuccess)
		 */
		virtual ErrorCode DocumentLayoutChanged (ILayoutControlData *lcd) = 0;

	};

#endif // _IDocumentLayoutSuite_