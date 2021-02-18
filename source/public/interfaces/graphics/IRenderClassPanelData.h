//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IRenderClassPanelData.h $
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
	#ifndef _IRenderClassPanelData_
	#define _IRenderClassPanelData_
//___________________________________________________________________________________
//	INCLUDES
//___________________________________________________________________________________
	#include "IPMUnknown.h"
//===================================================================================
//___________________________________________________________________________________
//	CLASS DECLARATION
//___________________________________________________________________________________

	/**	A service provider interface to supply the WidgetID which implements
		an option dialog for creating and editing an rendering type such as
		kPMColorBoss.
	*/
	class IRenderClassPanelData : public IPMUnknown
		{
		/**	Returns the widget ID of the option dialog panel for creating and editing
			the rendering object.
		*/
		public:
			virtual WidgetID		GetOptionPanelWidgetID		(void) = 0;
		};
		
#endif // _IRenderClassPanelData_
