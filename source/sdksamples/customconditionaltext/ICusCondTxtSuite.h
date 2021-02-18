//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/ICusCondTxtSuite.h $
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

#ifndef __CustomConditionTag_h__
#define __CustomConditionTag_h__

// Interface includes:
#include "IPMUnknown.h"

// General includes:

// Project includes:
#include "CusCondTxtID.h"

struct ConditionTagInfo
{
	typedef object_type data_type;
	int32 textStart;
	int32 textEnd;
	K2Vector<UID> tagUIDs;
};

class ICusCondTxtSuite : public IPMUnknown
{
public:
	enum	{kDefaultIID = IID_ICUSCONDTXTSUITE};
	
	/** @return kTrue if conditional data can be accessed, kFalse otherwise.
	 */		
	virtual bool16 CanGetConditionalData() = 0;
	
	/** Get condition tags applied a range text.
		@param condTags the retrieved condition tags.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	virtual ErrorCode GetConditionTags(K2Vector<ConditionTagInfo>& condTags) = 0;
	
	/** Get text which is hidden with conditions applied.
		@param hiddenCondText the retrieved text.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	virtual ErrorCode GetHiddenConditionalText(WideString& hiddenCondText) = 0;
};

#endif



