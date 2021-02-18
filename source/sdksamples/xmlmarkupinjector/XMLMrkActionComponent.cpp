//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlmarkupinjector/XMLMrkActionComponent.cpp $
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
#include "IActiveContext.h"
#include "ISelectionManager.h"
#include "IXMLMrkSuite.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"

// Project includes:
#include "XMLMrkID.h"


/** 
This class
	implements the actions that are executed when the plug-in's
	menu items are selected. XMLMrkActionComponent implements IActionComponent based on
	the partial implementation CActionComponent.

	The implementations are very straightforward given the IXMLMrkSuite interface that may
	be present on the abstract selection; given this interface, determine if a capability exists,
	and if it does then exercise that capability.

	@ingroup xmlmarkupinjector
	
*/
class XMLMrkActionComponent : public CActionComponent
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		XMLMrkActionComponent(IPMUnknown* boss);

		/**
			The action component should do the requested action.
			This is where the menu item's action is taken.
			When a menu item is selected, the Menu Manager determines
			which plug-in is responsible for it, and calls its DoAction
			with the ID for the menu item chosen.

			@param actionID identifies the menu item that was selected.
			@see CActionComponent::DoAction
			*/
		virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);

	protected:
		/** Helper method to discover if the active selection has our suite aggregated 
			@param ac IN The active context. From this, the selection is obtained.
			@return reference-incremented interface ptr to our suite if it exists on the abstract selection,
			or nil otherwise
		*/
		IXMLMrkSuite* queryOurSuite(IActiveContext* ac);
		
		/** Encapsulates functionality for the about menu item. */
		void DoAbout();

		/** Encapsulates functionality for the CompoundSection menu item. */
		void DoCompoundSection(IActiveContext* ac);

		/** Encapsulates functionality for the CompoundTable menu item. */
		void DoCompoundTable(IActiveContext* ac);

		/** Encapsulates functionality for the CompoundItemizedList menu item. */
		void DoCompoundItemizedList(IActiveContext* ac);

		/** Encapsulates functionality for the CompoundMediaObject menu item.*/
		void DoCompoundMediaObject(IActiveContext* ac);

		/** Encapsulates functionality for the CompoundKeywordSet menu item.*/
		void DoCompoundKeywordSet(IActiveContext* ac);

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(XMLMrkActionComponent, kXMLMrkActionComponentImpl)

/* XMLMrkActionComponent Constructor
*/
XMLMrkActionComponent::XMLMrkActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/* DoAction
*/
void XMLMrkActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kXMLMrkAboutActionID:
		{
			this->DoAbout();
			break;
		}

		case kXMLMrkCompoundSectionActionID:
		{
			this->DoCompoundSection(ac);
			break;
		}

		case kXMLMrkCompoundTableActionID:
		{
			this->DoCompoundTable(ac);
			break;
		}

		case kXMLMrkCompoundItemizedListActionID:
		{
			this->DoCompoundItemizedList(ac);
			break;
		}

		case kXMLMrkCompoundMediaObjectActionID:
		{
			this->DoCompoundMediaObject(ac);
			break;
		}

		case kXMLMrkCompoundKeywordSetActionID:
		{
			this->DoCompoundKeywordSet(ac);
			break;
		}

		default:
		{
			break;
		}
	}
}

/* DoAbout
*/
void XMLMrkActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
		kXMLMrkAboutBoxStringKey,				// Alert string
		kOKString, 						// OK button
		kNullString, 						// No second button
		kNullString, 						// No third button
		1,							// Set OK button to default
		CAlert::eInformationIcon				// Information icon.
	);
}

/* DoCompoundSection
*/
void XMLMrkActionComponent::DoCompoundSection(IActiveContext* ac)
{
	InterfacePtr<IXMLMrkSuite> iXMLMrkSuite(this->queryOurSuite(ac));
	if(iXMLMrkSuite && iXMLMrkSuite->CanMakeSectionComposite()) {
		iXMLMrkSuite->MakeSectionComposite();
	}
}

/* DoCompoundTable
*/
void XMLMrkActionComponent::DoCompoundTable(IActiveContext* ac)
{
	InterfacePtr<IXMLMrkSuite> iXMLMrkSuite(this->queryOurSuite(ac));
	if(iXMLMrkSuite && iXMLMrkSuite->CanMakeTable()) {
		iXMLMrkSuite->MakeTable(kTrue);
	}
}

/* DoCompoundItemizedList
*/
void XMLMrkActionComponent::DoCompoundItemizedList(IActiveContext* ac)
{
	InterfacePtr<IXMLMrkSuite> iXMLMrkSuite(this->queryOurSuite(ac));
	if(iXMLMrkSuite && iXMLMrkSuite->CanMakeItemizedList()) {
		iXMLMrkSuite->MakeItemizedList();
	}
}

/* DoCompoundMediaObject
*/
void XMLMrkActionComponent::DoCompoundMediaObject(IActiveContext* ac)
{
	InterfacePtr<IXMLMrkSuite> iXMLMrkSuite(this->queryOurSuite(ac));
	if(iXMLMrkSuite && iXMLMrkSuite->CanMakeMediaObject()) {
		iXMLMrkSuite->MakeMediaObject();
	}
}

/* DoCompoundKeywordSet
*/
void XMLMrkActionComponent::DoCompoundKeywordSet(IActiveContext* ac)
{
	InterfacePtr<IXMLMrkSuite> iXMLMrkSuite(this->queryOurSuite(ac));
	if(iXMLMrkSuite && iXMLMrkSuite->CanMakeKeywordSet()) {
		iXMLMrkSuite->MakeKeywordSet();
	}
}


/* queryOurSuite
*/
IXMLMrkSuite* XMLMrkActionComponent::queryOurSuite(IActiveContext* ac)
{
	if (ac == nil)
	{
		ASSERT(ac);
		return nil;
	}
	
	InterfacePtr<IXMLMrkSuite> iXMLMrkSuite(ac->GetContextSelection(), UseDefaultIID());
	return iXMLMrkSuite.forget();
}

//  Generated by Dolly build 17: template "IfPanelMenu".
// End, XMLMrkActionComponent.cpp.





