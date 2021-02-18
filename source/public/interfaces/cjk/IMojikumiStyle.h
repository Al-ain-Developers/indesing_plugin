//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IMojikumiStyle.h $
//  
//  Owner: nmccully
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
#ifndef __IMojikumiStyle__
#define __IMojikumiStyle__


#include "IPMUnknown.h"

#include "IMojikumiTable.h"
#include "ICompositionStyle.h"
#include "CTextEnum.h"
#include "CJKID.h"

class IKinsokuTable;
class ITsumeTable;
class PMMatrix;
 

const double kAutoAkiMagicNumber = -1.0;
#define kSpacing_Auto	kAutoAkiMagicNumber
#define kSpacing_2bu	0.5
#define kSpacing_4bu	0.25
#define kSpacing_2bu4bu	0.75
#define kSpacing_8bu	0.125
#define kSpacing_None	0.0
#define kSpacing_FullWidth	1.0

/**
	IMojikumiStyle is one of the interfaces hanging off the kComposeStyleBoss object.
	As such, it is easily Queried from an IDrawingStyle interface.
	Text attributes can be summarized into a kComposeStyleBoss object, which is a non-persistent
	summary of every text attribute applied to some text. IMojikumiStyle lists character attributes
	associated with the Japanese text composition.
	IMojikumiStyle should be considered a "read-only" interface because the set operations have no
	impact beyond this data interface. It does not apply through to the text that this interface derived from.
	The text attributes themselves are the primary setters of the data.
	@see IDrawingStyle
	@see IVerticalRelatedStyle
	@see IGridRelatedStyle
	@see IRubyStyle
	@see IWarichuStyle
	@see IKinsokuTable
	@see ITsumeTable
	@see IMojikumiTable
	@ingroup text_comp_style
	@ingroup text_attr
*/
class IMojikumiStyle : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IMOJIKUMISTYLE };

	//-------------------------------------------------------------------------------
	/**@name 	Mojikumi table methods	*/
	/**         the MojikumiTable contains the relative spacing and compression values
				for character classes used by the Composer to set the text */
	//@{-----------------------------------------------------------------------------
		/** Sets the MojikumiTable in this interface only
		@param tableID [IN] UID of the mojikumi table
		*/
		virtual void SetMojikumiTable(UID tableID) = 0;		
		/** Gets the MojikumiTable UID
		@return UID of the MojikumiTable
		*/
		virtual UID GetMojikumiTable() const = 0;
		/** Query the IMojikumiTable interface
		@return IMojikumTable interface
		*/
		virtual IMojikumiTable* QueryMojikumiTable() const = 0;
	//@}-----------------------------------------------------------------------------
		
	//-------------------------------------------------------------------------------
	/**@name 	Kinsoku table methods */
	/**         the KinsokuTable contains lists of characters
				that cannot begin a line, cannot end a line, cannot be separated, and can 
				hang outside the frame at line end  */
	//@{-----------------------------------------------------------------------------
		/** Sets the KinsokuTable in this interface only
		@param tableID [IN] UID of the kinsoku table
		*/
		virtual void SetKinsokuTable(UID tableID) = 0;
		/** Gets the KinsokuTable UID
		@return UID of the KinsokuTable
		*/
		virtual UID GetKinsokuTable() const = 0;
		/** Query the IKinsokuTable interface
		@return IKinsokuTable interface
		*/
		virtual IKinsokuTable* QueryKinsokuTable() const = 0;
	//@}-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name 	Tsume table methods	*/
	/**			the TsumeTable is a table of kerning ratios (in em units) for characters
				whose normal width differs from the JIS X 4051 standard. The table
				dictates how much width to remove from the left and/or right sides of the character
				before adding in mojikumi spacing
	*/
	//@{-----------------------------------------------------------------------------
		/** Sets the TsumeTable in this interface only
		@param tableID [IN] UID of the TsumeTable
		*/
		virtual void SetTsumeTable(UID tableID) = 0;
		/** Gets the TsumeTable UID
		@return UID of the TsumeTable
		*/
		virtual UID GetTsumeTable() const = 0;
		/** Query the ITsumeTable interface
		@return ITsumeTable interface
		*/
		virtual ITsumeTable* QueryTsumeTable() const = 0;
	//@}-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name 	Character attributes	*/
	//-------------------------------------------------------------------------------
		/** Given the current mojikumi spacing, are ligatures allowed, or will they break
		@param vertical [IN] current selection is vertical text
		@return kTrue if ligatures are allowed
		*/
		virtual bool16 LigaturesAllowed(bool16 vertical) const = 0;
		
	//-------------------------------------------------------------------------------
	/**@name 	Force spacing
		if < 0, then not applied.
	*/
	//-------------------------------------------------------------------------------
		/** Set mojikumi spacing before (left side spacing)
		@param spacing [IN] spacing before in em units
		*/
		virtual void SetForceBeforeSpacing(PMReal spacing) = 0;
		/** Get mojikumi spacing before (left side spacing)
		@return spacing before in em units
		*/
		virtual PMReal GetForceBeforeSpacing() const = 0; 
		/** Set mojikumi spacing after (right side spacing)
		@param spacing [IN] spacing after in em units
		*/
		virtual void SetForceAfterSpacing(PMReal spacing) = 0;
		/** Get mojikumi spacing after (right side spacing)
		@return spacing after in em units
		*/
		virtual PMReal GetForceAfterSpacing() const = 0;
	//@}-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name 	Character-based rotation	*/
	//@{-----------------------------------------------------------------------------
		/** Set character rotation angle
		@param p [IN] rotation angle in degrees
		*/
		virtual void SetRotateAngle(const PMReal& p) = 0;
		/** Get character rotation angle
		@return rotation angle in degrees
		*/
		virtual PMReal GetRotateAngle() const = 0;
	//@}-----------------------------------------------------------------------------
		
	//-------------------------------------------------------------------------------
	/**@name 	Used by shatai	*/
	//@{-----------------------------------------------------------------------------
		/** Set character obliquing (shatai) lens magnification
		@param p [IN] lens magnification
		*/
		virtual void 	SetShataiMagnification(PMReal p) = 0;
		/** Get character obliquing (shatai) lens magnification
		@return lens magnification
		*/
		virtual PMReal	GetShataiMagnification() const = 0;
		/** Set character obliquing (shatai) lens angle
		@param p [IN] lens angle
		*/
		virtual void 	SetShataiAngle(PMReal p) = 0;
		/** Get character obliquing (shatai) lens angle
		@return lens angle
		*/
		virtual PMReal	GetShataiAngle() const = 0;
		/** Set character obliquing (shatai) adjust rotation to match line
		@param p [IN] kTrue if the attribute is on
		*/
		virtual void 	SetShataiAdjustRotation(bool16 p) = 0;
		/** Get character obliquing (shatai) adjust rotation to match line
		@return kTrue if the attribute is on
		*/
		virtual bool16	GetShataiAdjustRotation() const = 0;
		/** Set character obliquing (shatai) adjust tsume (kerning) to make text tighter
		@param p [IN] kTrue if the attribute is on
		*/
		virtual void 	SetShataiAdjustTsume(bool16 p) = 0;
		/** Get character obliquing (shatai) adjust tsume (kerning) to make text tighter
		@return kTrue if the attribute is on
		*/
		virtual bool16	GetShataiAdjustTsume() const = 0;

		/** Transforms the given matrix to match the shatai (character obliquing) settings
		@param pMatrix [IN/OUT] font matrix of the text. Will be transformed with the shatai matrix.
		@param vertical [IN] whether the text is vertical or not
		@param widthAdjustment [OUT] amount to adjust the character widths
		@param widthToEmRatio [IN] ratio of character width to em width
		@param rawShataiMatrix [OUT] matrix with only shatai settings (no external scaling)
		*/
		virtual void	ShataiTransformFontMatrix(PMMatrix *pMatrix, bool16 vertical, PMReal *widthAdjustment = nil, PMReal widthToEmRatio = 1.0, PMMatrix *rawShataiMatrix = nil) const = 0;
	//@}-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name 	OpenType	*/
	//@{-----------------------------------------------------------------------------
		/** Set OpenType feature use horizontal-only or vertical-only kana forms
		@param b [IN] kTrue if the attribute is on
		*/
		virtual void	SetUseHVKana(bool16 b) = 0;
		/** Get OpenType feature use horizontal-only or vertical-only kana forms
		@return kTrue if the attribute is on
		*/
		virtual bool16	GetUseHVKana() const = 0;
		/** Set OpenType feature use proportional Japanese metrics
		@param b [IN] kTrue if the attribute is on
		*/
		virtual void	SetUseProportionalMetrics(bool16 b) = 0;
		/** Get OpenType feature use proportional Japanese metrics
		@return kTrue if the attribute is on
		*/
		virtual bool16	GetUseProportionalMetrics() const = 0;
		/** Set OpenType feature use Roman Italic forms in Japanese fonts
		@param b [IN] kTrue if the attribute is on
		*/
		virtual void	SetUseRomanItalics(bool16 b) = 0;
		/** Get OpenType feature use Roman Italic forms in Japanese fonts
		@return kTrue if the attribute is on
		*/
		virtual bool16	GetUseRomanItalics() const = 0;
	//@}-----------------------------------------------------------------------------

	//-------------------------------------------------------------------------------
	/**@name 	Paragraph attributes	*/
	//@{-----------------------------------------------------------------------------
		/** Specifies the type of kinsoku processing.
		*/
		enum KinsokuType {
			kKinsoku_PushInFirst = 0,
			kKinsoku_PushOutFirst,
			kKinsoku_PushOutOnly,
			kKinsoku_PushInAlways
			};
		/** Set Kinsoku justification type
		@param type [IN] Kinsoku justification type
		*/
		virtual void SetKinsokuType(KinsokuType	type) = 0;
		/** Get Kinsoku justification type
		@return Kinsoku justification type
		*/
		virtual KinsokuType GetKinsokuType() const = 0;
		
		/** Specifies the type of kinsoku hang.
		*/
		enum KinsokuHangType {
			kKinsokuHang_None = 0,		// no burasagari
			kKinsokuHang_Regular,		// IDJ 1.0 style burasagari
            kKinsokuHang_Force			// AI style burasagari
        };
		/** Set Kinsoku hang type
		@param type [IN] Kinsoku hang type
		*/
		virtual void SetKinsokuHangType(KinsokuHangType	type) = 0;
		/** Get Kinsoku hang type
		@return Kinsoku hang type
		*/
		virtual KinsokuHangType GetKinsokuHangType() const = 0;
		/** Set Leading Model basis position (point in the line height from which line leading is to be measured)
		@param m [IN] leading model (implies also leading measurement direction)
		*/
		virtual void SetLeadingModel(Text::LeadingModel m) = 0;
		/** Get Leading Model basis position (point in the line height from which line leading is to be measured)
		@return leading model (implies also leading measurement direction)
		*/
		virtual Text::LeadingModel GetLeadingModel() const = 0;
		/** Set Rensuuji shori (no-break of Japanese numbers)
		@param flag [IN] kTrue if attribute is on
		*/
		virtual void SetRensuuji(bool16	flag) = 0;
		/** Get Rensuuji shori (no-break of Japanese numbers)
		@return kTrue if attribute is on
		*/
		virtual bool16 GetRensuuji() const = 0;
		/** Set Inseparables no-break and no-justify (repeating inseparable characters (from Kinsoku table))
		@param flag [IN] kTrue if attribute is on
		*/
		virtual void SetNotSeparate(bool16 flag) = 0;
		/** Get Inseparables no-break and no-justify (repeating inseparable characters (from Kinsoku table))
		@return kTrue if attribute is on
		*/
		virtual bool16 GetNotSeparate() const = 0;
		/** Set if Ideographic Space will not wrap to next line, like other space chars
		@param flag [IN] kTrue if attribute is on
		*/
		virtual void SetTreatIdeoSpaceAsSpace(bool16 flag) = 0;
		/** Get if Ideographic Space will not wrap to next line, like other space chars
		@return kTrue if attribute is on
		*/
		virtual bool16 GetTreatIdeoSpaceAsSpace() const = 0;
		/** Set if Roman words wrap on any character
		@param flag [IN] kTrue if attribute is on
		*/
		virtual void SetWordWrapOff(bool16 flag) = 0;
		/** Get if Roman words wrap on any character
		@return kTrue if attribute is on
		*/
		virtual bool16 GetWordWrapOff() const = 0;
	//@}-----------------------------------------------------------------------------
		
		// Obsolete/unused methods
	//@{-----------------------------------------------------------------------------
		virtual void SetTsume(const PMReal& ratio) = 0;
		virtual PMReal GetTsume() const = 0;
		virtual void SetRomanMojikumi(bool16 flag) = 0;
		virtual bool16 GetRomanMojikumi() const = 0;
		virtual void SetAdjustFullWidth(bool16	flag) = 0;
		virtual bool16 GetAdjustFullWidth() const = 0;
		virtual void SetAdjustPeriodPos(bool16	flag) = 0;
		virtual bool16 GetAdjustPeriodPos() const = 0;
		virtual void SetKinsokuFlag(bool16	flag) = 0;
		virtual bool16 GetKinsokuFlag() const = 0;
	//@}-----------------------------------------------------------------------------
};


#endif
		// __IMojikumiStyle__
