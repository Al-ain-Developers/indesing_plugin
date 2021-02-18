//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextCommandPreProcess.h $
//  
//  Owner: ekenning
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
#ifndef __ITextCommandPreProcess__
#define __ITextCommandPreProcess__

#include "IPMUnknown.h"
#include "TextID.h"
#include "PMTextUtils.h"

class ITextModel;
class WideString;
class AttributeBossList;
class PasteData;
class ILanguage;
class ICommand;

/** 
	@ingroup text_service
*/
class ITextCommandPreProcess : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTEDITPREPROCESS };
		
			// allows service to preprocess text commands -- return kTrue if you modified anything
		virtual bool16 DeletePreProcess(ITextModel* model, TextIndex& position, int32& length) = 0;
		virtual bool16 ApplyStylePreProcess(ITextModel* model, TextIndex& position, int32& length, UID& styleRef, ClassID& whichStrand) = 0;

			// return nil if you didn't change anything. return a new pointer if you want to apply other attributes.
			// return the same pointer if you changed something besides the data pointed to
		virtual WideString* InsertPreProcess(ITextModel* model, TextIndex& position, const WideString* data, const ILanguage *language = nil ) = 0;

		virtual WideString* ReplacePreProcess(ITextModel* model, TextIndex& position, int32& length, const WideString* data, const ILanguage *language = nil) = 0;

		virtual AttributeBossList* ApplyOverridesPreProcess(ITextModel* model, TextIndex& position, int32& length, const AttributeBossList *attributes, ClassID& whichStrand) = 0;
		virtual AttributeBossList* ClearOverridesPreProcess(ITextModel* model, TextIndex& position, int32& length, const AttributeBossList *attributes, ClassID& whichStrand) = 0;

		virtual PasteData* PastePreProcess(ITextModel* model, TextIndex& position, const PasteData *data, int32 subrange) = 0;
		virtual void GetSubRangePreProcess(ITextModel* model, TextIndex& start, int32& length, const Text::StoryRangeList& contextList, int32 contextListIndex) = 0;

			// Begin/EndProcessCommand are called by UserApplyAttrCmd and UserTypeTextCmd to temporarily enable CJKTextPreProcessor and ScriptTextProcessor.
		virtual void	BeginProcessCommand( ICommand *cmd ) = 0;
		virtual void	EndProcessCommand( ICommand *cmd ) = 0;
};


#endif
		// __ITextCommandPreProcess__
