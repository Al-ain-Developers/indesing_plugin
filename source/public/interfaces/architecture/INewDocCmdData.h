//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/INewDocCmdData.h $
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
#ifndef __INewDocCmdData__
#define __INewDocCmdData__

#include "IPMUnknown.h"
#include "PMRect.h"
#include "IDocument.h"
#include "IColumns.h"
#include "IPageSetupPrefs.h"
#include "IMasterOverrideable.h"

class FormatID;

/**
   This interface is used to cache data for creating document or document styles related commands including 
   kNewDocCmdBoss, kInCopyNewDocCmdBoss, kDocEditStyleCmdBoss, kSaveDocumentStyleDataCmdBoss
*/
class INewDocCmdData : public IPMUnknown
{
public:
	/**
		Define the default IID for INewDocCmdData.
	*/
	enum { kDefaultIID = IID_INEWDOCCMDDATA };

	/**
		Set UI flags indicating if we need to bring up dialog when processing command.

		@param uiflags refers to UI setting such as kSuppressUI, kMinimalUI and kFullUI. UIFlags is defined in BaseType.h.
		@return void.
	*/

	virtual void SetUIFlags(UIFlags uiflags) = 0;

	/**
		Get the UI settings when processing command.
			
		@return UIFlags the UI setting when processing command. 
	*/

	virtual UIFlags GetUIFlags() const = 0;

	/**
		The following three lines defines a set of bits to specify what kind of document is being created. 
		For historical reasons, the flags are defined as integers instead of enum values.

		kFullNewDocument means standard document probably only meaningful by itself. 
		kMinimalNewDocument means minimal document formerly known as "Basic Document". 
		kXMLInterchangeNewDocument means XML interchange document which is a new document supported in InDesign 3.0.
	*/

	#define	kFullNewDocument			0x00		
	#define kMinimalNewDocument			0x01		
	#define kXMLInterchangeNewDocument	0x02

	/**
		Set the type flag that what kind of document is being created. 
		
		@param typeFlags refers to different types of document. 
		The type of document could be:
		1) kFullNewDocument means standard document probably only meaningful by itself. 
		2) kMinimalNewDocument means minimal document formerly known as "Basic Document". 
		3) kXMLInterchangeNewDocument means XML interchange document which is a new document supported in InDesign 3.0.
		@return void.
	*/

	virtual void SetCreateBasicDocument(uint16 typeFlags) = 0;

	/**
		Get the type of the document being created. 

		@return uint16 indicating what kind of document being created. 
		The type of document could be:
		1) kFullNewDocument means standard document probably only meaningful by itself. 
		2) kMinimalNewDocument means minimal document formerly known as "Basic Document". 
		3) kXMLInterchangeNewDocument means XML interchange document which is a new document supported in InDesign 3.0.
	*/

	virtual uint16 GetCreateBasicDocument() const = 0;
	
	/**
		Set the margins for the new document. 

		@param insideLeft refers to inside margin for facing pages case or left margin.
		@param top refers to top margin.
		@param outsideRight refers to outside margin for facing pages case or right margin.
		@param bottom refers to bottom margin
		@return void.
	*/

	virtual void SetMargins(const	PMReal&	insideLeft,		/* inside (for facing pages case) or left margin */
							const	PMReal&	top,			/* top margin */
							const	PMReal&	outsideRight,	/* outside (for facing pages case) or right margin */
							const	PMReal&	bottom			/* bottom margin */
							) = 0;

	/**
		Get the margins for the new document through the passed out parameters. 

		@param insideLeft refers to inside margin for facing pages case or left margin.
		@param top refers to top margin.
		@param outsideRight refers to outside margin for facing pages case or right margin.
		@param bottom refers to bottom margin
		@return void.
	*/

	virtual void GetMargins(PMReal* insideLeft, PMReal* top, PMReal* outsideRight, PMReal* bottom) = 0;

	/**    
		Set the flag determining if all margin values set from the top value.

	    @param bUniform kTrue indicating all margin values should use the top value, otherwise set as kFalse.
		@return void.
	*/

	virtual void SetUseUniformMargins(bool16 bUniform) = 0;

	/**    
		Get the flag that determining if all margin values are set from the top value.

		@return bool16 kTrue indicating all margin values should use the top value, otherwise set as kFalse.
	*/

	virtual bool16 GetUseUniformMargins() const = 0;
	
	/**
		Set the column attributes for the new document. 

		@param numColumns refers to the number of columns for the new document.
		@param gutter refers to distance between two adjacent columns.
		@param direction refers to column direction which is either horizontal or vertical. 
		If direction is kTrue indicating vertical columns, otherwise, it is horizontal columns.
		@return void.
	*/

	virtual void SetColumns_4( int32 numColumns, PMReal gutter, IColumns::ColumnOrientation direction) = 0;

	/**
		Get the number of columns of the new document.

		@return const int32 the number of columns.
	*/

	virtual int32 GetNumColumns() const = 0;

	/**
		Get the gutter value(the distance between two adjacent columns) of the new document.

		@return const PMReal the gutter value.
	*/

	virtual PMReal GetGutter() const = 0;

	/**
		Get the direction of columns of the new document.

		@return const bool16 kTrue is vertical column and kFalse is horizontal column.
	*/

	virtual IColumns::ColumnOrientation GetColumnOrientation_4() const = 0;

	/**
	    Set the flag determining if you want to create text frame on master page with the 
		margin size when create a new document.

		@param shown kTrue indicating creating text frame on master page, otherwise set as kFalse.
	*/

	virtual void SetAutoTextFrame( bool16 shown) = 0;

	/**
	    Get the setting that determine if we need to create text frame on master page with the 
		margin size when create a new document.

		@return const bool16 kTrue indicating creating text frame on master page, otherwise kFalse.
	*/

	virtual bool16 GetAutoTextFrame() const = 0;

	/**
	    Set the flag determining if you want to create text frame on master page with the 
		overrideable attribute. Only valid when GetAutoTextFrame is kTrue. Defaults to kTrue.

		@param bOverride indicating auto text frame on master page should be overridden or not.
	*/

	virtual void SetOverrideAutoTextFrame( bool16 bOverride) = 0;

	/**
		Return if auto text frame should be overridden.

		@return kTrue to override auto text frame (when it's on), kFalse for not.
	*/
	virtual bool16 GetOverrideAutoTextFrame() const = 0;

	/**
		Set the dimensions of the new page size. 

		@param pageSize refers to the new page size. 
		@return void.
	*/

	virtual void SetNewDocumentPageSize(const PMPageSize& pageSize) = 0;

	/**
		Get the dimensions of the new page size.
			
		@return const PMRect refers to the new page dimension.
	*/

	virtual const PMPageSize& GetNewDocumentPageSize() const = 0;

	/**
		Set the default scale to apply to new spreads. We typically apply scaling to spreads based on the ppi of the pages that will be in the spread.
		@param scale [IN] The x and y scale to apply to the spread.
	*/
	virtual void SetSpreadScale(const K2Pair<PMReal, PMReal>& scale) = 0;

	/** Return the width scale to apply to the spread.
	*/
	virtual PMReal GetSpreadWidthScale() const = 0;

	/** Return the height scale to apply to the spread.
	*/
	virtual PMReal GetSpreadHeightScale() const = 0;

	/**
		Set the orientation of the document.

		@param bWide refers to if the document is wide or tall(kTrue if it is wide, kFalse if it is tall). 
		@return void.
	*/

	virtual void SetWideOrientation( bool16 bWide) = 0;

	/**
		Get the orientation of the document.
		
		@return const bool16 kTrue if the orientation is wide, kFalse if it is not.
	*/

	virtual bool16 GetWideOrientation() const = 0;
	
	/**
		Set the number of pages the document will have. 

		@param numPages refers to number of pages. 
		@return void.
	*/

	virtual void SetNumPages( int32 numPages) = 0;

	/**
		Get the number of pages the document will have. 
			
		@return const int32 the number of pages for the document.
	*/

	virtual int32 GetNumPages() const = 0;
	
	/**
		Set the number of pages each spread will have.

		@param numPagesPerSpread refers to the number of pages per spread. 
		@return void.
	*/

	virtual void SetPagesPerSpread( int32 numPagesPerSpread) = 0;

	/**
		Get the number of pages each spread will have.
			
		@return const int32 the number of pages for each spread.
	*/

	virtual int32 GetPagesPerSpread() const = 0;

	/**
		Set the binding of the pages in the document. Currently page binding could be kDefaultBinding(-1), kLeftToRightBinding(0), kRightToLeftBinding(1).

		@param bindingDirection refers to binding setting. 
		@return void.
	*/

	virtual void SetPageBinding( int32 bindingDirection) = 0;

	/**
		Get the page binding setting. 
			
		@return const int32 indicating kDefaultBinding(-1), kLeftToRightBinding(0), kRightToLeftBinding(1).
	*/

	virtual int32 GetPageBinding() const = 0;

	/**
		Set the flag determining if page numbering needs to be restart or not. 

		@param bRestartPageNum a flag determining if page numbering needs to be restart or not. 
		@return void.
	*/

	virtual void SetRestartPageNum( bool16 bRestartPageNum) = 0;

	/**
		Get the flag if page numbering needs to be restart or not.
			
		@return const bool16 kTrue if page number needs to be restart, kFalse if it is not.
	*/

	virtual bool16 GetRestartPageNum() const = 0;

	/**    
		Set the bleed offsets.

	    @param offsets the bleed offsets which is stored in a rect. Inside offset stored in left, outside offset stored in right.
		@return void.
	*/

	virtual void SetBleedBox(PMRect offsets) = 0;

	/**    
		Get the bleed offsets.

	    @return PMRect the bleed offsets which is stored in a rect. Inside offset stored in left, outside offset stored in right.
	*/

	virtual PMRect GetBleedBox() = 0;
	
	/**    
		Tell whether a change to any bleed value change them all to that value.

	    @param bUniform is a flag determining a change to any bleed value change them all to that value.
		@return void.
	*/

	virtual void SetUseUniformBleed(bool16 bUniform) = 0;

	/** 
		Check whether a change to any bleed value changes them all to that value.

		@return bool16 kTrue indicating use uniform bleed, kFalse indicating not use uniform bleed. 
	*/

	virtual bool16 GetUseUniformBleed() const = 0;
	

	/**    
		Set the slug box offsets.

	    @param offsets refers to the slug offsets which is stored in a rect. Inside offset stored in left, outside offset stored in right.
		@return void.
	*/

	virtual void SetSlugBox(PMRect offsets) = 0;

	/**    
		Get the slug box offsets.

	    @return PMRect the slug offsets which is stored in a rect. Inside offset stored in left, outside offset stored in right.
	*/

	virtual PMRect GetSlugBox() = 0;
	
	/**    
		Tell whether a change to any slug value changes them all to that value.

	    @param bUniform is a flag determining a change to any slug value changes them all to that value.
		@return void.
	*/

	virtual void SetUseUniformSlug(bool16 bUniform)  = 0;

	/**    
		Check whether a change to any slug value changes them all to that value.

		@return bool16 kTrue indicating use uniform slug, kFalse indicating not use uniform slug. 
	*/

	virtual bool16 GetUseUniformSlug() const = 0;
	
	/**    
		Set the starting page number for the document.

	    @param startPageNumber the number for the first page of the document. Defaults to 1.
		@return void.
	 */

	virtual void SetStartPageNumber(int32 startPageNumber) = 0;
	/**    
		Get the starting page number for the document.

		@return const int32 the starting page number for the first page of the document.
	 */
	virtual int32 GetStartPageNumber() const = 0;

	/**	Get the document intent preference
		@param void 
		@return DocumentIntent 
	 */
	virtual DocumentIntent GetIntent() const = 0;

	/**	Set the document intent preference
		@param intent IN - the new setting
	 */
	virtual void SetIntent(DocumentIntent intent) = 0;

	/**    
		Allow the setting of a custom document boss type other than kDocBoss.

		@param bossID id of boss to use.
		@return void. 
	*/

	virtual void SetDocBossClassID(ClassID bossID = kDocBoss) = 0;
	
	/**    
		Return the value set in SetDocBossClassID.

		@return boss id used to create document. 
	*/

	virtual ClassID GetDocBossClassID() const = 0;

	/**
		Set the undo support option @see IDocument.

		@param IDocument::UndoSupport.  
	*/
	virtual void SetUndoSupport(IDocument::UndoSupport undoSupport) = 0;

	/**
		Get the undo support option @see IDocument.

		@return IDocument::UndoSupport.  
	*/
	virtual IDocument::UndoSupport GetUndoSupport() const = 0;

};

#endif

