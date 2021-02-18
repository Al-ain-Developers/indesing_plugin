//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/DataUpdaterParsingContext.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface Includes
#include "IDataUpdaterParsingContext.h"


// Implementation Includes

#include "CPMUnknown.h"
// Project includes:

/** Stores state we read or need when parsing.
	The intent was that we could can will know where we are when processing
	characters we get from the stream. Depending the state, we can parse the
	characters different.

	@ingroup xmldataupdater
*/

class DataUpdaterParsingContext : public CPMUnknown<IDataUpdaterParsingContext>
{
public:

	/** Constructor
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	DataUpdaterParsingContext(IPMUnknown* boss);

	/** Destructor
	*/
	virtual ~DataUpdaterParsingContext() {}

	/** Set up the current parsing state
		@param state specifying the ParsingState
	*/
	virtual void SetParsingState(const ParsingState& state) {
		this->fParsingState = state;
	}

	/** Get parsing state
		@return ParsingState 
	*/
	virtual ParsingState GetParsingState() const {
		return this->fParsingState;
	}

	/** Set up the current parsing element
		@param state specifying the parsing element
	*/
	virtual void SetParsingElement(const XMLReference& element) {
		this->fParsingElement = element;
	}

	/** Get parsing element
		@return Current parsing element 
	*/
	virtual XMLReference GetParsingElement() const {
		return this->fParsingElement;
	}

private:
	ParsingState fParsingState;
	XMLReference fParsingElement;
};


/*	
*/
CREATE_PMINTERFACE(DataUpdaterParsingContext, kDataUpdaterParsingContextImpl)

/*	Constructor
*/
DataUpdaterParsingContext::DataUpdaterParsingContext(IPMUnknown* boss) :
CPMUnknown<IDataUpdaterParsingContext>(boss),fParsingState(IDataUpdaterParsingContext::kOutside) 
{
}


//	end, File: DataUpdaterParsingContext.cpp
