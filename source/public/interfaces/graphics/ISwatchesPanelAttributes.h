//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISwatchesPanelAttributes.h $
//  
//  Owner: SusanCL
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
#ifndef __ISwatchesPanelAttributes__
#define __ISwatchesPanelAttributes__

#include "widgetid.h"

/**	This interface reads a set of attributes from a resource file. These attributes control
	how the "Swatch List" widget will configure itself (graphic state interaction, button visibility,
	swatch editability etc.) and which color items in the model it will display. Adding all referenced
	unnamed colors to color list might have performance issues. 
	
	
	"Any Swatch" entry can be added to swatch list. This entry essentially means no color. This is
	used for no particular selection.
*/
class ISwatchesPanelAttributes : public IPMUnknown
{
public:
	enum	{kDefaultIID = IID_ISWATCHESPANELATTRIBUTES};
	// ----- Query -----
	
	/**	Returns true if swatch list widget has interaction with the graphic state objects.
	*/
	virtual bool16		GetGraphicStateInteraction() const = 0;
	/**	Returns true if swatch list widget should include show swatch buttons.
	*/
	virtual bool16		GetShowButtons() const = 0;
	/**	Returns true if swatch list item can be edited directly by double-clicking.
	*/
	virtual bool16		GetListItemsEditable() const = 0;
	/**	Returns true if swatch list widget is allowed to display the currently selected
		unnamed swatch.
	*/
	virtual bool16		GetAddUnnamedColorFlag() const = 0;
	/** Should the "Swatch List" widget show all referenced unnamed colors
		For large documents there might be performance issues with this.
	    @return kTrue or kFalse
	*/
	virtual bool16		AllowAllReferencedUnnamedColors() const = 0;
	/** Should the "Swatch List" widget show an entry named "Any Swatch"
	    @return kTrue or kFalse
	*/
	virtual bool16		AllowAnySwatchEntry() const = 0;

	/**	Return the rendering object class ID the swatch list widget is filtered with.
		If kInvalidClass is returned then all rendering types in the swatch list is shown.
	*/
	virtual ClassID	GetViewFilterClassID() const = 0;

	/**
	 * Returns a bool indicating if this instance of swatches panel should observe IID_IRENDERINGOBJECT protocol. Attaching to this protocol ensures that the swatches list gets updated as soon as we add/delete a swatch
	 */
	virtual bool16		ShouldObserveRenderingObjectChange() const = 0;

	// ----- Set -----

	/**	Set the swatch list view filter class ID.
		@param newClassId specifies the new list view filter class ID.
	*/
	virtual void		SetViewFilterClassID( const ClassID& newClassId) = 0;
};

#endif
