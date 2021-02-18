//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyGalleySettingData.h $
//  
//  Owner: Cindy Chen
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
//  Purpose:
//  
//========================================================================================

#pragma once
#ifndef __IInCopyGalleySettingData__
#define __IInCopyGalleySettingData__

#include "IPMUnknown.h"
#include "WritingModeUIID.h"
#include "WritingModeID.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IWindow.h"
#include "PMReal.h"
#include "UIDList.h"
#include "UIDRef.h"

/**
 Interface that contains settings that used to construct the galley panel, 
 and contains information about the constructed galley panel
 for printing/pdf-export in InCopy
*/

class IInCopyGalleySettingData : public IPMUnknown
{
public:
	enum	{	kDefaultIID = IID_IINCOPYGALLEYSETTINGDATA };

/**	Copy the interface data
	@param copyFrom The interface data to be copied
 */
	virtual void CopyData(IInCopyGalleySettingData const* copyFrom) = 0;
	
/**	Set method to store the galley control view for print/PDF-export
	@param view 
 */
	virtual void SetWritingView(IControlView * view) = 0;

/**	Get method to get the galley control view
	@param none
	@return IControlView 
 */
	virtual IControlView * GetWritingView() const = 0;

/**	Set method to store the Info Column (kInfoColumnID) control view
	@param view 
 */
	virtual void SetInfoColumnView(IControlView * view) = 0;

/** Get method to get the info column control view
	@param none
	@return IControlView 
 */
	virtual IControlView * GetInfoColumnView() const = 0;

/** Not used anymore. Set method to store the line number control view
	@param view 
 */
	virtual void SetLineNumberView(IControlView * view) = 0;

/**	Not used anymore. Get method to get the line number control view
	@param none
	@return IControlView 
 */
	virtual IControlView * GetLineNumberView() const = 0;

/**	Set method to store the splitter panel control view
	@param view 
 */
	virtual void SetInfoSplitterView(IControlView * view) = 0;

/**	Get method to get the splitter panel control view
	@param none
	@return IControlView 
 */
	virtual IControlView * GetInfoSplitterView() const = 0;

/**	Set method to store the total height of the constructed galley view
	@param height 
 */
	virtual void SetTotalHeight(PMReal height) = 0;

/**	Get method to get the total height of the constructed galley view
	@param none
	@return PMReal 
 */
	virtual PMReal GetTotalHeight() const = 0;

/**	Not used anymore. 
	@param line 
 */
	virtual void SetStartLineNumber(int32 line) =0;

/**	Not used anymore.
	@param none
	@return int32 
 */
	virtual int32 GetStartLineNumber() const = 0;
	
/**	Not used anymore.
	@param line 
 */
	virtual void SetEndLineNumber(int32 line)=0;

/**	Note used anymore.
	@param none
	@return int32 
 */
	virtual int32 GetEndLineNumber() const = 0;
	
/**	Set method to store the width of the printing column in galley panel
	@param width 
 */
	virtual void SetColumnWidth(PMReal width) = 0;

/**	Get method to get the width of the printing column in galley panel
	@param none
	@return PMReal 
 */
	virtual PMReal GetColumnWidth() const = 0;

/**	Set method to store the flag that tells if this is a temporary galley panel
	@param setting kFalse means this is a temporary galley panel
 */
	virtual void SetGalleySetting(bool16 setting) = 0;

/**	Set method to get the flag that tells if this is a temporary galley panel
	@param none
	@return bool16 kFalse means this is a temporary galley panel
 */
	virtual bool16 GetGalleySetting() const = 0;

/**	Set method to store the document UIDRef
	@param docUIDRef 
 */
	virtual void SetDocUIDRef(const UIDRef& docUIDRef)=0;

/**	Get method to get the document UIDRef
	@param none
	@return const 
 */
	virtual const UIDRef& GetDocUIDRef() const=0;
	
/**	Set method to set printing/PDF-exporting with paragraph style
	@param displayed 
 */
	virtual void SetParaStyles(bool16 displayed) = 0;

/**	Get method to get if printing/PDF-exporting with paragraph style
	@param none
	@return bool16 kTrue means to print/PDF-export with paragraph style
 */
	virtual bool16 GetParaStyles() const = 0;

/** Set method to set printing/PDF-exporting with line number
	@param displayed 
 */
	virtual void SetLineNumber(bool16 displayed) = 0;

/** Get method to get if printing/PDF-exporting with line number
	@param none
	@return bool16 kTrue means to print/PDF-export with line number
 */
	virtual bool16 GetLineNumber() const = 0;

/**	Set method to set printing/PDF-exporting with accurate line ening
	@param displayed 
 */
	virtual void SetALE(bool16 displayed) = 0;

/**	Get method to get if printing/PDF-exporting with accurate line ening
	@param none
	@return bool16 kTrue means to print/PDF-export with accurate line ening
 */
	virtual bool16 GetALE() const = 0;

	// to print with notes displayed

/**	Set method to set printing/PDF-exporting with Notes displayed
	@param displayed 
 */
	virtual void SetNotes(bool16 displayed) = 0;

/**	Get method to get printing/PDF-exporting with Notes displayed
	@param none
	@return bool16 kTrue means to print/PDF-export with Notes displayed
 */
	virtual bool16 GetNotes() const = 0;
     
/**	Set method to set printing/PDF-exporting with track changes displayed
	@param displayed 
 */
	virtual void SetTrackChanges(bool16 displayed) = 0;

/**	Get method to get printing/PDF-exporting with track changes displayed
	@param none
	@return bool16 kTrue means printing/PDF-exporting with track changes displayed
 */
	virtual bool16 GetTrackChanges() const = 0;

/**	Set method to set the Notes display type 
	@param type 0 = display all Notes, 1 = display visible Notes
 */
	virtual void SetNotesType(int32 type) = 0;

/**	Get method to get the Notes display type 
	@param none
	@return int32 0 = display all Notes, 1 = display visible Notes
 */
	virtual int32 GetNotesType() const = 0;

/**	Set method to set the Track Changes display type 
	@param type 0 = display all Track Changes, 1 = display visible Track Changes
 */
	virtual void SetTrackChangesType(int32 type) = 0;

/**	Get method to get the Track Changes display type 
	@param none
	@return int32 0 = display all Track Changes, 1 = display visible Track Changes
 */
	virtual int32 GetTrackChangesType() const = 0;

/**	Set method to set the font for printing/PDF-exporting
	@param fontName 
 */
	virtual void SetFontName(const PMString& fontName) = 0;

/**	Get method to get the font for printing/PDF-exporting
	@param none
	@return PMString The font name
 */
	virtual PMString GetFontName() const = 0;

/**	Set method to set the font type for printing/PDF-exporting
	@param fontType 
 */
	virtual void SetFontType(const PMString& fontType) = 0;

/**	Get method to get the font for printing/PDF-exporting
	@param none
	@return PMString 
 */
	virtual PMString GetFontType() const = 0;

/**	Set method to set the font size for printing/PDF-exporting
	@param fontSize 
 */
	virtual void SetFontSize(const PMString& fontSize) = 0;

/**	Get method to get the font size for printing/PDF-exporting
	@param none
	@return PMString 
 */
	virtual PMString GetFontSize() const = 0;

/**	Set method to set the font leading for printing/PDF-exporting
	@param fontLeading 
 */
	virtual void SetFontLeading(const PMString& fontLeading) = 0;

/**	Get method to get the font leading for printing/PDF-exporting
	@param none
	@return PMString 
 */
	virtual PMString GetFontLeading() const = 0;

/**	Set method to set the type of scope for printing/PDF-exporting
	@param range 0 = all stories, 1 = range
 */
	virtual void SetWhich(int32 range)=0;

/**	Get method to get the type of scope for printing/PDF-exporting
	@param none
	@return int32 0 = all stories, 1 = range
 */
	virtual int32 GetWhich() const = 0;

/**	Set method to set line range for printing/PDF-exporting
	@param range 
 */
	virtual void SetRange(PMString range)=0;

/**	Get method to get line range for printing/PDF-exporting
	@param none
	@return PMString 
 */
	virtual PMString GetRange() const = 0;

/**	Set method to store the printing galley panel size
	@param frame 
 */
	virtual void SetFrameSize(PMRect frame)=0;

/**	Get method to get the printing galley panel size
	@param none
	@return PMRect 
 */
	virtual PMRect GetFrameSize() const = 0;

/**	Set method to set printing/PDF-exporting to fill the panel with multi-column
	@param displayed 
 */
	virtual void SetFill(bool16 displayed) = 0;

/**	Get method to get if printing/PDF-exporting fills the panel with multi-column
	@param none
	@return bool16 
 */
	virtual bool16 GetFill() const = 0;

/**	Set method to set the story scope for printing/PDF-exporting
	@param scope 0 = all stories, 1 = current story in active document, 2 = expanded story in active document
 */
	virtual void SetScope(int32 scope) = 0;

/**	Get method to get the story scope for printing/PDF-exporting
	@param none
	@return int32 0 = all stories, 1 = current story in active document, 2 = expanded story in active document
 */
	virtual int32 GetScope() const = 0;

/**	Set method to set printing/PDF-exporting with story information
	@param displayed 
 */
	virtual void SetStoryInfo(bool16 displayed) = 0;

/**	Get method to get if printing/PDF-exporting with story information
	@param none
	@return bool16 
 */
	virtual bool16 GetStoryInfo() const = 0;

/**	Set method to set inline Notes background with color when printing/PDF-exporting
	@param displayed 
 */
	virtual void SetNotesBackgroundInColor(bool16 displayed) = 0;

/**	Get method to get inline Notes background color when printing/PDF-exporting
	@param none
	@return bool16 
 */
	virtual bool16 GetNotesBackgroundInColor() const = 0;

/**	Set method to set track changes background with color when printing/PDF-exporting
	@param displayed 
 */
	virtual void SetTrackChangesBackgroundInColor(bool16 displayed) = 0;

/**	Get method to get if track changes background with color when printing/PDF-exporting
	@param none
	@return bool16 
 */
	virtual bool16 GetTrackChangesBackgroundInColor() const = 0;

/**	Set method to set printing/PDF-exporting with page information
	@param displayed 
 */
	virtual void SetPagesInfo(bool16 displayed) = 0;

/**	Get method to get if printing/PDF-exporting with page information
	@param none
	@return bool16 
 */
	virtual bool16 GetPagesInfo() const = 0;

/**	Set method to set number of column to print/PDF-export in a single page
	@param columns 
 */
	virtual void SetColumns(int32 columns) = 0;

/**	Get method to get number of column in printing/PDF-exporting
	@param none
	@return int32 
 */
	virtual int32 GetColumns() const = 0;

	// manage story list

/**	Get method to get the number of story to print/PDF-export
	@param none
	@return int32 
 */
	virtual int32 GetStoryCount() const = 0;

/**	Get method to get the index of story by given story UIDRef
	@param storyRef 
	@return int32 
 */
	virtual int32 GetStoryIndex(const UIDRef& storyRef) const = 0;

/**	Get method to get story UIDRef by given the index
	@param index 
	@return const 
 */
	virtual const UIDRef& GetStoryRef(int32 index) const = 0;

/**	Get method the get the collapsing state of the story by given index
	@param index 
	@return bool16 
 */
	virtual bool16 GetNthStoryCollapsedState(int32 index) const = 0;

/**	Set method to store the current story index
	@param index 
 */
	virtual void SetCurrentStoryIndex(int32 index)=0;

/**	Get method to get the current story index
	@param none
	@return int32 
 */
	virtual int32 GetCurrentStoryIndex() const = 0;

/**	Query the current document galley settings to store in IInCopyGalleySettingData
	@param document The active document
	@param galley Galley control view in active document
 */
	virtual void QueryGalleySettings(IDocument * document, IControlView* galley) = 0;
	
/**	Calculate and set the min/max number of galley lines by giving the galley control view
	@param galley 
 */
	virtual void SetLineRangeLimits(IControlView* galley) = 0;

/**	Calculate each rect bounding for each column in a page for printting/PDF-exporting
	@param none
 */
	virtual void InitializeColumnBounds() = 0;

/**	Get the column's rect bounding by given column index
	@param index 
	@return PMRect 
 */
	virtual PMRect GetNthColumnBounds(int32 index) const = 0;

/**	Get the total number of columnes rect bounding will be print/PDF-export
	@param none
	@return int32 
 */
	virtual int32 GetColumnBoundsCount() const = 0;
};

class StoryState
{
public:
	typedef base_type data_type;
	UIDRef fStoryRef;
	bool16 fCollapsed;
};

#endif

// End, IPrintGalleyData.h.
