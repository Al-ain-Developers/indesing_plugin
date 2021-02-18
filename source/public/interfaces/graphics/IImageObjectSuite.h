//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageObjectSuite.h $
//  
//  Owner: DBerggren
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
//  Defines the interface for the image object suite to be used in the new selection architecture
//  
//========================================================================================

#pragma once
#ifndef __IImageObjectSuite__
#define __IImageObjectSuite__

// ----- Interface files
#include "IPMUnknown.h"
#include "IGraphicLayerInfo.h"

// ----- ID files
#include "ImageID.h"

class IImageObjectSuite : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IIMAGEOBJECTSUITE };

		//________________________________________________________________________________________
		//	Accessors
		//________________________________________________________________________________________
		
		/**	Initialize the layer information for the selected graphic - fires
			off the command kInitializeGraphicLayersCmdBoss if necessary
			@return ErrorCode 
			@precondition CanModifyLayers() == kTrue. 
		*/
		virtual ErrorCode			InitGraphicLayerInfo	() = 0;

		/**	Copies the layer information from the selected graphic to the given interface
			@param IGraphicLayerInfo* - the layer information interface to copy to
			@return ErrorCode 
			@precondition CanModifyLayers() == kTrue. 
		*/
		virtual ErrorCode			GetGraphicLayerInfo	(IGraphicLayerInfo* dstLayerInfo) = 0;

		/**	Copies the given layer information to the selected graphic
			@param IGraphicLayerInfo* - the layer information interface to copy from
			@return ErrorCode 
			@precondition CanModifyLayers() == kTrue. 
		*/
		virtual ErrorCode			SetGraphicLayerInfo	(IGraphicLayerInfo* srcLayerInfo) = 0;

		/**	Get the selected graphic item, IF it is either a PSD or PDF 
			@return ErrorCode 
			@precondition CanModifyLayers() == kTrue. 
		*/
		virtual ErrorCode			GetGraphicItem			(UIDRef& itemUIDRef) = 0;

		/**	Determine if the selected item is a PDF or PSD. 
			@return kTrue if selected item is PDF or PSD (or if the frame is selected), kFalse otherwise 
		*/
		virtual bool16				CanModifyLayers			() = 0;
		
		/**	Determine if the selected item has a bad link state. 
			@return kTrue if selected item is missing, out of date, or embedded, kFalse otherwise 
		*/
		virtual bool16				BadLinkState			() = 0;
		
		/**	Determine if the selected item has layer comp info (PSD only). 
			@return kTrue if selected item has layer comp info, kFalse otherwise 
		*/
		virtual bool16				HasLayerCompInfo		() = 0;
		
};

#endif		// __IImageObjectSuite__