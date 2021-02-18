//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IResourceSrcFileInfo.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IResourceSrcFileInfo_h__
#define __IResourceSrcFileInfo_h__

#include "IPMUnknown.h"
#include "RsrcSpec.h"

/** Interface for maintaining resource file information for a widget, part of kPrimaryResourcePanelWidgetBoss
*/
class IResourceSrcFileInfo : public IPMUnknown
{
public:
	/** Initialize the data

		@param filename IN the file name
		@param lineno IN the starting line number
	*/
	virtual void		Set(const PMString& filename, int32 lineno) = 0;
	/** Get the file name */
	virtual PMString	GetFilename() const = 0;
	/** Get the starting line number */
	virtual int32		GetLineno() const = 0;
};

#endif // __IResourceSrcFileInfo_h__

