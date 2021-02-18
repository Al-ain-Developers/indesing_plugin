//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ITrapStyle.h $
//  
//  Owner: James Jardee-Borquist
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

#ifndef __ITrapStyle__
#define __ITrapStyle__

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef __ODFRC__	// when used for core resource compilation, provide just the parameter range constants

#include "IPMUnknown.h"
#include "PrintID.h"

//_______________________________________________________________________________________
//	Default value for each of the Trap style properties are defined below.
//_______________________________________________________________________________________

//_______________________________________________________________________________________
// CLASS ITrapStyle
//_______________________________________________________________________________________

/**	A data interface for the trap style.
*/
class ITrapStyle : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITRAPSTYLE };
	
	/**	Set the style name
		@param inName is the new style name to set.
	*/
	virtual void SetName(const PMString &inName) = 0;
	
	/**	Returns the trap style name.
	*/	virtual PMString GetName() const = 0;
	
	
	enum {
		/**	kImg2Obj_Off indicates image to object trapping is turned off.
		*/
		kImg2Obj_Off					= 0,
		/**	kImg2Obj_Off indicates image to object trapping is turned on.
		*/
		kImg2Obj_On						= 1
	};
	
	/**	Set the image-to-object trapping.
		@param inImg2Obj specifies the image-to-object trap setting.
	*/
	virtual void SetImg2Obj(int32 inImg2Obj) = 0;

	/**	Returns the image-to-object trap setting.
	*/
	virtual int32 GetImg2Obj() const = 0;
	
	enum {
		/**	kImg2Img_Off indicates image to image trapping is turned off
		*/
		kImg2Img_Off					= 0,
		/**	kImg2Img_On indicates image to image trapping is turned on
		*/
		kImg2Img_On						= 1
	};
		
	/**	Set the image-to-image trap setting.
		@param inImg2Img specifies the image-to-image setting
	*/
	virtual void SetImg2Img(int32 inImg2Img) = 0;

	/**	Returns the image-to-image trap setting
	*/
	virtual int32 GetImg2Img() const = 0;

	enum {
		/**	kInternalImg_Off indicates trapping within individual images is turned off.
		*/
		kInternalImg_Off				= 0,
		/**	kInternalImg_On indicates trapping within individual images is turned on.
		*/
		kInternalImg_On					= 1
	};
	
	/**	Set the trapping within individual images.
		@param inInternalImg specifies whether of not trapping wihtin individual images is on or off.
	*/
	virtual void SetInternalImg(int32 inInternalImg) = 0;

	/**	Returns true if the trapping within individual images is turned on.
	*/
	virtual int32 GetInternalImg() const = 0;
	
	/**	Set the default trap width
		@param inDfltWidth specifies the default trap width
	*/
	virtual void SetDfltWidth(const PMReal &inDfltWidth/*0.0 to 8.0*/) = 0;

	/**	Returns the default trap width
	*/
	virtual PMReal GetDfltWidth() const = 0;
	
	/**	Set the black trap width
		@param inBlkWidth specifies the black trap width
	*/
	virtual void SetBlkWidth(const PMReal &inBlkWidth/*0.0 to 8.0*/) = 0;

	/**	Returns the black trap width
	*/
	virtual PMReal GetBlkWidth() const = 0;
	
	/**	Set the color scaling factor
		@param inClrScaling specifies the color scaling factor
	*/
	virtual void SetClrScaling(const PMReal &inClrScaling/*0.0 to 100.0*/) = 0;
	
	/**	Returns the color scaling factor
	*/
	virtual PMReal GetClrScaling() const = 0;
	
	/**	Set the trap step threshhold
		@param inStepTH specifies the trap step threshhold
	*/
	virtual void SetStepTH(const PMReal &inStepTH/*1.0 to 100.0*/) = 0;
	
	/**	Returns the trap step threshhold
	*/
	virtual PMReal GetStepTH() const = 0;
	
	/**	Set the black color threshhold
		@param inBlkColorTH specifies the black color threshhold
	*/
	virtual void SetBlkColorTH(const PMReal &inBlkColorTH/*0.0 to 100.0*/) = 0;
	
	/**	Returns the black color threshhold
	*/
	virtual PMReal GetBlkColorTH() const = 0;
	
	/**	Set the black density threshhold
		@param inBlkDnstyTH specifies the black density threshhold
	*/
	virtual void SetBlkDnstyTH(const PMReal &inBlkDnstyTH/*0.001 to 12.0*/) = 0;
	
	/**	Returns the black density threshhold
	*/
	virtual PMReal GetBlkDnstyTH() const = 0;
	
	/**	Set the sliding trap threshhold
		@param inSlidingTH specifies the sliding trap threshhold
	*/
	virtual void SetSlidingTH(const PMReal &inSlidingTH/*0.0 to 100.0*/) = 0;
	
	/**	Returns the sliding trap threshhold
	*/
	virtual PMReal GetSlidingTH() const = 0;
	
	/**	Trap settings for determining where trap falls when trapping vector graphics to images.
	*/
	enum {
		/**	kImgPlacement_Center indicates the trap straddles the edges between objects and images.
		*/
		kImgPlacement_Center			= 0,
		/**	kImgPlacement_Choke indicates the objects is to overlap the abutting images.
		*/
		kImgPlacement_Choke				= 1,
		/**	kImgPlacement_NeutralDensity indicates same trapping rules are applied as used elsewhere in the document.
		*/
		kImgPlacement_NeutralDensity	= 2,
		/**	kImgPlacement_Spread indicates the images is to overlap the abutting objects.
		*/
		kImgPlacement_Spread			= 3
	};
	
	/**	Sets the image placement trap setting.
		@param inImgPlacement specifies the image placement trap setting
	*/
	virtual void SetImgPlacement(int32 inImgPlacement) = 0;

	/**	Returns the image placement trap setting.
	*/
	virtual int32 GetImgPlacement() const = 0;
	
	enum {
		/**	kImagemasks_Off indicate if 1-bit image should not be trapped to abutting objects.
		*/
		kImagemasks_Off					= 0,
		/**	kImagemasks_On indicate if  1-bit image is trapped to abutting objects.
		*/
		kImagemasks_On					= 1
	};
	
	/**	Set the 1-bit image trap setting.
		@param inImagemasks specifies the 1-bit image trap setting.
	*/
	virtual void SetImagemasks(int32 inImagemasks) = 0;

	/**	Returns the 1-bit image trap setting.
	*/
	virtual int32 GetImagemasks() const = 0;

	/**	Trap settings for controling the shape of the outside join of two trap segments.
	*/
	enum {
		/**	kMiterTrapJoin indicates the join is mitered.
		*/
		kMiterTrapJoin					= 0,
		/**	kRoundTrapJoin indicates the join is rounded.
		*/
		kRoundTrapJoin					= 1,	
		/**	kBevelTrapJoin indicates the join is beveled.
		*/
		kBevelTrapJoin					= 2
	};

	/**	Set the trap join appearance setting.
		@param inTrapJoinStyle specifies the trap join.
	*/
	virtual void SetTrapJoinStyle(int32 inTrapJoinStyle) = 0;

	/**	Returns the trap join setting.
	*/
	virtual int32 GetTrapJoinStyle() const = 0;
	
	/**	Trap settings for controling the intersection of three-way traps.
	*/
	enum {
		/**	kMiterTrapEnd shapes the end of the trap to keep it away from the intersecting object.
		*/
		kMiterTrapEnd					= 0,
		/**	kOverlapTrapEnd shapes the end of the lightest trap by wrapping around
			the point where the three objects intersect.
		*/
		kOverlapTrapEnd					= 1
	};

	/**	Sets the trap end appearance setting.
		@param inTrapEndStyle specifies the trap end setting.
	*/
	virtual void SetTrapEndStyle(int32 inTrapEndStyle) = 0;
	/**	Returns the trap end setting.
	*/
	virtual int32 GetTrapEndStyle() const = 0;
	
	/**	Copy the trap style from inTrapStyle.
		@param inTrapStyle is the source trap style to copy from
	*/
	virtual void CopyData(const ITrapStyle *inTrapStyle) = 0;

	/**	Reset all trap style settings to default values.
	*/
	virtual void Reset2DefaultValue() = 0;
	
	enum {
		/**	kNameFlag indicate style name is set.
		*/
		kNameFlag						= (1 << 0),
		/**	kImg2ObjFlag indicate image to object trap setting is set.
		*/
		kImg2ObjFlag					= (1 << 1),
		/**	kInternalImgFlag indicate internal image trap setting is set.
		*/
		kInternalImgFlag				= (1 << 2),
		/**	kDfltWidthFlag indicate default width is set.
		*/
		kDfltWidthFlag					= (1 << 3),
		/**	kBlkWidthFlag indicate black width is set.
		*/
		kBlkWidthFlag					= (1 << 4),
		/**	kClrScalingFlag indicate color scaling factor is set.
		*/
		kClrScalingFlag					= (1 << 5),
		/**	kStepTHFlag indicate trap step threshhold is set.
		*/
		kStepTHFlag						= (1 << 6),
		/**	kBlkColorTHFlag indicate black color threshhold is set.
		*/
		kBlkColorTHFlag					= (1 << 7),
		/**	kBlkDnstyTHFlag indicate black density threshhold is set.
		*/
		kBlkDnstyTHFlag					= (1 << 8),
		/**	kSlidingTHFlag indicate slinding threshhold is set.
		*/
		kSlidingTHFlag					= (1 << 9),
		/**	kImgPlacementFlag indicate image placement trap setting is set.
		*/
		kImgPlacementFlag				= (1 << 10),
		/**	kImagemasksFlag indicate 1-bit image trap setting is set.
		*/
		kImagemasksFlag					= (1 << 11),
		/**	kJoinStyleFlag indicate trap join is set.
		*/
		kJoinStyleFlag					= (1 << 12),
		/**	kEndStyleFlag indicate trap end is set.
		*/
		kEndStyleFlag					= (1 << 13),
		/**	kImg2ImgFlag indicate image to image trap setting is set.
		*/
		kImg2ImgFlag					= (1 << 14)
	};
	
	/**	Returns whether or not the specifies property is set.
		@param inFlag is one of the enum described immediately above.
		@return true if the specified inFlag is set.
	*/
	virtual bool16 GetFlag(int32 inFlag) const = 0;
};

#endif //ODFRC

//_______________________________________________________________________________________
//	Minimum and maximum values allow for each TrapStyle property.
//	Default values
//_______________________________________________________________________________________
/**	kTrapStyleMinBlackWidth specifies the minimum black width value.
*/
const PMReal	kTrapStyleMinBlackWidth				= 0;
/**	kTrapStyleMaxBlackWidth specifies the maximum black width value.
*/
const PMReal	kTrapStyleMaxBlackWidth				= 8.0;
/**	kTrapStyleMinDefaultWidth specifies the minimum default width value.
*/
const PMReal	kTrapStyleMinDefaultWidth			= 0;
/**	kTrapStyleMaxDefaultWidth specifies the maximum default width value.
*/
const PMReal	kTrapStyleMaxDefaultWidth			= 8.0;
/**	kTrapStyleMinStep specifies the minimum trap step value.
*/
const PMReal	kTrapStyleMinStep					= 1.0;
/**	kTrapStyleMaxStep specifies the maximum trap step value.
*/
const PMReal	kTrapStyleMaxStep					= 100.0;
/**	kTrapStyleMinBlackColor specifies the minimum black color value.
*/
const PMReal	kTrapStyleMinBlackColor				= 0.0;
/**	kTrapStyleMaxBlackColor specifies the maximum black color value.
*/
const PMReal	kTrapStyleMaxBlackColor				= 100.0;
/**	kTrapStyleMinBlackDensity specifies the minimum black density value.
*/
const PMReal	kTrapStyleMinBlackDensity			= 0.001;
/**	kTrapStyleMaxBlackDensity specifies the maximum black density value.
*/
const PMReal	kTrapStyleMaxBlackDensity			= 10.0;
/**	kTrapStyleMinSlidingTrap specifies the minimum sliding trap scale value.
*/
const PMReal	kTrapStyleMinSlidingTrap			= 0.0;
/**	kTrapStyleMaxSlidingTrap specifies the maximum sliding trap scale value.
*/
const PMReal	kTrapStyleMaxSlidingTrap			= 100.0;

#ifndef __ODFRC__	// when used for core resource compilation, provide just the parameter range constants

/**	kTrapStyleDefaultBlackWidth specifies the default black width value.
*/
const PMReal	kTrapStyleDefaultBlackWidth			= 0.5;
/**	kTrapStyleDefaultWidth specifies the default width value.
*/
const PMReal	kTrapStyleDefaultWidth				= 0.25;
/**	kTrapStyleDefaultImagePlacement specifies the default image placement trap setting.
*/
const int32		kTrapStyleDefaultImagePlacement 	= ITrapStyle::kImgPlacement_Center;
/**	kTrapSytleDefaultObj2Image specifies the default object to image trap setting.
*/
const bool16	kTrapSytleDefaultObj2Image			= ITrapStyle::kImg2Obj_On;
/**	kTrapSytleDefaultImage2Image specifies the default image to image trap setting.
*/
const bool16	kTrapSytleDefaultImage2Image		= ITrapStyle::kImg2Img_On;
/**	kTrapSytleDefaultInternalImage specifies the default internal image setting.
*/
const bool16	kTrapSytleDefaultInternalImage		= ITrapStyle::kInternalImg_Off;
/**	kTrapSytleDefaultImageMask specifies the default 1-bit image trap setting.
*/
const bool16	kTrapSytleDefaultImageMask			= ITrapStyle::kImagemasks_On;
/**	kTrapStyleDefaultStep specifies the default trap step value.
*/
const PMReal	kTrapStyleDefaultStep				= 10.0;
/**	kTrapStyleDefaultBlackColor specifies the default black color value.
*/
const PMReal	kTrapStyleDefaultBlackColor			= 100.0;
/**	kTrapStyleDefaultBlackDensity specifies the default black density value.
*/
const PMReal	kTrapStyleDefaultBlackDensity		= 1.60;
/**	kTrapStyleDefaultSlidingTrap specifies the default sliding trap scale value.
*/
const PMReal	kTrapStyleDefaultSlidingTrap		= 70.0;
/**	kTrapStyleDefaultColorReduction specifies the default color reduction value.
*/
const PMReal	kTrapStyleDefaultColorReduction		= 1.0;
/**	kTrapStyleDefaultJoinStyle specifies the default trop join setting.
*/
const int32		kTrapStyleDefaultJoinStyle			= ITrapStyle::kMiterTrapJoin;
/**	kTrapStyleDefaultEndStyle specifies the default trop end setting.
*/
const int32		kTrapStyleDefaultEndStyle			= ITrapStyle::kMiterTrapEnd;

#endif //ODFRC
#endif // __ITrapStyle__

// End, ITrapStyle.h.
