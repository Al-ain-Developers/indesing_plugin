//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGradientFillInstall.h $
//  
//  Owner: Thanh Nguyen
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
//  Install Gradient Fills.
//  
//========================================================================================

#pragma once
#ifndef __IGradientFillInstall__
#define __IGradientFillInstall__


#include "IPMUnknown.h"
#include "PMMatrix.h"
#include "IColorData.h"
#include "K2Vector.h"
#include "IGraphicsPort.h"
#include "IInkResourceData.h"
#include "GraphicTypes.h"
#include "GradientFillID.h"


/**	This interface helps to install a gradient rendering object in the graphic port.
	To use, you have to set up all the attribute of the gradient first.  This is
	done by using the IGRADIENTFILL interface. 
	Gradient rendering objects are defined in GradientFillID.h.
	@see GradientFillID.h
	@see IRenderingObject
	@see IGradientFill
*/
class IGradientFillInstall : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IGRADIENTFILLINSTALL } ;

		/** This method is typcially used to install a gradient for proxy and swatch icons.
			@param port the graphic port in which to install the gradient object.
			@param r the rectangular arear where the gradient will be installed.
			@param angle the gradient angle.
			@param gradBound the list of gradient stop positions.
			@param gradMidPoint the list of gradinet mid points.
			@param gradType the gradient type to install.
		*/
		virtual void InstallGradient(IGraphicsPort* port, const PMRect& r, PMReal angle,
											   K2Vector<PMReal>* gradBound,
											   K2Vector<PMReal>* gradMidPoint,
											   GradientType gradType
										  ) = 0;

		/** This method is typcially used to install either a gradient fill or a gradient stroke
			of an InDesign document objects such as page items, text, or table objects.
			All relevant graphic attributes are taken into account when the gradient is installed.
			@param port the graphic port in which to install the gradient object.
			@param length the gradient length.
			@param radius the gradient radius.
			@param angle the gradient angle.
			@param hiliteLen the gradient highlight length.
			@param hiliteAngle the gradient highlight angle.
			@param gradBound the list of gradient stop positions.
			@param gradMidPoint the list of gradinet mid points.
			@param gradType the gradient type to install.
			@param gradMatrix the transformation matrix for the gradient.
		*/
		virtual void InstallGradient( IGraphicsPort* port, PMReal length, 
										PMPoint innerCenter, PMPoint outerCenter, 
										PMReal radius, PMReal angle,
										PMReal hiliteLen, PMReal hiliteAngle,
										K2Vector<PMReal>* gradBound,
										K2Vector<PMReal>* gradMidPoint,
										GradientType gradType,
										PMMatrix gradMatrix ) = 0 ;

};

#endif // __IGradientFillInstall__
