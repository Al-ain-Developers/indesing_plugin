//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyexportui/ICSExportAllGraphicsSuite.cpp $
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

#include "CInCopyStoryExportSuite.h"

// Interfaces
#include "ITextTarget.h"
#include "IDocument.h"
#include "ITextTarget.h"
#include "ISelectionManager.h"
#include "IStoryList.h"

#include "ITextRanges.h"
#include "ILayoutTarget.h"
#include "IHierarchy.h"
#include "IXMLUtils.h"
#include "IInCopyWorkFlowUtils.h"
#include "IPageItemTypeUtils.h"

#include "IGraphicFrameData.h"
#include "ISpreadList.h"

// Includes
#include "UIDList.h"
#include "InCopyExportUIID.h"
#include "HelperInterface.h"
#include "Utils.h"

//================================================================================================
//	InCopyStoryExportAllGraphicsSuite
//	
//	This class provides InCopy graphic specific export functionality.
//
//	Only here for one purpose: to get the list of grpahics needed to export
//	This version is used when nothing is selected
//
//================================================================================================
class InCopyStoryExportAllGraphicsSuite : public CInCopyStoryExportSuite
{
	public:
		InCopyStoryExportAllGraphicsSuite ( IPMUnknown *boss );
		
		virtual void ExportToFile(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags);
		
	protected:
	// The only function that really needs to be overriden.... do not export master items
		virtual UIDList GetExportableItemList (IPMUnknown* targetboss) const;
};

CREATE_PMINTERFACE(InCopyStoryExportAllGraphicsSuite, kICExportAllGraphicsSuiteImpl)

InCopyStoryExportAllGraphicsSuite::InCopyStoryExportAllGraphicsSuite(  IPMUnknown *boss ) 
	: CInCopyStoryExportSuite(boss)
{}

void InCopyStoryExportAllGraphicsSuite::ExportToFile(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetboss, const PMString& formatName, UIFlags uiFlags)
{
	ICommandSequence *cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
	cmdSeq->SetName ("Export_All_Graphics");
	
	CInCopyStoryExportSuite::ExportToFile(sysFile, doc, targetboss, formatName, uiFlags);
	
	CmdUtils::EndCommandSequence(cmdSeq);
}


// Shouldn't be too bad.  Make a list of all the graphics in the document, and return it
UIDList InCopyStoryExportAllGraphicsSuite::GetExportableItemList (IPMUnknown* targetboss) const
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
				ASSERT_FAIL("InCopyStoryExportAllGraphicsSuite::GetExportableItemList - No Doc, eh?");
				return returnList;
			}

			return Utils<IInCopyWorkFlowUtils>()->GetNonInCopyGraphicStories(doc, kFalse); // do not include master items
		}
	}
	UIDList nullList;
	return nullList;
}
