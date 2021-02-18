//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateInCopyCJKGridAttributes.cpp $
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
#include "ICommand.h"
#include "IDataBase.h"
#include "IDocPresetListMgr.h"
#include "IDocument.h"
#include "IGridAttributesPrefs.h"
#include "IGridAttributesPrefsData.h"
#include "IMeasurementSystem.h"
#include "ISession.h" // the session
#include "IUIDData.h"
#include "IUnitOfMeasure.h"
#include "IWorkspace.h"

// General includes:
#include "CJKLayoutID.h" // kHaBoss
#include "CmdUtils.h"
#ifdef DEBUG
#include "DebugClassUtils.h"
#endif
#include "InCopyCoreID.h" // kSetGridAttributesPrefsCmdBoss
#include "K2Pair.h"
#include "K2Vector.h"
#include "K2Vector.tpp"
#include "PersistUtils.h"
#include "Utils.h"
#include "FeatureSets.h"
#include "LocaleSetting.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
 * 	\li	Inspects and modifies the InCopy CJK grid settings in the text area 
 * 		of an InCopy story document.
 * 
 * 	CJK grid settings in an InCopy story document are encapsulated in the 
 * 	IGridAttributesPrefs interface. This interface is aggregated 
 * 	on one of the 4 following bosses:
 * 	<UL>
 *  <LI>kDocWorkspaceBoss</LI>
 * 	<LI>kDocPresetDefaultBoss (accessible via IDocPresetListMgr on kWorkspaceBoss, index 0)</LI>
 * 	<LI>kDocPresetBoss (accessible via IDocPresetListMgr on kWorkspaceBoss, index other than 0)</LI>
 * 	<LI>kWorkspaceBoss</LI>
 * 	</UL>
 * 
 * 	Note that this code snippet only loads in the Japanese feature set of InCopy 
 *  (kInCopyProductFS | kJapaneseLanguageFS), or kInCopyJapaneseFS.
 * 
 * 	@ingroup sdk_snippet, sdk_incopy, sdk_cjk
 */
class SnpManipulateInCopyCJKGridAttributes
{
	public:
		/** A structure to hold CJK Grid Attributes. */
		struct GridAttributes
		{
			/** Text area grid characters per line */
			int32 fCharPerLine;
			/** Text area grid vertical scale (1.0 = 100%) */
			PMReal fGridVScale;
			/** Text area grid horizontal scale (1.0 = 100%) */
			PMReal fGridHScale;
			/** Text area grid character spacing (points) */
			PMReal fGridCharAki;
			/** Text area grid Line Spacing (points) */
			PMReal fGridLineAki;
			/** Text area grid driection */
			IGridAttributesPrefs::TextDirection fDirection;
			/** Text area frame grid type */
			IGridAttributesPrefs::FrameType fFrameGridType; 
		};

		/** Type definition for keeping a UIDRef of the boss
		 * 	that agregates IGridAttributesPres and its description.
		 */
		typedef K2Pair<UIDRef, PMString> RefNamePair;

		/** A vector of RefNamePair.
		 * 	@see RefNamePair
		 */
		typedef K2Vector<RefNamePair> RefNamePairs;

		/** Inspects settings in IGridAttributesPrefs.
		 * 	@param gridAttributesPrefs IN A specific instance of a IGridAttributesPrefs interface.
		 * 	@param prefsData OUT The inspected preference settings. 
		 * 	@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode InspectGridAttributes(const IGridAttributesPrefs* gridAttributesPrefs, GridAttributes& prefsData);

		/** Modifies settings in a specific instance of IGridAttributesPrefs.
		 * 	@param gridAttributesPrefs IN A specific instance of a IGridAttributesPrefs interface.
		 * 	@param prefsData IN The preference settings to set.
		 * 	@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode ModifyGridAttributes(IGridAttributesPrefs* gridAttributesPrefs, const GridAttributes& prefsData);

		/** Arbitrarily sets the grid attributes data structure so 
		 * 	that it could be passed to ModifyGridAttributes. 
		 * 
		 * 	Modify the contents of this implementation as desired. 
		 */
		void SetAttributes(GridAttributes& prefsData);

		/** Reports the values in GridAttributes to SNIPLOG. 
		 * 	You can pass the GridAttributes gathered with InspectGridAttributes. 
		 * 	@param prefsData IN GridAttributes filled in.
		 */
		void ReportAttributes(const GridAttributes& prefsData);

		/** Gathers the UIDRefs of instances of bosses that aggregate IGridAttributesPrefs
		 * 	and associates each item with a description.  The descriptions can be
		 * 	passed on to ISnipRunParameterUtils::GetChoice to help the user pick
		 * 	a specific instance. 
		 * 
		 * 	@param doc IN IDocument from a specific document, if available.
		 * 		If doc is non-nil, then the IGridAttributesPrefs from kDocWorkspaceBoss
		 * 		will be included in the returned vector. 
		 * 	@return RefNamePairs containing the UIDRef for the boss instance that 
		 * 		aggregates IGridAttributesPrefs and a description of that instance. 
		 */
		RefNamePairs GetCJKGridAttributeRefNamePairs(IDocument* doc = nil);

private:
	/** Gets the class name as a string. 
	 * 	@param unknown IN Some interface pointer. 
	 * 	@return If unknown == nil, this will return the string "<unknown>". 
	 * 			Otherwise,
	 * 			 (Debug build) the class name as a qualified boss name if it exists, 
	 * 			  the classID as a hexadecimal string if it doesn't; 
	 * 			 (Release build) the classID as a hexadecimal string.
	 */
	PMString GetClassName(const IPMUnknown* unknown);
};

/* InspectGridAttributes
*/
ErrorCode SnpManipulateInCopyCJKGridAttributes::InspectGridAttributes(const IGridAttributesPrefs* gridAttributesPrefs, 
																	  GridAttributes& prefsData)
{
	ErrorCode result = kFailure;
	do 
	{
		if (gridAttributesPrefs == nil)
		{
			SNIPLOG("We cannot inspect a nil IGridAttributesPrefs - aborting...");
			break;
		}
		PMString className = this->GetClassName(gridAttributesPrefs);
		SNIPLOG("Inspecting IGridAttributesPrefs on %s", className.GetPlatformString().c_str());

		prefsData.fCharPerLine = gridAttributesPrefs->GetCharPerLine();
		prefsData.fGridHScale = gridAttributesPrefs->GetGridHScale();
		prefsData.fGridVScale = gridAttributesPrefs->GetGridVScale();
		prefsData.fGridCharAki = gridAttributesPrefs->GetGridCharAki();
		prefsData.fGridLineAki = gridAttributesPrefs->GetGridLineAki();
		prefsData.fDirection = gridAttributesPrefs->GetDirection();
		prefsData.fFrameGridType = gridAttributesPrefs->GetFrameGridType();
		result = kSuccess;
	} while(false);
	return result;
}

/* ModifyGridAttributes
*/
ErrorCode SnpManipulateInCopyCJKGridAttributes::ModifyGridAttributes(IGridAttributesPrefs* gridAttributesPrefs, 
																	 const GridAttributes& prefsData)
{
	ErrorCode result = kFailure;
	do 
	{
		if (gridAttributesPrefs == nil)
		{
			SNIPLOG("We cannot modify a nil IGridAttributesPrefs - aborting...");
			break;
		}
		PMString className = this->GetClassName(gridAttributesPrefs);
        SNIPLOG("Modifying IGridAttributesPrefs on %s", className.GetPlatformString().c_str());

		// create a command to set the grid attributes prefs and set the data
        InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetGridAttributesPrefsCmdBoss));
		InterfacePtr<IGridAttributesPrefsData> data(cmd, UseDefaultIID());

		// we have to figure out how to specify the instance we want to modify
		UIDRef ref = GetUIDRef(gridAttributesPrefs);
		InterfacePtr<IDocument> doc(ref.GetDataBase(), ref.GetDataBase()->GetRootUID(), UseDefaultIID());
		InterfacePtr<IWorkspace> workspace(ref, UseDefaultIID());

		if (doc != nil)
		{
			// prefs on document workspace
			data->SetDocument(GetUIDRef(doc));
		}
		else if (workspace == nil)
		{
			// on a document preset style
			InterfacePtr<IUIDData> styleUIDRef(cmd, UseDefaultIID());
			styleUIDRef->Set(ref);
		}
		// else session workspace prefs 
		// leave the style UIDRef and document as nil

		// set the grid attributes data
		data->SetCharPerLine(prefsData.fCharPerLine);
		data->SetGridHScale(prefsData.fGridHScale);
		data->SetGridVScale(prefsData.fGridVScale);
		data->SetGridCharAki(prefsData.fGridCharAki);
		data->SetGridLineAki(prefsData.fGridLineAki);
		data->SetDirection(prefsData.fDirection);
		data->SetFrameGridType(prefsData.fFrameGridType);

		result = CmdUtils::ProcessCommand(cmd);
	} while(false);
	return result;
}

/* SetAttributes
 */
void SnpManipulateInCopyCJKGridAttributes::SetAttributes(GridAttributes& prefsData)
{
	srand((unsigned)time(nil));

	// NOTE: This code snippet assigns random values in an arbitrary range. 
	// Change this routine as desired.

	prefsData.fCharPerLine = rand() % 19 + 1; // min 1, max 20 (NOTE: 0 chars per line will cause InCopy to crash)
	prefsData.fGridHScale = ((rand() % 100) /100.0) * 0.50 + 0.25; // min 0.25, max 0.75
	prefsData.fGridVScale = ((rand() % 100) /100.0) * 0.75 + 0.50; // min 0.50, max 1.25

	// set defaults
	prefsData.fGridCharAki = 0;
	prefsData.fGridLineAki = 0;
	// convert points to "Ha" unit
	InterfacePtr<IMeasurementSystem> ms(GetExecutionContextSession(), UseDefaultIID());
	ASSERT(ms);
	int32 index = ms->Location(kHaBoss);
	InterfacePtr<IUnitOfMeasure> haUnit(ms->QueryUnitOfMeasure(index));
	if (haUnit)
	{
		SNIPLOG("(Setting char and line aki in units of Ha)");
		// assign arbitrary values in "Ha"
		prefsData.fGridCharAki = haUnit->UnitsToPoints(((rand() % 300 + 100) /100.0)); // min 1 Ha (0.25 mm), max 4 Ha (1 mm)
		prefsData.fGridLineAki = haUnit->UnitsToPoints(((rand() % 700 + 100) /100.0)); // min 1 Ha (0.25 mm), max 8 Ha (2 mm)
	}

	// 50/50 chance for choosing horizontal with plain text frame or vertical with CJK grid.
	if ((rand() % 100) > 50)
	{
		prefsData.fDirection = IGridAttributesPrefs::kHorizontal;
		prefsData.fFrameGridType = IGridAttributesPrefs::kFrameTypePlain;
	}
	else
	{
		prefsData.fDirection = IGridAttributesPrefs::kVertical;
		prefsData.fFrameGridType = IGridAttributesPrefs::kFrameTypeCJKGrid;
	}
}

/* ReportAttributes
 */
void SnpManipulateInCopyCJKGridAttributes::ReportAttributes(const GridAttributes& prefsData)
{
	SNIPLOG("Chars per line: %d", prefsData.fCharPerLine);
	SNIPLOG("Grid horizontal scale: %f (%.2f %%)", ::ToDouble(prefsData.fGridHScale), ::ToDouble(prefsData.fGridHScale * 100.0));
	SNIPLOG("Grid vertical scale: %f (%.2f %%)", ::ToDouble(prefsData.fGridVScale), ::ToDouble(prefsData.fGridVScale * 100.0));

	InterfacePtr<IMeasurementSystem> ms(GetExecutionContextSession(), UseDefaultIID());
	ASSERT(ms);
	int32 index = ms->Location(kHaBoss);
	InterfacePtr<IUnitOfMeasure> haUnit(ms->QueryUnitOfMeasure(index));
	if (haUnit)
	{
		SNIPLOG("Grid chararcter aki: %f Ha (%.2f pts)", ::ToDouble(haUnit->PointsToUnits(prefsData.fGridCharAki)), ::ToDouble(prefsData.fGridCharAki));
		SNIPLOG("Grid line aki: %f Ha (%.2f pts)", ::ToDouble(haUnit->PointsToUnits(prefsData.fGridLineAki)), ::ToDouble(prefsData.fGridLineAki));
	}
	else
	{
		SNIPLOG("Grid chararcter aki: %f pts", ::ToDouble(prefsData.fGridCharAki));
		SNIPLOG("Grid line aki: %f pts", ::ToDouble(prefsData.fGridLineAki));
	}
	SNIPLOG("Grid direction: %s", (prefsData.fDirection == IGridAttributesPrefs::kHorizontal) ? "kHorizontal" : "kVertical");
	SNIPLOG("Frame grid type: %s", (prefsData.fFrameGridType == IGridAttributesPrefs::kFrameTypeCJKGrid) ? "kFrameTypeCJKGrid" : "kFrameTypePlain");
}

/* GetCJKGridAttributeRefNamePairs
 */
SnpManipulateInCopyCJKGridAttributes::RefNamePairs 
	SnpManipulateInCopyCJKGridAttributes::GetCJKGridAttributeRefNamePairs(IDocument* doc)
{
	RefNamePairs pairs;
	pairs.clear();
	RefNamePair pair;

	// get the UIDRef from the session workspace
	InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
	ASSERT(workspace);
	InterfacePtr<IGridAttributesPrefs> wsPrefs(workspace, UseDefaultIID());
	ASSERT_MSG(wsPrefs, "Ooops - it doesn't seem like kWorkspaceBoss has IGridAttributesPrefs");
    pairs.push_back(RefNamePair(GetUIDRef(workspace), "session workspace"));

	// get the UIDRef from the document workspace (if doc was passed in)
    if (doc)
	{
		UIDRef docWorkspaceRef = doc->GetDocWorkSpace();
		InterfacePtr<IGridAttributesPrefs> docWSPrefs(docWorkspaceRef, UseDefaultIID());
		ASSERT_MSG(docWSPrefs, "Ooops - it doesn't seem like kDocWorkspaceBoss has IGridAttributesPrefs");
		pairs.push_back(RefNamePair(docWorkspaceRef, "document workspace"));
	}

	// get the UIDRefs from the doc presets
    InterfacePtr<IDocPresetListMgr> docPresetListMgr(workspace, UseDefaultIID());
	ASSERT(docPresetListMgr);
	int32 n = docPresetListMgr->GetNumStyles();
	for (int32 i = 0 ; i < n ; i ++)
	{
		UIDRef ref = docPresetListMgr->GetNthStyleRef(i);
		InterfacePtr<IGridAttributesPrefs> presetPrefs(ref, UseDefaultIID());
		ASSERT_MSG(presetPrefs, "Ooops - it doesn't seem like this doc preset boss has IGridAttributesPrefs");

		PMString name;
		ErrorCode status = docPresetListMgr->GetNthStyleName(i, &name);
		if (status == kSuccess)
		{
			pairs.push_back(RefNamePair(ref, name));
		}
		else
		{
			ASSERT_FAIL(FORMAT_ARGS("Failed to get doc preset style %d", i));
		}
	}
	return pairs;
}

/* GetClass
*/
PMString SnpManipulateInCopyCJKGridAttributes::GetClassName(const IPMUnknown* unknown)
{
	PMString retval("", PMString::kEncodingASCII);
	char className[512]={0};
	if (unknown != nil)
	{
		ClassID classID = ::GetClass(unknown);
#ifdef DEBUG
		DebugClassUtils::GetIDName(&className, classID);
#endif
		if (strlen(className) == 0)
		{
			sprintf(className, "ClassID <0x%X>", classID.Get());
		}
	}
	else
	{
		strcpy(className, "<unknown>");
	}
	retval.SetCString(className, PMString::kUnknownEncoding );
	return retval;
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpManipulateInCopyCJKGridAttributes available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerManipulateInCopyCJKGridAttributes : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerManipulateInCopyCJKGridAttributes();

		/** Destructor.
		 */
		virtual			~_SnpRunnerManipulateInCopyCJKGridAttributes();

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

		/** Identifies whether this code snippet can be loaded
		 * 	in the current environment.
		 * 	@return if kTrue, this code snippet can be loaded in 
		 * 		the current environment.
		 */
		virtual bool16 CanLoad(void) const;
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunNoContext;}
};

/* Describe your snippet to the framework here.
*/
_SnpRunnerManipulateInCopyCJKGridAttributes::_SnpRunnerManipulateInCopyCJKGridAttributes() : SnpRunnable("ManipulateInCopyCJKGridAttributes")
{
	this->SetDescription("Inspects and modifies InCopy CJK grid attribute preferences for the text area.");
	this->SetPreconditions("none");
	this->SetCategories("sdk_snippet, sdk_incopy, sdk_cjk");
}

/* Destructor.
*/
_SnpRunnerManipulateInCopyCJKGridAttributes::~_SnpRunnerManipulateInCopyCJKGridAttributes()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerManipulateInCopyCJKGridAttributes::CanRun(ISnpRunnableContext* runnableContext)
{
	return kTrue;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerManipulateInCopyCJKGridAttributes::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do 
	{
		SnpManipulateInCopyCJKGridAttributes instance;

		// get front document
		IDocument* doc = runnableContext->GetActiveContext()->GetContextDocument();

		// get a list of the bosses that aggregate IGridAttributePrefs and their descriptions
		SnpManipulateInCopyCJKGridAttributes::RefNamePairs pairs = instance.GetCJKGridAttributeRefNamePairs(doc);

		// Use IParameterUtils to prompt for parameters to set up your call(if any).
		Utils<ISnipRunParameterUtils> parameterUtils;
		enum { kModify, kInspect }; 
		int32 defaultMode = kInspect;
		PMString prompt("Would you like to modify or inspect InCopy CJK Grid Attributes?", PMString::kEncodingASCII);
		K2Vector<PMString> choices;
		choices.push_back(PMString("Modify", PMString::kEncodingASCII));
		choices.push_back(PMString("Inspect", PMString::kEncodingASCII));
		int32 mode = parameterUtils->GetChoice(prompt, choices, defaultMode);
		if (parameterUtils->WasDialogCancelled())
		{
			break;
		}

		// select which InCopy CJK Grid Attributes to modify. 
		int32 defaultItem = 0;
		prompt = PMString("Which item would you like to modify/inspect?", PMString::kEncodingASCII);
		choices.clear();
		for (int32 i = 0 ; i < pairs.size() ; i++)
		{
			choices.push_back(pairs[i].second);
		}
		int32 item = parameterUtils->GetChoice(prompt, choices, defaultItem);
		if (parameterUtils->WasDialogCancelled())
		{
			break;
		}
		UIDRef ref = pairs[item].first;
		InterfacePtr<IGridAttributesPrefs> gridAttributesPrefs(ref, UseDefaultIID());

		// Perform your operation.
		SnpManipulateInCopyCJKGridAttributes::GridAttributes prefsData; 
		switch (mode)
		{
		case kModify:
			{
				instance.SetAttributes(prefsData);
				status = instance.ModifyGridAttributes(gridAttributesPrefs, prefsData);
				if (status == kSuccess)
				{
					instance.ReportAttributes(prefsData);
				}
			}
			break;
		case kInspect:
			{
				status = instance.InspectGridAttributes(gridAttributesPrefs, prefsData);
				if (status == kSuccess)
				{
					instance.ReportAttributes(prefsData);
				}
			}
			break;
		default:
			SNIPLOG("INVALID OPTION");
			break;
		}
	} while(false);
	return (status);
}

/* CanLoad
*/
bool16 _SnpRunnerManipulateInCopyCJKGridAttributes::CanLoad() const 
{
	// only load under InCopy Japanese (this snippet requires kHaBoss)
	bool16 isInCopyProductFS = LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS);
	bool16 isJapaneseFS = LocaleSetting::GetLocale().IsLanguageFS(kJapaneseLanguageFS);
	return (isInCopyProductFS && isJapaneseFS);
}


/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerManipulateInCopyCJKGridAttributes instance_SnpRunnerManipulateInCopyCJKGridAttributes;
DEFINE_SNIPPET(_SnpRunnerManipulateInCopyCJKGridAttributes) 	

// End, SnpManipulateInCopyCJKGridAttributes.cpp

