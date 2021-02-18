//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/cellpanel/CelPnlEditBoxEventHandler.cpp $
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
#include "ITextControlData.h"
#include "IPanelControlData.h"
#include "IWidgetParent.h"
#include "ITableCellData.h"

// General includes:
#include "CIDEditBoxEventHandler.h"
#include "IEvent.h"
#include "keyboarddefs.h"	

// Project includes:
#include "CelPnlID.h"

/** CelPnlEditBoxEventHandler
	implements the event handler.

	CelPnlEditBoxEventHandler implements IEventHandler by
	specializing keydown behavior in the concrete implementation CIDEditBoxEventHandler.

	@ingroup cellpanel
	
*/
class CelPnlEditBoxEventHandler : public CIDEditBoxEventHandler
{
	typedef CIDEditBoxEventHandler inherited;
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
				CelPnlEditBoxEventHandler(IPMUnknown *boss);
	/**
		Destructor.
	*/
	virtual		~CelPnlEditBoxEventHandler();
					
	 /**
		On key-down, swallow all keys which have no meaning for positive numeric entry.
		Note: we can't notify observers, since the alteration of the associated text
		control data doesn't occur until the Key-up event is processed.
		
		@param pEvent IEvent object.
	*/
	virtual bool16	KeyDown(IEvent* pEvent) ; //Override
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CelPnlEditBoxEventHandler, kCelPnlEditBoxEventHandlerImpl)

/* CelPnlEditBoxEventHandler
*/
CelPnlEditBoxEventHandler::CelPnlEditBoxEventHandler(IPMUnknown *boss) :
	inherited(boss)
{

}

/* ~CelPnlEditBoxEventHandler
*/
CelPnlEditBoxEventHandler::~CelPnlEditBoxEventHandler()
{
}


/* KeyDown
	On key-down, swallow all keys which have no meaning for positive numeric entry
	Note: we can't notify observers, since the alteration of the associated text
	control data doesn't occur until the Key-up event is processed
*/
bool16 CelPnlEditBoxEventHandler::KeyDown(IEvent* pEvent)
{
	if(pEvent == nil) return kFalse;

	if(pEvent->CmdKeyDown())
		return inherited::KeyDown(pEvent);

	const VirtualKey vKey = pEvent->GetVirtualKey();
	if( vKey == kVirtualReturnKey || vKey == kVirtualEnterKey)
	{
		do{
		InterfacePtr<IWidgetParent>		myParent(this, UseDefaultIID());
		if(myParent == nil) break;
			
		InterfacePtr<ITableCellData>	pTableCellData((ITableCellData*)myParent->QueryParentFor(IID_ITABLECELLDATA));
		if(pTableCellData == nil) break;

		InterfacePtr<IPanelControlData>	panel((IPanelControlData*)myParent->QueryParentFor(IID_IPANELCONTROLDATA));
		if(panel == nil) break;
			
		InterfacePtr<IControlView>		editBoxView(panel->FindWidget(kTableCellEditBoxWidgetID), UseDefaultIID());
		if(panel == nil) break;

		InterfacePtr<ITextControlData>	selectedChar(editBoxView, UseDefaultIID());
		if(selectedChar == nil) break;
			
		PMString  s = selectedChar->GetString();
		s.SetTranslatable(kFalse);
			
		pTableCellData->SetCellString(WideString(s)); // Set string to selected cell.
			
		InterfacePtr<IControlView> tableCell(panel->FindWidget(kTableCellWidgetID), UseDefaultIID());
		if(tableCell == nil) break;
			
		tableCell->Invalidate();

		}while(false);
		return inherited::KeyDown(pEvent);
	}


	if( vKey == kVirtualDeleteKey || vKey == kVirtualTabKey || vKey == kVirtualBackspaceKey || vKey == kVirtualEscapeKey
		 || vKey == kVirtualRightArrowKey || vKey == kVirtualLeftArrowKey
		 || vKey.GetChar() == '0' || vKey.GetChar() == '1' || vKey.GetChar() == '2' || vKey.GetChar() == '3'
		 || vKey.GetChar() == '4' || vKey.GetChar() == '5' || vKey.GetChar() == '6' || vKey.GetChar() == '7'
		  || vKey.GetChar() == '8' || vKey.GetChar() == '9')
		return inherited::KeyDown(pEvent);

	return kTrue; // prevent processing of non numeric keys.
}

// End, CelPnlEditBoxEventHandler.cpp