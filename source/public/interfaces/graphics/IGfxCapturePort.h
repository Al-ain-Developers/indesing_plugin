//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGfxCapturePort.h $
//  
//  Owner: Pushp Agarwal
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change $
//  ___________________
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2014 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by all applicable intellectual property
//  laws, including trade secret and copyright laws.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================
#pragma once
#ifndef __IGFXCAPTUREPORT__
#define __IGFXCAPTUREPORT__

#include "BravoForwardDecl.h" 
#include "GraphicsID.h"

/**	GfxCapturePort
 */
class IGfxCapturePort : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGFXCAPTUREPORT };

	/** 
         Initializes the port. 
    */ 
	virtual void Setup() = 0;
	
	/** 
         Internal use only
    */
	virtual void Setup(AGMGraphic*) = 0;
	virtual AGMGraphic* GetGraphic() const = 0;
	virtual AGMGraphixCapturePort* GetPort() const = 0;
	
	/** 
         Marks start of device size graphics. Location is the (0,0) point or anchor point of graphic. This point get transformed with current
		 matrix but graphic remains fixed size in device space and relative to this location.
         @param location			IN anchor point location as explained above
		 @param viewThreshhold		IN minimum zoom level to show graphic. Below this zoom graphic is not visible.
    */ 
	virtual void BeginFixedSizeGraphix(const PMPoint& location,PMReal viewThreshhold=0.0f) = 0;
	
	/** 
         Marks end of device size graphics. 

		 @see BeginFixedSizeGraphix 
    */
	virtual void EndFixedSizeGraphix() = 0;

	/** 
         Marks start of clip group. 
         @param clipRect			IN  clip rect of the group
		 @param matrix				IN  matrix is concated to port current matrix
    */ 
	virtual void StartClipGroup(const PMRect& clipRect,const PMMatrix& matrix) = 0;

	/** 
         Marks end of of clip group. 

		 @see StartClipGroup 
    */
	virtual void EndClipGroup() = 0;
	
	/** 
         Internal use only
    */
	virtual void DrawGraphic(AGMGraphic* graphic) = 0;
	/*
		Returns true if line width of stroke applied is not scaled with ctm. This setting is part of GState
	*/
	virtual bool16 GetDrawFixedLineWidth() const = 0;

	/**
		if fixed is true, line width of stroke applied is not scaled with ctm 
		@param fixed			IN  line width of stroke is fixed or not
	*/
	virtual void SetDrawFixedLineWidth(bool16 fixed) = 0;

	/**
		if enable is true, greeking is enabled on future text drawing on port
		@param enable			IN  whether to enable greeking for text
	*/
	virtual void SetGreekingEnabled(bool16 enable = true) = 0;
    
    /**
     Internal use only
     */
    virtual void SetupWithPort(AGMGraphixPort*) = 0;
};
#endif