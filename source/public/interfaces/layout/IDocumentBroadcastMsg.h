//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDocumentBroadcastMsg.h $
//  
//  Owner: Michael Martz
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
//  Note:		This is not intended as an interface header. ILayoutSelContentChangedMsg is an 
//  abstract class declaration that allows the Layout CSB to communicate with its suites
//  using a abstract message class. This class is passed in ISuite::SelectionContentChanged()
//  as the void*.
//  
//========================================================================================

#pragma once
	#ifndef _IDocumentBroadcastMsg_
	#define _IDocumentBroadcastMsg_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	//.......Interface headers....................................................................
	#include "IPMUnknown.h" 		// for the definition of INHERITFROM
	//.......Other headers........................................................................
//________________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________________
	class ISubject;
//================================================================================================
/** 
	The document broadcast message
*/
class IDocumentBroadcastMsg INHERITFROM
	{
	public:
/** 
		Return the message type of this message.
*/
		virtual void SetData (const ClassID&, ISubject*, const PMIID&, void*) = 0;

/** 
		Return the classID from the observer's Update() call.
*/
		virtual ClassID GetClassID (void) const = 0;

/** 
		Return the ISubject from the observer's Update() call.
*/
		virtual ISubject* GetSubject (void) const = 0;

/** 
				Return the PMIID from the observer's Update() call.
*/
		virtual PMIID GetPMIID (void) const = 0;

/** 
			Return the void* from the observer's Update() call.
*/
		virtual void* GetVoidStar (void) const = 0;
	};

#pragma export off

#endif // _IDocumentBroadcastMsg_