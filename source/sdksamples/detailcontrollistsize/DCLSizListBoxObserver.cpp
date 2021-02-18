//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/detailcontrollistsize/DCLSizListBoxObserver.cpp $
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
#include "ISubject.h"
#include "IPalettePanelUtils.h"
#include "ITreeViewController.h"
#include "ITreeViewWidgetMgr.h"
#include "TreeViewDefs.h"
#include "StringNodeID.h"
#include "K2Vector.tpp"

// Implementation includes:
#include "CAlert.h"
#include "CObserver.h"
#include "DCLSizID.h"
#include "widgetid.h"



/**
	Implements IObserver. The intent of this class is to provide handling for the AutoAttach (sent when shown), AutoDetach (hidden)
	and Update (when listbox hit by end-user, for instance) message
	
	The class is derived from CObserver, and overrides the AutoAttach(), AutoDetach(), and Update() methods.
	This class implements the IObserver interface using the CObserver helper class,
	and is listening along the IID_ILISTCONTROLDATA protocol for changes in the list-data model.

	@ingroup detailcontrollistsize
	
*/
class DCLSizListBoxObserver : public CObserver
{
public:
	
	/**
		Constructor for WLBListBoxObserver class.
		@param interface ptr from boss object on which this interface is aggregated.
	*/
	DCLSizListBoxObserver(IPMUnknown* boss);

	/**
		Destructor for DCLSizListBoxObserver class - 
		performs cleanup 
	*/	
	~DCLSizListBoxObserver();

	/**
		AutoAttach is only called for registered observers
		of widgets.  This method is called by the application
		core when the widget is shown.	
	*/	
	virtual void AutoAttach();

	/**
		AutoDetach is only called for registered observers
		of widgets. Called when widget hidden.
	*/	
	virtual void AutoDetach();

	/**
		Update is called for all registered observers, and is
		the method through which changes are broadcast. 

		This class is interested in changes along IID_ILISTCONTROLDATA protocol with classID of
		kListSelectionChangedByUserMessage. This message is sent when a user clicks on an element
		in the list-box.
	
		@param theChange this is specified by the agent of change; it can be the class ID of the agent,
		or it may be some specialised message ID.
		@param theSubject this provides a reference to the object which has changed; in this case, the button
		widget boss object that is being observed.
		@param protocol the protocol along which the change occurred.
		@param changedBy this can be used to provide additional information about the change or a reference
		to the boss object that caused the change.
	*/	
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(DCLSizListBoxObserver, kDCLSizListBoxObserverImpl)


/* Constructor
*/
DCLSizListBoxObserver::DCLSizListBoxObserver(IPMUnknown* boss)
: CObserver(boss)
{
}

/* Destructor
*/
DCLSizListBoxObserver::~DCLSizListBoxObserver()
{
}

/* AutoAttach
*/
void DCLSizListBoxObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject != nil)
	{
		subject->AttachObserver(this, IID_ITREEVIEWCONTROLLER);
	}
}

/* AutoDetach
*/
void DCLSizListBoxObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject != nil)
	{
		subject->DetachObserver(this, IID_ITREEVIEWCONTROLLER);
	}
}

/* Update
*/
void DCLSizListBoxObserver::Update
(
	const ClassID& theChange, 
	ISubject* theSubject, 
	const PMIID &protocol, 
	void* changedBy
)
{
	if ((protocol == IID_ITREEVIEWCONTROLLER) && 
		(theChange == kListSelectionChangedMessage)) 
	{
		do 
		{
			InterfacePtr<ITreeViewController> 	controller(this, UseDefaultIID());
			ASSERT(controller);
			if(!controller)
			{
				break;
			}

			NodeIDList selectedItems;
			controller->GetSelectedItems(selectedItems);
			const int kSelectionLength =  selectedItems.size() ;
			if (kSelectionLength> 0 )
			{
				PMString dbgInfoString("Selected item(s): ");
				for(int32 i = 0; i <  kSelectionLength; i++)
				{
					TreeNodePtr<StringNodeID> oneNode(selectedItems[i]);
					PMString item = oneNode->GetString();
					item.Translate();
					dbgInfoString.Append(item);
  					if(i < kSelectionLength - 1) 
						dbgInfoString += ", ";
				}

				dbgInfoString.SetTranslatable(kFalse);	// only for debug- not real code
				CAlert::InformationAlert(dbgInfoString);
			}
		} while(false);
	}
}

// End, DCLSizListBoxObserver.cpp.

