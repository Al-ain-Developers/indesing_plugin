//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ILinesToRedrawData.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __ILinesToRedrawData__
#define __ILinesToRedrawData__

#include "IPMUnknown.h"
#include "IGraphicsContext.h"
#include "IWaxStrand.h"

#include "WritingModeUIID.h"
#include "PMRect.h"
#include "PMString.h"

/** 
	Third parties shouldn't need to use. Only SetShouldErase/ShouldErase does anything currently
*/
class ILinesToRedrawData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ILINESTOREDRAWDATA };
	
		/** 
			Called internally to flag a condition when we are asked to draw but text is not ready to draw so that a draw
			will occur later. Probably not interesting to third parties.
			@param set kTrue to redraw later.
			return none
		*/
		virtual void SetShouldErase(bool16 erase) = 0;
		
		/** 
			Retrieve whether flag set with SetShouldErase
			return kTrue to redraw
		*/
		virtual bool16 ShouldErase() = 0;
		
#ifdef ID_DEPRECATED
		virtual void SetEraseCaret(bool16 eraseCaret) = 0;
		virtual bool16 ShouldEraseCaret() = 0;

		// Not used
		virtual void DrawOk(bool8 drawOK) = 0;
		virtual bool8 IsDrawOk() = 0;
		
		// Not used
		virtual void SetRangeToRedraw(int32 first, int32 last) = 0;
		virtual int32 GetFirstLineToRedraw() = 0;
		virtual int32 GetLastLineToRedraw() = 0;
		
		// Not used
		virtual void SetDrawStartTextOffset(TextIndex textOffset) = 0;
		virtual TextIndex GetDrawStartTextOffset() = 0;

		// Not used
		virtual void SetDrawingFromInval(bool16 invalRedraw) = 0;
		virtual bool16 GetDrawingFromInval() = 0;

		// Not used
		virtual void SetForceRedrawRect(PMRect rect) = 0;
		virtual PMRect GetForceRedrawRect() = 0;
		
		// Not used
		virtual void SetToNone() = 0;
		virtual bool8 IsNone() = 0;
		virtual void ClearTypingInval() = 0;
		virtual void SetIsTypingInval(bool8 typing) = 0;
		virtual bool8 IsTypingInval() = 0;
		virtual PMRect GetRedrawRect(IGraphicsContext* gc, int32 flags, IWaxStrand *waxStrand) = 0;
		virtual bool8 DrawThisLine(int32 lineNumber) = 0;
		virtual bool8 RedrawEveryThing() = 0;
		virtual void SetRedrawEveryThing(bool8 redraw = kTrue) = 0;
		virtual void SetNumberOfLines(int32 lines) = 0;
		virtual int32 GetNumberOfLines() = 0;
#endif
};

#endif 		// __ILinesToRedrawData__