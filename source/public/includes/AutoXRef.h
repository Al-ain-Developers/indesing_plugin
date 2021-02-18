//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AutoXRef.h $
//  
//  Owner: Paul Sorrick
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
//  Purpose of class
//  AutoXRef is to used with IXReferenceUID to automatically call BeginXRefSession and EndXRefSession.
//  
//========================================================================================

#pragma once
#ifndef __AUTOXREF__
#define __AUTOXREF__

#include "IXReferenceUID.h"

class IDataBase;

/** Automatically calls IXReferenceUID::BeginXRefSession in constructor and 
	IXReferenceUID::EndXRefSession in destructor so you do not have to explicitly
	to call BeginXRefSession and EndXRefSession. Just create an AutoXRef stack object
	and you are done. Prevents problems with early returns forgetting to call 
	EndXRefSession and leaving a session open.

	e.g.
	the following code:

		InterfacePtr<IXReferenceUID> xRef(GetExecutionContextSession(), IID_IXREFERENCEUID);
		if (xRef)
		    xRef->BeginXRefSession(sourceDB, targetDB);
		...
		Some code here
		...
		if (xRef)
		    xRef->EndXRefSession(sourceDB, targetDB);

	would become:

		AutoXRef autoXRef(sourceDB, targetDB);
		Some code here

	When the AutoXRef object is created, BeginXRefSession is called, and likewise when 
	the AutoXRef goes out of scope, EndXRefSession is called. You can force the destructor
	by using scoping brackets { } as necessary so you don't have to leave the XRefSession open
	longer than necessary.

  @see IXReferenceUID.h
  @see AutoGSave.h

*/
class AutoXRef
{
public:
	/** Constructor
	*/
	explicit AutoXRef(IDataBase* sourceDB, IDataBase* targetDB)
	{
		InterfacePtr<IXReferenceUID> xRef(GetExecutionContextSession(), UseDefaultIID());
		if (xRef) xRef->BeginXRefSession(sourceDB, targetDB);
	}
	/** Destructor
	*/
	~AutoXRef()
	{
		InterfacePtr<IXReferenceUID> xRef(GetExecutionContextSession(), UseDefaultIID());
		if (xRef) xRef->EndXRefSession();
	}

};

#endif //__AUTOXREF__