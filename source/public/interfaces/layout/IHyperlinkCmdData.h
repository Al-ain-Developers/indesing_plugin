//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkCmdData.h $
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
#ifndef __IHyperlinkCmdData__
#define __IHyperlinkCmdData__

#include "IPMUnknown.h"
#include "HyperlinkID.h"
#include "IHyperlinkAppearanceData.h"

/** Command data interface associated with commands that modify hyperlinks (kHyperlinkBoss).
	@ingroup layout_hyper
	@see kHyperlinkBoss
	@see IHyperlink
	@see kNewHyperlinkCmdBoss 
	@see kChangeHyperlinkCmdBoss 
	@see kDuplicateHyperlinkCmdBoss 
*/
class IHyperlinkCmdData : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IHYPERLINKCMDDATA};
	
	// General hyperlink characteristics (required):

	/**	Set the required information by calling this single method
		@param &hyperLinkDestination - The destination to point to
		@param name - The name of the hyperlink
	 */
	virtual void Set(	const UIDRef &hyperLinkDestination,
						const PMString *name = nil) = 0;


	/**	Initialize the hyperlink to the standard default appearance
		@param *db - DataBase (to get the UID of the color)
	 */
	virtual void InitializeToDefaultAppearance(IDataBase *db) = 0;


	/**	Set Hyperlink name
		@param name - Name to use
	 */
	virtual void			SetHyperlinkName(const PMString *name = nil) = 0;

	/**	Get Hyperlink name
		@param none
		@return const PMString& - Name of the new hyperlink
	 */
	virtual const PMString&	GetHyperlinkName() const = 0;

	/**	Are we actually changing the name of the hyperlink?
		@param none
		@return bool16 - kTrue == Yes
	 */
	virtual bool16			ChangingHyperlinkName() const = 0;


	/**	Set the hyperlink destination UIDRef
		@param &hyperLinkDestination - UIDRef of the destination
	 */
	virtual void			SetHyperlinkDestination(const UIDRef &hyperLinkDestination) = 0;

	/**	Get the hyperlink destination UIDRef
		@param none
		@return const UIDRef& - UIDRef of the required destination
	 */
	virtual const UIDRef	&GetHyperlinkDestination() const = 0;

	/**	Set the hyperlink destination unique key
		@param uniqueKey - unique key of the destination
	 */
	virtual void			SetHyperlinkDestinationUniqueKey(int32 uniqueKey) = 0;
	/**	Get the hyperlink destination unique key
		@param none
		@return int32 - unique key of the required destination
	 */
	virtual int32			GetHyperlinkDestinationUniqueKey() const = 0;

	/**	Are we actually changing the destination of the hyperlink?
		@param none
		@return bool16 - kTrue == Yes
	 */
	virtual bool16			ChangingHyperlinkDestination() const = 0;

	// Hyperlink Appearance characteristics (optional):

	/**	Set Hyperlink visible rectangle state
		@param bIsVisible - kTrue == Visible rectangle
	 */
	virtual void			SetVisible(const bool16 bIsVisible) = 0;

	/**	Get Hyperlink visible rectangle state
		@param none
		@return bool16 - kTrue == Visible rectangle
	 */
	virtual bool16			GetVisible() const = 0;

	/**	Are we actually changing the visible attribute of the hyperlink?
		@param none
		@return bool16 - kTrue == Yes
	 */
	virtual bool16			ChangingVisibleAttribute() const = 0;


	/**	Set Hyperlink line width
		@param strokeWidthInPixels - 1 == Thin, 2 == Medium, 3 == Thick
	 */
	virtual void			SetBorderLineWidth(const int32 strokeWidthInPixels) = 0;

	/**	Get Hyperlink line width
		@param none
		@return int23  - 1 == Thin, 2 == Medium, 3 == Thick
	 */
	virtual int32			GetBorderLineWidth() const = 0;

	/**	Are we actually changing the border width of the hyperlink?
		@param none
		@return bool16 - kTrue == Yes
	 */
	virtual bool16			ChangingBorderLineWidth() const = 0;


	/**	Set Hyperlink hilight
		@param hilightType - Used for Acrobat
	 */
	virtual void			SetHyperlinkHilight(IHyperlinkAppearanceData::HyperlinkHilight hilightType) = 0;

	/**	Get Hyperlink hilight
		@param none
		@return IHyperlinkAppearanceData::HyperlinkHilight - Used for Acrobat
	 */
	virtual IHyperlinkAppearanceData::HyperlinkHilight	GetHyperlinkHilight() const = 0;

	/**	Are we actually changing the hilight of the hyperlink?
		@param none
		@return bool16 - kTrue == Yes
	 */
	virtual bool16			ChangingHyperlinkHilight() const = 0;
	

	/**	Set Hyperlink border color
		@param interfaceColorUID - UID of color to use in the border
	 */
	virtual void			SetBorderColorUID(const UID interfaceColorUID) = 0;

	/**	Get Hyperlink border color
		@param none
		@return const UID - UID of color to use in the border
	 */
	virtual const UID		GetBorderColorUID() const = 0;

	/**	Are we actually changing the color of the hyperlink?
		@param none
		@return bool16 - kTrue == Yes
	 */
	virtual bool16			ChangingBorderColor() const = 0;


	/**	Set Hyperlink outline line style
		@param style kHyperlinkSolidOutline == solid line, kHyperlinkDashedOutline == dashed line
	 */
	virtual void			SetHyperlinkOutlineLineStyle(IHyperlinkAppearanceData::HyperlinkOutlineLineStyle style) = 0;

	/**	Get Hyperlink outline line style
		@param none
		@return IHyperlinkAppearanceData::HyperlinkOutlineLineStyle kHyperlinkSolidOutline == solid line, kHyperlinkDashedOutline == dashed line
	 */
	virtual IHyperlinkAppearanceData::HyperlinkOutlineLineStyle GetHyperlinkOutlineLineStyle() const = 0;

	/**	Are we actually changing the outline line style of the hyperlink?
		@param none
		@return bool16 - kTrue == Yes
	 */
	virtual bool16			ChangingHyperlinkOutlineLineStyle() const = 0;

	/** Set hyperlink destination file missing flag
		@param fileMising - kTrue if file is missing, kFalse otherwise.
	*/
	virtual void 			SetFileMissing(bool16 fileMissing) = 0;
	/** Get hyperlink destination file missing flag
		@return bool16
	*/
	virtual bool16			GetFileMissing() const = 0;
	/** Are we actually changing the hyperlink destination file missing flag?
		@return bool16 - kTrue = Yes
	*/
	virtual bool16			ChangingFileMissing() const = 0;
	
	/**	Is this from a duplicate command.
		@return bool16 kTrue is we are creating a new text destination from a dupplicate command.
	 */
	virtual bool16 			IsFromDuplicate() const = 0;
	/**	Set whether it is from a duplicate command.
		@param fromDup - kTrue if from duplicate command.
	 */
	virtual void 			SetFromDuplicate(bool16 fromDup) = 0;

	/** Are we actually changing the hyperlink altenate text?
	@return bool16 - kTrue = Yes
	*/
	virtual bool16			ChangingHyperlinkAltText() const = 0;

	/** Set Hyperlink alternate text.
		@param altText - Alternate text of hyperlink.
	*/
	virtual void			SetHyperlinkAltText(const PMString altText) = 0;

	/**	Get Hyperlink alternate text.
		@param none
		@return const PMString - Alternate text of hyperlink
	*/
	virtual const PMString		GetHyperlinkAltText() = 0;

};


#endif // __IHyperlinkCmdData__

