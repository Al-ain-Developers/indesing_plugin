//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IMultiColumnTextFrame.h $
//  
//  Owner: dwaterfa
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
//  The IMultiColumnTextFrame interface exists on a kMultiColumnItemBoss.
//  kMultiColumnItemBoss is within a graphic frame (which may be any spline
//  shape).
//  
//  The IMultiColumnTextFrame interface holds information on the relationship
//  between multi column text and the story displayed in the multi column frame
//  item. The children (by IHierarchy) of the IMultiColumnTextFrame are one or
//  more ITextFrameColumn(s).
//  
//========================================================================================

#pragma once
#ifndef __IMultiColumnTextFrame__
#define __IMultiColumnTextFrame__

#include "IPMUnknown.h"
#include "IFrameList.h"
#include "ITextParcelList.h"
#include "TextID.h"
#include "CTextEnum.h"
#include "PMRect.h"
#include "IReferencePointData.h"

class ITextModel;
class PMPoint;
class IdleTimer;
class ITextFrameColumn;
class IStoryOptions;
class IParcel;
class ITextColumnSizer;

/**
	Text support for PageItems. Currently kMultiColumnItemBoss implements this interface.
	kMultiColumnItemBoss is a child of the spline.
	@ingroup text_layout
*/
class IMultiColumnTextFrame : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMULTICOLUMNTEXTFRAME };

	/**
	Returns the TextIndex of the first character in this IMultiColumnTextFrame.
	@returns The TextIndex in the primary story thread where this IMultiColumnTextFrame starts. This value will be >= 0 and <= span of the primary story thread.
	*/
	virtual TextIndex TextStart() const = 0;

	/**
	Returns the number of characters currently composed in the IMultiColumnTextFrame.
	@returns The number of characters currently composed in the IMultiColumnTextFrame.
	*/
	virtual int32 TextSpan() const = 0;

	/**
	Reports which IFrameList this IMultiColumnTextFrame is contained in. Note that for the kMultiColumnItemBoss this will be the IFrameList its children ITextFrames are part of.
	@returns UID of the containing IFrameList.
	*/
	virtual UID GetFrameListUID() const = 0;

	/**
	Reports the IFrameList this IMultiColumnTextFrame is contained in. Note that for the kMultiColumnItemBoss this will be the IFrameList its children ITextFrames are part of.
	@returns A pointer to the containing IFrameList.
	*/
	virtual IFrameList * QueryFrameList() const = 0;

	/**
	Reports which ITextModel this IMultiColumnTextFrame is associated with.
	@returns UID of ITextModel this IMultiColumnTextFrame is associated with.
	*/
	virtual UID GetTextModelUID() const = 0;

	/**
	Reports which ITextModel this IMultiColumnTextFrame is associated with.
	@returns A pointer to the ITextModel this IMultiColumnTextFrame is associated with.
	*/
	virtual ITextModel * QueryTextModel() const = 0;

	/**
	Reports which IStoryOptions this IMultiColumnTextFrame is associated with.
	@returns A pointer to the IStoryOptions this IMultiColumnTextFrame is associated with.
	*/
	virtual IStoryOptions * QueryStoryOptions() const = 0;

	/**
	Adobe internal use only. Do not use.
	Returns a pointer to the first TextFrameColumn child of this
	MultiColumnTextFrame.
	@returns A pointer to our first child.
	*/
	virtual ITextFrameColumn* QueryFrameInFrameList() const = 0;

	/**
	Adobe internal use only. Do not use.
	Returns the UID of the first (or last) TextFrameColumn which is the child
	of this MultiColumnTextFrame.
	@param getLast If kTrue, the UID of the last child ITextFrameColumn of the MultiColumnFrame is returned, otherwise the UID of the first child ITextFrameColumn.
	@returns UID to child ITextFrameColumn.
	*/
	virtual UID GetUIDInFrameList(bool16 getLast = kFalse) const = 0;

	/**
	Determine the closest TextIndex to the specified Pasteboard point.
	NOTE:  If the passed in point is outside the boundary of the frame, this
	method still returns the text index of the closest character.
	@param pPt Point in pasteboard coordinates
	@param composeFirst If kTrue and the Frame requires composition, then the Frame is composed before computing the hit.
	@param nextLine If non-nil and a hit is registered, set to the TextIndex of the next WaxLine.
	@param primarySTOnly If kTrue, then only WaxLines in the Frame are examined. Otherwise the method will burrow into objects such as Tables and Footnotes within the Frame to find the closest hit.
	@returns The TextIndex of the closest character/glyph within the Frame or kInvalidTextIndex if nothing is hit.
	*/
	virtual PMReal HitTestFrame(const PMPoint & pPt, bool16 composeFirst,
								TextIndex *nextLine,
								bool16 primarySTOnly = kTrue) = 0;

	/**
	Sets the baseline offset of the first line in the IMultiColumnTextFrame independent of
	the inset. All columns of the MultiColumnFrame share the same value.
	@param nFirstLineOffset Value to set
	*/
	virtual void SetFirstLineOffsetMetric(Text::FirstLineOffsetMetric nFirstLineOffset) = 0;

	/**
	Gets the baseline offset of the first line in the IMultiColumnTextFrame independent of
	the inset. All columns of the MultiColumnFrame share the same value.
	@returns FirstLineOffsetMetric
	*/
	virtual Text::FirstLineOffsetMetric GetFirstLineOffsetMetric() const = 0;

	/**
	Sets the minimum baseline offset of the first line in the IMultiColumnTextFrame independent of the inset. All columns of the MultiColumnFrame share the same value.
	@param x Non-negative value to set
	*/
	virtual void SetMinFirstLineOffset(PMReal x) = 0;

	/**
	Gets the minimum baseline offset of the first line in the IMultiColumnTextFrame independent of the inset. All columns of the MultiColumnFrame share the same value.
	@returns minFirstLineOffset
	*/
	virtual PMReal GetMinFirstLineOffset() const = 0;

	/**
	Sets the vertical justification in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@param vj Value to set
	*/
	virtual void SetVerticalJustification(Text::VerticalJustification vj) = 0;

	/**
	Gets the vertical justification in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@returns VerticalJustification
	*/
	virtual Text::VerticalJustification GetVerticalJustification() const = 0;

	/**
	Sets the vertical justification maximum inter-paragraph space in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@param maxInterParaSpace Value to set
	*/
	virtual void SetMaxVJInterParaSpace(PMReal maxInterParaSpace) = 0;

	/**
	Gets the vertical justification maximum inter-paragraph space in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@returns maxVJInterParaSpace
	*/
	virtual PMReal GetMaxVJInterParaSpace() const = 0;

	/**
	*/
	virtual void SetVJBalanceColumns(bool16 balanced) = 0;

	/**
	*/
	virtual bool16 GetVJBalanceColumns() const = 0;

	/**
	Sets the auto sizing dimension in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@param asDimension Value to set
	*/
	virtual void SetAutoSizeDimension(Text::AutoSizeDimension asDimension) = 0;

	/**
	Gets the auto sizing dimension in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@returns AutoSizeDimension
	*/
	virtual Text::AutoSizeDimension GetAutoSizeDimension() const = 0;

	/**
	Sets the auto sizing reference point in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@param asRefPoint Value to set
	*/
	virtual void SetAutoSizeRefPoint(IReferencePointData::ReferencePointPosition asRefPoint) = 0;

	/**
	Gets the auto sizing reference point in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@returns AutoSizeRefPoint
	*/
	virtual IReferencePointData::ReferencePointPosition GetAutoSizeRefPoint() const = 0;

	/**
	Sets the auto sizing - has minimum height in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@param asHasMinHeight Value to set
	*/
	virtual void SetAutoSizeHasMinHeight(bool16 asHasMinHeight) = 0;

	/**
	Gets the auto sizing - has minimum height  in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@returns whether the auto sizing has a min height available or not
	*/
	virtual bool16 GetAutoSizeHasMinHeight() const = 0;

	/**
	Sets the auto sizing min height value in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@param asMinHeightValue Value to set
	*/
	virtual void SetAutoSizeMinHeightValue(PMReal asMinHeightValue) = 0;

	/**
	Gets the auto sizing min height value in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@returns AutoSize MinHeightValue
	*/
	virtual PMReal GetAutoSizeMinHeightValue() const = 0;

	/**
	Sets the auto sizing - has minimum width in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@param asHasMinWidth Value to set
	*/
	virtual void SetAutoSizeHasMinWidth(bool16 asHasMinWidth) = 0;

	/**
	Gets the auto sizing - has minimum width in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@returns whether the auto sizing has a min width available or not
	*/
	virtual bool16 GetAutoSizeHasMinWidth() const = 0;

	/**
	Sets the auto sizing min width value in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@param asMinWidthValue Value to set
	*/
	virtual void SetAutoSizeMinWidthValue(PMReal asMinWidthValue) = 0;

	/**
	Gets the auto sizing min width value in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@returns AutoSize MinWidthValue
	*/
	virtual PMReal GetAutoSizeMinWidthValue() const = 0;

	/**
	Sets the auto sizing - has no line break in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@param asNoLineBreak Value to set
	*/
	virtual void SetAutoSizeNoLineBreak(bool16 asNoLineBreak) = 0;

	/**
	Gets the auto sizing - no line break in the IMultiColumnTextFrame. All columns of the MultiColumnFrame share the same value.
	@returns whether there are no line breaks for auto-sizing or not
	*/
	virtual bool16 GetAutoSizeNoLineBreak() const = 0;

	virtual PMRect CalculateNthColumnBBox(int32 n) const = 0;

	/**
	The MultiColumnFrame supports changing its size during composition so it
	fits the available text content. This method says if its is active or not.
	@returns kTrue if fitting should be done during composition, kFalse otherwise
	*/
	virtual bool16	GetIsFittingToContent() const = 0;

	/**
	Reports the state of Text content in the IMultiColumnTextFrame.
	@param optionalIsOnlyLastCR Pointer to bool16 which, if non-nil, will be set to kTrue if the non-emptiness is ONLY due to containing the final CR of the PrimaryStoryThread, kFalse if empty or has other content.
	@returns kTrue if the TextFrame has no content in it. Note that a TextFrame
	with a TextSpan of zero can still have other content such as Footnotes.
	*/
	virtual bool16 GetIsEmpty(bool16* optionalIsOnlyLastCR = nil) const = 0;

	/**
	Reports whether the MultiColumnTextFrame is ignoring all Wraps.
	@returns kTrue if Wraps are ignore, kFalse otherwise.
	*/
	virtual bool16 GetIgnoringTextWrap() const = 0;

	/**
	Complex content such as Tables and Footnotes which are composed into the
	MultiColumnTextFrame can be themselves contain overset TextStoryThreads.
	This only applies to complex content, MultiColumnTextFrames with only simple
	text will never contain overset content.
	@return kTrue if any complex content contains overset.
	*/
	virtual bool16	GetContainsOversetContent() const = 0;

	/**
	This method will return kTrue if this MultiColumnTextFrame represents the
	the last logical MultiColumnTextFrame in the FrameList and any span in the
	Primary Story Thread or related content (such as split Footnotes) is not
	composed into this MultiColumnTextFrame. Note that if only the last CR in
	the Primary Story Thread is overset this method will return kFalse, that is
	NOT overset.
	@return kTrue if overset, kFalse otherwise.
	*/
	virtual bool16	GetIsOverset() const = 0;

	/**
	@return kTrue if this MultiColumnTextFrame manages the only TextFrameColumns in the FrameList
	*/
	virtual bool16		GetIsOnlyMCF() const = 0;

	/**
	@return kTrue if this MultiColumnTextFrame manages the first TextFrameColumn in the FrameList
	*/
	virtual bool16		GetIsFirstMCF() const = 0;

	/**
	@return UID of the previous MultiColumnTextFrame in the FrameList, or kInvalidUID if the MultiColumnTextFrame manages the first TextFrameColumn in the FrameList.
	*/
	virtual UID			GetPreviousMCFUID() const = 0;

	/**
	@return kTrue if this MultiColumnTextFrame manages the last TextFrameColumn in the FrameList
	*/
	virtual bool16		GetIsLastMCF() const = 0;

	/**
	@return UID of the next MultiColumnTextFrame in the FrameList, or kInvalidUID if the MultiColumnTextFrame manages the last TextFrameColumn in the FrameList.
	*/
	virtual UID			GetNextMCFUID() const = 0;

	/**
	@return Index of this MultiColumnTextFrame relative the TextFrameColumns it manages in the FrameList. Returns 0 if GetIsFirstMCF() returns kTrue. Returns -1 if the MultiColumnTextFrame is not part of any FrameList.
	*/
	virtual int32		GetMCFIndex() const = 0;

	/**
	@param whereInMCFCoord
	@return Pointer to IParcel
	*/
	virtual IParcel*	QueryParcelAt(const PMPoint& whereInMCFCoord) const = 0;

	/**
	Changes the FrameList (and story) the MCF is associated with. The MCF will
	be unlinked from it's current FrameList before establishing the new link.
	@param newFrameList Pointer to new IFrameList, or nil to unlink only.
	@param frameListAt This value will be passed to the new FrameList AddFrameAt() method.
	*/
	virtual void		LinkToFrameList(IFrameList* newFrameList,
										int32 frameListAt = IFrameList::kAtTheEnd) = 0;

	/**
	This method will return the width of the variable columns of the called
	MultiColumnTextFrame if the number of columns and gutter width were as
	specified. The resize policy embodied by this is to attempt to keep the
	containing Spline the same size and simply adjust the returned variable
	width as appropriate to achieve this. However, rounding based on grids or
	minimum widths may cause the Spline to grow.
	@param numColums
	@param gutterWidth
	@param insets
	@return computed variable column width
	*/
	virtual PMReal		CalculateVariableColWidthIf(int32 numColumns,
													PMReal gutterWidth,
													const PMRect& insets) const = 0;

	/**
	This method will return an adjusted fixed column width for the called
	MultiColumnTextFrame to fit within the constraints defined by minimum width
	and rounding due to grids.
	@param fixedColWidth
	@return adjusted fixed column width
	*/
	virtual PMReal		CalculateAdjustedFixedColumnWidthIf(PMReal fixedColWidth) const = 0;

	/**
	This method will return an adjusted range column width for the called
	MultiColumnTextFrame to fit within the constraints defined by min and max column
	widths, and will also return a possibly changed number of columns.
	@param mcfWidth, if 0 will use current mcfWidth of the multi-column frame, otherwise will use provided value
	@param gutterWidth
	@param insets
	@param minColWidth (ITextColumnSizer::kMinimumValidInUIColumnWidth)
	@param maxColWidth
	@param [OUT] newNumColumns
	@return adjusted column width
	*/
	virtual PMReal		CalculateAdjustedFlexibleColumnWidthIf(PMReal mcfWidth, PMReal gutterWidth, const PMRect& insets, PMReal minWidth, PMReal maxWidth, int32* newNumColumns) const = 0;

	/**
	This method will adjust the specified width and height for the Spline to
	conform to the internal properties of the MultiColumnTextFrame. For example,
	if the MultiColumnTextFrame is using fixed column sizing then any value
	for the Spline width that does not yield an integral number columns
	(assuming a horizontal story) will be adjusted up appropriately to achieve
	an integral number of column. The underlying MCF must have either an active
	CJKGrid OR fixed column sizing.
	@param ceiling If kTrue, we will ceiling the result, otherwise floor
	@param pAdjWidth Pointer to PMReal with Spline width to adjust - only changed if constrained by the MultiColumnTextFrame.
	@param pWidthConstrained Pointer to bool16 which will be set to kTrue if the MultiColumnTextFrame is constraining the Spline width. If set to kFalse, then pAdjWidth will be unchanged.
	@param pAdjHeight Point to PMReal with Spline height to adjust - only changed if constrained by the MultiColumnTextFrame.
	@param pHeightConstrained Pointer to bool16 which will be set to kTrue if the MultiColumnTextFrame is constraining the Spline height.
	*/
	virtual void		CalculateAdjustedSplineDimensions(bool16 ceiling,
														PMReal* pAdjWidth,
														bool16* pWidthConstrained,
														PMReal* pAdjHeight,
														bool16* pHeightConstrained) const = 0;

	/**
	Adobe internal use only. Will change.
	AnchorCorner 0:top/left, 1:top/right, 2:right/bottom, 3:bottom/left
	*/
	virtual void		GetLayoutProperties(int32* pParentAnchorCorner,
											int32* pMCFAnchorCorner) const = 0;

	/**
	This method is added as an API convenience. Internally it will simply find
	the related IFrameListComposer (on the IFrameList) and call RecomposeUpto()
	which will force all MultiColumnTextFrames upto and including this one to
	be fully composed.
	*/
	virtual void		RecomposeThru() const = 0;

};

#endif
