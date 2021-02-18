//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TransformUtils.h $
//  
//  Owner: ?
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
//  Some often used tranformation calculations shelled with easy to use functions
//  
//========================================================================================

#pragma once
#ifndef __TransformUtils__
#define __TransformUtils__

#include "PMMatrix.h"
#include "PMPoint.h"
#include "ITransform.h"

class IPMUnknown;
class PMRect;
class PMPolygon4;
class IHierarchy;
class PMPathPoint;
class IGraphicsPort;

#pragma export on

/**	Transform Utility methods;
	These utility methods provide
	(1) transformation among Inner, Parent, and pasteboard 
		coordinates for point, rectange, ploygon etc,
	(2) Tranform matrix for transformation among Inner, Parent, 
		and pasteboard coordinates,
	(3) Actual transform pageitems (PageItem transform helper functions).
 */

//
// Inner <--> Pasteboard
//


/**	Transform a point from Pasteboard coordinates to the inner coordinates of a pageitem
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] point to transform
 */
PUBLIC_DECL void TransformPasteboardPointToInner(const IPMUnknown * pUnknown, PMPoint * pt);

/**	Transform a point from the inner coordinates of a pageitem to pasteboard coordinates
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] point to transform
 */
PUBLIC_DECL void TransformInnerPointToPasteboard(const IPMUnknown * pUnknown, PMPoint * pt);


/**	Transform a distance from the inner coordinates of a pageitem to pasteboard coordinates
	@param pUnknown [IN] any interface on the pageitem
	@param delta [IN/OUT] the distance (in delta.X() and delta.Y())
 */
PUBLIC_DECL void InnerToPasteboardDelta(const IPMUnknown * pUnknown, PMPoint * delta);


/**	Transform a path point from Pasteboard coordinates to the inner coordinates of a pageitem
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] PathPoint (point with directions)
 */
PUBLIC_DECL void TransformPasteboardPathToInner(const IPMUnknown * pUnknown, PMPathPoint * pt);

/**	Transform a path point from the inner coordinates of a pageitem to Pasteboard coordinates
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] Pathpoint to transform
 */
PUBLIC_DECL void TransformInnerPathToPasteboard(const IPMUnknown * pUnknown, PMPathPoint * pt);


/**	Transform a rectangle from Pasteboard coordinates to the inner coordinates of a pageitem
	@param pUnknown [IN] any interface on the pageitem
	@param r [IN/OUT] Rectangle to transform
 */
PUBLIC_DECL void TransformPasteboardRectToInner(const IPMUnknown * pUnknown, PMRect * r);

/**	Transform a rectangle from inner coordinates to pasteboard coordinates
	@param pUnknown  any interface on the pageitem
	@param r Rectangle to transform
*/
PUBLIC_DECL void TransformInnerRectToPasteboard(const IPMUnknown * pUnknown, PMRect * r);

// These are useful for rotating a rectangle and then rebounding the points to find
// the bounding box of the transformed object

/**	Transform a collection of 4 points from Pasteboard coordinates to the inner coordinates of a pageitem
	@param pUnknown [IN] any interface on the pageitem
	@param poly [IN/OUT]ploygon to transform
 */
PUBLIC_DECL void TransformPasteboardPolyToInner(const IPMUnknown * pUnknown, PMPolygon4 * poly);

/**	Transform a collection of 4 points from the inner coordinates of a pageitem to pasteboard coordinates
	@param pUnknown [IN] any interface on the pageitem
	@param poly [IN/OUT] polygon to transform
 */
PUBLIC_DECL void TransformInnerPolyToPasteboard(const IPMUnknown * pUnknown, PMPolygon4 * poly);


//
// Parent <--> Pasteboard
//


/**	Transform a point from Pasteboard coordinates to the coordinates of a pageitem's parent
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] point to be transformed
 */
PUBLIC_DECL void TransformPasteboardPointToParent(const IPMUnknown * pUnknown, PMPoint * pt);

/**	Transform a point from the coordinates of a pageitem's parent to pasteboard coordinates
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] point to be transformed
 */
PUBLIC_DECL void TransformParentPointToPasteboard(const IPMUnknown * pUnknown, PMPoint * pt);


/**	Transform a distance from Pasteboard coordinates to the coordinates of a pageitem's parent
	@param pUnknown [IN] any interface on the pageitem
	@param delta [IN/OUT] Distance represented as PMPoint.X() and Y()
 */
PUBLIC_DECL void PasteboardToParentDelta(const IPMUnknown * pUnknown, PMPoint * delta);


/**	Transform a path point from Pasteboard coordinates to the coordinates of a pageitem's parent
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] Pathpoint to be transformed
 */
PUBLIC_DECL void TransformPasteboardPathToParent(const IPMUnknown * pUnknown, PMPathPoint * pt);

/**	Transform a path point from the coordinates of a pageitem's parent to Pasteboard coordinates
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] Pathpoint to be transformed
 */
PUBLIC_DECL void TransformParentPathToPasteboard(const IPMUnknown * pUnknown, PMPathPoint * pt);


/**	Transform a rectangle from Pasteboard coordinates to the coordinates of a pageitem's parent
	@param pUnknown [IN] any interface on the pageitem
	@param r [IN/OUT] rectangle to be transformed
 */
PUBLIC_DECL void TransformPasteboardRectToParent(const IPMUnknown * pUnknown, PMRect * r);

/**	Transform a rectangle from the coordinates of a pageitem's parent to Pasteboard coordinates
	@param pUnknown [IN] any interface on the pageitem
	@param r [IN/OUT] rectangle to be transformed
 */
PUBLIC_DECL void TransformParentRectToPasteboard(const IPMUnknown * pUnknown, PMRect * r);

// These are useful for rotating a rectangle and then rebounding the points to find
// the bounding box of the transformed object

/**	Transform a collection of 4 points from Pasteboard coordinates to the coordinates of a pageitem's parent
	@param pUnknown [IN] any interface on the pageitem
	@param poly [IN/OUT] polygon to be transformed
 */
PUBLIC_DECL void TransformPasteboardPolyToParent(const IPMUnknown * pUnknown, PMPolygon4 * poly);

/**	Transform a collection of 4 points from the coordinates of a pageitem's parent to pasteboard coordinates
	@param pUnknown [IN] any interface on the pageitem
	@param poly [IN/OUT] polygon to be transformed
 */
PUBLIC_DECL void TransformParentPolyToPasteboard(const IPMUnknown * pUnknown, PMPolygon4 * poly);

//
// Inner <--> Spread
//


/**	Transform a point from spread coordinates to the inner coordinates of a pageitem
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] point to transform
 */
PUBLIC_DECL void TransformSpreadPointToInner(const IPMUnknown * pUnknown, PMPoint * pt);

/**	Transform a point from the inner coordinates of a pageitem to spread coordinates
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] point to transform
 */
PUBLIC_DECL void TransformInnerPointToSpread(const IPMUnknown * pUnknown, PMPoint * pt);


/**	Transform a path point from spread coordinates to the inner coordinates of a pageitem
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] PathPoint (point with directions)
 */
PUBLIC_DECL void TransformSpreadPathToInner(const IPMUnknown * pUnknown, PMPathPoint * pt);

/**	Transform a path point from the inner coordinates of a pageitem to spread coordinates
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] Pathpoint to transform
 */
PUBLIC_DECL void TransformInnerPathToSpread(const IPMUnknown * pUnknown, PMPathPoint * pt);


/**	Transform a rectangle from spread coordinates to the inner coordinates of a pageitem
	@param pUnknown [IN] any interface on the pageitem
	@param r [IN/OUT] Rectangle to transform
 */
PUBLIC_DECL void TransformSpreadRectToInner(const IPMUnknown * pUnknown, PMRect * r);

/**	Transform a rectangle from inner coordinates to spread coordinates
	@param pUnknown  any interface on the pageitem
	@param r Rectangle to transform
*/
PUBLIC_DECL void TransformInnerRectToSpread(const IPMUnknown * pUnknown, PMRect * r);

// These are useful for rotating a rectangle and then rebounding the points to find
// the bounding box of the transformed object

/**	Transform a collection of 4 points from spread coordinates to the inner coordinates of a pageitem
	@param pUnknown [IN] any interface on the pageitem
	@param poly [IN/OUT]ploygon to transform
 */
PUBLIC_DECL void TransformSpreadPolyToInner(const IPMUnknown * pUnknown, PMPolygon4 * poly);

/**	Transform a collection of 4 points from the inner coordinates of a pageitem to spread coordinates
	@param pUnknown [IN] any interface on the pageitem
	@param poly [IN/OUT] polygon to transform
 */
PUBLIC_DECL void TransformInnerPolyToSpread(const IPMUnknown * pUnknown, PMPolygon4 * poly);


//
// Parent <--> Spread
//


/**	Transform a point from spread coordinates to the coordinates of a pageitem's parent
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] point to be transformed
 */
PUBLIC_DECL void TransformSpreadPointToParent(const IPMUnknown * pUnknown, PMPoint * pt);

/**	Transform a point from the coordinates of a pageitem's parent to spread coordinates
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] point to be transformed
 */
PUBLIC_DECL void TransformParentPointToSpread(const IPMUnknown * pUnknown, PMPoint * pt);



/**	Transform a path point from spread coordinates to the coordinates of a pageitem's parent
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] Pathpoint to be transformed
 */
PUBLIC_DECL void TransformSpreadPathToParent(const IPMUnknown * pUnknown, PMPathPoint * pt);

/**	Transform a path point from the coordinates of a pageitem's parent to spread coordinates
	@param pUnknown [IN] any interface on the pageitem
	@param pt [IN/OUT] Pathpoint to be transformed
 */
PUBLIC_DECL void TransformParentPathToSpread(const IPMUnknown * pUnknown, PMPathPoint * pt);


/**	Transform a rectangle from spread coordinates to the coordinates of a pageitem's parent
	@param pUnknown [IN] any interface on the pageitem
	@param r [IN/OUT] rectangle to be transformed
 */
PUBLIC_DECL void TransformSpreadRectToParent(const IPMUnknown * pUnknown, PMRect * r);

/**	Transform a rectangle from the coordinates of a pageitem's parent to spread coordinates
	@param pUnknown [IN] any interface on the pageitem
	@param r [IN/OUT] rectangle to be transformed
 */
PUBLIC_DECL void TransformParentRectToSpread(const IPMUnknown * pUnknown, PMRect * r);

// These are useful for rotating a rectangle and then rebounding the points to find
// the bounding box of the transformed object

/**	Transform a collection of 4 points from spread coordinates to the coordinates of a pageitem's parent
	@param pUnknown [IN] any interface on the pageitem
	@param poly [IN/OUT] polygon to be transformed
 */
PUBLIC_DECL void TransformSpreadPolyToParent(const IPMUnknown * pUnknown, PMPolygon4 * poly);

/**	Transform a collection of 4 points from the coordinates of a pageitem's parent to spread coordinates
	@param pUnknown [IN] any interface on the pageitem
	@param poly [IN/OUT] polygon to be transformed
 */
PUBLIC_DECL void TransformParentPolyToSpread(const IPMUnknown * pUnknown, PMPolygon4 * poly);


//
// Inner <--> Parent
//




/**	Transform a rectangle from inner coordinates to Parent coordinates. 
	This is just a convenience method for using an IPMUnknown to get to an
	associated ITransform and call its InnerToParent method. Note the returned
	rect is not necessarily normalized, so depending on client needs, you may want to
	call Normalize on the returned PMRect.
	@param pUnknown [IN] any interface on the pageitem
	@param r [IN/OUT] Rectangle to be transformed
 */
PUBLIC_DECL void TransformInnerPointToParent( const IPMUnknown* pUnknown, PMPoint * pt); //t_TransformPoint
PUBLIC_DECL void TransformParentPointToInner( const IPMUnknown* pUnknown, PMPoint * pt); //t_InverseTransformPoint
PUBLIC_DECL void TransformInnerRectToParent( const IPMUnknown* pUnknown, PMRect * r); //t_TransformRect
PUBLIC_DECL void TransformParentRectToInner( const IPMUnknown* pUnknown, PMRect * r); //t_InverseTransformRect
PUBLIC_DECL void TransformInnerPolyToParent( const IPMUnknown* pUnknown, PMPolygon4 * poly); //t_TransformPolygon4
PUBLIC_DECL void TransformParentPolyToInner( const IPMUnknown* pUnknown, PMPolygon4 * poly); //t_InverseTransformPolygon4

//
// Query matrix functions
//

PUBLIC_DECL PMMatrix InnerToOuterMatrix( const Transform::CoordinateSpace& coordinateSpace, const IPMUnknown * pUnknown );


/**	Get the InnerToPasteboardMatrix for a pageitem.
	@param pUnknown [IN] any interface on the pageitem
	@return PMMatrix [OUT] the matrix required to transform the object (a page item supporting ITransform) 
	from inner coordinates to PasteBoard coordinates.
 */
PUBLIC_DECL PMMatrix InnerToPasteboardMatrix(const IPMUnknown * pUnknown);
	

/**	Get the ParentToPasteboardMatrix for a pageitem.
	@param pUnknown [IN] any interface on the pageitem
	@return the matrix required to transform the object (a page item supporting ITransform) 
	from parent coordinates to PasteBoard coordinates.
 */
PUBLIC_DECL PMMatrix ParentToPasteboardMatrix( const IPMUnknown* pUnknown);


/**	Get the InnerToSpreadMatrix for a pageitem.
	@param pUnknown [IN] any interface on the pageitem
	@return PMMatrix [OUT] the matrix required to transform the object (a page item supporting ITransform) 
	from inner coordinates to spread coordinates.
 */
PUBLIC_DECL PMMatrix InnerToSpreadMatrix(const IPMUnknown * pUnknown);

/**	Get the ParentToSpreadMatrix for a pageitem.
	@param pUnknown [IN] any interface on the pageitem
	@return the matrix required to transform the object (a page item supporting ITransform) 
	from parent coordinates to spread coordinates.
 */
PUBLIC_DECL PMMatrix ParentToSpreadMatrix( const IPMUnknown* pUnknown);




/**	Get the InnerToParentMatrix for a pageitem.
	@param pUnknown [IN] any interface on the pageitem
	@return the matrix required to transform the object (a page item supporting ITransform) 
	from inner coordinates to parent coordinates.
*/
PUBLIC_DECL PMMatrix InnerToParentMatrix(const IPMUnknown * pUnknown);


/**	Calculate the Inner to arbitrary parent tranform Matrix for a pageitem. The matrix that represents 
	the transform from inner space to the space of the child of pParent. 
	For example, let's say I wanted the matrix that goes from pageitem A up to and
	including the layer it is on.  The syntax is 
	InnerToArbitraryParentMatrix (resultingMatrix, IPMUnknown* pStart, IHierarchy* pSpread)
	This tells the function to stop concatenating matrices when it reaches the spread.  The
	matrix does NOT include pParent. 
	@param resultMat [OUT] resulting Matrix to return 
	@param pUnknown [IN] any interface on the pageitem
	@param pParent [IN] a parent item.
 */
PUBLIC_DECL void InnerToArbitraryParentMatrix( PMMatrix* resultMat, const IPMUnknown* pUnknown, const IHierarchy* pParent);
	


/** Compute for each item in 'pageItems', the 'coordinateSpace' coordinates of the location specified by 'location'.
    For example, 
		K2Vector<PMPoint> corner;
		ResolveLocation( UIDList(item), Transform::ParentCoordinates(), Transform::InnerLocation(0,0), &corner);
	In this example, corner[0] will contain the location of the origin in inner coordinates in item's parent coordinate system.
	See TransformTypes.h for a description of the full generality of the TransformOrigin data type.
	@param pageItems [IN] the page items of interest. (may contain UIDs for spreads and pages as well) 
	@param coordinateSpace [IN] the coordinate space of the returned locations
	@param location [IN] the location of interest.
	@param resolvedLocation [OUT] the resulting list of resolved locations--one for each item.
*/

PUBLIC_DECL void ResolveLocation( const UIDList* pageItems, const Transform::CoordinateSpace& coordinateSpace,
	const Transform::TransformOrigin& location, K2Vector<PMPoint>* resolvedLocation);



#pragma export off

#endif
