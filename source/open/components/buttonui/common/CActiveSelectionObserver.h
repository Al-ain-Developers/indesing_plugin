//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/common/CActiveSelectionObserver.h $
//  
//  Owner: Michael Burbidge
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

#pragma once
#ifndef __CActiveSelectionObserver_h__
#define __CActiveSelectionObserver_h__

#include "SelectionObserver.h"
#include "ITriStateControlData.h"

class IDocument;

//========================================================================================
// CLASS CActiveSelectionObserver
//========================================================================================

class CActiveSelectionObserver : public ActiveSelectionObserver
{
public:
	CActiveSelectionObserver(IPMUnknown *boss, const PMIID& observerIID = IID_IOBSERVER);
	virtual ~CActiveSelectionObserver();

protected:
	void		AttachToWidget(const WidgetID& widgetId,
							   const PMIID& interestedIn = IID_IUNKNOWN, const PMIID& asObserver = IID_IOBSERVER,
							   IPMUnknown* widget = nil);
	void		DetachFromWidget(const WidgetID& widgetId,
							     const PMIID& interestedIn = IID_IUNKNOWN, const PMIID& asObserver = IID_IOBSERVER,
							     IPMUnknown* widget = nil);
	void		AttachToDocument(IDocument* document, const PMIID& iid);
	void		DetachFromDocument(IDocument* document, const PMIID& iid);

	// ----- Getter and Setter Helper Methods -----
	
	virtual void				SetTextControlData(const WidgetID& widgetId, const PMString& text, IPMUnknown* widget = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	virtual PMString			GetTextControlData(const WidgetID& widgetId, IPMUnknown* widget = nil) const;
	
	virtual void							SetTristateControlData(const WidgetID& widgetId, const ITriStateControlData::TriState& text, IPMUnknown* widget = nil, bool16 invalidate = kTrue, bool16 notifyOfChange = kTrue);
	virtual ITriStateControlData::TriState	GetTristateControlData(const WidgetID& widgetId, IPMUnknown* widget = nil) const;

private:
	InterfacePtr<IDocument>		fDocument;
};

#endif // __CActiveSelectionObserver_h__
