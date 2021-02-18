//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/detailcontrollistsize/DCLSizPanelOptions.cpp $
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

// API includes
#include "CPMUnknown.h"

// Project includes:
#include "DCLSizID.h" 
#include "IDCLSizPanelOptions.h"

/** Non persistent implementation of IDCLSizPanelOptions used by clients who
	just want to pass IDCLSizPanelOptions parameters around at run time and don't
	need their value stored persistently.

	@ingroup detailcontrollistsize
*/
class DCLSizPanelOptions : public CPMUnknown<IDCLSizPanelOptions>
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	DCLSizPanelOptions(IPMUnknown* boss);
	
	/** Destructor
	 */
	virtual ~DCLSizPanelOptions() {};

	/** See IDCLSizPanelOptions.
	*/
	virtual const bool16 Get();

	/** See IDCLSizPanelOptions.
	*/
	virtual void Set
	(
		const bool16 value 
	);

private:
	bool16	fLargeSize;

};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(DCLSizPanelOptions, kDCLSizPanelOptionsImpl)

/* Constructor
*/
DCLSizPanelOptions::DCLSizPanelOptions(IPMUnknown* boss)
: CPMUnknown<IDCLSizPanelOptions>(boss)
, fLargeSize(kTrue)
{
}

/*
*/
void DCLSizPanelOptions::Set (const bool16 value)
{
	fLargeSize = value;
}

/*
*/
const bool16 DCLSizPanelOptions::Get()
{
	return fLargeSize;
}

// End DCLSizPanelOptions.cpp


