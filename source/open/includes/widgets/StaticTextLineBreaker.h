//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/StaticTextLineBreaker.h $
//  
//  Owner: Rich Gartland
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
#ifndef __StaticTextLineBreaker__
#define __StaticTextLineBreaker__

#include "IStaticTextLineBreaker.h"
#include "HelperInterface.h"
#include "InterfaceFontInfo.h"
#include "PMRect.h"
#include "PMReal.h"
#include "PMPoint.h"
#include "K2Vector.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

//class InterfaceFontInfo;
class IGraphicsContext;
class IControlView;
class IScrollBarPanoramaSync;

class WIDGET_DECL StaticTextLineBreaker : public IStaticTextLineBreaker
{
public:
						StaticTextLineBreaker(IPMUnknown *boss);
	virtual 			~StaticTextLineBreaker();

	virtual void CreateLineBreaks(const PMString& stringToBreak, const PMReal maxLineWidth,  
						const InterfaceFontInfo& fontInfo);
	virtual PMString GetNthLine(int32 lineIndex) const;
	virtual PMPoint GetNthLineSize(int32 lineIndex) const;
	virtual int32 GetNumLines() const;
	
protected:
	// set up in CreateLineBreaks but then never changed...
	K2Vector<PMString> 	fLines;
	K2Vector<PMPoint> fLineSizes;

DECLARE_HELPER_METHODS()
};

#pragma export off

#endif //__StaticTextLineBreaker__
