//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvUtils.cpp $
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
#include "IImportExportFacade.h"
#include "IImportResourceCmdData.h"
#include "IDocument.h"
#include "IPlaceGun.h"
#include "IPanelControlData.h"
#include "IUIDData.h"
#include "IPnlTrvOptions.h"
#include "IWorkspace.h"
#include "IURIUtils.h"

// Other API includes
#include "K2SmartPtr.h"
#include "SDKFileHelper.h"
#include "IPalettePanelUtils.h"
#include "TextChar.h"
#include "ErrorUtils.h"

// Project includes
#include "PnlTrvUtils.h"


#ifdef WINDOWS
#define PLATFORM_PATH_DELIMITER kTextChar_ReverseSolidus
#endif
#ifdef MACINTOSH
#define PLATFORM_PATH_DELIMITER kTextChar_Colon
#endif


/* TruncatePath
*/
PMString PnlTrvUtils::TruncatePath(const PMString& fromthis)
{
	if(fromthis.empty() == kTrue) return PMString("Empty!");

	PMString retval = fromthis;
	int32 lastpos = (-1);
	for (int32 i = 0 ; i < fromthis.CharCount();i++)
	{
		bool16 predicate = (fromthis[i] == PLATFORM_PATH_DELIMITER);
		if (predicate)
		{
			lastpos = i;
		}
	}

	if(lastpos >= 0)
	{
		// Suppose we have ../X/Y.gif
		// Then, lastpos would be 4, and we'd want 5 chars from 5 onwards
		int32 countChars = fromthis.CharCount() - (lastpos+1);
		int32 startIndex = lastpos+1;
		int32 endIndex = (startIndex + countChars);
		if((endIndex > startIndex) && (endIndex <= fromthis.CharCount()))
		{
			K2::scoped_ptr<PMString> ptrRightStr(fromthis.Substring(startIndex, countChars));
			if(ptrRightStr)
			{
				retval = *ptrRightStr;
			}
		}
	} 
	return retval;
}


/* ImportImageAndLoadPlaceGun
*/
UIDRef PnlTrvUtils::ImportImageAndLoadPlaceGun(
	const UIDRef& docUIDRef, const PMString& fromPath)
{
	// Precondition: active document
	// Precondition: file exists
	// 
	UIDRef retval = UIDRef::gNull;
	do
	{
		SDKFileHelper fileHelper(fromPath);
		bool16 fileExists = fileHelper.IsExisting();
		// Fail quietly... ASSERT(fileExists);
		if(!fileExists)
		{
			break;
		}
		InterfacePtr<IDocument> 
			iDocument(docUIDRef, UseDefaultIID());
		ASSERT(iDocument);
		if(!iDocument)
		{
			break;
		}

		// Wrap the import in a command sequence.
		PMString seqName("Import");
		CmdUtils::SequenceContext seq(&seqName);

		// If the place gun is already loaded abort it so we can re-load it. 
		InterfacePtr<IPlaceGun> placeGun(iDocument, UseDefaultIID());
		ASSERT(placeGun);
		if (!placeGun) 
		{
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}
		if (Utils<Facade::IImportExportFacade>()->AbortPlaceGun( placeGun, Facade::IImportExportFacade::kAllItems ) != kSuccess) 
		{
			ASSERT_FAIL("AbortPlaceGun failed");
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}

		// Now import the selected file and load it's UID into the place gun.
		IDataBase* db = docUIDRef.GetDataBase();
		ASSERT(db);
		if(!db)
		{
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}

#pragma message("LINKREWORK: Temporary, fix this up later!")
// TODO: LINKREWORK fix.

		URI tmpURI;
		Utils<IURIUtils>()->IDFileToURI(fileHelper.GetIDFile(), tmpURI);
		const bool16 retainFormat = kFalse ;
		const bool16 convertQuotes = kFalse ;
		const bool16 applyCJKGrid = kFalse ;
		bool16 useClippingFrame, skipPlace ;
		ErrorCode err = Utils<Facade::IImportExportFacade>()->ImportAndLoadPlaceGun(db, tmpURI, kMinimalUI, 
			retainFormat, convertQuotes, applyCJKGrid, useClippingFrame, skipPlace ) ;
		ASSERT(err == kSuccess);
		if(err != kSuccess)
		{
			break;
		}	
		// Get the contents of the place gun as our return value
		UIDRef placedItem(db, placeGun->GetFirstPlaceGunItemUID());
		retval = placedItem; 
	} while(kFalse);

	return retval;
}


/* GetWidgetOnPanel
*/
IControlView* PnlTrvUtils::GetWidgetOnPanel(
	const WidgetID& panelWidgetID, const WidgetID& widgetID)
{
	IControlView* controlView=nil;
	do
	{
		InterfacePtr<IPanelControlData> 
			panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(panelWidgetID));	
		// Don't assert, fail silently, the tree view panel may be closed.
		if(panelData == nil)
		{
			break;
		}
		controlView = panelData->FindWidget(widgetID);
		ASSERT(controlView);
		if(controlView == nil)
		{
			break;
		}
	} while(0);
	
	return controlView;
}



PMString PnlTrvUtils::GetFolderSelectedPath()
{
	PMString retval="";
	do
	{
		InterfacePtr<IWorkspace> 
			sessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(sessionWorkspace);
		if(sessionWorkspace == nil)
		{
			break;
		}
		InterfacePtr<IPnlTrvOptions>
			pnlTrvOptions(sessionWorkspace, UseDefaultIID());
		ASSERT(pnlTrvOptions);
		if(!pnlTrvOptions)
		{
			break;
		}
		retval = pnlTrvOptions->GetNthOption(0);
		
	} while(kFalse);
	return retval;
}

//	end, File: PnlTrvUtils.cpp
