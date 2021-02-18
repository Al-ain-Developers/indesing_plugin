//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPNGIconAttributes.h $
//  
//  Owner: Kenneth Philbrick
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
#ifndef __IPNGICONBUTTONATTRIBUTES__
#define __IPNGICONBUTTONATTRIBUTES__

#include "IPMUnknown.h"
#include "widgetid.h"


/**
		Abstract interface for accessing and modifying the settings of a icon.
		All icon resource should contain a PNGIconAttributes interface and resource data.

		The constants defined in IconStyleDefs.h should be used when defineing an Icons view.fr resource
*/
class IPNGIconAttributes : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPNGICONATTRIBUTES };	

		/**
				GetIconCentering								
					@return Icon centering value (kIconCentering  | kIconNoCentering  | kIconHorizontalCentering  | kIconVerticalCentering )
		*/		
		virtual int32 GetIconCentering() const = 0;    

		/**
				SetIconCentering								
				Sets the icon centering value
					@param (kIconCentering  | kIconNoCentering  | kIconHorizontalCentering  | kIconVerticalCentering )
					@return 
		*/		
		virtual void  SetIconCentering(const int32 centering) = 0;

		/**
				SetIconLook								
				Sets the icon look
					@param (kIconRaisedLook | kIconFlushLook)
					@return 
		*/		
		virtual void  SetIconLook (const int32 _look) = 0;

		/**
				GetIconLook								
					@return The icon look (kIconRaisedLook | kIconFlushLook)
		*/		
		virtual int32 GetIconLook () const = 0;				
		
		/**
				GetDrawIconWell								
					@return True if the icon draws a well or false if the well is skipped.
		*/		
		virtual bool GetDrawIconWell () const = 0;
		
		/**
		 GetDrawIconBorder								
		 @return True if the icon draws a border frame around itself or false if the border is skipped.
		 */		
		virtual bool GetDrawIconBorder () const = 0;
	
		/**
				SetAttributes											
				Sets the icon attributes				
					@param		centering
					@param		_look
					@param		_drawIconWell
					@return
		*/		
		virtual void SetAttributes (const int32 centering, const int32 _look, const bool _drawIconWell) = 0;	
};

#endif



