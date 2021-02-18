//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IWatermarkData.h $
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

#ifndef __IWatermarkData_h__
#define __IWatermarkData_h__

// Interface includes:
#include "IPMUnknown.h"

// General includes:

// Project includes:
#include "DocFrameworkID.h"



class IPMUnknown;

class IWatermarkData : public IPMUnknown
{
public:

	enum	{kDefaultIID = IID_IWATERMARKDATA};

	/** The data structure used to store and transfer information about the watermark.
		This structure contains constructors, Get, Set, and ReadWrite methods.
	 */
	typedef struct
	{
		typedef enum
		{
			kWatermarkHPosLeft = 0,
			kWatermarkHPosCenter,
			kWatermarkHPosRight
		} WatermarkHPos;

		typedef enum 
		{
			kWatermarkVPosTop = 0, 
			kWatermarkVPosCenter,
			kWatermarkVPosBottom
		} WatermarkVPos;

		typedef object_type data_type;	

		/** Display flag, kTrue means display the watermark */
		bool16	fVisibility;
		
		/** Print flag, kTrue means print the watermark */
		bool16	fDoPrint;
		
		/** Draw In Back flag, kTrue means draw behind page items */
		bool16	fDrawInBack;
		
		/** Watermark string to be displayed */		
		WideString	fText;

		/** Font family to be displayed */		
		WideString	fFontFamily;

		/** Font style to be displayed */		
		WideString	fFontStyle;

		/** Font point size of displayed watermark text */
		int32	fFontPointSize;	

		/** Font color to be displayed */		
		UID	fFontColor;
		
		/** Watermark opacity (as a percentage 0 to 100) */		
		int32	fOpacity;
		
		/** Watermark rotation (positive or negative) */		
		int32	fRotation;

		/** Watermark horizontal page position:  center, left, right*/		
		WatermarkHPos	fHorzPosition;
		
		/** Watermark horizontal page offset relative to position*/	
		PMReal	fHorzOffset;
		

		/** Watermark vertical page position:  center, top, bottom*/		
		WatermarkVPos	fVertPosition;
		
		/** Watermark vertical page offset relative to position*/		
		PMReal	fVertOffset;
	} WatermarkInfo;

	/** Accessor 
		Sets the properties of this class
		@param	wmkInfo	 watermark properties.
	*/
	virtual void Set(const WatermarkInfo& wmkInfo) = 0;

	/** Accessor
		@return	watermark properties
	*/
	virtual const WatermarkInfo& Get() const = 0;

};

#endif // __IWatermarkData_h__

