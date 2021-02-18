//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDocIterationProvider.h $
//  
//  Owner: Chris Jones
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
#ifndef __IDocIterationProvider__
#define __IDocIterationProvider__

#include "PrintID.h"
#include "PMRect.h"
class IDocument;
class PMMatrix;
class IExportValidationCmdData;

/**
 This interface is used to provide a callback mechanism when
 the document is iterated through prior to print and export events.
 A class can be sub-classed from this interface, and if properly
 paired with the kDocIterationServiceImpl, the provider will be
 called back at various times throughout the iteration process.
 Note that only the pages or spreads being printed or exported are 
 iterated.  */
class IDocIterationProvider : public IPMUnknown
{
public:
	/** 
	 Default enum.	*/
	enum { kDefaultIID = IID_IDOCITERATIONPROVIDER };

	/**
	 Identifies the context of the iteration. */
	enum IterationContext
	{	
		/**
		 Iterating prior to printing. */
		kGatherAndValidateBeforePrint = 1,
		/**
		 Iterating prior to PDF export. */
		kValidateBeforePDFExport      = 2,
		/**
		 Iterating prior to EPS export. */
		kValidateBeforeEPSExport      = 3,
		
		/**
		 was OBSOLETE: again bringing it back for SVG export in CS6.0.
		*/
		kValidateBeforeSVGExport      = 4,

		 /** Currently unused. */
		kValidateBeforeHTMLExport     = 5,
		/**
		 Iterating prior to placing an InDesign document. */
		kGatherAndValidateBeforePlace = 6,
		/**
		 Iterating prior to XFL/FLA export. */
		kValidateBeforeXFLExport      = 8
	};

public:	
	/**	Used by the iteration code to set the context and a data interface specific
		to the context.

		@param pIterationData	IN data interface specific to the given iteration context
		@param nContext		IN the iteration context defined above
	 */
	virtual void SetIterationData( IPMUnknown* pIterationData, IterationContext nContext ) = 0;


	/**	Determines if the iteration provider is interested in participating in the
		specified iteration context.

		@param nContext		IN the iteration context
		@return bool16		kTrue if interested in participating, kFalse otherwise
	 */
	virtual bool16 InterestedIn( IterationContext nContext ) = 0;

	/**	Whether to stop the iteration.

		@return bool16 kTrue stops the iteration.
	*/
	virtual bool16 StopIterating() const = 0;

	/** Called at the beginning of the iteration.
	*/
	virtual void BeginIteration() = 0;

	/** Called at the end of the iteration.
	*/
	virtual void EndIteration() = 0;

	/**	Beginning of a page or spread in the iteration.

		@param pDoc				IN pointer to the IDocument
		@param nOutputPage		IN index of the current page or spread
		@param refPageOrSpread	IN the UIDRef of the page or spread
		@param rectBounds		IN bounds of the page or spread in that objects coordinate system
		@param boundsToSpreadMatrix	IN the transformation matrix that maps the rectBounds of a page to spread coordinates.
										This matrix will be an identity matrix when printing or exporting spreads.
	 */
	virtual void BeginPageOrSpread(IDocument*		pDoc, 
		                           const int32		nOutputPage, 
		                           const UIDRef		refPageOrSpread, 
								   const PMRect&	rectBounds,
								   const PMMatrix&	boundsToSpreadMatrix ) = 0;

	/**	End of a page or spread.
	*/
	virtual void EndPageOrSpread() = 0;

	/** Process an item on the page. Called for each page item.

		@param masterSpread2LayoutSpreadMatrix	IN the page item's transformation matrix
		@param pPageItem						IN the page item itself
		@param nFlags							IN the current drawing flags
	*/
	virtual void VisitPageItem( const PMMatrix* masterSpread2LayoutSpreadMatrix, IPMUnknown* pPageItem, int32 nFlags) = 0;

	/** Allows the provider to do whatever it wants when the iteration completes. Can be used
		to display error or warning messages.

		@return bool16 if kFalse returned, other providers will not be called (i.e. if the operation was cancelled).
	*/
	virtual bool16 OnIterationCompleted() = 0;

	/** Allows the provider to do cleanup tasks.
	*/
	virtual void Cleanup() = 0;

};

#endif

// End, IDocIterationProvider.h.
