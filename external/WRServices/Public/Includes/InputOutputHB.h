//========================================================================================
//  
//  File: InputOutputHB.h
//  
//  Author: Shubhi Mohta
//  
//  Copyright 2018 Adobe Inc.
//  Usage rights licenced to Adobe Inc.
//  
//========================================================================================
#pragma once
#ifndef _InputOutputHB_
#define _InputOutputHB_


#include "WRConfig.h"

#include "WRDefines.h"
#include "WRClass.h"
#include "WRVector.h"
#include <map>

typedef WRInt32			HBIndex;
typedef WRInt32 HBInnerPosition;
/*
InputOutputHB is the Input-Output Interface when Harfbuzz Shaping is used.

Each output glyph has a cluster value assigned to it with the possiblity of many glyphs forming a cluster and hence having the same cluster value in case of complex scripts;

HBClusters
-clusterValue: cluster value (with 0 being the first cluster). Cluster value of a cluster is the smallest index of the input characters which form that cluster. Hence cluster values might not be continuous values .
-glyphStart/glyphEnd: tells us the start and end of the glyphs forming a cluster
-unicodeStart/UnicodeEnd: tells us the start and end of the input unicodes forming a cluster

All Hit-Test, Selection, cursor movement workflows should be cluster based.


*/
class HBClusters
{
public:
	HBClusters() {};
	HBClusters& operator=(const HBClusters& rhs) {
		glyphEnd = rhs.glyphEnd;
		glyphStart = rhs.glyphStart;
		unicodeStart = rhs.unicodeStart;
		unicodeEnd = rhs.unicodeEnd;
		clusterValue = rhs.clusterValue;
        return *this;
	};
	HBClusters(WRInt32 a, WRInt32 b, WRInt32 c, WRInt32 d, WRInt32 e) : clusterValue(a), glyphStart(b), glyphEnd(c), unicodeStart(d), unicodeEnd(e) {};
	WRInt32 clusterValue;
	WRInt32 glyphStart;
	WRInt32 glyphEnd;
	WRInt32 unicodeStart;
	WRInt32 unicodeEnd;
	bool operator==(HBClusters& rhs);
};

class HBRun
{
public:
	HBRun() { }
	HBRun(HBIndex c, WRInt32 d) { count = c; data = d; }
	HBIndex count; // no of characters/glyphs
	WRInt32	data;// start index
};

class HBRunList : public WRVector<HBRun>
{
public:
	HBIndex	GetLength() const { WRInt32 res = 0; for (WRInt32  i = 0; i < fSize; i++) res += fData[i].count; return res; }
};

class WRSERVICES_DECL InputOutputHB : public WRClass
{
private:
	WRInt32				fInputCount; ///< number of input slots (characters) 
	WRInt32				fClientInputCount;//client's original character input count
	WRInt32				fOutputCount; ///< number of output slots (glyphs) 
	HBRunList			fInputRuns;///track of input runs
	HBRunList			fOutputRuns;///track of output runs
	WRVector<WRInt32> fInputClusters;// keep track of cluster values of input characters before shaping
	WRVector<WRInt32> fUpdatedInputClusters;// keep track of cluster values of input characters after shaping
	WRVector<WRInt32> fOutputClusters;// keep track of cluster values of output glyphs
	WRVector<WRInt32> glyphPos;//keep track of cummulative x-advances in case of horizontal direction/y-advances of glyphs in case of vertical direction;  for 0th glyph its glyphPos to be assumed 0
    
	std::map<int, HBClusters*> clusterInfo;
	void fillClusterInfo();

public:
    
	WRInt32 WR_DLLLOCAL getGlyphClusterValue(WRInt32 glyphIndex) const;//return the cluster value of the glyph
	WRInt32 WR_DLLLOCAL getUnicodeClusterValue(WRInt32 unicodeIndex) const;//returns the cluster value of input character
	HBClusters WR_DLLLOCAL getCluster(WRInt32 clusterValue); //returns HBCluster corresponding to the output clusters
	enum {
		kInputOutputHB_NoErr, kInputOutputHB_AllocErr, kInputOutputHB_OutOfRangeErr
	};
	InputOutputHB();
	~InputOutputHB();

	void Reset();
	void setInputCount(WRInt32 count) { fClientInputCount = count; }
	WRInt32 getInputCount() { return fClientInputCount; };
	WRInt32 getOutputCount() { return fOutputCount; };
	void SetUTFMapping(const WRVector<WRInt32>& mapping) { fUTFMapping = mapping; }
	void MergeClusters(WRVector<WRInt32> inputClusters, WRVector<WRInt32> outputClusters, WRInt32 charCount, WRInt32 glyphCount, WRVector<WRInt32> advances);//TODO:decide if public or private
	HBClusters getClusterFromGlyph(WRInt32 glyphIndex) const;// returns HBCluster of the glyph 
	HBClusters getClusterFromUnicode(WRInt32 unicodeIndex) const;// returns HBCluster corresponding to the input character

	/*==========Functions for internal calls only, encoding assumed to be UTF32================*/
	HBClusters getClusterFromGlyphUTF32(WRInt32 glyphIndex) const;// returns HBCluster of the glyph 
	HBClusters getClusterFromUnicodeUTF32(WRInt32 unicodeIndex) const;// returns HBCluster corresponding to the input character
	/*================================================*/

	WRInt32 Extract(InputOutputHB& extractedIOMapping, WRInt32 start, WRInt32 count) const;//NOTE: This does not update fUTFMapping. To update the Mapping use ExtractClientEncoding after Extract with the extractedIOMapping returned from this API
	WRInt32 ExtractClientEncoding(InputOutputHB& extractedIOMapping, WRInt32 start, WRInt32 count) const;
	void AppendUTFMappingRange(WRInt32 nb, WRInt32 itemSz);
	/*==========================Funcations to update clusters and glyphpos=====================================================*/
	void updateOutputCluser(WRVector<WRInt32>& tempoutputcluser);
	void updateCluserInMap(HBClusters& tempcluster);
	void swapCluster(WRInt32 left, WRInt32 right);
	/*================================================*/

	WRInt32 Copy(const InputOutputHB& b);
	WRInt32 Catenate(const InputOutputHB& b);
	InputOutputHB & operator = (const InputOutputHB &t);
	/*
	takes input runs and updates the count to reflect the number of output glyphs of the run
	*/
	void Replay(HBRunList& runs, WRInt32 startPos);


	/*
	void OutputToInput(HBIndex glyphIndex, HBInnerPosition &inner, HBIndex &characterIndex);

	-glyphIndex : 0-based index of the output glyph sequence
	-inner: As input it contains the portion(0-100) of the glyph
			As output it return 0 or 100 as described below
	-charcaterIndex: the start or end unicodeIndex of the range of unicodes forming the output cluster which contains the output glyph(glyphIndex)
	1. if the glyph is part of the first half of the cluster ; it returns the start unicode and inner=0
	2. if the glyph is part of the secont half od the cluster; it returns the end unicode and inner=100
	*/
	void OutputToInput(HBIndex glyphIndex, HBInnerPosition &inner, HBIndex &characterIndex);
	/*
	void InputToOutput(HBIndex characterIndex, HBInnerPosition &inner, HBIndex &glyphIndex);

	-characterIndex : 0-based index of the input unicode sequence
	-inner: As input it contains the portion(0-100) of the unicode character
			As output it returns 0 or 100 as described below
	-glyphIndex: the start or end glyphIndex of the range of glyphs forming the output cluster which is formed by the input unicode(characterIndex)

	1. if the unicode character is part of the first half of the cluster ; it returns the start glyph and inner=0
	2. if the unicode character is part of the secont half od the cluster; it returns the end glyph and inner=100
	*/

	void InputToOutput(HBIndex characterIndex, HBInnerPosition &inner, HBIndex &glyphIndex);

	//API corresponding to traditional APIs in Substitution Log
	/*
	WRInt32 MaxExtent(WRInt32 len, WRInt32 startPos = 0) const;

	returns maximum of len or fOutputCount
	*/
	WRInt32 MaxExtent(WRInt32 len, WRInt32 startPos = 0) const;

	WRVector<WRInt32>	fUTFMapping;
	WRInt32 UTF32ToClientEncoding(WRInt32 pos) const;
	WRInt32 ClientEncodingToUTF32(WRInt32 pos) const;
};
template <class T> WRInt32 ReplayInputOutputHB(InputOutputHB& mapping, T* t, WRInt32 len = 0, WRInt32 maxLen = 0, WRInt32 startPos = 0)
{
	//We are assuming that the client is passing full input text in t ; 
	WRUNUSED(maxLen);//not making use of maxLen as of now.These have been kept to make this API similar to Substitution Log APIs.
	T* copyOf_t = new T[len];
	for (int i = 0; i < len; i++)
	{
		copyOf_t[i] = t[i];
	}

	WRInt32 count = mapping.getInputCount();
	if (t != NULL)
	{
		for (int i = startPos; i < count; i++)
		{
			HBClusters cluster = mapping.getClusterFromUnicode(i);
			int unicodeStart = cluster.unicodeStart;
			int unicodeEnd = cluster.unicodeEnd;
			int glyphStart = cluster.glyphStart;
			int glyphEnd = cluster.glyphEnd;
			int replace = unicodeStart;
			for (int i = unicodeStart; i <= unicodeEnd; i++)
			{
				if (copyOf_t[i] == 0x0020 || copyOf_t[i] == 0x0007 || copyOf_t[i] == 0x0008 || copyOf_t[i] == 0x0009 || copyOf_t[i] == 0x000A || copyOf_t[i] == 0x000D || copyOf_t[i] == 0x200B)
					continue;
				else
				{
					replace = i;
					break;
				}
			}
			for (int j = glyphStart; j <= glyphEnd; j++)
				t[j] = copyOf_t[replace];
			i = unicodeEnd;
		}
	}
	delete[] copyOf_t;
	return mapping.getOutputCount();
}
template <class T> WRInt32 ReplayInputOutputHBClientEncoding(InputOutputHB& mapping, T* t, WRInt32 len = 0, WRInt32 maxLen = 0)
{
	WRUNUSED(maxLen);
	T* in = t;
	T* out = in;
	for (WRInt32 i = 0; i < mapping.fUTFMapping.Size(); i++)
	{
		WRInt32 count = mapping.fUTFMapping[i] >> 4;
		WRInt32 packSz = mapping.fUTFMapping[i] & 0x0F;
		for (WRInt32 j = 0; j < count; j++)
		{
			*(out++) = *in;
			in += packSz;
		}
	}
	len -= t - out;
	return ReplayInputOutputHB(mapping, t, len, maxLen, 0);
}


#endif // ! _InputOutputHB_
