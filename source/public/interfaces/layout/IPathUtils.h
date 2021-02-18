//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPathUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IPathUtils__
#define __IPathUtils__

#include "GenericID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "INewPageItemCmdData.h"
#include "TransformTypes.h"		// CoordinateSpace
#include "PMPathPoint.h"
#include "PMRect.h"
#include "UIDList.h"

/** Pageitem type for use in WhichKindOfPageItem() */
enum PMPageItemType {
	/** pageitem is point */
	kIsPoint,	
	/** pageitem is line */
	kIsLine,	
	/** pageitem is square */
	kIsSquare,			
	/** pageitem is rectangle */
	kIsRectangle,
	/** pageitem is circle */
	kIsCircle,
	/** pageitem is oval/ellipse */
	kIsOval,
	kIsEllipse = kIsOval,
	/** pageitem is a polygon */
	kIsPoly,
	/** pageitem is a path */
	kIsPath,
	/** pageitem is a compound path */
	kIsCompoundPath,
	/** pageitem is unknown */
	kPMUnknownType
};

class IPathGeometry;
class IHandleShape;
class IPathSelectionList;
class IPathSelectionSuite;
class PathSelectionList;
class ITransform;
class IHierarchy;


/** Utilities for working with paths.
	@ingroup layout_util
*/
class IPathUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPATHUTILS };

	/** @name Spline creation methods.

		These methods process commands.  Make sure to use a sequence to include them with other commands.
	*/
	//@{

	/** Creates a page item and fills out the points describing a rectangle. 
		@param parent [IN] The parent for this item (typically a layer).
		@param boundsRect [IN] Where the item should be positioned.
		@param attrType [IN] Type of graphic attributes to assign to the item.
		@param itemClass [IN] Boss class to use for new item. 
		@param bAllowDefaultStandoff [IN] Passed to INewPageItemCmdData::SetAllowDefaultStandOff() when the item
		is created.
		@param boundsSpace [IN] Specifies the coordinate space for the bounds.  Choices are 
		IGeometry::kPasteboardCoordinateSpace (default) or IGeometry::kInnerCoordinateSpace (which means
		the bounds are already in the coordinate space of the parent item).
		@param howToApplyObjStyle [IN] how to apply the object style @see INewPageItemCmdData::ObjectStyleApplication

		@return A UIDRef for the newly created item.

		@see INewPageItemCmdData.h for graphic attribute types.
	*/
	virtual UIDRef CreateRectangleSpline 
		(
			const UIDRef& parent,
			PMRect& boundsRect,
			INewPageItemCmdData::GraphicAttrType attrType,
			ClassID itemClass,
			bool16	bAllowDefaultStandOff = kTrue,
			const Transform::CoordinateSpace &boundsSpace = Transform::PasteboardCoordinates(),
			INewPageItemCmdData::ObjectStyleApplication howToApplyObjStyle = INewPageItemCmdData::kCommandAppliesObjectStyle
		) const = 0;

	/** Creates a page item and fills out the points describing a rectangle. 
		The classID used for the item is kSplineItemBoss.
		@param parent [IN] The parent for this item (typically a layer).
		@param boundsRect [IN] Where the item should be positioned.
		@param attrType [IN] Type of graphic attributes to assign to the item.
		@param bAllowDefaultStandoff [IN] Passed to INewPageItemCmdData::SetAllowDefaultStandOff() when the item
		is created.
		@param boundsSpace [IN] Specifies the coordinate space for the bounds.  Choices are 
		IGeometry::kPasteboardCoordinateSpace (default) or IGeometry::kInnerCoordinateSpace (which means
		the bounds are already in the coordinate space of the parent item).

		@return A UIDRef for the newly created item.

		@see INewPageItemCmdData.h for graphic attribute types.
	*/
	virtual UIDRef CreateRectangleSpline 
		(
			const UIDRef& parent,
			PMRect& boundsRect,
			INewPageItemCmdData::GraphicAttrType attrType,
			bool16	bAllowDefaultStandOff = kTrue,
			const Transform::CoordinateSpace &boundsSpace = Transform::PasteboardCoordinates()
		) const = 0;
		
	/** Creates a page item and fills out the points describing an oval. 
		The classID used for the item is kSplineItemBoss.
		@param parent [IN] The parent for this item (typically a layer).
		@param boundsRect [IN] Where the item should be positioned.
		@param attrType [IN] Type of graphic attributes to assign to the item.
		@param bAllowDefaultStandoff [IN] Passed to INewPageItemCmdData::SetAllowDefaultStandOff() when the item
		is created.
		@param boundsSpace [IN] Specifies the coordinate space for the bounds.  Choices are 
		IGeometry::kPasteboardCoordinateSpace (default) or IGeometry::kInnerCoordinateSpace (which means
		the bounds are already in the coordinate space of the parent item).

		@return A UIDRef for the newly created item.

		@see INewPageItemCmdData.h for graphic attribute types.
	*/
	virtual UIDRef CreateOvalSpline 
		(
			const UIDRef& parent,
			PMRect& boundsRect,
			INewPageItemCmdData::GraphicAttrType attrType,
			bool16	bAllowDefaultStandOff = kTrue,
			const Transform::CoordinateSpace &boundsSpace = Transform::PasteboardCoordinates()
		) const = 0;

	/** Creates a page item and fills out the points describing a line. 
		The classID used for the item is kSplineItemBoss.
		@param parent [IN] The parent for this item (typically a layer).
		@param pathPoints [IN] The start and end points for the line.
		@param attrType [IN] Type of graphic attributes to assign to the item.
		@param bAllowDefaultStandoff [IN] Passed to INewPageItemCmdData::SetAllowDefaultStandOff() when the item
		is created.
		@param boundsSpace [IN] Specifies the coordinate space for the points.  Choices are 
		IGeometry::kPasteboardCoordinateSpace (default) or IGeometry::kInnerCoordinateSpace (which means
		the points are already in the coordinate space of the parent item).

		@return A UIDRef for the newly created item.

		@see INewPageItemCmdData.h for graphic attribute types.
	*/
	virtual UIDRef CreateLineSpline 
		(
			const UIDRef& parent,
			const PMPointList& pathPoints,
			INewPageItemCmdData::GraphicAttrType attrType,
			bool16	bAllowDefaultStandOff = kTrue,
			const Transform::CoordinateSpace &boundsSpace = Transform::PasteboardCoordinates()
		) const = 0;
		
	/** Creates a page item and fills out the points describing an arbitrary spline shape. 
		The classID used for the item is kSplineItemBoss.
		@param parent [IN] The parent for this item (typically a layer).
		@param pathPointList [IN] The path points for the spline.
		@param attrType [IN] Type of graphic attributes to assign to the item.
		@param bAllowDefaultStandoff [IN] Passed to INewPageItemCmdData::SetAllowDefaultStandOff() when the item
		is created.
		@param bClosedPath [IN] kTrue to create a closed path.
		@param boundsSpace [IN] Specifies the coordinate space for the points.  Choices are 
		IGeometry::kPasteboardCoordinateSpace (default) or IGeometry::kInnerCoordinateSpace (which means
		the points are already in the coordinate space of the parent item).

		@return A UIDRef for the newly created item.

		@see INewPageItemCmdData.h for graphic attribute types.
	*/
	virtual UIDRef CreateSpline 
		(
			const UIDRef& parent,
			const PMPathPointList& pathPointList,
			INewPageItemCmdData::GraphicAttrType attrType,
			bool16	bAllowDefaultStandOff = kTrue,
			bool16  bClosedPath = kTrue,
			const Transform::CoordinateSpace &boundsSpace = Transform::PasteboardCoordinates()
		) const = 0;
		
	/** Creates a page item and fills out the points describing a regular spline shape. 
		The classID used for the item is kSplineItemBoss.
		@param parent [IN] The parent for this item (typically a layer).
		@param boundsRect [IN] The bounds for the item.
		@param numSides [IN] The number of sides (or points, if using a non-zero starInset) for the polygon.
		@param starInset [IN] The amount of "star inset," or depth of the inset between points, as a percentage
		of the circumscribing circle's radius (0-100).  A value of zero results in no inset.
		@param attrType [IN] Type of graphic attributes to assign to the item.
		@param bAllowDefaultStandoff [IN] Passed to INewPageItemCmdData::SetAllowDefaultStandOff() when the item
		is created.
		@param boundsSpace [IN] Specifies the coordinate space for the bounds.  Choices are 
		IGeometry::kPasteboardCoordinateSpace (default) or IGeometry::kInnerCoordinateSpace (which means
		the bounds are already in the coordinate space of the parent item).

		@return A UIDRef for the newly created item.

		@see INewPageItemCmdData.h for graphic attribute types.
	*/
	virtual UIDRef CreateRegPolySpline 
		(
			const UIDRef& parent,
			PMRect& boundsRect,
			int32 numSides,
			int32 starInset,
			INewPageItemCmdData::GraphicAttrType attrType,
			bool16	bAllowDefaultStandOff = kTrue,
			const Transform::CoordinateSpace &boundsSpace = Transform::PasteboardCoordinates()
		) const = 0;
	//@}

	/** @name Path-making functions */
	//@{
	/** Make a line path.
		@param iPathGeometry [IN] Pointer to IPathGeometry to contain the path.
		@param pathPoints [IN] List of points for the path.
	*/
	virtual void MakeLinePath 
		(
			IPathGeometry* iPathGeometry,
			const PMPointList& pathPoints
		) const = 0;


	/** Make a rectangle path.
		@param iPathGeometry [IN] Pointer to IPathGeometry to contain the path.
		@param boundsRect [IN] Bounds rectangle for the path.
	*/
	virtual void MakeRectanglePath 
		(
			IPathGeometry* iPathGeometry,
			const PMRect& boundsRect
		) const = 0;
		
	/** Make an oval path.
		@param iPathGeometry [IN] Pointer to IPathGeometry to contain the path.
		@param boundsRect [IN] Bounds rectangle for the path.
	*/
	virtual void MakeOvalPath 
		(
			IPathGeometry* iPathGeometry,
			const PMRect& boundsRect
		) const = 0;
		
	/** Make a regular polygon path.
		@param iPathGeometry [IN] Pointer to IPathGeometry to contain the path.
		@param boundsRect [IN] Bounds rectangle for the path.
		@param numSides [IN] The number of sides (or points, if using a non-zero starInset) for the polygon.
		@param starInset [IN] The amount of "star inset," or depth of the inset between points, as a percentage
		of the circumscribing circle's radius (0-100).  A value of zero results in no inset.
	*/
	virtual void MakeRegPolyPath 
		(
			IPathGeometry* iPathGeometry,
			const PMRect& boundsRect,
			int32 numSides,
			int32 starInset
		) const = 0;
	
	/** Make an arbitrary spline path.
		@param iPathGeometry [IN] Pointer to IPathGeometry to contain the path.
		@param pathPointList [IN] List of points for the path.
		@param bClosePath [IN] kTrue to create a closed path.
	*/
	virtual void MakeSplinePath 
		(
			IPathGeometry* iPathGeometry,
			const PMPathPointList& pathPointList,
			bool16 bClosePath = kTrue
		) const = 0;

	/** Make a list of points describing a regular polygon that fits inside a 100-unit circle, with optional star inset.
		@param polyPts [IN] The list to receive the points.
		@param numSides [IN] The number of sides (or points, if using a non-zero starInset) for the polygon.
		@param starInset [IN] The amount of "star inset," or depth of the inset between points, as a percentage
		of the circumscribing circle's radius (0-100).  A value of zero results in no inset.
	*/
	virtual void MakeUnitCirclePolygon
		(
			PMPointList& polyPts,
			int32 numSides,
			int32 starInset
		) const = 0;
		
	//@}

	/** Compute the default left and right direction points for a given PMPathPoint.
		@param iPathGeometry [IN] Pointer to IPathGeometry to contain the path.
		@param pathPoint [IN] an anchor PMPathPoint, must be on the iPathGeometry
		@param pathIndex [IN] Which subpath on iPathGeometry to use.
		@param pointIndex [IN] Which index the pathPoint is on its subpath.
		@param leftDirPt [OUT] a computed left direction point
		@param rightDirPt [OUT] a computed right direction point
		@return kTrue if direction points can be calculated, kFalse if not.
	*/
	virtual bool16 CalculateDirectionPoints(const IPathGeometry* iPathGeometry, const PMPathPoint& thePoint, const int32 pathIndex, const int32 pointIndex, PMPoint& leftDirPt, PMPoint& rightDirPt) const = 0;

	/** @name Type-of-pageitem functions */
	//@{

	/** Tell whether the path is a square.
		@param iPathGeometry [IN] IPathGeometry interface for the path in question.
		@return kTrue for a square path.
	*/
	virtual bool16 IsSquare( const IPathGeometry* iPathGeometry ) const = 0;

	/** Tell whether the path is a rectangle.
		@param iPathGeometry [IN] IPathGeometry interface for the path in question.
		@return kTrue for a rectangular path.
	*/
	virtual bool16 IsRectangle( const IPathGeometry* iPathGeometry ) const = 0;

	/** Tell whether the path is a single point.
		@param iPathGeometry [IN] IPathGeometry interface for the path in question.
		@return kTrue for an single point path.
	*/
	virtual bool16 IsPoint( const IPathGeometry* iPathGeometry ) const = 0;

	/** Tell whether the path is a line.
		@param iPathGeometry [IN] IPathGeometry interface for the path in question.
		@return kTrue for a line path.
	*/
	virtual bool16 IsLine( const IPathGeometry* iPathGeometry ) const = 0;

	/** Tell whether the path is an oval.
		@param iPathGeometry [IN] IPathGeometry interface for the path in question.
		@return kTrue for an oval path.
	*/
	virtual bool16 IsOval( const IPathGeometry* iPathGeometry ) const = 0;

	/** Tell whether the path is a circle.
		@param iPathGeometry [IN] IPathGeometry interface for the path in question.
		@return kTrue for a circular path.
	*/
	virtual bool16 IsCircle( const IPathGeometry* iPathGeometry ) const = 0;

	/** Tell whether the path is a polygon.
		@param iPathGeometry [IN] IPathGeometry interface for the path in question.
		@return kTrue for a polygonal path (closed path with only line segments).
	*/
	virtual bool16 IsPolygon( const IPathGeometry* iPathGeometry ) const = 0;

	/** Tell whether the path is a compound path.
		@param iPathGeometry [IN] IPathGeometry interface for the path in question.
		@return kTrue for if there are >1 paths.
	*/
	virtual bool16 IsCompoundPath( const IPathGeometry* iPathGeometry ) const = 0;

	/** Tells the type of pageitem for a path.
		@param iPathGeometry [IN] IPathGeometry interface for the path in question.
		@return PMPageItemType for the pageitem of iPathGeometry.

		@see PMPageItemType
	*/
	virtual PMPageItemType WhichKindOfPageItem( const IPathGeometry* iPathGeometry ) const = 0;
	//@}


	/** @name Selection-related functions */
	//@{
	/** Append a portion of a pageitem's path to a list of point selectors.
		@param pathGeom [IN] IPathGeometry pointer for the pageitem.
		@param pathIndex [IN] Which subpath to retrieve.
		@param pts [IN/OUT] The list the subpath's point selectors are appended to.
	*/
	virtual void AppendPathPointSelectors( IPathGeometry* pathGeom, int32 pathIndex, PointSelectorList& pts ) const = 0;

	/** Append all of a pageitem's path to a list of point selectors.
		@param pathGeom [IN] IPathGeometry pointer for the pageitem.
		@param pts [IN/OUT] The list the path's point selectors are appended to.
	*/
	virtual void AppendAllPathPointSelectors( IPathGeometry* pathGeom, PointSelectorList& pts ) const = 0;

	/** Tell whether a pageitem could support a path selection.
		@param pageItem [IN] Interface pointer for pageitem.
		@return kTrue item could conceivably support a path selection.
	*/
	virtual bool16 IsPathSelectable( const IPMUnknown* pageItem ) const = 0;

	/** Tell whether a pageitem could support a path selection.
		@param pageItem [IN] UIDRef for pageitem.
		@return kTrue item could conceivably support a path selection.
	*/
	virtual bool16 IsPathSelectable( const UIDRef& pageItem ) const = 0;

	/** Appends non-path-selectable items to a list. Note that if the selectionList contains 
		parent non-path items (e.g. groups)	and itemList as passed in contains all the child items, 
		the child items will be removed. Don't want parent and child items in same list.
		@param selectionList [IN] The input UIDList of pageitems.
		@param itemList [IN/OUT] The UIDList onto which to append non-path-selectable items. May have child items removed as well.
	*/
	virtual void AppendNonPathSelectables( const UIDList& selectionList, UIDList& itemList ) const = 0;

	/** Filter out any path selectable page items that currently have no path components selected.
		@param pathSelectionSuite [IN] IPathSelectionSuite interface from current selection.
		@param itemList [IN/OUT] UIDList of pageitems to filter.  Items which are path-selectable but which currently
		have no path components selected are removed from this list on output.
	*/
	virtual void FilterUnselectedPathObjects( const IPathSelectionSuite* pathSelectionSuite, UIDList& itemList ) const = 0;

	/** Filter out non-path selectable page items.
		@param itemList [IN/OUT] UIDList of items to filter.  Items which are not path-selectable are removed on output.
	*/
	virtual void FilterNonPathSelectables( UIDList& itemList ) const = 0;

	/** Tell whether all the path points of a pageitem are represented in a path selection list.
		@param pathSelectionList [IN] The IPathSelectionList interface to check.
		@param pathGeom [IN] The IPathGeometry interface for the pageitem.
		@return kTrue if all path points of the item are present in pathSelectionList.
	*/
	virtual bool16 AllPointsOnObjectSelected( IPathSelectionList* pathSelectionList, IPathGeometry* pathGeom ) const = 0;

	/** Tell whether all the path points of a particular subpath of a pageitem are represented in a path selection list.
		@param pathSelectionList [IN] The IPathSelectionList interface to check.
		@param pathGeom [IN] The IPathGeometry interface for the pageitem.
		@param pathIndex [IN] The index of the subpath to check in the pageitem.
		@return kTrue if all path points of the item's subpath are present in pathSelectionList.
	*/
	//virtual bool16 AllPointsOnPathSelected( IPathSelectionList* pathSelectionList, IPathGeometry* pathGeom, int32 pathIndex ) const = 0;

	virtual bool16 AllPointsOnObjectSelected( IPathGeometry* pathGeom, const PointSelectorList& pts ) const = 0;
	virtual bool16 AllPointsOnPathSelected( IPathGeometry* pathGeom, int32 pathIndex, const PointSelectorList& pts ) const = 0;

	//@}

	/** @name Other functions */
	//@{

	/** Get the bounding box for a polygonal path.
		@param polyPts [IN] The list of points for the path.
		@return The bounding rectangle for the points.
	*/
	virtual PMRect GetPolyPathBBox
		(
			const PMPointList& polyPts
		) const = 0;

	/** Query the IHandleShape interface for a pageitem.
		@param tryPathHandleShape [IN] kTrue to get IID_IPATHHANDLESHAPE interface; kFalse to get IID_IHANDLESHAPE.
		@param item [IN] UIDRef of the pageitem.
		@return IHandleShape interface pointer for the item.
	*/
	virtual IHandleShape* QueryHandleShape
		(
			bool16 tryPathHandleShape,
			const UIDRef& item
		) const = 0;

	/** Query the IHandleShape interface for a pageitem.
		@param tryPathHandleShape [IN] kTrue to get IID_IPATHHANDLESHAPE interface; kFalse to get IID_IHANDLESHAPE.
		@param iUnknown [IN] An interface pointer on the pageitem.
		@return IHandleShape interface pointer for the item.
	*/
	virtual IHandleShape* QueryHandleShape
		(
			bool16 tryPathHandleShape,
			IPMUnknown* iUnknown
		) const = 0;

	/** Tell whether any paths of an item are open.
		@param iPathGeometry [IN] IPathGeometry of the item to check.
		@return kTrue if any of the item's paths are open.
	*/
	virtual bool16 IsAnyPathOpen( const IPathGeometry* iPathGeometry ) const = 0;

	/** Validate a point selector against a pageitem.
		@param pathGeom [IN] IPathGeometry of the pageitem.
		@param handle [IN] PointSelector to validate.
		@return kTrue if the specified handle is an actual component in this pathGeom.
	*/
	virtual bool16 IsValidSelector( const IPathGeometry* pathGeom, const PointSelector& handle ) const = 0;

	/** Map point index to a visual index with respect to the user. 
		Takes transform (flip) into account.
		@param controlPtIndex [IN] The point to check.
		@param itemTransform [IN] The ITransform interface for the pageitem.
		@return The PointIndex corresponding to the point.
		@see PMRect.h for PointIndex values.
	*/
	virtual PMRect::PointIndex GetVisualPointIndex(const PointSelector& controlPtIndex, ITransform* itemTransform) const = 0;

	/** Fill in a UIDList containing the first level path-selectable items, given a hierarchy.
		Will navigate down groups. Used for group selection tool page item collection (option/alt + direct select tool).
		@param resultList [IN/OUT] A UIDList initialized with the database, to hold the results.
		@param hierarchy [IN] The IHierarchy interface for the item to start from.
	*/
	virtual void GetPathSelectableUIDList(UIDList* resultList, IHierarchy* hierarchy) = 0;
	//@}
};


#endif	// __IPathUtils__
