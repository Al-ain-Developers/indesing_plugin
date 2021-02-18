//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextCommandPostProcess.h $
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
#ifndef __ITextCommandPostProcess__
#define __ITextCommandPostProcess__

#include "IPMUnknown.h"
#include "IStrand.h"
#include "K2SmartPtr.h"
#include "TextID.h"


class WideString;
class AttributeBossList;
class PasteData;
class ITextModel;
class ILanguage;
class ICommand;

/** 
	@ingroup text_service
*/
class ITextCommandPostProcess : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTEDITPOSTPROCESS };
		
			// allows service to postprocess text commands
		virtual void InsertPostProcess(ITextModel* model,  TextIndex position, const WideString* data, const ILanguage *pLanguage = nil ) = 0;
		virtual void ReplacePostProcess(ITextModel* model, TextIndex position, int32 length, const WideString* data, const ILanguage *pLanguage = nil ) = 0;
		virtual void DeletePostProcess(ITextModel* model, TextIndex position, int32 length) = 0;
		virtual void ApplyStylePostProcess(ITextModel* model, TextIndex position, int32 length, UID styleRef, ClassID whichStrand) = 0;

		virtual void ApplyOverridesPostProcess(ITextModel* model, TextIndex position, int32 length, const AttributeBossList *attributes, ClassID whichStrand) = 0;
		virtual void ClearOverridesPostProcess(ITextModel* model, TextIndex position, int32 length, const AttributeBossList *attributes, ClassID whichStrand) = 0;

		virtual void PastePostProcess(ITextModel* model, TextIndex position, const PasteData *data, int32 subrange) = 0;
		virtual void ReplacePostProcess(ITextModel* model, const boost::shared_ptr<ITextModel::ReplacementList>& replList) = 0;

			// Begin/EndProcessCommand are called by UserApplyAttrCmd and UserTypeTextCmd to temporarily enable CJKTextPreProcessor and ScriptTextProcessor.
		virtual void BeginProcessCommand( ICommand *cmd ) = 0;
		virtual void EndProcessCommand( ICommand *cmd ) = 0;
};


#endif
		// __ITextCommandPostProcess__
