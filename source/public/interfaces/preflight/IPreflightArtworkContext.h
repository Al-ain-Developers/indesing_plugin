//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightArtworkContext.h $
//  
//  Owner: Matt Phillips
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

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"

class IPreflightArtworkShapeContext;
class IPreflightArtworkTextContext;
class IPreflightArtworkTableContext;
class IPreflightArtworkOPIContext;

/** This interface is used by rules that examine marking operations.

	This interface sits on the three artwork bosses: marks, groups, and context. It provides
	utilities for accessing the context in which any of those nodes exists.

	BACKGROUND

	An artwork node can be either a marking operation, a group (eg transparency group), or 
	a context node. The context node is the link to an InDesign object that the marking or
	group is part of. For example we have a context for shape, and all marking operations
	that comprise the shape are under that context node. An example hierarchy might be:

		Context (Shape): Spread
			Context (Shape): Group Page Item
				Context (Shape): Graphic Frame
					Context (Shape): Graphic Frame / Subpart = Native Fill
						Mark: Fill
					Context (Shape): Image Page Item
						Mark: Image
					Context (Shape): Graphic Frame / Subpart = Native Stroke
						Mark: Stroke

	TYPICAL APPLICATION

	Normally this is used when looking at marking operations and you want to know what the
	marking operation is part of. For example you might want to know what shape it's part
	of, or what wax run it's part of (or just *whether* it's part of either of those). 

	For example, in  if you want to know whether a given image marking operation is part of an
	image or a PDF you could use code like this:

		virtual void MyRuleVisitor::Visit(IPreflightVisitInfo* iVisit)
		{
			InterfacePtr<IPreflightObject> iObj(iVisit->QueryObject());

			if (iVisit->GetObjectID().GetClass() == kPreflightOM_ArtworkMark)
			{
				InterfacePtr<IPreflightArtworkContext> iContext(iObj, UseDefaultIID());
				InterfacePtr<IPreflightArtworkShapeContext> iShapeContext(iContext->QueryParentShapeContext());

				if (iShapeContext)
				{
					InterfacePtr<IShape> iShape(iShapeContext->GetShapeRef());
					// Use iShape operations, interface queries, IPageItemTypeUtils, etc., to 
					// examine the object
					// ...
				}
			}
		}

	Another common example is when you want to know if a marking operation is part of drawing
	a proxy, as opposed to "real" artwork:

		virtual void MyRuleVisitor::Visit(IPreflightVisitInfo* iVisit)
		{
			InterfacePtr<IPreflightObject> iObj(iVisit->QueryObject());

			if (iVisit->GetObjectID().GetClass() == kPreflightOM_ArtworkMark)
			{
				InterfacePtr<IPreflightArtworkContext> iContext(iObj, UseDefaultIID());
				if (iContext->GetShapeContextDepth(kPreflightOSP_GraphicProxy, kTrue))
				{
					// Yep, part of a proxy, so don't look at it.
					return;
				}
				// Not a proxy, so evaluate the marking operation.
				// ...
			}
		}


*/

class IPreflightArtworkContext : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTARTWORKCONTEXT };

	/** Get the total number of ancestor context nodes (not including this node). This method
		is used if you want to look at *all* contexts regardless of type, eg if you want to know
		whether there's a text context within a particular shape context.

		@param stopAtOne IN If true, stops as soon as it hits one match. More efficient if you're
			only interested in the presence of a node rather than the total number.
		@return The total number of parent/ancestor context nodes.
	*/
	virtual int32 GetContextDepth(bool stopAtOne = kFalse) const = 0;

	/** Get the total number of ancestor shape context nodes (not including this node). This does
		not consider other kinds of contexts. However, note that each shape context is both a 
		shape *and* a subpart so in some/most cases you'll find repeats. See class comments for
		an example of this.

		@param stopAtOne IN If true, stops as soon as it hits one match. More efficient if you're
			only interested in the presence of a node rather than the total number.
		@param subpartID IN The subpart you want to look for. kInvalidClass will match any.
		@return The total number of parent/ancestor context nodes.
	*/
	virtual int32 GetShapeContextDepth(ClassID subpartID = kInvalidClass, bool stopAtOne = kFalse) const = 0;

	/** Get the total number of ancestor text context nodes (not including this node). 

		@param stopAtOne IN If true, stops as soon as it hits one match. More efficient if you're
			only interested in the presence of a node rather than the total number.
		@return The total number of parent/ancestor context nodes.
	*/
	virtual int32 GetTextContextDepth(bool stopAtOne = kFalse) const = 0;

	/** Get the total number of ancestor table context nodes (not including this node). 

		@param stopAtOne IN If true, stops as soon as it hits one match. More efficient if you're
			only interested in the presence of a node rather than the total number.
		@return The total number of parent/ancestor context nodes.
	*/
	virtual int32 GetTableContextDepth(bool stopAtOne = kFalse) const = 0;

	/** Get the total number of ancestor OPI context nodes (not including this node). 

		@param stopAtOne IN If true, stops as soon as it hits one match. More efficient if you're
			only interested in the presence of a node rather than the total number.
		@return The total number of parent/ancestor context nodes.
	*/
	virtual int32 GetOPIContextDepth(bool stopAtOne = kFalse) const = 0;

	/** Query a context node that is a parent or ancestor of this one. This method matches any
		kind of context, so it's useful (along with GetContextDepth) at examining the entire
		context stack associated with a node.

		@param depth IN The depth to query; 0 means the immediate parent. Should be between
			0 and GetContextDepth() - 1.
		@return A refcounted context interface or nil if there is none at the requested depth.
			Typically you'd query from this interface for one of the specific context interfaces.
	*/
	virtual IPreflightArtworkContext* QueryParentContext(int32 depth = 0) const = 0;

	/** Query a shape context node that is a parent or ancestor of this one.

		@param depth IN The depth to query; 0 means the immediate parent. Should be between
			0 and GetShapeContextDepth() - 1.
		@return A refcounted shape context interface or nil if there is none at the requested depth.
	*/
	virtual IPreflightArtworkShapeContext* QueryParentShapeContext(int32 depth = 0) const = 0;

	/** Query a shape context node that is a parent or ancestor of this one and matches the
		specified subpart.

		@param subpartID IN The subpart in which you're interested. 0 matches any.
		@param depth IN The depth to query; 0 means the immediate parent. Should be between
			0 and GetShapeContextDepth(subpartID) - 1.
		@return A refcounted shape context interface or nil if there is none at the requested depth.
	*/
	virtual IPreflightArtworkShapeContext* QueryParentShapeContext(ClassID subpartID, int32 depth = 0) const = 0;

	/** Query a text context node that is a parent or ancestor of this one.

		@param depth IN The depth to query; 0 means the immediate parent. Should be between
			0 and GetTextContextDepth() - 1.
		@return A refcounted text context interface or nil if there is none at the requested depth.
	*/
	virtual IPreflightArtworkTextContext* QueryParentTextContext(int32 depth = 0) const = 0;

	/** Query a table context node that is a parent or ancestor of this one.

		@param depth IN The depth to query; 0 means the immediate parent. Should be between
			0 and GetTableContextDepth() - 1.
		@return A refcounted table context interface or nil if there is none at the requested depth.
	*/
	virtual IPreflightArtworkTableContext* QueryParentTableContext(int32 depth = 0) const = 0;

	/** Query an OPI context node that is a parent or ancestor of this one.

		@param depth IN The depth to query; 0 means the immediate parent. Should be between
			0 and GetOPIContextDepth() - 1.
		@return A refcounted OPI context interface or nil if there is none at the requested depth.
	*/
	virtual IPreflightArtworkOPIContext* QueryParentOPIContext(int32 depth = 0) const = 0;
};

