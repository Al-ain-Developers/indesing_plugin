//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISVGExportCommandData.h $
//  
//  Owner: Greg St. Pierre
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __ISVGExportCommandData__
#define __ISVGExportCommandData__

class RangeProgressBar;

#include "SVGExportID.h"

#include "IPMStream.h"
#include "ISVGExportPreferences.h"
#include "TransformTypes.h"

/**
 Data interface used to store settings for the SVG export command
 */
class ISVGExportCommandData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISVGEXPORTCOMMANDDATA };

	/**
	 Sets the UI flags to use during the export (used to determines whether to 
	 display progressbar, etc)
	 
	 @param uiFlags		The UI flags to use during the export
	 */
	virtual void SetUIFlags(UIFlags uiFlags) = 0;
	/**
	 Gets the UI flags to use during the export
	 
	 @return the UIFlags to use
	 */
	virtual UIFlags GetUIFlags() const = 0;

	/**
	 Sets boolean flag that indicates whether we should compress output
	 
	 @param compress	kTrue if output should be compressed, else kFalse
	 */
	virtual void SetCompressSVGOutput(bool16 compress) = 0;
	/**
	 Gets boolean flag that indicates whether we should compress output
	 
	 @return kTrue if output should be compressed, else kFalse
	 */
	virtual bool16 GetCompressSVGOutput() const = 0;

	/**
	 Sets the progress bar to use during the export. 
	 
	 Note: progress bar is not owned by this object. It must remain valid
	 for the duration of the export and must be cleaned up the caller.
	 
	 @param pProgress	The progress bar to use during export
	 */
	virtual void SetProgress( RangeProgressBar* pProgress ) = 0;
	
	/**
	 Gets the progress bar to use during the export
	 
	 @return The progress bar to use during export
	 */
	virtual RangeProgressBar* GetProgress() = 0;

	//[TODO]temporary for prototype APIs
	virtual void SetOutputStream(
		InterfacePtr<IPMStream> inOutputStream) = 0;

	virtual InterfacePtr<IPMStream> GetOutputStream() const = 0;
	/**
	 sets whether to include optical alignment margin while exporting page items
	 as svg
	 @param use kTrue if optical alignment needs to be considered.
	 */

	virtual void SetIncludeOpticalMarginAlignment(bool16 use) = 0;

	/**
	 Gets whether to include optical alignment margin while exporting page items
	 as SVG
	 @return kTrue if optical alignment needs to be considered.
	*/
	virtual bool16 GetIncludeOpticalMarginAlignment() const = 0;

	/**
	 sets coordinate space to be used when exporting svg page items. 
	 Note that this option works only we are exporting a single page items . For multiple page 
	 items coordinate space is by default by spread.
	 @param coordinateSpace  coordinate space to be used.
	 */
	virtual void SetCoordinateSpace(const Transform::CoordinateSpace& coordinateSpace) = 0;

	/**
	 Gets the coordinate space to be used for exporting page item
	 as SVG
	 @return coordinate space 
	*/

	virtual Transform::CoordinateSpace GetCoordinateSpace() const = 0;

	/**
	Sets whether to include inline objects in svg output. 
		@param includeInline  kTrue if inline objects need to be included
	*/
	virtual  void SetIncludeInlineObjects(bool16 includeInline) = 0;

	/**
	Gets whether to include inline objects in svg output.
	@return kTrue if inline objects need to be included
	*/
	virtual bool16 GetIncludeInlineObjects() const = 0;
};

#endif //!def __ISVGExportCommandData__