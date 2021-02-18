//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISelectUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __ISelectUtils__
#define __ISelectUtils__

#include "AppFrameworkID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "IShape.h"
#include "PMRect.h"
#include "PathSelectionList.h"
#include "HitTestDragConstants.h"
#include "ISelectionMessages.h"

class ICommand;
class UIDList;
class ITextFocus;
class IFocusCache;
class IPMUnknown;
class IUIDListData;
class RangeData;
class ISelectionManager;



#ifdef ID_DEPRECATED
/** This class is obsolete. Do not use.
*/
class ISelectUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISELECTUTILS };

	// These 2 will go away when Shawn unifies the TextSelectionSuite

#if 0
	/** Obsolete.
	*/
	virtual ICommand* SelectTextRange( const UIDRef& model, const RangeData& rangeToSelect,
	                                  //if doScroll is kScrollIntoView and scrollSpot is nil then scrollSpot defaults to MidPoint(rangeToSelect)
	                                  Selection::ScrollChoice doScroll, const RangeData* scrollSpot,
	                                  //if selMgr is non-nil, then view is ignored
	                                  //if selMgr is nil, then the view's selMgr is used,
	                                  //if view is nil, then the session's active selMgr is used for now--later I'll assert.
	                                  ISelectionManager* selMgr, IControlView* view
                                     ) = 0;
#endif

	/** Obsolete.
	*/
	virtual ErrorCode ProcessSelectText( const UIDRef& model, const RangeData& rangeToSelect,
	                                  Selection::ScrollChoice doScroll, const RangeData* scrollSpot,
	                                  ISelectionManager* selMgr, IControlView* view 
                                     ) = 0;

	/** Obsolete.
	*/
	virtual void GoToTextWithMarker(UIDRef &textStory, TextIndex nStart, int32 nnCount) = 0;
	                
};

#endif // ID_DEPRECATED

#endif	// __ISelectUtils__
