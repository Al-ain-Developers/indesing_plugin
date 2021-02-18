//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ITrapStyleUtils.h $
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
#ifndef __ITrapStyleUtils__
#define __ITrapStyleUtils__

#include "PrintID.h"
#include "IPMUnknown.h"
#include "Utils.h"


#include "UIDList.h"
#include "K2Vector.h"

//	Forward declarations
class IDocument;
class ITrapStyleListMgr;


/**	An utility interface for trap styles.
*/
class ITrapStyleUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITRAPSTYLEUTILS };

	/**	Returns the trap style list manager for the specified document.
		@param doc is the document.
		@return the document's trap style list manager.
	*/
	virtual ITrapStyleListMgr*	QueryTrapStyleListMgr				(IDocument* doc) = 0;

	/**	Returns the trap style list manager for the specified list UIDRef.
		@param listRef specifies the UIDRef of the trap style list. If UIDRef is UIDRef::gNull
		then the session workspace's trap style list manager is returned.
		@return the specified trap style list manager.
	*/
	virtual ITrapStyleListMgr*	QueryTrapStyleListMgr				(const UIDRef& listRef) = 0;

	/**	Assign the specified trap style to the list of pages.
		@param pageUIDList list of page UIDs.
		@param trapStyleRef is the trap style to assign.
		@return kSuccess if successful otherwise returns an error code.
	*/
	virtual ErrorCode			AssignStyleToPageList				(const UIDList& pageUIDList, UIDRef trapStyleRef) = 0;

	/**	Delete the specified trap styles specified by styleIndexList.
		@param iListMgr is the trap style list manager to use
		@param styleIndexList is the list of styles to delete
		@param doReplacement if set to true, the replacement trap style is assigned to the
		specified page list before deleting the trap styles.
		@param pPageUIDList is the list of page UIDs
		@param pRelacementStyleRef ist he replacement trap style
	*/
	virtual ErrorCode			ReplaceAndDeleteTrapStyles			(ITrapStyleListMgr* iListMgr, K2Vector<int32>& styleIndexList, bool16 doReplacement = kFalse, const UIDList* pPageUIDList= nil, const UIDRef* pReplacmentStyleRef = nil) = 0;

	/**	Get a page list (UIDList) in the specified document whose assigned
		trap style matches the specified trap stye list.
		@param iDoc is the document
		@param styleIndexList is the list of trap styles
		@return a list of pages assigned the specified trap styles.
	*/
	virtual UIDList				GetDocumentTrapStylePageList		(IDocument*, const K2Vector<PMString>&) = 0;

	/**	Build a summary text containing the document's trap style usages.
		@param trapStyleList specifies the list of trap styles
		@param trapstyleUseSummaryText is the string containing the usage information for the specified
		trap styles.
	*/
	virtual void				BuildDocumentPageTrapStyleUsageInfo (IDocument* iDoc, const K2Vector<PMString>& trapStyleList, PMString& trapStyleUseSummaryText) = 0; 

};


#endif	// __ITrapStyleUtils__
