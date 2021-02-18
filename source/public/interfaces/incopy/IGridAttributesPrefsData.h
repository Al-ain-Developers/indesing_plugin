//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IGridAttributesPrefsData.h $
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
#ifndef __IGridAttributesPrefsData__
#define __IGridAttributesPrefsData__

#include "IPMUnknown.h"
#include "PMRect.h"
#include "InCopyCoreID.h"
#include "IGridAttributesPrefs.h"

/**
   This interface is used to cache data for creating document or document styles related commands including 
   kInCopyNewDocCmdBoss, kDocEditPresetCmdBoss, kSaveDocumentPresetDataCmdBoss, kSetGridAttributesPrefsCmdBoss
*/
class IGridAttributesPrefsData : public IPMUnknown
{
public:
	/**
		Define the default IID for IGridAttributesPrefsData.
	*/
	enum { kDefaultIID = IID_IGRIDATTRIBUTESPREFSDATA };

	virtual void Set(UIDRef docref,  
		const IGridAttributesPrefs::TextDirection direction,
		const IGridAttributesPrefs::FrameType type,
		const int32 charPerLine,
		const PMReal gridVScale, const PMReal gridHScale, 
		const PMReal charAki, const PMReal lineAki) =0;
	
	/**
		SetDocument indicating the document to set the IGridAttributesPrefs.
		not setting the document means to set the IGridAttributesPrefs in session workspace

		@param docref refers to the document to set the IGridAttributesPrefs .
		@return void.
	*/
	virtual void SetDocument(UIDRef docref) = 0;

	/**
		Get the document UIDRef
			
		@return UIDRef of document
	*/
	virtual UIDRef GetDocument() const = 0;

	/**
		Set the Text Area Grid Character per Line
		@param charPerLine the character per Line
		@return void.
	*/
	virtual void SetCharPerLine(const	int32 charPerLine) = 0;

	/**
		Get the Text Area Grid Character per Line
		@return the character per Line
	*/
	virtual int32 GetCharPerLine() const = 0;

	/**
		Set the Grid Vertical Scale
		@param vScale the grid vertical Scale
		@return void.
	*/
	virtual void SetGridVScale(const	PMReal	vScale) = 0;

	/**
		Set the Grid Vertical Scale
		@return the grid vertical Scale
	*/
	virtual PMReal GetGridVScale() const = 0;

	/**
		Set the Grid Horizontal Scale
		@param hScale the grid horizontal scale
		@return void.
	*/
	virtual void SetGridHScale(const	PMReal	hScale) = 0;

	/**
		Set the Grid Horizontal Scale
		@return the grid horizontal Scale
	*/
	virtual PMReal GetGridHScale() const = 0;

	/**
		Set the Grid Character Spacing
		@param charAki the Grid Character Spacing
		@return void.
	*/
	virtual void SetGridCharAki(const	PMReal	charAki) = 0;

	/**
		Set the Grid Character Spacing
		@return the grid Character Spacing
	*/
	virtual PMReal GetGridCharAki() const = 0;

		/**
		Set the Grid Line Spacing
		@param charAki the Grid Line Spacing
		@return void.
	*/
	virtual void SetGridLineAki(const	PMReal	lineAki) = 0;

	/**
		Set the Grid Line Spacing
		@return the grid Line Spacing
	*/
	virtual PMReal GetGridLineAki() const = 0;

		/**
		Set the Grid Driection
		@param direction the Grid Direction
		@return void.
	*/
	virtual void SetDirection(const	IGridAttributesPrefs::TextDirection	direction) = 0;

	/**
		Set the Grid Direction
		@return the grid Direction
	*/
	virtual IGridAttributesPrefs::TextDirection GetDirection() const = 0;

	/**
		Get the Frame Grid Type
		@return the Frame Grid Type
	**/
	virtual IGridAttributesPrefs::FrameType GetFrameGridType() const = 0;

	/**
		Set the Frame Grid Type
		@param direction the Frame Grid Type
		@return void.
	*/
	virtual void SetFrameGridType(const	IGridAttributesPrefs::FrameType	type) = 0;

	
};

#endif

