//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IBaseVisitor.h $
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
#ifndef __IBASEVISITOR__
#define __IBASEVISITOR__

#include "IPMUnknown.h"
#include "IBaseHandler.h"
#include "IShape.h"

#include "GraphicsID.h"

class IDataBase;
class IBaseHandler;
class IVisitorHelper;

/** An interface class used in conjunction with IBaseHandler and IVisitorHelper, IBaseVisitor 
	accomplishes a traversal (or visitation) of an arbitrary structure of connected
	nodes -- typically (but not limited to) pageitems on a spread.  As the visitor traverses the
	structure, it uses each node's IVisitorHelper::Accept() routine to invoke the appropriate method 
	in the IBaseHandler to accomplish whatever task is required.  A depth-first traversal of the node
	structure is performed in the visitation scheme.
	
	Using a separate handler is an extension of the visitor design pattern presented
	in Gamma, et al, and allows the visitor scheme to be problem-independent.  That is, a generic
	visitor scheme for traversal can be married with any number of handler bosses, each doing a 
	specific task or solving a particular problem during the traversal.  An example of the use
	of the visitor/handler scheme in InDesign is hit-testing.
	
	NOTE: Third-party-created pageitems that are not derived from built-in InDesign page item bosses must contain
	an IVisitorHelper interface on the page item boss in order for hit-testing to be supported for the item.  
	Also, since VisitXXX routines aren't defined for these pageitems in IBaseVisitor,
	these should be provided by custom implementations that are added-in to the kBaseVisitorBoss.  

	InDesign's visitor capability can be extended to support new types of nodes by creating an interface,
	say IMyNodeVisitor, and adding it in to kBaseVisitorBoss.  It would contain a VisitMyNode routine, as
	follows:
	<pre>
	bool16  MyNodeVisitorImpl::VisitMyNode(IVisitorHelper* pVisitable)
	{
		bool16 bDone = kFalse;
		// Get the current handler by asking the base visitor
		InterfacePtr<IBaseVisitor> baseVisitor(this, UseDefaultIID());
		if (baseVisitor)
		{
			InterfacePtr<IBaseHandler> theHandler(baseVisitor->GetHandler(), IID_IBASEHANDLER);
			if (theHandler) 
			{
				// Invoke the handler's HandleMyNode, which is added-in to the handler boss
				InterfacePtr<IMyNodeHandler> myHandler(theHandler, UseDefaultIID());
				if (myHandler)
					bDone = myHandler->HandleMyNode(pVisitable, this);
			}
		}
		return bDone;
	}
	</pre>

	A custom IMyNodeVisitor may implement an alternative child traversal scheme by providing its own
	version of VisitChildren.  The built-in IBaseVisitor::VisitChildren() implementation is as follows:

	<pre>
	bool16 BaseVisitorImpl::VisitChildren(IVisitorHelper* pVisitable) 
	{
		bool16 bDone = kFalse;
		// fTheHandler and fFinishChildren were cached when InitVisitor was called
		if (pVisitable) 
		{
			int32 childCount = pVisitable->CollectChildren(fTheHandler);
			for (int32 i = childCount-1; i >= 0 && (fFinishChildren || !bDone); i--) 
			{
				InterfacePtr<IVisitorHelper> aChild(pVisitable->QueryChild(i));
				if (aChild) 
				{
					bDone |= aChild->Accept(this);
				}
			}
		}
		return bDone;
	}
	</pre>

	@see IBaseHandler
	@see IVisitorHelper
	*/
class IBaseVisitor : public IPMUnknown
{
	public:

		/**	Initialize the visitor with the database, the handler to use for acting on each node visited,
			and a flag dictating whether all children of a node should be visited if one returns kTrue.
			@param theDB IN IDataBase pointer for database being traversed
			@param theHandler IN IBaseHandler pointer for handler to use for node actions
			@param bFinishChildren IN kFalse if VisitChildren should return immediately after a child returns kTrue from
			visitation, kTrue if all children should be visited regardless of return value
		*/
		virtual bool16 InitVisitor(IDataBase* theDB, IBaseHandler* theHandler, bool16 bFinishChildren = kFalse) = 0;

		/** Get the handler used in this visitation
			@return IBaseHandler pointer for handler provided in InitVisitor
		*/
		virtual IBaseHandler* GetHandler(void) const = 0;

		/** Get the bFinishChildren flag
			@return bool16 provided as bFinishChildren in InitVisitor
		*/
		virtual bool16 GetFinishChildren(void) const = 0;

		/** Visit the children of the node referenced by pVisitable.
			The base class implementation knows how to use IHierarchy to traverse nodes.
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitChildren(IVisitorHelper* pVisitable) = 0;

		/** Visit an ISpread item
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitSpread(IVisitorHelper* pVisitable) = 0;

		/** Visit a spread layer item
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitSpreadLayer(IVisitorHelper* pVisitable) = 0;

		/** Visit an inline pageitem
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitInlineItem(IVisitorHelper* pVisitable) = 0;

		/** Visit a spline, or CGraphicFrameShape item
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitSplineItem(IVisitorHelper* pVisitable) = 0;

		/** Visit a multicolumn frame item
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitMultiColumnFrameItem(IVisitorHelper* pVisitable) = 0;

		/** Visit a text frame (a child of multicolumn frame item)
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitFrameItem(IVisitorHelper* pVisitable) = 0;

		/** Visit a group item
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitGroupItem(IVisitorHelper* pVisitable) = 0;

		/** Visit a guide item
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitGuideItem(IVisitorHelper* pVisitable) = 0;

		/** Visit a page
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitPage(IVisitorHelper* pVisitable) = 0;

		/** Visit an image
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitImageItem(IVisitorHelper* pVisitable) = 0;

		/** Visit an embedded HTML Page Item
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitHTMLItem(IVisitorHelper* pVisitable) = 0;

		/** Visit an EPS text item
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitEPSTextItem(IVisitorHelper* pVisitable) = 0;

		/** Visit an ISpread item
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitEPSItem(IVisitorHelper* pVisitable) = 0;

		/** Visit a PICT item
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitPICTItem(IVisitorHelper* pVisitable) = 0;

		/** Visit Windows metafile item
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitWMFItem(IVisitorHelper* pVisitable) = 0;

		/** Visit a PDF item
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitPDFItem(IVisitorHelper* pVisitable) = 0;

		/** Visit a Text on a Path item
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitTOPItem(IVisitorHelper* pVisitable) = 0;

		/** Visit an owned item -- that is, owned by a text frame
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitOwnedItem(IVisitorHelper* pVisitable) = 0;

		/** Visit an IWaxAnchoredElement, such as an anchored graphic
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitWaxAnchoredElementItem(IVisitorHelper* pVisitable) = 0;

		/** Visit a parcel -- not really a pageitem (such as a line of text or a table cell)
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitParcelItem(IVisitorHelper* pVisitable) = 0;

		/** Visit an item of unknown type (provides generic handling)
			@param pVisitable IN IVisitorHelper pointer for item whose children are to be visited
			@return bool16 indicating whether visitation should stop immediately
		*/
		virtual bool16 VisitUnknownItem(IVisitorHelper* pVisitable) = 0;
};


#endif
