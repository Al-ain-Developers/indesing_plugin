//========================================================================================
//  
//  File: SubstitutionLog.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __SubstitutionLog__
#define __SubstitutionLog__

#include "WRConfig.h"

#include "WRDefines.h"
#include "WRClass.h"
#include "WRVector.h"

#include <memory.h>
#ifdef WR_MAC_ENV
#include <string.h>
#endif

#ifdef WR_MAC_ENV
#pragma options align=power
#endif

typedef WRInt32			SLIndex;
typedef unsigned char	SLCount;
typedef unsigned char	SLOperation;
typedef WRInt32	SLInnerPosition;
#define SLINVALIDINDEX 0xFFFF

#define kHundredPerCent 100

/*
The substitution log object is used to do a 
journaling of operations perform on an array of 
strikes:
- Single substitutions : in order to know if a strike has been replaced
- Multiple substitutions : one glyph replaced by many (AXt glyphs, calculated text)
- Ligatures : multiple glyphs replaced by one
- Deletion : glyphs removed from the array (soft hyphens, zw spaces, ...)
- Swapping : the order of glyphs are reversed other a segment (often the whole array)
	this is important for dealing easily with the drawing order. the analyzer 
	applies a swap before positionning diacs, if the input is RTL
- Move: used when reordering runs (to be implemented)
	usually not issued by the analyzer itself, but by the client, run-by-run
	analysis loop

The sublog also hold the clustering information: it's a partition of the input stream
in base+mark(s) sequences. This information was by the past recorded as a special op in the 
journal. It has be moved in a separate place because it wasn't easy to catenate.


Logs must be concateneted when merging strike arrays.

Once the modifications on a strike array are completed, the log
may be used to implement the mapping from characters to glyphs (text hiliting for example)
and from the glyph to character (hittest). 

Both mappings may be made very accurately, even in complex situations: the inner position 
is a percentage of either the character or the glyph. For example, when dealing with a hittest,
the innerPos is computeed from the target glyph origin, width and hit point. The mapping returns
a character index and a char innerPos: if it's between 0 and 50%, the first logical part
of the character was hit, if it isn't, the last part was hit. This information may be
used to set the insert position and the current writting style (the one before or after the
insert position). On the other end, if the target glyph is a ligature, the innerPos is used 
to determine the component.
On the reverse way, the innerPos may be used to hilite part of a ligature glyph.

Note: the innerPos is swapped when glyphs are swapped.

Another way to use the log is to replay it on an arbitrary array: the recorded transformations 
are applied on the array. For example, the array may be a array of references to styles, or
direction embedding levels. 
The rules are:
- an entry subject to a 1->n susbtitution is copied in the n entries
- a ligature entry inherit from its first component.
These rules may be overriden by providing a merge and a split callback.


the most significant bit is used as an op marker
Single:  [0,index] (no marker)
Multiple: [1,M,count] [0,index]
Ligature: [1,L,termdiaccount-3bits,count-5bits] count * [0,index] [1,L,termdiaccount-3bits,count-5bits]
Delete: [1,D,count] [0,index]
Swap: [1,SW,0] [0,index] [0,index+count]
Move: [1,MV,0] [0,srcindex] [0,dstindex] [0,index+count]
Atom: [1,A,count] [0,index]: like a lig, but moving inside or deleting partially is forbidden (eg: surrogates are atoms)
Group: [1,G,input count] [0,index] [1,G,output count]: like lig+multiple, partial deletion is ok (eg: Indic aksara)

Note on termdiaccount:
it's the number of ligature components that are at lig end and are marks. This information is used
to split the advance differently: lamalif is split in two equal parts, shinsindotdagesh is split in 2/3
for sheen and 1/6 for the dot and 1/6 for dagesh.


*/

#ifdef WR_WIN_ENV
#pragma warning (disable:4251)
#endif

class SLRange;
class SLRangeList;
class SLPosition;
class I2OMapping;
class SLRun;
class SLRunList;

class WRSERVICES_DECL SubstitutionLog : public WRClass
{
public:
	enum { kSubLog_NoErr, kSubLog_AllocErr, kSubLog_OutOfRangeErr };
	enum { kLigature = 0x80,kMultiple,kDelete, // basic OT substitutions
		kReverse,kMove, // bidi reordering
		kSingle, // was kAtom, never used, kSingle isn't use in regular logs
		kGroup,// aksara
		kMergeToLiga,
		kWideMultiple,
		kLongIndexes = 0x40
	};

	typedef unsigned short Token;

	SubstitutionLog();
	SubstitutionLog(void* data);
	~SubstitutionLog();

	Token* GetSubs() { return fSubs.PeekArray(); }
	Token* GetClusters() { return fClusters.PeekArray(); }
	WRInt32* GetUTFMapping() { return fUTFMapping.PeekArray(); }

	const WRVector<Token>& Subs() const { return fSubs; }
	const WRVector<Token>& Clusters() const { return fClusters; }
	const WRVector<WRInt32>& UTFMapping() const { return fUTFMapping; }

	// manage the input and output  counts so that the client don't have to maintain it externally (required to do concats)
	WRInt32	GetInputCount() const { return fInputCount; }
	void SetInputCount(WRInt32 count) { fInputCount = count; } 
	void AddToInputCount(WRInt32 n) { fInputCount += n; } 

	WRInt32	GetOutputCount() const { return fOutputCount; }
	void SetOutputCount(WRInt32 count) { fOutputCount = count; } 
	void AddToOutputCount(WRInt32 n) { fOutputCount += n; } 

	WRInt32 Catenate(const SubstitutionLog& next);
	WRInt32 Extract(SubstitutionLog& extractedLog, WRInt32 start, WRInt32 count) const;
	WRInt32 Copy(const SubstitutionLog& log);
	
	/// Reset the log
	/**
	Resets the substitution log (no operations, no cluster, empty input and output) 
	without actually releasing the allocated memory, unlike Clear()
	@sa Clear()
	*/
	void	Reset() { fSubs.Resize(0); fClusters.Resize(0);fInputCount = fOutputCount = 0; }
	
	/// Clear the log
	/**
	Clears the substitution log (no operations, no cluster, empty input and output) 
	and releases the allocated memory, unlike Reset()
	@sa Reset()
	*/
	void	Clear() { fSubs.Clear(); fClusters.Clear(); fInputCount = fOutputCount = 0; }

	WRInt32 GetSubsSize() const { return fSubs.Size(); }
	WRInt32 GetClustersSize() const { return fClusters.Size(); }
	void ResizeSubs(WRInt32 n) { fSubs.Resize(n); }
	void ResizeClusters(WRInt32 n) { fClusters.Resize(n); }
	WRVector<Token>& Clusters() { return fClusters; }


	void RecordSingle(SLIndex tk);			
	void RecordDelete(WRInt32 count,SLIndex tk);
	void RecordMultiple(WRInt32 count,SLIndex tk);
	void RecordMove(SLIndex src, SLIndex dst, WRInt32 count);	
	void RecordMergeToLiga(SLInnerPosition inner,SLIndex src, SLIndex dst )	;	
	void RecordReverse(WRInt32 count, SLIndex start);	
	void RecordGroup(WRInt32 inputLen, SLIndex glyphStart, WRInt32 reorderedLen);	

	void StartLigature(WRInt32 count, WRInt32 termDiacCount = 0);		
	void LigatureComponent(SLIndex pos);
	void EndLigature(WRInt32 count, WRInt32 termDiacCount = 0);

	void AppendCluster(SLIndex start,SLCount count);

	WRInt32 Forget(SubstitutionLog& newLog, WRInt32 segStart, WRInt32 segCount) const;

	SLIndex OutputToInput(SLIndex index,SLInnerPosition& innerPosition, WRInt32 startPos = 0) const ;
	void InputToOutput(I2OMapping& params, WRInt32 startPos = 0) const ;
	void InputToOutput(I2OMapping& params, WRInt32 startPos, bool searchGroup, WRInt32* stopPos, SLRange* pGroup) const ;
	WRInt32 MaxExtent(WRInt32 len, WRInt32 startPos = 0) const ; // maximum size of the strike array during the subs process.
	void InputToOutputRanges(SLRangeList& ranges,WRInt32 startPos = 0) const ;
	void OutputToInputRanges(SLRangeList& ranges,WRInt32 startPos = 0) const ;
	void OutputToInputRanges(SLRangeList& ranges,WRInt32 startPos, WRInt32 endPos) const ;

	SLIndex ClientEncodingToUTF32(SLIndex) const;
	SLIndex UTF32ToClientEncoding(SLIndex) const;

	void ToClusterBase(SLPosition& pos) const;
	void GetCluster(SLIndex ix, SLIndex& start, SLCount& count) const;
	SLIndex FromClusterBase(SLIndex pos, SLInnerPosition inner) const;
	void NextCluster(WRInt32& pos, SLIndex& start,SLCount& count) const;

	typedef void (*SLSplitProc) (void* src, WRInt32 itemSize, WRInt32 count);
	typedef void (*SLMergeProc) (void* src, void* lig, WRInt32 itemSize, WRInt32 count, WRInt32 termDiacs, WRInt32 i);

	WRInt32 Replay(SLMergeProc mergeProc,SLSplitProc splitProc,void* array, WRInt32 len, WRInt32 maxLen, WRInt32 itemSize, WRInt32 startPos) const ;
		// replay the substitution sequence on the array
		// which must be at least size = maxextent long (!= initial and final len!)
		// return the final length
		// startPos = 0 means the whole log,
		// other meaningful value may the GetUndo()
		// the merge and split proc are called when a multiple or ligature substitution is performed
		// if NULL, the entry is duplicated on Multiple subst. and the first component is taken as result
		// for a ligature.

	// same meaning as the above members but only the last 
	// part of the log, starting with the setundo position,
	// is replayed

	void Replay(SLRunList& runs,WRInt32 startPos = 0) const ;

	enum { kLeft,kRight,kLeftMost,kRightMost};
	bool VisualMove(WRInt32 whichMove,SLPosition& pos, bool& keyboardIsRTL);

	void AppendUTFMappingRange(WRInt32 nb, WRInt32 itemSz);
	void SetUTFMapping(const WRVector<WRInt32>& mapping) { fUTFMapping = mapping; }
	void ToClusterBaseClientEncoding(SLPosition& pos) const;
	void GetClusterClientEncoding(SLIndex ix, SLIndex& start, SLCount& count) const;
	bool VisualMoveClientEncoding(WRInt32 whichMove,SLPosition& pos, bool& keyboardIsRTL);
	SLIndex OutputToInputClientEncoding(SLIndex index,SLInnerPosition& innerPosition) const ;
	void InputToOutputClientEncoding(I2OMapping& params) const ;
	WRInt32 MaxExtentClientEncoding(WRInt32 len) const ; // maximum size of the strike array during the subs process.
	void InputToOutputRangesClientEncoding(SLRangeList& ranges) const ;
	void OutputToInputRangesClientEncoding(SLRangeList& ranges) const ;
	WRInt32 ExtractClientEncoding(SubstitutionLog& extractedLog, WRInt32 start, WRInt32 count) const;
	void ReplayClientEncoding(SLRunList& runs) const ;
	WRInt32 ReplayClientEncoding(SLMergeProc mergeProc,SLSplitProc splitProc,void* array, WRInt32 len, WRInt32 maxLen, WRInt32 itemSize) const ;
	SLIndex FromClusterBaseClientEncoding(SLIndex posClientEncoding, SLInnerPosition inner) const;
	bool GetGroup(SLIndex ix, SLRange& group) const;
	bool GetGroupClientEncoding(SLIndex ix, SLRange& group) const;

	enum { kConsistent, kInputLenMismatch, kOutputLenMismatch, kCorrupted, kResultLenMismatch, kTruncated };

	WRInt32 Verify(WRInt32 inputLen, WRInt32 outputLen = -1) const ;

//protected:

	void SwapEntries(char* t, WRInt32 itemSize, WRInt32 i, WRInt32 j) const;
	void SwapRange(char* t, WRInt32 len, WRInt32 itemSize, WRInt32 i, WRInt32 j) const;
	WRInt32 Append(Token tk);
	WRInt32 Append(WRInt32 tk) { return Append((Token) tk); }
	//WRInt32 Append(WRInt32 tk) { return Append((Token) tk); } - dsvoboda: removed because it becomes the same on 64 bit platform.
	WRInt32 AppendOp(WRInt32 op,WRInt32 count);
	void AppendLongIndex(SLIndex pos);
	
	short				fUndo; ///< obsolete
	WRInt32				fInputCount; ///< number of input slots (characters) in the array describe by the log
	WRInt32				fOutputCount; ///< number of output slots (glyphs) in the array describe by the log
	WRVector<Token>		fSubs; ///< storage for operation logging
	WRVector<Token>		fClusters;	///< storage for cluster boundaries
	WRVector<WRInt32>	fUTFMapping; ///< variable to fixed size encoding data
};

class WRSERVICES_DECL SubstitutionLogIterator
{
public:
	SubstitutionLogIterator(SubstitutionLog* log, WRInt32 startPos = 0) : 
		fEnd(log->GetSubs() + log->GetSubsSize()),
		fNextToken(log->GetSubs() + startPos),
		fBase(((SubstitutionLog*)log)->GetSubs()),
		fCurrentCount(0),
		fCorrupted(false)
	{
	}

	SubstitutionLogIterator(const SubstitutionLog* log, WRInt32 startPos = 0) : 
		fEnd(((SubstitutionLog*)log)->GetSubs() + log->GetSubsSize()),
		fNextToken(((SubstitutionLog*)log)->GetSubs() + startPos),
		fBase(((SubstitutionLog*)log)->GetSubs()),
		fCurrentCount(0),
		fCorrupted(false)
	{
	}

	SubstitutionLogIterator(const SubstitutionLog* log, WRInt32 startPos, WRInt32 endPos) : 
		fEnd(((SubstitutionLog*)log)->GetSubs() + endPos),
		fNextToken(((SubstitutionLog*)log)->GetSubs() + startPos),
		fBase(((SubstitutionLog*)log)->GetSubs()),
		fCurrentCount(0),
		fCorrupted(false)
	{
	}

	bool GetRecord();

	bool		HasLongIndexes() const			{ return fLongIndexes; }
	SLOperation Operation() const				{ return fCurrentOperation; }
	WRInt32		Count() const					{ return fCurrentCount; }
	WRInt32		GetInner() const				{ return fCurrentCount; } // mergetoliga
	WRInt32		OutputCount() const				{ return fOutputCount; }
	WRInt32		TermDiacs() const				{ return fTermDiacs; }
	SLIndex		GetTarget() const				{ return fTarget1; }
	SLIndex		GetSource() const				{ return fTarget1; }
	SLIndex		GetDest() const					{ return fTarget2; }
	SLIndex		GetComp()						{ return ReadIndexPreInc(); }
	bool		NoMarkSkipped() const			{ return GetNthComp(fCurrentCount-1) == GetNthComp(0) + fCurrentCount - 1; }
	WRInt32		GetPosition() const				{ return static_cast<WRInt32>(fCurToken - fBase); }
	WRInt32		GetNextPosition() const			{ return static_cast<WRInt32>(fNextToken - fBase); }
	bool		IsCorrupted() const				{ return fCorrupted; }
	void		CheckNextToken()				{ if  (fNextToken > fEnd) fCorrupted = true; }

	void		UpdateTermDiacs(WRInt32 n)			
	{
		SubstitutionLog::Token tk = fNextToken[-1];
		tk |= (n << 5);
		fNextToken[-1] = tk;
		if (fLongIndexes)
			fNextToken[-2 - fCurrentCount * 2] = tk;
		else
			fNextToken[-2 - fCurrentCount] = tk;
	}

	SLIndex ReadIndexPreInc()
	{
		SLIndex res = *(++fCurToken);
		if (fLongIndexes)
			res = res << 16 | *(++fCurToken);
		return res;
	}

	SLIndex GetNthComp(WRInt32 n) const
	{
		if (fLongIndexes)
		{
			SubstitutionLog::Token* p = fCurToken + n + n;
			SLIndex res = p[1];
			res = res << 16 | p[2];
			return res;
		}
		else
			return fCurToken[n +1];
	}

	void SkipIndexes(WRInt32 count)
	{
		fCurToken += count;
		if (fLongIndexes)
			fCurToken += count;
	}

	void SkipEndToken()
	{
		if (fLongIndexes)
			fCurToken ++;
	}

	SubstitutionLog::Token*	fCurToken;
	SubstitutionLog::Token*	fEnd;
	SubstitutionLog::Token*	fNextToken;
	SubstitutionLog::Token*	fBase;

protected:
	SLOperation			fCurrentOperation;
	bool				fLongIndexes;
	WRInt32				fCurrentCount;
	WRInt32				fOutputCount;
	WRInt32				fTermDiacs;
	SLIndex				fTarget1;
	SLIndex				fTarget2;
	bool				fCorrupted;
};

class WRSERVICES_DECL SubstitutionLogBackwardIterator
{
public:
	SubstitutionLogBackwardIterator(SubstitutionLog* log, WRInt32 startPos = 0) : 
		fEnd ( log->GetSubs() + startPos - 1 ), 
		fNextToken(log->GetSubs()+ log->GetSubsSize() - 1),
		fBase(((SubstitutionLog*)log)->GetSubs())
	{
		fPendingSingles = 0;
	}
	SubstitutionLogBackwardIterator(const SubstitutionLog* log, WRInt32 startPos = 0) : 
		fEnd ( ((SubstitutionLog*)log)->GetSubs() + startPos - 1 ), 
		fNextToken(((SubstitutionLog*)log)->GetSubs()+ log->GetSubsSize() - 1),
		fBase(((SubstitutionLog*)log)->GetSubs())
	{
		fPendingSingles = 0;
	}

	SubstitutionLogBackwardIterator(const SubstitutionLog* log, WRInt32 startPos, WRInt32 endPos) : 
		fEnd ( ((SubstitutionLog*)log)->GetSubs() + startPos - 1 ), 
		fNextToken(((SubstitutionLog*)log)->GetSubs()+ endPos - 1),
		fBase(((SubstitutionLog*)log)->GetSubs())
	{
		fPendingSingles = 0;
	}

	bool GetRecord();

	bool		HasLongIndexes() const			{ return fLongIndexes; }
	SLOperation Operation() const				{ return fCurrentOperation; }
	WRInt32		Count() const					{ return fCurrentCount; }
	WRInt32		GetInner() const				{ return fCurrentCount; } // mergetoliga
	WRInt32		OutputCount() const				{ return fOutputCount; }
	WRInt32		TermDiacs() const				{ return fTermDiacs; }
	SLIndex		GetTarget() const				{ return fTarget1; }
	SLIndex		GetSource() const				{ return fTarget1; }
	SLIndex		GetDest() const					{ return fTarget2; }
	SLIndex		GetComp()						{ return ReadIndexPreDec(); }
	WRInt32		SkippedMarkCount() const		{ return GetNthComp(fCurrentCount-1) - GetNthComp(0) - fCurrentCount + 1; }
	WRInt32		GetPosition() const				{ return static_cast<WRInt32>(fCurToken - fBase); }

	SLIndex ReadIndexPreDec()
	{
		SLIndex res = *(--fCurToken);
		if (fLongIndexes)
			res |= *(--fCurToken) << 16;
		return res;
	}

	void SkipIndexes(WRInt32 count)
	{
		fCurToken += count;
		if (fLongIndexes)
			fCurToken += count;
	}

	SLIndex GetNthComp(WRInt32 n) const
	{
		if (fLongIndexes)
		{
			SubstitutionLog::Token* p = fNextToken + 2 + n + n;
			SLIndex res = *p;
			res = res << 16 | p[1];
			return res;
		}
		else
			return fNextToken[n + 2];
	}

	void SkipStartToken()
	{
		fCurToken --;
	}


	SubstitutionLog::Token*	fCurToken;
	SubstitutionLog::Token*	fEnd;
	SubstitutionLog::Token*	fNextToken;
	SubstitutionLog::Token*	fBase;

protected:

	bool ReleasePending(WRInt32 n);

	SLOperation			fCurrentOperation;
	bool				fLongIndexes;
	WRInt32				fCurrentCount;
	WRInt32				fOutputCount;
	WRInt32				fTermDiacs;
	SLIndex				fTarget1;
	SLIndex				fTarget2;
	WRInt32				fPendingSingles;
};


inline void SubstitutionLog::SwapEntries(char* t, WRInt32 itemSize, WRInt32 i, WRInt32 j) const 
{
	switch(itemSize)
	{
	case 1:
		{
			char temp = t[i];
			t[i] = t[j];
			t[j] = temp;
		}
		return;
	case 2:
		{
			short* t2 = (short*)t;
			short temp = t2[i];
			t2[i] = t2[j];
			t2[j] = temp;
		}
		return;
	case 4:
		{
			WRInt32* t4 = (WRInt32*)t;
			WRInt32 temp = t4[i];
			t4[i] = t4[j];
			t4[j] = temp;
		}
		return;
	default:
		{
			char* t1 = t + i*itemSize;
			char* t2 = t + j*itemSize;
			char* end = t1 + itemSize;
			char temp;
			while(t1 < end)
			{ 
				temp = *t1;
				*(t1++) = *t2;
				*(t2++) = temp;
			}
		}
	}
}


inline void SubstitutionLog::SwapRange(char* t, WRInt32 len, WRInt32 itemSize, WRInt32 i, WRInt32 j) const
{
	if (!(i>=0 && i<= len && j >= 0 && j <= len && i < j))
		return;
	j--;
	while(i<j)
		SwapEntries(t,itemSize,i++,j--);
}

template <class T> void SwapRange(T* t, WRInt32 len, WRInt32 i, WRInt32 j) 
{
	if (!(i>=0 && i<= len && j >= 0 && j <= len && i < j))
		return;
	j--;
	while(i<j)
		{
			T temp = t[i];
			t[i] = t[j];
			t[j] = temp;
			i++;j--;
		}
}

template <class T> WRInt32 ReplayLogClientEncoding(SubstitutionLog& log,T* t,WRInt32 len, WRInt32 maxLen) 
{
	T* in = t;
	T* out = in;
	for (WRInt32 i = 0; i < log.fUTFMapping.Size(); i++)
	{
		WRInt32 count = log.fUTFMapping[i] >> 4;
		WRInt32 packSz = log.fUTFMapping[i] & 0x0F;
		for (WRInt32 j = 0; j < count; j++)
		{
			*(out++) = *in;
			in += packSz;
		}
	}
	len -= t - out;
	return ReplayLog(log,t,len,maxLen,0);
}


template <class T> WRInt32 ReplayLog(SubstitutionLog& log,T* t, WRInt32 len, WRInt32, WRInt32 startPos) 
{	
	SubstitutionLogIterator it(&log, startPos);

	while (it.GetRecord())
	{
		WRInt32 count = it.Count();
		switch (it.Operation())
		{
			case SubstitutionLog::kMultiple:
				{
					// all children glyphs inherit from their parent glyph
					SLIndex target = it.GetTarget();
					WRASSERT (target < len, "bad target");
					memmove((void*)(t+target+count), (void*)(t+target+1), sizeof(T)*(len-target-1));
					for (WRInt32 i = 1; i< count; i++)
						//memcpy(t+itemSize*(target+1),t+itemSize*(target),itemSize);
						t[target+i] = t[target];
					len += count-1;
				}
				break;
			case SubstitutionLog::kLigature:
				{
					SLIndex lig = it.GetComp();
					WRUNUSED(lig);
					SLIndex dst = it.GetComp();
					SLIndex src = dst+1;
					
					// lig packing
					for (WRInt32 j = 2; j < count ; j++)
					{
						SLIndex comp = it.GetComp();
						while (src < comp)
							//memcpy(t+itemSize*(dst++),t+itemSize*(src++),itemSize);
							t[dst++] = t[src++];
						src++;
					}
					
					// move the tail of the array
					memmove((void*)(t+dst), (void*)(t+src),sizeof(T)*(len-src));
					len -= count - 1;
				}
				break;
			case SubstitutionLog::kDelete:
				{
					// all children glyphs inherit from their parent glyph
					SLIndex target = it.GetTarget();
					memmove((void*)(t+target), (void*)(t+target+count), sizeof(T)*(len - target - count));
					len -= count;
				}
				break;
			case SubstitutionLog::kMergeToLiga:
				{
					// count is used to store the inner position inside the ligature
					SLIndex src = it.GetTarget();
					memmove((void*)(t+src), (void*)(t+src+1), sizeof(T)*(len - src - 1));
					len --;
				}
				break;
			case SubstitutionLog::kReverse:
				{
					SLIndex target = it.GetTarget();
					WRInt32 i = target;
					WRInt32 j = target+count;

					SwapRange(t,len,i,j);
				}
				break;
			case SubstitutionLog::kMove:
				{
					SLIndex src = it.GetSource();
					SLIndex dst = it.GetDest();

					WRInt32 a,b,c;
					if (dst < src)
					{
						a = dst;
						b = src + count;
						c = dst + count;
					}
					else
					{
						a = src;
						b = dst + count;
						c = dst;
					}
					SwapRange(t,len,a,b);
					SwapRange(t,len,a,c);
					SwapRange(t,len,c,b);
				}
				break;
			case SubstitutionLog::kGroup:
				{
					// all child glyphs inherit from the first parent glyph
					SLIndex target = it.GetTarget();
					WRInt32 outcount = it.OutputCount();
					WRInt32 diff = outcount - count;
					if (diff)
					{
						WRInt32 numToMove = len-target-count;
						if (numToMove > 0) // protection
							memmove((void*)(t+target+outcount), (void*)(t+target+count), sizeof(T)*(numToMove));
						len += diff;
					}
					for (WRInt32 i = 1; i< outcount; i++)
						t[target+i] = t[target];
					
				}
				break;
		}
	}
	return len;
}

class SLPosition
{
public:
	SLPosition () : index(0), inner(0) {}
	SLPosition (SLIndex ix,SLInnerPosition in) : index(ix), inner(in) {}
	SLIndex index;
	SLInnerPosition inner;

	void Replace(SLIndex pos,WRInt32 beforeCount,WRInt32 afterCount);
	void AtomSubs(SLIndex pos,WRInt32 count);
	void LigatureSubs(SubstitutionLogIterator& it, bool rangeEnd = false);
	void Unligate(SubstitutionLogBackwardIterator& it);
	void RemoveHundreds();
	void RestoreHundreds();
	void Offset(WRInt32 offset) { index = SLIndex(WRInt32(index) + offset); }
};

class SLRange
{
public:
	SLRange() { }
	SLRange(const SLPosition& aPos,const SLPosition&bPos) : a(aPos), b(bPos) { }
	SLRange(SLIndex ixa,SLInnerPosition ina,SLIndex ixb,SLInnerPosition inb) :a(ixa,ina), b(ixb, inb) { }
	SLPosition a;
	SLPosition b;
	bool LigatureSubs(SubstitutionLogIterator& it);
	void RemoveHundreds();
	void RestoreHundreds();
	void Offset(WRInt32 offset) { a.Offset(offset); b.Offset(offset); }
	void Replace(SLIndex pos,WRInt32 beforeCount,WRInt32 afterCount);
};

class SLRangeList : public WRVector<SLRange>
{
public:
	SLRangeList() {}
	SLRangeList(const SLRangeList& ranges) : WRVector<SLRange>((WRVector<SLRange>&)ranges) {  }
	SLRangeList(const SLRange& range) { Append(range); }
	SLRangeList(const SLPosition& start, const SLPosition& end) { Append(SLRange(start,end)); }
	SLRangeList(SLIndex ixa,SLInnerPosition ina,SLIndex ixb,SLInnerPosition inb) { Append(SLRange(ixa,ina,ixb,inb)); }
	void CutAt(SLPosition cut);
	void WRSERVICES_DECL CropAt(SLPosition start,SLPosition end);
	void Replace(SLIndex pos,WRInt32 beforeCount,WRInt32 afterCount);
	void Swap(WRInt32 i,WRInt32 j);
	void SortAndMerge();
	void RemoveHundreds();
	void RestoreHundreds();
	void MirrorSegment(SLIndex start,WRInt32 count);
	void MoveSegment(SLIndex start,WRInt32 count,SLIndex dest);
	void LigatureSubs(SubstitutionLogIterator& it);
	void Unligate(SubstitutionLogBackwardIterator& it);
	void MergeToLiga(SLIndex src,SLIndex dst,WRInt32 inner);
	void ExtractFromLiga(SLIndex src,SLIndex dst,WRInt32 inner);
	void WRSERVICES_DECL Offset(WRInt32 offset);
	bool WRSERVICES_DECL Intersect(const SLRange& range);
};

class SLRun
{
public:
	SLRun() { }
	SLRun(SLIndex c,WRInt32 d) { count = c; data = d; }
	SLIndex count;
	WRInt32	data;
};

class SLRunList : public WRVector<SLRun>
{
public:
	SLIndex	GetLength() const { WRInt32 res = 0; for (WRInt32  i = 0 ; i < fSize; i++) res += fData[i].count; return res; }
};

class I2OMapping
{
public:
	SLPosition fInput;			// i: character index
	SLPosition fOutput;			// o: inner position in the input char/output glyph

	bool fDir;				// o: writing direction of the input character (determined by looking at swap ops)
	SLCount fComponentIndex;// o: component number (0-based) of the input char in its corresponding glyph (may be non_null in a ligature)

	I2OMapping() {}
	I2OMapping(SLIndex ix,SLInnerPosition in) { fInput.index = ix; fInput.inner = in; }
	I2OMapping(SLPosition pos) { fInput = pos; }
} ;

inline void SLPosition::RemoveHundreds()
{
	if (inner == kHundredPerCent)
	{
		inner = 0;
		index++;
	}
}

inline void SLPosition::RestoreHundreds()
{
	if (inner == 0 && index)
	{
		inner = kHundredPerCent;
		index--;
	}
}

inline bool operator < (SLPosition a,SLPosition b)
{
	a.RemoveHundreds();
	b.RemoveHundreds();
	return a.index < b.index || (a.index == b.index && a.inner < b.inner);
}

inline bool operator <= (SLPosition a,SLPosition b)
{
	a.RemoveHundreds();
	b.RemoveHundreds();
	return a.index < b.index || (a.index == b.index && a.inner <= b.inner);
}

inline bool operator > (SLPosition a,SLPosition b)
{
	a.RemoveHundreds();
	b.RemoveHundreds();
	return a.index > b.index || (a.index == b.index && a.inner > b.inner);
}

inline bool operator >= (SLPosition a,SLPosition b)
{
	a.RemoveHundreds();
	b.RemoveHundreds();
	return a.index > b.index || (a.index == b.index && a.inner >= b.inner);
}

inline bool operator == (SLPosition a,SLPosition b)
{
	a.RemoveHundreds();
	b.RemoveHundreds();
	return a.index == b.index && a.inner == b.inner;
}

inline bool operator != (SLPosition a,SLPosition b)
{
	a.RemoveHundreds();
	b.RemoveHundreds();
	return a.index != b.index || a.inner != b.inner;
}

#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif
