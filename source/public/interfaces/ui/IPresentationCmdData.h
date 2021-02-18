//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPresentationCmdData.h $
//  
//  Owner: Dave Burnard
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
#ifndef __IPresentationCmdData__
#define __IPresentationCmdData__

#include "AppUIID.h"

class IDocumentPresentation;

/**
   This interface is the data interface for several close presentation commands, 
   e.g., kClosePresentationCmdBoss, kCloseGalleyPresentationCmdBoss.
*/
class IPresentationCmdData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IPRESENTATIONCMDDATA };

	/**
		Set the presentation we operate on.
		@param win refers to the window we operate on.
	*/
	virtual void Set(IDocumentPresentation* presentation) = 0;

	/**
		Get the window we operate on.
		@return IWindow, the window we operate on.
	*/
	virtual IDocumentPresentation* GetPresentation() const = 0;

	/**
		Set whether the command may be canceled. Default is kTrue.
		@param allowCancel whether the command may be canceled.
	*/
	virtual void SetAllowCancel( bool16 allowCancel ) = 0 ;

	/**
		Get whether the command may be canceled.
		@return whether the command may be canceled.
	*/
	virtual bool16 GetAllowCancel() const = 0 ;
};

#endif // __IPresentationCmdData__
