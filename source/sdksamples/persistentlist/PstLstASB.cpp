//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstASB.cpp $
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

#include "VCPlugInHeaders.h"								

// Interface headers
#include "ICommandSequence.h"
#include "ISelectionManager.h"
#include "IPstLstSuite.h"			// Superclass declaration

// ID headers

// Other headers
#include "CmdUtils.h"
#include "HelperInterface.h"
#include "SelectionASBTemplates.tpp"
#include "SelectionExtTemplates.tpp"

//	CLASS FORWARDS
	class ClassInfo;

//	CLASS DECLARATIONS
/** 
	Abstract selection boss (ASB) IPstLstSuite implementation.  The purpose of this integrator suite is
	to determine how to forward the client request on to the CSB suite(s).  Note that the client does not
	interact with the CSB (which has all the real implementation of the suite) directly, the client interacts 
	with the ASB only.  Also note that the Suite API shouldn't contain model data that is specific to a 
	selection format (layout uidLists, text model/range, etc) so that the client code can be completely 
	decoupled from the underlying CSB.

	This suite is an advanced suite which uses selection extension.  The selection extension is a bridge 
	between a suite implementation with an unknown interface (IPstLstData) and the selection architecture. The
	main reason this extension is needed is so we can be notified of current selection's model change (thru
	SelectionAttributeChanged).
	 
	@ingroup persistentlist
	
*/
class PstLstASB : public CPMUnknown<IPstLstSuite>
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	PstLstASB(IPMUnknown* boss);
	
	/** Destructor. */
	virtual		~PstLstASB(void);

//	Member functions
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

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PstLstASB, kPstLstASBImpl)

/*	PstLstASB Constructor
*/
PstLstASB::PstLstASB(IPMUnknown* boss) :
	CPMUnknown<IPstLstSuite>(boss)
{
}

/*	PstLstASB Destructor
*/
PstLstASB::~PstLstASB(void)
{
}

#pragma mark-

/*	PstLstASB::GetNumDrawablePageItemSelected
*/
void PstLstASB::GetNumDrawablePageItemSelected(int32 &num) const
{
	CallEach(make_functor(&IPstLstSuite::GetNumDrawablePageItemSelected, num), this);
}
/*	PstLstASB::GetNthSelectedDrawablePageItem
*/
void PstLstASB::GetNthSelectedDrawablePageItem(int32 nth, UIDRef &item) const
{
	CallEach(make_functor(&IPstLstSuite::GetNthSelectedDrawablePageItem, nth, item), this);
}
