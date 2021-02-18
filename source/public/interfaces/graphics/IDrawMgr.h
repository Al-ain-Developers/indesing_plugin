//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDrawMgr.h $
//  
//  Owner: Jack Kirstein
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
//  Purpose of Interface:
//  This serves as a bottleneck interface for all drawing, both display and printing.
//  For more information, see the DrawMgr paper
//  
//========================================================================================

#pragma once
#ifndef __IDrawMgr__
#define __IDrawMgr__

#include "GraphicsID.h"
#include "PMRect.h"
#include "PMMatrix.h"
#include "UIDList.h"
#include "HitTestDragConstants.h"
#include "IShape.h"		

class IGraphicsContext;
class DrawInterrupter;
class DrawFilter;
class ICallback;
class IDVPlatformOffscreen;

#include "DVAForwardDeclarations.h"

/** The DrawMgr is a class that exists on each port and is used to set clipping areas as well as
	to initiate the drawing of any page element and its children.  Optionally, this class can be
	used to iterate the draw order, calling a client provided callback routine for every page item
	in the hierarchy.
*/
class IDrawMgr: public IPMUnknown
{
	public:
		/**
			default enum
		*/
		enum {kDefaultIID = IID_IDRAWMGR};

		/** Sets an interrupt checker before drawing to a port.  If this method is called
			before calling Draw(), then the interrupt checker will periodically (usually before each page item
			in the hierarchy is drawn) be called to see if the draw should be aborted.
			@param interruptChecker IN the DrawInterrupter
		*/
		virtual void BeginInterruptableDraw(DrawInterrupter* interruptChecker = nil) = 0;

		/** Removes the interrupt checker set by BeginInterruptableDraw.
		*/
		virtual void EndInterruptableDraw() = 0;

		/**
			Enables/disables the ability to interrupt drawing.  When enabled, 
			BeginInterruptableDraw() has no effect.  Useful in some tracking situations.
			@param enable IN whether to enable drawing interrupt
		*/
		virtual void EnableInterruptableDraw(bool16 enable = kTrue) = 0;

		/**
			Same as EnableInterruptableDraw(kFalse).
		*/
		virtual void DisableInterruptableDraw() = 0;

		/**
			Used to determine whether or not interruptable drawing has been disabled via a call to 
			EnableInterruptableDraw() or DisableInterruptableDraw().
			@return kTrue if interrupts are allowed, kFalse if interrupts have been disabled
		*/
		virtual bool16 IsDrawingInterruptable() = 0;

		/**
			Interrupts drawing, with the side effect that the current update area will be invalidated, 
			causing an update/paint event to occur such that the drawing will start again in the future.
		*/
		virtual void Abort() = 0;
		
		/** Main entry point - if kFalse is returned, any loops (ie hierarchy loops) should immediately abort.
			@param gc IN the graphics context.  Contains info about the port.
			@param thing IN the page item to draw
			@param flags IN see IShape.h for the drawing flags
			@return if kFalse, any loops (ie hierarchy loops) should immediately abort
		*/
		virtual bool16 DrawAtOnce(IGraphicsContext* gc, const UIDRef& thing, int32 flags) = 0; //perhaps name DrawNow
		
		/** Draw with timed updates to the screen.  The client passes in a droverized platform offscreen
		 and a pointer to the screen. Make sure the update bounds encompasses the entire
		 region that will be painted by thing and its children. tickCount is the update
		 interval.  Too small and the screen is updated far too often.  Too large and the
		 benefit is minimal.  Suggested value is 1/2 second (500 ticks).
		 @param gc IN the graphics context.  Contains info about the port.
		 @param thing IN the page item to draw
		 @param flags IN see IShape.h for the drawing flags
		 @param srcOffscreen IN a pointer to the droverized offscreen we are drawing to
		 @param dstDrawbot IN a pointer to the destination drawbot we are drawing to
		 @param updateBounds IN the area of the port or offscreen we are updating
		 @param tickCount IN how frequently to update the port using the srcOffscreen
		 @return kTrue if drawing was successful
		 */
		virtual bool16 DrawIncrementallyUsingDrawbot(
			IGraphicsContext *			gc, 
			const UIDRef &				thing, 
			int32						flags,
			IDVPlatformOffscreen *		srcOffscreen, 
			dvaui::drawbot::Drawbot *	dstDrawbot,
			SysRect						updateBounds, 
			int32						tickCount) = 0;
		
		/** Set "clipping" region.  Draw not called for items that fall outside the clip rect
			Beginning a new clip while a clip is already installed will push the new clip
			onto the draw mgr stack.  The new clip does not union or intersect with the previous
			clip, it simply supercedes it.  When endclip is called the clip is popped off the
			stack and the old clip takes over.
			@param r IN specifies clipping rect
		*/
		virtual void BeginCullToViewRect(const PMRect& r) = 0;
		/** Set "clipping" region.  Draw not called for items that fall outside the clip rect
			Beginning a new clip while a clip is already installed will push the new clip
			onto the draw mgr stack.  The new clip does not union or intersect with the previous
			clip, it simply supercedes it.  When endclip is called the clip is popped off the
			stack and the old clip takes over. Makes a copy of rgn.
			@param rgn IN specifies clipping region
		*/
		virtual void BeginCullToViewRegion(const SysRgn& rgn) = 0;

		/** Removes the current clipping from the stack.
			@return kTrue if there are still clips on the draw mgr stack, kFalse otherwise
		*/
		virtual bool16 EndLatestViewSpaceCulling() = 0;

		/** Returns a copy of the current clipping region.  If there is no clipping region,
			then nil is returned. Caller is responsible for disposing of the result if non-nil.
			@return SysRgn of the current clipping region
		*/
		virtual SysRgn GetViewCullRegion() const = 0;



		virtual uint32 GetSpreadFilterCount() const = 0;

		/** A filter is a PMRect which specifies an area which must be intersected by a page
			item before it will be drawn.  This filter does not affect how the page item is
			drawn (i.e. it does not clip).  To clip the page item, use BeginClip.
			@param r IN the filter rect 
		*/
		virtual uint32 BeginFilterToSpreadRect( const PMRect& r, const PMMatrix& m = PMMatrix(1.,0.,0.,1.,0.,0.), const PMMatrix& rest = PMMatrix(0.,0.,0.,0.,0.,0.)) = 0;
		/** End the current filter.
		*/
		virtual uint32 EndFilterToSpreadRect( PMRect* r = nil, PMMatrix* m = nil, PMMatrix* rest = nil) = 0;
		/** Get the current filter in use.
			@return PMRect the current filter rect
		*/
		struct FilterInfo
		{
			FilterInfo( const PMRect& r, const PMMatrix& m, const PMMatrix& rest) : fFilterRect(r), fFilterMatrix(m), fRestMatrix(rest) {}
			PMRect fFilterRect;
			PMMatrix fFilterMatrix;
			PMMatrix fRestMatrix;
		};
		virtual FilterInfo GetNthSpreadFilter( uint32 which) const = 0;

		/** Do not use, use ProcessEvent() with the kAbortCheckMessage event to check for interruption.
		*/
		virtual bool16 IsDrawAborted() = 0;

		/** Do not use, use ProcessEvent() with the kFilterCheckMessage event to check for clipping.
		*/
		virtual bool16 IsDrawClipped( IPMUnknown *thing, const PMMatrix* pb2view) = 0; //IGraphicsContext* gc) = 0;

		/** 
			Do not use, this method is called by the Draw Event Handler at the beginning of every IShape::Draw
			implementation.
			@param theShape IN the shape being drawn
			@return kTrue if the IShape implementation should not continue with the drawing of this page item
		*/
		virtual bool16 BeginShape(IPMUnknown *theShape) = 0;

		/** 
			Do not use, this method is called by the Draw Event Handler at the end of every IShape::Draw
			implementation.  Every call to BeginShape should be paired with a call to EndShape, even if the
			drawing was aborted.
			@param theShape IN the shape being drawn
		*/
		virtual void EndShape(IPMUnknown *theShape) = 0;

		/** IsDrawAborted flushes the offscreen to the screen every few seconds.  Sometimes, you want to 
			flush the offscreen, but you don't want to set the aborted flag, even if the user has done something
			to abort.  This will accomplish that.  You can call it alot, it will only have an effect every 
			few seconds or so, just like IsDrawAborted.
		*/
		virtual void FlushOffscreenIfNecessary() = 0;
		
		/** Disable an item.  It is up to the page item to call back and ask if it is in fact disabled.
			@param item IN UID of the page item to disable
			@param disable IN specifies whether to disable item
		*/
		virtual void Disable (UID item, bool16 disable) = 0;

		/** Returns whether page item is disabled.
			@param item UID of the page item
		*/
		virtual bool16 IsItemDisabled (UID item) const = 0;
		
		/** Returns whether draw was aborted or not during the last Begin/End Interruptable
			draw sequence.  The flag is cleared either by a successful Begin/End Interruptable
			draw or by calling ClearAborted()
			@return kTrue if the draw was aborted, kFalse otherwise.
		*/
		virtual bool16 WasDrawAborted() const = 0;

		/** Clears flag if Draw was aborted during the last Begin/End Interruptable draw sequence.  
		*/
		virtual void ClearAborted() = 0;
		

		/** To walk the display hierarchy in the same order as Draw, use this. 
			the transform matrix is passed instead of a graphics context (which may
			not exist); callees can modify the transform for their own purposes (e.g.
			master pages will concatenate a translation).
			@param xform IN specifies transform matrix.
			@param thing IN UIDRef of the shape to iterate from.
			@param callbackInfo IN the ICallback interface to use to for callback.
			@param flags IN see IShape.h for the drawing flags
		*/
		virtual void IterateDrawOrder_ (const PMMatrix *xform, const UIDRef &thing, ICallback *callbackInfo, int32 flags) = 0;
		
		void IterateDrawOrder( const UIDRef &thing, ICallback *callbackInfo, int32 flags)
		{
			PMMatrix identity;
			IterateDrawOrder_( &identity, thing, callbackInfo, flags);
		}
		
		/**
		Does a "global" disabling of any clipping or filtering. This method
		is useful for situations where a piece of content, such as a PageItem
		child or even Text content knows that it needs to draw but by the rules
		of the hierarchy it will get either clipped or filtered out.
		@return kTrue if Clipping or Filtering was enabled, kFalse otherwise.
		*/
		virtual bool16	DisableClippingOrFiltering() = 0;

		/**
		Re-enables clipping or filtering disabled by a call to the previous
		method.
		*/
		virtual void	EnableClippingOrFiltering() = 0;

		/**
		Stack based helper class for wrapping disabling/enabling of clipping
		or filtering.
		*/
		class PUBLIC_DECL ClippingOrFilteringDisabler
		{
		public:
			ClippingOrFilteringDisabler(IDrawMgr* drawMgr) :
				fDrawMgr(drawMgr),
				fWasEnabled(drawMgr && drawMgr->DisableClippingOrFiltering())
				{ }

			~ClippingOrFilteringDisabler()
				{
				if (fWasEnabled)
					fDrawMgr->EnableClippingOrFiltering();
				}

		private:
			IDrawMgr*		fDrawMgr;
			const bool16	fWasEnabled;
		};

};
#endif
