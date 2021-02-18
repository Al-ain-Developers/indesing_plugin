//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IShape.h $
//  
//  Owner: Jeff Argast
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
//  Restricted File
//  
//========================================================================================

#pragma once
#ifndef __ISHAPE__
#define __ISHAPE__

#include "IPMUnknown.h"
#include "GenericID.h"
#include "GraphicsID.h"
#include "PMRect.h"
#include "UIDRef.h"
#include "UIDList.h"
#include "IGraphicsContext.h"
#include "GraphicsData.h"
#include "TransformTypes.h"

class IViewPort;
class IGeometry;
class PMMatrix;
class ICallback;

/**
	This interface is used to inval and draw the item. 
*/
class IShape : public IPMUnknown
{
	public:
		/**
			Define the default IID for IShape.
		*/
		enum { kDefaultIID = IID_ISHAPE };
	
		/**
			Define drawing flags.
		*/
		enum {
			/** kNoFlags */
			kNoFlags = 0,
			/** kDrawingClippedOutImageData */
			kDrawingClippedOutImageData = 1,
			/** when used with wireframe, causes drawing in XOR mode */
			kUseXOR = 2,			
			/** flags specifying dynamic drawing - Shapes that take too long to draw
				dynamicly may choose to draw differently in dynamic situations. */
			kDrawResizeDynamic = 4,
			/** kDrawRotateDynamic */
			kDrawRotateDynamic = 8,
			/** kDrawScaleDynamic */
			kDrawScaleDynamic = 16,
			/** kDrawMoveDynamic */
			kDrawMoveDynamic = 32,
			/** kDrawCreateDynamic */
			kDrawCreateDynamic = 64,
			/** set if Patient user timer expired */
			kPatientUser = 128,
			/** set if doing text composition during patient user tracker and drag and drop operations */
			kDynamicPause = 256,
			/** kPrinting, NOTE: see kIteratePrinting below. */
			kPrinting = 512,
			/** kDoBroadcast */
			kDoBroadcast = 1024,
			/** kDrawFrameEdge */
			kDrawFrameEdge = 2048,
            /** aka print preview */
			kPreviewMode = 4096
			};
			
		/**
			Define hit test flags.
		*/
		enum {
			/** Normal selection with the pointer tool - Selects object and content */
			kSelect = 1,					
			/** "tunnels" the hit test to allow leaf node items and paths to be selected */
			kDirectSelect = 2,				
			/** Successive clicks adds another subset of grouped objects to the selection */
			kGroupSelect = 4,				
			/** if hitting a master page item, override it & return the local UID */
			kOverrideMasterPageItemNoSelect = 8,	
			/** if hitting a master page item, override it & return the local UID plus select the item */
			kOverrideMasterPageItem = kOverrideMasterPageItemNoSelect + kSelect,	
			/** Hit test items - Doesn't not include items on hidden/locked layers, but does include master page items. */
			kHitTest = 16,					
			/** Normal selection with the pointer tool but treats every pageitem as it was filled (used by IBeamTracker). */
			kSolidSelect = 32,				
			/** Used by TOPTool to only detect a hit on a path */
			kOnlyPath = 64,					
			/** Hit test items on locked layers - UID returned should not be used to change the page item (used by ToolTips). */
			kHitTestLockedLayers = 128,		
			/** Used by TextOnPath to detect a hit on a TextOnPath adornment shape */
			kHitTextOnPath = 256,
			/** When using one of the kOverrideMasterPageItem flags above, additionally override text frames threaded to the hit object & return the local UID */
			kOverrideThreadedMasterPageItems = 512
			};
		
		/**
			Define iterate flags.
		*/
		enum {
			/** Set if the page item being iterated is from a master, clear otherwise */
			kIsAMasterPageItem = 1,
			/** Pass to IterateDrawOrderHierarchy() to prevent IterateDrawOrder() from iterating through its children */
			kSkipChildren = 2,
			/** Pass to IterateDrawOrderHierarchy() to prevent IterateDrawOrder() from iterating through hidden spread layers */
			kSkipHiddenLayers = 4,
			/** Pass to IterateDrawOrderHierarchy() to prevent IterateDrawOrder() from iterating through locked spread layers */
			kSkipLockedLayers = 8,
			/** Pass to IterateDrawOrderHierarchy() to prevent IterateDrawOrder() from iterating through hidden and locked spread layers */
			kSkipHiddenAndLockedLayers = kSkipHiddenLayers + kSkipLockedLayers,	
			/** Pass to IterateDrawOrderHierarchy() to prevent IterateDrawOrder() from iterating through guide spread layers */
			kSkipGuideLayers = 16,		
			/** Pass to IterateDrawOrderHierarchy() to prevent IterateDrawOrder() from iterating through items on the masters assigned to this hierarchy */
			kSkipMasterPageItems = 32,
			/** Pass to IterateDrawOrderHierarchy() to prevent IterateDrawOrder() from iterating through non-guide spread layers (that is, skip regular layers) */
			kSkipNonGuideLayers = 64,		
			/** Pass to IterateDrawOrderHierarchy() to allow IterateDrawOrder() to iterate over hidden form states */
			kIncludeHiddenFormStates = 128,
			/** Pass to IterateDrawOrderHierarchy() to prevent IterateDrawOrder() from iterating through non-printing spread layers */
			kSkipNonPrintingLayers = 256,
			/** Pass to IterateDrawOrderHierarchy() to allow IterateDrawOrder() to iterate over as if printing. Due to lack up type checking for IShape enums, this must match kPrinting above since they are unfortunately used interchangeably in the codebase. */
			kIteratePrinting = 512,
			/** Pass to IterateDrawOrderHierarchy() to allow IterateDrawOrder() to iterate over text on path items. Must be iterating children for this to work (i.e. kSkipChildren should be off) */
			kIncludeTOPPageItems = 1024,
			
			/** 
			 Pass to IterateDrawOrderHierarchy() to prevent IterateDrawOrder() from iterating over form states.

			 If specified, states in multi-state page items (e.g., buttons) will *not* be iterated. This supersedes
			 kIncludeHiddenFormStates. If both flags are specified, kIncludeHiddenFormStates is implicitly ignored.

			 @see kIncludeHiddenFormStates
			 */
			kSkipFormStates = 2048,
			/** PDF export */
			kPDFExportMode = 4096
			};

		/**
			Define inval flags.
		*/
		enum {
			/** Inval path handle shape */
			kPathSelection = 1
			} ;

		/**
			Draw the shape of item. In general, don't call draw or HitTest directly. Use IDrawMgr instead.

			@param gd the graphics context used for drawing.
			@param flags default as kNoFlags and serves as a drawing flag.
			@return void.
		*/
		virtual void ProcessDrawShape( GraphicsData* gd, int32 flags = kNoFlags) = 0;

		/**
			Call callbackInfo->callback for each item in this shape's hierarchy.

			@param xform the matrix to transform coordinates.
			@param callbackInfo 
			@param flags default as kNoFlags and serves as a drawing flag.
			@return void.
		*/
		virtual void IterateShapeDrawOrder_(const PMMatrix *xform, ICallback *callbackInfo, int32 flags = 0) = 0;
		void IterateShapeDrawOrder( ICallback *callbackInfo, int32 flags = 0)
		{
			PMMatrix identity;
			IterateShapeDrawOrder_( &identity, callbackInfo, flags);
		}

		/**
			Get the painted bounds. The bounds must include all painted area but does not
			need to be pixel perfect. Compute the bounds in pasteboard coords and then
			transform by theMatrix.

			@param theMatrix the matrix to transform the bounds based on pasteboard coordinates.
			@return PMRect the bounds for painting(redrawing). 
		*/
		virtual PMRect GetPaintedBBox(const PMMatrix& theMatrix, const Transform::CoordinateSpace& coordinateSpace /*= Transform::PasteboardCoordinates()*/) = 0;
		
		/**
			Get the bounds around what will actually print. This includes the stroke bounds
			plus whatever adornments are set to print. Compute the bounds in pasteboard coords and then
			transform by theMatrix.

			@param theMatrix the matrix to transform the bounds based on pasteboard coordinates.
			@param includeAdornments [IN] Whether or not printing adornments are included in the resulting bounding box
			@return PMRect the bounds for printing. 
		*/
		virtual PMRect GetPrintedBBox(const PMMatrix& theMatrix, const Transform::CoordinateSpace& coordinateSpace /*= Transform::PasteboardCoordinates()*/, bool32 includeAdornments = kTrue) = 0;
		
		/**
			Invalidate the appropriate region of the object in the graphics context.

			@param gd the graphics context used for invalidation.
			@param reasonForInval the ClassID defined for inval reason for handling different inval cases. 
			@param flags default as kNoFlags and serves as a drawing flag.
			@return void.
		*/
		virtual void Inval(GraphicsData *gd, ClassID reasonForInval = 0, int32 flags = 0) = 0;
		
};


#endif
