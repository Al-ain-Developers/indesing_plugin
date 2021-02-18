//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/tableattributes/TblAttWidgetObserver.cpp $
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
#include "ISubject.h"
#include "IControlView.h"
#include "ITextValue.h"
#include "IPanelControlData.h"
// Impl includes
#include "CObserver.h"
#include "Trace.h"
// Project includes
#include "TblAttID.h"
#include "TblAttQueryMutHelper.h"


/**
	Class to observe changes in the active context.
	@ingroup tableattributes
	
 */
class TblAttWidgetObserver : public CObserver
{
public:
	/** 
		Constructor.
	*/
	TblAttWidgetObserver(IPMUnknown *boss);
	/**
		Destructor.
	*/
	virtual ~TblAttWidgetObserver();
	/** 
		attaches observer to the panel's widgets.
	*/
	virtual void AutoAttach();

	/** 
		detaches observer from the panel's widgets.
	*/
	virtual void AutoDetach();

	/**
		a panel widget value has been changed.
	*/
	virtual void Update( const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy ) ;

private:

	void attachWidget(InterfacePtr<IPanelControlData>&  panelControlData, const WidgetID& widgetID, const PMIID& interfaceID);
	void detachWidget(InterfacePtr<IPanelControlData>& panelControlData, const WidgetID& widgetID, const PMIID& interfaceID);
	void cellStrokeWeightChanged(InterfacePtr<IControlView>& widgetControlView);
	void rowStrokeWeightChanged(InterfacePtr<IControlView>&  widgetControlView);
	void colStrokeWeightChanged(InterfacePtr<IControlView>& widgetControlView);
	void tableStrokeWeightChanged(InterfacePtr<IControlView>&  widgetControlView);

	const PMIID fObserverIID;
	TblAttQueryMutHelper fQueryMutHelper;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(TblAttWidgetObserver, kTblAttWidgetObserverImpl);

/* Constructor
*/
TblAttWidgetObserver::TblAttWidgetObserver(IPMUnknown *boss) 
:	CObserver(boss), fObserverIID(IID_ITBLATTWIDGETOBSERVER)
{
}

/* Destructor
*/
TblAttWidgetObserver::~TblAttWidgetObserver()
{
}

/* AutoAttach
*/
void TblAttWidgetObserver::AutoAttach()
{
	do
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if (panelControlData == nil)
		{
			break;
		}
		const PMIID alongProtocol = IID_ITEXTCONTROLDATA;
		this->attachWidget(panelControlData, kTblAttCellLeftComboBoxWidgetID, alongProtocol);
		this->attachWidget(panelControlData, kTblAttCellRightComboBoxWidgetID, alongProtocol);
		this->attachWidget(panelControlData, kTblAttCellTopComboBoxWidgetID, alongProtocol);
		this->attachWidget(panelControlData, kTblAttCellBottomComboBoxWidgetID, alongProtocol);

		this->attachWidget(panelControlData, kTblAttRowComboBoxWidgetID, alongProtocol);
		this->attachWidget(panelControlData, kTblAttColComboBoxWidgetID, alongProtocol);

		this->attachWidget(panelControlData, kTblAttTableLeftComboBoxWidgetID, alongProtocol);
		this->attachWidget(panelControlData, kTblAttTableRightComboBoxWidgetID, alongProtocol);
		this->attachWidget(panelControlData, kTblAttTableTopComboBoxWidgetID, alongProtocol);
		this->attachWidget(panelControlData, kTblAttTableBottomComboBoxWidgetID, alongProtocol);
	} while (kFalse);
}

/* AutoDetach
*/
void TblAttWidgetObserver::AutoDetach()
{
	do
	{
		InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if (panelControlData == nil)
		{
			break;
		}

		const PMIID alongProtocol = IID_ITEXTCONTROLDATA;   
		this->detachWidget(panelControlData, kTblAttCellLeftComboBoxWidgetID, alongProtocol);
		this->detachWidget(panelControlData, kTblAttCellRightComboBoxWidgetID, alongProtocol);
		this->detachWidget(panelControlData, kTblAttCellTopComboBoxWidgetID, alongProtocol);
		this->detachWidget(panelControlData, kTblAttCellBottomComboBoxWidgetID, alongProtocol);

		this->detachWidget(panelControlData, kTblAttRowComboBoxWidgetID, alongProtocol);
		this->detachWidget(panelControlData, kTblAttColComboBoxWidgetID, alongProtocol);

		this->detachWidget(panelControlData, kTblAttTableLeftComboBoxWidgetID, alongProtocol);
		this->detachWidget(panelControlData, kTblAttTableRightComboBoxWidgetID, alongProtocol);
		this->detachWidget(panelControlData, kTblAttTableTopComboBoxWidgetID, alongProtocol);
		this->detachWidget(panelControlData, kTblAttTableBottomComboBoxWidgetID, alongProtocol);

	} while (kFalse);
}


/* Update
*/
void TblAttWidgetObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy )
{
	TRACE("TblAttWidgetObserver::Update(), protocol =  %d, theChange = %d\n", protocol.Get(), theChange.Get());
	do
	{
		// Take action based on the message protocol
		if (theChange == kTextChangeStateMessage)
		{
			InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
			ASSERT(controlView != nil);
			if (controlView==nil)
			{
				break;
			}

			WidgetID widgetID = controlView->GetWidgetID();
			switch (widgetID.Get())
			{
			case kTblAttCellLeftComboBoxWidgetID:
			case kTblAttCellRightComboBoxWidgetID:
			case kTblAttCellTopComboBoxWidgetID:
			case kTblAttCellBottomComboBoxWidgetID:
				{

					this->cellStrokeWeightChanged(controlView);
				}
				break;


			case kTblAttTableLeftComboBoxWidgetID:
			case kTblAttTableRightComboBoxWidgetID:
			case kTblAttTableTopComboBoxWidgetID:
			case kTblAttTableBottomComboBoxWidgetID:
				{

					this->tableStrokeWeightChanged(controlView);
				}
				break;


			case kTblAttColComboBoxWidgetID:
				{

					this->colStrokeWeightChanged(controlView);
				}
				break;

			case kTblAttRowComboBoxWidgetID:
				{

					this->rowStrokeWeightChanged(controlView);
				}
				break;


			default:
				break;
			}
		}

	} while (kFalse);

}

/* attachWidget
*/
void TblAttWidgetObserver::attachWidget(InterfacePtr<IPanelControlData>& panelControlData, const WidgetID& widgetID, const PMIID& interfaceID)
{
	ASSERT(panelControlData);

	TRACE("TblAttWidgetObserver::attachWidget(widgetID=0x%x, interfaceID=0x%x\n", widgetID.Get(), interfaceID.Get());
	do
	{
		if (panelControlData == nil) break;

		IControlView* controlView = panelControlData->FindWidget(widgetID);
		ASSERT(controlView);
		if (controlView == nil)
		{
			break;
		}

		InterfacePtr<ISubject> subject(controlView, UseDefaultIID());
		ASSERT(subject);
		if (subject == nil)
		{
			break;
		}
		subject->AttachObserver(this, interfaceID, fObserverIID);
	}
	while (kFalse);
}

/* detachWidget
*/
void TblAttWidgetObserver::detachWidget(InterfacePtr<IPanelControlData>& panelControlData, const WidgetID& widgetID, const PMIID& interfaceID)
{
	ASSERT(panelControlData);
	do
	{
		if (panelControlData == nil) break;

		IControlView* controlView = panelControlData->FindWidget(widgetID);
		ASSERT(controlView);
		if (controlView == nil)
		{
			break;
		}

		InterfacePtr<ISubject> subject(controlView, UseDefaultIID());
		ASSERT(subject);
		if (subject == nil)
		{
			break;
		}
		subject->DetachObserver(this, interfaceID, fObserverIID);
	}
	while (kFalse);
}

/* cellStrokeWeightChanged
*/
void TblAttWidgetObserver::cellStrokeWeightChanged(InterfacePtr<IControlView>& widgetControlView)
{
	do
	{
		ASSERT(widgetControlView);
		if (widgetControlView==nil)
		{
			break;
		}

		InterfacePtr<ITextValue> textValue(widgetControlView, UseDefaultIID());
		ASSERT(textValue);
		if (textValue==nil)
		{
			break;
		}

		PMReal newStrokeWeight = textValue->GetTextAsValue();
		TRACE("TblAttWidgetObserver::cellStrokeWeightChanged() newStrokeWeight=%f\n", ::ToDouble(newStrokeWeight));

		WidgetID widgetID = widgetControlView->GetWidgetID();

		Tables::ESelectionSides sides = Tables::eNoSides;

		switch (widgetID.Get())
		{
		case    kTblAttCellLeftComboBoxWidgetID:
			sides = Tables::eLeftSide;
			break;

		case    kTblAttCellRightComboBoxWidgetID:
			sides = Tables::eRightSide;
			break;

		case    kTblAttCellTopComboBoxWidgetID:
			sides = Tables::eTopSide;
			break;

		case    kTblAttCellBottomComboBoxWidgetID:
			sides = Tables::eBottomSide;
			break;

		default:
			ASSERT_FAIL("Did not find widget ID expected");
			break;
		}

		if (sides != Tables::eNoSides)
		{
			fQueryMutHelper.SetCellStroke(sides, newStrokeWeight);
		}
	} while (kFalse);
}

/* tableStrokeWeightChanged
*/
void TblAttWidgetObserver::tableStrokeWeightChanged(InterfacePtr<IControlView>& widgetControlView)
{
	do
	{
		ASSERT(widgetControlView);
		if (widgetControlView==nil)
		{
			break;
		}

		InterfacePtr<ITextValue> textValue(widgetControlView, UseDefaultIID());
		ASSERT(textValue);
		if (textValue==nil)
		{
			break;
		}

		PMReal newStrokeWeight = textValue->GetTextAsValue();
		WidgetID widgetID = widgetControlView->GetWidgetID();

		ClassID classID;
		switch (widgetID.Get())
		{
		
		case    kTblAttTableLeftComboBoxWidgetID:
			classID = kTableAttrOuterLeftStrokeWeightBoss;
			break;

		case    kTblAttTableRightComboBoxWidgetID:
			classID = kTableAttrOuterRightStrokeWeightBoss;
			break;

		case    kTblAttTableTopComboBoxWidgetID:
			classID = kTableAttrOuterTopStrokeWeightBoss;
			break;

		case    kTblAttTableBottomComboBoxWidgetID:
			classID = kTableAttrOuterBottomStrokeWeightBoss;
			break;


		default:
			ASSERT_FAIL("Could not find widget ID for class ID");
			break;
		}

		if (classID.IsValid())
		{
			fQueryMutHelper.SetTableAttributeReal(classID, newStrokeWeight);
		}

	} while (kFalse);

}

/* rowStrokeWeightChanged
*/
void TblAttWidgetObserver::rowStrokeWeightChanged(InterfacePtr<IControlView>& widgetControlView)
{
	do
	{
		ASSERT(widgetControlView );
		if (widgetControlView==nil)
		{
			break;
		}

		InterfacePtr<ITextValue> textValue(widgetControlView, UseDefaultIID());
		ASSERT(textValue);
		if (textValue==nil)
		{
			break;
		}

		PMReal newStrokeWeight = textValue->GetTextAsValue();
		TRACE("TblAttWidgetObserver::rowStrokeWeightChanged() newStrokeWeight=%f\n", ::ToDouble(newStrokeWeight));

		// Note that this is a table attr and NOT a row attrib
		fQueryMutHelper.SetTableAttributeReal(kTableAttrRowStrokeWeightBoss, newStrokeWeight);

	} while (kFalse);
}

/* colStrokeWeightChanged
*/
void TblAttWidgetObserver::colStrokeWeightChanged(InterfacePtr<IControlView>& widgetControlView)
{
	do
	{
		ASSERT(widgetControlView );
		if (widgetControlView==nil)
		{
			break;
		}

		InterfacePtr<ITextValue> textValue(widgetControlView, UseDefaultIID());
		ASSERT(textValue);
		if (textValue==nil)
		{
			break;
		}

		PMReal newStrokeWeight = textValue->GetTextAsValue();
		TRACE("TblAttWidgetObserver::colStrokeWeightChanged() newStrokeWeight=%f\n", ::ToDouble(newStrokeWeight));
		// Note that this is a table attr and NOT a row attrib
		fQueryMutHelper.SetTableAttributeReal(kTableAttrColStrokeWeightBoss, newStrokeWeight);

	} while (kFalse);
}

// End, TblAttWidgetObserver.cpp.
