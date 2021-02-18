//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IMetaDataIterator.h $
//  
//  Owner: Raveendra Madala
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

#ifndef __IMetaDataIterator_h__
#define __IMetaDataIterator_h__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- ID.h files -----

#include "MetaDataID.h"

//========================================================================================
// CLASS IMetaDataIterator
//========================================================================================

class IMetaDataIterator : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMETADATAITERATOR };

	/**
		This should be used by external users, this is used to set the tool kit wrapper
	*/
	virtual void	Adopt(void* iter) = 0;

	/**
		Get the information from the next iteration.
		@param schemaNS A pointer to the string that will be assigned the schema namespace URI of
						the current property. May be null if the value is not wanted.
		@param propPath A pointer to the string that will be assigned the XPath name of the current
						property. May be null if the value is not wanted.
		@param propValue A pointer to the string that will be assigned the value of the current
						property. May be null if the value is not wanted.
		@param options Option flags describing the current property.
		@return Returns true if there was another node to visit, false if the iteration is done.
	*/
	virtual bool16	Next(PMString& ns, PMString& path, PMString& prop, IMetaDataAccess::IteratorOptions* options = 0) const = 0;
    /**
		Skip some portion of the remaining iterations.
		@param options Option flags to control the iteration.
						The available option flags are:
						kIterSkipSubtree -  Skip the subtree below the current node.
						kIterSkipSiblings - Skip the subtree below and remaining siblings of the current node.
	*/
	virtual void	Skip( IMetaDataAccess::SkipOptions	options ) = 0;
};

#endif // __IMetaDataIterator_h__
