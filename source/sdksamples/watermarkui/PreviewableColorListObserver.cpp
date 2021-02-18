//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/watermarkui/PreviewableColorListObserver.cpp $
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
#include "IPanelControlData.h"
#include "ISubject.h"
#include "IColorListControlData.h"

// General includes:
#include "CObserver.h"

// Project includes:
#include "WatermarkUIID.h"


/** Implements IObserver based on the partial implementation CObserver.
		
	Because our dialog has a Preview button, we need to know immediately when data changes for a widget.
	Normally, when an attached widget's value is changed, the dialog observer's Update() method is called,
	and then widget observers are updated.

	For dropdown menus, the call to the dialog observer's Update comes after a particular menu item is
	selected.  This works fine for all the color dropdown's menu items except for the 'custom' item.  
	When the 'custom' item is chosen, first the dialog observer's Update method gets called as normal, then
	the color dropdown widget observer's Update method gets called.  Inside the color dropdown observer's Update
	method, if the 'custom' items was selected, a system dialog is displayed to allow the user to 
	select their custom color.

	After this system dialog is dismissed, the color list data is updated, and the dropdown menu is
	redrawn using the selected color, but there is no message sent to the color dropdown's observers 
	indicating the custom color has been changed.  This leaves the previewed document out of sync 
	with the dialog.

	To deal with this issue, an additional observer was added to the color list dropdown.  This was
	implemented by aggregating both IControlViewObservers and PreviewableColorListObserver onto 
	kColorListDropDownWidgetBoss.  IControlViewObservers implements a list of observers, and 
	PreviewableColorListObserver implements the new observer.
	
	PreviewableColorListObserver responds to the same kPopupChangeStateMessage that the color dropdown 
	observer responds to, but because it gets updated AFTER the color dropdown observer is updated, we 
	can safely notify attached items (namely, our dialog) that the IID_ICOLORLISTCONTROLDATA has been modified.  
	Our dialog, then, can properly sync the document to the dialog when a custom color is chosen.

	@ingroup watermarkui
*/
class PreviewableColorListObserver : public CObserver
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		PreviewableColorListObserver(IPMUnknown* boss);

		/** Destructor. */
		virtual ~PreviewableColorListObserver() {}

		/**
			Called by the application to allow the observer to attach to the subjects
			to be observed, in this case the dialog's color widget.
		*/
		virtual void AutoAttach();

		/** Called by the application to allow the observer to detach from the subjects being observed. */
		virtual void AutoDetach();

		/**
			Called by the host when the observed object changes.
			@param theChange specifies the class ID of the change to the subject. Frequently this is a command ID.
			@param theSubject points to the ISubject interface for the subject that has changed.
			@param protocol specifies the ID of the changed interface on the subject boss.
			@param changedBy points to additional data about the change. Often this pointer indicates the class ID of the command that has caused the change.
		*/
		virtual void Update( const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy );

};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID making the 
 C++ code callable by the application.
*/
CREATE_PMINTERFACE(PreviewableColorListObserver, kPreviewableColorListObserverImpl)


/* PreviewableColorListObserver
*/
PreviewableColorListObserver::PreviewableColorListObserver(IPMUnknown* boss)
	: CObserver(boss, IID_IPREVIEWABLECOLORLISTOBSERVER)
{
}


/* AutoAttach
*/
void PreviewableColorListObserver::AutoAttach()
{
	CObserver::AutoAttach();

    InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject != nil){
        subject->AttachObserver(this, IID_IPANELCONTROLDATA, IID_IPREVIEWABLECOLORLISTOBSERVER);
	}
}

/* AutoDetach
*/
void PreviewableColorListObserver::AutoDetach()
{
    InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
    if (subject != nil)
        subject->DetachObserver(this, IID_IPANELCONTROLDATA, IID_IPREVIEWABLECOLORLISTOBSERVER);

	CObserver::AutoDetach();
}

/* Update
*/
void PreviewableColorListObserver::Update( const ClassID& theChange, ISubject* theSubject,
											 const PMIID& protocol, void* changedBy )
{
	if (protocol == IID_IPANELCONTROLDATA && (theChange == kPopupChangeStateMessage))
	{
		// Notify observers that IID_ICOLORLISTCONTROLDATA has (potentially) changed
		InterfacePtr<ISubject> pSubj(this, IID_ISUBJECT);
		if( pSubj ){
			pSubj->Change( kPopupChangeStateMessage, IID_ICOLORLISTCONTROLDATA );
		}
	}
}

