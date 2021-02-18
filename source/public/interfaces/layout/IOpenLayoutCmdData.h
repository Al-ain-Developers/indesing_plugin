//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IOpenLayoutCmdData.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IOpenLayoutCmdData__
#define __IOpenLayoutCmdData__

#include "IPMUnknown.h"
#include "DocumentID.h"
#include "ILayoutControlData.h"
#include "IDocumentPresentation.h"
#include "LayoutUIID.h"

class PMString;
class PMPoint;
class PaletteRef;

/** Data interface for commands that open a layout presentation (kNewWritingPanelCmdBoss and kOpenLayoutCmdBoss).
	Allows you to specify attributes about the  zoom percentage and scroll location, 
	as well as the suggested size of the layout.
*/
class IOpenLayoutPresentationCmdData : public IPMUnknown {
public:
	enum { kDefaultIID = IID_IOPENLAYOUTCMDDATA };

	/**	The suggested size of the layout to be opened. Optional.
		@param bBox suggested bbox of preentation in global system coordinates. 
	 */
	virtual void SetPreferredBounds(const GSysRect& bBox) = 0;

	/**	Retrieve the value from SetPreferredBounds
		@return global sys rect from SetPreferredBounds
	 */
	virtual const GSysRect& GetPreferredBounds() const = 0;
	
	/**	Set various attributes about the layout that will be opened. Generally populated from
		IID_IDOCUMENTUISTATE, IDocumentUIState values from document workspace. Optional.
		@param xScaleFactor X Scaling factor 
		@param yScaleFactor Y Scaling factor (should match x) 
		@param scrollOffset scroll offset as a point in pasteboard coordinates. 
		@param fit the layout "fit" setting from ILayoutControlData. 
	 */
	virtual void SetPerspective_(
			PMReal xScaleFactor,
			PMReal yScaleFactor, 
			PMPoint scrollOffset,
			ILayoutControlData::FitSetting fit) = 0;
	
	/**	Retrieve values from SetPerspective.
		@param xScaleFactor OUT X Scaling factor 
		@param yScaleFactor OUT Y Scaling factor  (should match x) 
		@param scrollOffset OUT scroll offset as a point in pasteboard coordinates. 
		@param fit OUT the layout "fit" setting from ILayoutControlData. 
	 */
	virtual void GetPerspective_(PMReal& xScaleFactor, PMReal& yScaleFactor, PMPoint& scrollOffset, ILayoutControlData::FitSetting& fit) const = 0;

	/**	Set the parenting prefs for creation. Optional. (defaults to user pref setting)
		@param relativeTo for relative parenting prefs, specify the presentation to position relative to
		@param parentGroup for opening a document within a particular group
		@param parentingPrefs see IDocumentPresentation::CreationParentingPrefs for possible values. 
	 */
	virtual void SetParentingPreferenceForCreation(IDocumentPresentation::CreationParentingPrefs parentingPrefs = IDocumentPresentation::kDefaultParentingPref, const IDocumentPresentation* relativeTo = nil, const PaletteRef* parentGroup = nil) = 0;

	/**	Retrieve the suggested floating vs embedded state
		@param relativeTo for relative parenting prefs, returns the presentation to position relative to
		@param parentGroup for parenting prefs, returns the parent group to position the new presentation in
		@return parentingPrefs see IDocumentPresentation::CreationParentingPrefs for possible values 
	 */
	virtual IDocumentPresentation::CreationParentingPrefs GetParentingPreferenceForCreation(const IDocumentPresentation** relativeTo = nil, const PaletteRef** parentGroup = nil) const = 0;
	
	/**	Internal use only: The SetPresentation() method is ONLY to be called by
		OpenLayoutCmd!!! Do not call!!!
		@param IDocumentPresentation* 
	 */
	virtual void SetCommandResult(IDocumentPresentation*) = 0;
	

	/**	Retrieve the resulting presentation after kOpenLayoutCmdBoss is processed.
		@return the newly created presentation. 
	 */
	virtual IDocumentPresentation* GetResultingPresentation() const = 0;
};


#endif
