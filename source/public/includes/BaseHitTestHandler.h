//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/BaseHitTestHandler.h $
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
#ifndef __BASEHITTESTHANDLER__
#define __BASEHITTESTHANDLER__

#include "IPMUnknown.h"
#include "IBaseHandler.h"

#include "LayoutUIID.h"
#include "HelperInterface.h"
#include "IAdornmentShape.h"

#pragma export on

/** Base implementation for IBaseHandler to accomplish hit-testing in InDesign.
	This implements the most widely-used handler routines for basic hit-testing.  Several specialized
	subclasses exist, and in fact none of the hit-test handler bosses in InDesign derive solely from 
	this implementation.  
	
	When a hit is found by a handler routine, it appends the item UID to the UIDList pointed to by fThingsHit,
	for access by the top-level caller to the item hit.  This mechanism could support the storage of more
	than one hit item, though in practice this handler typically stops hit-testing after one hit is found.

	Situations requiring hit-testing behavior other than this implementation should subclass and override
	the HandleXXX routines as necessary.  See related files for information on adding hit-testing support
	for new types of pageitems.

	@see IBaseHandler
	@see IBaseVisitor
	@see IVisitorHelper
*/
class WIDGET_DECL BaseHitTestHandlerImpl : public IBaseHandler
{
	public:
		/**
			Flags for DoHandleSplineItem for extra control over how hit-testing works.
		*/
		typedef enum { 
			/** Don't visit items on locked layers. */
			kDontSeeLockedItems = 0, 
			/** Visit items even if on locked layers. */
			kSeeLockedItems 
		} LockedItemTreatment;
		
		/**
			Flags for DoHandleSpreadLayer for extra control over how hit-testing works.
		*/
		typedef enum { 
			/** Don't visit items on locked layers. */
			kDontSeeLockedLayers = 0, 
			/** Visit items even if on locked layers. */
			kSeeLockedLayers 
		} LockedLayerTreatment;
		
		/** 
			Flags for how to treat master page items while hit-testing.
		*/
		typedef enum { 
			/** Don't visit any master page items. */
			kDontSeeMPItems = 0, 
			/** See and override a master page item that is hit. */
			kSeeAndOverrideMPItems, 
			/** See master page items, but don't override if we hit one. */
			kOnlySeeMPItems, 
			/** See master page items and override if hit, including text frames threaded to the hit item.  */
			kSeeAndOverrideMPItemsAndThreads 
		} MasterPageHandlerTreatment;

		BaseHitTestHandlerImpl(IPMUnknown *boss);
		~BaseHitTestHandlerImpl();

		/** Do some caching, do a gsave, and concatenate theShape's ParentToPasteboardMatrix into the gport.
			@param gd IN GraphicsData pointer for drawing environment
			@param theShape IN IShape pointer for initial shape to hit-test from, typically a spread
		*/
		virtual void InitHandler(GraphicsData* gd, IShape* theShape);

		/** Do a grestore to match the gsave performed in InitHandler().
		*/
		virtual void TerminateHandler(void);

		/** Get the hit-testing rectangle stored in IBaseSelectionHandlerData.
			@return the hit-test rectangle for this handler boss
		*/
		virtual const PMRect GetHandlerIntersectionRect(void) const ;

		/** Get the GraphicsData pointer provided to InitHandler()
			@return the GraphicsData pointer
		*/
		virtual const GraphicsData* GetHandlerGraphicsDataPtr(void) const { return fHitTestHandlerGrarphicsData; }

		/** Hit-test a spread
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleSpread(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Hit-test a spread layer
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleSpreadLayer(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Hit-test an inline item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleInlineItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Hit-test a spline item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleSplineItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Invoke StandardPageItemHandler for a multi-column frame.
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleMultiColumnFrameItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Invoke StandardPageItemHandler for a text frame.
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleFrameItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Invoke StandardPageItemHandler for a group item.
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleGroupItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Check for a hit in the area occupied by a ruler guide.
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleGuideItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Invoke StandardLeafNodeHandler for a page.
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandlePage(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Invoke StandardLeafNodeHandler for an image.
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleImageItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Invoke StandardLeafNodeHandler for an embedded HTML item.
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleHTMLItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Invoke StandardLeafNodeHandler for an EPS text item.
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleEPSTextItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Invoke StandardLeafNodeHandler for an EPS item.
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleEPSItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Invoke StandardLeafNodeHandler for a PICT.
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandlePICTItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Invoke StandardLeafNodeHandler for a Windows metafile.
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleWMFItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Invoke StandardLeafNodeHandler for a PDF item.
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandlePDFItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Invoke StandardPageItemHandler for a text on a path item.
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleTOPItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Hit-test an owned item, such as a graphic anchored in a text frame or a table
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleOwnedItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Hit-test a wax anchored element, such as a footnote
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleWaxAnchoredElementItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Hit-test a text parcel
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleParcelItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Invoke StandardPageItemHandler for an unknown item.
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16 HandleUnknownItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

	protected:
		/** Subclasses can handle adornments here.
		*/
		virtual bool16 HandleAdornments(IAdornmentShape::AdornmentDrawOrder drawOrder, IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);
		
		/** Use this stack based class to Setup/CleanupPort instead of direct calls.
		*/
		class ConcatTransformInScope
		{
		public:
			ConcatTransformInScope(BaseHitTestHandlerImpl* handler, IShape* theShape)
			{
				fHandler = handler;
				if (fHandler)
				{
					fHandler->AddRef();
					fHandler->SetupHitTestHandlerPort(theShape);
				}
			}
			ConcatTransformInScope(BaseHitTestHandlerImpl* handler, const PMMatrix& toPasteboard)
			{
				fHandler = handler;
				if (fHandler)
				{
					fHandler->AddRef();
					fHandler->SetupHitTestHandlerPort(toPasteboard);
				}
			}

			~ConcatTransformInScope()
			{
				if (fHandler)
				{
					fHandler->CleanupHitTestHandlerPort();
					fHandler->Release();
				}
			}

		private:
			ConcatTransformInScope(const ConcatTransformInScope& other);
			ConcatTransformInScope& operator=(const ConcatTransformInScope& other);

			//---- Data
			BaseHitTestHandlerImpl* fHandler;
		};

		friend class ConcatTransformInScope;

		//---- Helpers
		/** Cache some information from other interfaces on this boss.
		*/
		void	InitAssociatedData(void);	

		/**	Apply bare-bones hit-testing logic to a pageitem by only checking adornments and children, but
			not the item itself.

			Steps:
			1.	If trivial reject fails based on entire shape's bbox being outside hit rect, return kFalse.
			2.	Handle any kAfterShape adornments for the pageitem.  
			3.	Visit the children.  
			4.	Handle all adornments for the item.  
			Note that this handler does not test the item itself for a hit. Also, any hit item has its UID appended
			to the UIDList at fThingsHit.

			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16	StandardPageItemHandler(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/**	Apply simple hit-testing logic to an item that has graphic data by checking adornments, any clipping
			path, and the item's shape itself.

			Steps:
			1.	If trivial reject fails based on entire shape's bbox being outside hit rect, return kFalse.
			2.	Handle any kAfterShape adornments for the pageitem.  
			3.	Check for a hit in the clipping path, if one exists.
			4.	Check for a hit in the fill area of the shape itself.
			5.	Handle all adornments for the item.  
			Any hit item has its UID appended to the UIDList at fThingsHit.

			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16	StandardLeafNodeHandler(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);	

		/** Test for a hit using IMainItemTOPData::PointIsInTOPTextArea
			@param iShape IN pointer to the shape having the text on a path
			@param drawOrder UNUSED pass a dummy value
			@param gd IN GraphicsData pointer
			@param r IN the hit-test rectangle
			@return kTrue for a hit; kFalse for no hit
		*/
		virtual bool16	HitTestTextOnPath( IShape*	iShape, IAdornmentShape::AdornmentDrawOrder drawOrder, GraphicsData* gd, const PMRect&	r /*in view coordinates*/) const ;

		/**	Hit-tests a spread, while passing a flag to master pages code to override any hit item
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16	HandleSpreadOMP(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor);

		/** Hit-test a spread layer, with control over how to handle masterpage items and locked layers
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@param mph IN specifies how to treat masterpage items
			@param llt IN specifies how to treat locked layers
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16	DoHandleSpreadLayer(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor, MasterPageHandlerTreatment mph, LockedLayerTreatment llt = kDontSeeLockedLayers);

		/** Hit-test a SplineItem, with control over how to handle locked items
			@param pVisitable IN the IVisitorHelper interface on the item
			@param theVisitor IN the IBaseVisitor interface used for traversal
			@param mph IN specifies how to treat masterpage items
			@param llt IN specifies how to treat locked layers
			@return kTrue to be done with all handling, kFalse to continue
		*/
		virtual bool16	DoHandleSplineItem(IVisitorHelper* pVisitable, IBaseVisitor* theVisitor, LockedItemTreatment lit = kDontSeeLockedItems);

		/* Checks to see if an item is locked. It looks for the IID_ILOCKPOSITION interface and checks the lock state.
			@param item pointer to an impl on the boss of the item to check.
			@return kTrue if locked. kFalse if unlocked or the interface is not there.
		*/
		virtual bool16 IsItemLocked(IPMUnknown * item);

		//---- Data
		GraphicsData*	fHitTestHandlerGrarphicsData;		
		PMRect			fTheHitTestRectangle;//view coordinates -- is this ever modified ? set up in BaseHitTestHandlerImpl::InitAssociatedData from theData->GetHitTestRectangle()
		UIDList*		fThingsHit;
		IShape*			fShape;

		DECLARE_HELPER_METHODS()
private:
		void SetupHitTestHandlerPort(IShape* theShape);
		void SetupHitTestHandlerPort(const PMMatrix& toPasteboard);
		void CleanupHitTestHandlerPort(void);
};

#pragma export off

#endif
