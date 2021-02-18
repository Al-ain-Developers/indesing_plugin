//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IGenericSettings.h $
//  
//  Owner: Chris Jones
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
//  Programmatically accessible list of preferences/settings.
//  
//========================================================================================

#pragma once
#ifndef __IGenericSettings__
#define __IGenericSettings__

#include "IPMUnknown.h"
#include "IGenericSettingsGroup.h"
#include "IGenericSettingsOutput.h"
#include "IPMUnknownIterator.h"
#include "GenericSettingsID.h"

/** IGenericSettings is used to describe preset preference values.
*/
class IGenericSettings: public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGENERICSETTINGS };

public:
	/** Get the root group of the settings hierarchy.
        @return a pointer to an IGenericSettingsGroup interface.  The
		pointer is valid as long as this IGenericSettings interface is valid.
	*/ 
	virtual IGenericSettingsGroup* GetRootGroup() = 0;

public:
	/** Write out all preset values of the hierarchy.
        @param pStrategy defines the formatting interface to use.
	*/ 
	virtual void WriteTo( IGenericSettingsOutputStrategy* pStrategy ) = 0;
};


#endif 
