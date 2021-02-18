//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/ICusCondTxtFacade.h $
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

#ifndef __ICusCondTxtFacade_H_DEFINED__
#define __ICusCondTxtFacade_H_DEFINED__

// Interface includes:
#include "IPMUnknown.h"
// Project includes:
#include "CusCondTxtID.h"

class IDocument;

class ICusCondTxtFacade : public IPMUnknown
	{
		
	public:
		/** Default interface identifier for UseDefaultIID 
		 @see UseDefaultIID
		 */
		enum { kDefaultIID = IID_ICUSCONDTXTFACADE };
		
		enum CustomConditionAttr {kPrintVisibility, kIdmlVisibility};
		
		/** Turns off the visibility of conditions by checking its custom data.
		 
		 @param cusCondAttr represents the attribute of custom condition, visibility for print/PDF, or IDML
		 */
		virtual  void TurnOffConditionVisibility(IDocument* document, CustomConditionAttr cusCondAttr)=0;
		
		/** Turns on the visibility of conditions by checking its custom data.
		 */
		virtual  void TurnOnConditionVisibility(IDocument* document) = 0;
		
		/** Set value of visibility for printing and exporting PDF
		 @param item represents the condition tag
		 @param value true is visible, false otherwise
		 @return kSuccess on success, other ErrorCode otherwise.
		 */
		virtual ErrorCode SetPrintVisibility(const UIDRef& item, bool16 value) = 0;
		
		/** Set value of visibility for exporting IDML
		 @param item represents the condition tag
		 @param value true is visible, false otherwise
		 @return kSuccess on success, other ErrorCode otherwise.
		 */
		virtual ErrorCode SetIDMLVisibility(const UIDRef& item, bool16 value) = 0;
		
	private:
		
		/** Set custom condition data
		 @param item represents the condition tag
		 @param cusCondAttr represents the attribute of custom condition, visibility for print/PDF, or IDML
		 @param value true is visible, false otherwise
		 @return kSuccess on success, other ErrorCode otherwise.
		 */
		virtual ErrorCode SetCustomConditionData(const UIDRef& item, CustomConditionAttr cusCondAttr, bool16 value) = 0;
	};

#endif // __ICusCondTxtFacade_H_DEFINED__

