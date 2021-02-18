//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflowui/XDocBkUIPanelCreator.cpp $
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

// Interface Includes:
// none

// Implementation Includes:
#include "cpanelcreator.h"

// Project includes:
#include "XDocBkUIID.h"


/** This class is used when creating this plug-in's preferences panel for 
	the InDesign preferences selectable dialog.
 
	@ingroup xdocbookworkflowui
	
*/
class XDocBkUIPanelCreator : public CPanelCreator
{
	public:
		/** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		XDocBkUIPanelCreator(IPMUnknown* boss) : CPanelCreator(boss) {}

		/** Destructor.
		*/
		virtual	~XDocBkUIPanelCreator() {}
	
		/** GetPanelRsrcID()
		*/
		virtual RsrcID GetPanelRsrcID() const;
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(XDocBkUIPanelCreator, kXDocBkUIPanelCreatorImpl)


/*	GetPanelRsrcID
	Simply returns the resource id of the panel that is used
	in defining the IDList and IDListPair. (See XDocBkUI.fr)
*/
RsrcID XDocBkUIPanelCreator::GetPanelRsrcID() const
{
	return kSDKDefIDListPairResourceID;
}

// End, XDocBkUIPanelCreator.cpp

