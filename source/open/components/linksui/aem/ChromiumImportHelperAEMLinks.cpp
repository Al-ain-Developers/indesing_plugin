//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/aem/ChromiumImportHelperAEMLinks.cpp $
//  
//  Owner: Swati Garg
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2015 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "CPMUnknown.h"

#include "IChromiumImportHelper.h"
#include "IActiveContext.h"
#include "IBoolData.h"
#include "IControlView.h"
#include "IConcreteSelection.h"
#include "ICursorMgr.h"
#include "IDocument.h"
#include "IHierarchy.h"
#include "IImportExportFacade.h"
#include "IImportSuite.h"
#include "ILayoutUIUtils.h"
#include "ILayoutHitTestSuite.h"
#include "ILayerList.h"
#include "ILinkCmdSuite.h"
#include "ILinkFacade.h"
#include "ILinkUtils.h"
#include "IPageItemTypeUtils.h"
#include "IPasteboardUtils.h"
#include "ISpread.h"
#include "ITextFragmentLinkFacade.h"
#include "IXMLUtils.h"
#include "IXMLReferenceData.h"

#include "CAlert.h"
#include "ProgressBar.h"
#include "PreferenceUtils.h"
#include "LinksUIID.h"
#include "ErrorUtils.h"
#include "EventUtilities.h"
#include "IJsonUtils.h"
#include "SelectionUtils.h"
#include "StringUtils.h"

//========================================================================================
// Class ChromiumImportHelperAEMLinks
//========================================================================================
class ChromiumImportHelperAEMLinks : public CPMUnknown<IChromiumImportHelper>
{
public:
	typedef CPMUnknown<IChromiumImportHelper> inherited;

	ChromiumImportHelperAEMLinks(IPMUnknown* boss);
	virtual ~ChromiumImportHelperAEMLinks();

	virtual bool16 IsSupportingSourceAttributeInJsonData();
	virtual const char* GetSourceAttribute();
	virtual void ImportData(std::stringstream &jsonDataStringStream, UIFlags uiFlags);

private:
	// Prevent copy construction and assignment.
	ChromiumImportHelperAEMLinks(const ChromiumImportHelperAEMLinks&);
	ChromiumImportHelperAEMLinks& operator=(const ChromiumImportHelperAEMLinks&);
	void ImportAEMAssets(JSON &jsonChromiumData, UIFlags uiFlags);
	
	void ImportAEMAlert(const int32 totalAssetCount, const int32 unSupportedFilesCount, const int32 inAccessibleFilesCount, const int32 unKnownFilesCount) const;
	void ImportAEMGenericAlert(const ErrorCode& errCode) const;
	void ImportAEMGenericAlert(const PMString& message) const;
	void ImportAEMGenericAlert() const;
};


CREATE_PMINTERFACE(ChromiumImportHelperAEMLinks, kChromiumImportHelperAEMLinksImpl)


//========================================================================================
//
// ChromiumImportHelperAEMLinks Public Implementation
//
//========================================================================================

//========================================================================================
// Constructor
//========================================================================================
ChromiumImportHelperAEMLinks::ChromiumImportHelperAEMLinks(IPMUnknown* boss)
: inherited(boss)
{
}

//========================================================================================
// Destructor
//========================================================================================
ChromiumImportHelperAEMLinks::~ChromiumImportHelperAEMLinks()
{
}

//========================================================================================
// ChromiumImportHelperAEMLinks::IsSupportingSourceAttributeInJsonData
//========================================================================================
bool16 ChromiumImportHelperAEMLinks::IsSupportingSourceAttributeInJsonData()
{
	return kTrue;
}

//========================================================================================
// ChromiumImportHelperAEMLinks::GetSourceAttribute
//========================================================================================
const char* ChromiumImportHelperAEMLinks::GetSourceAttribute()
{
	return "com.adobe.assetlink";
}

//========================================================================================
// ChromiumImportHelperAEMLinks::ImportData
//========================================================================================
void ChromiumImportHelperAEMLinks::ImportData(std::stringstream &jsonDataStringStream, UIFlags uiFlags)
{
	JSON jsonObj;
	try
	{
		jsonObj.read_json(jsonDataStringStream);
	}
	catch (...)
	{
		//Error in parsing the json
		ErrorUtils::PMSetGlobalErrorCode(kFailure);
		return;
	}

	std::string typeOfAEMAssets = jsonObj.GetString("type");
    
	if (typeOfAEMAssets == "asset")
	{
		ImportAEMAssets(jsonObj, uiFlags);
	}
}

//========================================================================================
// ChromiumImportHelperAEMLinks::ImportAEMAssets
//========================================================================================
void ChromiumImportHelperAEMLinks::ImportAEMAssets(JSON &jsonChromiumData, UIFlags uiFlags)
{
	std::vector<URI> uriList;
    
    bool16 embedLinks = kFalse, dragdrop = kFalse;

	JSONArray assetList;
	jsonChromiumData.GetListAt("assetList", assetList);

	if (assetList.size() == 0)
	{
		return;
	}

    if (jsonChromiumData.checkKey("embed") && jsonChromiumData.GetString("embed") == "true")
        embedLinks = kTrue;
    
    
    if (jsonChromiumData.checkKey("dragdrop") && jsonChromiumData.GetString("dragdrop") == "true")
        dragdrop = kTrue;
    
	//Prepare a list of files to be loaded into the place gun
	int32 skippedFilesCount = 0;
	for (auto& asset : assetList)
	{
		//skip this asset
		if (!asset.checkKey("path"))
			continue;

		std::string assetPathStr = asset.GetString("path");
		if ((assetPathStr.length() == 0))
		{
			//No assetPath
			continue;
		}

		//skipping ICML related files because we are not supporting them in current work flow.
		//TODO: once ICML related workflow is added for AEM assets, please remove this logic.
		bool16 skippedFlag = kFalse;
		size_t fileExtpos = (int32)assetPathStr.find_last_of('.');
		if (fileExtpos != std::string::npos)
		{
			std::string   fileExt(assetPathStr.substr(fileExtpos + 1));
			std::string   skippedFiles[] = { "ICML", "INCD", "INCX" };
			const int32 skippedFilesType = 3;
			std::transform(fileExt.begin(), fileExt.end(), fileExt.begin(), ::toupper);

			for (int32 i = 0; i < skippedFilesType; i++)
			{
				if (fileExt == skippedFiles[i])
				{
					skippedFlag = kTrue;//skip this asset
					skippedFilesCount++;
					break;
				}
			}
		}
        
		if (!skippedFlag)
		{
			PMString filePathString;
			filePathString.SetUTF8String(assetPathStr.c_str());
			WideString wFilePathString(filePathString);
			uriList.push_back(wFilePathString);
		}
	}

	//Find the active document and its front most view
	IActiveContext* ac = GetExecutionContextSession()->GetActiveContext();
	IDocument* activeDoc = ac->GetContextDocument();
	IControlView* view = ac->GetContextView();
	if (!view)
	{
		ImportAEMGenericAlert();
		return;
	}

	InterfacePtr<ILayoutControlData> layoutControlData(view, UseDefaultIID());
	if (!layoutControlData)
	{
		ImportAEMGenericAlert();
		return;
	}


	//Calculate cursor position in PasteBoard coordinates
	GSysPoint globalPoint;
	globalPoint = ::GetGlobalMouseLocation();

	PMPoint convertedPoint = Utils<ILayoutUIUtils>()->ComputePasteboardPoint(globalPoint, view);

	ErrorCode err = kFailure;

	InterfacePtr<ISpread> spread(Utils<IPasteboardUtils>()->QueryNearestSpread(view, convertedPoint));

	if (!spread)
	{
		ImportAEMGenericAlert();
		return;
	}

	IDataBase* db = ::GetDataBase(spread);

	size_t noOfURIs = uriList.size();
	if (noOfURIs == 0)
	{
		if (skippedFilesCount)
		{
			ImportAEMAlert((int32)noOfURIs + skippedFilesCount, skippedFilesCount, 0, 0);
		}
		return;
	}

    
    InterfacePtr<IPlaceGun> placeGun(db, db->GetRootUID(), UseDefaultIID());
    int32 numItemsInPlaceGunBeforeImport = placeGun->CountPlaceGunUIDs();
    
	bool16 showTaskStatus = (noOfURIs > 1);
	TaskProgressBar	progress((showTaskStatus ? "kImportingAEMAssets" : "kImportingAEMAsset"), (int32)noOfURIs, kTrue);
	progress.DisableChildProgressBars(kTrue);


	//We have the file list now lets import

	int32 modifierKeys = ICursorMgr::kNoModifiers;
	uiFlags = kMinimalUI;

	int32 unSupportedFilesCount = 0;
	int32 inAccessibleFilesCount = 0;
	int32 unKnownFilesCount = 0;
	int32 importFailureCount = 0;

	PMString totalAssets;
	totalAssets.AppendNumber((int32)uriList.size());
	totalAssets.SetTranslatable(kFalse);

	PMString templatedTaskString("kImportingAssetName");
	templatedTaskString.Translate();

	PMString templatedFileNameString("kImportingFileName");
	templatedFileNameString.Translate();
	bool16 shouldAutoTagAssets = kFalse;
	InterfacePtr<IBoolData> shouldTagAEMAssetsPref((IBoolData*)::QuerySessionPreferences(IID_IHTTPLINKS_AUTO_TAG_ASSET_PREFERENCE));
	if (shouldTagAEMAssetsPref)
	{
		shouldAutoTagAssets = shouldTagAEMAssetsPref->Get();
	}

	for (size_t fileIndex = 0; fileIndex < noOfURIs; ++fileIndex)
	{
		URI uri = uriList[fileIndex];

		PMString taskString(templatedTaskString);
		PMString currentIndex;
		currentIndex.AppendNumber((int32)(fileIndex + 1));
		currentIndex.SetTranslatable(kFalse);
		::ReplaceStringParameters(&taskString, currentIndex, totalAssets);
		progress.SetTaskStatus(taskString);

		PMString fileNameString(templatedFileNameString);
		PMString fileName;
        
		// Get filename from uri
		fileName = uri.GetComponent(URI::kPath);
		CharCounter pos = fileName.LastIndexOfWChar(kTextChar_Solidus);  // find the last slash ('/') 
		if (pos != -1) {
			fileName.Remove(0, pos + 1);
		}
		fileName.SetTranslatable(kFalse);
		::ReplaceStringParameters(&fileNameString, fileName);

		progress.DoTask(fileNameString);

        // Set Default rendition type to kOriginal (AAL is not supporting FPO currently)
        ErrorCode err = Utils<Facade::ILinkFacade>()->SetHTTPLinksDefaultRenditionType(ILinkResourceRenditionData::kOriginal);
        
        ISelectionManager* currentSelection = ::GetExecutionContextSession()->GetActiveContext()->GetContextSelection();
        InterfacePtr<IImportSuite> iImportSuite(SelectionUtils::QuerySuite<IImportSuite>(currentSelection));
        
        if (dragdrop)
            err = Utils<Facade::IImportExportFacade>()->ImportAndLoadPlaceGun(db, uri, uiFlags, kFalse, kFalse, kFalse, UID(kInvalidUID), IPlaceGun::kAddToBack);
        else
            if (iImportSuite->DoImport(uri, db, kTrue, uiFlags, kFalse, kFalse, kFalse) == kTrue)
                err = kSuccess;

		if (progress.WasCancelled())
		{
			ErrorUtils::PMSetGlobalErrorCode(err);
			break;
		}
		if (err != kSuccess)
		{
			if (err == kNoFilterFoundError) //Unsupported file
			{
				unSupportedFilesCount++;
			}
			else if (err == kFileDoesNotExistError || err == kFileInaccessibleError) //missing or inaccessible file
			{
				inAccessibleFilesCount++;
			}
			else
			{
				unKnownFilesCount++; //unKnown error
			}
			importFailureCount++;
			ErrorUtils::PMSetGlobalErrorCode(kSuccess);
		}
		else
		{
			if (shouldAutoTagAssets)
			{
				uint32 placeGunItems = placeGun->CountPlaceGunUIDs();
				if (placeGunItems >= 1)
				{
					UID newlyPlacedItem = placeGun->GetNthPlaceGunItemUID(placeGunItems - 1);
					UIDList itemsToTag(db, newlyPlacedItem);
					bool16 canAutoTagItems = kFalse;

					for (int32 i = 0; i < itemsToTag.Length(); ++i)
					{
						InterfacePtr<IHierarchy> hier(itemsToTag.GetRef(i), UseDefaultIID());
						// Make sure this item type is actually taggable 
						if (Utils<IXMLUtils>()->IsTaggablePageItem(hier))
						{
							// Now make sure that it isn't already tagged 
							InterfacePtr<IXMLReferenceData> xmlReferenceData(Utils<IXMLUtils>()->QueryXMLReferenceData(hier));
							if (!xmlReferenceData /* possible? */ || xmlReferenceData->GetReference() == kInvalidXMLReference)
							{
								// Finally make sure it isn't a locked story 
								if (!Utils<IXMLUtils>()->IsStoryLocked(itemsToTag.GetRef(i)))
								{
									canAutoTagItems = kTrue; // found unlocked, untagged, taggable page item
									break;
								}

							}
						}
					}


					if (canAutoTagItems)
					{
						ErrorCode err = Utils<IXMLUtils>()->SetLayoutTag(itemsToTag, UIDRef::gNull, kFalse, kFalse);
						ErrorUtils::PMSetGlobalErrorCode(kSuccess);
					}
				}
			}
		}
	}

    if (embedLinks)
    {
        // Did the uris end up in the place gun?
        int32 numItemsInPlaceGun = placeGun->CountPlaceGunUIDs();
        if (numItemsInPlaceGun != numItemsInPlaceGunBeforeImport && numItemsInPlaceGun > 0)
        {
            int32 assetsToEmbed = numItemsInPlaceGun - numItemsInPlaceGunBeforeImport;
            
            for (int i = 1; i <= assetsToEmbed; i++)
            {
                UID pageItem = placeGun->GetNthPlaceGunItemUID(numItemsInPlaceGun - i);
                UID linkUID = Utils<ILinkUtils>()->FindLink(UIDRef(db, pageItem));
                InterfacePtr<ILinkCmdSuite> iLinkCmdSuite(db, db->GetRootUID(), UseDefaultIID());
                if (linkUID != kInvalidUID)
                    iLinkCmdSuite->EmbedLinks(UIDList(db, linkUID));
            }
        }
        else
        {
            // Get page items in the selection.
            InterfacePtr<ISelectionManager> selectionManager(Utils<ISelectionUtils>()->QueryActiveSelection());
            if (!selectionManager)
                return;
            
            InterfacePtr<ILayoutHitTestSuite> selection(Utils<ISelectionUtils>()->QueryLayoutHitTestSuite(selectionManager));
            if (!selection)
                return;
            
            InterfacePtr<IConcreteSelection> layoutCSB(selection, UseDefaultIID());
            InterfacePtr<ILayoutTarget> layoutTarget(layoutCSB, UseDefaultIID());
            UIDList pageItems = layoutTarget->GetUIDList(kDontStripStandoffs);
            // Remove any guides from the selection.
            Utils<IPageItemTypeUtils> pageItemTypeUtils;
            int32 numItems = pageItems.Length();
            for (int32 i = numItems - 1; i >= 0; i--)
            {
                if (pageItemTypeUtils->IsGuide(pageItems.GetRef(i)))
                    pageItems.Remove(i);
            }
            numItems = pageItems.Length();
            if (numItems == 1)
            {
                UIDRef pageItemRef = pageItems.GetRef(0);
                UID linkResourceUID = Utils<ILinkUtils>()->FindLinkResource(pageItemRef);
                InterfacePtr<ILinkResource> iLinkResource(pageItemRef.GetDataBase(), linkResourceUID, UseDefaultIID());
                if (iLinkResource && iLinkResource->GetId() == uriList[0])
                {
                    UID linkUID = Utils<ILinkUtils>()->FindLink(pageItemRef);
                    InterfacePtr<ILinkCmdSuite> iLinkCmdSuite(db, db->GetRootUID(), UseDefaultIID());
                    iLinkCmdSuite->EmbedLinks(UIDList(db, linkUID));
                }
            }
        }
        
    }
    
	if (importFailureCount || skippedFilesCount)
	{
		ImportAEMAlert((int32)noOfURIs + skippedFilesCount, unSupportedFilesCount + skippedFilesCount, inAccessibleFilesCount, unKnownFilesCount);
	}
	return;
}


//========================================================================================
// ChromiumImportHelperAEMLinks::ImportAEMGenericAlert
//========================================================================================
void ChromiumImportHelperAEMLinks::ImportAEMGenericAlert(const ErrorCode& errCode) const
{
	PMString errorString = ErrorUtils::PMGetErrorString(errCode);
	
	if (errorString.empty())
	{
		ImportAEMGenericAlert();
		return;
	}
	ImportAEMGenericAlert(errorString);
}

//========================================================================================
// ChromiumImportHelperAEMLinks::ImportAEMGenericAlert
//========================================================================================
void ChromiumImportHelperAEMLinks::ImportAEMGenericAlert(const PMString& message) const
{
	CAlert::InformationAlert(message);
}

//Alert on generic failures while import aem based content
//========================================================================================
// ChromiumImportHelperAEMLinks::ImportAEMGenericAlert
//========================================================================================
void ChromiumImportHelperAEMLinks::ImportAEMGenericAlert() const
{
	ImportAEMGenericAlert(PMString("AEMGenericImportFailure"));
}

//Alert on File failure from AAL panel
//========================================================================================
// ChromiumImportHelperAEMLinks::ImportAEMAlert
//========================================================================================
void ChromiumImportHelperAEMLinks::ImportAEMAlert(const int32 totalAssetCount, const int32 unSupportedFilesCount, const int32 inAccessibleFilesCount, const int32 unKnownFilesCount) const
{
	PMString totalAssetCountStr;
	totalAssetCountStr.AppendNumber((int32)totalAssetCount);
	totalAssetCountStr.SetTranslatable(kFalse);

	int32 importFailureCount = unSupportedFilesCount + inAccessibleFilesCount + unKnownFilesCount;

	if (unSupportedFilesCount == importFailureCount)//only Unsupported
	{
		PMString message("AEMUnsupportedFiles");
		message.Translate();

		PMString unSupportedFilesString;
		unSupportedFilesString.AppendNumber((int32)unSupportedFilesCount);
		unSupportedFilesString.SetTranslatable(kFalse);

		StringUtils::ReplaceStringParameters(&message, unSupportedFilesString, totalAssetCountStr);
		CAlert::InformationAlert(message);
	}

	else if (inAccessibleFilesCount == importFailureCount)//only Inaccessible
	{
		PMString message("AEMInaccessibleFiles");
		message.Translate();

		PMString inAccessibleFilesString;
		inAccessibleFilesString.AppendNumber((int32)inAccessibleFilesCount);
		inAccessibleFilesString.SetTranslatable(kFalse);

		StringUtils::ReplaceStringParameters(&message, inAccessibleFilesString, totalAssetCountStr);
		CAlert::InformationAlert(message);
	}
	else if (unKnownFilesCount == importFailureCount)//only Unknown
	{
		PMString message("AEMUnknownFiles");
		message.Translate();

		PMString unKnownFilesString;
		unKnownFilesString.AppendNumber((int32)unKnownFilesCount);
		unKnownFilesString.SetTranslatable(kFalse);

		StringUtils::ReplaceStringParameters(&message, unKnownFilesString, totalAssetCountStr);
		CAlert::InformationAlert(message);
	}
	else
	{
		PMString message("AEMMixedImportFailedFiles");
		message.Translate();

		PMString importFailFilesString;
		importFailFilesString.AppendNumber((int32)importFailureCount);
		importFailFilesString.SetTranslatable(kFalse);

		PMString unSupportedFilesString;
		unSupportedFilesString.AppendNumber((int32)unSupportedFilesCount);
		unSupportedFilesString.SetTranslatable(kFalse);

		PMString inAccessibleFilesString;
		inAccessibleFilesString.AppendNumber((int32)inAccessibleFilesCount);
		inAccessibleFilesString.SetTranslatable(kFalse);

		PMString unKnownFilesString;
		unKnownFilesString.AppendNumber((int32)unKnownFilesCount);
		unKnownFilesString.SetTranslatable(kFalse);

		StringUtils::ReplaceStringParameters(&message, importFailFilesString, totalAssetCountStr, unSupportedFilesString, inAccessibleFilesString, unKnownFilesString);
		CAlert::InformationAlert(message);
	}
	return;
}
