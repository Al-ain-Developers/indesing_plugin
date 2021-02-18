//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IImportPreview.h $
//  
//  Owner: jargast
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
#ifndef __IImportPreview__
#define __IImportPreview__

#include "IPMUnknown.h"
#include "OpenPlaceID.h"

/** IImportPreview
	This class is used to create a 24 bit RGB preview for the Place dialog.  This interface
	lives off of the PlaceProviderBoss (the boss containing an IID_IIMPORTPROVIDER interface)
	for each specific page item.  If the interface does not exist, then the OS is responsible
	for drawing the preview on the Mac and no preview is drawn on Windows.  If you are implementing
	this routine, it is desirable to periodically check events to allow the user to abort
	the preview creation process.
*/
class IImportPreview : public IPMUnknown
{
public:
	/** Create a 24 bit RGB preview of the stream contents.
		@param prevBaseAddr - OUT: Pointer to the bitmap data. The base addr points to an already 
			allocated block of memory that is (((width * 3) + 3) / 4) * 4 * height bytes large.  
			That is, each row is long aligned.
		@param prevWidth - IN: The width of the preview area.
		@param prevHeight - IN: The height of the preview area.
		@param iPMStream - IN: the input stream containing the data we want previewed.
		@param useProgressBar - IN: kTrue if it is okay to draw a progress bar.
		@return kSuccess if successful.  Otherwise, something like kFailure.
	*/
		
	virtual ErrorCode Create24bitRGBPreview 
						(
							uint8*		prevBaseaddr,
							int32		prevWidth,
							int32		prevHeight,	
							IPMStream*	iPMStream,
							bool16		useProgressBar
						) const = 0;
};

#endif	//__IImportPreview__
