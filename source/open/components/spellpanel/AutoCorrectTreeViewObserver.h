//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectTreeViewObserver.h $
//  
//  Owner: Heath Horton
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
#ifndef _H_AutoCorrectTreeViewObserver
#define _H_AutoCorrectTreeViewObserver

#include "AutoCorrectPanelObserver.h"

#include "K2Vector.h"
#include "PMString.h"

class ISubject;

//----------------------------------------------------------------------------------------
// Class AutoCorrectTreeViewObserver
//----------------------------------------------------------------------------------------

class AutoCorrectTreeViewObserver : public AutoCorrectPanelObserver
{
public:
						AutoCorrectTreeViewObserver(IPMUnknown *boss);

		virtual	void	Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

		virtual	bool16	SetupWidget();
		
		virtual	bool16	AddEntry();
		virtual	bool16	RemoveEntry();
		
		virtual bool16	GetAutoCorrectList(K2Vector<PMString>& misspelledItems);
};

#endif //_H_AutoCorrectTreeViewObserver