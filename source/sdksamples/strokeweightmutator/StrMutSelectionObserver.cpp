//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/strokeweightmutator/StrMutSelectionObserver.cpp $
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

// Interface include:
#include "IControlView.h"
#include "ITextValue.h"
#include "IPanelControlData.h"
#include "IStrokeAttributeSuite.h"
#include "IGraphicAttrRealNumber.h"
#include "ISelectionManager.h"
#include "IPersistUIDData.h"
#include "ISubject.h"
#include "IGraphicAttrMessage.h"
#include "ISelectionManager.h"
#include "ITextControlData.h"

// General includes:
#include "SelectionObserver.h" // for ActiveSelectionObserver
#include "UIDList.h"
#include "PMString.h"
#include "K2Assert.h"
#include "Trace.h"
#include "DebugClassUtils.h"

// Project includes:
#include "StrMutID.h"
#include "StrMutDiagnosticHelper.h"

/** Implements an observer, IObserver based
	on ActiveSelectionObserver, that updates
	the stroke weight displayed in the panel's
	widget when the stroke weight of the selected
	objects change, and updates the stroke 
	weight of the selected objects when the
	user changes the value of the panel's stroke
	weight widget.

	The panel's stroke weight widget is maintained 
	in a way that mimics the value displayed in the 
	Stroke Weight panel.
	
	The implementation shows how to specialise
	ActiveSelectionObserver so that widgets can be
	observed in addition to the selection within
	within a single observer implementation.
	
	IStrokeAttributeSuite is used to get and change
	the stroke weight which is maintained by a 
	widget on the panel. IGraphicAttributeSuite is
	used to determine if the stroke is being actively
	drawn or not.

	
	@ingroup strokeweightmutator
	@see IStrokeAttributeSuite
	@see IGraphicAttributeSuite
*/
class StrMutSelectionObserver : public ActiveSelectionObserver
{
	public:
		/**	Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		StrMutSelectionObserver(IPMUnknown *boss);

		/** Destructor.
		*/
		virtual ~StrMutSelectionObserver();

	//________________________________________________________________________________________
	// The methods below allow specialise ActiveSelectionObserver to observe changes 
	// to the panel's widget as well as the selection.
	public:
		/** Attaches observer to the panel's widget and calls parent class
			to attach to the active selection.
		*/
		virtual void AutoAttach();

		/** Detaches observer from the panel's widget and calls parent class
			to detach from the active selection.
		*/
		virtual void AutoDetach();

	protected:
		/**	Called when the observed subjects change, in this case when
			the panel's widget is changed or when the active selection changes.
			Events resulting from widget clicks are handled here, 
			selection events are passed to the parent class.
			@param theChange specifies the class ID of the change to the subject. Frequently this is a command ID.
			@param theSubject points to the ISubject interface for the subject that has changed.
			@param protocol specifies the ID of the changed interface on the subject boss.
			@param changedBy points to additional data about the change. Often this pointer indicates the class ID of the command that has caused the change.
		*/
		virtual void HandleSelectionUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

	private:
		/**	Attach this observer to the given widget.
			@param panelControlData IN specifies the panel that owns the widget.
			@param widgetID IN specifies the widget to be observed.
		*/
		void AttachWidget(IPanelControlData* panelControlData, const WidgetID& widgetID, const PMIID& interfaceID);

		/**	Detach this observer from the given widget.
			@param panelControlData IN specifies the panel that owns the widget.
			@param widgetID IN specifies the widget to stop observing.
		*/
		void DetachWidget(IPanelControlData* panelControlData, const WidgetID& widgetID, const PMIID& interfaceID);

		/**	Called when the stroke weight widget value is changed by the user.
			IStrokeAttributeSuite is used to change the
			stroke weight of the selected objects.
			@param widgetControlView IN control view of widget that changed.
		*/
		void StrokeWeightWidgetValueChanged(IControlView* widgetControlView);

	//________________________________________________________________________________________
	// Methods called when the selection changes to update the stroke
	// weight displayed by the panel's widget.
	protected:
		/**	Called when there is a new active selection or when objects are
			added or removed from the selection.
			@param selectionMessage IN message from the selection about the change,
				if the pointer is nil then widgets must be updated to synchronise
				with the new selection, otherwise the client can examine the message
				to see if the change that has taken place requires them to update.
		*/
		virtual void	HandleSelectionChanged(const ISelectionMessage* selectionMessage);

		/**	Called when a property of the selection changes, stroke weight or color for example.
			Note: It is important that client code examine the message parameter
			and only update when data that the client needs has changed. The client
			can be called when data that it is not interested in changes and it is
			important for performance reasons that these calls are filtered so that 
			unnecessary updates don't take place.
			@param selectionMessage client code must examine the message and only
				update when a message is received from the suite that manages the
				properties that are being displayed.
		*/
		virtual void HandleSelectionAttributeChanged(const ISelectionMessage* selectionMessage);

	private:
		/** Examine the message from selection to see if the stroke weight
			widget state needs to be synchronised with the selection's
			stroke weight. The implementation assumes stroke is affected and 
			only returns kFalse if the message explicitly says stroke is
			not affected.
			@param selectionMessage to be examined.
			@return kTrue (default) if stroke weight widget is affected by the given message
				and should be updated, kFalse otherwise.
		 */
		bool16 IsStrokeWeightWidgetAffected(const ISelectionMessage* selectionMessage);

		/**	Update the panel's stroke weight widget to display the 
			stroke weight of the selection.
		*/
		virtual void HandleStrokeWeightSelectionAttributeChanged();

		/**	Return kTrue if any selected object is stroked (i.e. the stroke
			is being visibly drawn), kFalse if all selected objects are not stroked.
			@return kTrue if any selected object is stroked (i.e. the stroke
			is being visibly drawn), kFalse if all selected objects are not stroked.
		 */
		bool16 HasRenderedStroke();

	//________________________________________________________________________________________
	// Widget management methods.
	private:
		/** Set the value displayed in the stroke weight widget.
			@param value IN
		*/
		virtual void SetStrokeWeightWidgetValue(const PMReal& value);

		/** Clear the value displayed in the stroke weight widget.
		*/
		virtual void ClearStrokeWeightWidgetValue();

		/** Enable or disable the stroke weight widget.
			@param enable IN kTrue to enable, kFalse to disable.
		*/
		virtual void EnableStrokeWeightWidget(bool16 enable);

		/** Set the given widget's value.
			@param widgetID IN specifies the widget.
			@param value IN give the value to display.
		*/
		virtual void SetWidgetValue(const WidgetID& widgetID, const PMReal& value);

		/** Clear the given widget.
			@param widgetID IN specifies the widget.
		*/
		virtual void ClearWidgetValue(const WidgetID& widgetID);

		/** Enable or disable the given widget.
			@param widgetID IN specifies the widget.
			@param enable IN kTrue to enable, kFalse to disable.
		*/
		virtual void EnableWidget(const WidgetID& widgetID, bool16 enable);

};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(StrMutSelectionObserver, kStrMutSelectionObserverImpl)

/* Constructor.
*/
StrMutSelectionObserver::StrMutSelectionObserver(IPMUnknown *boss) :
	ActiveSelectionObserver(boss)
{
}

/* Destructor.
*/
StrMutSelectionObserver::~StrMutSelectionObserver()
{
}

/*
*/
void StrMutSelectionObserver::HandleSelectionChanged(const ISelectionMessage* selectionMessage)
{
	TRACEFLOW(kStrMutPluginName, "StrMutSelectionObserver::HandleSelectionChanged()-->In\n");

	// Trace the message from selection.
	StrMutDiagnosticHelper diagnosticHelper;
	diagnosticHelper.DumpSelectionMessage(selectionMessage);

	InterfacePtr<IStrokeAttributeSuite> strokeAttributeSuite(fCurrentSelection, UseDefaultIID());
	if (selectionMessage == nil || strokeAttributeSuite == nil)
	{
		// If the selection tells everything to update or,
		// if IStrokeAttributeSuite is not supported we
		// need to update the widget with the state of
		// the selection.
		this->HandleStrokeWeightSelectionAttributeChanged();
	}
	else
	{
		// Only update if the selection message affects the stroke.
		if (this->IsStrokeWeightWidgetAffected(selectionMessage))
		{
			this->HandleStrokeWeightSelectionAttributeChanged();
		}
	}

	TRACEFLOW(kStrMutPluginName, "StrMutSelectionObserver::HandleSelectionChanged()-->Out\n");
}

/*
*/
void StrMutSelectionObserver::HandleSelectionAttributeChanged
(
	const ISelectionMessage* selectionMessage
)
{
	TRACEFLOW(kStrMutPluginName, "StrMutSelectionObserver::HandleSelectionAttributeChanged()-->In\n");

	// Trace the message from selection.
	StrMutDiagnosticHelper diagnosticHelper;
	diagnosticHelper.DumpSelectionMessage(selectionMessage);

	// Act on the message from selection.
	if (this->IsStrokeWeightWidgetAffected(selectionMessage))
	{
		this->HandleStrokeWeightSelectionAttributeChanged();
	}

	TRACEFLOW(kStrMutPluginName, "StrMutSelectionObserver::HandleSelectionAttributeChanged()-->Out\n");
}

/*
*/
bool16 StrMutSelectionObserver::IsStrokeWeightWidgetAffected(const ISelectionMessage* selectionMessage)
{
	// The widget should always be updated unless the selection message indicates
	// the update is not necessary.
	bool16 result = kTrue;
	do 
	{
		if (selectionMessage == nil)
		{
			// Everything associated with the selection should update.
			result = kTrue;
			break;
		}
		InterfacePtr<IStrokeAttributeSuite> strokeAttributeSuite(fCurrentSelection, UseDefaultIID());
		if (strokeAttributeSuite == nil)
		{
			// Update if IStrokeAttributeSuite is not available for the current selection.
			result = kTrue;
			break;
		}

		// Check if there a message from selection that might be of interest?
		if(selectionMessage->WasSuiteAffected(IGraphicAttributeSuite::kDefaultIID) == kFalse) 
		{
			// The message is not from IGraphicAttributeSuite, don't update.
			result = kFalse;
			break;
		}

		// Examine the message from IGraphicAttributeSuite.
		IGraphicAttrMessage* graphicAttrMessage = static_cast<IGraphicAttrMessage*>
					(selectionMessage->GetSuiteBroadcastData(IGraphicAttributeSuite::kDefaultIID));
		if (graphicAttrMessage == nil) 
		{
			// Update if IGraphicAttributeSuite doesn't post any message data.
			result = kTrue;
			break;
		}

		// Examine the message to see if stroke weight is affected.
		IGraphicAttrMessage::MessageType messageType = graphicAttrMessage->GetMessageType();
		switch (messageType)
		{
		case IGraphicAttrMessage::kMsg_DefinitionChanged:
			{
				// Assume the stoke is not affected by the message.
				bool16 isStrokeAffected = kFalse;
				int32 classIDCount = graphicAttrMessage->GetClassIDCount();
				if (classIDCount == 0)
				{
					// When no ClassID's are posted assume stroke is affected.
					isStrokeAffected = kTrue;
				}
				else
				{
					// Examine the ClassID's in the message to see if
					// the stroke is affected.
					for (int32 i = 0; i < classIDCount; i++)
					{
						ClassID classID = graphicAttrMessage->GetClassID(i);
						if (classID == kGraphicStyleStrokeWeightAttrBoss ||
							classID == kGraphicStyleStrokeRenderingAttrBoss)
						{
							// Stroke is affected.
							isStrokeAffected = kTrue;
							break;
						}
					}
				}
				result = isStrokeAffected;
			}
			break;
		case IGraphicAttrMessage::kSwapStrokeAndFillMsg:
			// Don't update.
			result = kFalse;
			break;
		default:
			// Unless selection tells us not too we always update.
			result = kTrue;
			break;
		}

	} while(false);
	return result;
}

/* 
*/
void StrMutSelectionObserver::HandleStrokeWeightSelectionAttributeChanged()
{
	do 
	{
		// Use IStrokeAttributeSuite to manage the stroke weight.
		InterfacePtr<IStrokeAttributeSuite> strokeAttributeSuite(fCurrentSelection, UseDefaultIID());
		if (strokeAttributeSuite == nil) 
		{
			this->EnableStrokeWeightWidget(kFalse);
			break;
		}

		// Disable the stroke weight widget if the suite indicates
		// stroke weight is not available.
		bool16  isStrokeWeightEnabled = strokeAttributeSuite->IsStrokeWeightEnabled();
		TRACEFLOW(kStrMutPluginName, " isStrokeWeightEnabled=%d\n", isStrokeWeightEnabled);
		if (isStrokeWeightEnabled == kFalse)
		{
			this->EnableStrokeWeightWidget(kFalse);
			break;
		}

#ifdef DEBUG
		// Diagnostic code to trace the visible stroke weight.
		int32 visibleStrokeWeightCount = strokeAttributeSuite->GetVisibleStrokeWeightCount();
		TRACEFLOW(kStrMutPluginName, " i, visibleStrokeWeight (visibleStrokeWeightCount=%d)\n",
			visibleStrokeWeightCount);
		for (int32 i = 0; i < visibleStrokeWeightCount; i++)
		{
			PMReal  visibleStrokeWeight = strokeAttributeSuite->GetVisibleStrokeWeight(i);
			TRACEFLOW(kStrMutPluginName, " %d, %f\n",
				i,
				::ToDouble(visibleStrokeWeight));
		}
#endif //DEBUG

		int32 strokeWeightCount = strokeAttributeSuite->GetStrokeWeightCount();

#ifdef DEBUG
		// Diagnostic code to trace the stroke weight.
		TRACEFLOW(kStrMutPluginName, " j, strokeWeight (strokeWeightCount=%d)\n",
			strokeWeightCount);
		for (int32 j = 0; j < strokeWeightCount; j++)
		{
			PMReal  strokeWeight = strokeAttributeSuite->GetStrokeWeight(j);
			TRACEFLOW(kStrMutPluginName, " %d, %f\n",
				j,
				::ToDouble(strokeWeight));
		}

		// Diagnostic code to trace if the stroke is being drawn or not.
		bool16 hasStroke = this->HasRenderedStroke();
		TRACEFLOW(kStrMutPluginName, "hasStroke=%d\n", hasStroke);
#endif

		// Update the value of the stroke weight widget displayed
		// in the panel. Note that stroke weight is used in
		// preference to the visible stroke weight. This is because
		// stroked text and table cells don't get reported as having
		// visible stroke by IStrokeAttributeSuite. So stroke weight
		// is used and an extra check is made to see if the stroke
		// is actually being drawn or not (see StrMutSelectionObserver::HasRenderedStroke).

		if (this->HasRenderedStroke() == kFalse)
		{
			// Clear the widget if any selected object is not stroked.
			this->ClearStrokeWeightWidgetValue();
		}
		else if (strokeWeightCount > 1)
		{
			// Clear the widget if the selected objects have different
			// stroke weight values.
			this->ClearStrokeWeightWidgetValue();
		}
		else if (strokeWeightCount == 1)
		{
			// Display the stroke weight value in the widget when
			// all selected objects have the same stroke weight.
			PMReal  strokeWeight = strokeAttributeSuite->GetStrokeWeight(0);
			this->SetStrokeWeightWidgetValue(strokeWeight);
		}
		else
		{
			// Otherwise, display zero in the widget.
			this->SetStrokeWeightWidgetValue(0.0);
		}

		// Enable the stroke weight widget so that the user
		// can change the stroke weight of selected objects.
		this->EnableStrokeWeightWidget(kTrue);

	} while (false);
}

/*
*/
bool16 StrMutSelectionObserver::HasRenderedStroke()
{
	// Assume all selected objects are not stroked.
	bool16 result = kFalse;
	do
	{
		// IGraphicAttributeSuite is used to get the
		// boss class being used to draw the stroke.
		// It's ClassID indicates whether or not the stroke
		// will get drawn.
		InterfacePtr<IGraphicAttributeSuite> graphicAttributeSuite(fCurrentSelection, UseDefaultIID());
		if (!graphicAttributeSuite)
		{
			break;
		}
		ClassID strokeClass = graphicAttributeSuite->GetStrokeClass();	
		switch (strokeClass.Get())
		{
		case kGraphicStateNoneRenderingObjectBoss:
			{
				// Indicates that the stoke is not drawn.
				result = kFalse;
				break;
			}
		case kMultipleRenderingObjectsBoss:
			{
				// Indicates that more than one object is involved and
				// we need to examine each one individually to see if
				// its stroke is drawn. Get hold of the interfaces
				// needed to make this check.
				InterfacePtr<ISelectionManager> selectionManager (graphicAttributeSuite, UseDefaultIID ());
				ASSERT(selectionManager);
				if (!selectionManager)
				{
					break;
				}
				IDataBase* dataBase = selectionManager->GetDataBase();
				ASSERT(dataBase);
				if (!dataBase)
				{
					break;
				}
				// The boss class being used to draw the stroke is referred to by
				// attribute kGraphicStyleStrokeRenderingAttrBoss. Examine each
				// in turn for one that is stroked, and stop if we find one, because
				// it means that at least one object in the selection has its
				// stroke being drawn.
				int32 attributeCount = graphicAttributeSuite->GetAttributeCount(kGraphicStyleStrokeRenderingAttrBoss);
				for (int32 n = 0; n < attributeCount; n++ )
				{
					InterfacePtr<const IPersistUIDData> persistUIDData(static_cast<const IPersistUIDData*> (graphicAttributeSuite->QueryAttribute (n, 
																kGraphicStyleStrokeRenderingAttrBoss,
																IPersistUIDData::kDefaultIID)));
					ClassID strokeRenderingClassID = dataBase->GetClass(persistUIDData->GetUID());
					if (strokeRenderingClassID != kGraphicStateNoneRenderingObjectBoss)
					{	
						// At least one selected object is stroked.
						result = kTrue;
						break;
					}
				}
				break;
			}
		default:
			{
				// Stroke class indicates a type that will draw the stroke.
				// At least one selected object is stroked.
				result = kTrue;
				break;
			}
		}	
	} while(false);
	return result;
}

/*
*/
void StrMutSelectionObserver::SetStrokeWeightWidgetValue(const PMReal& newValue)
{
	this->SetWidgetValue(kStrMutStrokeWeightWidgetID, newValue);
}

/*
*/
void StrMutSelectionObserver::ClearStrokeWeightWidgetValue()
{
	this->ClearWidgetValue(kStrMutStrokeWeightWidgetID);
}

/*
*/
void StrMutSelectionObserver::EnableStrokeWeightWidget(bool16 enable)
{
	this->EnableWidget(kStrMutStrokeWeightWidgetID, enable);
}

/*
*/
void StrMutSelectionObserver::SetWidgetValue(const WidgetID& widgetID, const PMReal& newValue)
{
	do
	{
		InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
		ASSERT(panelData);
		if (!panelData)
		{
			break;
		}
		IControlView* controlView = panelData->FindWidget(widgetID);
		ASSERT(controlView);
		if (!controlView)
		{
			break;
		}
		InterfacePtr<ITextValue> textValue(controlView, UseDefaultIID());
		ASSERT(textValue);
		if (!textValue)
		{
			break;
		}
		textValue->SetTextFromValue(newValue, kTrue, kFalse);
	} while(false);
}

/*
*/
void  StrMutSelectionObserver::ClearWidgetValue(const WidgetID& widgetID)
{
	do
	{
		InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
		ASSERT(panelData);
		if (!panelData)
		{
			break;
		}
		IControlView* controlView = panelData->FindWidget(widgetID);
		ASSERT(controlView);
		if (!controlView)
		{
			break;
		}
		InterfacePtr<ITextValue> textValue(controlView, UseDefaultIID());
		ASSERT(textValue);
		if (!textValue)
		{
			break;
		}
		textValue->SetControlState(ITextValue::kUnknown, kTrue/*invalidate*/, kFalse/*don't notify*/);
	} while(false);
}

/*
*/
void  StrMutSelectionObserver::EnableWidget(const WidgetID& widgetID, bool16 enable)
{
	do
	{
		InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
		ASSERT(panelData);
		if (!panelData)
		{
			break;
		}
		IControlView* controlView = panelData->FindWidget(widgetID);
		ASSERT(controlView);
		if (!controlView)
		{
			break;
		}
		controlView->Enable(enable);
	} while(false);
}

/* 
*/
void StrMutSelectionObserver::AutoAttach()
{
	// Call parent class so we attach the active selection.
	ActiveSelectionObserver::AutoAttach();

	// Synchronise the state of the stroke weight widget with the state of selection.
	this->HandleStrokeWeightSelectionAttributeChanged();

	// Observe the user changing the stroke weight widget value in the panel.
	InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
	ASSERT(panelControlData);
	if (panelControlData)
	{
		this->AttachWidget(panelControlData, kStrMutStrokeWeightWidgetID, ITextControlData::kDefaultIID);

	}
}

/*
*/
void StrMutSelectionObserver::AutoDetach()
{
	// Stop observing the stroke weight widget.
	InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());
	ASSERT(panelControlData);
	if (panelControlData)
	{
		this->DetachWidget(panelControlData, kStrMutStrokeWeightWidgetID, ITextControlData::kDefaultIID);
	}

	// Call the parent class to detach from the active selection.
	ActiveSelectionObserver::AutoDetach();
}

/*
*/
void StrMutSelectionObserver::HandleSelectionUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy )
{
	TRACEFLOW(kStrMutPluginName, "StrMutSelectionObserver::HandleSelectionUpdate()-->In\n");

	// Trace the update message.
	StrMutDiagnosticHelper diagnosticHelper;
	diagnosticHelper.DumpUpdate(theChange, theSubject, protocol, changedBy);

	// Call the parent class to handle updates from the active selection.
	ActiveSelectionObserver::HandleSelectionUpdate(theChange, theSubject, protocol, changedBy);

	// Handle updates from the stroke weight widget on the panel.
	if (theChange == kTextChangeStateMessage)
	{
		InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
		if (controlView) 
		{
			WidgetID widgetID = controlView->GetWidgetID();
			switch (widgetID.Get())
			{
				case kStrMutStrokeWeightWidgetID:
					this->StrokeWeightWidgetValueChanged(controlView);
					break;
				default:
					ASSERT_FAIL(FORMAT_ARGS("Unknown WidgetID 0x%x", widgetID.Get()));
					break;
			}
		}
	}

	TRACEFLOW(kStrMutPluginName, "StrMutSelectionObserver::HandleSelectionUpdate()-->Out\n");
}

/*
*/
void StrMutSelectionObserver::AttachWidget(IPanelControlData* panelControlData, const WidgetID& widgetID, const PMIID& interfaceID)
{
	do
	{
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
	while (false);
}

/*
*/
void StrMutSelectionObserver::DetachWidget(IPanelControlData* panelControlData, const WidgetID& widgetID, const PMIID& interfaceID)
{
	do
	{
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
	while (false);
}

/*
*/
void StrMutSelectionObserver::StrokeWeightWidgetValueChanged(IControlView* widgetControlView)
{
	TRACEFLOW(kStrMutPluginName, "StrMutSelectionObserver::StrokeWeightWidgetValueChanged()-->In\n");
	do {
		InterfacePtr<IStrokeAttributeSuite> strokeAttributeSuite(fCurrentSelection, UseDefaultIID());
		if (!strokeAttributeSuite) {
			break;
		}
		InterfacePtr<ITextValue> textValue(widgetControlView, UseDefaultIID());
		ASSERT(textValue);
		if (!textValue)
		{
			break;
		}
		PMReal newStrokeWeight = textValue->GetTextAsValue();
		strokeAttributeSuite->ApplyStrokeWeight(newStrokeWeight);
	} while(false);
	TRACEFLOW(kStrMutPluginName, "StrMutSelectionObserver::StrokeWeightWidgetValueChanged()-->Out\n");
}

// End, StrMutSelectionObserver.cpp.

