//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyfileactionsui/InCopyRecentDocsComponent.cpp $
//  
//  Owner: Robin_Briggs
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
//  NOTE: This plugin and all of its code was given to System Integraters 
//  as a part of Denali. To do this we needed to make sure that no
//  headers from private were included anywhere in this project. This
//  forced us to move FileUtils.h to public. To merge this code with Dragontail
//  if have re-added private access paths to this project. At some point
//  in the future FileUtils.h will need to be made public or another solution 
//  is needed for Mont Blanc. --cparrish 06.24.02
//  
//========================================================================================

#include "VCPlugInHeaders.h"

//interfaces
#include "IApplication.h"
#include "ICommand.h"
#include "IDocumentList.h"
#include "IRecentFileListFacade.h"
#include "IInCopyDocUtils.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "ILibraryCmdUtils.h"
#include "ILibraryService.h"
#include "IOpenFileCmdData.h"

// includes
#include "CActionComponent.h"
#include "CmdUtils.h"
#include "ErrorUtils.h"
#include "FileUtils.h"
#include "OpenPlaceID.h"
#include "RealTimeMark.h"

#include "SysFileList.h"
#include "Utils.h"

#ifdef MACINTOSH
#include "MacFileUtils.h"
#endif

// IDs
#include "InCopyFileActionsUIID.h"


class InCopyRecentDocsComponent : public CActionComponent
{
public:
	InCopyRecentDocsComponent(IPMUnknown *boss) : 
	  CActionComponent(boss)
	  {}

	void DoAction(IActiveContext* ac, ActionID localID, GSysPoint mousePoint, IPMUnknown* widget);
};



CREATE_PMINTERFACE(InCopyRecentDocsComponent, kInCopyRecentDocsComponentImpl)

void InCopyRecentDocsComponent :: DoAction(IActiveContext* ac, ActionID localID, GSysPoint mousePoint, IPMUnknown* widget)
{
	RealTimeMark("Opening previous document");

	int32 fileIndex = localID - kFirstDocActionID;
	if (fileIndex < Utils<Facade::IRecentFileListFacade>()->GetFileCount())	
	{
		const IDFile *fileToOpen = Utils<Facade::IRecentFileListFacade>()->GetNthFile(fileIndex);
		if(nil == fileToOpen)
        {
			// check to make sure file exists.  This avoids annoying assertions later
			ErrorUtils::PMSetGlobalErrorCode(kFileDoesNotExistError);
			return;
		}  

#if defined(MACINTOSH) 
		
		// check if the file to be opened exists
		if (!fileToOpen->Exists())
		{
			ErrorUtils::PMSetGlobalErrorCode(kFileNotFound);
			return;
		}
		
		// Since we resolve aliases to keep tabs on files that have moved, we have to make sure this
		//	file didn't get moved to the trash. It'll briefly appear, then the proxy monitor task will close it.
		
		// Check If the file is in trash
		if (FileUtils::IsFileInTrash(*fileToOpen))
			ErrorUtils::PMSetGlobalErrorCode(kCouldntResolveAliasError);
		else
#endif
		{
			// check to see if it is a book (try document first will result
			// in an error message if it is a book
			ErrorCode result = kSuccess;
			
			SysFileType fileType;
			bool16 knownType = FileUtils::GetOpenFileType(*fileToOpen, fileType);
			// This assert is too aggressive.  If the type is not found then we will open it
			// as an incopy document.  -jargast. bug 625311
			//ASSERT_MSG(knownType, "InCopyRecentDocsComponent::DoAction() - Unknown file type.");

			// first test if it is a book file 
			if (fileType == kBookFileType)
			{
				ASSERT_FAIL("Unsupported file type");
			}
			else if (fileType == kAssetLibraryType)
			{
				InterfacePtr<ILibraryCmdUtils> libraryCmdUtils(ILibraryCmdUtils::QueryLibraryCmdUtils());
				if (libraryCmdUtils)
					result = libraryCmdUtils->OpenLibraryWithUI(*fileToOpen);	// In LibraryCmdUtils.cpp
			}
			else
			{
				Utils<IInCopyDocUtils>()->DoOpen(*fileToOpen, IOpenFileCmdData::kOpenOriginal);
			}

			RealTimeMark("Document opened");
		}
	}
}
