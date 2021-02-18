//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hidpi/HiDPIWidgetControlView.cpp $
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
//========================================================================================
#include "VCPlugInHeaders.h"
#include "HiDPIWidgetControlView.h"
#include "HiDPIID.h"
#include "IGraphicsPort.h"
#include "IViewPort.h"
#include "HiDPI.fr"
#include "PNGIcon.h"

void HiDPIWidgetControlView::ReadWrite(IPMStream* iStreamP, ImplementationID iImpID)
{
	DVControlView::ReadWrite(iStreamP, iImpID);
}

/** Draw function actually draws PNG image within icon */
void HiDPIWidgetControlView::Draw(IViewPort* iViewPortP, SysRgn iUpdateRgn)
{
	InterfacePtr<IGraphicsPort> gPort (iViewPortP, IID_IGRAPHICSPORT);
	gPort->gsave();
	PNGIcon myIcon;

	myIcon.LoadIcon(kHiDPIPluginID,kHiDPIIconRsrcID);
	myIcon.DrawIcon(gPort);
	
}

CREATE_PERSIST_PMINTERFACE(HiDPIWidgetControlView, kHiDPIControlViewImpl);