//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/InLineEditEditingAttributes.h $
//  
//  Owner: jshankar 
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
//  
//  Owner
//  
//========================================================================================

#pragma once
#ifndef __InLineEditEditingAttributes__
#define __InLineEditEditingAttributes__

// ----- Interface Includes -----
#include "IInLineEditEditingAttributes.h"

// ----- Implementation Includes -----

class WIDGET_DECL InLineEditEditingAttributes : public IInLineEditEditingAttributes
{
public:	
	InLineEditEditingAttributes(IPMUnknown *boss);
	~InLineEditEditingAttributes();

	virtual void ReadWrite(IPMStream* s, ImplementationID prop);

	virtual InLineEditWidgetType GetEditWidgetType() const;

	virtual void		SetIsEditable(bool16 isEditable);
	virtual bool16 		IsEditable() const { return fIsEditable; }

	virtual void		SetTakeKeyboardFocus(bool16 keyFocus) ;
	virtual bool16 		GetTakeKeyboardFocus() const { return fCanTakeFocus; }

	virtual bool16 		IsSelected() const;

	virtual void		SetFitEditBoxtoText(bool16 fitText);
	virtual bool16 		GetFitEditBoxtoText() const;

private:
	bool16 fIsEditable;
	bool16 fCanTakeFocus;
	bool16 fFitEditBoxtoText;
	InLineEditWidgetType	fEditWidgetType;

DECLARE_HELPER_METHODS()
};

#endif