//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDCSInfo.h $
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
//  Holds the information associated with a DCS (Desktop Color Separation) file.
//  This interface hangs off the kDCSItemBoss. A DCS item is created when a DCS
//  file is imported in pieces mode. This interface holds the information used
//  by the OPI print engine when printing a DCS item.	
//  
//========================================================================================

#pragma once
#ifndef __IDCSInfo__
#define __IDCSInfo__

#include "IPMUnknown.h"
#include "PMString.h"
#include "EPSTagTableData.h"

class IDCSInfo : public IPMUnknown 
{
public:

	// Set methods
	
	virtual void SetEmpty(void) = 0;
	virtual void SetInfoFlag(const INFOFLAGS flag) = 0;
	virtual void AppendPlate(const CString plateName, const CString plateFile) = 0;
	virtual void AppendPlate(const CString plateName, const double plateOffset, const double plateLength) = 0;
	
	// Access method
		
	virtual uint16 PlateCount(void) const = 0;
	virtual INFOFLAGS InfoFlag(void) const = 0;
	virtual PMString PlateName(uint16 index) const = 0;
	virtual PMString PlateFile(uint16 index) const = 0;
	virtual PMString PlateFile(PMString plateName) const = 0;
	virtual uint32 PlateOffset(uint16 index) const = 0;
	virtual uint32 PlateOffset(PMString plateName) const = 0;
	virtual uint32 PlateLength(uint16 index) const = 0;
	virtual uint32 PlateLength(PMString plateName) const = 0;
	virtual bool16 IsEmpty(void) const = 0;
		
	// Copy method

	virtual void CopyDCSInfo (const IDCSInfo* otherInfo) = 0;
};				

#endif