//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayerUIUtils.h $
//  
//  Owner: Paul Sorrick
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
//  Purpose:
//  Utilities for use for dealing with layers.
//  
//========================================================================================

#pragma once
#ifndef __ILayerUIUtils__
#define __ILayerUIUtils__

#include "Utils.h"
#include "LayerPanelID.h"
class ILayerList;
/** Utilities for use for dealing with layers when there is a view.
	@ingroup layout_layer
	@ingroup layout_util
 */
class ILayerUIUtils : public IPMUnknown 
{
	public:
		enum	{kDefaultIID = IID_ILAYERUIUTILS};

		/**	Get the active document layer for the specified context. Works even when a document window isn't open.
			@param context IN IActiveContent to use for active layer. 
			@return the active document layer. 
		 */
		virtual IDocumentLayer* QueryContextActiveLayer(IActiveContext* context) = 0;
		virtual IDocumentLayer* QueryNthUILayer(const ILayerList* list, int32 nth) = 0;
		virtual int32 GetUILayerIndex(const ILayerList* list, UID docUILayerUID) = 0;
};
	
#endif // __ILayerUIUtils__
