//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CTextCommandPreProcess.h $
//  
//  Owner: Robin Briggs
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
#ifndef __CTextCommandPreProcess__
#define __CTextCommandPreProcess__

#include "ITextCommandPreProcess.h"
#include "CPMUnknown.h"

class PUBLIC_DECL CTextCommandPreProcess : public CPMUnknown<ITextCommandPreProcess>
{
	public:		
		CTextCommandPreProcess(IPMUnknown * boss);

		virtual bool16 DeletePreProcess(ITextModel* model, TextIndex& position, int32& length);
		virtual bool16 ApplyStylePreProcess(ITextModel* model, TextIndex& position, int32& length, UID& styleRef, ClassID& whichStrand);

		virtual WideString* InsertPreProcess(ITextModel* model, TextIndex& position, const WideString* data, const ILanguage *language = nil );

		virtual WideString* ReplacePreProcess(ITextModel* model, TextIndex& position, int32& length, const WideString* data, const ILanguage *language = nil);

		virtual AttributeBossList* ApplyOverridesPreProcess(ITextModel* model, TextIndex& position, int32& length, const AttributeBossList *attributes, ClassID& whichStrand);
		virtual AttributeBossList* ClearOverridesPreProcess(ITextModel* model, TextIndex& position, int32& length, const AttributeBossList *attributes, ClassID& whichStrand);

		virtual PasteData* PastePreProcess(ITextModel* model, TextIndex& position, const PasteData *data, int32 subrange);

		virtual void GetSubRangePreProcess(ITextModel* model, TextIndex& start, int32& length, const Text::StoryRangeList& contextList, int32 contextListIndex);

		virtual void	BeginProcessCommand( ICommand *cmd );
		virtual void	EndProcessCommand( ICommand *cmd );
};



#endif // __CTextCommandPreProcess__
