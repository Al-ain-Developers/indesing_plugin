//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyexportui/InCopyStoryExportLayer.cpp $
//  
//  Owner: Ben Park
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
#include "IMasterSpread.h"
#include "IPageItemTypeUtils.h"
#include "ISelectionManager.h"
#include "ISpreadLayer.h"
#include "ISpreadList.h"
#include "IStoryList.h"
#include "ITextFrameColumn.h"
#include "ITextModel.h"

// ----- Includes -----

#include "CInCopyStoryExportSuite.h"
#include "HelperInterface.h"
#include "UIDList.h"

// ----- Utility files -----

#include "IInCopyWorkFlowUtils.h"
#include "ILayerUtils.h"
#include "IStoryUtils.h"
#include "IXMLUtils.h"
#include "Utils.h"

// ----- ID.h files -----

#include "InCopyExportUIID.h"

//================================================================================================
//	InCopyStoryExportLayer
//	
//	This class provides InCopy story specific export functionality.
//
//	This is here to get the list of stories needed to export.
//	This version is used to export all stories off the active layer.
//	NOTE: This has nothing to do with the selection - it bypasses that part completely :)
//
//================================================================================================
class InCopyStoryExportLayer : public CInCopyStoryExportSuite
{
	public:
		InCopyStoryExportLayer ( IPMUnknown *boss );
		
		virtual void ExportToFile(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags);
		
	protected:
	// The only function that really needs to be overriden.... do not export master items
		virtual UIDList GetExportableItemList (IPMUnknown* targetboss) const;
};

CREATE_PMINTERFACE(InCopyStoryExportLayer, kICExportLayerStoriesImpl)

InCopyStoryExportLayer::InCopyStoryExportLayer(  IPMUnknown *boss ) 
	: CInCopyStoryExportSuite(boss)
{}

void InCopyStoryExportLayer::ExportToFile(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags)
{
	ICommandSequence *cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
	cmdSeq->SetName ("Export_Layer");
	
	CInCopyStoryExportSuite::ExportToFile(sysFile, doc, targetboss, formatName, uiFlags);
	
	CmdUtils::EndCommandSequence(cmdSeq);
}


// We're going to loop through the story list, get the first frame of the story, find
// the layer it's on, and see if it's the active layer
UIDList InCopyStoryExportLayer::GetExportableItemList (IPMUnknown* targetboss) const
{
	InterfacePtr<ISelectionManager> selMgr (targetboss, UseDefaultIID());
	IDataBase* db = selMgr->GetDataBase();
	UIDList returnList (db);

	// Does this trick still work?
	InterfacePtr<IDocument> doc ( db, db->GetRootUID(), UseDefaultIID());

	if (!doc)
	{
		ASSERT_FAIL("InCopyStoryExportLayer::GetExportableItemList - No Doc, eh?");
		return returnList;
	}

	// Get the storylist
	InterfacePtr<IStoryList> storyList (doc, UseDefaultIID());

	// Figure out how many we have
	int32 storyCount = storyList->GetUserAccessibleStoryCount();

	// Get the current layer
	InterfacePtr<IDocumentLayer> activeDocLayer (Utils<ILayerUtils>()->QueryDocumentActiveLayer(doc));
	UID activeDocLayerUID = ::GetUID(activeDocLayer);
	
	bool16 exportParentsOnly = kTrue; //preference?

	// Loop through the storyList
	for (int32 i = 0; i < storyCount; i++)
	{
		InterfacePtr<ITextModel> currentModel (storyList->GetNthUserAccessibleStoryUID(i), UseDefaultIID());
		InterfacePtr<IFrameList> frameList (currentModel->QueryFrameList());

		if (frameList->GetFrameCount() > 0) // What can I say - I'm paranoid...
		{
			// Get the layer that the first frame is on
			InterfacePtr<IHierarchy> frameHier (db, frameList->GetNthFrameUID(0), UseDefaultIID());
			UID layerUID = Utils<ILayerUtils>()->GetLayerUID (frameHier);
			InterfacePtr<ISpreadLayer> spreadLayer (db, layerUID, UseDefaultIID());
			if (!spreadLayer)
				continue;

			UID docLayerUID = spreadLayer->GetDocLayerUID();

			// Now compare the layer with the active layer
			if (docLayerUID == activeDocLayerUID)
			{
				if (exportParentsOnly)
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

				// Last check - if the story is already an InCopyStory, then we don't want to export it again
				UIDRef modelRef( ::GetUIDRef(currentModel) );
				if (!Utils<IStoryUtils>()->IsAStory( modelRef ) &&
					!Utils<IInCopyWorkFlowUtils>()->IsAFormObject( modelRef ) &&
					Utils<IXMLUtils>()->IsExportableInCopyStory( modelRef ))
				{
					// Append the model to the list
					returnList.Append(modelRef.GetUID());
				}
			}
		}
	}

	// now add in the layer's graphic page items
	returnList.Append(Utils<IInCopyWorkFlowUtils>()->GetAllGraphics(doc, kFalse, activeDocLayerUID, kFalse)); // do not include master items

	return returnList;
}
