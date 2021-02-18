//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/IFrmLblData.h $
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

#ifndef __IFrmLblData_h__
#define __IFrmLblData_h__

// Interface includes:
#include "IPMUnknown.h"

// General includes:

// Project includes:
#include "FrmLblID.h"

struct FrmLblInfo;

/** 
	From SDK sample; interface to store persistent data to control the display of
	the frame label adornment.

	@ingroup framelabel
	
*/
class IFrmLblData : public IPMUnknown
{
public:

	enum	{kDefaultIID = IID_IFRMLBLDATA};

	/** Accessor 
		Sets the properties of this class
		@param	frmLblInfo	frame label properties.
	*/
	virtual void Set(const FrmLblInfo& frmLblInfo) = 0;

	/** Accessor
		@return	frame label properties
	*/
	virtual const FrmLblInfo& Get() const = 0;
};

#endif // __IFrmLblData_h__

