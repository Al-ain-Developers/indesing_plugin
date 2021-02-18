//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyexportui/InCopyStoryExportAllSuite.cpp $
//  
//  Owner: Lonnie Millett
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
//  
//  This file contains the specific implementations of the InCopyStoryExportSuite that are specific to each CSB.  The majority
//  of the content is the same between them all - the only difference is in how the stories are collected for export.  The 
//  method GetExportableItemList is overriden in each case to deal with this.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IDocument.h"
#include "IFrameList.h"
#include "IGraphicFrameData.h"
#include "IHierarchy.h"
#include "ILayoutTarget.h"
#include "IMasterSpread.h"
#include "ISelectionManager.h"
#include "ISpreadList.h"
#include "IStoryList.h"
#include "ITextFrameColumn.h"
#include "ITextRanges.h"
#include "ITextTarget.h"
#include "IXMLUtils.h"

// ----- Includes -----

#include "CInCopyStoryExportSuite.h"
#include "HelperInterface.h"
#include "UIDList.h"

// ----- Utility files -----

#include "IInCopyWorkFlowUtils.h"
#include "IStoryUtils.h"
#include "IPageItemTypeUtils.h"
#include "Utils.h"

// ----- ID.h files -----

#include "InCopyExportUIID.h"



//================================================================================================
//	InCopyStoryExportAllSuite
//	
//	This class provides InCopy story and graphics specific export functionality.
//
//	Only here for one purpose: to get the list of stories needed to export
//	This version is used when nothing is selected
//
//================================================================================================
class InCopyStoryExportAllSuite : public CInCopyStoryExportSuite
{
	public:
		InCopyStoryExportAllSuite ( IPMUnknown *boss );
		
		virtual void ExportToFile(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags);
		
	protected:
	// The only function that really needs to be overriden.... do not export master items
		virtual UIDList GetExportableItemList (IPMUnknown* targetboss) const;
};

CREATE_PMINTERFACE(InCopyStoryExportAllSuite, kICExportAllSuiteImpl)

InCopyStoryExportAllSuite::InCopyStoryExportAllSuite(  IPMUnknown *boss ) 
	: CInCopyStoryExportSuite(boss)
{}

void InCopyStoryExportAllSuite::ExportToFile(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags)
{
	ICommandSequence *cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
	cmdSeq->SetName ("Export_All_Stories");
	
	CInCopyStoryExportSuite::ExportToFile(sysFile, doc, targetboss, formatName, uiFlags);
	
	CmdUtils::EndCommandSequence(cmdSeq);
}


// Shouldn't be too bad.  Make a list of all the stories in the storylist, and return it
// Actually need to restrict list if targetboss is not a selection manager
UIDList InCopyStoryExportAllSuite::GetExportableItemList (IPMUnknown* targetboss) const
{	
	IDataBase* db = nil;
	// NOTE: I'm not sure if the selections owner is the workspace...
	// OTHER NOTE: It ain't... :)
	InterfacePtr<ISelectionManager> selMgr (targetboss, UseDefaultIID());
	if (selMgr)
	{
		db = selMgr->GetDataBase();
		if (db)
		{
			UIDList returnList(db);
			InterfacePtr<IDocument> doc ( db, db->GetRootUID(), UseDefaultIID());
			if (!doc)
			{
				ASSERT_FAIL("InCopyStoryExportAllSuite::GetExportableItemList - No Doc, eh?");
				return returnList;
			}

			bool16 exportParentsOnly = kTrue; //preference?
		
			// Get the storylist
			InterfacePtr<IStoryList> storyList (doc, UseDefaultIID());
		
			// Construct a list of user accessible stories.
			int32 storyCount = storyList->GetUserAccessibleStoryCount();
		
			for (int32 i = 0; i < storyCount; i++)
			{
				UIDRef ithStory = storyList->GetNthUserAccessibleStoryUID(i);
				
				if (exportParentsOnly)
				{
					InterfacePtr<ITextModel> textModel(ithStory, UseDefaultIID());
					InterfacePtr<IFrameList> frameList(textModel->QueryFrameList());
					if (frameList)
					{
						if (frameList->GetFrameCount() > 0)
						{
							InterfacePtr<ITextFrameColumn> tfc(frameList->QueryNthFrame(0));
							InterfacePtr<IHierarchy> inlineHier(tfc, UseDefaultIID());
							if (inlineHier)
							{
								if (Utils<IPageItemTypeUtils>()->IsInline(inlineHier))
								{
									continue;
								}
							}

							// do not include master items
							InterfacePtr<IMasterSpread> isMasterSpread(db, inlineHier->GetSpreadUID(), UseDefaultIID());
							if(isMasterSpread)
							{
								continue;
							}
						}
					}
				}

				// Ok, we check to see if it's already an InCopy story.  If it is, we don't add it
				if (!Utils<IStoryUtils>()->IsAStory( ithStory ) && 
					!Utils<IInCopyWorkFlowUtils>()->IsAFormObject( ithStory ) &&
					Utils<IXMLUtils>()->IsExportableInCopyStory( ithStory ))
					returnList.Append(ithStory.GetUID());
			}

			returnList.Append(Utils<IInCopyWorkFlowUtils>()->GetNonInCopyGraphicStories(doc, kFalse)); // do not include master items

			return returnList;
		}
	}

	UIDList nullList;
	return nullList;
}
