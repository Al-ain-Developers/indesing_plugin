//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CGeometry.h $
//  
//  Owner: Jack Kirstein
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
#ifndef __CGeometry__
#define __CGeometry__

#include "IGeometry.h"
#include "HelperInterface.h"

#pragma export on

class PUBLIC_DECL CGeometry : public IGeometry
{
public:
	CGeometry(IPMUnknown *boss);
	virtual ~CGeometry();

	// All of the *StrokeBoundingBox methods call the *PathBoundingBox methods
	virtual PMRect GetStrokeBoundingBox() const;
	virtual PMRect GetStrokeBoundingBox( const PMMatrix& theMatrix) const;
	virtual ErrorCode SetStrokeBoundingBox( const PMRect& newBBox);
	virtual ErrorCode SetStrokeBoundingBox( const PMMatrix& theMatrix, const PMRect& newBBox);

	// Clients must override these methods
	virtual PMRect GetPathBoundingBox() const = 0;
	virtual PMRect GetPathBoundingBox( const PMMatrix& theMatrix) const = 0;
	virtual ErrorCode SetPathBoundingBox( const PMRect& newBBox) = 0;
	virtual ErrorCode SetPathBoundingBox( const PMMatrix& theMatrix, const PMRect& newBBox) = 0;
		
	virtual PMReal GetStrokeProportion() const;
	virtual PMReal GetPathProportion() const;

DECLARE_HELPER_METHODS()

};

#pragma export off
#endif