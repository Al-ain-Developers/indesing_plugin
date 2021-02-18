//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printmemorystream/PrtMemPrintDataHelperStrategy.cpp $
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

// Interface includes:
#include "IPrintDataHelperStrategy.h"

// Project includes
#include "PrtMemID.h"
// NOTE: See comment about this global flag in PrtMemActionComponent.cpp.
extern bool16 gPrtMemPrintingToMemory;


/** Implementation of IPrintDataHelperStrategy, which participates in 
 * 	setting up the Print/Print Preset dialog UI elements.
 * 	@ingroup printmemorystream
*/
class PrtMemPrintDataHelperStrategy : public CPMUnknown<IPrintDataHelperStrategy>
{
public:
	/** Constructor.
	 * 	@param boss interface ptr from boss object on which this interface is aggregated.
	 */
	PrtMemPrintDataHelperStrategy(IPMUnknown* boss);

	/** Destructor 
	 */
	virtual ~PrtMemPrintDataHelperStrategy(void);

    /**	See IPrintDataHelperStrategy::IsLocked
	 */
	virtual bool16 IsLocked(const IPrintData* printData, IPrintData::Id id) const;

	/**	See IPrintDataHelperStrategy::IsRelevant
	 */
	virtual bool16 IsRelevant(const IPrintData* printData, IPrintData::Id id) const;
};

// CREATE_PMINTERFACE
//	Binds the C++ implementation class onto its ImplementationID 
// 	making the C++ code callable by the application.
CREATE_PMINTERFACE(PrtMemPrintDataHelperStrategy, kPrtMemPrintDataHelperStrategyImpl)

/* Constructor
*/
PrtMemPrintDataHelperStrategy::PrtMemPrintDataHelperStrategy(IPMUnknown *boss)
:   CPMUnknown<IPrintDataHelperStrategy>(boss)
{
}

/* Destructor
*/
PrtMemPrintDataHelperStrategy::~PrtMemPrintDataHelperStrategy()
{
}

/* IsLocked
*/
bool16 PrtMemPrintDataHelperStrategy::IsLocked(const IPrintData* printData, IPrintData::Id id) const
{
	// none of the UI elements are to be locked by this plug-in. 
	return kFalse;
}

/* IsRelevant
*/
bool16 PrtMemPrintDataHelperStrategy::IsRelevant(const IPrintData* printData, IPrintData::Id id) const
{
	// Disable some of the print UI that are not relevant to our plug-in, like the printer.
	if (gPrtMemPrintingToMemory == kTrue && 
		(id == IPrintData::kPrinterId))
	{
		return kFalse;
	}
	return kTrue;
}

// End, PrtMemPrintDataHelperStrategy.cpp.
