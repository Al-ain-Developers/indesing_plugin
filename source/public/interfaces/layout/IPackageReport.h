//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPackageReport.h $
//  
//  Owner: KenS
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
//  Interface for package report
//  
//========================================================================================

#pragma once
#ifndef __IPACKAGEREPORT__
#define __IPACKAGEREPORT__

#include "IPMUnknown.h"
#include "IS4SPPackage.h"
#include "IS4SPPackageBook.h"

/** This interface is generate the report created when packaging
	a document or a book.

	@see kS4SPPackageReportBoss
	@see IS4SPPackage
	@see IS4SPPackageBook
*/
class IPackageReport : public IPMUnknown
{
public:
  virtual bool16 GenerateReport( IS4SPPackage* pPackage, IDFile* overridden = NULL, bool16 showCAlert = kTrue, bool16 createReport = kFalse ) = 0;
  virtual bool16 GenerateReport( IS4SPPackageBook* pPackage, IDFile* overridden = NULL, bool16 showCAlert = kTrue, bool16 createReport = kFalse ) = 0;
};


#endif //__IPACKAGEREPORT__

/*==============================================================================
 * $Log: /shuksan/source/components/S4SP/Control/Interfaces/IPackageReport.h $
 * 
 * 2     7/17/98 2:34p Sdu
 * The Final Check in of the Preflight and Package plug-in by Paradigm
 * 
 * 6     7/15/98 4:33p Kens
 * Added flag for showing alert box
 * 
 * 5     7/02/98 3:31p Kens
 * Modified GenerateReport() to take in current package
 * 
 * 4     6/30/98 3:27p Kens
 * Routine checkin
 * 
 * 3     6/25/98 10:49a Kens
 * 
 * 2     6/22/98 4:52p Kens
 * 
 *=============================================================================
 */
