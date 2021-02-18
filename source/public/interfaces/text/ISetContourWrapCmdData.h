//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ISetContourWrapCmdData.h $
//  
//  Owner: Dave Stephens
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
#ifndef __ISetContourWrapCmdData__
#define __ISetContourWrapCmdData__

#include "IPMUnknown.h"

#include "IStandOffContourWrapSettings.h"

#include "StandOffID.h"

/** Command data interface for the SetContourWrapCmd.  This command is used to save off
	the contour text wrap settings used to create a contour text wrap.

	NOTE: Pass an itemlist containing a UIDRef of the page item(s) we are interested in.  Alternatively,
		  you can pass in the IDataBase * of the document and kInvalidUID to get the defaults
		  for the document workspace, or nil and kInvalidUID to get the defaults for
		  the session workspace.

	@ingroup text_wrap
*/
class ISetContourWrapCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISETCONTOURWRAPCMDDATA };

	// pass the contour wrap settings and the pageItem for which the settings apply
	virtual void Init(IStandOffContourWrapSettings::ContourWrapType type,
					int16 pathOrAlphaIndex,	// 0 based embbeded path or alpha channel index
					PMReal Tolerance,
					uint8 Threshold,
					bool8 AllowHoles) = 0;

	// Accessor methods
	virtual IStandOffContourWrapSettings::ContourWrapType GetType() const = 0;

	virtual int16 GetIndex() const = 0;

	virtual PMReal GetTolerance() const = 0;

	virtual uint8 GetThreshold() const = 0;

	virtual bool8 GetAllowHoles() const = 0;
};

#endif // __ISetContourWrapCmdData__
