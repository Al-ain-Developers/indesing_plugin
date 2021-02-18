//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/CusCondTxtFacade.h $
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

#ifndef _CusCondTxtResponder_h_
#define _CusCondTxtResponder_h_
#include "Utils.h"
#include "ICusCondTxtFacade.h"
#include "CusCondTxtID.h"

class CusCondTxtFacade : public CPMUnknown<ICusCondTxtFacade>
{
	public:
	
		/** Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
		 */
		CusCondTxtFacade(IPMUnknown* boss);
		
		/** Turns off the visibility of conditions by checking its custom data.
		 
			@param cusCondAttr represents the attribute of custom condition, visibility for print/PDF, or IDML
		 */
		virtual void TurnOffConditionVisibility(IDocument* document, CustomConditionAttr cusCondAttr);
		
		/** Turns on the visibility of conditions by checking its custom data.
		 */
		virtual void TurnOnConditionVisibility(IDocument* document);

		/** Set value of visibility for printing and exporting PDF
			@param item represents the condition tag
			@param value true is visible, false otherwise
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		virtual ErrorCode SetPrintVisibility(const UIDRef& item, bool16 value);
		
		/** Set value of visibility for exporting IDML
			@param item represents the condition tag
			@param value true is visible, false otherwise
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		virtual ErrorCode SetIDMLVisibility(const UIDRef& item, bool16 value);
		
	private:
	
		/** Set custom condition data
			@param item represents the condition tag
			@param cusCondAttr represents the attribute of custom condition, visibility for print/PDF, or IDML
			@param value true is visible, false otherwise
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		virtual ErrorCode SetCustomConditionData(const UIDRef& item, CustomConditionAttr cusCondAttr, bool16 value);
};

#endif