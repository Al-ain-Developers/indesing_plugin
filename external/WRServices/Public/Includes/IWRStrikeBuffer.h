//========================================================================================
//  
//  File: IWRStrikeBuffer.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __IWRStrikeBuffer__
#define __IWRStrikeBuffer__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"
#include "IWRStrike.h"

#ifdef WR_WIN_ENV
#pragma warning(disable:4250)
#endif

/// Strike Buffer interface
/**
IWRStrikeBuffer is an abstract interface to access dynamic arrays of strikes (StrikeBuffer).
Strikes (OptycaStrike) are accessed thru a IWRStrike.
A strike buffer also maintains an end position, a trailing width and an ideal end position.
The ideal position of a strike is where it should ideally lay to get a perfect full justification or tracking,
it there were no limitations linked to cursivity.
A region of interest can be created to bufferize insertion and deletion and make them more efficient
**/

class WRSERVICES_DECL IWRStrikeBuffer
{
public:
	virtual				~IWRStrikeBuffer() {}
	/// Return the ith strike
	/**
	@param i a WRInt32 index of the strike
	@return a reference to a IWRStrike
	**/
	virtual IWRStrike&	GetStrike(WRInt32 i) = 0;
	
	/// Number of strikes in the buffer
	virtual WRInt32		Size(void) const = 0;
	
	/// Remove strikes from the buffer
	/**
	@param start a WRInt32 index of the first strike to remove
	@param count a WRInt32 number of strikes to remove (default=1)
	**/	
	virtual void		Remove(WRInt32 start, WRInt32 count = 1) = 0;

	/// Insert strikes in the buffer
	/**
	Insert count strikes a index start, initializing them to *item if item is not NULL
	@param item a pointer to a IWRStrike used to initialize the new strikes (may be NULL)
	@param start a WRInt32 index of the first strike to remove
	@param count a WRInt32 number of strikes to insert (default=1)
	@return a WRError
	**/	
	virtual WRError		Insert(IWRStrike* item, WRInt32 start, WRInt32 count = 1) = 0;
	
	/// Append a strike to the region of interest
	/**
	Insert one strikes at the end of the region of interest, initializing its segment index. 
	This method is mainly used by external modules, but not by the build-in OT-based processing.
	@param segIndex a pointer to a IWRStrike used to initialize the new strikes (may be NULL)
	@return a IWRStrike pointer to the new strike
	@sa SetRegionOfInterest, ClearRegionOfInterest, InsertInTarget, RemoveFromTarget, GetRegionOfInterest
	**/	
	virtual IWRStrike*	AppendNew(WRInt32 segIndex) = 0;
	
	/// Reset the x and y positions of a range of strike
	/**
	Set to 0,0 the position of strikes between start and start+count
	@param start a WRInt32 index of the first strike
	@param count a WRInt32 number of strikes
	@sa IWRStrike::GetXPosition, IWRStrike::XPosition, IWRStrike::GetYPosition, IWRStrike::SetYPosition
	**/	
	virtual void		ResetPositions(WRInt32 start, WRInt32 count) = 0;
	
	/// Reset the x and y offsets of a range of strike
	/**
	Set to 0,0 the offsets of strikes between start and start+count
	@param start a WRInt32 index of the first strike
	@param count a WRInt32 number of strikes
	@sa IWRStrike::GetXOffset, IWRStrike::SetXOffset, IWRStrike::GetYOffset, IWRStrike::SetYOffset
	**/	
	virtual void		ResetMarkPositions(WRInt32 start, WRInt32 count) = 0;
	
	/// Reset the change attribute of a range of strike
	/**
	Set to 0 the change attribute of strikes between start and start+count
	@param start a WRInt32 index of the first strike
	@param count a WRInt32 number of strikes
	@sa IWRStrike::GetChangeAttrib, IWRStrike::SetChangeAttrib
	**/	
	virtual void		ResetChangeAttribs(WRInt32 start, WRInt32 count) = 0;
	
	/// Apply a many(consecutive)-by-one substitution
	/**
	Replace a consecutive sequence of glyphs by another glyph (ligature). This method is used to implement one of the callback of OT processing
	@param where a WRInt32 index of the first strike to ligate
	@param newGlyphId a WRGlyphID32 glyph id of the ligature
	@param count a WRInt32 number of components in the ligature
	@param termDiacCount a WRInt32 reference containing on return the number of marks at the end of the ligature (used to implement a consistent mark behavior)
	@return a WRError
	**/
	virtual WRError		ReplaceRangeByOne(WRInt32 where, WRGlyphID32 newGlyphId, WRInt32 count, WRInt32& termDiacCount) = 0;
	
	/// Apply a one-by-one substitution
	/**
	Replace a glyph by another glyph (variant substitution). This method is used to implement one of the callback of OT processing
	@param where a WRInt32 index of the strike to replace
	@param newGlyphId a WRGlyphID32 glyph id of the ligature
	@return a WRError
	**/
	virtual WRError		ReplaceOneByOne(WRInt32 where, WRGlyphID32 newGlyphId) = 0;

	/// Apply a one-by-many substitution
	/**
	Replace a glyph by a sequence glyph (decomposition). This method is used to implement one of the callback of OT processing
	@param where a WRInt32 index of the strike to decompose
	@param newGlyphIds a pointer to WRGlyphID32 glyph id array containing the decomposition
	@param count a WRInt32 number of components	
	@return a WRError
	**/
	virtual WRError		ReplaceOneByMany(WRInt32 where, const WRGlyphID32* newGlyphIds, WRInt32 count) = 0;

	/// Apply a many(non consecutive)-by-one substitution
	/**
	Replace a non consecutive sequence of glyphs by another glyph (ligature). 
	Skipped glyphs are left in the original order after the replaced first glyph.
	This method is used to implement one of the callback of OT processing
	@param start a WRInt32 index of the first strike to ligate
	@param offsets a pointer to an array of WRInt32 containing the offsets of each component relatively to the start index
	@param newGlyphId a WRGlyphID32 glyph id of the ligature
	@param count a WRInt32 number of components in the ligature
	@param termDiacCount a WRInt32 reference containing on return the number of marks at the end of the ligature (used to implement a consistent mark behavior)
	@return a WRError
	**/
	virtual WRError		ReplaceManyByOne(WRInt32 start, const WRInt32* offsets, WRGlyphID32 newGlyphId, WRInt32 count, WRInt32& termDiacCount) = 0;

	/// Apply position adjustment
	/**
	Move a glyph and / or change its advance 
	NB: Those adjustments go to the X and Y Offsets of the strikes and are later converted to real position ajustements by Lipika if needed
	This method is used to implement one of the callback of OT processing
	@param strikeIndex a WRInt32 index of the strike to adjust
	@param endStrikeIndex a WRInt32 index of the end strike (past the last) up to which a advance ajustment must be propagated
	@param xPlacementDelta a float containing the x offset (not propagated), for a 1 pt font (scaled to the effective size later by Optyca)
	@param yPlacementDelta a float containing the y offset (not propagated), for a 1 pt font (scaled to the effective size later by Optyca)
	@param xAdvanceDelta a float containing the x advance adjustment (propagated), for a 1 pt font (scaled to the effective size later by Optyca)
	@param yAdvanceDelta a float containing the y advance adjustment (currently ignored), for a 1 pt font (scaled to the effective size later by Optyca)
	@param rtl a bool true if the text is writteng right to left
	@param isMark a bool true if the moved glyph is a mark (only affects the type of the change in the change attrbute)
	**/
	virtual void		AdjustPlacementAndAdvance(WRInt32 strikeIndex, WRInt32 endStrikeIndex, WRFloat xPlacementDelta, WRFloat yPlacementDelta, WRFloat xAdvanceDelta, WRFloat yAdvanceDelta, bool rtl, bool isMark) = 0;

	/// Align anchors
	/**
	Apply positional adjustmenst by aligning OT anchors
	NB: Those adjustments go to the X and Y Offsets of the strikes and are later converted to real position ajustements by Lipika if needed
	This method is used to implement one of the callback of OT processing
	@param elementIndex1 a WRInt32 index of the first strike (in logical order)
	@param anchor1x a float containing the x coordinate of the anchor on the first strike, for a 1 pt font (scaled to the effective size later by Optyca)
	@param anchor1y a float containing the y coordinate of the anchor on the first strike, for a 1 pt font (scaled to the effective size later by Optyca)	
	@param isMark1 a bool true if the first glyph is a mark
	@param elementIndex2 a WRInt32 index of the second strike (in logical order)
	@param anchor2x a float containing the x coordinate of the anchor on the second strike, for a 1 pt font (scaled to the effective size later by Optyca)
	@param anchor2y a float containing the y coordinate of the anchor on the second strike, for a 1 pt font (scaled to the effective size later by Optyca)
	@param isCursiveAttachment a bool true if the alignment is aimed to attch cursive base glyphs
	@param lastOnBaseline a bool true if during cursive attachment, the second glyph sticks to the baseline and the first one is move (e.g. Arabic)
	@todo lastOnBaseline=false is currently not supported by Optyca
	**/
	virtual void		MergeAnchors (WRInt32 elementIndex1, WRFloat anchor1x, WRFloat anchor1y, bool isMark1, WRInt32 elementIndex2, WRFloat anchor2x, WRFloat anchor2y, bool isCursiveAttachment, bool lastOnBaseline) = 0;

	/// Sets a region of interest
	/** A region of interest (ROI) can be set temporarily of a strike buffer. Its purpose is to limit
	the range and number of shifts performed on the whole buffer when applying many insertions and deletions on a
	limited range of strikes. 
	Once set, operations must be performed only inside its boundaries. Deleting a strike only shifts up to the end of the ROI,
	creating a empty slot after it. The ROI keep track of ROI size and of the number of free slots.
	When inserting a strike, strikes up to the end of the ROI at pushed, and the strikes after the ROI and pushed only
	if there was no free slot left. When the ROI is cleared, the remaining free slots are disposed by shifting the end strikes.
	@param target a WRInt32 index of the end of ROI (there is no benefit in setting a start index)
	@sa ClearRegionOfInterest, InsertInTarget, RemoveFromTarget, GetRegionOfInterest
	**/
	virtual void		SetRegionOfInterest(WRInt32 target) = 0;
	
	/// Unset the region of interest
	/**
	Delete the remaining free slots by shifting the end strikes and resizing the buffer
	@sa SetRegionOfInterest, InsertInTarget, RemoveFromTarget, GetRegionOfInterest, AppendNew
	**/
	virtual void		ClearRegionOfInterest() = 0;
	
	/// Insert empty strikes in the region of interest
	/**
	When inserting a strike, strikes up to the end of the ROI at pushed, and the strikes after the ROI and pushed only
	if there was no free slot left. 
	@param pos a WRInt32, index where strikes must be inserted
	@param count a WRInt32 number of strikes to insert
	@sa SetRegionOfInterest, ClearRegionOfInterest, RemoveFromTarget, GetRegionOfInterest, AppendNew
	**/
	virtual WRError		InsertInTarget(WRInt32 pos, WRInt32 count) = 0;

	/// Delete from the region of interest
	/**
	Deleting a strike only shifts strikes up to the end of the ROI, creating a empty slot after it.  
	@param pos a WRInt32, index of the first strike to be removed
	@param count a WRInt32 number of strikes to delete
	@sa SetRegionOfInterest, ClearRegionOfInterest, InsertInTarget, GetRegionOfInterest, AppendNew
	**/
	virtual void		RemoveFromTarget(WRInt32 pos, WRInt32 count) = 0;
	
	/// Size the region of interest
	/**
	Return the current size of the ROI
	@return  a WRInt32 number of strikes in the ROI
	@sa SetRegionOfInterest, ClearRegionOfInterest, InsertInTarget, RemoveFromTarget, AppendNew
	**/
	virtual WRInt32		GetRegionOfInterest(void) const = 0;

	/// Get the ideal X position of a strike
	/**
	Return the ideal x position of a strike identified by its index. If this index is equal to Size(), then
	the ideal width of the buffer is returned, so that the caller doesn't need to check if GetIdealWidth or
	GetIdealXPosition must be called
	@param i a WRInt32 the index of the strike
	@return  a WRInt32 x position of the strike
	@sa GetIdealXPosition, GetWidth
	**/
	virtual WRFloat		GetIdealXPosition(WRInt32 i) const = 0;
	
	/// Get the X position of a strike
	/**
	Return the x position of a strike identified by its index. If this index is equal to Size(), then
	the width of the buffer is returned, so that the caller doesn't need to check if GetWidth or GetXPosition must be called
	@param i a WRInt32 the index of the strike
	@return  a WRInt32 x position of the strike
	@sa GetIdealXPosition, GetWidth
	**/
	virtual WRFloat		GetXPosition(WRInt32 i) const = 0;
	
	/// Get the width of the strike buffer
	/**
	Returns the width of the strike buffer, i.e. the position after its last strike
	@return a WRFloat 
	@sa SetWidth, AddWidth
	**/
	virtual WRFloat		GetWidth(void) const = 0; 

	/// Set the width of the strike buffer
	/**
	Change the width of the strike buffer, i.e. the position after its last strike, to a given value
	@param w a WRFloat, the new width
	@sa GetWidth, AddWidth
	**/
	virtual void		SetWidth(WRFloat w) = 0;

	/// Increase the width of the strike buffer
	/**
	Increase the width of the strike buffer, i.e. the width of its last strike, by a given amount
	@param w a WRFloat, the width to be added to the last strike
	@sa GetWidth, SetWidth
	**/
	virtual void		AddWidth(WRFloat w) = 0;
	
	
	/// Get the ideal width of the strike buffer
	/**
	Returns the ideal width of the strike buffer, i.e. the ideal position after its last strike
	@return a WRFloat 
	@sa SetIdealWidth, AddIdealWidth
	**/
	virtual WRFloat		GetIdealWidth(void) const = 0;
	
	/// Set the ideal width of the strike buffer
	/**
	Change the ideal width of the strike buffer, i.e. the ideal position after its last strike, to a given value
	@param w a WRFloat, the new ideal width
	@sa GetIdealWidth, AddIdealWidth
	**/
	virtual void		SetIdealWidth(WRFloat w) = 0;

	/// Increase the ideal width of the strike buffer
	/**
	Increase the ideal width of the strike buffer, i.e. the ideal width of its last strike, by a given amount
	@param w a WRFloat, the ideal width to be added to the last strike
	@sa GetIdealWidth, SetIdealWidth
	**/
	virtual void		AddIdealWidth(WRFloat w) = 0;
	
	/// Get the trailing width of the strike buffer
	/**
	Returns the trailing width of the strike buffer, i.e.  the non marking width that must be ignore when full-justifying, for example
	@return a WRFloat 
	@sa SetTrailingWidth, SetWidth
	**/
	virtual WRFloat		GetTrailingWidth(void) const = 0;
	
	/// Set the trailing width of the strike buffer
	/**
	Set the non marking width that must be ignore when full-justifying, for example
	@param w a WRFloat, the new trailing width
	@sa GetWidth, GetTrailingWidth
	**/
	virtual void		SetTrailingWidth(WRFloat w) = 0;
	
	/// Get the marking width of the strike buffer
	/**
	Returns the width of the strike buffer without the trailing width
	@return a WRFloat 
	@sa GetTrailingWidth, GetWidth
	**/
	virtual WRFloat		GetWidthWithoutTrailing(void) const = 0;
	
	virtual void		TransferAdvance(WRInt32 pos) = 0;
	
	/// Advance adjustement
	/**
	Moves horizontally all the strikes including and after a given index by a given amount.
	The net effect is to change the advance of the previous strike.
	This method is currently used only by external modules.
	@param startIndex a WRInt32 index of the first strike to move
	@param amount a WRFloat x offset to be added to strikes (in pts)
	**/
	virtual void		StrikeHorizontalShift(WRInt32 startIndex,WRFloat amount) = 0;
};

#endif
