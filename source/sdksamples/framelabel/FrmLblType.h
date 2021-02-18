//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/FrmLblType.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __FrmLblType_h__
#define __FrmLblType_h__

enum FrmLblPosition
{
	kFrmLblPosNone = -1,
	kFrmLblTop, 
	kFrmLblBottom,	 
	kFrmLblLeft,
	kFrmLblRight,

};

struct FrmLblInfo
{
	typedef object_type data_type;	

	/** String label to be displayed */		
	WideString		label;				
	/** Height limit of display text */
	int32			pointSize;
	/** Display flag, kTrue means display the adornment */
	bool16			visibility;
	/** String label font color to be displayed */		
	UID				fontColor;
	/** String label positin, top, bottom, left, right*/		
	FrmLblPosition	position;

	FrmLblInfo() :
		label(kFrmLblDefaultLabel),
		pointSize(kFrmLblDefaultPointSize),
		visibility(kFrmLblDefaultVisibility),
		fontColor(kFrmLblDefaultColor),
		position(kFrmLblBottom)
	{
	}

	FrmLblInfo(const WideString& labelstr, int32 size, bool16 vis, UID color, FrmLblPosition pos)
	{
		label = labelstr;
		pointSize = size;
		visibility = vis;
		fontColor = color;
		position = pos;
	}

};

#endif