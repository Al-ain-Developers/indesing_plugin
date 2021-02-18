//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstLayoutCSB.cpp $
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

//===========================
//  INCLUDES
//===========================

#include "VCPlugInHeaders.h"								// For MSVC

// Interface headers
#include "ILayoutTarget.h"
#include "IDocumentBroadcastMsg.h"
#include "IPstLstData.h"
#include "IPstLstSuite.h"										// Superclass declaration
#include "IPstLstUIDList.h"										// Superclass declaration

// Other headers
//#include "HelperInterface.h"
#include "K2Vector.tpp"
#include "CmdUtils.h"
#include "UIDList.h"
#include "GenericID.h"										// ID definition header
#include "K2Vector.tpp"
#include "SelectionExtTemplates.tpp"

// Project headers
#include "PstLstUtils.h"
#include "PstLstID.h"

//	CLASS DECLARATIONS
/** 
	Layout concrete selection boss (CSB) IPstLstSuite implementation.  The suite implementations on the CSBs are 
	responsible for doing all of the model specific work.  The implementation of a CSB suite deals with the 
	model format of its owning boss. The only information that the suite should need is from sibling interfaces 
	on the CSB, primarily the target interface. This interface specifies which items to act upon. For the 
	LayoutCSB, the target interface is ILayoutTarget which wraps a UIDList. So usually you see the methods in
	this CSB will first get an InterfacePtr to a ILayoutTarget, then it gets the UIDList of the selected items
	from the pointer.
	
    Note that the client does not interact with the CSB (which has all the real implementation of the suite) 
    directly, the client interacts with the ASB only.  Also note that the Suite API shouldn't contain model 
    data that is specific to a selection format (layout uidLists, text model/range, etc) so that the client 
    code can be completely decoupled from the underlying CSB.

	This suite is an advanced suite which uses selection extension.  The selection extension is a bridge 
	between a suite implementation with an unknown interface (IPstLstData) and the selection architecture. The
	main reason this extension is needed is so we can be notified of current selection's model change (thru
	SelectionAttributeChanged).
	 
	@ingroup persistentlist
	
*/
class PstLstLayoutCSB : public CPMUnknown<IPstLstSuite>
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	PstLstLayoutCSB(IPMUnknown* boss);
	
	/** Destructor. */
	virtual					~PstLstLayoutCSB(void);

//	Suite Member functions
public:

	/**
		Check the number of a drawable page item selected, a drawable page item will have a IPstLstUIDList interface when the plug-in is loaded.
		So we will check if we can get a valid IPstLstUIDList InterfacePtr thru the selected items as the test to see if it is a
		drawable page item.
	*/
	virtual void	GetNumDrawablePageItemSelected(int32 &num)const;

	/**
		Get the nth selected drawable page item with a valid IPstLstUIDList Interface.
	*/
	virtual void	GetNthSelectedDrawablePageItem(int32 nth, UIDRef &item)const;		

	//________________________________________________________________________________
	//	Selection Extention functions 
	//________________________________________________________________________________
	/**
		This function is called when the selection sub-system starts up. Any suite initialization
		code can be placed in this funciton. Called for suites on the ASB and CSBs.
	*/
	virtual void				Startup			 					(void) {}

	/**
		This function is called when the selection sub-system shuts down. Any suite termination 
		code can be placed in this funciton. Called for suites on the ASB and CSBs.
	*/
	virtual void				Shutdown			 				(void) {}

	/**
		This function is called when an item is added to or removed from the selection.  Suites on the 
		changing CSB and the ASB are called.	
	*/
	virtual void				SelectionChanged 					(SuiteBroadcastData*, const PMIID&, void*) {}

	/**
		This function is called when an attribute of the selection has changed. It is only called on the CSB whose
		selection attribute has changed. For the layout CSB an ProtocolCollection must be supplied first.
	*/
	virtual void				SelectionAttributeChanged 			(SuiteBroadcastData*, const PMIID&, void*);

	/**
		This is only supported on the ASB and is rarely used.
	*/
	virtual void				HandleIntegratorSuiteMessage		(void*, const ClassID&, ISubject*, const PMIID&, void*) {}

	/**
		Each suite must define the protocols that contain the attributes that they care about. The Layout CSB's selection 
		attribute observer asks each suite with a selection extension for a list of protocols to observer on the document.  
		Thereby, allowing all suites to share a single observer. When a document broadcast occurs with the specified 
		protocol, the suite must first determine if the command affects the selection by comparing the commands target to 
		the LayoutTarget (This is necessary because all commands don't use the UIDList for page items.).	
	*/
	virtual ProtocolCollection*	CreateObserverProtocolCollection(void);

	
};

CREATE_PMINTERFACE(PstLstLayoutCSB, kPstLstLayoutCSBImpl)

/*
	Instatiate the selection extension template and create an InDesign interface.
	The parameter to the template is the suite implementation class.
*/
template class SelectionExt<PstLstLayoutCSB>;
CREATE_PMINTERFACE(SelectionExt<PstLstLayoutCSB>, kPstLstSuiteLayoutSelectionExtImpl)

/*	Constructor
*/
PstLstLayoutCSB::PstLstLayoutCSB(IPMUnknown* boss) :
	CPMUnknown<IPstLstSuite>(boss)
{
}

#pragma mark -

/*	Destructor
*/
PstLstLayoutCSB::~PstLstLayoutCSB(void)
{
}




/*	PstLstLayoutCSB::GetNumDrawablePageItemSelected
*/
void PstLstLayoutCSB::GetNumDrawablePageItemSelected(int32& num)const
{
	num = 0;
	do
	{
		InterfacePtr<ILayoutTarget>		iLayoutTarget(this, UseDefaultIID());
		if (iLayoutTarget == nil)
		{
			ASSERT_FAIL("ILayoutTarget invalid");
			break;
		}
		const UIDList					selectedItems(iLayoutTarget->GetUIDList(kStripStandoffs));

		// loop thru all the selected items to see if any of it is a drawable page item.
		// we only want to apply the IPstLst data to drawable page item, since the IPstLstUIDList interface
		// is only aggregated to kDrawablePageItemBoss.  
		// so the way to check if it is a drawable page item is to see if it has IPstLstUIDList interface
		for (int32 i = 0; i < selectedItems.Length(); i++)
		{
			InterfacePtr<IPstLstUIDList> iUIDList(selectedItems.GetRef(i), UseDefaultIID());
			if (iUIDList != nil)
			{
				num ++;
			}
		}
	} while (kFalse);
}

/*	PstLstLayoutCSB::GetNumDrawablePageItemSelected
*/
void PstLstLayoutCSB::GetNthSelectedDrawablePageItem(int32 nth, UIDRef& item) const
{
	int32	count = 0;
	do
	{
		InterfacePtr<ILayoutTarget>		iLayoutTarget(this, UseDefaultIID());
		if (iLayoutTarget == nil)
		{
			ASSERT_FAIL("ILayoutTarget invalid");
			break;
		}
		const UIDList					selectedItems(iLayoutTarget->GetUIDList(kStripStandoffs));

		for (int32 i = 0; i < selectedItems.Length(); i++)
		{
			InterfacePtr<IPstLstUIDList> iUIDList(selectedItems.GetRef(i), UseDefaultIID());
			if (iUIDList != nil)
			{
				if (count == nth)
				{
					item = selectedItems.GetRef(i);
					break;
				}

				count++;
			}

		}
	} while (kFalse);
}


/*	PstLstLayoutCSB::CreateObserverProtocolCollection
*/
ProtocolCollection*	PstLstLayoutCSB::CreateObserverProtocolCollection(void)
{
	ProtocolCollection*	protocolList = new ProtocolCollection();
	protocolList->insert(protocolList->begin(), 1, IPstLstData::kDefaultIID);

	return protocolList;
}

/*	PstLstLayoutCSB::SelectionAttributeChanged
*/
void PstLstLayoutCSB::SelectionAttributeChanged(SuiteBroadcastData* broadcastData, const PMIID& messageID, void* message)
{
	if (messageID == IID_IDOCUMENT_BROADCAST)
		{
		IDocumentBroadcastMsg*	layoutMessage = static_cast<IDocumentBroadcastMsg*>(message);
		do {
			if (layoutMessage->GetPMIID() == IPstLstData::kDefaultIID)
			{
				// check to see if we've been called before and have already signalled
				// that we want client code to be messaged.
				PMIID key(IPstLstSuite::kDefaultIID);
				if (FindLocationInSorted(*broadcastData, key) >= 0)
					break;
				InsertKeyValueInSorted(*broadcastData, static_cast<PMIID>(IPstLstSuite::kDefaultIID), boost::shared_ptr<SelectionSuiteData>());
			}
			else	
				ASSERT_FAIL("Selection Attribute changed called for an unregistered protocol.");
		} while(false);
		}
}

