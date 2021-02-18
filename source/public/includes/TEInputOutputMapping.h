//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TEInputOutputMapping.h $
//  
//  Owner: shagupta
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change $
//  ___________________
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2018 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by all applicable intellectual property
//  laws, including trade secret and copyright laws.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================



#ifndef __TEInputOutputMapping__
#define __TEInputOutputMapping__

#include "IWROptyca.h"
#include <vector>

#define kHundredPerCent 100 

class TEPosition
{
public:
	TEPosition() : index(0), inner(0) {}
	TEPosition(int32 ix, int32 in) : index(ix), inner(in) {}
	int32 index;
	int32 inner;
};

class TERange
{
public:
	TERange() { }
	TERange(int32 ixa, int32 ina, int32 ixb, int32 inb) :a(ixa, ina), b(ixb, inb) { }
	TERange(const TEPosition& aPos, const TEPosition&bPos) : a(aPos), b(bPos) { }
	TEPosition a;
	TEPosition b;
};

class TERangeList : public std::vector<TERange>
{
public:
	TERangeList() {}
	void Append(TERange range)
	{
		this->push_back(range);
	}
	int Size()
	{
		return (int) this->size();
	}
	int Remove(int pos)
	{
		if (pos >= (int)this->size())
		{
			return -1;
		}
		vector<TERange>::iterator it;
		it = this->begin();
		it += pos;
		this->erase(it);
		return 1;
	}
	TERange* PeekArray()
	{
		return &this->front();
	}
};

class TEInputOutputMapping
{
	/*
	This is a base class with 2 child classes. One of the child class is a wrapper over InputOutputHB, and the other over SubstitutionLog. If optyca has been initialized and DoShaping is called, a pointer of TEInputOutputMapping will then point to an object of one of these child sub-classes.
	*/
public:

	TEInputOutputMapping()
	{
	}
	~TEInputOutputMapping()
	{
		
	}

	enum { kLeft, kRight, kLeftMost, kRightMost };

	virtual void Initialize(IWROptyca* optycaInstance) { ASSERT(" This function is not available on Harfbuzz!"); }

	virtual void InputToOutput(int32 characterIndex, int32 &inner, int32 &glyphIndex)  
	{
		glyphIndex = characterIndex;
	}

	virtual void InputToOutput(int32 characterIndex, int32 &inner, int32 &glyphIndex, bool16 &direction)  { glyphIndex = characterIndex; direction = reverse; }

	virtual void InputToOutputRanges(TERangeList& ranges) { };

	virtual void InputToOutputClientEncoding(int32 characterIndex, int32 &inner, int32 &glyphIndex)  { 
		glyphIndex = characterIndex;
	}

	virtual void InputToOutputRangesClientEncoding(TERangeList& ranges) { ASSERT(" This function is not available on Harfbuzz!"); }

	virtual void OutputToInput(int32 glyphIndex, int32 &inner, int32 &characterIndex, int32 startPos = 0) 
	{
		characterIndex = glyphIndex;
	};

	virtual void OutputToInputRanges(TERangeList& ranges) {};

	virtual int32 GetInputCount() { return 0; }

	virtual void SetInputCount(int count) {  };

	virtual int32 GetOutputCount() { return 0; }

	virtual void SetOutputCount(int count) {  };

	virtual void Clear() { }; // not available on harfbuzz

	virtual void Reset() {  };

	virtual int MaxExtent(int len, int start = 0) { return len; }

	virtual int TEReplayLog(short* t, int32 len, int32 maxLen, int32 startPos) { return len; }

	virtual void GetCluster(int32 ix, int32& start, unsigned char& count) 
	{
		start = ix;
		count = 1;
	};

	virtual void ToClusterBase(int32& index, int32& inner) {};

	virtual void RecordReverse(int32 count, int32 start) { reverse = kTrue; };

	virtual int32 TEReplayLogClientEncoding(int32* t, int32 len, int32 maxLen) { return len; }

	virtual bool VisualMove(int32 whichMove, int32& ix, int32& in, bool& keyboardIsRTL) {
		return false;
	}

	virtual void RecordMove(int32 src, int32 dst, int32 count) { };

	virtual int32 GetSubsSize() const { return 0; }

	virtual int32 GetClustersSize() const { ASSERT(" This function is not available on Harfbuzz!"); return 0; }

	virtual void ResizeClusters(int32 n) { ASSERT(" This function is not available on Harfbuzz!"); }

	virtual unsigned short&  Clusters(int32 index) { ASSERT(" This function is not available on Harfbuzz!"); return dummyShort; }

	virtual unsigned short&  GetSubs(int32 index) { return dummyShort; }

	virtual int32&  UTFMapping(int32 index) { return dummyInt; }

	virtual int32  UTFMappingSize() { return 0; }

	virtual short GetUndo() { return 0; }

	virtual void Resize(int32 n) { };

	virtual int  UTFMappingResize(int n) { return 0; }

	virtual int32 TEExtract(TEInputOutputMapping& extractedLog, int32 start, int32 count) { return 0; }

	virtual int32 Catenate(TEInputOutputMapping& next) { return 0; } // implement

	virtual int GetMappingType() { return 2; }

	void slToTeRangeList(SLRangeList &slRanges, TERangeList &ranges)
	{
		for (int i = 0; i < slRanges.Size(); i++)
		{
			if (i + 1 > ranges.Size())
			{
				TERange temp(0, 0, 0, 0);
				ranges.Append(temp);
			}
			ranges[i].a.index = slRanges[i].a.index; ranges[i].a.inner = slRanges[i].a.inner; ranges[i].b.index = slRanges[i].b.index; ranges[i].b.inner = slRanges[i].b.inner;
		}
	}

	void teToSlRangeList(SLRangeList &slRanges, TERangeList &ranges)
	{
		for (int i = 0; i < ranges.Size(); i++)
		{
			SLRange temp(ranges[i].a.index, ranges[i].a.inner, ranges[i].b.index, ranges[i].b.inner);
			slRanges.Append(temp);
		}
	}

	int32 dummyInt = 0;
	unsigned short dummyShort = 0;
	bool16 reverse = kFalse;
};


#endif //__TEInputOutputMapping__
