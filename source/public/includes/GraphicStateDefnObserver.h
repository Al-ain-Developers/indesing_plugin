//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/GraphicStateDefnObserver.h $
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
//========================================================================================

#pragma once
#ifndef __GraphicStateDefnObserver__
#define __GraphicStateDefnObserver__

#include "SelectionObserver.h"

//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------
class IGraphicAttrMessage;
class IGraphicAttributeSuite;
//----------------------------------------------------------------------------------------
// Class Info
//----------------------------------------------------------------------------------------

#pragma export on

/**	A utility class for observing active selection related to graphic attributes.
	This class inherits from ActiveSelectionObserver.
	@see also SelectionObserver.h
*/
class WIDGET_DECL GraphicStateDefnObserver : public ActiveSelectionObserver
{
	public:
		GraphicStateDefnObserver(IPMUnknown *boss);
		virtual ~GraphicStateDefnObserver();
		
		/**	Called when this observer should attach to the subject(s) that it  
			observes (Active Context and Active Selection).
		*/
		virtual void	AutoAttach();
		/**	Called when this observer should automatically detach from the subject(s) 
			that it observes.
		*/
		virtual void	AutoDetach();
			
	protected:
	
		//................................................................................................
		//	Inherited from SelectionObserver
		//................................................................................................

		/**	Handles any selection changed related messages.
			@param iSelectionMsg is the selection message. If iSelectionMsg is nil, 
			everything should update.
		*/
		virtual void	HandleSelectionChanged 				(const ISelectionMessage* iSelectionMsg);
		/**	Handles any selection attributes changed related messages. Only IID_IGRAPHICATTRIBUTESUITE
			messages are handled in this method.
			@param iSelectionMsg is the selection message. If iSelectionMsg is nil, 
			everything should update.
		*/
		virtual void	HandleSelectionAttributeChanged 	(const ISelectionMessage* iSelectionMsg);

	protected:

		/**	Handles any graphic attribute related changes.
			@param iGraphicAttrSuite is the graphic attribute suite affected by this change.
			@param iGraphicAttrMsg is the graphic attribute message forward from the selection.
		*/
		virtual void	HandleDefinitionChange				(IGraphicAttributeSuite* iGraphicAttrSuite, IGraphicAttrMessage* iGraphicAttrMsg);
		
		/**	Override some or all of the following to respond to, according to the state of the definition.
			By default they do nothing.
		*/

		/**	Update to reflect the current definition. This method is called whenever there's a change in that cannot be 
			described by the other messages. It is usually called when something external changes the current selection.
			One or more objects could be selected. By default the method updates the active render data. The subclass 
			must overwrite this and do the rest of the updates.
			@param iGraphicAttrSuite is the graphic attribute suite affected by this change.
			@param iGraphicAttrMsg is the graphic attribute message forward from the selection.
		*/
			virtual void	UpdateDefinition					(IGraphicAttributeSuite* iGraphicAttrSuite, IGraphicAttrMessage* iGraphicAttrMsg) = 0;

		/**	Called when the current target's fill rendering data has changed.
			@param iGraphicAttrSuite is the graphic attribute suite affected by this change.
			@param renderUID is the new fill rendering UID.
			@param iGraphicAttrMsg is the graphic attribute message forward from the selection.
		*/
		virtual void	UpdateFillRenderData				(IGraphicAttributeSuite* iGraphicAttrSuite, UID renderUID, IGraphicAttrMessage* iGraphicAttrMsg);

		/**	Called when the current target's stroke rendering data has changed.
			@param iGraphicAttrSuite is the graphic attribute suite affected by this change.
			@param renderUID is the new stroke rendering UID.
			@param iGraphicAttrMsg is the graphic attribute message forward from the selection.
		*/
		virtual void	UpdateStrokeRenderData				(IGraphicAttributeSuite* iGraphicAttrSuite, UID renderUID, IGraphicAttrMessage* iGraphicAttrMsg);
		
		/**	Called when the current target's has its fill and stroke swapped.
			@param iGraphicAttrSuite is the graphic attribute suite affected by this change.
			@param iGraphicAttrMsg is the graphic attribute message forward from the selection.
		*/
		virtual void	UpdateSwapStrokeAndFill				(IGraphicAttributeSuite* iGraphicAttrSuite, IGraphicAttrMessage* iGraphicAttrMsg);

		/**	Called to Enable/Disable the associated widget(s).
			@param enableFlag is true if the associated widgets should be enabled.
		*/
		virtual void	EnableWidget	(bool16 enableFlag);

	private:
		/**	Process change messages for the observer.
			@param iGraphicAttrSuite is the graphic attribute suite affected by this change.
			@param iGraphicAttrMsg is the graphic attribute message forward from the selection.
		*/
		void			HandleChangeMessage					(IGraphicAttributeSuite* iGraphicAttrSuite, IGraphicAttrMessage* iGraphicAttrMsg);
		
		
	protected:
		/** fEnabledState keeps track of the widgets' enabling state. */
		bool16						fEnabledState;

	private:
		/** fOriginalSelection is the currently observed selection manager. */
		ISelectionManager*			fOriginalSelection;
};

#pragma export off

#endif	// __GraphicStateDefnObserver__
