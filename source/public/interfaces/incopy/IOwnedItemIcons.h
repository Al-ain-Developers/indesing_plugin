//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IOwnedItemIcons.h $
//  
//  Owner: Kevin Van Wiel
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IOwnedItemIcons__
#define __IOwnedItemIcons__

#include "IPMUnknown.h"
#include "ILayoutViewLineData.h"

#include "WritingModeUIID2.h"
#include "UIDRef.h"

class IWaxLine;
class IGraphicsContext;
class LineDescription;
class IGraphicsPort;

/**
	This inteface is used for the detection, drawing and measurement of icons display in story type views for items that have a character
	in the text stream with an associated owned item. Items like xml tags page numbers and other things are displayed using this interface.
*/
class IOwnedItemIcons : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IOWNEDITEMICONS };

		/** Type of owned item icons supported are defined in this enum
   		*/
		enum ItemType {
			/** Table */
			kTable = 0,
			/** Inline text frame or picture frame */
			kInlineFrame,
			/** Hyperlink destination */
			kHyperlink,
			/** Index marker */
			kIndexMarker,
			/** Page number character */
			kTextPageNum,
			/** xml begin tag */
			kXMLBeginTag,
			/** xml end tag */
			kXMLEndTag,
			/** note indicator, used in track change deleted text only */
			kNoteTag,
			/** means no icon */
			kOtherType,
			/** story xml tag */
			kXMLStoryTag,
			/** footnote indicator, used in track change deleted text only */
			kFootnoteTag,
			/** footnote reference number */
			kFootnoteCharacter,
			/**  used to denote endnotes anchor and text range */
			kEndnoteCharacter,
			/** Auto Text character */
			kAutoText,
			/** hidden text marker */
			kHiddenText
		};

		/**
			Figure out if the character is a supported owned item and return it's type if so otherwise return kOtherType.
			for kOtherType there may or may not be an owned item character associated with the character or not. Either way,
			this interface doesn't support icon display for it.
			@param textModelRef - uid ref of the text model
			@param character - character code at the passed in TextIndex (next param). This is mostly to make it quicker to calculate since we typically know the character code already
			@param position - text index to check for an owned item at
			@param storyThreadUID - if the text index is within track change deleted text should pass in a UID for the story thread of the deleted text.
			@return the type of item at the text index
		**/
		virtual ItemType GetItemType(UIDRef textModelRef, UTF32TextChar character, TextIndex position, UID storyThreadUID = kInvalidUID) = 0;

		/**
			Return the width of an icon of ItemType. Should include any extra border space need for the icon. This is the.
			amount of space that will be inserted in the text to draw the icon. It's expected that the caller of this routine
			has already called GetItemType above and knows that an owned item is at the text index provided to this method.
			@param type - type of owned item icon to get width of
			@param textModelRef - uid ref of the text model
			@param position - text index the icon is associated with
			@param storyThreadUID - if the text index is within track change deleted text should pass in a UID for the story thread of the deleted text.
			@return width of the icon to be drawn
		**/
		virtual PMReal GetIconWidth(ItemType type, UIDRef textModelRef, TextIndex position, UID storyThreadUID = kInvalidUID) = 0;

		/**
			Draw an owned item at the given itemRect location. The itemRect width is same as return by GetIconWidth
			and is the height of the line of text the owned item resides in. The draw routine will draw. You may assume,
			the background has already been filled with the current galley background color.
			@param type - type of owned item icon to draw
			@param itemRect - rectangle bounds to draw icon in
			@param textYPosition - yPosition where text is drawn (used for icons that have text draw in combination with them like xml tags)
			@param gPort - port to draw the icon into.
			@param textModelRef - uid ref of the text model
			@param position - text index the icon is associated with
			@param lineIndex - index of the line the icon is being drawn in
			@param storyThreadUID - if the text index is within track change deleted text should pass in a UID for the story thread of the deleted text.
			@return width of the icon to be drawn
		**/
		virtual void Draw(ItemType type, const PMRect &itemRect, PMReal textYPosition, IGraphicsPort *gPort, UIDRef textModelRef,
							TextIndex position, int32 lineIndex, UID storyThreadUID = kInvalidUID) = 0;

};

#endif 		// __IOwnedItemIcons__
