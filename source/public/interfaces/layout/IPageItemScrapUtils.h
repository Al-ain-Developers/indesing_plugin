//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageItemScrapUtils.h $
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
#ifndef __IPageItemScrapUtils__
#define __IPageItemScrapUtils__

#include "GenericID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "K2Vector.h"
#include "PMString.h"
#include "PMRect.h"
#include "PathTypes.h"

class UIDList;
class ICommand;
class PathSelectionList;
class IHierarchy;
class IPageItemLayerData;
class IDocumentLayer;

/** Utilities related to page item scrap and duplicating page items.
	@ingroup layout_util
	@ingroup arch_scrap 
*/
class IPageItemScrapUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGEITEMSCRAPUTILS };

	virtual ICommand* GetDuplicatePageItemsCmd( const UIDList *pageItems, const PMPoint& offset, UIDRef parent, bool16 preserveLayers) const = 0;
	virtual ICommand* GetDuplicatePathPointsCmd( const UIDList *pageItems, const PathSelectionList* pathItems, K2Vector<PointSelectorList>* newPathItems, const PMPoint& offset, UIDRef parent, bool16 preserveLayers) const = 0;
	
	/**	Find the uid of the spread layer to put a duplicated item on. Used when Paste Remembers Layers is on.
		@param parentHier the hierarchy interface for the parent of the item being duplicated.
		@param searchName, the name of the layer the item being duplicated is on. 
		@param isGuideLayer pass kTrue if duplicating guides (kGuideItemBoss), otherwise use kFalse.
		@return UID the UID of the spread layer to duplicate the item on, kInvalidUID if a layer with that
				name is not present in the document.
		@see ILayerList.h
		@see ISpreadLayer.h
	 */
	virtual UID FindLayer(IHierarchy* parentHier, const PMString& searchName, bool16 isGuideLayer) const = 0;

	/** Create a layer with the given name in the document targetted by docRef, and using the data in layerData.
		Target layer will be created in same z-order position in target document as specified in layerData. Generally
		used internally by duplicate code to create matching destination layers as necessary. Only a layer is created,
		no content is copied.
		@param docRef a UIDRef to the target document
		@param layerName a pointer to the string to use for the name
		@param layerData an interface pointer containing information 
		@return a UIDRef to the created document layer.
		@see IPageItemLayerData.h
		@see IDocumentLayer.h
	*/
	virtual UIDRef MakeLayer(const UIDRef& docRef, PMString* layerName, const IPageItemLayerData* layerData) = 0;

	/** Create a layer in the target document with all the attributes of the source layer.
		Target layer will be created in same z-order position in target document as it is in source document.
		Generally internally by duplicate code to create matching destination layers as necessary.
		Only a layer is created, no content is copied.
		@param docRef a UIDRef to the target document
		@param sourceDocLayer an interface pointer to the IDocumentLayer to copy attributes from.
		@return a UIDRef to the created document layer.
		@see IDocumentLayer.h
	*/
	virtual UIDRef MakeLayer(const UIDRef& docRef, IDocumentLayer* sourceDocLayer) = 0;
};


#endif	// __IPageItemScrapUtils__
