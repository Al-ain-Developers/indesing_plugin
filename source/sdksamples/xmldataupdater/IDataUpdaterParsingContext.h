//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/IDataUpdaterParsingContext.h $
//  
//  Owner: Ian Paterson
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
#ifndef __IDataUpdaterParsingContext_h__
#define __IDataUpdaterParsingContext_h__

#include "IPMUnknown.h"
#include "XMLReference.h"
#include "DataUpdaterID.h"

/** Stores state that we need during parsing.
	@see kXMLParserLocatorBoss.

	@ingroup xmldataupdater
*/
class IDataUpdaterParsingContext : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDATAUPDATERPARSINGCONTEXT }; 

		typedef enum
		{
			kOutside, 
			kWithinTableHasChildren,
			kWithinTableNoChild,
			kWithinRecordHasChildren,
			kWithinRecordNoChild
		} ParsingState;

		/** Set up the current parsing state
			@param state specifying the ParsingState
		*/
		virtual void SetParsingState(const ParsingState& state)=0;

		/** Get parsing state
			@return ParsingState 
		*/
		virtual ParsingState GetParsingState()  const =0;

		/** Set up the current parsing element
			@param state specifying the parsing element
		*/
		virtual void SetParsingElement(const XMLReference& element) = 0;

		/** Get parsing element
			@return Current parsing element 
		*/
		virtual XMLReference GetParsingElement() const = 0;
	
};

#endif // __IDataUpdaterParsingContext_h__


