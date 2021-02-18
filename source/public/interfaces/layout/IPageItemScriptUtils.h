//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageItemScriptUtils.h $
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
#ifndef __IPageItemScriptUtils__
#define __IPageItemScriptUtils__

#include "GenericID.h"
#include "IPMUnknown.h"
#include "TransformTypes.h"
#include "Utils.h"

#include "PMPathPoint.h"
#include "ScriptData.h"
#include "IReferencePointData.h"

class IHierarchy;
class IScriptRequestData;
class ITextModel ;
class DOMAttributeValue;
class PMMatrix;

typedef K2Vector<UIDRef> UIDRefList ;

/** Utilities related to page item scripting.
	@ingroup layout_util
	@ingroup arch_script
*/
class IPageItemScriptUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGEITEMSCRIPTUTILS };

	typedef enum 
	{
		kParentOnly = 0,			// Always include the parents only
		kChildrenOnly,				// Always include the children only
		kParentAndChildren,			// Always include both the parents and the children
		kChildrenIfNotParent		// If the parent supports it, just get the parent. If not, look into the children
	} MatchingPIOption;

	/** Determine the type of a page item script object */
	virtual ScriptID GetPageItemType( const IScript* script ) const = 0;

	/** Count the number of page item children of the type specified by data->GetDesiredType() */
	virtual int32 CountPageItemChildren( IScript* parent, const IScriptRequestData* data ) const = 0;
	/** Retrieve the nth page item child of the type specified by data->GetDesiredType() */
	virtual UID GetNthPageItemChild( int32 piIndex, IScript* parent, const IScriptRequestData* data ) const = 0;	//0-based index
	/** Retrieve every page item child of the type specified by data->GetDesiredType() */
	virtual UIDList GetEveryPageItemChild( IScript* parent, const IScriptRequestData* data, bool16 allChildren = kFalse) const = 0;
	/** Retrieve the nth page item child of the type specified by data->GetDesiredType() */
	virtual ErrorCode GetNthPageItemChild( int32 piIndex, IScript* parent, const IScriptRequestData* data, ScriptList& objectList ) const = 0;	//0-based index
	/** Retrieve every page item child of the type specified by data->GetDesiredType() */
	virtual ErrorCode GetEveryPageItemChild( IScript* parent, const IScriptRequestData* data, ScriptList& objectList, bool16 allChildren = kFalse ) const = 0;
	
	/** Returns a list of all inline page items of the type specified by data->GetDesiredType() */
	virtual void GetListOfInlines( ITextModel* model, TextIndex start, TextIndex end, UIDList* itemList, const IScriptRequestData* data, bool16 checkLastCharacter = kTrue, bool16 allChildren = kFalse) const = 0;

	typedef ErrorCode (*CreatePageItemFunc)( IScriptRequestData* data, IScript* script, IPMUnknown* parent, const PMPointList& bounds, UIDRef& pageItem, const Transform::CoordinateSpace& boundsSpace ) ;
	virtual ErrorCode DoCreatePageItem( IScriptRequestData* data, IScript* script, CreatePageItemFunc callbackFunction ) const = 0 ;
	virtual ErrorCode PreparePageItemParent( IScriptRequestData* data, IPMUnknown* parent, UIDRef& parentRef ) const = 0;

	virtual UID GetComposedLayerUID(IHierarchy* pageItem, const RequestContext& context, bool16 useLastFrameIfOverset = kFalse) const = 0 ;
	virtual UID GetComposedSpreadUID(IHierarchy* pageItem, const RequestContext& context, bool16 useLastFrameIfOverset = kFalse) const = 0 ;

	virtual ErrorCode GetReferencePoint( IScript* pageItem, PMPoint* refPoint, IScriptRequestData* data = nil) const = 0;

	/** GetSpreadOffsetPoint takes in a page item and will return you the zero point offset 
		taking into account the ruler origin setting of the doc
		@param pageItem is the page item
		@param context is the script request context
		@param offset is the offset [out]
	*/
	virtual ErrorCode GetSpreadOffsetPoint(IScript* pageItem, const RequestContext& context, PMPoint& offset) const = 0;

	/** GetOffsetPoint takes a spread/master spread/page/page item/document and returns an offset in spread coordinates.
		It is used during creation of page items and placing of files and when no explicit location was provided.
		If you pass in a spread/master spread -> It returns you the zero point of the spread (not accounting for the ruler origin).
		If you pass in a page -> It returns you the top left corner of the page.
		If you pass in a page item -> It returns you the top left corner of the page item.
		If you pass in a document -> It returns you the  zero point of the spread (not accounting for the ruler origin) of the first spread.
	*/
	virtual ErrorCode GetOffsetPoint(IScript* script, IScriptRequestData* data, PMPoint& offset) const = 0;

	/** GetMeasurementPoint takes a list, a script data interface and script representing a parent
		It then extracts the x and y value of the point, coverting the values to points depending
		on the x and y unit of measure. The point variable gets populated with the proper value,
		taking into account whatever offset is needed based on the parent.
	*/
	virtual ErrorCode GetMeasurementPoint(ScriptListData& list, IScript* script, IScriptRequestData* data, PMPoint& point) const = 0;
	/** Similar to GetMeasurementPoint but doesn't add in the spread offset */
	virtual ErrorCode GetCoordinates( const ScriptData& scriptData, PMPoint& coordinates, IScript* script, const EngineContext& context ) const = 0 ;

	/** Returns kTrue if page item is not locked */
	virtual bool16 IsEditable( IPMUnknown* pageItem ) const = 0;
	virtual int32 FilterByGraphicAttribute( UIDList& piList, ClassID attr ) const = 0;

	virtual IScript* QueryPageItemParent( const IScript* script, const RequestContext& context ) const = 0;

	/** GetMatchingPageItems takes a ScriptList* of one or more page items and returns all the children (1 level deep only) of each
		page item that support the passed in iid. If includeParents is true, the resutling list will also includes page items in
		the passed in ScriptList that support the iid. */
	virtual ErrorCode GetMatchingPageItems(const RequestContext& context, ScriptList* inPageItems, ScriptList* outPageItems, PMIID iidToLookFor, MatchingPIOption whatToInclude) const = 0;

	virtual ErrorCode GetDefaultReferencePosition(const UIDList& itemList, IReferencePointData::ReferencePointPosition& refPosition) const = 0;
	virtual ErrorCode GetDefaultReferenceLocation(const UIDList& itemList, ReferencePointLocation& refLocation) const = 0;

	/** AccessItemGeometry is a routine which was defined in TextWrapScriptProvider and PageItemScriptProvider.  It is used
		to obtain or set the points in a page item's IPathGeometry, the PathBoundingBox in its IGeometry, its IGraphicBounds (if
		it is a graphic), and its ITransform.
		@param data - IN - Contains script data such as arguments for the various geometric commands.
		@param script - IN - Represents the page item
		@param applyToTextWrap - IN - if kTrue, the page items text wrap will be the focus of the operations.  Otherwise,
			the page item represented by 'script' will be the focus.
		@return kSuccess or an error code if failure.
	*/
	virtual ErrorCode AccessItemGeometry(IScriptRequestData* data, IScript* script, bool32 applyToTextWrap) = 0;

	/** AccessPathGeometry is a routine used by TextWrapScriptProvider and PageItemScriptProvider to obtain or set 
		the path geometry in a page item's IPathGeometry.
		This routine can be used for properies whose data type is a variable arry of kGeoPathTypeDefScriptElement.
		@param propID - IN - the ID of the corresponding property.
		@param data - IN/OUT - The event data representing the property.
		@param script - IN - Represents the page item
		@param applyToTextWrap - IN - if kTrue, the page item's text wrap will be the focus of the operations.  Otherwise,
			the page item represented by 'script' will be the focus.
		@return kSuccess or an error code if failure.
	*/
	virtual ErrorCode AccessPathGeometry(ScriptID propID, IScriptRequestData* data, IScript* script, bool32 applyToTextWrap) = 0;

	/** A routine to obtain or set the bounding box data in a page item's IGeometry.
		This routine can be used for properies whose data type is kRecBoundsTypeDefScriptElement.
		@param propID - IN - the ID of the corresponding property.
		@param data - IN/OUT - The event data representing the property.
		@param script - IN - Represents the page item
		@return kSuccess or an error code if failure.
	*/
	virtual ErrorCode AccessBoundingBox(ScriptID propID, IScriptRequestData* data, IScript* script) = 0;

	/** A routine to obtain or set the graphic bounds in a page item's IGraphicBounds.
		This routine can be used for properies whose data type is kRecBoundsTypeDefScriptElement.
		@param propID - IN - the ID of the corresponding property.
		@param data - IN/OUT - The event data representing the property.
		@param script - IN - Represents the page item
		@return kSuccess or an error code if failure.
	*/
	virtual ErrorCode AccessGraphicBounds(ScriptID propID, IScriptRequestData* data, IScript* script) = 0;

	/** GetItemLayerMatrix will return the item's transform matrix transformed to layer coordinates.
		@param item - IN - The item.
		@param m - OUT - The processed matrix.
		@return kSuccess or an error code if failure.
	*/
	virtual ErrorCode GetItemLayerMatrix(IPMUnknown *item, PMMatrix &m) const = 0;

	/** SetItemGeometryMatrix will replace the PMMatrix data stored in the caller's p_ItemGeometry data.
		@param m - IN - The new matrix.
		@param g - OUT - The value of the p_ItemGeometry property.
		@return kSuccess or an error code if failure.
	*/
	virtual ErrorCode SetItemGeometryMatrix(const PMMatrix &m, DOMAttributeValue &g) const = 0;

	/** AccessItemTransform is a routine which was defined in TextWrapScriptProvider and PageItemScriptProvider.  It is used
		to obtain its transform matrix.
		@param data - IN - Contains script data such as arguments for the various geometric commands.
		@param script - IN - Represents the page item
		@param applyToTextWrap - IN - if kTrue, the page items text wrap will be the focus of the operations.  Otherwise,
			the page item represented by 'script' will be the focus.
		@return kSuccess or an error code if failure.
	*/
	virtual ErrorCode AccessItemTransform(IScriptRequestData* data, IScript* script, bool32 applyToTextWrap) = 0;
};

#endif	// __IPageItemScriptUtils__
