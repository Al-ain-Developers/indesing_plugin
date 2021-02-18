//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IAnchoredObjectInsertData.h $
//  
//  Owner: Eric Menninga
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
#ifndef __IANCHOREDOBJECTINSERTDATA__
#define __IANCHOREDOBJECTINSERTDATA__

#include "IPMUnknown.h"
#include "TextID.h"


/**
	IAnchoredObjectInsertData is an interface used to store the properties used when creating anchored objects.
	Used by both the CreateAnchoredObjectCmd and also defaults, this interface stores information
	about the size, what kind of object, and some intitial properties when created anchored pageitems automatically.

	@see IAnchoredObjectData
	@ingroup text_layout
*/
class IAnchoredObjectInsertData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IANCHOREDOBJECTINSERTDATA };

	/** the initial inserted object's content types */
	typedef enum { kTextFrame, kGraphicFrame, kUnassignedFrame } AnchoredContent;

	/** used by the ChangeAnchoredObjectCmd's IIntData interface to control which fields to set by the command */
	enum { kCmdSelector_Content = 0x01, kCmdSelector_ObjectStyle = 0x02, kCmdSelector_ParaStyle = 0x04,
			kCmdSelector_Height = 0x08, kCmdSelector_Width = 0x010 };

	/** When inserting an anchored object automatically, which type of object should be inserted?
		@param content is the type of object to insert: text frame, graphic frame, unassigned frame.
	*/
	virtual void SetInitialContent(IAnchoredObjectInsertData::AnchoredContent content) = 0;
	/** Get the type of content that will be inserted.
		@return the content type.
	*/
	virtual IAnchoredObjectInsertData::AnchoredContent GetInitialContent() const = 0;

	/** Set the object style to be applied to the inserted object.
		@param styleID is the object style to apply.
	*/
	virtual void SetInitialObjectStyle(UID styleID) = 0;
	/** Get the object style that would be applied to the inserted object.
		@return the UID of the object style.
	*/
	virtual UID GetInitialObjectStyle() const = 0;

	/** Set the paragraph style to be applied to the inserted object, IFF the object is a text frame.
		@param styleID is the paragraph style to apply
	*/
	virtual void SetInitialParagraphStyle(UID styleID) = 0;
	/** Get the paragraph style that would be applied to an inserted text frame.
		@return the UID of the paragraph style.
	*/
	virtual UID GetInitialParagraphStyle() const = 0;

	/** Set the width of the object to be inserted.
		@param w is the width in points.
	*/
	virtual void SetInitialWidth(PMReal w) = 0;
	/** Get the initial width of the object that would be inserted.
		@return the initial width.
	*/
	virtual PMReal GetInitialWidth() const = 0;

	/** Set the height of the object to be inserted.
		@param h is the height in points.
	*/
	virtual void SetInitialHeight(PMReal h) = 0;
	/** Get the height of the object to be inserted.
		@return the initial height in points.
	*/
	virtual PMReal GetInitialHeight() const = 0;

};

#endif
		// __IANCHOREDOBJECTINSERTDATA__




