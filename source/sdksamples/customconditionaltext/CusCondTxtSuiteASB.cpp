//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/CusCondTxtSuiteASB.cpp $
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

#include "VCPlugInHeaders.h"

// Interface includes:

// General includes:
#include "SelectionASBTemplates.tpp"

// Project includes:
#include "CusCondTxtID.h"
#include "ICusCondTxtSuite.h"

class CusCondTxtSuiteASB : public CPMUnknown<ICusCondTxtSuite>
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	CusCondTxtSuiteASB (IPMUnknown* boss);
	
	/** Destructor. 
	 */
	virtual ~CusCondTxtSuiteASB (void);

	/** @see ICusCondTxtSuite.
	 */
	virtual bool16 CanGetConditionalData();
	
	/** @see ICusCondTxtSuite.
	 */
	virtual ErrorCode GetConditionTags(K2Vector<ConditionTagInfo>& condTags);
	
	/** @see ICusCondTxtSuite.
	 */
	virtual ErrorCode GetHiddenConditionalText(WideString& hiddenCondText);
};

/* CREATE_PMINTERFACE
 	Binds the C++ implementation class onto its ImplementationID making the C++ code callable by the application.
*/
CREATE_PMINTERFACE (CusCondTxtSuiteASB, kCusCondTxtSuiteASBImpl)

/* CusCondTxtSuiteASB Constructor
*/
CusCondTxtSuiteASB::CusCondTxtSuiteASB(IPMUnknown* iBoss) :
	CPMUnknown<ICusCondTxtSuite>(iBoss)
{
}

/* CusCondTxtSuiteASB Destructor
*/
CusCondTxtSuiteASB::~CusCondTxtSuiteASB(void)
{
}

bool16 CusCondTxtSuiteASB::CanGetConditionalData()
{
	return (AnyCSBSupports (make_functor(&ICusCondTxtSuite::CanGetConditionalData), this));
}
	
ErrorCode CusCondTxtSuiteASB::GetConditionTags(K2Vector<ConditionTagInfo>& condTags)
{
	return (Process (make_functor(&ICusCondTxtSuite::GetConditionTags, condTags), this, ICusCondTxtSuite::kDefaultIID));
}
	
ErrorCode CusCondTxtSuiteASB::GetHiddenConditionalText(WideString& hiddenCondText)
{
	return (Process (make_functor(&ICusCondTxtSuite::GetHiddenConditionalText, hiddenCondText), this, ICusCondTxtSuite::kDefaultIID));
}

// End, CusCondTxtSuiteASB.cpp.



