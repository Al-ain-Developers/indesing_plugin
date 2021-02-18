//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IPDFAnnotationHandler.h $
//  
//  Owner: Tim Wright
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
#ifndef __IPDFAnnotationHandler_h__
#define __IPDFAnnotationHandler_h__

#include "FormFieldID.h"

//=============================================================================
class ISubject;

/** A service interface that is notified when a PDF annotation type item (form field/movie/sound)
  is added or removed from the hierarchy.  A list of the affected annotations is provided.
  To use, create a boss that implements IID_IK2SERVICEPROVIDER as kPDFAnnotationEventProviderImpl,
  and IID_IPDFANNOTATIONHANDLER as a custom implementation of IPDFAnnotationHandler.
  
  
*/
class IPDFAnnotationHandler : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPDFANNOTATIONHANDLER };
	
	/** Called when a PDF annotation type item (form field/movie/sound)
  		is added or removed from the hierarchy
  
  		@param theChange From Update call in a doc observer.  The Command that did the change. kAddToHierarchyCmdBoss or kRemoveFromHierarchyCmdBoss
  		@param theSubject From Update call in a doc observer.  The item that is being changed.
  		@param protocol  From Update call in a doc observer.  The protocol that is being changed. Should be IID_IHIERARCHY_DOCUMENT
  		@param changedBy  From Update call in a doc observer.  Pointer to ICommand doing the change.
  		@param inPDFAnnotationItems a list of PDF annotation page items being  added (kAddToHierarchyCmdBoss) or removed (kRemoveFromHierarchyCmdBoss)
  	*/ 
	virtual void HandlePDFAnnotationEvent(	const ClassID& theChange,
											ISubject* theSubject,
											const PMIID &protocol,
											void* changedBy,
											const UIDList& inPDFAnnotationItems) = 0;
};

//=============================================================================

#endif //

//  IFormFieldFactory.h.
