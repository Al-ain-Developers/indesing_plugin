//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicshape/BscShpUtils.cpp $
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

#include "VCPlugInHeaders.h"

// Interfaces:
#include "IPathUtils.h"
#include "INewPageItemCmdData.h"

// General:
#include "Utils.h"
#include "PMRect.h"

// Project:
#include "BscShpUtils.h"
#include "BscShpID.h"

/*
*/
UIDRef BscShpUtils::CreateBasicShape(const UIDRef& parent, PBPMRect bbox)
{
	return Utils<IPathUtils>()->CreateRectangleSpline(	parent, 
														bbox, 
														INewPageItemCmdData::kGraphicFrameAttributes,
														kBscShpPageItemBoss,
														kTrue);
}
			
// End BscShpUtils.cpp

