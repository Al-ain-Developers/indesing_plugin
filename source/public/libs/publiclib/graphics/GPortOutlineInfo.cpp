//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/graphics/GPortOutlineInfo.cpp $
//  
//  Owner: Jeff Argast
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

#include "VCPublicHeaders.h"
#include "GPortOutlineInfo.h"
#include "IGraphicsPort.h"



//---------------------------------------------------------------
// GPortOutlineInfo constructor
//---------------------------------------------------------------

GPortOutlineInfo::GPortOutlineInfo( IGraphicsPort *gPort)
	: fBeginPathCalled(kFalse)
{
	fPort = gPort;
	fPort->AddRef();
}

//---------------------------------------------------------------
// GPortOutlineInfo destructor
//---------------------------------------------------------------

GPortOutlineInfo::~GPortOutlineInfo()
{
	fPort->Release();
}

//---------------------------------------------------------------
// GPortOutlineInfo::BeginPath
//---------------------------------------------------------------

void GPortOutlineInfo::BeginPath()
{
	if ( !fBeginPathCalled )
	{
		fPort->newpath();
		
		fBeginPathCalled = kTrue;
	}
}

//---------------------------------------------------------------
// GPortOutlineInfo::EndPath
//---------------------------------------------------------------

void GPortOutlineInfo::EndPath()
{
}


//---------------------------------------------------------------
// GPortOutlineInfo::moveto
//---------------------------------------------------------------

void GPortOutlineInfo::moveto(const PMReal& x, const PMReal& y)
{
	fPort->moveto (x, y);
}

//---------------------------------------------------------------
// GPortOutlineInfo::lineto
//---------------------------------------------------------------

void GPortOutlineInfo::lineto(const PMReal& x, const PMReal& y)
{
	fPort->lineto (x, y);
}

//---------------------------------------------------------------
// GPortOutlineInfo::closepath
//---------------------------------------------------------------

void GPortOutlineInfo::closepath()
{
	fPort->closepath();
}


//---------------------------------------------------------------
// GPortOutlineInfo::curveto
//---------------------------------------------------------------

void GPortOutlineInfo::curveto(const PMReal& x1, const PMReal& y1, const PMReal& x2, const PMReal& y2, const PMReal& x3, const PMReal& y3)
{
	fPort->curveto (x1, y1, x2, y2, x3, y3);							
}

