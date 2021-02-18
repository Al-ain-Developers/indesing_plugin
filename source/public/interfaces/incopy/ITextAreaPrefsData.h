//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ITextAreaPrefsData.h $
//  
//  Owner: psorrick
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
#ifndef __ITextAreaPrefsData__
#define __ITextAreaPrefsData__

#include "IPMUnknown.h"
#include "PMRect.h"
#include "InCopyCoreID.h"
#include "ITextAreaPrefs.h"

/**
   This interface is used to cache data for creating document or document styles related commands including 
   kInCopyNewDocCmdBoss, kDocEditPresetCmdBoss, kSaveDocumentPresetDataCmdBoss, kSetTextAreaPrefsCmdBoss
*/
class ITextAreaPrefsData : public IPMUnknown
{
public:
	/**
		Define the default IID for ITextAreaPrefsData.
	*/
	enum { kDefaultIID = IID_ITEXTAREAPREFSDATA };

	virtual void Set(UIDRef docref, const PMReal width, const PMReal depth,const ITextAreaPrefs::TextAreaDepthUnit unitIndex) =0;
	
	/**
		SetDocument indicating the document to set the ITextAreaPrefs.
		not setting the document means to set the ITextAreaPrefs in session workspace

		@param docref refers to the document to set the ITextAreaPrefs .
		@return void.
	*/
	virtual void SetDocument(UIDRef docref) = 0;

	/**
		Get the document UIDRef
			
		@return UIDRef of document
	*/

	virtual UIDRef GetDocument() const = 0;

	
	/**
		Set the width of text area.

		@param width the width of the text area
		@return void.
	*/
	virtual void SetTextAreaWidth(const PMReal width) = 0;

	/**
		Get the width of text area.
		
		@return const the width of the text area
	*/
	virtual PMReal GetTextAreaWidth() const = 0;

	/**
		Set the depth of text area.

		@param depth the depth of the text area
		@return void.
	*/
	virtual void SetTextAreaDepth(const PMReal depth) = 0;

	/**
		Get the depth of text area.
		
		@return const the depth of the text area
	*/
	virtual PMReal GetTextAreaDepth() const = 0;

	/**
		Set the unit index for the depth of text area.

		@param unitIndex the index of unit for the depth of the text area 
		@return void.
	*/
	virtual void SetTextAreaDepthUnit(const ITextAreaPrefs::TextAreaDepthUnit unitIndex) = 0;

	/**
		Get the unit idnex of depth of text area.
		
		@return const the unit index of depth of the text area
	*/
	virtual ITextAreaPrefs::TextAreaDepthUnit GetTextAreaDepthUnit() const = 0;
	
};

#endif

