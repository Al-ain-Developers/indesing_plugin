//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IMissingFontSignalData.h $
//  
//  Owner: daan Strebe
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
//  Purpose:	Data sent with the missing font signals
//  
//========================================================================================

#pragma once
#ifndef __IMISSINGFONTSIGNALDATA__
#define __IMISSINGFONTSIGNALDATA__

#include "IPMUnknown.h"

#include "IPMFont.h"
#include "PMString.h"
#include "IFontMgr.h"
#include "FontMgrID.h"


/**	IMissingFontSignalData
	When the Font Manager cannot find a matching font in response to IFontMgr::QueryFont (...), it signals all responders
	of type kMissingFontSignalResponderService (see FontMgrID.h). This gives interested parties a chance to supply a suitable
	substitute or to acquire the font from somewhere else. A missing font responder's "Respond" method should query its Signal
	Manager for an interface of type IMissingFontSignalData, with an IID of IID_IMISSINGFONTSIGNALDATA. It should ask whether
	someone has already supplied a result by calling HaveResult(). If HaveResult() returns false then the responder is free to
	supply its own result. It asks the IMissingFontSignalData interface for information about the requested font using the
	various "Get" methods. If it can fulfill the request for a font, it supplies it to the Font Manager by calling SetResult.
	@see IFontMgr, ISignalMgr, IResponder 
*/

class IMissingFontSignalData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IMISSINGFONTSIGNALDATA };
		
			/**	Supply the information needed to specify the font. Normally this should not be called by responders, but only
				by the Font Manager.
				@param	fontName		IN: The PostScript name of the needed font.
				@param	styleBits		IN: Whether book, italic, bold, etc.
				@param	writingScript	IN: Whether Roman, Cyrillic, Japanese, etc. Values for script can be found in SDKDef.h.
				@param	smallCapScale	IN: When styleBits specifies kSmallCaps, smallCapScale supplies the scale factor.
				@param	forceFake		IN: Signals that the intended font should be a substitution font (IFontMgr::kInternal_Substitution)
			*/
			virtual
			void
		SetFontByPSName (const PMString &fontName, IFontMgr::FontStyleBits styleBits, int32 writingScript, PMReal smallCapScale, bool16 forceFake)
			= 0;

			/**	Retrieve the PostScript name of the font that the Font Manager is looking for.
				@return	PMString &		The PostScript name of the font the Font Manager is looking for. Notice that this is a
										PMString REFERENCE, so copy it somewhere if you intend to use it outside of the scope in
										which you acquire it.
			*/
			virtual
			const PMString &
		GetFontPSName() const
			= 0;

			/**	Retrieve the style bits describing characteristics of the font that the Font Manager is looking for.
				@return	FontStyleBits	Whether book, italic, bold, etc. See IFontMgr.
			*/
			virtual
			IFontMgr::FontStyleBits
		GetStyleBits() const
			= 0;
			
			/**	Retrieve the writing script that the font has been created to serve. Values for script can be found in SDKDef.h
				@return	int32			Which writing script (kSDKRomanScript, kSDKJapaneseScript, etc.) the needed font serves.
			*/
			virtual
			int32
		GetWritingScript() const
			= 0;
			
			/**	Retrieve the scale factor of the small caps synthesis. This is only relevant if FontStyleBits contains kSmallCaps.
				@return	PMReal			What to multiply full-sized characters by to synthesize small caps.
			*/
			virtual
			PMReal
		GetSmallCapScale() const
			= 0;
			
			/**	Retrieve the "force fake" flag.
				@return	bool16			If this flag is set then the font is intended to serve as a substitute font.
			*/
			virtual
			bool16
		GetForceFake() const
			= 0;

			/**	If the responder is able to fulfill the request, it should notify the Font Manager via SetResult.
				@param	result			An IPMFont that fulfills the Font Manager's request for a font as described by the "Get"
										methods. The recipient owns the IMPFont pointer and will dereference it when no longer needed.
			*/
			virtual
			void
		SetResult (IPMFont *result)
			= 0;

			/**	Retrieve the last font set through the SetResult method. Normally only used by the Font Manager.
				@return	IPMFont *		The font supplied by a responder as a suitable representative of the font needed by the Font
										manager. Recipient must Release() the IPMFont * when done with it.
			*/
			virtual
			IPMFont *
		GetResult() const
			= 0;

			/**	Tells whether any responder fulfilled the request for a font.
				@return	bool16			Return kTrue if any responder called "SetResult".
			*/
			virtual
			bool16
		HaveResult() const
			= 0;

			/**	Tell the IMissingFontSignalData to discard any SetResult information. Subsequent calls to GetResult() will return kFalse.
			*/
			virtual
			void
		ClearResult()
			= 0;	
};

#endif // __IMISSINGFONTSIGNALDATA__

