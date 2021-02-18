//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IRulerCaret.h $
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
#ifndef __IRULERCARET__
#define __IRULERCARET__

//========================================================================================
// Forward declarations
//========================================================================================
#include "RulerID.h"

class IControlView;
class IViewPort;

#if ID_NO_DIRECT_DRAWING_ALLOWED
#include "DVAForwardDeclarations.h"
#endif

//========================================================================================
// CLASS IRulerCaret
//========================================================================================

class IRulerCaret : public IPMUnknown
{
// ----- Constructors/destructors
public:
		enum { kDefaultIID = IID_IRULERCARET };

	virtual void InitRulerCaret(IControlView* constrainingView) = 0;
	inline void ShowRulerCaret() { ShowRulerCaret___( true);}
	inline void HideRulerCaret() { HideRulerCaret___( true);}
	virtual void MoveRulerCaretTo(const SysPoint& position) = 0;
	virtual void MoveRulerCaretTo(const SysPoint& position1, const SysPoint& position2) = 0;
	virtual bool16 RulerCaretShowing() = 0;

protected:
	friend class CAbstractRulerView; //for now--these members are going away
	virtual void ShowRulerCaret___(bool doInval /* = true*/) = 0;
	virtual void HideRulerCaret___(bool doInval /* = true*/) = 0;
	virtual void DrawRulerCaret___(dvaui::drawbot::Drawbot* drawbotP) =0;

};

#endif


