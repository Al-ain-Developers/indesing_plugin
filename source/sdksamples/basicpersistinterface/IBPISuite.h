//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/IBPISuite.h $
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

#ifndef _IBPISuite_h_
#define _IBPISuite_h_

#include "BPIID.h"

class IPMUnknown;
class WideString;

/** From SDK sample; new abstract suite interface that extends the capability of the selection
	so that it can manipulate the value of IBPIData associated with the 
	objects that are currently selected.

	Four implementations are provided in this plug-in, BPISuiteASB,
	BPISuiteLayoutCSB, BPISuiteTextCSB and BPISuiteDefaultCSB.

	Note: This suite API doesn't contain model data that is specific to a 
	selection format (UIDList, text model/range, etc) so that the client 
    code is completely decoupled from the underlying concrete selection.

	For more documentation on suites please read the Selection fundamentals chapter 
	in Programming Guide.

	@ingroup basicpersistinterface
	
	@see Selection fundamentals chapter in Programming Guide
*/
class IBPISuite : public IPMUnknown
{
//	Data Types
public:
	enum { kDefaultIID = IID_IBPISUITE };

//	Member functions
public:
	/**
		@return kTrue if the caller can apply IBPIData to the objects that are currently selected, kFalse otherwise.
	*/
	virtual bool16			CanApplyBPIData(void) = 0;

	/**
		Apply the given value for IBPIData to the objects that are currently selected.
		@pre IBPISuite::CanApplyBPIData returns kTrue
		@param value IN the string value to be set in the IBPIData of the selected objects.
		@return kSuccess if the value was applied successfully, kFailure otherwise.
	*/
	virtual ErrorCode		ApplyBPIData(const WideString& value) = 0;

	/**
		@return kTrue if there is any IBPIData associated with objects that are currently selected, kFalse otherwise
	*/
	virtual bool16			CanGetBPIData(void) = 0;

	/**
		Retrieve the IBPIData associated with the objects that are currently selected. Note that since
		more than one object can be selected and each one can have distinct IBPIData value a vector is
		used to get the data.
		@pre IBPISuite::CanGetBPIData returns kTrue
		@param values OUT vector of the IBPIData(a WideString) values of the current selected items.
		Note only unique string values are returned. If several objects have the same IBPIData value
		e.g. the string "hello" only one "hello" string is returned.
	*/
	virtual void			GetBPIData(K2Vector<WideString>& values) = 0;
};

#endif // _IBPISuite_

// End, IBPISuite.h


