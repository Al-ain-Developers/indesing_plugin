//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkTextSourceCmdData.h $
//  
//  Owner: Jianlan Song
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

#include "HyperlinkID.h"
#include "itextRangeNode.h"

/** This class stores information needed for text source commands. (used in conjunction with
	the NewHyperlinkTextSourceCmd.)
*/
class IHyperlinkTextSourceCmdData : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IHYPERLINKTEXTSOURCECMDDATA};

	/** Use this method to setup of the data
		@param name - the name of the new text source
		@param storyUIDRef - text model UIDRef
		@param start - The start text index to create source at. 
		@param end - The end text index for the source. The end index is really 1 past the last character in the range.
		@param isVisible - kFalse = not visible in the UI; kTrue = visible in the UI.
		@param bookmarkUID - linked bookmark data.
		@param isXref - kTrue if it is a cross reference text source.
		@param xRefFormat - UID of the format used by the cross reference.
	*/
	virtual void Set(	const PMString& name, const UIDRef& storyUIDRef, 
					TextIndex start, TextIndex end, bool16 isVisible, const UIDRef& bookmarkUIDRef, bool16 isXref = kFalse, UID xRefFormat = kInvalidUID) = 0;

	/** Get the name of the source 
		@return const PMString& - name string
	*/
	virtual PMString GetName() const = 0;
	virtual void SetName( const PMString& name) = 0;
	virtual bool16 ChangingName() const = 0;

	/** Get the text model UIDRef 
		@return const UIDRef& - The text model UIDRef
	*/
	virtual UIDRef	GetStoryUIDRef() const = 0;
	virtual void			SetStoryUIDRef(const UIDRef& storyUIDRef) = 0;
	virtual bool16			ChangingTextModel() const = 0;

	/** Get the start index of the range to create source at
		@return TextIndex - start index
	*/
	virtual TextIndex GetStartIndex() const = 0;
	
	/** Get the length of the range to create source at
		@return int32 - range length
	*/
	virtual int32 GetRangeLength() const = 0;

	virtual void SetRangeData(TextIndex start, TextIndex end) = 0;
	virtual bool16 ChangingRangeData() const = 0;

	/** Get the character style for the hyperlink source
		@return UID character style UID
	*/
	virtual UID GetCharStyle() const = 0;
	virtual void SetCharStyle(UID charStyle) = 0;
	virtual bool16 ChangingCharStyle() const = 0;
	
	/** Return kTrue if the source is visible in UI.
		@return bool16 - kTrue if the source is visible in UI.
	*/
	virtual bool16 IsVisible() const = 0;
	virtual void SetIsVisible(bool16 isVisible) = 0;
	virtual bool16 ChangingVisibility() const = 0;

	/** Get the book mark data
		@return const UID& - book mark data UID.
	*/
	virtual UIDRef GetBookmarkData() const = 0;
	virtual void 		SetBookmarkData(const UIDRef& bookmarkUIDRef) = 0;
	virtual bool16		ChangingBookmarkData() const = 0;

	virtual void SetIsXRef(bool16 isXRef) = 0;
	virtual bool16 IsXRef() const = 0;

	virtual void SetXRefFormat(UID xRefFormat) = 0;
	virtual UID GetXRefFormat() const = 0;
	virtual bool16 ChangingXRefInfo() const = 0;
};

