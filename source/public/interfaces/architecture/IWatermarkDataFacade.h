//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IWatermarkDataFacade.h $
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

#ifndef __IWatermarkDataFacade_h__
#define __IWatermarkDataFacade_h__

// Interface includes:
#include "IPMUnknown.h"
#include "IWatermarkData.h"


// General includes:
// Project includes:

/** A facade that provides useful manipulations of IWatermarkData.

	@ingroup Watermark
*/
class IWatermarkDataFacade : public IPMUnknown
{
public:

	enum	{kDefaultIID = IID_IWATERMARKDATAFACADE};

	/**	Get entire preference setting of the watermark from workspace.
	 *	@param workspace IN The workspace that contains the watermark setting.
	 * 	@param wmkInfo OUT The preference for the watermark.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode GetWatermarkPref(const UIDRef& workspace, IWatermarkData::WatermarkInfo& wmkInfo) = 0;

	/**	Set entire preference setting of the watermark in workspace.
	 *	@param workspace IN The workspace to update.
	 * 	@param wmkInfo OUT The preference for the watermark.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode SetWatermarkPref(const UIDRef& workspace, const IWatermarkData::WatermarkInfo& wmkInfo) = 0;
};

#endif // __IWatermarkDataFacade_h__

