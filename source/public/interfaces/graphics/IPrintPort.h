//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPrintPort.h $
//  
//  Owner: David Berggren
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
//  
//  Purpose:
//  Interface off the print port, so drawing routines have access to the
//  print client items and print object interfaces.	
//  
//========================================================================================

#pragma once
#ifndef __IPrintPort__
#define __IPrintPort__

#include "IPMUnknown.h"
#include "PMString.h"

class IPrintData;
class IInkList;

/** Utility interface to hold information for a print port, such as the
	current print data and ink list, as well as the current ink being printed.
	@see IPrintData
	@see IInlList
*/
class IPrintPort : public IPMUnknown
{
public:

	/** Get the current print data
		@return IPrintData pointer for the print data in use
	*/
	virtual IPrintData *GetPrintData() = 0;

	/** Get the ink list being used
		@return IInkList pointer for the ink list in use
	*/
	virtual IInkList *GetInkList() = 0;

	/** Get the name of current separation, or "Composite" if not doing seps
		@param currentInk OUT the name of the current separation, or "Composite" if not printing seps
	*/
	virtual void GetCurrentInk(PMString& currentInk) = 0;

	/** Set the current print data
		@param iPrtData IN pointer to the print data being used
	*/
	virtual void	Set(IPrintData *iPrtData) = 0;

	/** Set the ink list
		@param iInkList IN pointer to the ink list being used
	*/
	virtual void	Set(IInkList *iInkList) = 0;

	/** Set the current ink being printed
		@param currentInk IN string containing the current ink being printed, or "Composite" if not printing separations
	*/
	virtual void	Set(PMString& currentInk) = 0;

};

#endif
