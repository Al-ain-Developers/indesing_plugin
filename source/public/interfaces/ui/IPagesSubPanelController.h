//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPagesSubPanelController.h $
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
#ifndef __IPagesSubPanelController__
#define __IPagesSubPanelController__

#include "IPMUnknown.h"
#include "PagesPanelID.h"
#include "PMTypes.h"

class PMString;
class IDocument;
class UIDList;
class PMRect;

/**
	Interface that controls the two sub-panels of the pages panel; the observers that 
	watch the document for relevant changes trigger pages panel updates via this interface.
*/
class IPagesSubPanelController : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGESSUBPANELCONTROLLER };

	typedef enum { kNoReasonSpecified, kPageAdded, kSpreadAdded, kPagesPanelPrefsChanged } ReasonForUpdate;

		/** 
			Called to update the pages panel when the active document has changed
			
			@param theNewDoc IDocument pointer of the newly active document (may be nil, when last document is closed)
		*/
	virtual bool16	ActiveDocChange(IDocument *theNewDoc) = 0;

		/** 
			Called to update the pages panel when a page is added (or undeleted)
			
			@param numPages number of pages added
			@param spreadUID spread pages were added to
		*/
	virtual void	AddPageToPanel(int32 numPages, const UIDRef& spreadUID) = 0;

		/** 
			Called to update the pages panel
			
			@param bForceUpdateAll set to true if all page tab widgets should be updated (expensive)
			@param bForcePurge set to true to delete all cached page tab widgets (expensive)
			@param reason why update is being called
		*/
	virtual void	UpdatePagesPanel(	bool16 bForceUpdateAll /*= kFalse*/,
									bool16 bForcePurge /*= kFalse*/, 
									IPagesSubPanelController::ReasonForUpdate reason /*= kNoReasonSpecified*/) = 0;

		/** 
			Called to check the update state of the pages panel
			
			@return set to true if the pages panel has an update pending; false otherwise
		*/
	virtual bool16	IsPanelUpdatePending() = 0;

		/** 
			Called to update the pages panel when a spread has been added
			
			@param spreadList list of added spreads
		*/
	virtual void	AddSpreadToPanel(const UIDList *spreadList) = 0;

		/** 
			Scroll the pages panel to view a particular page or spread
			
			@param spreadUID spread or page uid to scroll into view in the pages panel
		*/
	virtual void	ScrollPanelToSpread(const UIDRef& spreadUID) = 0;

		/** 
			Called when the pages panel is just about to draw. If there is a pending update, this may do a lot of work.
			
			@param updateRgn area that is going to draw
		*/
	virtual void	AboutToDraw(SysRgn updateRgn) = 0;

		/** 
			Gets the bounds of the panorama the pages panel is viewing
			
			@param panoramaRect returned bounds
		*/
	virtual void	GetPanelPanoramaBounds(PMRect *panoramaRect) = 0;

		/** 
			Called when the panel has been resized
		*/
	virtual void	PagesPanelResized() = 0;

		/** 
			Called when the panel is closed - sent when the panel has gone away (hook to free any memory being held)
		*/
	virtual void	PagesPanelClosed() = 0;


		/** 
			Called to invalidate a single spread widget in the pages panel

			@param spreadUID UID of the spread whose widget should be invalidated
		*/
	virtual bool16	InvalidateSpreadWidget(const UIDRef& spreadUID) = 0;

		/** 
			Called to invalidate a single page widget in the pages panel

			@param spreadUID UID of the spread containing the page widget
			@param pageUID UID of the page whose widget should be invalidated
		*/
	virtual bool16	InvalidatePageWidget(const UIDRef& spreadUID, const UIDRef& pageUID) = 0;
};

#endif
