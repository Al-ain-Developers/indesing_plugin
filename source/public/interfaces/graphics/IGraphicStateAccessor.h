//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicStateAccessor.h $
//  
//  Owner: Michael_Martz
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
	#ifndef _IGraphicStateAccessor_
	#define _IGraphicStateAccessor_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "GraphicStylesID.h"
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATION
//
//	NOTE:
//			There are two implementations of this interface. One is added to the 
//		workspace (session and document) to make the workspace's graphic state object
//		persistent. The second is created by the graphic state context observer and 
//		is added to the active context. This is a session based object (database = nil),
//		and therefore is non-persistent.
//
//			Originally, there was just the workspace based accessor which was also 
//		added to the active context. Unfortunately, this forced the workspace object
//		to be held in memory, which prevented the purging of unneeded plugins. 
//________________________________________________________________________________________

/**	An interface for accessing the graphic state object.
*/
class IGraphicStateAccessor : public IPMUnknown
	{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IGRAPHICSTATE_ACCESSOR};
		
	//____________________________________________________________________________________
	//	Accessor memeber functions
	//____________________________________________________________________________________
	public:

		/**	Returns the graphic state object UID.
		*/
		virtual UID			GetGraphicStateUID			(void) = 0;
		/**	Set the graphic state object UID.
			@param gfxStateUID is the graphic state object UID.
		*/
		virtual void		SetGraphicStateUID			(UID gfxStateUID) = 0;
	
		/**	Returns the workspace UIDRef which owns the graphic state object.
		*/
		virtual UIDRef		GetOwningWorkspace			(void) = 0;

		/**	Set the workspace for the graphic state object.
			@param workspaceRef specifies the workspace UIDRef.
		*/
		virtual void		SetOwningWorkspace			(const UIDRef& workspaceRef) = 0;
		
		/**	Returns an graphic state interface specified by the interface IID.
			@param interfaceIID specifies the interested interface IID.
			@return the interface pointer for the requested interface IID.
		*/
		virtual IPMUnknown*	QueryGraphicStateInterface	(const PMIID& interfaceIID) = 0;
	};
		
#endif // _IGraphicStateAccessor_
