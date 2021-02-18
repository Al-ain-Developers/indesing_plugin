//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextWalkerSelectionUtils.h $
//  
//  Owner: HabibK
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
#ifndef __TextWalkerSelectionUtils__
#define __TextWalkerSelectionUtils__

#include "FindChangeID.h"

class ITextModel;
class ITextWalker;

/** 
	@ingroup text_util 
	@ingroup text_find
*/
class ITextWalkerSelectionUtils : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTWALKERSELECTIONUTILS };

		/** 
			Selects specified text range in model.

			@param textStory		Text model to select text from.
			@param nStart		Text index to start selection.
			@param nnCount		Length of the tex to select.
			
			@return bool16		kTrue if selection succeeded. 
		*/
		virtual bool16	SelectText( UIDRef &textStory, TextIndex nStart, int32 nnCount )	= 0;

		/** 
			Initializes the text walker terminator.
		*/
		virtual void 	InitTextWalkerTerminator()	= 0;

		/** 
			Releases the text walker terminator.
		*/
		virtual void 	TerminateTextWalkerTerminator() = 0;

		/** 
			Saves the selection snapshot.
		*/
		virtual void	SaveSelectionsSnapshot() = 0; //SpellPanelObserver::Update

		/** 
			Restores the selection snapshot.
		*/
		virtual void	RestoreSelectionsSnapshot() = 0; //SpellPanelObserver::Update

		/** 
			Clears the selection snapshot.
		*/
		virtual void	ClearSelectionsSnapshot() = 0; //TextWalkerTerminator::DoHalt, TextWalkerSelectionUtils::SwitchToTextSelection

		/** 
			Resets rescue window.

			Note RestoreSelectionsSnapshot has the opposite effect.
		*/
		virtual void	RetainLastWindow() = 0; 
		
		/** 
			Starts text walker selections critical section.
		*/
		virtual	void	EnterWalkerSelections_CriticalSection() = 0;

		/** 
			Ends text walker selections critical section.
		*/
		virtual	void	ExitWalkerSelections_CriticalSection	() = 0;

		/** 
			Switches selection snapshot to text selection.
		*/
		virtual void	SwitchToTextSelection() = 0; //FindChangeService::ProcessFindChangeCommand, FindPanelObserver::Update
		
};

/** 
	@ingroup text_find
*/
class TextWalkerSelections_CriticalSection
{
	public:
		TextWalkerSelections_CriticalSection(ITextWalkerSelectionUtils *pUtils):
		fUtils(nil)
		{
			if (pUtils)
			{
				fUtils = pUtils;
				pUtils->AddRef();
				pUtils->EnterWalkerSelections_CriticalSection();
			}
		}
	
		~TextWalkerSelections_CriticalSection()
		{
			if (fUtils)
			{
				fUtils->ExitWalkerSelections_CriticalSection();
				fUtils->Release();
			}
		}
	private:
		ITextWalkerSelectionUtils *fUtils;
};
#endif

