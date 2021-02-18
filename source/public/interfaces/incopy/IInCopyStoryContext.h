//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyStoryContext.h $
//  
//  Owner: Jeff Argast
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
#ifndef __IInCopyStoryContext__
#define __IInCopyStoryContext__

#include "IPMUnknown.h"

#include "InCopyWorkflowID.h"

class WideString;
class IInCopyXMLElementAttr;
class IAttrReport;
class InCopyHyperlinkSource;
class InCopyHyperlinkDestination;
class InCopyInlineSpec;
class ITableAttrReport;
class ITableModel;
class GridAddress;
class IInCopyImportOptions;

class IInCopyStoryContext : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINCOPYSTORYCONTEXT };

	virtual void BeginStory (const UIDRef& storyRef, int32 textIndex, IInCopyImportOptions* options) = 0;

	virtual void EndStory () = 0;

	virtual void AppendContent (const WideString& content) = 0;

	virtual void ChangeTextAttribute (IAttrReport* iReport) = 0;

    //----------------------------------------------------------------------------------------
	virtual void AddMissingColorTextAttribute(
		IAttrReport* iReport, 
		const PMString& colorName
		) = 0;

	virtual void EndTextAttribute (ClassID attrClass) = 0;
	
	virtual void ChangeParagraphStyle (const WideString& styleName) = 0;

	virtual void ChangeCharacterStyle (const WideString& styleName) = 0;
	
	virtual void StartChangeRecord (int32 type, uint64& time, bool16 moved, PMString& user, UID ownedItem = kInvalidUID) = 0;

	virtual void EndChangeRecord () = 0;

	virtual void ApplyHyperlinkSource (InCopyHyperlinkSource& source) = 0;

	virtual void ApplyHyperlinkDestination(InCopyHyperlinkDestination& source) = 0;

	virtual void ApplyInline(InCopyInlineSpec& inlineSpec) = 0;
	
	virtual void PushElement
		( 
			const WideString& 		localName,
			const WideString& 		qName,
			IInCopyXMLElementAttr*	iAttrs,
			bool16					bIsInline = kFalse
		) = 0;


	virtual void PopElement
		(
			const WideString& 		localName,
			const WideString& 		qName
		) = 0;

	/** Add XML comment to the context
		@param comment body of the XML comment
	*/
	virtual void XMLComment(const WideString& comment) = 0;

	/** Add XML processing instruction to the context
		@param piTarget processing instruction target
		@param piData processing instruction data
	*/
	virtual void XMLProcessingInstruction(const WideString& piTarget, const WideString& piData) = 0;

    //----------------------------------------------------------------------------------------
	virtual void BeginTable (
		) = 0;

    //----------------------------------------------------------------------------------------
	virtual void EndTable(
		int32 numRows
		) = 0;

    //----------------------------------------------------------------------------------------
	virtual void BeginCell(
		ITableModel* tableModel,
		GridAddress cellAnchor,
		const UIDRef& storyRef, 
		int32 textIndex
		) = 0;

    //----------------------------------------------------------------------------------------
	virtual void AddCellAttribute (
		ITableAttrReport* cellAttr
		) = 0;

    //----------------------------------------------------------------------------------------
	virtual void EndCell() = 0;

	virtual int32 GetCurrentIndex() const = 0;
	
	virtual void SetDefaultFont(
		const WideString& defaultFontName
		) = 0;
};


#endif // __IInCopyStoryContext__



