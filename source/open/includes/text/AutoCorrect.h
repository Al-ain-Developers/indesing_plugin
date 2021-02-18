//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/text/AutoCorrect.h $
//  
//  Owner: Heath Horton
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
#ifndef __AutoCorrect__
#define __AutoCorrect__

#include "K2Vector.h"
#include "k2sortedlookup.h"

class PUBLIC_DECL AutoCorrectItem
{
public:
    typedef object_type data_type;
    AutoCorrectItem();
    AutoCorrectItem(const AutoCorrectItem& other);
    ~AutoCorrectItem();

    void     operator=    (const AutoCorrectItem& copy);
    bool16     operator==    (const AutoCorrectItem& other) const
        { return (fLanguageID == other.fLanguageID && fAutoStringPair == other.fAutoStringPair); }
    bool16     operator>    (const AutoCorrectItem& other) const
        { return fLanguageID > other.fLanguageID; }
    bool16     operator<    (const AutoCorrectItem& other) const
        { return fLanguageID < other.fLanguageID; }

    void ReadWrite(IPMStream* s);

//protected:
	int16												fLanguageID;
	K2SortedLookup<WideString, WideString>				fAutoStringPair;	//misspelled, corrected
};

class PUBLIC_DECL AutoCorrectList        //sorted
{
    public:
        AutoCorrectList()
            {}
        AutoCorrectList(const AutoCorrectList& copy)
            { *this = copy; }
        ~AutoCorrectList();

        void clear();
        void Clear()
            { clear(); }

        int32 size() const
            { return (int32)fList.size(); }
        int32 Length() const
            { return size(); }

        void Insert(const AutoCorrectItem& item);

        const AutoCorrectItem& operator[](int32 i) const
            { ASSERT(fList[i] != nil); return *(fList[i]); }
        AutoCorrectItem& operator[](int32 i)
            { ASSERT(fList[i] != nil); return *(fList[i]); }

        AutoCorrectList& operator=(const AutoCorrectList& copy);

        bool16 operator==(const AutoCorrectList& other) const;
        bool16 operator!=(const AutoCorrectList& other) const
            { return !(*this == other); }

        void ReadWrite(IPMStream* s);

    private:
        K2Vector<AutoCorrectItem*>        fList;
};


#endif
