//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ISetTabOrderCmdData.h $
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
#ifndef __ISetTabOrderCmdData__
#define __ISetTabOrderCmdData__

#include "IPMUnknown.h"
#include "UIDRef.h" 
#include "ISpreadFieldOrder.h" 
#include "FormFieldID.h"

/** Data for Set Tab Order command */
class ISetTabOrderCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISETTABORDERCMDDATA };
	
	/** Set the tab order for a page
		@param doc document of page to set
		@param inSpread spread of page to set
		@param inPage page whose order to set
		@param inOrder the ordering of form fields on the page
	*/
	virtual void Set(const	UIDRef&	doc, UID inSpread, UID inPage, const ISpreadFieldOrder::TabOrder& inOrder) = 0;
	
	/** Get the document being changed */
	virtual const UIDRef& GetDocument() const = 0;

	/** Get the UID of the spread being changed */
	virtual UID GetSpread() const = 0;

	/** Get the UID of the page being changed */
	virtual UID GetPage() const = 0;
	
	/** Get the new ordering of the fields on the page */
	virtual ISpreadFieldOrder::TabOrder GetOrder() const = 0;
};


#endif
