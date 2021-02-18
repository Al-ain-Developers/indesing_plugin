//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/CdlChartSuiteCSB.h $
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

#ifndef __CdlChartSuiteCSB_h__
#define __CdlChartSuiteCSB_h__

// Interface includes:
#include "ICdlChartSuite.h"

// General includes:
#include "CPMUnknown.h"


/** Base class for CSB (concrete selection boss) suite implementations of ICdlChartSuite;  
	the CSB suites are responsible for doing all of the model specific work involved
	in accessing and manipulating ICdlChartData. 99% of the CSB suite implementation 
	of ICdlChartSuite is provided here in this base class.

	Sub-classes implement CdlChartSuiteCSB::GetTarget to examine the selection target for their CSB and determine the
	UID's of selected objects that have an ICdlChartData interface. For example CdlChartSuiteLayoutCSB uses
	ILayoutTarget to get a UIDList of selected objects and CdlChartSuiteTextCSB uses ITextTarget to
	get the range of text and the story that underlies the selection and it then figures out the
	UIDList of frame page items touched by the text selection that have ICdlChartData.
	
	Note that the client does not interact with the CSB suite directly, the client 
	interacts with the ASB only. The implementation of a CSB suite deals with the 
	selection format of its CSB.

	@ingroup candlechart
	
	@see Selection fundamentals in Programming Guide
*/
class CdlChartSuiteCSB : public CPMUnknown<ICdlChartSuite>
{
public:
	/**	Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	CdlChartSuiteCSB(IPMUnknown* iBoss);
	
	/** Destructor. 
	 */
	virtual ~CdlChartSuiteCSB(void);

//	Suite Member functions
	/**	Check if it is able to give the name of the chart.
		@return kTrue if it is capable of giving the name of the chart.
	*/
	virtual bool16 CanGetChartName(void);

	/** Get the name of the chart.
		@param outChartName string where the name of the chart will be given.
	*/
	virtual ErrorCode GetChartName(WideString& outChartName);


// Member functions to be overriden by each CSB sub-class.
protected:
	/** Each CSB suite examines its target interface (ILayoutTarget, ITextTarget etc.) and
		returns the list of objects that are selected and might have ICdlChartData.
		@return a list of the objects that are selected.
	*/
	virtual UIDList GetTarget(void) = 0;
	
};

#endif
// End, CdlChartSuiteCSB.h.

