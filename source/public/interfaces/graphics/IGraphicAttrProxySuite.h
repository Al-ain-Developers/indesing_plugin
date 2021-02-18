//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicAttrProxySuite.h $
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
	#ifndef _IGraphicAttrProxySuite_
	#define _IGraphicAttrProxySuite_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "ISelectionMessages.h"

	#include "GraphicStylesID.h"
	#include "ShuksanID.h"
	
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATIONS
//________________________________________________________________________________________

/**	A graphic selection attribute suite for the management of graphic proxy.
	This proxy either affects layout or text.
*/
class IGraphicAttrProxySuite : public IPMUnknown
	{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IGRAPHICATTRPROXYSUITE };

		//____________________________________________________________________________________
		// The types that can be displayed as the stroke/fill proxy
		//____________________________________________________________________________________
		enum ActiveProxyType
			{
			/**	kDefaultProxyType indicates the default proxy type.
			*/
			kDefaultProxyType,
			/**	kNoActiveProxyType indicates no active proxy in effect.
			*/
			kNoActiveProxyType,
			/**	kTextProxyType indicates the text proxy type.
			*/
			kTextProxyType,
			/**	kLayoutProxyType indicates the layout proxy type.
			*/
			kLayoutProxyType
			};
			
	//____________________________________________________________________________________
	//	Public accessors
	//____________________________________________________________________________________
	public:
		/**	Returns true if the specified proxy type can be swapped to be the active proxy.
			@param proxyType specifies the proxy type.
			@return true if can be swapped.
		*/
		virtual bool16				CanSwapActiveProxyType			(ActiveProxyType proxyType) = 0;
		/**	Swap the specified proxy type as the active proxy type.
			@param proxyType specifies the proxy type to swap to.
		*/
		virtual void				SwapActiveProxyType				(ActiveProxyType proxyType) = 0;
		/**	Returns the active proxy type.
		*/
		virtual IGraphicAttrProxySuite::ActiveProxyType GetActiveProxyType (void) = 0;
		
	};

//____________________________________________________________________________________
//	Used internally for communication between ASB and CSB
//____________________________________________________________________________________
DECLARE_BASE_TYPE(IGraphicAttrProxySuite::ActiveProxyType);

/**	This message class is used internally for communicating between the ASB and CSB.
	Clients should not be creating this message.
*/
class GfxAttrProxySuiteMsg : public SelectionSuiteData
	{
	public:
	//____________________________________________________________________________________
	//	Data Members		
	//____________________________________________________________________________________

	/**	messageID is the message protocol IID.
	*/
	PMIID									messageID;
	/**	proxyType secifies the proxy type affected.
	*/
	IGraphicAttrProxySuite::ActiveProxyType	proxyType;
	};
	

#endif // _IGraphicAttrProxySuite_
