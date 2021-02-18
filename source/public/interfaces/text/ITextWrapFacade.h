//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextWrapFacade.h $
//  
//  Owner: David Stephens
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
#ifndef __ITextWrapFacade__
#define __ITextWrapFacade__

// ----- Interfaces -----

#include "IDocumentLayer.h"
#include "IPMUnknown.h"
#include "ISpread.h"
#include "ISpreadList.h"
#include "IStandOff.h"
#include "IStandOffContourWrapSettings.h"

// ----- Utility files -----

#include "Utils.h"

// ----- ID.h files -----

#include "StandOffID.h"

namespace Facade
{
	/** A high level API for dealing with text wrap.  To use this Facade, include
		this header file and the use the following example syntax:
		theMode = Utils<Facade::ITextWrapFacade>()->GetMode( pageItem );

		@author David Stephens
	*/
	class ITextWrapFacade : public IPMUnknown
	{
	public:

		enum { kDefaultIID = IID_ITEXTWRAPFACADE };
		enum { kUnchanged = 0xFFFF };
		typedef enum {
			kDoNotIgnore = 0,
			kIgnore = 1,
			kLeaveUnchanged
		} IgnoreEnum;

		/**	Description: Get the text wrap mode for the given page item, Document workspace, or the session workspace.
			@param pageItem IN: The UIDRef of the page item we are interested in. 
			Alternatively, you can pass in the UIDRef of the document or session workspace.
			@return  The text wrap mode for the given pageItem.
		 */
		virtual IStandOff::mode	GetMode(const UIDRef& pageItem)  const = 0;

		/** Description: Get whether given page item has a user modified/edited text
			wrap.
			@param pageItem IN: The UIDRef of the page item we are interested in. 
			@return ChangedType - whether or not the given page item has a user-modified path
		*/
		virtual bool32 GetUserModified(const UIDRef& pageItem) const = 0;

		/**	Description: Allows the client to specify a text wrap mode for
			several page items at once, or for the document- or session-workspace.
			@param pageItems IN: The list of page items to which we will apply the text wrap. 
			Alternatively, you can pass in the UIDRef of the document or session workspace.
			@param Mode IN: The text wrap mode to apply.
			@param setUserModified IN: User modified paths become locked such that if the
			geometry (shape) of a page item changes, the text wrap does NOT update to match the
			new geometry.  However, it will continue to move when the page item moves.
			@param doAutoSelect IN: Enable Auto Selecting of most relevant Text Wrap Contour option
			in case Manual Contour is chosen and no previous chosen state exists.
			@return  Any errors or kSuccess if successful.
		 */
		virtual ErrorCode SetMode( const UIDList& pageItems, IStandOff::mode mode,
			bool16 setUserModified = kFalse,
			bool16 doAutoSelect = kFalse ) const = 0;


		/**	Description: Images with a text wrap mode of IStandOff::kManualContour have additional options
			available including using an embedded Photoshop clipping path, performing edge detection on the
			image or on a given alpha channel, wrapping around the image bounds, wrapping around the graphic
			frame which contains the image, or wrapping around whatever is currently clipping the image (either
			a clipping path or the frame itself).
			@param imageItems IN: The list of images to which we will apply the settings (not a list of text wrap items)
			@param contourType IN: The text wrap contour type to apply.
			@param pathIndex IN: If the countourType is kEmbeddedPath then pathIndex
			represents the zero based index of the embedded path to use.
			@param alphaIndex IN: If the countourType is kAlpha, then alphaIndex
			represents the zero based index of the alpha channel to use.
			@param tolerance IN: Edge detection based on the image or an alpha channel occurs in two steps.  The first
			step generates a polygonal path which perfectly matches what InDesign believes is the edge.  Because the
			polygonal path may contain thousands of points, it is smoothed into a bezier path during the second step if
			tolerance is non-zero.  During this smoothing step, the tolerance indicates how closely the resulting path
			must match A value between 0 and 100 which indicates how closely the resulting path must
			match the polygonal path from step 1.
			@param threshhold IN: During edge detection of an image or alpha channel, the source pixels are converted
			to grayscale and then to a 1-bit bitmap.  The threshhold is a value between 0 and 255.  Any gray value
			greater than or equal to the threshold will be mapped to white.  All other pixels will be mapped to black.
			@param allowHoles IN: If kFalse, then all subpaths representing holes will be removed.
			@return  Any errors or kSuccess if successful.
		 */
		virtual ErrorCode SetContourWrapSettings( const UIDList& imageItems, IStandOffContourWrapSettings::ContourWrapType contourType,
					int16 pathIndex,
					int16 alphaIndex,
					PMReal tolerance,
					uint8 threshhold,
					bool8 allowHoles ) const = 0;

		/**	Description: Get the current ContourWrapSettings for a given image, document workspace, or the session workspace.
			@param imageItem IN: The image whose ContourWrapSettings we are interested in obtaining. Note that imageItem
			is not the text wrap item (i.e. not the standoff). 
			Alternatively a UIDRef of the document or session workspace may be used.
			@param contourTypePtr OUT: If non-nil, then the current contour type will be returned.
			@param pathIndexPtr OUT: If non-nil and the contourType is kEmbeddPath, then the zero-based
			index of the path will be returned in this parameter.
			@param alphaIndexPtr OUT: If non-nil and the contourType or kAlpha, then the zero-based
			index of the alpha channel will be returned in this parameter.
			@param tolerancePtr OUT: If non-nil, then the current tolerance value will be returned.
			@param threshholdPtr OUT: If non-nil, then the current threshhold value between 0 and 255 will be returned.
			@param allowHolesPtr OUT: If non-nil, then the current allowHoles setting will be returned.
			@return  Any errors or kSuccess if successful.
		 */
		virtual ErrorCode GetContourWrapSettings( const UIDRef& imageItem, IStandOffContourWrapSettings::ContourWrapType* contourTypePtr,
					int16* pathIndexPtr = nil,
					int16* alphaIndexPtr = nil,
					PMReal* tolerancePtr = nil,
					uint8* threshholdPtr = nil,
					bool8* allowHolesPtr = nil ) const = 0;

		/**	Description: Should the text wrap path be inverted?
			@param textWrapItems IN: The list of text wrap items to which we will apply the bInvert setting. Alternatively a list with the UIDRef of the document or session workspace may be used.
			Alternatively, you can pass in the UIDRef of the document or session workspace.
			@param bInvert IN: kTrue to invert the text wrap.
			@return  Any errors or kSuccess if successful.
		 */
		virtual ErrorCode SetInvert(const UIDList& textWrapItems, bool8 bInvert) const = 0;

		/**	Description: Is the text wrap path inverted?
			@param textWrapItem IN: The text wrap item from which we will get the bInvert setting. 
			Alternatively, you can pass in the UIDRef of the document or session workspace.
			@return  kTrue if the text wrap is user modified, kFalse otherwise.
		 */
		virtual ErrorCode GetInvert(const UIDRef& textWrapItem, bool8& bInvert) const = 0;

		/**	Description: Set the margins (outsets) for text wrap. Use kUnchanged to leave a
			value unchanged.  If a text wrap is non-rectangular, then the topMargin will be applied as
			an outset to the entire path.
			@param textWrapItems IN: The list of text wrap items to which we will apply the margin settings.
			Alternatively, you can pass in the UIDRef of the document or session workspace.
			@param topMargin IN: The top margin. Use kUnchanged to leave current setting unchanged.
			@param leftMargin IN: The left margin. Use kUnchanged to leave current setting unchanged.
			@param bottomMargin IN: The bottom margin. Use kUnchanged to leave current setting unchanged.
			@param rightMargin IN: The right margin. Use kUnchanged to leave current setting unchanged.
			@return  Any errors or kSuccess if successful.
		 */
		virtual ErrorCode SetMargins(const UIDList& textWrapItems, const PMReal& topMargin,
																const PMReal& leftMargin,
																const PMReal& bottomMargin,
																const PMReal& rightMargin) const = 0;

		/**	Description: Get the current margins (outsets) for a given text wrap. Use kUnchanged to leave a
			value unchanged.  If a text wrap is non-rectangular, then the topMargin is applied as
			an outset to the entire path.
			@param textWrapItem IN: The text wrap item from which we will obtain the margin settings. 
			Alternatively, you can pass in the UIDRef of the document or session workspace.
			@param topMargin OUT: The top margin.
			@param leftMargin OUT: The left margin.
			@param bottomMargin OUT: The bottom margin.
			@param rightMargin OUT: The right margin.
			@param singleDistance OUT: Whether the item only supports one value for all sides (i.e. topMargin is the only valid margin)
			@return  Any errors or kSuccess if successful.
		 */
		virtual ErrorCode GetMargins(const UIDRef& textWrapItem, PMReal& topMargin,
																PMReal& leftMargin,
																PMReal& bottomMargin,
																PMReal& rightMargin,
																bool8& singleDistance) const = 0;

		/**	Description: Should a MasterPage based text wrap be active on Spreads that is appears on?
			@param textWrapItems IN: The list of text wrap items to which we will apply the bActive setting. Alternatively a list with the UIDRef of the document or session workspace may be used.
			Alternatively, you can pass in the UIDRef of the document or session workspace.
			@param bActive IN: kTrue to have MasterPage based wrap be active on Spreads in which it appears
			@return Any errors or kSuccess if successful.
		 */
		virtual ErrorCode SetActiveFromMaster(const UIDList& textWrapItems, bool16 bActive) const = 0;

		/**	Description: Is a MasterPage based text wrap active on Spreads that it appears on?
			@param textWrapItem IN: The text wrap item from which we will get the bActive setting. 
			Alternatively, you can pass in the UIDRef of the document or session workspace.
			@return kTrue if the text wrap is user modified, kFalse otherwise.
		 */
		virtual ErrorCode GetActiveFromMaster(const UIDRef& textWrapItem, bool16& bActive) const = 0;

		/**	Description: Allows the client to specify a text wrap side for
			several page items at once, or for the document- or session-workspace.
			@param textWrapItems IN: The list of text wrap items to which we will apply the Side setting. Alternatively a list with the UIDRef of the document or session workspace may be used.
			Alternatively, you can pass in the UIDRef of the document or session workspace.
			@param Side IN: The text wrap side to apply.
			@return Any errors or kSuccess if successful.
		 */
		virtual ErrorCode SetSide(const UIDList& textWrapItems, IStandOff::side Side) const = 0;

		/**	Description: Get the text wrap side for the given page item, Document workspace, or the session workspace.
			@param pageItem IN: The UIDRef of the page item we are interested in. 
			Alternatively, you can pass in the UIDRef of the document or session workspace.
			@return  The text wrap side for the given pageItem.
		 */
		virtual ErrorCode GetSide(const UIDRef& textWrapItem, IStandOff::side& Side) const = 0;

		/**	Description: Should the text wrap be ignored?
			@param ignoreWrapItems IN: The list of MultiColumnTextFrame or parent items to which we will apply the ignore setting.
			Alternatively, you can pass in the UIDRef of the document or session workspace.
			@param bIgnore IN: kTrue to ignore text wrap.
			@return kTrue if the text wrap is user modified, kFalse otherwise.
			@see ITextOptions.h for document and session preferences settings.
		 */
		virtual ErrorCode SetIgnoreWrap(const UIDList& ignoreWrapItems, bool8 bIgnore) const = 0;

		/**	Description: Is the text wrap path currently ignored?
			@param ignoreWrapItem IN: The MultiColumnTextFrame or parent item from which we will get the ignore setting.
			Alternatively, you can pass in the UIDRef of the document or session workspace.
			@return kTrue if text wrap is currently ignored, kFalse otherwise.
			@see ITextOptions.h for document and session preferences settings.
		 */
		virtual ErrorCode GetIgnoreWrap(const UIDRef& ignoreWrapItem, bool8& ignore) const = 0;

		/**	Description: GetSkipByLeadingHeight() returns kTrue if the text tiler will skip down
			by the leading height when an obstruction is encountered.  kFalse will be returned if
			the tiler will skip down 1 point.
			@param workspace IN - the UIDRef of the target workspace.  This UIDRef can be either a
			document workspace or the session workspace.
			@param skipByLeading OUT - kTrue if the tiler will skip by leading height.
			@return ErrorCode - kSuccess if successful, an error otherwise
		 */
		virtual ErrorCode GetSkipByLeadingHeight(const UIDRef& workspace, bool16& skipByLeading) const = 0;

		/**	Description: SetSkipByLeadingHeight() is used to set the tiler behavior when a text
			wrap obstruction is encountered and the tiler needs to move down to find a tile.
			@param workspace IN - the UIDRef of the target workspace.  This UIDRef can be either a
			document workspace or the session workspace.  Changing the session workspace setting
			will cause all new documents to take on the new setting.  Changing the document workspace
			setting changes the setting in only that document.
			@param skipByLeading IN - pass kTrue to make the tiler skip down by the leading height
			when an obstruction is encountered.  Pass kFalse to make the tiler skip down 1 point.  If
			moving down by the leading height, then the next line of text may or may not abut the
			bottom of the obstruction but it will be faster to compose and the lines of text in a
			multi-column text frame are more likely to align.
			@return ErrorCode - kSuccess if successful, an error otherwise
		 */
		virtual ErrorCode SetSkipByLeadingHeight(const UIDRef& workspace, bool16 skipByLeading) const = 0;

		/**	Description: GetZOrderBasedTextWrap() returns kTrue if text wrap only affects items above
			it in the z-order.  kFalse is returned if text wrap affects all text regardless of the
			z-order.
			@param workspace IN - the UIDRef of the target workspace.  This UIDRef can be either a
			document workspace or the session workspace.
			@param zOrder OUT - kTrue indicates z-order based text wrap will be used.
			@return ErrorCode - kSuccess if successful, an error otherwise
		 */
		virtual ErrorCode GetZOrderBasedTextWrap(const UIDRef& workspace, bool16& zOrder) const = 0;

		/**	Description: SetZOrderBasedTextWrap() is used to set whether or not text wrap is z-order
			based.
			@param workspace IN - the UIDRef of the target workspace.  This UIDRef can be either a
			document workspace or the session workspace.  Changing the session workspace setting
			will cause all new documents to take on the new setting.  Changing the document workspace
			setting changes the setting in only that document.
			@param useZOrder IN - pass kTrue to force text wrap items to only affect text which
			is above the text wrap in the z-order.  Pass kFalse to have text wrap affect all text
			regardless of the z-order.
			@return ErrorCode - kSuccess if successful, an error otherwise
		 */
		virtual ErrorCode SetZOrderBasedTextWrap(const UIDRef& workspace, bool16 useZOrder) const = 0;

		/** Description:  When replacing a page item with wrap, either via the Place dialog, relinking an
			image or pasting another page item into the parent frame, we sometimes want to preserve the text
			wrap of the page item that is being replaced.  This method is used to copy the text wrap settings
			from one page item to another.  It also will copy the actual text wrap path if the path was modified
			by the user.
			@param srcPageItem IN:	Notice that this parameter is a const.
			@param dstPageItem IN:	On return, this page item will have the same text wrap settings (if possible) as
									the source.  Sometimes it is not possible to copy the settings.  For example,
									the text wrap on the source may be using an embedded clipping path which does not
									exist in the destination.  In such cases, this routine will get as close as possible.
									For the said example, it will choose "Same As Clipping" instead.
		*/
		virtual void CopyTextWrap(const UIDRef& srcPageItem, const UIDRef& dstPageItem) const = 0;

	};
}

#endif	// __ITextWrapFacade__
