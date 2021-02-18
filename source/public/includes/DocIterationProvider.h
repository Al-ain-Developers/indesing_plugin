//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DocIterationProvider.h $
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
#ifndef __CDocIterationProvider__
#define __CDocIterationProvider__

#include "IDocIterationProvider.h"
#include "IExportValidationCmdData.h"
#include "HelperInterface.h"

#pragma export on

class PUBLIC_DECL CDocIterationProvider: public IDocIterationProvider
{
public:
	// Constructors and Destructors
	CDocIterationProvider(IPMUnknown* pBoss);
	virtual ~CDocIterationProvider();

	virtual void SetIterationData( IPMUnknown* pIterationData, IterationContext nContext );


	virtual bool16 InterestedIn( IterationContext nContext );

	// returning true stops the iteration.
	virtual bool16 StopIterating() const;

	// bookends for the iteration itself.
	virtual void BeginIteration();
	virtual void EndIteration();

	// bookends for each page or spread in the iteration.
	virtual void BeginPageOrSpread(IDocument*      pDoc, 
		                           const int32     nOutputPage, 
		                           const UIDRef    refPageOrSpread,			//ignored by base class CDocIterationProvider
								   const PMRect&   rectBounds,				//ignored by base class CDocIterationProvider
								   const PMMatrix& boundsToSpreadMatrix);	//ignored by base class CDocIterationProvider
	virtual void EndPageOrSpread();

	// process an item on the page.
	virtual void VisitPageItem( const PMMatrix*   pXForm, 
		                        IPMUnknown* pPageItem, 
								int32       nFlags);

	// allows the provider to do whatever it wants when the iteration completes.
	virtual bool16 OnIterationCompleted();

	// allows the provider to do cleanup tasks.
	virtual void Cleanup();

protected:
	// Utilities
	virtual void Clear();

	bool16 ShowVerificationWarning( IExportValidationCmdData* pData,
	 	                            int32                     nTest);

	bool16 ShowVerificationError(IExportValidationCmdData* pData, int32 nTest);

	bool16 ShowVerificationWarningDontShowAgain( IExportValidationCmdData* pData,
                                                 int32                     nTest,
                                                 int32                     nWarningID);

protected:
	// Member Variables
	IPMUnknown*               fpIterationData;
	IDocument*                fpDocument;
	IterationContext          fnIterationContext;

	int32                fnCurrentPage;
//	UIDRef               frefCurrentPage; -- override BeginPageOrSpread if you need to remember this
//	PMRect               frectCurrentBounds; -- override BeginPageOrSpread if you need to remember this
//	PMMatrix             fcurrentBoundsMatrix; -- override BeginPageOrSpread if you need to remember this

DECLARE_HELPER_METHODS()
};

#pragma export off
#endif

// End, IPrintData.h.
