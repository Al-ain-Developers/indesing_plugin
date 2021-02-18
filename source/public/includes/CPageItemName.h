//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CPageItemName.h $
//  
//  Owner: lance bushore
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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
#ifndef __CPageItemName__
#define __CPageItemName__

#include "IPageItemName.h"
#include "CPMUnknown.h"

#pragma export on

class  PUBLIC_DECL CPageItemName : public CPMUnknown<IPageItemName>
{
public:
	CPageItemName(IPMUnknown *boss);
	virtual ~CPageItemName();
	
	virtual PMString GetPageItemName() const;
	virtual PMString GetDefaultNameForObject() const;
	virtual void SetPageItemName(const PMString& newName);
	
	virtual void ReadWrite(IPMStream *s, ImplementationID prop);	
	
private:
	PMString fCurrentName;

};
#pragma export off

#endif
