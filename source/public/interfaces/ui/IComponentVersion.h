//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IComponentVersion.h $
//  
//  Owner: Kenneth Philbrick
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
#ifndef _ICOMPONENT_VERSION_H_
	
	#define _ICOMPONENT_VERSION_H_
	#include "AboutBoxID.h"
	
	class PMString;
	class IPMUnknown;
	
	/**
		Abstract interface for components to return their name  and version number.
		This is used to display this info in component information dialog 
	*/
	class IComponentVersion : public IPMUnknown
	{
		public:
			enum { kDefaultIID = IID_ICOMPONENT_VERSION };
	
			/**
				GetComponentNamePMString 				
					@param
					@return The name of the component as a PMString
			*/
			virtual PMString GetComponentNamePMString () = 0;
			

			/**
				GetComponentVersionPMString 				
					@param
					@return The version of the component as a PMString
			*/
			virtual PMString GetComponentVersionPMString () = 0;
	};

#endif