//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/dialogs/FieldOrderDlgController.h $
//  
//  Owner: Tim Wright
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

#include "VCPlugInHeaders.h"

// API:

#pragma once
#ifndef __FieldOrderDialogController__
#define __FieldOrderDialogController__

#include "CDialogController.h"
#include "IDocumentFieldOrder.h"

//------------------------------------------------------------------------
class IDocument;

class FieldOrderDialogController : public CDialogController
{
	public:
		FieldOrderDialogController(IPMUnknown* boss);
		void InitializeDialogFields( IActiveContext* dlgContext);
		void ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId);

	protected:
		virtual void GetOrder( IActiveContext* activeContext, IDocumentFieldOrder::FieldOrder* outOrder ) = 0;
		virtual void SetOrder( IDocument* inDocument, const IDocumentFieldOrder::FieldOrder& inOrder ) = 0;
};

#endif //__FieldOrderDialogController__
