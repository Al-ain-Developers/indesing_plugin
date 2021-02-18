//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/ICHLData.h $
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

#pragma once

#ifndef __ICHLData__
#define __ICHLData__

#include "IPMUnknown.h"
#include "CHLID.h"

class WideString;

//----------------------------------------------------------------------------------------
// Interface ICHLData
//----------------------------------------------------------------------------------------

class ICHLData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICHLINGUISTICDATA };

	virtual int32			GetNumSearchPaths(void) = 0;
	virtual void			SetNumSearchPaths(int32 numSearchPaths) = 0;
	virtual void*			AddSearchPath(bool16 flush) = 0;
	virtual void*			RemoveSearchPath(bool16 flush) = 0;

	virtual	void			SetNotWordUDCFileName( const PMString &rName ) = 0;
	virtual	const PMString&	GetNotWordUDCFileName() const = 0;
	virtual	void			SetIsWordUDCFileName( const PMString &rName ) = 0;
	virtual	const PMString&	GetIsWordUDCFileName() const = 0;

	virtual IDFile*			CreateNewUDC(const PMString& fileName) = 0;
	virtual IDFile*			GetUDC(const PMString& fileName) = 0;
	virtual	IDFile*			GetNotWordUDC( bool16 bCreateIfNotFound ) = 0;	/* get the NOT data file */
	virtual	IDFile*			GetIsWordUDC( bool16 bCreateIfNotFound ) = 0; /* get the default userdict UDC data file */
};

#endif
