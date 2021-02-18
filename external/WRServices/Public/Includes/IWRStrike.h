//========================================================================================
//  
//  File: IWRStrike.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2010 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __IWRStrike__
#define __IWRStrike__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"
#include "IWRChar.h"

#ifdef WR_WIN_ENV
#pragma warning(disable:4250)
#endif

/// Interface to access strikes
/**
This interface exposes the strike objects to the outside of optyca: client application but also extension modules.
The exposed attributes are the style, glyph ID and  position, as well as a couple of attributes which are required
very often during the processing (OT glyph class, OT operation performed on the strike).
The strike drawing position is made of the advance position (x and y position), the raw width and an offset (mainly diac offset). The raw width is the advance of glyph coming from the font, before letter 
spacing, tracking, kerning, justification are applied. These raw advance are necessary to compute an offset to be added to xpositions before
drawing, so that RTL glyphs are drawn aligned with the right side of their advance cells, instead of with the left side. 
Strikes are almost always accessed as items of IWRStrikeBuffer
@sa OptycaStrike, IWRStrikeBuffer, StrikeBuffer, OptycaRunSettings, OptycaCharType
**/

class WRSERVICES_DECL IWRStrike
{
public:
	/// constants for representing OT glyph classes
	enum WRGlyphClassValue {
		kWRGlyphClassValue_Unknown = 0,		///< class info not available or not computed yet
		kWRGlyphClassValue_Base = 1,		///< base glyph
		kWRGlyphClassValue_Ligature = 2,	///< result of a n-1 substitution
		kWRGlyphClassValue_Mark = 3,		///< combining mark
		kWRGlyphClassValue_Component = 4	///< result of a 1-n substitution
	};


	/// constants for the kind of connection attachment with the previuous glyph
	enum ConnectionType { 
				kNoConnection,		
				kSoftConnection,		///< connecting, apply stretching/kashida
				kPostSeenConnection,	///< privilegied place for naskh kashidas
				kKafAlifLikeConnection, ///< not eligible for Naskh kashidas
				kManualKashidaConnection, ///< 
				kHardConnection,		///< connecting, don't apply stretching/kashida
				//kStretchedConnection, // connection stretched by the user, do not stretch the word 
				kDiacConnection			///< holder is a mark, should be ignore when processing connections
	};

	enum WRGlyphClassExtendedFlags { 
		kWRGlyphClassExtended_kMoveableMark = 1,			///< set if the glyph is a mark and is ok to move away from baseline (ie: Arabic vowel or shadda)
		kWRGlyphClassExtended_Last = 1			///< hihest bit mask used by the lipika core code
	};

	virtual ~IWRStrike();
	virtual WRGlyphID32 GetGlyphID(void) const = 0;			///< get the glyph id
	virtual void		SetGlyphID(WRGlyphID32 gid) = 0;	///< set glyph id

	virtual WRFloat		GetXPosition(void) const = 0;		///< get the x-position 
	virtual void		SetXPosition(WRFloat x) = 0;		///< set the x-position
	virtual void		MoveXPosition(WRFloat dx) = 0;		///< move the glyph horizontally

	virtual WRFloat		GetYPosition(void) const = 0;		///< get the y-position 
	virtual void		SetYPosition(WRFloat y) = 0;		///< set the y-position
	virtual void		MoveYPosition(WRFloat dy) = 0;		///< move the glyph vertically

	virtual WRFloat		GetXOffset(void) const = 0;			///< get the additional x-offset
	virtual void		SetXOffset(WRFloat x) = 0;			///< set the additional x-offset
	virtual void		MoveXOffset(WRFloat dx) = 0;		///< increase the additional x-offset

	virtual WRFloat		GetYOffset(void) const = 0;			///< get the additional y-offset
	virtual void		SetYOffset(WRFloat y) = 0;			///< set the additional y-offset
	virtual void		MoveYOffset(WRFloat dy) = 0;		///< increase the additional y-offset

	virtual WRFloat		GetWidth(void) const = 0;			///< get the raw glyph width
	virtual void		SetWidth(WRFloat w) = 0;			///< set the raw glyph width

	virtual WRUInt8		GetChangeAttrib(void) const = 0;	///< get the report of OT operation perfomed on the strike
	virtual void		SetChangeAttrib(WRUInt8 a) = 0;		///< set the report of OT operation perfomed on the strike

	virtual WRUInt8		GetGlyphClass(void) const = 0;		///< get the strike OT glyph class @sa WRGlyphClassValue
	virtual void		SetGlyphClass(WRUInt8 c) = 0;		///< set the strike OT glyph class @sa WRGlyphClassValue

	virtual WRUInt32	GetGlyphClassExtended(void) const = 0;		///< get the strike OT extended glyph class 
	virtual void		SetGlyphClassExtended(WRUInt32 c) = 0;		///< set the strike OT extended glyph class 

	virtual OptycaCharType GetCharType(void) const = 0;		///< get the internal char type associated with the strike 
	virtual void		SetCharType(OptycaCharType t) = 0;	///< set the internal char type associated with the strike

	virtual StyleRef	GetStyle(void) const = 0;			///< get the style of the first char component of the strike (gives the drawing attributes)
	virtual void		SetStyle(StyleRef s) = 0;			///< set the style of the first char component of the strike (gives the drawing attributes)

	virtual StyleRef	GetEndStyle(void) const = 0;		///< get the style of the last char component of the strike (gives the kerning after the glyph)
	virtual void		SetEndStyle(StyleRef s) = 0;		///< set the style of the last char component of the strike (gives the kerning after the glyph)

	virtual ConnectionType	GetConnectionType(void) const = 0;	///< get the connection type after the strike
	virtual void		SetConnectionType(ConnectionType t) = 0;///< set the connection type after the strike

	virtual WRFloat		GetSpaceWidth(void) const = 0;		///< get the width of regular space (cache for the value coming from the font)
	virtual void		SetSpaceWidth(WRFloat w) = 0;		///< set the width of regular space (cache for the value coming from the font)

	virtual WRFloat		GetHSize(void) const = 0;			///< get the actual horizontal pt size 
	virtual void		SetHSize(WRFloat h) = 0;			///< set the actual horizontal pt size

	virtual const OptycaRunSettings&	GetSettings(void) const  = 0;	///< get the actual horizontal pt size 
	virtual void		SetSettings(const OptycaRunSettings& s) = 0;	///< set the actual horizontal pt size

	virtual WRInt8		GetLeftConnection(void) const = 0; ///< get the kind of connection with previous
	virtual void		SetLeftConnection(WRInt8) = 0; ///< set the kind of connection with previous
protected:
};


#endif
