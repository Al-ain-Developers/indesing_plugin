//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPathStroker.h $
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
//  
//  Defines the stroker service interface
//  
//========================================================================================

#pragma once
#ifndef __IPathStroker__
#define __IPathStroker__

#include "IPMUnknown.h"
#include "PMRect.h"
#include "GraphicsID.h"

class IPathGeometry;
class IPathPort;
class IGraphicsPort;
class IGraphicStyleDescriptor;
class PMMatrix;
class PMString;
class IGraphicAttributeSuite;

/** 
 IPathStroker defines the interface to be implemented by installable path strokers
 */
class IPathStroker : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPATHSTROKER };

	/**
	 Stroke the pageitem.  The word stroke is overloaded to really mean
	 set up the path and renderingobject and then call the appropriate marking
	 function (e.g. stroke) on gPort.  For solid lines StrokePath is a
	 simple copy of the path into the port.  For other styles, such as dotted or
	 dashed, a more elaborate path setup/stroke is required.

	 The rendering object is set before calling this method.  Also, the path 
	 already exists in the port  -- for solid strokes this means the implementation
	 is very simple.  If you want to change the path don't forget to call newpath 
	 first.
	 gsave/grestore is called for the path stroker -- no need to do it inside
	 strokepath.  If there is no stroke then StrokePath won't be called.
	 
	 @param pageitem		IN The pageitem's graphic style descriptor
	 @param srcPath			IN The pageitem's geometry
	 @param gPort			IN The graphics port in which to draw the stroke
	 @return an ErrorCode describing the success/failure of the stroke operation
	 @see IGraphicStyleDescriptor
	 @see IPathGeometry
	 @see IGraphicsPort
	 */
	virtual ErrorCode StrokePath 
		(
			IGraphicStyleDescriptor* 	pageitem, 
			const IPathGeometry* 		srcPath, 
			IGraphicsPort* 			gPort
		) const = 0;
	
	/**
	 Returns kTrue if the rect intersects the pageitem's stroke, else kFalse
	 
	 Note: Won't be called if the item has no stroke.
	 Note: gPort is assumed to aggregate IRasterPort
	 
	 @param pageitem		IN The pageitem's graphic style descriptor
	 @param srcPath			IN The pageitem's geometry
	 @param r				IN The rectangle to test against
	 @param gPort			IN The port to use
	 @return whether the given rectangle intersects the pageitem's stroke
	 @see IGraphicStyleDescriptor
	 @see IPathGeometry
	 @see IGraphicsPort
	 */
	virtual bool16 InStroke 
		(
			IGraphicStyleDescriptor* 	pageitem, 
			const IPathGeometry* 		srcPath, 
			const PMRect&				r, 
			IGraphicsPort* 				gPort
		) const = 0;

	/**
	 Returns the bounding box of the stroke transformed by theMatrix
	 
	 Note: Won't be called if the item has no stroke.
	 
	 Use the passed in values for stroke weight, line cap, join type, and 
	 miter limit because in certain instances they might be different
	 than that in the descriptor.
	 
	 @param pageitem		IN The pageitem's graphic style descriptor
	 @param strokeWeight	IN The pageitem's stroke weight
	 @param miterLimit		IN The pageitem's miter limit
	 @param lineCap			IN The pageitem's line cap
	 @param joinType		IN The pageitem's join type
	 @param srcPath			IN The pageitem's geometry
	 @param theMatrix		IN The matrix with which to transform the bounding box
	 @return the stroked bounding box
	 @see IPathStroker::GetPaintedStrokePathBBox
	 @see IGraphicStyleDescriptor
	 @see IPathGeometry
	 */
	virtual PMRect GetStrokePathBBox 
		(
			IGraphicStyleDescriptor* 		pageitem, 
			const PMReal&					strokeWeight,
			const PMReal&					miterLimit,
			int32							lineCap,
			int32							joinType,
			const IPathGeometry* 			srcPath, 
			const PMMatrix&					theMatrix
		) const = 0;
	
	/**
	 Returns the painted bounding box of the stroke transformed by theMatrix
	
	 Note: Won't be called if the item has no stroke.
	
	 Use the passed in values for stroke weight, line cap, join type, and 
	 miter limit because in certain instances they might be different
	 than that in the descriptor. This should be a fast but sloppy computation
	 of the bounds used for invalidation purposes only

	 @param pageitem		IN The pageitem's graphic style descriptor
	 @param strokeWeight	IN The pageitem's stroke weight
	 @param miterLimit		IN The pageitem's miter limit
	 @param lineCap			IN The pageitem's line cap
	 @param joinType		IN The pageitem's join type
	 @param srcPath			IN The pageitem's geometry
	 @param theMatrix		IN The matrix with which to transform the bounding box
	 @return the painted bounding box
	 @see IPathStroker::GetStrokePathBBox
	 @see IGraphicStyleDescriptor
	 @see IPathGeometry
	 */
	virtual PMRect GetPaintedStrokePathBBox 
		(
			IGraphicStyleDescriptor* 		pageitem, 
			const PMReal&					strokeWeight,
			const PMReal&					miterLimit,
			int32							lineCap,
			int32							joinType,
			const IPathGeometry* 			srcPath, 
			const PMMatrix&					theMatrix
		) const = 0;
	
	/**
	 Fills in the text string that describes this type of stroke.
	 Future versions of this interface will build an image representation
	 of the stroke.
	 
	 @param pathStrokerName	OUT The name of the stroker
	 */
	virtual void GetPathStrokerName
		(
			PMString* pathStrokerName
		) const = 0;
		
	/**
	 Returns the plugin id and resource id for the panel to load into the stroke
	 panel.  If this service does not have a custom panel then return kFalse.
	 
	 @param retPluginID		OUT The PluginID for the options panel resource
	 @param retRsrcID		OUT The RsrcID for the options panel resource
	 @return kTrue if the stroker has a custom panel resource, else kFalse
	 */
	virtual bool16 GetOptionsPanelRsrc 
		(
			PluginID* retPluginID, 
			RsrcID*   retRsrcID
		) const = 0;
		
	/**
	 Strokes the given path for use in the user interface. Implementations should 
	 use an appropriate default graphics state when drawing. 
	 
	 Note: A default rendering object has already been installed in the port
	 
	 @param srcPath			IN The path geometry for the stroke
	 @param gPort			IN The port in which to draw
	 @param strokeWidth		IN The stroke weight for the stroke
	 @see IPathGeometry
	 @see IGraphicsPort
	 */	 
	virtual ErrorCode StrokePathForUI
		(
			const IPathGeometry *srcPath,
			IGraphicsPort *gPort,
			PMReal const &strokeWidth
		) const = 0;
};


#endif
