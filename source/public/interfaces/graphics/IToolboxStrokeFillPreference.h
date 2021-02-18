//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IToolboxStrokeFillPreference.h $
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
//  
//  Note:			This interface is intended to hold the preference setting for the
//  stroke & fill proxy in the toolbox. It is added, as a singleton, to the 
//  session's workspace (stored in K2 Defaults). The flag is an application
//  wide setting.
//  
//========================================================================================

#pragma once
	#ifndef _IToolboxStrokeFillPreference_
	#define _IToolboxStrokeFillPreference_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "ToolboxProxyTypes.h"
	#include "IGraphicAttrProxySuite.h"						// for attribute proxy type

//========================================================================================
/** IToolboxStrokeFillPreference returns information about the stroke and fill proxy in the 
	toolbox.
*/
class IToolboxStrokeFillPreference : public IPMUnknown
	{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_TOOLBOX_STROKEFILL_PREF };
		
	//____________________________________________________________________________________
	//	Accessors
	//____________________________________________________________________________________
	public:
		/** Is Fill active
		
			@return bool16	True or false 
		*/
		virtual bool16		IsFillActive (const IGraphicAttrProxySuite::ActiveProxyType& attrProxyType) const = 0;
		/** Is Stroke active
		
			@return bool16	True or false 
		*/
		virtual bool16		IsStrokeActive (const IGraphicAttrProxySuite::ActiveProxyType& attrProxyType) const = 0;

		/** Is the specified graphic attribute proxy active
		
			@return bool16	True or false 
			@param x is the active proxy to check
			@param attrProxyType is the graphic attribute proxy
		*/
		virtual bool16		IsActive (const ToolboxProxy::ActiveProxyType& x, const IGraphicAttrProxySuite::ActiveProxyType& attrProxyType) const = 0;

		/** Set the stroke/fill proxy to active for the specified graphic attribute proxy type.
		
			@param x what to set
			@param attrProxyType is the graphic attribute proxy type.
		*/
		virtual void		SetActive (const ToolboxProxy::ActiveProxyType& x, const IGraphicAttrProxySuite::ActiveProxyType& attrProxyType) = 0;

		/** Get the active proxy for the specified graphic attribute proxy type.
		
			@return ToolboxProxy::ActiveProxyType what is active
		*/
		virtual ToolboxProxy::ActiveProxyType	GetActive	(const IGraphicAttrProxySuite::ActiveProxyType& attrProxyType) = 0;
	};
		
#endif // _IToolboxStrokeFillPreference_
