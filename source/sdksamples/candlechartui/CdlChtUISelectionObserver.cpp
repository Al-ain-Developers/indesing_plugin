//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechartui/CdlChtUISelectionObserver.cpp $
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
#include "ILayoutSelectionSuite.h"
#include "ILayoutTarget.h"
#include "IPanelControlData.h"
#include "ISelectionManager.h"
#include "ISelectionUtils.h"
#include "ITextControlData.h"

// General includes;
#include "SelectionObserver.h"
#include "Trace.h"
#include "widgetid.h"

// Project includes:
#include "CdlChtUIID.h"
#include "ICdlChartData.h"
#include "ICdlChartSuite.h"


/** Observes changes in the active context.

	@ingroup candlechartui
	
 */
class CdlChtUISelectionObserver : public ActiveSelectionObserver
{
public:
	/** Constructor.
	*/
	CdlChtUISelectionObserver(IPMUnknown* boss);

	/** Destructor.
	*/
	virtual ~CdlChtUISelectionObserver();

protected:
//		virtual void AutoAttach(void);

	/**	Everything relating to the selection should update.
		Either 	(a) there is a new active selection,
		or 		(b) the items in the selection has changed.

		If the table selected changes in some way then the UI will get
		updated accordingly.
	*/
	virtual void HandleSelectionChanged(const ISelectionMessage* selectionMessage);

};


CREATE_PMINTERFACE(CdlChtUISelectionObserver, kCdlChtUISelectionObserverImpl);

/* Constructor
*/
CdlChtUISelectionObserver::CdlChtUISelectionObserver(IPMUnknown* boss) :
	ActiveSelectionObserver(boss)	
{
}


/* Destructor
*/
CdlChtUISelectionObserver::~CdlChtUISelectionObserver()	
{
}

/* HandleSelectionChanged
*/
void CdlChtUISelectionObserver::HandleSelectionChanged(const ISelectionMessage* selectionMessage)
{
	do
	{
		WideString nameStr;
		InterfacePtr<ICdlChartSuite> candleChartSuite(fCurrentSelection, UseDefaultIID());
		if (candleChartSuite && candleChartSuite->CanGetChartName())
		{
			candleChartSuite->GetChartName(nameStr);
		}

		// Obtain panel control data to access widget kCdlChtUINameWidgetID
		InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
		if (iPanelControlData == nil)
		{
			break;
		}

		// Find the name static widget
		IControlView* iControlView = iPanelControlData->FindWidget(kCdlChtUINameWidgetID);
		if (iControlView == nil)
		{
			break;
		}

		// Obtain ITextControlData in order to update the name 
		InterfacePtr<ITextControlData> iTextControlData(iControlView, UseDefaultIID());
		if (iTextControlData == nil)
		{
			break;
		}

		PMString nameUIStr(nameStr);
		nameUIStr.SetTranslatable(kFalse);
		iTextControlData->SetString(nameUIStr);

	} while (kFalse);
}


// End, CdlChtUISelectionObserver.cpp.
