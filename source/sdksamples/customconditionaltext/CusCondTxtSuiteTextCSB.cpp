//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/CusCondTxtSuiteTextCSB.cpp $
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
#include "ITextTarget.h"
#include "ITextModel.h"
#include "IComposeScanner.h"
#include "IAttrReport.h"
#include "ITextFocus.h"
#include "ITextAttrUIDList.h"
#include "IConditionTag.h"
#include "IItemStrand.h"
#include "ITextStoryThread.h"

// General includes:
#include "SelectionASBTemplates.tpp"
#include "ConditionalTextID.h"
#include "K2Vector.h"
#include "K2Vector.tpp"

// Project includes:
#include "CusCondTxtID.h"
#include "ICusCondTxtSuite.h"							

class CusCondTxtSuiteTextCSB : public CPMUnknown<ICusCondTxtSuite>
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	CusCondTxtSuiteTextCSB (IPMUnknown* boss);
	
	/** Destructor. 
	 */
	virtual ~CusCondTxtSuiteTextCSB (void);

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
CREATE_PMINTERFACE (CusCondTxtSuiteTextCSB, kCusCondTxtSuiteTextCSBImpl)

/* CusCondTxtSuiteTextCSB Constructor
*/
CusCondTxtSuiteTextCSB::CusCondTxtSuiteTextCSB(IPMUnknown* iBoss) :
	CPMUnknown<ICusCondTxtSuite>(iBoss)
{
}

/* CusCondTxtSuiteTextCSB Destructor
*/
CusCondTxtSuiteTextCSB::~CusCondTxtSuiteTextCSB(void)
{
}

bool16 CusCondTxtSuiteTextCSB::CanGetConditionalData()
{
	InterfacePtr<ITextTarget> textTarget(this, UseDefaultIID());
	if (textTarget == nil) {
		return kFalse;
	}

	InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel ());
	return textModel != nil;
}
	
ErrorCode CusCondTxtSuiteTextCSB::GetConditionTags(K2Vector<ConditionTagInfo>& condTags)
{
	ErrorCode err = kFailure;
	
	do {
		InterfacePtr<ITextTarget> textTarget(this, UseDefaultIID());
		if (textTarget == nil) {
			break;
		}

		InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel ());
		if (textModel == nil) {
			break;
		}
		
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		if (textFocus == nil) {
			break;
		}

		TextIndex startTextIndex = textFocus->GetStart(nil);
		if (startTextIndex == kInvalidTextIndex) {
			break;
		}

		TextIndex endTextIndex = textFocus->GetEnd() + 1;
		if (endTextIndex == kInvalidTextIndex) {
			break;
		}

		InterfacePtr<IComposeScanner> composeScanner(textModel, UseDefaultIID());
		if(!composeScanner) {
			break;
		}
		
		do {
			int32 length = 0;
			//query conditional text style
			InterfacePtr<IAttrReport> attr((IAttrReport*)composeScanner->QueryAttributeAt(
																						startTextIndex, 
																						endTextIndex,
																						kConditionalTextAttributeBoss,
																						&length));
			ASSERT(length > 0);
			
			InterfacePtr<ITextAttrUIDList> attrData(attr, UseDefaultIID());
			if(attrData->GetUIDList().size() > 0)
			{
				ConditionTagInfo condTag;
				condTag.textStart = startTextIndex;
				condTag.textEnd = startTextIndex + length;
				condTag.tagUIDs = attrData->GetUIDList();
				condTags.push_back(condTag);
				err = kSuccess;
			}
			
			startTextIndex += length;
		} while(startTextIndex < endTextIndex);		
		
	} while(false);
	
	return err;
}
	
ErrorCode CusCondTxtSuiteTextCSB::GetHiddenConditionalText(WideString& hiddenCondText)
{
	ErrorCode err = kFailure;
	
	do {
		InterfacePtr<ITextTarget> textTarget(this, UseDefaultIID());
		if (textTarget == nil) {
			break;
		}

		InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel ());
		if (textModel == nil) {
			break;
		}
		
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		if (textFocus == nil) {
			break;
		}

		TextIndex startTextIndex = textFocus->GetStart(nil);
		if (startTextIndex == kInvalidTextIndex) {
			break;
		}

		TextIndex threadStart = 0;
		int32 threadSpan = 0;
		textModel->GetStoryThreadSpan(startTextIndex, &threadStart, &threadSpan);
		
		InterfacePtr<IItemStrand> itemStrand((IItemStrand*)textModel->QueryStrand(kOwnedItemStrandBoss, IID_IITEMSTRAND));
		if(!itemStrand) {
			break;
		}
		
		TextIterator ifirst(textModel, startTextIndex);

		UID ownedItemUID = kInvalidUID;
		if (*ifirst == kTextChar_ZeroSpaceNoBreak)
		{
			//the owned item for conditional text is kHiddenTextBoss
			ownedItemUID = itemStrand->GetOwnedUID(ifirst.Position(), kHiddenTextBoss);
		}
		
		if(ownedItemUID == kInvalidUID) {
			break;
		}

		InterfacePtr<ITextStoryThread> hidTextThread(::GetDataBase(textModel), ownedItemUID, UseDefaultIID());
		if(!hidTextThread) {
			break;
		}
			
		InterfacePtr<ITextModel> hidTextModel(hidTextThread->QueryTextModel());
		TextIterator hidTextFirst(hidTextModel, hidTextThread->GetTextStart());
		TextIterator hidTextLast(hidTextModel, hidTextThread->GetTextEnd());
		for(; hidTextFirst != hidTextLast; ++hidTextFirst)
		{
			hiddenCondText.Append(*hidTextFirst);
		}
		err = kSuccess;
		
	} while(false);
	
	return err;
}

// End, CusCondTxtSuiteTextCSB.cpp.



