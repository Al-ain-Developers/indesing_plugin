//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPDFFormXObjectSetupProvider.h $
//  
//  Owner: DBerggren
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
#ifndef __IPDFFormXObjectSetupProvider__
#define __IPDFFormXObjectSetupProvider__

#include "PDFID.h"
#include "PMRect.h"
#include "IPDFFormXObjectData.h"

class IDocument;
class IExportValidationCmdData;
class PMMatrix;

/**
	Document iteration service provider that assists in filling out the IPDFFormXObjectData 
	interface, which is used to create Form XObject constructs when exporting to PDF. This
	service provider will be called when the draw order it iterated, after the PDF UI, but
	before the export. The information returned by this service provider will be used to fill
	out the form lists and pages lists in the IPDFFormXObjectData interface. As page items 
	are visited, the provider reports which page items are in a static context. The page
	items in the static context are included in the form list for the page. At the end of
	the page or spread, this provider tells which forms are used on the page, which creates
	the page list.
 */
class IPDFFormXObjectSetupProvider: public IPMUnknown
{
public:
	/** default IID enumerator */
	enum { kDefaultIID = IID_IPDFFORMXOBJECTSETUPPROVIDER };

	/** Context states returned from VisitPageItem and EndPageOrSpread calls
	*/
	enum {
		/** Current page item is not part of a PDF Form XObject construct */
		kNotInContext							= 0,
		/** Current page item is the first to be used in a PDF Form XObject construct */
		kBeginStaticContext						= 1,
		/** Continue collecting UIDs to be used in form */
		kContinueStaticContext					= 2,
		/** Abort collecting UIDs for a form */
		kAbortStaticContext						= 3,
		/** End collecting, and include current page item as part of the form */
		kEndStaticContextInclude				= 4,
		/** End collecting, and do not include current page item as part of the form */
		kEndStaticContextExclude				= 5,
		/** End collecting, start a new form and include current page item as part of the new form */
		kEndStaticContextExcludeBeginNew		= 6,

		kPlaceholder							= ((int32)-32767)
	};

public:	

	/**
		Determine if this provider is interested in filling out PDF Form XObject information.
		@return bool16 - kTrue if interested, kFalse otherwise
	 */
	virtual bool16 InterestedIn() = 0;

	/**
		Called at the beginning of the iteration of the document.
		@param validData IN - see @IExportValidationCmdData
	 */
	virtual void BeginIteration(IExportValidationCmdData* validData) = 0;
	/**
		Called at the end of the iteration of the document.
	 */
	virtual void EndIteration() = 0;

	/**
		Called at the beginning of each page or spread.
		@param pDoc IN - see @IDocument
		@param nOutputPage IN - which page we are starting
		@param refPageOrSpread IN - UIDRef of the page or spread
		@param rectBounds IN - bounds of the page or spread in that objects coordinate system
		@param boundsToSpreadMatrix	IN the transformation matrix that maps the rectBounds of a page to spread coordinates.
										This matrix will be an identity matrix when exporting spreads.
	 */
	virtual void BeginPageOrSpread(	IDocument*      pDoc, 
									const int32     nOutputPage, 
									const UIDRef    refPageOrSpread, 
									const PMRect&	rectBounds,
									const PMMatrix&	boundsToSpreadMatrix ) = 0;
	/**
		Called at the end of each page or spread. Note that it is OK to return an abort or end
		context, but the form contexts do not spread across pages, so a begin or continue 
		return contexts are ignored.
		@param returnContext OUT - return context, see enum for context values.  
		@param returnFormID OUT - unique ID that identifies the form, if returning 
								one of the EndStaticContext enums
		@param formsUsedOnPage OUT - vector of FormIDs that are used on this page
	 */
	virtual void EndPageOrSpread(	int32*			returnContext,
									FormID*			returnFormID,
									K2Vector<FormID>& formsUsedOnPage) = 0;

	/**
		Called at the beginning of each page item. The return context is used to determine
		if the page item is to be used in a PDF Form XObject construct. 
		@param pXForm IN - transformation matrix
		@param pPageItem IN - the page item being visited
		@param nFlags IN - the drawing flags
		@param returnContext OUT - return context, see enum for context values.  
		@param returnFormID OUT - unique ID that identifies the form, if returning 
								one of the EndStaticContext enums
	 */
	 //As of Aug 2009 this has one caller: PDFFormXObjectGatherProvider::VisitPageItem
	 //and two implementations: MasterPageFormXObjectProvider and DataMergeFormXObjectProvider
	virtual void VisitPageItem(	const PMMatrix* masterSpread2LayoutSpreadMatrix, 
								IPMUnknown* pPageItem, 
								int32       nFlags,
								int32*		returnContext,
								FormID*		returnFormID) = 0;

	/**
		Called at conclusion of iteration. Passes the information we have collected.
		@param formData IN - see @IPDFFormXObjectData
	 */
	virtual bool16 OnIterationCompleted(IPDFFormXObjectData* formData) = 0;

};

#endif

