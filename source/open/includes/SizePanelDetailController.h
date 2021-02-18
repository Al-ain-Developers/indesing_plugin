//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/SizePanelDetailController.h $
//  
//  Owner: Lin Xia
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
#ifndef __SizePanelDetailController__
#define __SizePanelDetailController__

#include "ISizePanelDetailController.h"
#include "widgetid.h"
#include "PersistObjectCollection.tpp"
#include "HelperInterface.h"
#include "PMPoint.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

//========================================================================================
// CLASS SizePanelDetailController
//========================================================================================

class WIDGET_DECL SizePanelDetailController : public ISizePanelDetailController
{
public:
	SizePanelDetailController(IPMUnknown *boss);
	virtual ~SizePanelDetailController();
	
	virtual void	ReadWrite(IPMStream *s, ImplementationID prop);

	virtual void	RotateDetailLevel();
	virtual void	ShowDetailLevel(int16 nthLevel);

	virtual int16	GetDetailLevel() const;
	virtual int16	GetNumDetailLevels() const;
	virtual int16	GetDefaultDetailLevel() const;

	virtual void	SetDefaultSize(const PMPoint& size);

private:
	void			SizeWindowToFit();

protected:	
	PMPoint			fDefaultSize;
	PMPoint			fUserSize;
	
DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
