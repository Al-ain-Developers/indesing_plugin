//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/suppui/SuppUIQuickApplyFilterService.cpp $
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

// Interface includes
#include "IQuickApplyFilterService.h"

// General includes
#include "K2Vector.tpp"
#include "FindChangeID.h"

// Project includes
#include "SuppUIID.h"
#include "SuppUISuppressedUI.h"

/** Implementation of quick apply filter service. Allows third parties to remove elements from the list of those to be
	added to the quick apply dialog.

	@ingroup suppui
*/
class SuppUIQuickApplyFilterService: public CPMUnknown<IQuickApplyFilterService>
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	SuppUIQuickApplyFilterService(IPMUnknown *boss);

	/**
		Destructor.
	*/
	~SuppUIQuickApplyFilterService(){};
	
	/**
		Allows us to remove items from the quick apply dialog. This implementation removes all paragraph styles
		@param workingList IN/OUT list of items to be filtered. 
	*/
	void FilterItems(K2Vector<QuickApplyFindListNode> &workingList);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(SuppUIQuickApplyFilterService, kSuppUIQuickApplyFilterServiceImpl)

/* 
*/
SuppUIQuickApplyFilterService::SuppUIQuickApplyFilterService(IPMUnknown *boss) :
	CPMUnknown<IQuickApplyFilterService>(boss)
{
}


void SuppUIQuickApplyFilterService::FilterItems(K2Vector<QuickApplyFindListNode> &workingList)
{
	// if the user has not selected this functionality to be filtered, just return.
	if (SuppUISuppressedUI::gSuppressParaStyleQuickApply == kFalse)
		return;

	// we want to remove the set of paragraph styles
	// we remove from the back of the list
	for (K2Vector<QuickApplyFindListNode>::iterator quickApplyListIter = workingList.end(); quickApplyListIter != workingList.begin(); quickApplyListIter--)
	{
		if ((*quickApplyListIter).fType == kQuickApplyParagraphStylesPrefActionID)
		{
			PMString name = (*quickApplyListIter).fName;
			TRACEFLOW(kSuppUIPluginName, "SuppUIQuickApplyFilterService::FilterItems removing %s\n", name.GetUTF8String().c_str());
			workingList.erase(quickApplyListIter);
		}
	}
}
