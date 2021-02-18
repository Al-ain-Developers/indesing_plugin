//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageLayoutPrefsCmdData.h $
//  
//  Owner: psorrick
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
//  Data interface for oage layout prefs commands.
//  includes : 	shuffle on or off
//  
//========================================================================================

#pragma once
#ifndef __IPageLayoutPrefsCmdData__
#define __IPageLayoutPrefsCmdData__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "UIDRef.h" 

class IDataBase;

class IPageLayoutPrefsCmdData : public IPMUnknown
{
public:
	virtual void Set(	const	UIDRef&	doc, 			/* which document to affect */
						const	bool16	bShuffle,		/* Is shuffle on or off */
						const	bool16	bPreserveLayout = kTrue) = 0;	/* Preserve layout when turning shuffle on? (Set Keep Spread Together as necessary) */
	virtual const UIDRef& GetDocument() const = 0;
	virtual const bool16  GetShuffle() const = 0;
	virtual const bool16  GetPreserveLayout() const = 0;
};

#endif // __IPageLayoutPrefsCmdData__
