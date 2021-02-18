//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SwatchesObserver.h $
//  
//  Owner: SusanCL
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
//  Class definition for SwatchesObserver.
//  TODO:	Move to private/includes
//  
//========================================================================================

#pragma once
#ifndef __SwatchesObserverr__
#define __SwatchesObserverr__

#include "CObserver.h"

class ISubject;
class UIDRef;
class IGraphicStateRenderObjects;

#pragma export on
//========================================================================================
// Class Definition	
//========================================================================================
/**	An observer class responds to changes in the swatch list widget selection.
	As a result of updating the widget selection, it may also interact with the
	graphic state object.
	This observer lives on the swatch list widget.
	@see also CObserver.h for detail description of Update, AutoAttach, and AutoDetach.
*/
class WIDGET_DECL SwatchesObserver : public CObserver
{
	public:
		// ----- Initialization -----
		
		SwatchesObserver(IPMUnknown *boss);
		virtual ~SwatchesObserver();
		
		/**	Responds to interested change messages.
			@param theChange is the change message.
			@param theSubject is the subject broadcasting the change.
			@param protocol is the change message protocol.
			@param changedBy is any additional data passed along by the change subject.
		*/
		virtual void 		Update(const ClassID& theChange, ISubject* theSubject,
							   		const PMIID& protocol, void* changedBy);
		/**	Called when this observer should attach to the subject(s) that it  
			observes.
		*/
		virtual void		AutoAttach();
		/**	Called when this observer should automatically detach from the subject(s) 
			that it observes.
		*/
		virtual void		AutoDetach();
			
	

	protected:
		/**	Update the swatch list widget's swatches UID list to reflect the current selections
			in the swatches list widget. The implementation assumes we have an IListControlDataOf
			interface and swatch list widget has access to a IColorViewData interface.
			It also sorts the selection list so that the order of UIDList reflects the order
			the swatches in the swatch list widget.
			If your panel does not conform to this assumption, then it must be
			overwritten by the subclasses.
			@param iGfxStateRenderObjects is usually the active graphic state objects.
			@param theChange is the type of change.
		*/
		virtual bool16		UpdateSwatchesUIDData		(IGraphicStateRenderObjects* iGfxStateRenderObjects, const ClassID& theChange);
		
		/**	Change graphic state render data to update the render object.
			Additionaly it may also create and process a attribute command that is
			related to the rendering object being udpated.
			@param iGfxStateRenderObjects is usually the active graphic state objects.
			@param targetRenderObjectClassID is the new rendering class ID the swatch
			selection is updating to.
			@param targetRenderingUID is the corresponding rendering object UID.
			@param prevRenderingUID is the previous rendering object UID of the same rendering class.
		*/
		virtual bool16		UpdateRenderObject			(IGraphicStateRenderObjects* iGfxStateRenderObjects, ClassID targetRenderObjectClassID, UID targetRenderingUID, UID prevRenderingUID);

		/**	Apply relevant render object attributes to the graphic state based on the new
			rendering object.
			@param iDataBase is the database of the new rendering object UID.
			@param targetRenderingUID is the new rendering object UID.
			@param prevRenderingUID is the previous rendering object UID of the same rendering class.
			@param swatchIsUniqueSelection is true if this rendering UID is the unique selection
			and not part of the multiple selection.
		*/
		virtual bool16		ApplyRenderObjectAttributes	(IDataBase* iDataBase, UID targetRenderingUID, UID prevRenderingUID, bool16 swatchIsUniqueSelection = kFalse);
		/**	Update the graphic state based on the changes.
			@param iGfxStateRenderObjects is usually the active graphic state objects.
			@param swatchRef is the new rendering object UIDRef of the swatch
			selection is updating to.
			@param theChange is the type of change.
		*/
		virtual bool16		ProcessGraphicStateChanges	(IGraphicStateRenderObjects* iGfxStateRenderObjects, UIDRef swatchRef, const ClassID& theChange);
		
		/**	fAttachAsIID is the attached IID of the observer.
		*/
		PMIID				fAttachAsIID;
		/**	fAttachToIID is the interested procotol IID being observered.
		*/
		PMIID				fAttachToIID;

	private:
		/**	When there's a change in the graphic state's active rendering object,
			we need to clear all rendering blocks.
			@param iGfxStateRenderObjects is usually the active graphic state objects.
			@param swatchRef is the new rendering object UIDRef of the swatch
			selection is updating to.
			@param theChange is the type of change.
		*/
		bool16				ClearEveryBlock				(IGraphicStateRenderObjects* iGfxStateRenderObjects, UIDRef swatchRef, const ClassID& theChange);

		/**	Handles all neccessary actions whenver a graphic state active rendering object changes.
		  	Apply appropriate render object related attributes.
			@param iGfxStateRenderObjects is usually the active graphic state objects.
			@param swatchRef is the new rendering object UIDRef of the swatch
			selection is updating to.
			@param theChange is the type of change.
		*/
		bool16				HandleRenderObjectChanged	(IGraphicStateRenderObjects* iGfxStateRenderObjects, UIDRef swatchRef, const ClassID& theChange);

};
#pragma export off


#endif	// SwatchesObserver