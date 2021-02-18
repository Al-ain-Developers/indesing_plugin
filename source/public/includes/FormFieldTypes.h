//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/FormFieldTypes.h $
//  
//  Owner: Tim Wright
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
//  Comments:	Base types for Form Fields.
//  
//========================================================================================

#pragma once
#ifndef __FormFieldTypes_h__
#define __FormFieldTypes_h__

#include "IPMUnknown.h"
#include "PMString.h"
#include "PMPoint.h"
#include "UIDList.h"
#include "K2Vector.h"

#include "FormFieldID.h"

// --------------------------------------------------------------------------------

namespace Form
{

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// For Push Buttons:

enum HilightMode
{
	kHilightNone, //1 in pdf
	kHilightInvert,
	kHilightOutline,
	kHilightPush
};

// --------------------------------------------------------------------------------

enum CaptionPlacement
{
	kPlaceCaptionOnly,
	kPlaceIconOnly,
	kPlaceCaptionBelowIcon,
	kPlaceCaptionAboveIcon,
	kPlaceCaptionRightOfIcon,
	kPlaceCaptionLeftOfIcon,
	kPlaceCaptionOverIcon
};

// --------------------------------------------------------------------------------

enum IconScaling
{
	kScaleAlways, //1 in pdf
	kScaleWhenBigger,
	kScaleWhenSmaller,
	kScaleNever
};

// --------------------------------------------------------------------------------

enum IconScaleType
{
	kScaleTypeAnamorphic, //1 in pdf
	kScaleTypeProportional
};

// --------------------------------------------------------------------------------
//The ordering is what GetNthState will use, and therefore what the
//palette uses...

typedef int32 AppearanceState;
enum DefinedAppearanceState //To be used with Get/SetNth Icon/Caption, and GetActiveStateIndex
{
	kStateInvalid = -1,
	kStateNormal = 0,
	kStateOver,
	kStateDown,
	kStateNormalOn, //For checkboxes, radio buttons...
	kStateNormalOff,
	kStateOverOn,
	kStateOverOff,
	kStateDownOn,
	kStateDownOff,
	kStateFirst = kStateNormal,
	kStateLast = kStateDownOff
};

// --------------------------------------------------------------------------------

struct Appearance
{
	bool16 		fEnabled;  
	//PMString	fCaption;
	
	//PMString	fAppearanceName;
	
	Appearance() : fEnabled(kTrue) {}
	Appearance( const Appearance& inAppearance )
	: 
		//fCaption(inAppearance.fCaption),
		fEnabled(inAppearance.fEnabled)
		//,fAppearanceName(inAppearance.fAppearanceName),
	{}
	
	Appearance& operator=( const Appearance& inAppearance )
	{
		//This is to guard against a bug in UIDList operator=
		//which corrupts an UIDList when you assign it to itself.
		if (this != &inAppearance)
		{
			//fCaption = inAppearance.fCaption;
			fEnabled = inAppearance.fEnabled;
			//fAppearanceName = inAppearance.fAppearanceName;
		}
		return *this;
	}
};

// --------------------------------------------------------------------------------

inline bool operator==( const Appearance& app1, const Appearance& app2 )
{
	return app1.fEnabled && app2.fEnabled;
}

// --------------------------------------------------------------------------------

inline bool operator!=( const Appearance& app1, const Appearance& app2 )
{
	return !(app1.fEnabled == app2.fEnabled);
}

// --------------------------------------------------------------------------------

typedef std::pair<Form::AppearanceState, Form::Appearance> AppearancePair;

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// Radio/Check buttons:

enum CheckSymbol //not used right now...
{
	kCheckSymbolCheck = 1,
	kCheckSymbolCircle,
	kCheckSymbolCross,
	kCheckSymbolDiamond,
	kCheckSymbolSquare,
	kCheckSymbolStar
};

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// Text fields:

enum TextAlignment
{
	kAlignTextLeft = 0,
	kAlignTextCenter,
	kAlignTextRight
};

enum StrokeJoin
{
	kMiterJoin = 0,
	kRoundJoin,
	kBevelJoin
};

enum StrokeAlign
{
	// DV_Note: Apparently unused constants...
	kStrokeAlignCenter = 0, // kAlignCenter constant collides with other definitions
	kStrokeAlignOutside = 2
};

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// List/Combo boxes:


enum ChoiceStyle
{
	kChoiceStyleList = 1,
	kChoiceStyleComboBox = 2
};

// --------------------------------------------------------------------------------

struct Choice
{
	PMString	fItem;
	PMString 	fExportName;
};

typedef PMString ListItem;
typedef K2Vector<ListItem> ChoiceList;

// --------------------------------------------------------------------------------

extern const PMReal kFormTextAutoFontSize;

}

DECLARE_OBJECT_TYPE(Form::Choice);
DECLARE_OBJECT_TYPE(Form::Appearance);
DECLARE_OBJECT_TYPE(Form::AppearancePair);
DECLARE_BASE_TYPE(Form::DefinedAppearanceState);


#endif // __FormFieldTypes_h__

//  FormFieldTypes.h.
