//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDocumentUIState.h $
//  
//  Owner: lance bushore
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
//  This interface allows the view to get and set information for each window
//  in a document.
//  
//========================================================================================

#pragma once
#ifndef __IDocumentUIState__
#define __IDocumentUIState__

#include "IPMUnknown.h"
#include "PMRect.h"
#include "ILayoutControlData.h"
#include "IOpenLayoutCmdData.h"
#include "IDocumentPresentation.h"
#include "IWindow.h"
#include "ShuksanID.h"

const double kInvalidScrollOffset = -1000000;

class IPresentationList;

/**
	An interface off the document workspace (kDocWorkspaceBoss) that captures the ui state of a document.
	Currently this is only used on layout views in order to save and restore view size, position, scroll location,
	zoom factor, maximize/minimize state, etc when reopening a layout views. 
	Replaces the IDocWindowState.h interface.
	
	All the Set methods in this class are already called automatically in response to window size, zoom, etc events, 
	so they are probably of limited use to third parties.
	@see kDocWorkspaceBoss
	@see IPanorama.h, RestorePerspective
	@see IOpenLayoutWinCmdData.h, SetPerpective
 */
class IDocumentUIState : public IPMUnknown {
	public:
		enum { kDefaultIID = IID_IDOCUMENTUISTATE };

		/**	Return a presentation's view size.
			@return GSysRect frame size 
		 */
		virtual PMRect	GetPresentationFrame() const = 0;
		
		/**	Return the scale factor for a presentation. xScaleFactor and yScaleFactor are generally the same.
			@param IN/OUT xScaleFactor the x scaling factor for this view
			@param IN/OUT yScaleFactor the y scaling factor for this view
			@see GetPresentationCount
		 */
		virtual void	GetScaleFactor_(PMReal& xScaleFactor, PMReal& yScaleFactor) const = 0;

		/**	Set the x and y scale factors for a window. Called in response to zoom changes on the layout window.
			@param xScaleFactor 
			@param yScaleFactor 
			@see GetPresentationCount
		 */
		virtual void	SetScaleFactor_(PMReal& xScaleFactor, PMReal& yScaleFactor) = 0;

		/**	Return the scroll offset for a view.
			@see GetPresentationCount
		 */
		virtual PMPoint	GetScrollOffset() const = 0;

		/**	Set the scroll offset for a view. Called in response to scroll changes on the layout window.
			@param p a PMPoint value representing the offset
		 */
		virtual void	SetScrollOffset(PMPoint& p) = 0;

		/**	Return the 'fit' setting for the window.
			@return the 'fit' setting for the window. 
			@see ILayoutControlData.h for values for FitSetting
		 */
		virtual ILayoutControlData::FitSetting	GetFitSetting() const = 0;

		/**	Set the 'fit' setting for the window. Called in response to zoom changes on the layout window.
			@param fit the new fitting setting
		 */
		virtual void	SetFitSetting(ILayoutControlData::FitSetting fit) = 0;

		/**	Return the visible setting of the window.
			@return VisibleState of the window.
			@see IWindow.h
		 */
		virtual IWindow::VisibleState	GetVisibleSetting() const = 0;

		/**	Return the main monitor rect when the document was saved. Used when reopening a document
			to see if the current monitor is dramatically different than the one in use when the document
			was saved.
			@return the monitor rect this document was saved with. 
			@see IMonitorInfo.h
			@see GetMainScreenRect
		 */
		virtual PMRect	GetSavedMonitorRect() const = 0; 

		/**	Return a presentation's floating vs docked creation pref.
			@return the pref 
		 */
		virtual IDocumentPresentation::CreationParentingPrefs	GetParentingPreferenceForCreation() const = 0;
		
		/**	Capture the ui state for layout views for a document. This is saved persistently so
			when the document is reopened, the zoom factor, fit setting, scroll offset and view size
			are restored. This method is called internally in response to various size, zoom, scroll changes.
			@param *docPresentationList the document's presentation list.
		 */
		virtual void	UpdateUIState(IPresentationList *docPresentationList) = 0;
};


#endif // __IDocWindowState__

