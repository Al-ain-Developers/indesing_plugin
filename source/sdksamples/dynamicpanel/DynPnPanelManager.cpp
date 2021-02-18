//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/dynamicpanel/DynPnPanelManager.cpp $
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
#include "IControlView.h"
#include "IApplication.h"
#include "IPanelMgr.h"
#include "IActionManager.h"
#include "IMenuManager.h"
#include "ITextControlData.h"
#include "ISession.h"
#include "IPersistUIDData.h"
#include "IWindow.h"
// General includes:

#include "LocaleSetting.h"
#include "CoreResTypes.h" // kViewRsrcType
#include "ActionDefs.h"	// kDontTranslateChar
#include "AdobeMenuPositions.h"
#include "CPMUnknown.h"
#include "RsrcSpec.h"
#include "IPalettePanelUtils.h"
#include "UIDList.h"
// Project includes:
#include "DynPnID.h"
#include "IDynPnPanelManager.h"


IDynPnPanelManager* IDynPnPanelManager::QueryDynamicPanelManager()
{
	IDynPnPanelManager* retval=nil;
    do {
		// Get the UID for the Dynamic Panel Manager from the Session
		InterfacePtr<IPersistUIDData> uidData(GetExecutionContextSession(), IID_IDynPnPERSISTUIDDATA );
		ASSERT(uidData);
		if(!uidData) {
			break;
		}
		UID dynPanelMgrUID = uidData->GetUID();
		IDataBase *sessionDB = ::GetDataBase(GetExecutionContextSession());
		ASSERT(sessionDB);
		if(!sessionDB) {
			break;
		}
	
		if ( dynPanelMgrUID == kInvalidUID ) {
			// Create the Dynamic Panel Manager in the database
			// 
			dynPanelMgrUID = sessionDB->NewUID( kDynPnPanelManagerBoss );
			// Save the Dynamic Panel Manager's UID in the session boss object
			uidData->SetUID(dynPanelMgrUID);
		 }

		retval = (IDynPnPanelManager*) sessionDB->Instantiate(dynPanelMgrUID, IID_IDynPnPANELMANAGER);
	} while(kFalse);
	return retval;
}



/** Implements IDynPnPanelManager; responsible for managing lifetime of our dynamically created panels.

	
	@ingroup dynamicpanel
*/
class DynPnPanelManager : public CPMUnknown<IDynPnPanelManager>
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		DynPnPanelManager(IPMUnknown* boss);

		/**	Accessor for the count of (persistent) panels created
			@return int32 
		 */
		virtual int32 GetPanelsCreatedCount() ;

		/**	Create a panel with given name
			@param name 
			@return ErrorCode 
		 */
		virtual ErrorCode Create(const PMString& name);

		/**	Destroy the named panel
			@param name identifies the panel to destroy
			@return kSuccess on success, kFailure otherwise 
		 */
		virtual  ErrorCode Destroy(const PMString& name);

		/**	Determine if named panel is showing
			@param name specifies the panel whose visibility we're interested in
			@return bool16 
		 */
		virtual bool16 IsShowing(const PMString& name);

		/**	Serialise to or deserialise from given stream
			@param stream 
			@param implementation 
		 */
		virtual void ReadWrite(IPMStream*  stream, ImplementationID implementation);
	protected:

		/**	Method to start palette by name
			@param name identifies palette to start
			@return interface ptr on created palette, if it could be created, or nil if we couldnt start named palette
		 */
		UID StartupSomePalette( const PMString& name );

		/**	Method to destroy panel by UID
			@param panelUID identifies panel to destroy
		 */
		void DestroyDynamicPanel(const UID& panelUID);
	private:
			K2Vector<UID>			fDynamicPanelUIDList;


};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PERSIST_PMINTERFACE(DynPnPanelManager, kDynPnPanelManagerImpl)

/* DynPnPanelManager Constructor
*/
DynPnPanelManager::DynPnPanelManager(IPMUnknown* boss)
: CPMUnknown<IDynPnPanelManager>(boss)
{
}

int32 DynPnPanelManager::GetPanelsCreatedCount()
{
	return fDynamicPanelUIDList.size();
}

/* ReadWrite
*/
void DynPnPanelManager::ReadWrite(IPMStream*  s, ImplementationID implementation)
{
	/* 	
	//	REMINDER: 
	//	If you change the arrangement of persistent data in this method, 
	//	remember to update the format number in the PluginVersion resource. 
	//	(See the DynPnID.h file for the plug-in specific format numbers.) 
	*/
	
	int32 numUIDs=0;

	ASSERT(s);
	if(s->IsReading()) 
	{
		s->XferInt32(numUIDs);
		fDynamicPanelUIDList.reserve(numUIDs);
		UID theUID;
		for(int32 i = 0; i < numUIDs; i++) 
		{
			// Although we create the panel, we lose ownership when we call IPanelMgr::AdoptPanel
			// So, in our ReadWrite method, we should be calling XferReference rather than XferObject.
			s->XferReference(theUID);
			fDynamicPanelUIDList.push_back(theUID);
		}				
	}
	else 
	{
		numUIDs = fDynamicPanelUIDList.size();
		s->XferInt32(numUIDs);
		for(int32 i=0; i < numUIDs; i++) 
		{
			// Although we create the panel, we lose ownership when we call IPanelMgr::AdoptPanel
			// So, in our ReadWrite method, we should be calling XferReference rather than XferObject.
			s->XferReference(fDynamicPanelUIDList[i]);
		}
	}
}

ErrorCode DynPnPanelManager::Create(const PMString& name)
{
	bool16 retval=kFailure;
	do {
		PMString localName=name;
		localName.SetTranslatable(kFalse);	
		// Startup a new Palette for this
		UID	panelUID = this->StartupSomePalette(localName);
			
		// Save the panel's UID; this will get written to saved-data
		PreDirty();
		fDynamicPanelUIDList.push_back( panelUID );
		retval= kSuccess;
	} while(kFalse);
	
	return retval;
}

ErrorCode DynPnPanelManager::Destroy(const PMString& name)
{
	bool16 retval=kFailure;
	do {
		IDataBase* db = ::GetDataBase(this);
		ASSERT(db);
		if(!db) {
			break;
		}

		for ( int32 i=0; i<fDynamicPanelUIDList.size(); i++ ) {
			// We are instantiating a panel.. it should have
			// an ITextControlData interface containing the panel name
			// Let's see if this is the one to delete
			InterfacePtr<ITextControlData> textData((ITextControlData*)
					(db->Instantiate(fDynamicPanelUIDList[i], IID_ITEXTCONTROLDATA)));
			ASSERT(textData);
			if(!textData) {
				break;
			}
		
			// Check if this panel's name matches specified name
			if (name == textData->GetString()) {	
				// Destroy it based on UID now
				this->DestroyDynamicPanel(fDynamicPanelUIDList[i]);
				retval=kSuccess;		
				break;
			}
		}

	} while(kFalse);
	
	return retval;
}


bool16 DynPnPanelManager::IsShowing(const PMString& name)
{

	bool16 retval=kFalse;
	do {

		IDataBase* db = ::GetDataBase(this);
		ASSERT(db);
		if(!db) {
			break;
		}

		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		ASSERT(app);
		if(!app) {
			break;
		}
		InterfacePtr<IPanelMgr> panelMgr(app->QueryPanelManager());
		ASSERT(panelMgr);
		if(!panelMgr) {
			break;
		}

		for ( int32 i=0; i<fDynamicPanelUIDList.size(); i++ ) {
			// We are instantiating a panel.. it should have
			// an ITextControlData interface containing the panel name
			// Let's see if this is the one to delete
			InterfacePtr<ITextControlData> textData((ITextControlData*)
					(db->Instantiate(fDynamicPanelUIDList[i], IID_ITEXTCONTROLDATA)));
			ASSERT(textData);
			if(!textData) {
				break;
			}	// Check that this is visible
			InterfacePtr<IControlView> controlView(textData,UseDefaultIID());
			ASSERT(controlView);
			if(!controlView) {
				break;
			}
			if (name == textData->GetString()) {
				WidgetID widgetID = controlView->GetWidgetID();
				retval = panelMgr->IsPanelWithWidgetIDShown (widgetID);
				break;
			}
		}

	} while(kFalse);

	return retval;
			
}


UID DynPnPanelManager::StartupSomePalette( const PMString& name )
{
	UID newPanel = kInvalidUID;

	do {
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		ASSERT(app);
		if(!app) {
			break;
		}
		InterfacePtr<IPanelMgr> panelMgr(app->QueryPanelManager());
		ASSERT(panelMgr);
		if(!panelMgr) {
			break;
		}
		PMLocaleId localeId = LocaleSetting::GetLocale();
			
			PMString menuName;
			
			// Append the file's name to the menu name
			menuName.AppendW( kDontTranslateChar ) ;	// do this so the filename won't be translated by the menumgr.
			menuName.Append( name );
						
			// Make the new panel
			IDataBase *panelDB = ::GetDataBase(panelMgr);
			InterfacePtr<IControlView> panel((IControlView*) ::CreateObject(panelDB,
							RsrcSpec(localeId, kDynPnPluginID, kViewRsrcType, kSDKDefPanelResourceID, kTrue), IID_ICONTROLVIEW));
			ASSERT(panel);
			if(!panel) {
				break;
			}
			// Increment the reference count; conventional on Create or Query methods
//			panel->AddRef();
			panel->SetWidgetID ( kDynPnPanelWidgetID + this->GetPanelsCreatedCount() );
	
			//for return 
			newPanel = ::GetUID(panel);

			// Change the name of the panel
			InterfacePtr<ITextControlData> panelTextData(panel, UseDefaultIID());
			ASSERT(panelTextData);
			if(!panelTextData) {
				break;
			}
			panelTextData->SetString( name, kTrue, kTrue );
			
			// Insert a separator in the menu if this is the first open pnl
			if (this->GetPanelsCreatedCount() == 0 ) 
			{
				ASSERT(app);
				if(!app) {
					break;
				}
				InterfacePtr<IActionManager> actionMgr(app->QueryActionManager());
				ASSERT(actionMgr);
				if(!actionMgr) {
					break;
				}
				InterfacePtr<IMenuManager> menuMgr(actionMgr, UseDefaultIID());
				ASSERT(menuMgr);
				if(!menuMgr) {
					break;
				}
				menuMgr->AddMenuItem(kDynPnMenuSeparatorActionID, 
						"Main:&Window:-",
						kDynPnMenuSeparatorPosition,
						kFalse);
			}

			// Give the panel to the panel manager and display
			menuName.Insert("Main:&Window:");

			panelMgr->RegisterPanel( kTabPanelContainerType,panel, kFalse, "", kDynPnFirstPanelActionID + (this->GetPanelsCreatedCount()+1), menuName,kDynPnMenuPosition,c_Panel,kDynPnPluginID,0) ;
		
			// Make the Panel visible
			panelMgr->ShowPanelByWidgetID(kDynPnPanelWidgetID + this->GetPanelsCreatedCount());
	
	} while(kFalse);

	return newPanel;
}

void DynPnPanelManager::DestroyDynamicPanel(const UID& panelUID)
{
	do {
		PreDirty();
		// Remove the UID from the list
		K2Vector<UID>::iterator i = K2find(fDynamicPanelUIDList.begin(), fDynamicPanelUIDList.end(), panelUID);
		if ( i == fDynamicPanelUIDList.end())
		{
			break;
		}

		if (i != fDynamicPanelUIDList.end())
        {
            fDynamicPanelUIDList.erase(i);
        }
	

		// Remove the separator in the  menu if this is the last remaining panel
		if ( this->GetPanelsCreatedCount() == 0 ) 
		{
			InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
			ASSERT(app);
			if(!app) {
				break;
			}
			InterfacePtr<const IActionManager> actionMgr(app->QueryActionManager());
			ASSERT(actionMgr);
			if(!actionMgr) {
				break;
			}
			InterfacePtr<IMenuManager> menuMgr(actionMgr, UseDefaultIID());
			ASSERT(menuMgr);
			if(!menuMgr) {
				break;
			}
			menuMgr->RemoveAllMenusForAction( kDynPnMenuSeparatorActionID);
		}
		
		// Schedule the command to destroy the panel
		// Tricky. If the palette containing the panel
		// isn't visible, then we get an assert from the palette mgr 
		// 
		Utils<IPalettePanelUtils>()->ScheduleDestroyPanelCmd( panelUID );
	} while(kFalse);
}

//  Generated by Dolly build 17: template "IfPanelMenu".
// End, DynPnPanelManager.cpp.





