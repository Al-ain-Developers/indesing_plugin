//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IBaseHandler.h $
//  
//  Owner: Rich Gartland
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
#ifndef __IBASEHANDLER__
#define __IBASEHANDLER__

#include "IPMUnknown.h"
#include "IShape.h"

#include "GraphicsID.h"

class GraphicsData;
class IShape;
class IBaseVisitor;
class IVisitorHelper;

/** An interface class used in conjunction with IBaseVisitor and IVisitorHelper, IBaseHandler 
	accomplishes item-specific tasks during a traversal (or visitation) of a structure of connected
	nodes -- typically (but not limited to) pageitems on a spread.  As the visitor traverses the
	structure, it invokes the appropriate method in the handler to accomplish the task for the
	current node.  Using a separate handler is an extension of the visitor design pattern presented
	in Gamma, et al.
	
	The separation of handling the "problem" from the particulars of node traversal allows, for 
	instance, the same form of traversal to be used for several problem (or "handling") solutions.
	For instance, InDesign uses this visitor/handler scheme for hit-testing, but it could (though
	presently does not) use the same visitor and a different handler to support pageitem drawing.

	NOTE: It is the HandleXXX routine's responsibility to cause visitation of the item's children by
	calling theVisitor->VisitChildren(pVisitable), if it is desired that the child nodes be
	processed.  If for whatever reason the handler decides the children do not need visitation
	(say in the case of the handler's task already being accomplished within the HandleXXX routine), 
	it may simply return without visiting the children. 

	FURTHER NOTE: Third-party-created pageitems that are not derived from built-in InDesign page item bosses must contain
	an IVisitorHelper interface on the page item boss in order for hit-testing to be supported for the item.  
	Also, HandleXXX routines aren't defined for these pageitems in IBaseHandler, so
	these should be provided by custom implementations that are added-in to the kPtrHitTestHandlerBoss.  
	The kPtrHitTestHandlerBoss is the base boss for InDesign hit-testing; several other boss 
	classes derive from it.

	The handler mechanism can be extended to support a new node, by adding-in a new interface to the handler
	boss for the task or problem being handled.  Such an interface, say for a node called MyNode, would
	contain a HandleMyNode() routine, along these lines:
	<pre>
	bool16 MyNodeHandlerImpl::HandleMyNode(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor)
	{
		bool16 bDone = kFalse;
		// Whatever the task to perform, now is the time to perform it on this node, if the task
		// should be performed before performing it on the node's children.  Set bDone to kTrue
		// if no further handling should be done.
		// ...
		//
		if ( !bDone )
		{	
			// Not done, so visit the children
			bDone = theVisitor->VisitChildren(pVisitable);
			// If, after visiting the children, we have more to do, do it here
			}
		} 
		// If there is more data to return to caller than bDone, put it on an interface that has
		// been added-in to the handler boss.  The code that started this visitor/handler traversal
		// (see sample code in IVisitorHelper.h) can retrieve it there.

		return bDone;
	}

	</pre>

	@see IBaseVisitor
	@see IVisitorHelper
	*/
class IBaseHandler : public IPMUnknown
{
	public:
		/** Initialize the handler with the graphics data and initial IShape -- for instance, 
			setting up transform, doing gsave, etc. -- prior to handler invocation
			@param theGD IN GraphicsData pointer
			@param theShape IN IShape pointer for the initial item
		*/
		virtual void InitHandler(GraphicsData* theGD, IShape* theShape) = 0;

		/** Perform post-handling such as grestore, releasing pointers, etc.
		*/
		virtual void TerminateHandler(void) = 0;

		/** Get the target rectangle used by the handler.
			@return PMRect in pasteboard coordinates
		*/
		virtual const PMRect GetHandlerIntersectionRect(void) const = 0;

		/** Get the graphics data pointer for the handler
			@return GraphicsData* passed into InitHandler
		*/
		virtual const GraphicsData* GetHandlerGraphicsDataPtr(void) const = 0;

		/** Handle a spread item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleSpread(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle a spread layer item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleSpreadLayer(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle an inline pageitem
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleInlineItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle a spline, or CGraphicFrameShape item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleSplineItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle a multicolumn frame item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleMultiColumnFrameItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle a text frame (a child of multicolumn frame item)
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleFrameItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle a group item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleGroupItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle a guide item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleGuideItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle a page
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandlePage(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle an image
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleImageItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle an embedded HTML item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleHTMLItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle an EPS text item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleEPSTextItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle an EPS item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleEPSItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle a PICT item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandlePICTItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle a Windows metafile item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleWMFItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle a PDF item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandlePDFItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle a Text on a Path item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleTOPItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle an owned item -- that is, owned by a text frame
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleOwnedItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle an IWaxAnchoredElement, such as an anchored graphic
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleWaxAnchoredElementItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle a parcel -- not really a pageitem (such as a line of text or a table cell)
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleParcelItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;

		/** Handle an item of unknown type (provides generic handling)
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleUnknownItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor) = 0;
};

#endif
