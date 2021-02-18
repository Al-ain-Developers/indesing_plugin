//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hidpi/HiDPIWidgetControlView.h $
//  
//  Owner: Neelabh Sunny
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
//  Each C++ implementation class in the plug-in and its corresponding ImplementationID
//  should be registered in this file.
//  
//========================================================================================
#ifndef __HiDPIWidgetControlView_h__
#define __HiDPIWidgetControlView_h__

#include "DVControlView.h"

class HiDPIWidgetControlView : public DVControlView
{
public:

	/** Constructor. */
	HiDPIWidgetControlView(IPMUnknown* iBossP) : DVControlView(iBossP) {}
	
	virtual void ReadWrite(IPMStream* iStreamP, ImplementationID iImpID);

	/** Draw function actually draws PNG image within icon */
	virtual void Draw(IViewPort* iViewPortP, SysRgn iUpdateRgn);
};

#endif