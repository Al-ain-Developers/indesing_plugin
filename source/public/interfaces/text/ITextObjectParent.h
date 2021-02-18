//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextObjectParent.h $
//  
//  Owner: Jonathan W. Brown
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
#ifndef __ITextObjectParent__
#define __ITextObjectParent__

#include "ITextStoryThread.h"

#include "ScriptData.h"
#include "TextID.h"

/**
	This interface must be implemented for any scripting object that wants to act as a parent
	of text objects in the scripting DOM.
	
	For example, you might have a scripting resource like the following. Note that the provider 
	should be set to the kTextScriptProviderBoss, which knows how to use the ITextObjectParent
	implementations to service GetObject requests and Count events (@see IScriptProvider).
	
        Provider
        {
            kTextScriptProviderBoss,
            {
                Parent{ kFootnoteObjectScriptElement },

                RepresentObject{ kTextObjectScriptElement },
                RepresentObject{ kInsertionPointObjectScriptElement },
                RepresentObject{ kCharacterObjectScriptElement },
                RepresentObject{ kWordObjectScriptElement },
                RepresentObject{ kLineObjectScriptElement },
                RepresentObject{ kParagraphObjectScriptElement },
                RepresentObject{ kTextStyleRangeObjectScriptElement },

                CollectionMethod{ kCountMethodScriptElement },
            }
        }

	The implementation should be aggregated onto a boss that also aggregates 
	the IScript. For example:

		Class
		{
			kFootnoteReferenceBoss,
			kInvalidClass,
			{
				...
				IID_ITEXTSTORYTHREAD,       kFootnoteStoryThreadImpl,
				IID_ISCRIPT,                kFootnoteScriptImpl,
				IID_ITEXTOBJECTPARENT,		kFootnoteTextObjectParentImpl,
				...
			}
		}

	Note that it is possible to be a host for these objects without actually
	being the true parent. Consider the case of the MultiColumnTextFrame - it
	wants to return the Lines, Words, etc within it's composed span but the
	true parent of the objects will be the Story.

	Implementations that wish to be full parents must implement the
	ITextStoryThread::QueryParent() method to return a IScript object. In the
	example above, the Footnote simply returns a pointer to itself since it
	has an IScript interface.

*/
class ITextObjectParent : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTOBJECTPARENT } ;

	///
	class PUBLIC_DECL RangeIter
	{
	public:
		virtual ~RangeIter();

		/**
		Returns the first range (if any) managed by the parent. The range
		may include the final CR of the TextStoryThread not
		@param textModelUID
		@param threadStart The TextIndex of the start of the Thread
		@param threadSpan The number of characters in the Thread
		@param adjThreadStart The adjusted TextIndex of the start of the Thread. For more applications this will be the same as threadStart. However, some implementations such as the backing store wish to prevent access to some number of chracters at the start and end of the story thread without disguising the true thread boundries. All extending adjustments that take for things like Words, Lines, TextStyleRanges, etc will be clipped to the adjThreadStart and adjThreadSpan.
		@param adjThreadSpan The adjusted number of characters in the Thread
		@param rangeStart The TextIndex of the start of the range within which text objects will be found
		@param rangeSpan The number of characters in the range within which text objects will be found - may be zero.
		@return kTrue if there is a first Range, kFalse otherwise
		*/
		virtual bool16	GetFirstRange(UIDRef& textModelRef,
									InterfacePtr<const ITextStoryThread>& thread,
									TextIndex& threadStart,
									int32& threadSpan,
									TextIndex& adjThreadStart,
									int32& adjThreadSpan,
									TextIndex& rangeStart,
									int32& rangeSpan) = 0;

		/**
		Returns a subsequent range (if any) managed by the parent. The range
		may include the final CR of the TextStoryThread not
		@param threadStart The TextIndex of the start of the Thread
		@param threadSpan The number of characters in the Thread
		@param adjThreadStart The adjusted TextIndex of the start of the Thread. For more applications this will be the same as threadStart. However, some implementations such as the backing store wish to prevent access to some number of chracters at the start and end of the story thread without disguising the true thread boundries. All extending adjustments that take for things like Words, Lines, TextStyleRanges, etc will be clipped to the adjThreadStart and adjThreadSpan.
		@param adjThreadSpan The adjusted number of characters in the Thread
		@param rangeStart The TextIndex of the start of the range within which text objects will be found
		@param rangeSpan The number of characters in the range within which text objects will be found - may be zero.
		@return kTrue if there is a subsequent Range, kFalse otherwise
		*/
		virtual bool16	GetNextRange(InterfacePtr<const ITextStoryThread>& thread,
									TextIndex& threadStart,
									int32& threadSpan,
									TextIndex& adjThreadStart,
									int32& adjThreadSpan,
									TextIndex& rangeStart,
									int32& rangeSpan) = 0;

	protected:
		RangeIter();
		RangeIter(const RangeIter& other);

	};

	/// Helper class for those implemenations that only have a single range
	class PUBLIC_DECL SingleRangeIter : public RangeIter
	{
	public:
		SingleRangeIter(const UIDRef& textModelRef,
						const ITextStoryThread* thread,
						TextIndex threadStart, int32 threadSpan,
						// adjThreadStart, adjThreadSpan set to thread values
						TextIndex rangeStart, int32 rangeSpan);

		SingleRangeIter(const UIDRef& textModelRef,
						const ITextStoryThread* thread,
						TextIndex threadStart, int32 threadSpan,
						TextIndex adjThreadStart, int32 adjThreadSpan,
						TextIndex rangeStart, int32 rangeSpan);

		bool16	GetFirstRange(UIDRef& textModelRef,
								InterfacePtr<const ITextStoryThread>& thread,
								TextIndex& threadStart,
								int32& threadSpan,
								TextIndex& adjThreadStart,
								int32& adjThreadSpan,
								TextIndex& rangeStart,
								int32& rangeSpan)
			{
			textModelRef = fTextModelRef;
			thread = fThread;
			threadStart = fThreadStart;
			threadSpan = fThreadSpan;
			adjThreadStart = fAdjThreadStart;
			adjThreadSpan = fAdjThreadSpan;
			rangeStart = fRangeStart;
			rangeSpan = fRangeSpan;
			return kTrue;
			}

		bool16	GetNextRange(InterfacePtr<const ITextStoryThread>& thread,
								TextIndex& threadStart,
								int32& threadSpan,
								TextIndex& adjThreadStart,
								int32& adjThreadSpan,
								TextIndex& rangeStart,
								int32& rangeSpan)
			{ return kFalse; }

	private:
		UIDRef									fTextModelRef;
		InterfacePtr<const ITextStoryThread>	fThread;
		TextIndex								fThreadStart;
		int32									fThreadSpan;
		TextIndex								fAdjThreadStart;
		int32									fAdjThreadSpan;
		TextIndex								fRangeStart;
		int32									fRangeSpan;

	};
		
	/**
	Returns a RangeIter object that can be used to return one or more ranges
	of a specific TextModel where TextObjects can be found.
	@return Pointer to new RangeIter object that must be deleted by the caller when it is done.
	*/
	virtual RangeIter*	CreateRangeIterFor(const ScriptInfo::RequestContext& context, ScriptID childType) const = 0;

};

#endif
