//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CTextCommandPostProcess.h $
//  
//  Owner: robin briggs
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
#ifndef __CTextCommandPostProcess__
#define __CTextCommandPostProcess__

#include "ITextCommandPostProcess.h"
#include "CPMUnknown.h"


class PUBLIC_DECL CTextCommandPostProcess : public CPMUnknown<ITextCommandPostProcess>
{
	public:
		CTextCommandPostProcess(IPMUnknown * boss);

		virtual void InsertPostProcess(ITextModel* model,  TextIndex position, const WideString* data, const ILanguage *pLanguage = nil ); 
		virtual void ReplacePostProcess(ITextModel* model, TextIndex position, int32 length, const WideString* data, const ILanguage *pLanguage = nil ); 
		virtual void DeletePostProcess(ITextModel* model, TextIndex position, int32 length); 
		virtual void ApplyStylePostProcess(ITextModel* model, TextIndex position, int32 length, UID styleRef, ClassID whichStrand); 

		virtual void ApplyOverridesPostProcess(ITextModel* model, TextIndex position, int32 length, const AttributeBossList *attributes, ClassID whichStrand); 
		virtual void ClearOverridesPostProcess(ITextModel* model, TextIndex position, int32 length, const AttributeBossList *attributes, ClassID whichStrand); 

		virtual void PastePostProcess(ITextModel* model, TextIndex position, const PasteData *data, int32 subrange); 
		virtual void ReplacePostProcess(ITextModel* model, const boost::shared_ptr<ITextModel::ReplacementList>& replList);

		virtual void BeginProcessCommand( ICommand *cmd ); 
		virtual void EndProcessCommand( ICommand *cmd ); 
};


#endif
		// __CTextCommandPostProcess__
