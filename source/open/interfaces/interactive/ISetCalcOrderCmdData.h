//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/interactive/ISetCalcOrderCmdData.h $
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

#pragma once
#ifndef __ISetCalculationOrderCmdData__
#define __ISetCalculationOrderCmdData__

#include "IPMUnknown.h"
class UIDRef; 
#include "IDocumentFieldOrder.h"
#include "FormFieldID.h"

/** Data for Set Calculation Order command */
class ISetCalculationOrderCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISETCALCULATIONORDERCMDDATA };

	/** Set the calculation order for a page
		@param doc document of page to set
		@param inOrder the ordering of form fields on the doc
	*/
	virtual void Set(const	UIDRef&	doc, const IDocumentFieldOrder::CalculationOrder& inOrder) = 0;

	/** Get the document being changed */
	virtual const UIDRef& GetDocument() const = 0;
	
	/** Get the new ordering of the fields on the page */
	virtual IDocumentFieldOrder::CalculationOrder GetOrder() const = 0;
};


#endif
