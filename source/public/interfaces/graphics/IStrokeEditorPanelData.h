//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IStrokeEditorPanelData.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IStrokeEditorPanelData__
#define __IStrokeEditorPanelData__

#include "GraphicPanelsID.h"

class IGraphicsPort;
class IPathStroker;
class IDataBase;

/**
 Interface to be implemented by stroke-specific panels in the stroke editor
 dialog.

 @see IPathStroker
 */
class IStrokeEditorPanelData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTROKEEDITORPANELDATA };

	/**
	 Initialization routine. The stroke editor dialog will call this while 
	 it is initializing. The stroker parameter should be used to initialize 
	 the panel's internal state.

	 Note: It is legal for the stroke editor to pass a path stroker that is
	 either nil or else of a different type than that handled by the panel. 
	 Well-written implementations should handle these cases gracefully by 
	 falling back on the default case.

	 @param stroker			The stroker being edited by the dialog
	 @param wasApplicable	OUT Set to kTrue if stroker is associated with this
							panel, else kFalse
	 */
	virtual void Initialize(IPathStroker const *stroker, bool16 &wasApplicable) = 0;

	/** 
	 Clean up routine called by the stroke editor dialog as the dialog is
	 being destructed. Subclasses should override to clean up their internal
	 state
	 */
	virtual void CleanUp() = 0;

	/**
	 Accessor method. Retrieves path stroker this panel was initialized
	 with, or nil.

	 @return The panel's path stroker
	 */
	virtual IPathStroker *GetPathStroker() const = 0;

	/**
	 Draws a proxy representation of the current stroker data for use in the
	 stroke editor preview widget.

	 @param port			The port to draw to
	 @param start			Starting point of the path to stroke
	 @param end				Ending point of path
	 @param strokeWeight	Stroke weight of line
	 */
	virtual void DrawPreview(
		IGraphicsPort *port,
		PMPoint const &start,
		PMPoint const &end,
		PMReal const &strokeWeight
	) const = 0;

	/**
	 Returns a new path stroker in the specified database using current panel
	 settings.

	 @param db				The database for the new stroker
	 @return New stroker instance
	 */
	virtual IPathStroker *CreatePathStroker(IDataBase *db) const = 0;

	/**
	 Updates a path stroker to current panel settings.

	 @param stroker			The stroker to update
	 @return kTrue if successful, else kFalse
	 */
	virtual bool16 UpdatePathStroker(IPathStroker *stroker) const = 0;
};

#endif //!def __IStrokeEditorPanelData__
