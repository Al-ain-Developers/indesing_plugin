//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDocumentLayer.h $
//  
//  Owner: Zak WIlliamson
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
//  Describes the attributes of a document wide layer
//  
//========================================================================================

#pragma once
#ifndef __IDOCUMENTLAYER__
#define __IDOCUMENTLAYER__

#include "IPMUnknown.h"
#include "LayerID.h"

class PMString;

	/** Interface to get and set document layer options.

		@author Zak Williamson
	*/
class IDocumentLayer : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDOCUMENTLAYER };

	typedef enum {
		kDoNotIgnore = 0,
		kIgnore = 1,
		kLeaveUnchanged = 2
	} IgnoreEnum;

	/**	Description: Get the name of the layer.
		@param pName 
	 */
	virtual void GetName(PMString * pName) const = 0;

	/**	Description: Get the name of the layer.
		@param none
	 */
	virtual const PMString& GetName() const = 0;

	/**	Description: Set the name of the layer
		@param newName 
	 */
	virtual void SetName(const PMString& newName) = 0;

	/**	Description: Get the color of the layer
		@param none
		@return const 
	 */
	virtual const UID& GetColorUID() const = 0;


	/**	Description: Set the color of the layer.
		@param &newColor 
	 */
	virtual void SetColorUID(const UID &newColor) = 0;

	/**	Description: return TRUE if the layer is write locked, FALSE otherwise
		@param none
		@return bool16
	 */
	virtual bool16 IsLocked() const = 0;

		// set the lock attribute this layer

	/**	Description: set the lock attribute this layer
		@param active 
	 */
	virtual void SetLocked(bool16 active) = 0;
	

	/**	Description: return TRUE if the layer is visible, FALSE otherwise
		@param none
		@return bool16 
	 */
	virtual bool16 IsVisible() const = 0;
	
	/**	Description: set the visible attribute of this layer
		@param none
		@return bool16 
	 */
	virtual void SetVisible(bool16 visible) = 0;
	
	/**	Description: return TRUE if the layer is printable, FALSE otherwise
		@param none
		@return bool16 
	 */
	virtual bool16 IsPrintable() const= 0;
	
	/**	Description: set the printable attribute of this layer
		@param print - TRUE if layer is printable, FALSE otherwise
	 */
	virtual void SetPrintable(bool16 print) = 0;
	
	/**	Description: return TRUE if the layer is write locked, FALSE otherwise
		@param none
		@return bool16 
	 */
	virtual bool16 IsGuideLocked() const= 0;

	/**	Description: set the lock attribute for guides on this layer
		@param active 
	 */
	virtual void SetGuideLocked(bool16 active) = 0;
	
	/**	Description: return TRUE if the guides on this layer are visible, FALSE otherwise
		@param none
		@return bool16 
	 */
	virtual bool16 IsGuideVisible() const= 0;
	
	/**	Description: set the visible attribute for guides of this layer
		@param visible 
	 */
	virtual void SetGuideVisible(bool16 visible) = 0;
	
	/**	Description: return TRUE if the layer appears in the UI (Layers Panel), FALSE otherwise
		@param none
		@return bool16 
	 */
	virtual bool16 IsUILayer() const = 0;

	/**	Description: set whether the layer appears in the UI or not.
		@param uiLayer 
	 */
	virtual void SetUILayer(bool16 uiLayer) = 0;
	
	/**	Description: return TRUE if the layer can be deleted from the UI (Layers Panel), FALSE otherwise
		@param none
		@return bool16 
	 */
	virtual bool16 IsExpendableLayer() const = 0;

	/**	Description: set whether the layer layer can be deleted from the UI or not.
		@param expendableLayer 
	 */
	virtual void SetExpendableLayer(bool16 expendableLayer) = 0;

	/**	Description: If kTrue, then ignore all text wrap items on this layer when the layer is invisible.
		@param bIgnoreWhenNotVisible 
	 */
	virtual void SetIgnoreTextWrapWhenNotVisible(bool16 bIgnoreWhenNotVisible) = 0;

	/**	Description: Get whether or not text wrap items on this layer will be ignored when the layer is
		invisible.
		@param void 
		@return bool16 
	 */
	virtual bool16 GetIgnoreTextWrapWhenNotVisible(void) const = 0;
};

#endif
