//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/PrnSelSuiteCSB.h $
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

#ifndef __PrnSelSuiteCSB_h__
#define __PrnSelSuiteCSB_h__

// General includes:
#include "CPMUnknown.h"

// Project includes:
#include "IPrnSelSuite.h"
#include "ICallback.h"

// forward declarations
class UIDList;

/** Base class for CSB (concrete selection boss) suite implementations of IPrnSelSuite;  
	the CSB suites are responsible for doing all of the model specific work involved
	in accessing and manipulating features of this plug-in. Utilities methods for 
 	the CSB suite implementations are provided in this base class.  

    Sub-classes must implement PrnSelSuiteCSB::GetItemList to populate the 
  	list of page items that are to be printed by this plugin. 
 
	@ingroup printselection
*/
class PrnSelSuiteCSB : public CPMUnknown<IPrnSelSuite>
{
public:
	/** Constructor
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	PrnSelSuiteCSB(IPMUnknown* boss);

	/** Destructor. 
	 */
	virtual ~PrnSelSuiteCSB(void);

	/**	Populates 2 data structures: 
	 * 	(1)page UIDs for pages that contained selected items and 
	 * 	(2) page item UIDs of selected page items.
	*/
	virtual void StoreSelectionData(void);

	/** Can the print selection flag be retrieved?
	 * 	@return kTrue if it can be retrieved (i.e. a selection is available), 
	 * 			kFalse if not. 
	 */
	virtual bool16 CanGetPrintSelectionFlag(void);

	/** Get the print selection flag. 
	 * 	@return The current flag value 
	 */
	virtual bool16 GetPrintSelectionFlag(void);

	/** Can the print selection flag be set?
	 * 	@return kTrue if it can be set (i.e. a selection is available), 
	 * 			kFalse if not. 
	 */
	virtual bool16 CanSetPrintSelectionFlag(void);

	/** Set the print selection flag. 
	 * 	@param printSelection IN Set the print selection flag.
	 * 	@return kSuccess if success, other value if error. 
	 */
	virtual ErrorCode SetPrintSelectionFlag(const bool16 printSelection);

private:

	/**	Returns the UIDs of items in the layout selection.
	 * 	@return UIDList of selected items, without standoffs. 
	 */
	virtual UIDList GetItemList(void) const = 0;
};


#endif

