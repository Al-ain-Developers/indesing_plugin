//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpShowPalette.cpp $
//  
//  Owner: Adobe InDesign Developer Technologes
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
#include "IActionComponent.h"
#include "IActionManager.h"
#include "IApplication.h"
#include "IPanelMgr.h"
#include "PaletteRefUtils.h"
#include "PaletteRef.h"
#include "IControlView.h"

// General includes:
#include "AppUIID.h" // for kPanelMgrMenuBoss
#include "LocaleSetting.h"
#include "UIDList.h"
#ifdef DEBUG
#include "DebugClassUtils.h"
#endif
#include <map>
#include "XMediaUIID.h" // kTagPanel...
#include "StylePanelID.h"	// kPara...
#include "PagesPanelID.h"	// kPages...
#include "AlignPanelID.h"

// SnippetRunner includes:
#include "SnipRunLog.h"
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"


/** Shows how to:
\li Discover default properties of palette-panel widgets via action component (IActionComponent)
\li Show or hide a widget by ActionID, PaletteRef or WidgetID

	@ingroup sdk_snippet
	@ingroup sdk_ui
 */
class SnpShowPalette 
{
public:
	

	/** Constructor.
	 */
	SnpShowPalette() {}

	/** Destructor.
	 */
	virtual ~SnpShowPalette() {}

	/**	Show or hide panel widget by its UID.
		@param palRef the palette-panel to show or hide
		@param isShow specifies whether to show (if kTrue) or hide (if kFalse)
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode ShowHide(const PaletteRef& palRef, bool16 isShow);

	/**	Show or hide palette-panel widget by associated ActionID.
		@param actionID identifies the action to show the palette
		@param isShow specifies whether to show (if kTrue) or hide (if kFalse)
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	 */
	ErrorCode ShowHideByAction(const ActionID& actionID, bool16 isShow);

	/**	Acquire collection of palette-panel widgets, as mapping from names to UIDs.
		@param outNameUIDMap map that contains name to UID map for known palette-panels
		@return ErrorCode kSuccess on success, other ErrorCode otherwise 
	 */
	ErrorCode GetPanelsRegistered(std::map<PMString,PaletteRef>& outNameUIDMap);

	/**	Determine if specified palette is showing
		@param palRef specifies the palette-panel of interest
		@return kTrue if showing, kFalse if not
	 */
	bool16 IsShowing(const PaletteRef& palRef);

	/** Determine if specified panel is showing
		@param actionID specifies panel of interest
		@return kTrue if showing, kFalse if not
	 */
	bool16 IsShowingByAction(const ActionID& actionID);
	
	/** Determine if specified panel is showing
		@param widgetID specifies panel of interest
		@return kTrue if showing, kFalse if not
	 */
	bool16 IsShowingByWidget(const WidgetID& widgetID);

	/** Show or hide by WidgetID
		@param widgetID specifies which widget
		@param isShowing kTrue to show the panel, kFalse to hide it
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
	*/
	ErrorCode ShowHideByWidget(const WidgetID& widgetID, bool16 isShowing);

	/**	Implements scenario that exercises the code in this snippet.
		@param activeContext 
		@return ErrorCode kSuccess  on success, other ErrorCode otherwise
	 */
	ErrorCode RunScenario(IActiveContext* activeContext);

};

/*
*/
ErrorCode SnpShowPalette::GetPanelsRegistered(std::map<PMString,PaletteRef>& outNamePalRefMap)
{
	ErrorCode retval = kFailure;
	do {
		// Preconditions
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		ASSERT(app);
		if(!app) {
			break;
		}
		InterfacePtr<IActionManager> actionManager(app->QueryActionManager());
		InterfacePtr<IPanelMgr> panelMgr(app->QueryPanelManager());
		ASSERT(panelMgr);
		if(panelMgr == nil) {
			break;
		}
		// end preconditions
		uint32 numPanels = panelMgr->GetPanelCount();
		
		for (int32 i = 0 ; i < numPanels ; i++)
		{
			ActionID actionID;
			UID	panelUID;
			WidgetID	widgetID;
			PMString	panelName;
			ScriptID	scriptID;
			bool16 gotPanelInfo = kFalse;
			gotPanelInfo = panelMgr->GetNthPanelInfo(i, panelUID, &actionID, &widgetID, &panelName, &scriptID);
			InterfacePtr<IControlView> panelView(::GetDataBase(panelMgr), panelUID, UseDefaultIID());
			PaletteRef panelsContainer = panelMgr->GetPaletteRefContainingPanel( panelView );
			if (gotPanelInfo && panelsContainer.IsValid())
			{
				outNamePalRefMap.insert(std::pair<PMString,PaletteRef>(panelName, panelsContainer));
#ifdef DEBUG
				DebugClassUtilsBuffer actBuf;
				const char* actionName = DebugClassUtils::GetIDName(&actBuf, actionID, kActionIDSpace);
				if (actionName != nil) {
					SNIPLOG("Action %s => Panel %s", actionName, panelName.GetPlatformString().c_str());
				}
#endif
			}
#if 0			
			InterfacePtr<IActionComponent> actionComponent(actionManager->QueryActionComponent(actionID));
			if (actionComponent == nil) {
				continue;
			}
			ClassID classID = ::GetClass(actionComponent);
			// Trick: look for any panel that is registered by kPanelMgrMenuBoss, 
			// such as submenus under the "Window" menu.
			// This is a reasonable strategy when panels haven't been moved.
			if (classID == kPanelMgrMenuBoss) {
				PMString panelName = actionManager->GetActionName(actionID);
				UID uid = panelMgr->GetPaletteUID(actionID);
				ASSERT(uid != kInvalidUID);
				// UIDs are in same database as the session object
				if(uid != kInvalidUID) {
					outNamePalRefMap.insert(std::pair<PMString,UID>(panelName, uid));
				}
#ifdef DEBUG
				DebugClassUtilsBuffer actBuf;
				const char* actionName = DebugClassUtils::GetIDName(&actBuf, actionID, kActionIDSpace);
				if (actionName != nil) {
					SNIPLOG("Action %s => Panel %s", actionName, panelName.GetPlatformString().c_str());
				}
#endif

			}
#endif
		}

		retval = kSuccess;
	} while(kFalse);

	// Check postconditions
	ASSERT(retval==kSuccess);
	// Done postconditions
	return retval;
}




/* 
*/
ErrorCode SnpShowPalette::ShowHide(const PaletteRef& palRef, bool16 isShow)
{
	ErrorCode status = kFailure;
	do
	{
		ASSERT(palRef.IsValid());
		if (isShow)
			PaletteRefUtils::ShowHidePalette(palRef, PaletteRefUtils::kShowPalette);
		else
			PaletteRefUtils::ShowHidePalette(palRef, PaletteRefUtils::kHidePalette);
		status = kSuccess;
	
	} while (false);
	
	// Assert postconditions
	ASSERT(status == kSuccess);
	// Done postconditions	
	return status;

}

ErrorCode SnpShowPalette::ShowHideByAction(const ActionID& actionID, 
										  bool16 isShowing)
{
	ErrorCode result = kFailure;
	do {
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		ASSERT(app);
		if(!app) {
			break;
		}
		InterfacePtr<IPanelMgr> panelMgr(app->QueryPanelManager());
		ASSERT(panelMgr);
		if(panelMgr == nil) {
			break;
		}
		
		if(isShowing) {
			panelMgr->ShowPanelByMenuID(actionID);
		} else {
			panelMgr->HidePanelByMenuID(actionID);
		}
		result = kSuccess;
	} while(kFalse);
	return result;
}


ErrorCode SnpShowPalette::ShowHideByWidget(const WidgetID& widgetID,
										  bool16 isShowing)
{
	ErrorCode result = kFailure;
	do {
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		ASSERT(app);
		if(!app) {
			break;
		}
		InterfacePtr<IPanelMgr> panelMgr(app->QueryPanelManager());
		ASSERT(panelMgr);
		if((panelMgr == nil)) {
			break;
		}
		if(isShowing) {
			panelMgr->ShowPanelByWidgetID(widgetID, kFalse);
		} else {
			panelMgr->HidePanelByWidgetID(widgetID);
		}
		result = kSuccess;
	} while(kFalse);
	return result;
}


/*
*/
bool16 SnpShowPalette::IsShowing(const PaletteRef& palRef)
{
	bool16 retval = kFalse;
	do
	{
		ASSERT(palRef.IsValid());
		retval = PaletteRefUtils::IsPaletteVisible(palRef);
	
	} while (false);
	
	return retval;
}

/*
*/
bool16 SnpShowPalette::IsShowingByWidget(const WidgetID& widgetID)
{
	bool16 retval = kFalse;
	do
	{
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		ASSERT(app);
		if(!app) {
			break;
		}
		InterfacePtr<IPanelMgr> panelMgr(app->QueryPanelManager());
		ASSERT(panelMgr);
		if((panelMgr == nil)) {
			break;
		}
		
		retval = panelMgr->IsPanelWithWidgetIDShown(widgetID);
	
	} while (false);
	
	return retval;
}

/*
*/
bool16 SnpShowPalette::IsShowingByAction(const ActionID& actionID)
{
	bool16 retval = kFalse;
	do
	{
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		ASSERT(app);
		if(!app) {
			break;
		}
		InterfacePtr<IPanelMgr> panelMgr(app->QueryPanelManager());
		if(panelMgr == nil) {
			break;
		}
		
		retval = panelMgr->IsPanelWithMenuIDShown(actionID);
	
	} while (false);
	
	return retval;
}

/*
*/
ErrorCode SnpShowPalette::RunScenario(IActiveContext* activeContext) 
{
	ErrorCode status = kFailure;
	do {
		SnipRunLog::Instance()->Clear();
		std::map<PMString,PaletteRef> nmMap;
		// 1 Get palette-panels into name-UID map
		SNIPLOG("*** Acquiring list of panel widgets ***");
		status = this->GetPanelsRegistered(nmMap);
		ASSERT(status == kSuccess);
		if(status != kSuccess) {
			break;
		}
		IDataBase* db = ::GetDataBase(GetExecutionContextSession());
		ASSERT(db);
		if(!db) {
			break;
		}
		

		std::map<PMString,PaletteRef>::const_iterator iter;
		SNIPLOG("*** Inspecting panels and changing state ***");
		for(iter = nmMap.begin(); iter != nmMap.end(); iter++) {
			// 2 Inspect contents of the map
			PMString panelName = iter->first;
			PaletteRef nextPalRef = iter->second;

			PMString transPanelName = panelName;
			bool16 isShowing = this->IsShowing(nextPalRef);

			SNIPLOG("Title %s (untrans=%s) Showing=%d",
				transPanelName.GetPlatformString().c_str(), panelName.GetPlatformString().c_str(), isShowing);
		}

		// 3 Selectively hide/show one panel by action ID that would by default be visible.
		SNIPLOG("*** Toggling Pages panel by ActionID ***");
		bool16 newPagesState = (!(this->IsShowingByAction(kPagesPanelActionID)));
		status = this->ShowHideByAction(kPagesPanelActionID,newPagesState);
		ASSERT(status == kSuccess);

		// 4 Selectively show/hide one panel by name (the untranslated one that is)
		// The string we deduced from an earlier run of this snippet
		SNIPLOG("*** Toggling Tags Panel by name/UID ***");
		PMString findStr("Tag_PanelMenu");
		std::map<PMString,PaletteRef>::const_iterator findIter = nmMap.find(findStr);
		if(findIter != nmMap.end()) {
			PaletteRef palRef = findIter->second;
			ASSERT(palRef.IsValid());
			if(!palRef.IsValid()) {
				break;
			}
			bool16 newFoundState = (!(this->IsShowing(palRef)));
			status = this->ShowHide(palRef, newFoundState);
			
			ASSERT(status == kSuccess);
		}

		// 5 Selectively show/hide one panel by ActionID that otherwise wouldn't be visible
		SNIPLOG("*** Toggling Align Panel by ActionID ***");
		bool16 newAlignState = (!(this->IsShowingByAction(kAlignPanelActionID)));
		status = this->ShowHideByAction(kAlignPanelActionID, newAlignState);
		ASSERT(status == kSuccess);

		// 6 Selectively show/hide one panel by WidgetID, by default a stashed widget
		SNIPLOG("*** Toggling Paragraph Styles Panel by WidgetID ***");
		bool16 newParaState = (!(this->IsShowingByWidget(kParaStylePanelWidgetID)));
		status = this->ShowHideByWidget(kParaStylePanelWidgetID, newParaState);

		
		SNIPLOG("*** SCENARIO EXECUTED SUCCESSFULLY ***");
	} while(kFalse);
	return status;
}
// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

class _SnpRunnerShowPalette : public SnpRunnable
{


public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerShowPalette(void);

	/** Destructor.
	 */
	virtual ~_SnpRunnerShowPalette();

	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16 CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode Run(ISnpRunnableContext* runnableContext);

	
	/**  Specifies snippet should only be available
		to be chosen to run under a specific product(InDesign).
	*/
	virtual bool16 CanLoad() const;
	
	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunNoContext;}

};


/* Constructor.
*/
_SnpRunnerShowPalette::_SnpRunnerShowPalette() : SnpRunnable("ShowPalette")
{
	this->SetDescription("Shows/ hides and inspects palettes");
	this->SetPreconditions("None");
	this->SetCategories("sdk_snippet, sdk_ui");
}

/* Destructor.
*/
_SnpRunnerShowPalette::~_SnpRunnerShowPalette()
{
	// do nothing.
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerShowPalette::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do 
	{
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerShowPalette::Run(ISnpRunnableContext* runnableContext)
{
	SnpShowPalette instance;
	return instance.RunScenario(runnableContext->GetActiveContext());
}


bool16 _SnpRunnerShowPalette::CanLoad() const
{
	bool16 isInDesignProductFS = LocaleSetting::GetLocale().IsProductFS(kInDesignProductFS);
	// Don't load under InCopy
	return isInDesignProductFS;
}


/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerShowPalette instance_SnpRunnerShowPalette;
DEFINE_SNIPPET(_SnpRunnerShowPalette) 	

// End, SnpShowPalette.cpp

