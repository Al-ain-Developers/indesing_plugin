//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateTrapStyles.cpp $
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
#include "IDocument.h"
#include "IGenStyleLockInfo.h"
#include "IPageList.h"
#include "ITrapStyle.h"
#include "ITrapStyleListMgr.h"
#include "ITrapStyleUtils.h"

// General includes:
#include "Utils.h"
#include "UIDList.h"
#include "K2Vector.h"
#include "K2Vector.tpp"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** \li	A code snippet that shows how to manipulate trap styles in a document.

	@ingroup sdk_snippet, sdk_print
	@author Ken Sadahiro
 */
class SnpManipulateTrapStyles
{
public:
	/**	A simple data structure to pass around ITrapStyle data.
	 * 	@see Get methods in ITrapStyle and IGenStyleLockInfo
	 */
	struct TrapStyleData
	{
		PMString fName; 	// name of the trap style
		int32 fImg2Obj;
		int32 fImg2Img;
		int32 fInternalImg;
		PMReal fDfltWidth; 	// default width
		PMReal fBlkWidth;	// black width
		PMReal fClrScaling;	// color scaling
		PMReal fStepTH;		// step threshold
		PMReal fBlkColorTH;	// black color threshold
		PMReal fBlkDnstyTH;	// black density threshold
		PMReal fSlidingTH;	// sliding threshold
		int32 fImgPlacement;
		int32 fImagemasks;
		int32 fTrapJoinStyle;
		int32 fTrapEndStyle;
		/** NOTE: These are flags for specifying which fields are to be modified. 
		 * 		You only need to set them when processing a command. */
		int32 fFlag;		

		bool16 fIsEditLocked;	// from IGenStyleLockInfo
		bool16 fIsDeleteLocked;	// from IGenStyleLockInfo
		bool16 fIsNameLocked;	// from IGenStyleLockInfo
	};

	/** Inspects a trap style, and displays some of the settings to SNIPLOG.
	 * 	@param trapStyle IN The trap style (kTrapStyleBoss) to examine.
	 * 	@param document IN The document to examine pages for assigned trap styles.  
	 * 			If nil, trapstyles on pages will not be reported. 
	 * 	@see kTrapStyleBoss
	 * 	@see ITrapStyle
	 *	@see IGenStyleLockInfo
	 * 	@see IPageList
	 * 	@see kPageBoss
	 * 	@see IPersistUIDData (IID_ITRAPSTYLEUIDDATA, defined in PrintID.h)
	 * 	@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode InspectTrapStyle(const UIDRef& trapStyle, IDocument* document = nil);

	/** Add a new trap style with the given name. 
	 * 	@param trapStyleListMgr IN The ITrapStyleListMgr to which you want to add the trap style.
	 * 	@param newTrapStyleName IN The name of the trap style to add. 
	 * 	@param newTrapStyle OUT The UIDRef of the new trap style.
	 * 	@param nameLocked IN If kTrue, the name of the new trap style cannot be modified. 
	 * 	@param editLocked IN If kTrue, the new trap style cannot be modified. 
	 * 	@param deleteLocked IN If kTrue, the new trap style cannot be deleted. 
	 * 	@return Status code.  kSuccess if success.  
	 * 	@see ITrapStyleListMgr::AddStyle
	*/
	ErrorCode AddTrapStyle(ITrapStyleListMgr* trapStyleListMgr, 
						   const PMString& newTrapStyleName, 
						   UIDRef& newTrapStyle,
						   const bool16 nameLocked = kFalse,
						   const bool16 editLocked = kFalse,
						   const bool16 deleteLocked = kFalse);

	/** Modify an existing trap style.
	 * 
	 *  NOTE: ITrapStyleListMgr doesn't inherit from IGenEdtStlListMgr like 
	 * 	IPrStStyleListMgr does, so the EditNthStyle method 
	 * 	behaves a bit differently between the two interfaces.  
	 * 	For instance, the parameters and the return type are all different between
	 * 	ITrapStyleListMgr::EditNthStyle and IPrStStyleListMgr::EditNthStyle.
	 * 	And while the IPrStStyleListMgr::EditNthStyle implementation does open a 
	 * 	dialog box, ITrapStyleListMgr::EditNthStyle does not. 
	 * 
	 * 	@param trapStyleListMgr IN The ITrapStyleListMgr that contains the trap style to modify.
	 * 	@param trapStyleIndex IN The index of the trap style to modify. 
	 * 	@param newTrapData IN The trap data to modify with.
	 * 	@param updateLockInfo IN If kTrue, the nameLocked, editLocked, and deleteLocked 
	 * 			parameters will be updated in the trap style. Otherwise, the nameLocked, 
	 * 			editLocked, and deleteLocked parameters will be ignored.
	 * 	@param nameLocked IN If kTrue, the name of the new trap style cannot be modified. 
	 * 	@param editLocked IN If kTrue, the new trap style cannot be modified. 
	 * 	@param deleteLocked IN If kTrue, the new trap style cannot be deleted. 
	 * 	@return Status code.  kSuccess if success.  
	 * 	@see ITrapStyleListMgr::EditNthStyle
	*/
	ErrorCode ModifyTrapStyle(ITrapStyleListMgr* trapStyleListMgr,
							  const int32 trapStyleIndex, 
							  ITrapStyle* newTrapData,
							  const bool16 updateLockInfo = kFalse,
							  const bool16 nameLocked = kFalse,
							  const bool16 editLocked = kFalse,
							  const bool16 deleteLocked = kFalse);

	/** Delete an existing trap style. 
	 * 	@param trapStyleListMgr IN The ITrapStyleListMgr from which you want to delete the trap style.
	 * 	@param trapStyleIndex IN The index of the trap style to delete. 
	 * 	@return Status code.  kSuccess if success.  
	 * 	@see ITrapStyleListMgr::DeleteNthStyle
	*/
	ErrorCode DeleteTrapStyle(ITrapStyleListMgr* trapStyleListMgr,
							  const int32 trapStyleIndex);

	/** Assigns the trap style to a list of pages.
	 * 	@param trapStyle IN The trap style to apply. 
	 * 	@param pageUIDList IN The list of pages to which the trap styles are applied.
	 * 	@return Status code.  kSuccess if success.  
	 * 	@see ITrapStyleUtils::AssignStyleToPageList
	 */
	ErrorCode AssignTrapStyleToPages(const UIDRef& trapStyle, const UIDList& pageUIDList);

	/** Utility method: Gets trap style names.
	 * 	@param trapStyleListMgr IN The trap style list manager to get trap style names from
	 * 	@return A vector of trap style names.
	 * 	@see ITrapStyleListMgr
	*/
	K2Vector<PMString> GetTrapStyleNames(ITrapStyleListMgr* trapStyleListMgr);

	/** Utility method: Gets trap style data and puts it into a TrapStyleData struct.
	 * 	@param trapStyle IN The trap style to read. 
	 * 	@return TrapStyleData struct.
	 * 	@see ITrapStyle
	*/
	TrapStyleData GetTrapStyleData(const UIDRef& trapStyle);

	/** Utility method: Creates a temporary, non-persistent trap style boss
	 * 	based on an existing trap style, and sets some data so it can be 
	 * 	used by ModifyTrapStyle.
	 * 	@param trapStyle IN The trap style to base the temporary trap style on.
	 * 	@return Non-persistent instance of kTrapStyleBoss. This interface is
	 * 		AddRef'ed, so make sure you release it when no longer needed. 
	 * 	@see kTrapStyleBoss
	 * 	@see ITrapStyle
	 */
	ITrapStyle* CreateNewTrapStyleBasedOn(const UIDRef& trapStyle);

	/** Utility method: Copies trap style data from a TrapStyleData struct
	 * 	and puts it into a non-persistent trap style boss.
	 * 	@param trapStyleData IN The trap style data to set.
	 * 	@param trapStyle IN/OUT The trap style to set.  This should be non-persistent, 
	 * 		as this method will call its Set methods. The data in the boss will also
	 * 		be modified by this routine.
	 * 	@see ITrapStyle
	*/
	void CopyTrapStyleData(const TrapStyleData& trapStyleData, ITrapStyle* trapStyle);

	/** Utility method: Gets a list of all pages in a document.
	 * 	@param document IN The document to get pages from.
	 * 	@return UIDList of all pages in the document.
	 */
	UIDList GetAllPagesInDocument(IDocument* document);
};

/* InspectTrapStyle
*/
ErrorCode SnpManipulateTrapStyles::InspectTrapStyle(const UIDRef& trapStyle, IDocument* document)
{
	ErrorCode result = kFailure;
	do
	{
		bool16 reportTrapStylesForPages = (document != nil);

		TrapStyleData trapStyleData = GetTrapStyleData(trapStyle);

		SNIPLOG("Inspecting trap style 0x%X", trapStyle.GetUID().Get());
		SNIPLOG("[ITrapStyle]");
		SNIPLOG(" Name: %s", trapStyleData.fName.GetPlatformString().c_str());
		SNIPLOG(" DefaultWidth: %f", ::ToDouble(trapStyleData.fDfltWidth));
		SNIPLOG(" BlackWidth: %f", ::ToDouble(trapStyleData.fBlkWidth));
		/* NOTE: More settings are available in TrapStyleData.  
		// Expanding this code is left as an exercise for the developer.
		//
		// Many of the settings in ITrapStyle are specified as an int32, however
		// there are enums defined right above each Get/Set method declarations.
		// Refer to ITrapStyle.h for more details.
		*/

		SNIPLOG("[IGenStyleLockInfo]");
		SNIPLOG(" isEditLocked: %s", (trapStyleData.fIsEditLocked ? "true":"false"));
		SNIPLOG(" isDeleteLocked: %s", (trapStyleData.fIsDeleteLocked ? "true":"false"));
		SNIPLOG(" isNameLocked: %s", (trapStyleData.fIsNameLocked ? "true":"false"));
		result = kSuccess;
        
		if (reportTrapStylesForPages)
		{	
			InterfacePtr<ITrapStyleListMgr> trapStyleListMgr(Utils<ITrapStyleUtils>()->QueryTrapStyleListMgr(document));
			if (trapStyleListMgr == nil)
			{
				ASSERT(trapStyleListMgr);
				break;
			}
			InterfacePtr<IPageList> pageList(document, UseDefaultIID()); 
			if (pageList == nil)
			{
				ASSERT_FAIL("pageList is nil");
				break; // out of do while
			}

			// get the list of pages that use this trap style
			K2Vector<PMString> trapStyleNames;
			trapStyleNames.clear();
			trapStyleNames.push_back(trapStyleData.fName);
			UIDList pageUIDList = Utils<ITrapStyleUtils>()->GetDocumentTrapStylePageList(document, trapStyleNames);
			if (pageUIDList.Length() == 0)
			{
				SNIPLOG(" This trap style is not used on any of the pages in this document.");
			}
			else
			{
				// get the page range string
				PMString pageString = "";
				pageList->GetPageRangeString(pageUIDList, &pageString);
				SNIPLOG(" This trap style is used on the following page range: %s", pageString.GetPlatformString().c_str());
			}
		}
	} while (false);
	return result;
}

/* AddTrapStyle
*/
ErrorCode SnpManipulateTrapStyles::AddTrapStyle(ITrapStyleListMgr* trapStyleListMgr, 
                                                const PMString& newTrapStyleName, 
												UIDRef& newTrapStyle,
												const bool16 nameLocked,
												const bool16 editLocked,
                                                const bool16 deleteLocked)
{
	ErrorCode status = kFailure;
	if (trapStyleListMgr != nil)
	{
		// get the current count
		int32 currentCount = trapStyleListMgr->GetNumStyles();
		// add style
		PMString nonConstNewTrapStyleName(newTrapStyleName);
		status = trapStyleListMgr->AddStyle(nonConstNewTrapStyleName, 
											nameLocked, 
											editLocked, 
											deleteLocked);
		ASSERT(status == kSuccess);
		// get the new count
		int32 newCount = trapStyleListMgr->GetNumStyles();
		ASSERT_MSG(((newCount - currentCount) == 1), "The new trap style count doesn't make sense!");
		// get the UID of the new trap style
		newTrapStyle = trapStyleListMgr->GetNthStyleRef(newCount - 1);
	}
	return status;
}

/* ModifyTrapStyle
*/
ErrorCode SnpManipulateTrapStyles::ModifyTrapStyle(ITrapStyleListMgr* trapStyleListMgr,
												   const int32 trapStyleIndex, 
												   ITrapStyle* newTrapData,
												   const bool16 updateLockInfo,
												   const bool16 nameLocked,
												   const bool16 editLocked,
												   const bool16 deleteLocked)
{
	ErrorCode status = kFailure;
	if (trapStyleListMgr != nil)
	{

		status = trapStyleListMgr->EditNthStyle(trapStyleIndex, 
												newTrapData, 
												updateLockInfo, 
												nameLocked, 
												editLocked, 
												deleteLocked);
	}
	return status;
}

/* DeleteTrapStyle
*/
ErrorCode SnpManipulateTrapStyles::DeleteTrapStyle(ITrapStyleListMgr* trapStyleListMgr,
												   const int32 trapStyleIndex)
{
	ErrorCode status = kFailure;
	if (trapStyleListMgr != nil)
	{

		status = trapStyleListMgr->DeleteNthStyle(trapStyleIndex);
	}
	return status;
}

/* AssignTrapStyleToPages
*/
ErrorCode SnpManipulateTrapStyles::AssignTrapStyleToPages(const UIDRef& trapStyle, const UIDList& pageUIDList)
{
	return Utils<ITrapStyleUtils>()->AssignStyleToPageList(pageUIDList, trapStyle);
}


/* GetTrapStyleNames
*/
K2Vector<PMString> SnpManipulateTrapStyles::GetTrapStyleNames(ITrapStyleListMgr* trapStyleListMgr)
{
	K2Vector<PMString> names;
	names.clear();
	do
	{
		if (trapStyleListMgr == nil)
		{
			ASSERT_FAIL("trapStyleListMgr is nil!");
			break;
		}
		int32 numTrapStyles = trapStyleListMgr->GetNumStyles();
		for (int32 i = 0; i < numTrapStyles ; i++)
		{
			PMString name;
			ErrorCode status = trapStyleListMgr->GetNthStyleName(i, &name);
			if (status == kSuccess)
			{
				names.push_back(name);
			}
			else
			{
				ASSERT_FAIL(FORMAT_ARGS("Trouble getting trap style name index %d", i));
			}
		}
	} while (false);
	return names;
}


/* GetTrapStyleData
*/
SnpManipulateTrapStyles::TrapStyleData SnpManipulateTrapStyles::GetTrapStyleData(const UIDRef& trapStyle)
{
	TrapStyleData trapStyleData;
	memset(&trapStyleData, 0, sizeof(trapStyleData));
	do
	{
		if (trapStyle.ExistsInDB() == kFalse)
		{
			ASSERT_FAIL("Invalid trapStyle");
			break;
		}
		InterfacePtr<ITrapStyle> iTrapStyle(trapStyle, UseDefaultIID());
		if (iTrapStyle == nil)
		{
			ASSERT(iTrapStyle);
			break;
		}
		InterfacePtr<IGenStyleLockInfo> styleLockInfo(trapStyle, UseDefaultIID());
		if (styleLockInfo == nil)
		{
			ASSERT(styleLockInfo);
			break;
		}

		// get ITrapStyle data
		trapStyleData.fName = iTrapStyle->GetName();
		trapStyleData.fImg2Obj = iTrapStyle->GetImg2Obj();
		trapStyleData.fImg2Img = iTrapStyle->GetImg2Img();
		trapStyleData.fInternalImg = iTrapStyle->GetInternalImg();
		trapStyleData.fDfltWidth = iTrapStyle->GetDfltWidth();
		trapStyleData.fBlkWidth = iTrapStyle->GetBlkWidth();
		trapStyleData.fClrScaling = iTrapStyle->GetClrScaling();
		trapStyleData.fStepTH = iTrapStyle->GetStepTH();
		trapStyleData.fBlkColorTH = iTrapStyle->GetBlkColorTH();
		trapStyleData.fBlkDnstyTH = iTrapStyle->GetBlkDnstyTH();
		trapStyleData.fSlidingTH = iTrapStyle->GetSlidingTH();
		trapStyleData.fImgPlacement = iTrapStyle->GetImgPlacement();
		trapStyleData.fImagemasks = iTrapStyle->GetImagemasks();
		trapStyleData.fTrapJoinStyle = iTrapStyle->GetTrapJoinStyle();
		trapStyleData.fTrapEndStyle = iTrapStyle->GetTrapEndStyle();
	
		// get IStyleLockInfo data
		trapStyleData.fIsEditLocked = styleLockInfo->IsEditLocked();
		trapStyleData.fIsDeleteLocked = styleLockInfo->IsDeleteLocked();
		trapStyleData.fIsNameLocked = styleLockInfo->IsNameLocked();

	} while (false);
	return trapStyleData;
}

/* CreateNewTrapStyleBasedOn
*/
ITrapStyle* SnpManipulateTrapStyles::CreateNewTrapStyleBasedOn(const UIDRef& trapStyle)
{
	ITrapStyle* newTempTrapStyle = nil;
	do
	{
		TrapStyleData trapStyleData = GetTrapStyleData(trapStyle);
		// modify a field
		// NOTE: For the sake of making a simple example, we will only 
		// modify the Name.
		trapStyleData.fName += "!";

		// create a new kTrapStyleBoss instance (non-persistent)
		// NOTE: This does an AddRef.
		newTempTrapStyle = CreateObject2<ITrapStyle>(kTrapStyleBoss);
		if (newTempTrapStyle == nil)
		{
			ASSERT_FAIL("newTempTrapStyle is nil");
			break;
		}

		// copy the data over
		CopyTrapStyleData(trapStyleData, newTempTrapStyle);

	} while (false);
	return newTempTrapStyle;
}

/* CopyTrapStyleData
*/
void SnpManipulateTrapStyles::CopyTrapStyleData(const TrapStyleData& trapStyleData, ITrapStyle* trapStyle)
{
	do
	{
		if (trapStyle == nil)
		{
			ASSERT_FAIL("trapStyle is nil");
			break;
		}
		// copy the data to the kTrapStyleBoss instance
		trapStyle->SetBlkColorTH(trapStyleData.fBlkColorTH);
		trapStyle->SetBlkDnstyTH(trapStyleData.fBlkDnstyTH);
		trapStyle->SetBlkWidth(trapStyleData.fBlkWidth);
		trapStyle->SetClrScaling(trapStyleData.fClrScaling);
		trapStyle->SetDfltWidth(trapStyleData.fDfltWidth);
		trapStyle->SetImagemasks(trapStyleData.fImagemasks);
		trapStyle->SetImg2Img(trapStyleData.fImg2Img);
		trapStyle->SetImg2Obj(trapStyleData.fImg2Obj);
		trapStyle->SetImgPlacement(trapStyleData.fImgPlacement);
		trapStyle->SetInternalImg(trapStyleData.fInternalImg);
		trapStyle->SetName(trapStyleData.fName);
		trapStyle->SetSlidingTH(trapStyleData.fSlidingTH);
		trapStyle->SetStepTH(trapStyleData.fStepTH);
		trapStyle->SetTrapEndStyle(trapStyleData.fTrapEndStyle);
		trapStyle->SetTrapJoinStyle(trapStyleData.fTrapJoinStyle);

	} while (false);
}

/* GetAllPagesInDocument
*/
UIDList SnpManipulateTrapStyles::GetAllPagesInDocument(IDocument* document)
{
	IDataBase* db = ::GetDataBase(document);
	if (db == nil)
	{
		return UIDList();
	}
    UIDList pageUIDList(db);
	do
	{
		InterfacePtr<IPageList> pageList(document, UseDefaultIID());
		int32 numPages = pageList->GetPageCount();
		for (int32 iPage = 0 ; iPage < numPages ; iPage++)
		{
			pageUIDList.Append(pageList->GetNthPageUID(iPage));
		}
	} while (false);
	return pageUIDList;
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpTemplate available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerManipulateTrapStyles : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerManipulateTrapStyles();

		/** Destructor.
		 */
		virtual			~_SnpRunnerManipulateTrapStyles();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}
};

/* Constructor.
*/
_SnpRunnerManipulateTrapStyles::_SnpRunnerManipulateTrapStyles() : SnpRunnable("ManipulateTrapStyles")
{
	this->SetDescription("Inspects, adds, modifies and deletes trap styles");
	this->SetPreconditions("Document open");
	this->SetCategories("sdk_snippet, sdk_print");
}

/* Destructor.
*/
_SnpRunnerManipulateTrapStyles::~_SnpRunnerManipulateTrapStyles()	
{
}

/* Check if your preconditions are met.
*/
bool16  _SnpRunnerManipulateTrapStyles::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;

	/* NOTE: You can certainly manipulate trap styles on the kWorkspaceBoss, 
		however, since this snippet has an option to assign trap styles to
		specific pages on a document, this snippet requires that you have a
		document available.
	*/

	if (runnableContext->GetActiveContext()->GetContextDocument() != nil)
		result = kTrue;
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerManipulateTrapStyles::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do
	{
		/* --- STEP 0A: Get document and database --- */
		// See note in CanRun above.
		IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();
		if (document == nil)
		{
			SNIPLOG("A document is required");
			break; // out of do-while
		}

		/* --- STEP 0B: Get trap style list from document --- */
		InterfacePtr<ITrapStyleListMgr> trapStyleListMgr(Utils<ITrapStyleUtils>()->QueryTrapStyleListMgr(document));
		if (trapStyleListMgr == nil)
		{
			ASSERT(trapStyleListMgr);
			break; // out of do-while
		}

		// Declare variables to use for SnpManipulateTrapStyles
		SnpManipulateTrapStyles instance;
		UIDRef trapStyle = UIDRef::gNull;
		int32 trapStyleIndex = -1;
		PMString newTrapStyleName = "";
		K2Vector<PMString> trapStyleNames;

		// Use IParameterUtils to prompt for parameters
		Utils<ISnipRunParameterUtils> parameterUtils;

		K2Vector<PMString> choices;
		int32 defaultChoice = 0;
		enum { kInspect, kAdd, kModify, kDelete, kAssignToAllPages };
		choices.clear();
		choices.push_back("Inspect trap style");
		choices.push_back("Add new trap style"); // no need to select one below
		choices.push_back("Modify trap style");
		choices.push_back("Delete trap style");
		choices.push_back("Assign trap style to all pages");
		PMString prompt("Select an operation", PMString::kEncodingASCII);

		/* --- STEP 1A: Decide which operation to perform --- */
		int32 opChoice = parameterUtils->GetChoice(prompt, choices, defaultChoice);
		if (parameterUtils->WasDialogCancelled() == kTrue)
		{
			status = kCancel;
			break; // out of do-while
		}
		SNIPLOG("Selected operation: %s", choices[opChoice].GetPlatformString().c_str());

		if (opChoice != kAdd)
		{
			/* --- STEP 1B: Choose a trap style --- */
			trapStyleNames.clear();
			trapStyleNames = instance.GetTrapStyleNames(trapStyleListMgr);
			defaultChoice = 0;
			prompt = PMString("Select a trap style", PMString::kEncodingASCII);
			trapStyleIndex = parameterUtils->GetChoice(prompt, trapStyleNames, defaultChoice);
			if (parameterUtils->WasDialogCancelled() == kTrue)
			{
				status = kCancel;
				break; // out of do-while
			}
			SNIPLOG("Selected trap style:\n%s", trapStyleNames[trapStyleIndex].GetPlatformString().c_str());
			// get the UIDRef of the chosen trap style.
			trapStyle = trapStyleListMgr->GetNthStyleRef(trapStyleIndex);
		}
		else
		{
			/* --- STEP 1B for kAdd: specify a new trap style name --- */
			prompt = PMString("Specify a name for the new trap style", PMString::kEncodingASCII);
			PMString defaultName("NewTrapStyle", PMString::kEncodingASCII);
			newTrapStyleName = parameterUtils->GetPMString(prompt, defaultName);
			if (parameterUtils->WasDialogCancelled() == kTrue)
			{
				status = kCancel;
				break; // out of do-while
			}
			SNIPLOG("Specified new trap style name:\n%s", newTrapStyleName.GetPlatformString().c_str());
		}

		/* STEP 2: Perform the chosen operation */
		switch (opChoice)
		{
		case kInspect:
			{
				// inspect a trap style
				status = instance.InspectTrapStyle(trapStyle, document);
			}
			break;
		case kAdd:
			{
				// add a new trap style
				UIDRef newTrapStyle;
				status = instance.AddTrapStyle(trapStyleListMgr, newTrapStyleName, newTrapStyle);
				if (status == kSuccess)
					SNIPLOG("New trap style added: UID 0x%X, \"%s\"", 
							newTrapStyle.GetUID().Get(), newTrapStyleName.GetPlatformString().c_str());
			}
			break;
		case kModify:
			{
				// create a temporary ITrapStyle with desired data.
				InterfacePtr<ITrapStyle> trapStyleData(instance.CreateNewTrapStyleBasedOn(trapStyle));
				// modify the trap style data
				status = instance.ModifyTrapStyle(trapStyleListMgr, trapStyleIndex, trapStyleData);
				if (status == kSuccess)
					SNIPLOG("Trap style modified: UID 0x%X, \"%s\"", 
							trapStyle.GetUID().Get(),
							trapStyleNames[trapStyleIndex].GetPlatformString().c_str());
			}
			break;
		case kDelete:
			{
				// delete a trap style
				status = instance.DeleteTrapStyle(trapStyleListMgr, trapStyleIndex);
				if (status == kSuccess)
					SNIPLOG("Trap style deleted: UID 0x%X, \"%s\"", 
							trapStyle.GetUID().Get(),
							trapStyleNames[trapStyleIndex].GetPlatformString().c_str());
			}
			break;
		case kAssignToAllPages:
			{
				// gather UIDs of all pages in document
				UIDList pageUIDList = instance.GetAllPagesInDocument(document);
				// go assign the trap style to all pages
				status = instance.AssignTrapStyleToPages(trapStyle, pageUIDList);
				if (status == kSuccess)
					SNIPLOG("Trap style UID 0x%X \"%s\" assigned to all pages in document", 
							trapStyle.GetUID().Get(),
							trapStyleNames[trapStyleIndex].GetPlatformString().c_str());
			}
			break;
		default:
			ASSERT_FAIL("Invalid operation choice");
			break;
		}

	} while (false);
	return status;
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerManipulateTrapStyles instance_SnpRunnerManipulateTrapStyles;
DEFINE_SNIPPET(_SnpRunnerManipulateTrapStyles) 	

// End, SnpManipulateTrapStyles.cpp

