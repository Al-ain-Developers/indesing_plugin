//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/ICustomConditionTag.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __ICustomConditionTag_h__
#define __ICustomConditionTag_h__

// Interface includes:
#include "IPMUnknown.h"

// General includes:

// Project includes:
#include "CusCondTxtID.h"

class ICustomConditionTag : public IPMUnknown
{
public:

	enum	{kDefaultIID = IID_ICUSTOMCONDITIONTAG};
	
	/** Set visibility for printing and exporting PDF.
		@param visible true is visible
	*/
	virtual void SetPrintVisible(bool16 visible) = 0;
	
	/** @return kTrue visible on printing and exporting PDF, false otherwise.
	*/
	virtual bool16 IsPrintVisible() = 0;

	/** Set visibility for exporting IDML.
		@param visible true is visible
	*/
	virtual void SetIdmlVisible(bool16 visible) = 0;
	
	/** @return kTrue visible on exporting IDML, false otherwise.
	*/
	virtual bool16 IsIdmlVisible() = 0;
};

#endif