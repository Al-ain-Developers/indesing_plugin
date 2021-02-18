//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextFrameColumn.h $
//  
//  Owner: Zak_Williamson
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
//  The ITextFrameColumn interface exists on a text frame boss.
//  The text frame boss represents one column of text within a multi-column boss.
//  
//  The ITextFrameColumn interface holds information on the relationship between this column of text and the story
//  displayed in the column.
//  
//========================================================================================

#pragma once
#ifndef __ITextFrameColumn__
#define __ITextFrameColumn__

#include "IPMUnknown.h"
#include "TextID.h"
#include "CTextEnum.h"

class IFrameList;
class IMultiColumnTextFrame;
class IInlineData;
class IStoryOptions;
class ITextModel;
class ParcelKey;
class PMPoint;
class UIDList;

/**
	Text support for PageItems. Currently kFrameItemBoss implements this interface.
	kFrameItemBoss is a child of kMultiColumnItemBoss.
	@ingroup text_layout
*/
class ITextFrameColumn : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTFRAMECOLUMN };

	/**
	Returns a point to the parent MultiColumnTextFrame
	@return Pointer to MultiColumnTextFrame parent
	*/
	virtual IMultiColumnTextFrame*	QueryMultiColumnTextFrame() const = 0;

#ifdef ID_DEPRECATED
	/**
	Returns the TextIndex of the first character in this ITextFrameColumn.
	@returns The TextIndex in the primary story thread where this ITextFrameColumn starts. This value will be >= 0 and <= span of the primary story thread.
	*/
	virtual TextIndex 		TextStart() const = 0;

	/**
	Returns the number of characters currently composed in the ITextFrameColumn.
	@returns The number of characters currently composed in the ITextFrameColumn.
	*/
	virtual int32 			TextSpan() const = 0;
#endif	// ID_DEPRECATED

	/**
	Sets the IFrameList this ITextFrameColumn is contained in.  This method should
	only be called by the methods of IFrameList.
	@param frameListUID UID of the containing IFrameList.
	*/
	virtual void			SetFrameListUID(UID frameListUID) = 0;

	/**
	Reports which IFrameList this ITextFrameColumn is contained in. Note that for the kMultiColumnItemBoss this will be the IFrameList its children ITextFrames are part of.
	@returns UID of the containing IFrameList.
	*/
	virtual UID				GetFrameListUID() const = 0;

	/**
	Reports the IFrameList this ITextFrameColumn is contained in. Note that for the kMultiColumnItemBoss this will be the IFrameList its children ITextFrames are part of.
	@returns A pointer to the containing IFrameList.
	*/
	virtual IFrameList*		QueryFrameList() const = 0;

	/**
	Reports which ITextModel this ITextFrameColumn is associated with.
	@returns UID of ITextModel this ITextFrameColumn is associated with.
	*/
	virtual UID				GetTextModelUID() const = 0;

	/**
	Reports which ITextModel this ITextFrameColumn is associated with.
	@returns A pointer to the ITextModel this ITextFrameColumn is associated with.
	*/
	virtual ITextModel*		QueryTextModel() const = 0;

	/**
	Reports which IStoryOptions this ITextFrameColumn is associated with.
	@returns A pointer to the IStoryOptions this ITextFrameColumn is associated with.
	*/
	virtual IStoryOptions*	QueryStoryOptions() const = 0;

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
	virtual PMReal			HitTestFrame(const PMPoint & pPt,
										bool16 composeFirst,
										TextIndex *nextLine,
										bool16 primarySTOnly = kTrue) = 0;

	/**
	Reports the state of Text content in the ITextFrameColumn.
	@returns kTrue if the TextFrame has no content in it. Note that a TextFrame
	with a TextSpan of zero can still have other content such as Footnotes.
	*/
	virtual bool16			GetIsEmpty() const = 0;

	/**
	Appends to the list the Inlines which claim this TextFrameColumn when
	IInlineData::GetTextFrameRef() is called. Thus by definition only Inlines
	which are properly registered are returned by this call.
	@param childList Reference to UIDList
	*/
	virtual void			GetHierarchyChildren(UIDList& childList) const = 0;

	/**
	Add an Inline as being associated with this TextFrameColumn.
	*/
	virtual void			AddHierarchyChild(const IInlineData* id) = 0;

	/**
	Remove an Inline from being associated with this TextFrameColumn.
	*/
	virtual void			RemoveHierarchyChild(const IInlineData* id) = 0;

};

#endif
