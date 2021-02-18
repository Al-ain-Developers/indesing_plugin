//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFrameListComposer.h $
//  
//  Owner: Zak_Williamson
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
#ifndef __IFrameListComposer__
#define __IFrameListComposer__

#include "IPMUnknown.h"
#include "TextID.h"

class IdleTimer;
class IMultiColumnTextFrame;

/** This interface controls recomposition either by frame or up to a given TextIndex.
	@ingroup text_comp
*/
class IFrameListComposer : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IFRAMELISTCOMPOSER };

		/**
		Recompose all TextFrameColumns in the IFrameList.
		*/
		virtual void	RecomposeThruLastFrame() = 0;

		/**
		Recompose all frames up thru the one containing the specified TextIndex.
		@param composeUpThruThisIndex TextIndex to compose upto, pass kInvalidTextIndex to compose all text in the FrameList.
		*/
		virtual void	RecomposeThruTextIndex(TextIndex composeUpThruThisIndex) = 0;

		/**
		Recompose all frames up thru the one containing this text index
		or the specified MultiColumnTextFrame, whichever comes first.
		@param composeUpThruThisIndex
		@param sentinalMCFrame Optional pointer to MultiColumnTextFrame
		*/
		virtual void	RecomposeThru(TextIndex composeUpThruThisIndex,
									const IMultiColumnTextFrame* sentinalMCFrame = nil) = 0;

		/**
		Recomposes the first damaged frame in the frame list.
		For use by background recomposition.
		@param interruptCheck Pointer to optional IdleTimer
		@return kTrue if composition finished within the time given by the IdleTimer, kFalse if the frame remains damaged
		*/
		virtual bool16	RecomposeOneFrame(IdleTimer* interruptCheck) = 0;

		/**
		Recomposes damaged frames until index is composed or frame is composed
		or timeCheck returns 0, whichever comes first.
		@param index TextIndex to compose upto, pass kInvalidTextIndex to compose all text in the FrameList.
		@param mcFrame Pointer to MultiColumnTextFrame to compose thru, pass nil to compose all frames in the FrameList.
		@param timeCheck Pointer to optional IdleTimer
		@return kTrue if composition finished within the time given by the IdleTimer, kFalse if the target frame remains damaged.
		*/
		virtual bool16	RecomposeUntil(TextIndex index,
										const IMultiColumnTextFrame* mcFrame,
										IdleTimer *timeCheck) = 0;

		/**
		This method will compose all damaged frames in the FrameList and, if one
		or more frames WERE damaged and result in overset, and the addition of
		additional frames is supported and appropriate for this FrameList,
		additional frames will be added until the FrameList is no longer
		overset or it is determined that adding frames is not helping.
		*/
		virtual void	RecomposeFully() = 0;

};

#endif
