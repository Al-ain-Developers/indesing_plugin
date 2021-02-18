//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILinkCaptionPrefs.h $
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
//========================================================================================

#pragma once
#ifndef __ILinkCaptionPrefs
#define __ILinkCaptionPrefs

#include "IPMUnknown.h"
#include "LinksID.h"

/** This interface provides access to the preferences for generating captions for links. */
class ILinkCaptionPrefs : public IPMUnknown
{
public:	
	/** Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_ILINKCAPTIONPREFS };

	/** Ask how many caption lines there are */
	virtual int32 GetNumCaptionLines() const = 0;

	/** Ask for the nth 'before' caption string */
	virtual PMString GetNthBeforeString(int32 index) const = 0;

	/** Ask for the link info provider for the nth line */
	virtual PMString GetNthLinkInfoProviderName(int32 index) const = 0;

	/** Ask for the nth 'after' caption string */
	virtual PMString GetNthAfterString(int32 index) const = 0;
		
	/** clear all the caption lines */
	virtual void ClearAllCaptionLines() = 0;
	
	/** Add one new caption line. New line is appended after existing lines */
	virtual void AddNewCaptionLine(const PMString& beforeString, const PMString& linkInfoProviderName, const PMString& afterString) = 0;

	/** Get and set the amount of frame offset */
	virtual void SetFrameOffset(const PMReal& offset) = 0;
	virtual PMReal GetFrameOffset() const = 0;
	
	/** Get and set the paragraph style to use for the caption */
	virtual void SetCaptionParagraphStyleUID(UID styleUID) = 0;
	virtual UID GetCaptionParagraphStyleUID() const = 0;

	/** Get and set the flag which says to group the caption and image together */
	virtual void SetGroupCaptionWithImage(bool shouldGroup) = 0;
	virtual bool GetGroupCaptionWithImage() const = 0;

	/** Get and set the layer to use for the caption */
	virtual void SetCaptionLayerName(const PMString& layerName) = 0;
	virtual PMString GetCaptionLayerName() const = 0;

	enum CaptionAlignment
	{
		kAlignAbove,	
		kAlignBelow,
		kAlignLeft,
		kAlignRight
	};
	/** Get and set the alignment to use for the caption */
	virtual void SetCaptionAlignment(CaptionAlignment newAlign) = 0;
	virtual CaptionAlignment GetCaptionAlignment() const = 0;

	/** copy settings from a different instance of this interface */
	virtual void CopyFrom(const ILinkCaptionPrefs *src) = 0;
	
	
};

#endif
