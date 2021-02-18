//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IWaxStrand.h $
//  
//  Owner: zwilliam
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
#ifndef __IWaxStrand__
#define __IWaxStrand__

#include "IPMUnknown.h"
#include "TextID.h"
#include "CTextEnum.h"
#include "K2Vector.h"
#include "ParcelKey.h"

class IWaxLine;
class IParcelList;
class PMReal;
class IWaxIterator;
class PMPoint;
class PMRect;
class PMLineSeg;
class PMMatrix;
class IGraphicsContext;
class ITextModel;
class IComposeScanner;
class ITiler;
class IParcel;
class ITextParcelList;
class IComposeScanner;
class IParagraphComposer;
class IFrameList;
class IControlView;
#ifdef DEBUG
class CompositionTic;
#endif
#include "IStrand.h"

typedef std::pair<IWaxLine*, int32>				WaxLineApplyEntry;
DECLARE_BASE_TYPE(WaxLineApplyEntry);
typedef K2Vector<WaxLineApplyEntry>	WaxLineApplyList;

class IdleTimer;

/** This interface owns the wax for a story. A callback interface is provided to allow
	the wax for a story to be iterated over.
	@ingroup text_wax
*/
class IWaxStrand : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWAXSTRAND };

#ifdef DEBUG
	virtual void TraceStrandContents() = 0;
#endif
	
	virtual void MarkInsertDamage(TextIndex at, int32 amt) = 0;
	virtual void MarkDeleteDamage(TextIndex start, int32 length,
									bool16 paraStrandAfter = kTrue) = 0;

		// mark change damage should be filtered through the text model : ForceRecompositionDamage()
	virtual void MarkChangeDamage(TextIndex start, int32 length, bool16 addOneToLength = kFalse) = 0;

	enum CheckForKeeps { kDontCheckForKeeps = 0, kCheckForKeeps = 1 };
	enum TreatAsOverset { kDontTreatAsOverset = 0, kTreatAsOverset = 1 };
	virtual void MarkGeometryDamage(TextIndex start, int32 length,
					CheckForKeeps checkForKeeps = kCheckForKeeps,
					TreatAsOverset treatAsOverset = kDontTreatAsOverset,
					int32 limitLeanLeftParcelIndex = kInvalidParcelIndex) = 0;

	virtual void MarkRegenDamage(TextIndex start, int32 length) = 0;
	virtual void MarkContentDamage(TextIndex start, int32 length,
							CheckForKeeps checkForKeeps = kCheckForKeeps) = 0;	

	/**
	Returns a WaxIterator.
	@param changeAware If kTrue the iterator will not ASSERT if WaxLines change size during the life of the iterator.
	@return - a WaxIterator
	*/
	virtual IWaxIterator*	NewWaxIterator(bool16 changeAware = kFalse) const = 0;
	/**
	Returns a WaxIterator. For code that will not change wax lines or Apply wax
	lines. e.g. code that draws. Provides optimization on IWaxLine::TextOrigin
	call.
	@return - a WaxIterator
	*/
	virtual const IWaxIterator * NewReadOnlyWaxIterator() const = 0;

	virtual IWaxLine*		QueryNewWaxLine() const = 0;
	virtual void			ApplyLineIntoWax(IParcelList* pl,
									IWaxLine* waxLine,
									TextIndex waxLineTextIndex,
									int32 waxLineSpan,
									bool16 disableApplyInval) = 0;
	virtual void			NewDeferredInval() = 0;
	virtual void			AddDeferredInval(TextIndex at, bool16 disableInval,
									bool16 forceInkCache) = 0;
	virtual void			EndDeferredInval() = 0;

	enum {kLeanRight = 0, kLeanLeft = 1};
	virtual bool16 		GetTextIndexToWaxLineData(TextIndex index,
								bool16 leanLeft,
								int32 *pOffsetWithinLine = nil,
								int32 *pTextSpan = nil,
								ParcelKey *pParcelKey = nil,
								UID *pFrameUID = nil,
								PMReal *pLineHeight = nil,
								PMLineSeg *pSelection = nil,
								PMPoint *pWaxPt = nil,		// YPosition
								PMMatrix *pWaxToFrameMatrix = nil,
								PMMatrix *pWaxToGlyphMatrix = nil) = 0;

	virtual bool16		GetTextCaretLine( IFrameList* frameList,
								const IControlView* layoutView,
								TextIndex index,
								bool16 leanLeft,
								PMLineSeg* pCaretLine,
								UIDRef& textFrameUIDRef,
								ParcelKey& parcelKey) = 0;

	// This interface exists for legacy purposes, it internally calls
	// GetTextIndexToWaxLineData(). You should use that one too. pLocationHit
	// is returned in pasteboard coordinates BUT without having done any
	// waxToGlyphTransformation.
	virtual ITextFrameColumn * QueryFrameContaining(TextIndex indexHit,
						bool16 leanLeft /* = kFalse*/,
						PMPoint * pLocationHit = nil,	// pasteboard coord.
						PMReal * hitLineSelectionTop = nil,
						PMReal * hitLineSelectionBottom = nil) = 0;

	struct CallbackWaxIteratorData
	{
		PMReal		prevSelectionBottom;	// valid if !prevInvalid
		PMReal		prevSelectionTop;

		PMReal		thisSelectionTop;
		PMReal		thisSelectionBottom;

		PMReal		nextSelectionTop;		// valid if !nextInvalid

		IWaxLine	*waxLine;
		int32		localOffset;
		bool16		prevInvalid;			// kTrue if no interfering neighbor
		bool16		nextInvalid;			// kTrue if no interfering neighbor

		CallbackWaxIteratorData() :
				prevSelectionBottom(0.), prevSelectionTop(0.),
				thisSelectionTop(0.), thisSelectionBottom(0.),
				nextSelectionTop(0.), waxLine(nil),
				localOffset(0), prevInvalid(kFalse), nextInvalid(kFalse)
			{ }
	};

	virtual void CallbackWaxIterator(TextIndex start,
						bool16 (*callback)(void *priv,
											const CallbackWaxIteratorData *),
						void *callback_priv) = 0;

	//
	// Return the ParagraphComposer for the given WaxLine.
	//
	virtual IParagraphComposer *	QueryComposer(ITextModel* textModel,
												const IWaxLine* waxLine,
												TextIndex waxLineTextIndex) = 0;

	/// Returns the ParagraphComposer for the specified class id.
	virtual IParagraphComposer* QueryComposer(ClassID composerID) = 0;

	//
	// Notification of the creation/deletion of a StoryThread.
	//
	virtual void	StoryThreadCreated(TextIndex prevThreadStart,
										int32 prevThreadSpan,
										TextIndex newThreadStart,
										int32 newThreadSpan) = 0;

	virtual void	StoryThreadDeleted(TextIndex prevThreadStart,
										int32 prevThreadSpan,
										TextIndex oldThreadStart,
										int32 oldThreadSpan) = 0;

	//
	// FreezeDamage
	// For internal use. This method allows for a performance optimization by flipping
	// a flag that bypasses damage recording in wax. If damage is frozen all calls
	// to MarkChangeDamage and MargRegenDamage are ignored.
	// If used incorrectly this could leave the wax in a bad state and out of sync with 
	// the the model. The idea is to freeze damaging of wax in cases where we know that 
	// everything is damaged to start with. 
	// The freeze flag is non persistent. So make sure you hold on to the IWaxStrand interface
	// for the scope of the freeze/unfreeze.
	// Returns the previous freeze damage state
	virtual bool16		FreezeDamage(bool16 freeze) = 0;
	virtual int32 MarkPasteDamage(TextIndex pos, int32 len) = 0;
	virtual ITextModel * QueryTextModel() = 0;

	// Adobe internal use only
	virtual void ConvertAnnaTableFrameWaxLines(TextIndex at, int32 lineCount) = 0;
	virtual void MarkReplaceDamage(const boost::shared_ptr<ITextModel::ReplacementList  >& replList) = 0;
#ifdef DEBUG
	virtual void CheckFishyWaxWorld() const = 0;
#endif
};

#endif
