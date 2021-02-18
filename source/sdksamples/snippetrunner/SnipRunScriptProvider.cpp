//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunScriptProvider.cpp $
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
#include "IActionManager.h"
#include "IApplication.h"
#include "IDataBase.h"
#include "IPanelControlData.h"
#include "IPanelDetailController.h"
#include "IPanelMgr.h"
#include "IPMStream.h"
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IScriptUtils.h"
#include "ISelectionUtils.h"
#include "ISession.h" // the session
#include "IStringData.h"
#include "ITextControlData.h"
#include "ITriStateControlData.h"
#include "IXMLGenerator.h"
#include "IWindow.h"

// Project includes
#include "SnipRunID.h"
#include "SnipRunLog.h"
#include "SnipRunScriptingDefs.h"
#include "ISnipRunSuite.h"

// General includes
#include "AppUIID.h" // for kPanelMgrMenuBoss, IID_ITABSTASHDATA
#include "CScriptProvider.h" 
#include "DebugClassUtils.h"
#include "PrefsScriptProvider.h" 
#include "LocaleSetting.h"
#include "IPalettePanelUtils.h"
#include "StreamUtil.h"
#include "XMLID.h" // for IID_IXMLGENERATOR

const WidgetID kMyPanelWidgetID = kSnipRunPanelWidgetID;
const ActionID kMyPanelActionID = kSnipRunPanelWidgetActionID;


/** Script provider for the SDK code snippet runner script object.

	@ingroup snippetrunner
	@author Ken Sadahiro
*/
class SnipRunScriptProvider : public PrefsScriptProvider
{
public:
	/** Constructor.
	 */
	SnipRunScriptProvider(IPMUnknown* boss);

	/** Destructor
	 */
	virtual ~SnipRunScriptProvider(void);

	/** Handles an event. This call further delegates to private methods.
	 * 	@see IScriptProvider::HandleMethod
	 */
	virtual ErrorCode HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script);

	/** Processes a property access. This call further delegates to private methods.
	 * 	@see IScriptProvider::AccessProperty
	 */
	virtual ErrorCode AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);

private: 
  /* Methods called by HandleMethod */
	
	/** HandleMethod calls this method to delegate the e_SnipRunSnippetRegistered event. 
	 * 	@see HandleMethod
	*/
	ErrorCode HandleEvent_IsSnippetRegistered(IScriptRequestData* data, IScript* script);

	/** HandleMethod calls this method to delegate the e_SnipRunGetSnipLog event. 
	 * 	@see HandleMethod
	*/
	ErrorCode HandleEvent_GetSnipLog(IScriptRequestData* data, IScript* script);

	/** HandleMethod calls this method to delegate the e_SnipRunClearSnipLog event. 
	 * 	@see HandleMethod
	*/
	ErrorCode HandleEvent_ClearSnipLog(IScriptRequestData* data, IScript* script);

	/** HandleMethod calls this method to delegate the e_SnipRunSaveSnipLog event. 
	 * 	@see HandleMethod
	*/
	ErrorCode HandleEvent_SaveSnipLog(IScriptRequestData* data, IScript* script);


  /* Methods called by AccessProperty */

	/** AccessProperty calls this method to delegate access to the p_SnipRunPanelVisibility property.
	 * 	@see AccessProperty
	*/
	ErrorCode AccessProperty_SnipRunPanelVisibility(IScriptRequestData* data, IScript* script);

	/** AccessProperty calls this method to delegate access to the p_SnipRunTraceMode property.
	 * 	@see AccessProperty
	*/
	ErrorCode AccessProperty_SnipRunTraceMode(IScriptRequestData* data, IScript* script);


	/** Is the SnippetRunner panel visible?
	 * 	@return kTrue if visible, kFalse if not.
	 */
	bool16 IsSnipRunPanelVisible(void);

	/** Get the current visibility of the Snippet Runner panel in terms of a ScriptID.
	 * 	@param propertyValue OUT An Enum value describing the visibility.
	 * 	@return kSuccess if success.
	 */
	ErrorCode GetSnipRunPanelVisibility(ScriptID& propertyValue);

	/** Set the current visibility of the Snippet Runner panel using a ScriptID.
	 * 	@param propertyValue IN An Enum value describing the visibility.
	 * 	@return kSuccess if success.
	 */
	ErrorCode SetSnipRunPanelVisibility(const ScriptID& propertyValue);

	/** Actually shows/hides the SnippetRunner panel.
	 * 	@param show IN Set to kTrue to show the panel, kFalse to hide it.
	 * 	@return kSuccess if success.
	 */
	ErrorCode DoShowHideSnipRunPalette(const bool16 show = kTrue);

	/** Change the tristate control on the SnippetRunner panel (e.g. the Trace checkbox).
	 * 	@param widgetID IN The WidgetID of the tristate control to change. 
	 * 	@param newTriStateValue IN The new tristate value for the control.
	 * 	@return kSuccess if success.
	 */
	ErrorCode DoChangeTriStateControl(const WidgetID& widgetID, const ITriStateControlData::TriState newTriStateValue);

	/** (From SnpShowPalette.cpp) Palette type */
	enum PaletteType
	{
		/** Tab aware palette (kTabAwarePaletteBoss). 
		 * 	This boss aggregates the following key interfaces:
		 * <UL>
		 * 	<li>IID_IKITDRAGTARGET (defined in WidgetID.h)</li>
		 * 	<li>IID_IPALETTECONTROLDATA</li>
		 * 	<li>IID_IPALETTEWINDOWDATA</li>
		 * 	<li>IID_IPANELCONTROLDATA</li>
		 * 	<li>IID_IXMLGENERATOR</li> 
		 * </UL> */
		kTabAwarePalette, 
		/** Tabless palette (kTablessPaletteBoss). 
		 * 	This boss aggregates the following key interfaces:
		 * <UL>
		 *  <li>IID_IPALETTECONTROLDATA	</li>
		 * 	<li>IID_IPALETTEWINDOWDATA	</li>
		 * 	<li>IID_IPANELCONTROLDATA</li>
		 * 	<li>IID_IXMLGENERATOR <-- (Defined in XMLID.h) </li> 
		 * </UL> */
		kTablessPalette, 

		/** Tab stash palette (kTabStash_PaletteWindowBoss)
		 *  This boss aggregates everything that kTabAwarePaletteBoss does, 
		 * 	and IID_ITABSTASHDATA (defined in AppUIID.h) 
		 */
		kTabStashPalette,
		/** Tab station palette (kTabStationPaletteBoss)
		 * 	This boss aggregates the following key interfaces:
		 * <UL>
		 * 	<li>IID_IKITDRAGTARGET</li>
		 * 	<li>IID_IPANELCONTROLDATA</li>
		 * 	<li>IID_IPALETTECONTROLDATA</li>
		 * 	<li>IID_ITABSTATIONDATA <-- (Defined in TabStationID.h)</li>
		 * 	<li>but not IPaletteWindowData</li>
		 * </UL> */
        kTabStationPalette, 

		/** Horizontal and vertical dock bar palette (kHDockBarPaletteBoss and kHDockBarPaletteBoss)
		 * 	These bosses aggregates the following key interfaces:
		 * <UL>
		 * 	<li>IID_IDYNAMICERASEBEFOREDRAWFLAG</li>
		 *  <li>IID_IPANELCONTROLDATA</li>
		 *  <li>IID_IPMPOINTDATA</li>
		 *  <li>IID_IKITDRAGTARGET</li>
		 *  <li>IID_IPALETTECONTROLDATA</li>
		 *  <li>IID_IDOCKBAR <-- (Defined in DockBarID.h)</li> 
		 * </UL> */
		kHVDockBarPalette,

		/** unknown palette type */
		kUnknownPalette
	};


	/** (From SnpShowPalette.cpp) Palette state */
	enum PaletteState
	{
		/** palette is zoomed out - open */
		kZoomedOut = IWindow::kZoomedOut, 	// 0
		/** palette is zoomed in - minimized */
		kZoomedIn = IWindow::kZoomedIn,		// 1
		/** palette is closed */
		kClosed,							// 2
		/** palette is in a tabstash, and is open */
		kTabStash_Opened,					// 3
		/** palette is in a tabstash, and is stashed away */
		kTabStash_Stashed,					// 4
		/** palette is in a tab station, and is open */
		kTabStation_Opened, 				// 5
		/** palette is in a tab station, and is stashed away */
		kTabStation_Stashed,				// 6
		/** palette is a dock bar, and is open */
		kDockBar_Opened,					// 7
		/** palette is in a state unknown to mankind...  */
		kUnknownState						// 8
	};
};

/*  Make the implementation available to the application.
*/
CREATE_PMINTERFACE(SnipRunScriptProvider, kSnipRunScriptProviderImpl)

/*
*/
SnipRunScriptProvider::SnipRunScriptProvider(IPMUnknown* boss) : 
	PrefsScriptProvider(boss)
{
	DefinePreference(c_SnipRun, p_SnipRun); 
}

/*
*/
SnipRunScriptProvider::~SnipRunScriptProvider(void) 
{
	// do nothing
}

/* HandleMethod
*/
ErrorCode SnipRunScriptProvider::HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{
		switch (methodID.Get())
		{
		case e_SnipRunIsSnippetRegistered:
			result = HandleEvent_IsSnippetRegistered(data, script);
			break;
		case e_SnipRunGetSnipLog:
			result = HandleEvent_GetSnipLog(data, script);
			break;
		case e_SnipRunClearSnipLog:
			result = HandleEvent_ClearSnipLog(data, script);
			break;
		case e_SnipRunSaveSnipLog:
			result = HandleEvent_SaveSnipLog(data, script);
			break;
		default:
			result = PrefsScriptProvider::HandleMethod(methodID, data, script);
			break;
		}
	} while (false);
	// if kFailure, we need to change the error code so that we own the error string.
	if (result == kFailure)
	{
		result = kSnipRunInternalError;
	}
	return result;
}

/* AccessProperty
*/
ErrorCode SnipRunScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{
		switch (propID.Get())
		{
		case p_SnipRunPanelVisibility:
			result = AccessProperty_SnipRunPanelVisibility(data, script);
			break;
		case p_SnipRunTraceMode:
			result = AccessProperty_SnipRunTraceMode(data, script);
			break;
		default:
			/* NOTE:
			// The following properties, which are inherited from 
			// kPreferencesObjectScriptElement, are handled in the 
			// super class PrefsScriptProvider (See CScriptProvider.cpp):
			// * p_Parent (kParentPropertyScriptElement)
			// * p_Properties (kPropertiesPropertyScriptElement)
			*/
			result = PrefsScriptProvider::AccessProperty(propID, data, script);
			break;
		}
	} while (false);
	// if kFailure, we need to change the error code so that we own the error string.
	if (result == kFailure)
	{
		result = kSnipRunInternalError;
	}
	return result;
}

/* HandleEvent_IsSnippetRegistered
*/
ErrorCode SnipRunScriptProvider::HandleEvent_IsSnippetRegistered(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	bool16 isSnippetRegistered = kFalse;
	ScriptData returnData;
	do
	{
		ScriptData scriptData;
		PMString snippetName;
		result = data->ExtractRequestData(p_SnipRunSnippetToCheck, scriptData);
		if (result != kSuccess)	break;

		// set result so that we can check after the switch statement
		result = kFailure;
		switch (scriptData.GetType())
		{
		case ScriptData::s_string:
			{
				result = scriptData.GetPMString(snippetName);
				break;
			}
		case ScriptData::s_object:
			{
				InterfacePtr<IScript> script(scriptData.QueryObject());
				if (script == nil)
				{
					ASSERT(script);
					break; // switch
				}
				InterfacePtr<IStringData> snippetNameData(script, IID_ISNIPPETNAME);
				if (snippetNameData == nil)
				{
					ASSERT(snippetNameData);
					break; // switch
				}
				snippetName = snippetNameData->Get();
				result = kSuccess;
				break;
			}
		default:
			ASSERT_FAIL("unknown parameter type for IsSnippetRegistered");
			break;
		}
		if (result != kSuccess)
		{
			break;
		}

		// check if the snippet is registered
		InterfacePtr<ISnipRunSuite> snipRunSuite((ISnipRunSuite*)Utils<ISelectionUtils>()->QuerySuite(ISnipRunSuite::kDefaultIID));
		if (snipRunSuite == nil)
		{
			ASSERT_FAIL("Cannot query ISnipRunSuite!");
			result = kFailure;
			break;
		}
		isSnippetRegistered = snipRunSuite->IsRegistered(snippetName);
	} while (false);

	returnData.SetBoolean(isSnippetRegistered);
	data->AppendReturnData( script, e_SnipRunIsSnippetRegistered, returnData ) ;
	return result;
}

/* HandleEvent_GetSnipLog
*/
ErrorCode SnipRunScriptProvider::HandleEvent_GetSnipLog(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	PMString snipLogString = "";
	ScriptData returnData;
	do
	{
		// POSSIBLE ENHANCEMENT: ALL of this code should really be in SnipRunLog::GetLogText

		if (this->IsSnipRunPanelVisible() == kFalse)
		{
			// it's still a success -  it's just that the panel is not visible right now.
			// just return an empty string
			result = kSuccess;
			break;
		}

		// get the text control via the panel
		InterfacePtr<IPanelControlData> panelControlData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kMyPanelWidgetID));
		// this should not fail since we know by now the panel is visible
		ASSERT(panelControlData);

		IControlView* controlView = panelControlData->FindWidget(kSnipRunLogWidgetID);
		if (controlView == nil)
		{
			ASSERT_FAIL("controlView invalid for logWidget");
			break;
		}
		InterfacePtr<ITextControlData> logTextControlData(controlView, UseDefaultIID());
		if (logTextControlData == nil)
		{
			ASSERT_FAIL("invalid logTextControlData");
			break;
		}

		// get the string that is currently on the sniplog
		snipLogString = logTextControlData->GetString();
		result = kSuccess;

	} while (false);

	returnData.SetPMString(snipLogString);
	data->AppendReturnData( script, e_SnipRunGetSnipLog, returnData ) ;
	return result;
}

/* HandleEvent_ClearSnipLog
*/
ErrorCode SnipRunScriptProvider::HandleEvent_ClearSnipLog(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kSuccess;
	ScriptData returnData;

	if (this->IsSnipRunPanelVisible() == kFalse)
	{
		result = kSnipRunInvalidOperationWhenPanelIsInvisibleErrorCode; 
	}
	else
	{
		// clear the snip log
		SnipRunLog::Instance()->Clear();
	}

	// set the return value
	returnData.SetInt32(result);
	data->AppendReturnData( script, e_SnipRunClearSnipLog, returnData ) ;
	// NOTE: this is hardcoded
	return kSuccess;
}

/* HandleEvent_SaveSnipLog
*/
ErrorCode SnipRunScriptProvider::HandleEvent_SaveSnipLog(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kSuccess;
	ScriptData returnData;
	do
	{
		if (this->IsSnipRunPanelVisible() == kFalse)
		{
			result = kSnipRunInvalidOperationWhenPanelIsInvisibleErrorCode;
			break;
		}

		ScriptData scriptData;

		// get filename
		IDFile idFile;
		result = data->ExtractRequestData(keyAEFile, scriptData);
		if (result != kSuccess)	break;
		scriptData.GetFile(&idFile, data->GetRequestContext());

		// create a file write stream
		InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWriteLazy(idFile));
		if (stream == nil || stream->GetStreamState() != kStreamStateGood)
		{
			//ASSERT_FAIL("invalid file name for SaveSnipLog");
			result = kSnipRunInvalidFilePathForSaveSnipLogErrorCode;
			break;
		}
		// save the log
		SnipRunLog::Instance()->SaveLog(stream);

		result = kSuccess;
	} while (false);

	// set the return value
	returnData.SetInt32(result);
	data->AppendReturnData( script, e_SnipRunSaveSnipLog, returnData ) ;
	// NOTE: this is hardcoded
	return kSuccess;
}

/* AccessProperty_SnipRunPanelVisibility
*/
ErrorCode SnipRunScriptProvider::AccessProperty_SnipRunPanelVisibility(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	ScriptData propertyData;
	ScriptID propertyValue;
	do
	{
		if (data->IsPropertyGet())
		{
			// query for the current state of the panel
			result = this->GetSnipRunPanelVisibility(propertyValue);
			ASSERT(result == kSuccess);
			propertyData.SetEnumeration(propertyValue);
			data->AppendReturnData( script, p_SnipRunPanelVisibility, propertyData);
		}
		else if (data->IsPropertyPut())
		{
			result = data->ExtractRequestData(p_SnipRunPanelVisibility, propertyData);
			ASSERT(result == kSuccess);
			propertyData.GetEnumeration(&propertyValue);
			// set the state of the panel
			result = this->SetSnipRunPanelVisibility(propertyValue);
		}

	} while (false);
	return result;
}

/* AccessProperty_SnipRunTraceMode
*/
ErrorCode SnipRunScriptProvider::AccessProperty_SnipRunTraceMode(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	ScriptData propertyData;
	ScriptID propertyValue;
	do
	{
		if (data->IsPropertyGet())
		{
			// get for the current state of trace
			bool16 traceMode = SnipRunLog::Instance()->GetTrace();
			propertyValue = (traceMode == kTrue ? en_SnipRunTraceOn : en_SnipRunTraceOff);
			propertyData.SetEnumeration(propertyValue);
			data->AppendReturnData( script, p_SnipRunTraceMode, propertyData);
			result = kSuccess;
		}
		else if (data->IsPropertyPut())
		{
			result = data->ExtractRequestData(p_SnipRunTraceMode, propertyData);
			ASSERT(result == kSuccess);
			propertyData.GetEnumeration(&propertyValue);

			// go reflect this change on the UI
			// this will set the state in SnipRunLog as well by means of SnipRunPanelWidgetObserver
			ITriStateControlData::TriState newState = 
				(propertyValue == en_SnipRunTraceOn ? 
				 ITriStateControlData::kSelected : 
				 ITriStateControlData::kUnselected);
			result = this->DoChangeTriStateControl(kSnipRunTraceLogWidgetID, newState);
			ASSERT(result == kSuccess);
		}

	} while (false);
	return result;
}

/* IsSnipRunPanelVisible
*/ 
bool16 SnipRunScriptProvider::IsSnipRunPanelVisible(void)
{
	bool16 isVisible = kFalse;
	/*
	InterfacePtr<IPanelControlData> panelControlData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kSnipRunPanelWidgetID));
	isVisible = (panelControlData != nil ? kTrue : kFalse);
	*/
	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	ASSERT(app);
	InterfacePtr<IPanelMgr> panelMgr(app->QueryPanelManager());
	ASSERT(panelMgr);
	isVisible = panelMgr->IsPanelWithMenuIDShown(kMyPanelActionID);

	return isVisible;
}

/* GetSnipRunPanelVisibility
*/ 
ErrorCode SnipRunScriptProvider::GetSnipRunPanelVisibility(ScriptID& propertyValue)
{
	ErrorCode result = kSuccess;
	propertyValue = (this->IsSnipRunPanelVisible() == kTrue ? en_SnipRunPanelVisible : en_SnipRunPanelInvisible);
	return result;
}

/* SetSnipRunPanelVisibility
*/
ErrorCode SnipRunScriptProvider::SetSnipRunPanelVisibility(const ScriptID& propertyValue)
{
	ErrorCode result = kFailure;
	do
	{
		bool16 currentVisibility = this->IsSnipRunPanelVisible();
		bool16 newVisibiity = (currentVisibility == kTrue ? kFalse : kTrue);

		if ((propertyValue == en_SnipRunPanelVisible && currentVisibility == kFalse) ||
			(propertyValue == en_SnipRunPanelInvisible && currentVisibility == kTrue))
		{
			result = this->DoShowHideSnipRunPalette(newVisibiity);
		}
		else
		{
			//... already visible - do nothing
			result = kSuccess;
		}
	} while (false);
	return result;
}

/* DoShowHideSnipRunPalette
*/
ErrorCode SnipRunScriptProvider::DoShowHideSnipRunPalette(const bool16 show)
{
	ErrorCode result = kFailure;
	do
	{
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		if (app == nil)
		{
			ASSERT_FAIL("IApplication is nil");
			break;
		}
		InterfacePtr<IPanelMgr> panelMgr(app->QueryPanelManager());
		if (panelMgr == nil)
		{
			ASSERT_FAIL("IPanelMgr is nil");
			break;
		}

		if (show == kTrue)
		{
			panelMgr->ShowPanelByMenuID(kMyPanelActionID);
			result = kSuccess;
		}
		else
		{
			panelMgr->HidePanelByMenuID(kMyPanelActionID);
			result = kSuccess;
		}

	} while (false);
	return result;
}

/* DoChangeTriStateControl
*/
ErrorCode SnipRunScriptProvider::DoChangeTriStateControl(const WidgetID& widgetID, const ITriStateControlData::TriState newTriStateValue)
{
	ErrorCode result = kFailure;
	do
	{
		// get the subject of the widget
		if (this->IsSnipRunPanelVisible() == kFalse)
		{
			ASSERT_FAIL("Can't change a widget while it's invisible");
			break;
		}

		// get the tristate control via the panel
		InterfacePtr<IPanelControlData> panelControlData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kMyPanelWidgetID));
		// this should not fail since we know by now the panel is visible
		ASSERT(panelControlData);

		IControlView* controlView = panelControlData->FindWidget(widgetID);
		if (controlView == nil)
		{
			ASSERT_FAIL("controlView invalid for widgetID");
			break;
		}
		InterfacePtr<ITriStateControlData> triStateControlData(controlView, UseDefaultIID());
		if (triStateControlData == nil)
		{
			ASSERT_FAIL("triStateControlData invalid");
			break;
		}
		const bool16 invalidate = kTrue;
		const bool16 notify = kTrue;
		triStateControlData->SetState(newTriStateValue, invalidate, notify);
		result = kSuccess;

	} while (false);
	return result;
}

// End, SnipRunScriptProvider.cpp.
