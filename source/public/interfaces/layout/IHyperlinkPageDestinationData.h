//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkPageDestinationData.h $
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
#ifndef __IHyperlinkPageDestinationData__
#define __IHyperlinkPageDestinationData__

#include "IPMUnknown.h"
#include "HyperlinkID.h"
#include "IPDFHyperlinks.h"

/**
	@ingroup layout_hyper
*/
class IHyperlinkPageDestinationData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHYPERLINKPAGEDESTINATIONDATA };

	/**	Initialize all of the parameters at once rather than one at a time
		@param pageUID - Page to point to
		@param zoomPercent - Percentage to use
		@param &zoomRect - Rect to show
		@param destType - View type
	 */
	virtual void	Initialize(const UID pageUID, const PMReal zoomPercent, 
								const PMRect &zoomRect, 
								const IPDFHyperlinks::DestinationType destType) = 0;

	/**	Get the Page this destination points to
		@param none
		@return UID - Page to point to
	 */
	virtual	UID		GetPageUID() const = 0;

	/**	Get the zoom factor this destination uses
		@param none
		@return PMReal - The zoom factor to use
	 */
	virtual	PMReal	GetZoomPercent() const = 0;

	/**	Get the rect that this destination will zoom to
		@param *pmRect - Will be filled with a PMRect
	 */
	virtual	void	GetZoomBBox(PMRect *pmRect) const = 0;

	/**	Get the type of view this destination should use
		@param none
		@return IPDFHyperlinks::DestinationType - View type
	 */
	virtual IPDFHyperlinks::DestinationType	GetZoomType() const = 0;
};


#endif // __IHyperlinkPageDestinationData__

