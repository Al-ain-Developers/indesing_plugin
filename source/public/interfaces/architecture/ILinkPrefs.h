//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILinkPrefs.h $
//  
//  Owner: Michael Easter
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
//  Description:
//  This class defines an interface used to store and access link related preferences.
//  
//========================================================================================

#pragma once
#ifndef __ILinkPrefs__
#define __ILinkPrefs__

// ----- Includes -----
#include "IPMUnknown.h"
#include "LinksID.h"


/**
 ILinkPrefs is used to store and access preferences that specify the behavior InDesign in
 regards to links when a document is opened.

 @see ILink
 @see ILinkResource
 */
class ILinkPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKPREFS };

	/** Set the "Check Links Before Opening Document" preference.\\
		The preference specifies whether the state of a document's links
		should be updated during the open document operation.  If kTrue,
		all the links in the document will be updated when the document
		opens.  If any links have an out-of-date state, the user will be
		prompted to update the out-of-date links. */
	virtual void SetCheckLinksOnOpen(bool16 bCheckLinksOnOpen) = 0;
	/** Get the "Check Links Before Opening Document" preference. */
	virtual bool16 GetCheckLinksOnOpen() const = 0;

	/** Set the "Auto-find Missing Links Before Opening Document" preference.\\
		The preference specifies whether InDesign should automatically try to
		resolve a document's missing links during the open document operation.
		If kTrue, an attempt will be made to automatically resolve missing links
		when the document opens.  The "Auto-find Missing Links Before Opening
		Document" preference is ignored if the "Check Links Before Opening Document"
		is set to kFalse. */
	virtual void SetFindMissingLinksOnOpen(bool16 bFindMissingLinksOnOpen) = 0;
	/** Get the "Auto-find Missing Links Before Opening Document" preference. */
	virtual bool16 GetFindMissingLinksOnOpen() const = 0;
};

#endif //__ILinkPrefs__

