//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/tableattributes/TblAttSelectionObserver.cpp $
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
#include "ISelectionManager.h"
#include "ITableSuite.h"
#include "ITableAttrRealNumber.h"
#include "IPanelControlData.h"
#include "IControlView.h"
#include "ITextValue.h"
#include "SelectionObserver.h"

// Project includes
#include "TblAttID.h"
#include "TblAttQueryMutHelper.h"

/**	Class to observe changes in the active context, and change UI when attributes change.
	@ingroup tableattributes
 */
class TblAttSelectionObserver : public ActiveSelectionObserver
{
public:
	/** Constructor.
	*/
	TblAttSelectionObserver(IPMUnknown *boss);

	/** Destructor.
	*/
	virtual ~TblAttSelectionObserver();

protected:
	/**	Everything relating to the selection should update.
		Either 	(a) there is a new active selection,
		or 		(b) the items in the selection has changed.

		If the table selected changes in some way then the UI will get
		updated accordingly.
	*/
	virtual void    HandleSelectionChanged (const ISelectionMessage*);

	/** Some aspect of one or more items in the selection has changed. Only those
		clients whose observed suiteIID was affected by the selection message 
		should update. The suite may have also sent some suite specific broadcast
		data.

		If there is a change in one of the table strokes, the UI will get updated
		correspondingly.
	*/
	virtual void HandleSelectionAttributeChanged(const ISelectionMessage* selectionMessage);

private:
	void onSelectionChange();
	void processSelectionChanged();
	void setWidgetState(const WidgetID& widgetID, PMReal weightProp);
	void clearWidget(const WidgetID& widgetID);
	void updateCellWidgetState(const WidgetID& widgetID, const ClassID& classID);   
	void updateRowWidgetState(const WidgetID& widgetID, const ClassID& classID);    
	void updateColWidgetState(const WidgetID& widgetID, const ClassID& classID);    
	void updateTableWidgetState(const WidgetID& widgetID, const ClassID& classID);  
	void clearAllWidgets();
	void updateAnyWidget(const WidgetID& widgetID, PMReal weight);

	TblAttQueryMutHelper fQueryMutHelper;
};

CREATE_PMINTERFACE(TblAttSelectionObserver, kTblAttSelectionObserverImpl);


TblAttSelectionObserver::TblAttSelectionObserver(IPMUnknown *boss) :
ActiveSelectionObserver(boss, IID_ITBLATTSELECTIONOBSERVER)
{
}


TblAttSelectionObserver::~TblAttSelectionObserver()
{
}

/*

*/
void TblAttSelectionObserver::HandleSelectionChanged
	(
	const ISelectionMessage* selectionMessage
	)
{
	this->onSelectionChange();
}



/* HandleSelectionAttributeChanged
*/
void TblAttSelectionObserver::HandleSelectionAttributeChanged
	(
	const ISelectionMessage* selectionMessage
	)
{
	if (selectionMessage && selectionMessage->WasSuiteAffected(IID_ITABLE_ISUITE))
		this->processSelectionChanged();
}

void TblAttSelectionObserver::onSelectionChange()
{
	// OK, how do we know that it's something to do with a table?
	do
	{
		InterfacePtr<ITableSuite> tableSuite(fCurrentSelection, UseDefaultIID());
		if (tableSuite==nil)
		{
			break;
		}

		if (tableSuite->CanApplyTableOverrides())
		// It's probably a table in the selection
		{
			this->processSelectionChanged();
			// We may want to update their states next time to invalid
			return;
		}

	} while (kFalse);

	this->clearAllWidgets();

}


/* processSelectionChanged
*/
void TblAttSelectionObserver::processSelectionChanged()
{
	this->updateCellWidgetState(kTblAttCellLeftComboBoxWidgetID, kCellAttrLeftStrokeWeightBoss);    
	this->updateCellWidgetState(kTblAttCellRightComboBoxWidgetID, kCellAttrRightStrokeWeightBoss);  
	this->updateCellWidgetState(kTblAttCellTopComboBoxWidgetID, kCellAttrTopStrokeWeightBoss);  
	this->updateCellWidgetState(kTblAttCellBottomComboBoxWidgetID, kCellAttrBottomStrokeWeightBoss);    

	this->updateRowWidgetState(kTblAttRowComboBoxWidgetID, kTableAttrRowStrokeWeightBoss);  
	this->updateColWidgetState(kTblAttColComboBoxWidgetID, kTableAttrColStrokeWeightBoss);  

	this->updateTableWidgetState(kTblAttTableLeftComboBoxWidgetID, kTableAttrOuterLeftStrokeWeightBoss);    
	this->updateTableWidgetState(kTblAttTableRightComboBoxWidgetID, kTableAttrOuterRightStrokeWeightBoss);  
	this->updateTableWidgetState(kTblAttTableTopComboBoxWidgetID, kTableAttrOuterTopStrokeWeightBoss);  
	this->updateTableWidgetState(kTblAttTableBottomComboBoxWidgetID, kTableAttrOuterBottomStrokeWeightBoss);    

}


/* updateCellWidgetState
*/
void TblAttSelectionObserver::updateCellWidgetState(const WidgetID& widgetID, const ClassID& classID)
{
	Tables::ESelectionSides sides = Tables::eNoSides;
	switch (classID.Get())
	{
	case kCellAttrLeftStrokeWeightBoss:
		sides = Tables::eLeftSide;
		break;
	case kCellAttrRightStrokeWeightBoss:    
		sides = Tables::eRightSide;
		break;
	case kCellAttrTopStrokeWeightBoss:
		sides = Tables::eTopSide;
		break;
	case kCellAttrBottomStrokeWeightBoss:
		sides = Tables::eBottomSide;
		break;
	}
	PMReal weight = fQueryMutHelper.GetCellStroke(sides);
	this->updateAnyWidget(widgetID, weight);
}

/* updateRowWidgetState
*/
void TblAttSelectionObserver::updateRowWidgetState(const WidgetID& widgetID, const ClassID& classID)
{
	PMReal weight = fQueryMutHelper.GetTableAttributeReal(classID);
	this->updateAnyWidget(widgetID,weight);
}

/* updateRowWidgetState
*/
void TblAttSelectionObserver::updateColWidgetState(const WidgetID& widgetID, const ClassID& classID)
{
	PMReal weight = fQueryMutHelper.GetTableAttributeReal(classID);
	this->updateAnyWidget(widgetID,weight);
}



/* updateTableWidgetState
*/
void TblAttSelectionObserver::updateTableWidgetState(const WidgetID& widgetID, const ClassID& classID)
{
	PMReal weight = fQueryMutHelper.GetTableAttributeReal(classID);
	this->updateAnyWidget(widgetID,weight);
}

/* setWidgetState
*/
void TblAttSelectionObserver::setWidgetState(const WidgetID& widgetID, PMReal weightProp)
{
	do
	{
		InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
		ASSERT(panelData);
		if (panelData==nil)
		{
			break;
		}

		IControlView* controlView = panelData->FindWidget(widgetID);
		ASSERT(controlView);
		if (controlView==nil)
		{
			break;
		}

		InterfacePtr<ITextValue> adjustedValue(controlView, UseDefaultIID());
		ASSERT(adjustedValue);
		if (adjustedValue == nil)
		{
			break;
		}
		adjustedValue->SetTextFromValue(weightProp, kTrue/*invalidate*/, kFalse/*don't notify*/);
	} while (kFalse);
}


/* clearWidget
*/
void TblAttSelectionObserver::clearWidget(const WidgetID& widgetID)
{
	do
	{
		InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
		ASSERT(panelData);
		if (panelData==nil)
		{
			break;
		}

		IControlView* controlView = panelData->FindWidget(widgetID);
		ASSERT(controlView);
		if (controlView==nil)
		{
			break;
		}

		InterfacePtr<ITextValue> adjustedValue(controlView, UseDefaultIID());
		ASSERT(adjustedValue);
		if (adjustedValue == nil)
		{
			break;
		}
		adjustedValue->SetControlState(ITextValue::kUnknown, kTrue/*invalidate*/, kFalse/*don't notify*/);
	} while (kFalse);
}


/*
clearAllWidgets
*/
void TblAttSelectionObserver::clearAllWidgets()
{
	this->clearWidget(kTblAttCellLeftComboBoxWidgetID);
	this->clearWidget(kTblAttCellRightComboBoxWidgetID);
	this->clearWidget(kTblAttCellTopComboBoxWidgetID);
	this->clearWidget(kTblAttCellBottomComboBoxWidgetID);

	this->clearWidget(kTblAttRowComboBoxWidgetID);
	this->clearWidget(kTblAttColComboBoxWidgetID);

	this->clearWidget(kTblAttTableLeftComboBoxWidgetID);
	this->clearWidget(kTblAttTableRightComboBoxWidgetID);
	this->clearWidget(kTblAttTableTopComboBoxWidgetID);
	this->clearWidget(kTblAttTableBottomComboBoxWidgetID);
}

/* updateAnyWidget
*/
void TblAttSelectionObserver::updateAnyWidget(const WidgetID& widgetID, PMReal weight)
{
	if (weight >= 0.0)
	{
		this->setWidgetState(widgetID, weight);
	}
	else
	{
		this->clearWidget(widgetID);        
	}
}

// End, TblAttSelectionObserver.cpp.
