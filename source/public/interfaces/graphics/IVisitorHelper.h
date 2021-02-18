//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IVisitorHelper.h $
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
#ifndef __IVISITORHELPER__
#define __IVISITORHELPER__

#include "IPMUnknown.h"
#include "IBaseVisitor.h"
#include "GraphicsID.h"

class IVisitorHelper;

/**	A helper class, used with IBaseVisitor and IBaseHandler, to facilitate accomplishing tasks
	while traversing an arbitrary structure of nodes (typically of items on a spread).  IVisitorHelper is
	the "glue" that is aggregated to a structure node to enable it to be visited, as well as to hand
	control off to a handler routine for accomplishing a given task.

	The IVisitorHelper::Accept routine is based on the visitor design pattern from Gamma, et al., in tandem
	with the methods of IBaseVisitor.  It is the IVisitorHelper implementation on a given node boss that contains
	the knowledge of how links to child nodes are maintained.  For instance, while pageitems are typically
	linked by the IHierarchy interface in InDesign, the IVisitorHelper scheme doesn't require any specific
	interface to be supported by nodes; each node's implementation of IVisitorHelper utilizes the linkage
	mechanism native to the node to which it is aggregated.  Because of this, it is not even a requirement that
	all nodes in a given structure utilize a common linkage mechanism, in order for the visitor/handler scheme to
	operate.

	NOTE: Third-party-created pageitems that are not derived from built-in InDesign page item bosses must contain
	an IVisitorHelper interface on the page item boss in order for hit-testing to be supported for the item.  
	Also, since VisitXXX and HandleXXX routines aren't defined for these pageitems in IBaseVisitor and IBaseHandler,
	these should be provided by custom implementations that are added-in to the kBaseVisitorBoss and kPtrHitTestHandlerBoss
	(respectively).  The kPtrHitTestHandlerBoss is the base boss for InDesign hit-testing; several other boss 
	classes derive from it.

	Sample code for setting up the visitor, handler, and root item's visitor helper for a hit-testing scenario
	<pre>

	// Assume defined:	
	//	PMRect hitRect;		// a target rect to hit-test
	//	IControlView view;		// the current view
	//	UIDList* pTheSpreads;	// a list of spreads visible in the view
	//	ClassID handlerClass;	// ClassID of a handler boss that knows how to do hit-testing for each node type

	AGMGraphicsContext gc(view);
	PMMatrix theXForm = gc.GetTransform();
	theXForm.Transform(&hitRect);

	IDataBase* theDB = pTheSpreads->GetDataBase();

	// Create a visitor and the appropriate Handler for what we want to do.
	InterfacePtr<IBaseVisitor> theVisitor((IBaseVisitor*)::CreateObject(kBaseVisitorBoss, IID_IBASEVISITOR));
	InterfacePtr<IBaseHandler> theHandler((IBaseHandler*)::CreateObject(handlerClass, IID_IBASEHANDLER));

	// Load the visitor and handler with setup data.
	theVisitor->InitVisitor(theDB, theHandler);

	// Our hit-test handler boss keeps the hit rect on this interface; yours may store other things on add-ins
	InterfacePtr<IBaseSelectionHandlerData> theHandlerData(theHandler, IID_IBASESELECTIONHANDLERDATA);
	theHandlerData->Set(hitRect);
	// Handler boss uses one of its own interfaces for results of the hit-test task
	InterfacePtr<IUIDListData> theResults(theHandler, IID_IUIDLISTDATA);
	theResults->Set( new UIDList( theDB ));

	// loop through the spreads until a hit is found
	bool16 bDone = kFalse;

	GraphicsDataPtr gd(&gc);
	for (int32 i = 0; i < pTheSpreads->Length() && !bDone; i++)
	{
		InterfacePtr<IShape> spreadShape(pTheSpreads->GetRef(i), IID_ISHAPE);
		if (theVisitor && theHandler && spreadShape)
		{
			IBaseHandler *t = theHandler;
			BaseHitTestHandlerImpl* bhth = reinterpret_cast<BaseHitTestHandlerImpl*>(t);
			bhth->InitHandler(gd, spreadShape);

			// Call Accept on the spread with the visitor
			InterfacePtr<IVisitorHelper> theHelper(spreadShape, IID_IVISITORHELPER);
			if (theHelper)
				bDone = theHelper->Accept(theVisitor);
			bhth->TerminateHandler();
		}
	}
	// Upon completion, handler boss might have left interesting data on one of its interfaces.
	// In this example, the hit items are in theResults.  The bDone value tells whether it
	// actually found anything.

	</pre>
	@see IBaseVisitor
	@see IBaseHandler
*/
class IVisitorHelper : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IVISITORHELPER };

		/** Initiate traversal for the node.
			The Accept routine's role is to call the routine in theVisitor appropriate for the node.  For built-in
			nodes in InDesign, this means calling one of the IVisitor::VisitXXX routines.  An Accept routine
			for a custom node "MyNode" might look like the following, assuming a custom IMyNodeVisitor interface has been added-in to
			the kBaseVisitorBoss to pass control to the proper routine in the handler:
			<pre>
	bool16 MyNodeVisitorHelperImpl::Accept(IBaseVisitor* theVisitor) 
	{
		bool16 bDone = kFalse;
		// Query the interface added-in to kBaseVisitorBoss to visit my node
		InterfacePtr<IMyNodeVisitor> myVisitor(theVisitor, UseDefaultIID());
		// Call the Visitor without knowing anything about what its handler is going to do
		if (theVisitor)
			bDone = myVisitor->VisitMyNode(this);
		return bDone;
	}
			</pre>
			@param theVisitor IN a pointer to the IBaseVisitor that knows how to pass control off to specific visitor
			routines, depending on the type of node found
			@return bool16 whether to stop traversal yet or not; kTrue means stop immediately, kFalse means continue
		*/
		virtual bool16 Accept(IBaseVisitor* theVisitor) = 0;

		/** Determine how many children this node has, and if necessary, do any allocation or caching needed when 
			individual children are accessed via QueryChild.
			@param theHandler IN pointer to the IBaseHandler in use for this visitation.  This may be useful for
			interrogating information from the handler -- for instance, the GetHandlerIntersectionRect() routine to
			determine the target rectangle in a hit-testing task (useful for trivial rejection).
			@return bool16 the number of children found for this item.
		*/
		virtual int32 CollectChildren(IBaseHandler *theHandler) = 0;

		/**	Query for a specific child of this node.
			@param index IN the index of the node desired (zero-based)
			@return an IVisitorHelper pointer to the child node
		*/
		virtual IVisitorHelper* QueryChild(int32 index) = 0;
};


#endif
