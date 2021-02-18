//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGradientPanelHelper.h $
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
//  Helper interface to access the gradient panels.
//  
//========================================================================================

#pragma once
#ifndef __IGradientPanelHelper__
#define __IGradientPanelHelper__

#include "IRenderingObject.h"
#include "K2Vector.h"	


/**	This interface is obsolete and will not be supported.
*/
class IGradientPanelHelper : public IPMUnknown
{
	public:
		typedef enum
		{
			kMidPointThumb = 0,
			kStopThumb
		}thumbType;
		

		//==================================================================
		// Setting the gradient rendering setup which is used to draw the gradient
		// in the gradient panel.  This is included the gradient slider and
		// the proxy...
 		//==================================================================
		virtual void SetGradientRenderingSetup(IRenderingObject* renderingSetup) = 0;

		//==================================================================
		// Set either a midpoint or a thumb stop selection.  
		// This could be used to turn off the selection
		// of gradient thumbs.  To deselect thumb, set
		// index = -1
 		//==================================================================
		virtual void SetSelectedThumbIndex(int16 index) = 0;

 		//==================================================================
		// Set the total number of thumbs in the gradient.  The total number of 
		// thumbs are the sum number of thumb stops AND the midpoints
 		//==================================================================
		virtual void SetTotalThumbNum(int16 thumbNum) = 0;

 		//==================================================================
		// Set the position for each of the thumbs.  This is the list of thumb
		// stops and midpoint, alternating.  The position is ranging from 0...1
 		//==================================================================
		virtual void SetThumbList(K2Vector<PMReal>thumbList) = 0;

		//==================================================================
		// Set the position for the Nth thumb. The thumbPosition should
		// be between 0...1
		//==================================================================
		virtual void SetNthThumbPosition(int16 index, PMReal thumbPosition) = 0;
		
		//==================================================================
		// Setting the ratio of the midpoint relative to the two adjacent 
		// thumb stops.
 		//==================================================================
		virtual void SetMidPointRatio(K2Vector<PMReal>ratioList) = 0;

 		//==================================================================
		// Setting the midpoint ratio for the nth midpoint.  index is the 
		// index of the midpoint *NOT* the thumb list.  For example, if there
		// are total 5 thumbs (3 stops and 2 midpoints), index = 0 means the 
		// first midpoint and index == 1 is the index of the second midpoint.
 		//==================================================================
		virtual void SetNthMidPointRatio(int16 index, PMReal ratio) = 0;




		//==================================================================
 		// For pageItem rendering & graphic state interaction
		// This is the rendering object of the gradient the is drawn
		// in the gradient slider and the gradient proxy.  This rendering
		// set up should be gradientMetaDataRendering setup 
		// (ie. IID_IGRADIENTMETADATA,	kGradientMetaDataImpl) 
		//==================================================================
		virtual IRenderingObject* GetGradientRenderingObject() = 0;

		//==================================================================
		// Find out the current selected thumb.  return -1 if there
		// is currently no selected thumb.
		//==================================================================
		virtual int16 GetSelectedThumbIndex() = 0;

		//==================================================================
		// Get the total number of thumbs in the gradient slider.  This is
		// the total of the thumb stops and midpoints.  
		//==================================================================
		virtual int16 GetTotalThumbNum() = 0;

		//==================================================================
		// Get the list of thumb positions of the gradient slider.
		// This list contains all the positions of both thumb stops
		// and midpoints in the gradient slider.  The position should
		// be in the range 0...1. The midpoint position also from 0...1.  
		// However, if the midpoint is 0.5, it means that the midpoint is
		// right at the midpoint of its two adjacent thumb stops
 		//==================================================================
		virtual K2Vector<PMReal> GetThumbList() = 0;

 		//==================================================================
		// Get the position of the Nth thumb. The return position should
		// be between 0...1
 		//==================================================================
		virtual PMReal GetNthThumbPosition(int16 index) = 0;

 		//==================================================================
		// Getting the list of all the midpoint ratios.
  		//==================================================================
		virtual void GetMidPointRatio(K2Vector<PMReal>* thumbList) = 0;

 		//==================================================================
		// Getting the midpoint ratio for the nth midpoint.  index is the 
		// index of the midpoint *NOT* the thumb list.  For example, if there
		// are total 5 thumbs (3 stops and 2 midpoints), index = 0 means the 
		// first midpoint and index == 1 is the index of the second midpoint.
 		//==================================================================
		virtual PMReal GetNthMidPointRatio(int16 index) = 0;


 		//=============================================================================
		//			*******  GRADIENT PANEL EVENT HELPER METHODS    *******
 		//=============================================================================

 		//=============================================================================
		// Inserting a new thumb stop before the 'index' in the thumb list.
 		//=============================================================================
		virtual void InsertThumb(int16 index, PMReal thumbPosition) = 0;

 		//=============================================================================
		// Relocate the Nth thumb to the new location.
		// This also automatically:
		// Readjust the midpoint (if a thumb stop is moved)
		// Update the slider rendering data. (ie. re-arrange the color data list in 
		// the gradient rendering.
 		//=============================================================================
		virtual void RelocateNthThumb(int16 thumbIndex, PMReal toPosition) = 0;

 		//=============================================================================
		// Removing the thumb stop at 'index'.  This is also removing the 
		// associate midpoint and then readjust the affected midpoint according
		// to its midpoint ratio between the two adjacent thumb stops
 		//=============================================================================
		virtual void RemoveThumbStop(int16 index) = 0;

};



#endif // __IGradientPanelHelper__
