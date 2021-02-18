//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkAppearanceData.h $
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
#ifndef __IHyperlinkAppearanceData__
#define __IHyperlinkAppearanceData__

#include "IPMUnknown.h"
#include "HyperlinkID.h"

/**
	@ingroup layout_hyper
*/
class IHyperlinkAppearanceData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IHYPERLINKAPPEARANCEDATA };

	/**	Set whether this hyperlink is visible in the layout window
		@param bIsVisible - kTrue == Visible
	 */
	virtual void							SetVisible(const bool16 bIsVisible) = 0;

	/**	Get whether this hyperlink is visible in the layout window
		@param none
		@return bool16 - kTrue == visible
	 */
	virtual bool16							GetVisible() const = 0;


	/**	Set the thickness of the border of the hyperlink
		@param strokeWidthInPixels - 1 == thin, 2 == medium, 3 == thick
	 */
	virtual void							SetBorderLineWidth(const int32 strokeWidthInPixels) = 0;

	/**	Get the thickness of the border of the hyperlink
		@param none
		@return int32 - Thickness in pixels
	 */
	virtual int32							GetBorderLineWidth() const = 0;

	typedef enum {	kNoHyperlinkHilight = 0, 
					kInvertHyperlinkHilight = 1, 
					kInsetHyperlinkHilight = 2, 
					kOutlineHyperlinkHilight = 3} HyperlinkHilight;


	/**	Set the hilight style
		@param hilightType - The hilight style (This only matters when the file is exported to PDF
	 */
	virtual void							SetHyperlinkHilight(IHyperlinkAppearanceData::HyperlinkHilight hilightType) = 0;

	/**	Get the hilight style
		@return HyperlinkHilight - The hilight style (This only matters when the file is exported to PDF
	 */
	virtual HyperlinkHilight				GetHyperlinkHilight() const = 0;


	/**	Set the color of the hyperlink border
		@param interfaceColorUID - UID of the UI color to use
	 */
	virtual void							SetBorderColorUID(const UID interfaceColorUID) = 0;

	/**	Get the color of the hyperlink border
		@param none
		@return const UID - UID of the UI color to use
	 */
	virtual const UID						GetBorderColorUID() const = 0;

	typedef enum {	kHyperlinkSolidOutline = 0,
					kHyperlinkDashedOutline = 1 } HyperlinkOutlineLineStyle;


	/**	Set the outline style
		@param style - kHyperlinkSolidOutline == solid line, kHyperlinkDashedOutline == dashed line
	 */
	virtual void							SetHyperlinkOutlineLineStyle(HyperlinkOutlineLineStyle style) = 0;

	/**	Get the outline style
		@param none
		@return HyperlinkOutlineLineStyle - Style to use
	 */
	virtual HyperlinkOutlineLineStyle		GetHyperlinkOutlineLineStyle() const = 0;
};

#endif
