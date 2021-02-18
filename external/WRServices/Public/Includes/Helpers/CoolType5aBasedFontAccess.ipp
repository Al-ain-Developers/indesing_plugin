#ifndef __CoolType5aBasedFontAccess_ipp__
#define __CoolType5aBasedFontAccess_ipp__

#include <string>

#include "WRHybridVector.h"
#include "OpenTypeFontAccess.h"
#include "OpenTypeFontAccess.cpp"
#include "WRFromUnicodeTranslator.h"

/**
 * For MM1 fonts we need to preserve the old way of accessing CoolType.
 * The following callbacks are here for that matter
 **/

typedef struct
{
	WROTFeatureGSUBProc gsubProc;
	WROTFeatureGPOSProc gposProc;
	void*	clientCtx;
	WRUInt8*	attribs;
	int		ligCount;
	WRFontInstance* fontInstance ;
	WRRealGlyphPoint* strikes ;
	CTGlyphClassValue* classValues;
	IWRStrikeBuffer* strikes1; /** table of strikes from WRServices contains all strikes , not only those on which OT features are applies **/
	WRInt32 startStrike;

} CT4CT5GlueContext;

size_t BIBEXPORT CT4CT5GlueCTMarkToLigProc (void *clientCtx, size_t currentMarkGlyphPointIndex);
size_t BIBEXPORT CT4CT5GlueCTMarkToLigProc (
	void *clientCtx,
	size_t currentMarkGlyphPointIndex
)
{
	WRInt32 componentCount = 0;
	CT4CT5GlueContext* cntxt = (CT4CT5GlueContext*)clientCtx;
	if (cntxt && cntxt->gposProc)
		(*(cntxt->gposProc))(cntxt->clientCtx, (WRInt32) currentMarkGlyphPointIndex, &componentCount);
	return (size_t)componentCount;
}

void BIBEXPORT CT4CT5GlueCTGlyphSubProc (void *clientCtx, size_t glyphpointIndex, CTGlyphSub changeType, size_t componentCount);
void BIBEXPORT CT4CT5GlueCTGlyphSubProc (
	void *clientCtx,
	size_t glyphpointIndex,
	CTGlyphSub changeType,
	size_t componentCount
)
{
	CT4CT5GlueContext* cntxt = (CT4CT5GlueContext*)clientCtx;
	if (cntxt && cntxt->gsubProc)
	{
		WRInt32 flag = 0;
		switch (changeType)
		{
		case kCTGlyphSub_None:
		case kCTGlyphSub_MAX: //some gcc compilers needs this case here too
			flag = kWROTNoChange;
			break;
		case kCTGlyphSub_Single:
			flag = kWROTSingleSubstitute;
			break;
		case kCTGlyphSub_Alternate:
			flag = kWROTAlternate;
			break;
		case kCTGlyphSub_Multiple:
			flag = kWROTMultiSubstitute;
			break;
		case kCTGlyphSub_Ligature:
			cntxt->ligCount = static_cast<int>(componentCount);
			flag = kWROTLigature;
			break;
		case kCTGlyphSub_Deleted:
			flag = kWROTDeleted;
			componentCount = (componentCount == 1) ? cntxt->ligCount : 0;
			break;
		}
		WRInt32 limitIndex=(WRInt32)glyphpointIndex+(WRInt32)componentCount;
		WRInt32 startIndex=(WRInt32)glyphpointIndex;
		WRInt32 idx=0;
		if (*(cntxt->gsubProc)!=NULL)
		{
			if(flag == kWROTLigature)
			{	
				cntxt->attribs[glyphpointIndex]=kWROTLigature;

				(*(cntxt->gsubProc))(cntxt->clientCtx, (WRInt32) (startIndex + cntxt->startStrike), (WRInt32) kWROTLigature, (WRInt32) (limitIndex - startIndex), 0 /* only latin MM fonts exist*/);
				for (idx = startIndex+1 ; idx < limitIndex - 1 ; idx++)
					(*(cntxt->gsubProc))(cntxt->clientCtx, (WRInt32) (idx + cntxt->startStrike), (WRInt32) kWROTDeleted, (WRInt32) 0,  0 /* only latin MM fonts exist*/);
		
				(*(cntxt->gsubProc))(cntxt->clientCtx, (WRInt32) (limitIndex - 1 + cntxt->startStrike), (WRInt32) kWROTDeleted, (WRInt32) (limitIndex - startIndex), 0 /* only latin MM fonts exist*/);
			}
			else if(flag!=kWROTLigature && flag!=kWROTDeleted )
			{
				(*(cntxt->gsubProc))(cntxt->clientCtx, (WRInt32) glyphpointIndex, (WRInt32) flag, (WRInt32) componentCount, 0 /* only latin MM fonts exist*/);
			}
		}
		
		if(flag == kWROTDeleted)
		{
			(cntxt->strikes1)->RemoveFromTarget(cntxt->startStrike+(WRInt32)glyphpointIndex,1);
		}
	}
}

void BIBEXPORT CT4CT5GlueCTGlyphPosProc (void *clientCtx, size_t glyphpointIndex, BRVBool32 );
void BIBEXPORT CT4CT5GlueCTGlyphPosProc (
    void *clientCtx,
    size_t glyphpointIndex,
    BRVBool32 bHack
)
{
	CT4CT5GlueContext* cntxt = (CT4CT5GlueContext*)clientCtx;
	if (cntxt 
		&& cntxt->attribs 
		&& (cntxt->attribs[glyphpointIndex] & kWROTMarkMoved) != kWROTMarkMoved
		&& (cntxt->attribs[glyphpointIndex] & kWROTRepositioned) != kWROTRepositioned
		)
	{
		CTGlyphClassValue classValue ;
		if (cntxt->classValues == NULL)
		{
			CCTFontInstance fontInstance((CTFontInstance*)cntxt->fontInstance);
			CCTFontDict fontDict(fontInstance.GetFont());
			CTRealGlyphPoint* gl = (CTRealGlyphPoint*)cntxt->strikes + glyphpointIndex ;
			if (fontDict.GetGlyphClassValues(gl, 1, &classValue))
			{
				if (classValue == kCTGlyphClassValue_Mark && (bHack & 2))
					cntxt->attribs[glyphpointIndex] |= kWROTMarkMoved;
				else
					cntxt->attribs[glyphpointIndex] |= kWROTRepositioned;		
			}
		}
		else
		{
			classValue = cntxt->classValues[glyphpointIndex];
			if (classValue == kCTGlyphClassValue_Mark && (bHack & 2))
				cntxt->attribs[glyphpointIndex] |= kWROTMarkMoved;
			else
				cntxt->attribs[glyphpointIndex] |= kWROTRepositioned;		
		}
	}
}

/**
 * Special version of ApplyFeatures to support old MM1 fonts
 *
 * We assume here that MM can only perform 1-1 or n-1 substitutions, but no 1-n
 **/
WRInt32 CoolType5aBasedFontAccess::WRApplyFeaturesForMM1Fonts(WRFontInstance *inst, IWRStrikeBuffer *strikes, WRInt32 startStrike, WRInt32 *numStrikes, WROTFeatureInfo *featureInfo, WRFloat* endPenPos)
{	
	CCTFontInstance fontInstance((CTFontInstance*)inst);
	WRUInt32 i;
	
	size_t avail = static_cast<size_t>(*numStrikes);
	
	//dsvoboda: this is a necessary conversion to handle correctly size_t definition of featureRanges in CT. 
	//As in WRServices, it is defined as WRInt32, we need to do a copy here. But we should do an optimization for 32 bits and for aligned arrays.
	
	WRHybridVector<size_t,32> featureRanges;
			
	if (featureInfo->featureRanges != NULL)
	{
		WRUInt32 numranges = featureInfo->numFeatures * 2;
		featureRanges.Init(numranges,NULL);
		for (i = 0; i < numranges; i++)
		{
			featureRanges[i] = static_cast<size_t>(featureInfo->featureRanges[i] - startStrike);
		}
	}
	
	WRHybridVector<WRRealGlyphPoint,256> realGyphPoints;
	WRHybridVector<WRUInt8,256> attribs;
	WRUInt32 origNumStrikes = *numStrikes;
	realGyphPoints.Init(static_cast<WRInt32>(avail));
	attribs.Init(static_cast<WRInt32>(avail));
	for (i = 0; i < origNumStrikes; i++)
	{
		IWRStrike& strike = strikes->GetStrike(startStrike + i);
		realGyphPoints[i].glyphID = strike.GetGlyphID();
		realGyphPoints[i].xPosition = strike.GetXPosition();
		realGyphPoints[i].yPosition = strike.GetYPosition();
		attribs[i] = strike.GetChangeAttrib();
	}
		
	CTFeatureInfo info(
		(CTFeatureInfoFlags)(featureInfo->flags | kWRUseExtendedGPOSCallback ), // do GPOS and/or GSUB
		featureInfo->numFeatures,
		featureInfo->features,
		featureRanges.PeekArray(),
		(const BRVInt32*) featureInfo->choiceIndexes,
		featureInfo->script,
		featureInfo->language
	);

	memset(attribs.PeekArray(),0,*numStrikes);

	size_t myNumStrikes = static_cast<size_t>(*numStrikes);
	
	CT4CT5GlueContext ct4ct5Context;
	ct4ct5Context.classValues = NULL;
	WRHybridVector<CTGlyphClassValue,256> glyphClasses;
	
	if (featureInfo->version == 3)
	{
		ct4ct5Context.gsubProc = (featureInfo->otherParams)->featureGSUBCB;
		ct4ct5Context.gposProc = (featureInfo->otherParams)->featureGPOSCB;
		ct4ct5Context.clientCtx = (featureInfo->otherParams)->clientCtx;
		ct4ct5Context.attribs = attribs.PeekArray();
		ct4ct5Context.fontInstance = inst ;
		ct4ct5Context.strikes = realGyphPoints.PeekArray();
		ct4ct5Context.strikes1=strikes;
		ct4ct5Context.startStrike=startStrike;
		info.SetCBClientContext(&ct4ct5Context);
		info.SetGlyphSubCB(CT4CT5GlueCTGlyphSubProc);
		info.SetGlyphPosCB(CT4CT5GlueCTGlyphPosProc);
		info.SetMarkToLigCB(CT4CT5GlueCTMarkToLigProc );
		
		
		if ((featureInfo->flags & kWRApplyGlyphSub) == 0 && ct4ct5Context.attribs != NULL )
		{
			CCTFontDict fontDict(fontInstance.GetFont());
			glyphClasses.Init(*numStrikes);
			ct4ct5Context.classValues = glyphClasses.PeekArray();
			if (fontDict.GetGlyphClassValues((CTRealGlyphPoint*)ct4ct5Context.strikes, myNumStrikes, ct4ct5Context.classValues) == 0)
			{
				for (size_t j = 0; j < myNumStrikes; j++)
					ct4ct5Context.classValues[j] = kCTGlyphClassValue_Unknown;
			}
		}
	}

	strikes->SetRegionOfInterest(startStrike + *numStrikes);
	bool res = fontInstance.ApplyFeatures(
		(CTRealGlyphPoint*) realGyphPoints.PeekArray(), 
		myNumStrikes,
		avail, 
		info,
		(BRVRealCoord*)endPenPos);
	strikes->ClearRegionOfInterest();
	*numStrikes = static_cast<WRInt32>(myNumStrikes);

	for (i = 0; i < myNumStrikes; i++)
	{
		IWRStrike& strike = strikes->GetStrike(startStrike + i);
		strike.SetGlyphID(realGyphPoints[i].glyphID);
		strike.SetXOffset(realGyphPoints[i].xPosition);
		strike.SetYOffset(realGyphPoints[i].yPosition);
		strike.SetChangeAttrib(attribs[i]);
	}
	
	if (!res)
		return kWRArrayTooShortErr; // TODO get the real error
	else
		return kWRNoErr;
}

//////////////////////////////////////////////////////////////////////////////////
// End of MM1 support
//////////////////////////////////////////////////////////////////////////////////

/** \class CoolTypeContext
 *
 * This class contains everything that is needed for the callbacks that
 * interact with Cooltype in order to calculate glyph IDs and positions.
 *
 */
 

 
class CoolTypeContext : public OpenTypeContext
{
public :
	CoolTypeContext(IWRStrikeBuffer* buffer, WRInt32 start, WRInt32 nStrikes, unsigned short flags);
	~CoolTypeContext();

	virtual void ReplaceOneByMany(WRInt32 strikeIndex, const WRGlyphID32* newGlyphIDs, WRInt32 numGlyphIDs);
	virtual void ReplaceOneByOne(WRInt32 strikeIndex, WRGlyphID32 newGlyphIDs);
	virtual void ReplaceRangeByOne (WRInt32 startIndex, WRInt32 limitIndex,	WRGlyphID32 newGlyphID);
	virtual void ReplaceManyByOne (const WRInt32* strikeIndices, WRInt32 indexCount, WRGlyphID32 newGlyphID);
	//void AdjustPlacementAndAdvance (WRInt32 strikeIndex, WRFloat xPlacementDelta, WRFloat yPlacementDelta, WRFloat xAdvanceDelta, WRFloat yAdvanceDelta);
	//void MergeAnchors (WRInt32 elementIndex1, WRFloat anchor1x, WRFloat anchor1y, WRInt32 elementIndex2, WRFloat anchor2x, WRFloat anchor2y, bool isCursiveAttachment, bool lastOnBaseline);
	virtual void InsertAfterInRanges(WRInt32 index, WRInt32 count);
	virtual void DeleteOneInRanges(WRInt32 index);
	
	const char* features;
	WRInt32 *choiceIndexes;
	WRInt32* ranges; /** ranges of the features to be applied : even indexes contain the range start, odd indexes the range end **/
	WRInt32 numRanges; /** number of features to be applied, ranges' size is twice that number **/
	WRFontInstance* fontInstance;
		
	WRVector<WRInt32> numCount;
};
	

CoolTypeContext::CoolTypeContext(IWRStrikeBuffer* buffer, WRInt32 start, WRInt32 nStrikes, unsigned short inFlags) : OpenTypeContext(buffer, start, nStrikes, inFlags)
{
	numCount.Reset(0,static_cast<int>(nStrikes), 1); // initially, one input glyph for each output glyph
}

CoolTypeContext::~CoolTypeContext()
{
}



void CoolTypeContext::InsertAfterInRanges(WRInt32 strikeIndex, WRInt32 added)
{
	if (ranges)
	{
		WRInt32 nRange;
		for (nRange=0; nRange < 2*numRanges; nRange+=2)
		{
			if (ranges[nRange] > (WRInt32)strikeIndex)
				ranges[nRange] += static_cast<WRInt32>(added);
			if (ranges[nRange+1] >= (WRInt32)strikeIndex)
				ranges[nRange+1] += static_cast<WRInt32>(added);
		}
	}
}

void CoolTypeContext::DeleteOneInRanges(WRInt32 nDeletedIndex)
{
	if (ranges)
	{
		WRInt32 nRange;
		for (nRange=0; nRange < 2*numRanges; nRange+=2)
		{
			//Shorten ranges
			if (ranges[nRange] > nDeletedIndex)
			{
				ranges[nRange] -= 1;
//				if (ranges[nRange] <0)
//					ranges[nRange]=0;
			}
			if (ranges[nRange+1] >= nDeletedIndex) 
			{
				ranges[nRange+1] -= 1;
//				if (ranges[nRange+1] <0)
//					ranges[nRange+1]=0;
			}
		}
	}
}

void CoolTypeContext::ReplaceOneByMany(WRInt32 strikeIndex, const WRGlyphID32* newGlyphIDs, WRInt32 numGlyphIDs)
{
	OpenTypeContext::ReplaceOneByMany(strikeIndex, newGlyphIDs, numGlyphIDs);
	numCount[static_cast<int>(strikeIndex)] = numGlyphIDs;
	numCount.Insert(1,(int)strikeIndex+1,(int)(numGlyphIDs - 1));
}

void CoolTypeContext::ReplaceOneByOne (WRInt32 strikeIndex, WRGlyphID32 newGlyphID)
{
	numCount[static_cast<WRInt32>(strikeIndex)] = 1;
	OpenTypeContext::ReplaceOneByOne(strikeIndex, newGlyphID);
}

void CoolTypeContext::ReplaceRangeByOne (WRInt32 startIndex, WRInt32 limitIndex,	WRGlyphID32 newGlyphID)
{
	WRInt32 count = limitIndex - startIndex;
	OpenTypeContext::ReplaceRangeByOne(startIndex,limitIndex,newGlyphID);
	numCount[static_cast<int>(startIndex)] = count;
	numCount.Remove((int)startIndex+1,(int)(count - 1));
}

void CoolTypeContext::ReplaceManyByOne (const WRInt32* strikeIndices, WRInt32 indexCount, WRGlyphID32 newGlyphID)
{
	WRInt32 origCount = numStrikes; 
	OpenTypeContext::ReplaceManyByOne(strikeIndices, indexCount, newGlyphID);

	WRInt32*	p = numCount.PeekArray();
	numCount[(int)strikeIndices[0]] = indexCount;
	WRInt32 after = strikeIndices[1];
	WRInt32 before = after+1;
	WRInt32 last = strikeIndices[indexCount-1];
	

	// move inter-component slots
	for (WRInt32 index = 2; before < last ; before++)
	{
		if (before != strikeIndices[index])
			p[after++] = p[before];
		else
			index++;
	}
	// move the end
	memmove(p+after,p+last+1, (origCount-last-1)*sizeof(WRInt32));
	numCount.Resize((int)numStrikes);
}


// Forward declaration for callbacks
CTGlyphID BIBEXPORT GetGlyphIDAt (void* clientRunContext, size_t elementIndex);
void BIBEXPORT ReplaceOneByOne (void* clientRunContext, size_t strikeIndex, CTGlyphID newGlyphID, BRVBool32 isTempReplacement);
void BIBEXPORT ReplaceOneByMany (void* clientRunContext, size_t strikeIndex, const CTGlyphID* newGlyphIDs, size_t numGlyphIDs);
void BIBEXPORT ReplaceRangeByOne (void* clientRunContext, size_t startIndex, size_t limitIndex,	CTGlyphID newGlyphID);
void BIBEXPORT ReplaceManyByOne (void* clientRunContext, const size_t* strikeIndices, size_t indexCount, CTGlyphID newGlyphID);
size_t BIBEXPORT GetLigatureComponentIndex (void* clientRunContext, size_t strikeIndex);
void BIBEXPORT SetLigatureComponentIndex (void* clientRunContext, size_t strikeIndex, size_t newCompIndex);
size_t BIBEXPORT GetComponentCount (void *clientCtx, size_t strikeIndex);
void BIBEXPORT SetComponentCount (void *clientCtx, size_t strikeIndex, size_t newCompCount);
void BIBEXPORT AdjustPlacementAndAdvance (void *clientCtx, size_t strikeIndex, BRVRealCoord xPlacementDelta, BRVRealCoord yPlacementDelta, BRVRealCoord xAdvanceDelta, BRVRealCoord yAdvanceDelta);
void BIBEXPORT MergeAnchors (void *clientCtx, size_t elementIndex1, BRVRealCoord anchor1x, BRVRealCoord anchor1y, size_t elementIndex2, BRVRealCoord anchor2x, BRVRealCoord anchor2y, BRVBool32 isCursiveAttachment, BRVBool32 lastOnBaseline);
size_t BIBEXPORT GetAlternateIndex (void *clientCtx, size_t elementIndex, const size_t* featureTagIndices, size_t numFeatureTagIndices);
BRVBool32 BIBEXPORT FeatureSelectorProc (void* clientRunContext, const size_t *positions, size_t nbPositions, const size_t* featureTagIndices, size_t numFeatureTagIndices);

void CoolType5aBasedFontAccess::GetMinMaxRange(WRInt32 startIndex, WRInt32* ranges, WRInt32 size, size_t& min, size_t& max)
{
	min = 0;
	max = 0;
	if (ranges && size > 0)
	{
		WRInt32 n;
		min = (ranges[0] -= startIndex);
		max = (ranges[1] -= startIndex);
		int i=2;  
		while (i < size)
		{
			n = (ranges[i] -= startIndex);
			if (n < (WRInt32) min)
				min = n;
			n = (ranges[++i] -= startIndex);
			if (n > (WRInt32) max)
				max = n;
			i++;
		}
	}
}

WRInt32 CoolType5aBasedFontAccess::WRApplyFeatures(WRFontInstance *inst, IWRStrikeBuffer *strikes, WRInt32 startStrike, WRInt32 *pNumStrikes, WROTFeatureInfo *featureInfo, WRFloat* endPenPos)
{	
	WRInt32 err = kWRNoErr;
	CCTFontInstance fontInstance((CTFontInstance*)inst);
	CCTFontDict fontDict(fontInstance.GetFont());

	// Special case of MM1 fonts, revert to old-style API
	//if (fontDict.GetNumDesignAxes() != 0)
	 //return WRApplyFeaturesForMM1Fonts(inst, strikes, startStrike, pNumStrikes, featureInfo, endPenPos);

	// This object encapsulates the callbacks
    CTTextRunProcs runProcs(GetGlyphIDAt,
							ReplaceOneByOne,
							ReplaceOneByMany,
							ReplaceRangeByOne,
							ReplaceManyByOne,
							GetLigatureComponentIndex,
							SetLigatureComponentIndex,
							GetComponentCount,
							SetComponentCount,
							GetAlternateIndex,
							AdjustPlacementAndAdvance,
							MergeAnchors);
	// Context
	WRInt32 numStrikes = *pNumStrikes;
	CoolTypeContext clientRunContext(strikes, startStrike, numStrikes,featureInfo->flags);

	if (featureInfo && featureInfo->otherParams)
	{
		clientRunContext.gsubProc = (featureInfo->otherParams)->featureGSUBCB;
		clientRunContext.gposProc = (featureInfo->otherParams)->featureGPOSCB;
		clientRunContext.clientCtx = (featureInfo->otherParams)->clientCtx;
	}
	clientRunContext.strikes = strikes;
	clientRunContext.fontInstance = inst;
	clientRunContext.features = featureInfo->features;
	clientRunContext.ranges= featureInfo->featureRanges;
	clientRunContext.numRanges = featureInfo->numFeatures;
	clientRunContext.fError = kWRNoErr;
	clientRunContext.choiceIndexes = featureInfo->choiceIndexes;
	

	size_t startIndex = 0, limitIndex = 0;
	if (!featureInfo->featureRanges)
		limitIndex = numStrikes;
	else
	{
		GetMinMaxRange(startStrike, featureInfo->featureRanges, featureInfo->numFeatures*2, startIndex, limitIndex);
		limitIndex++;
	}
	
	CTFeatureType flags;
	if ((featureInfo->flags & kWRApplyGlyphSub) == kWRApplyGlyphSub)
		flags = kCTGlyphSubstitution;
	else
	{
		flags = kCTGlyphPositioning;
		strikes->ResetMarkPositions(startStrike,numStrikes);
	}	
	//if (clientRunContext.attribs != NULL )
#if 1
	{
		WRHybridVector<CTRealGlyphPoint,256> tempStrikes;
		CTRealGlyphPoint* pRealGlyphPoint = tempStrikes.Init(numStrikes,NULL);
		WRHybridVector<CTGlyphClassValue,256> tempClasses;
		CTGlyphClassValue* pClasses = tempClasses.Init(numStrikes,NULL);
		for (WRInt32 i = 0; i < numStrikes; i++)
			(pRealGlyphPoint++)->glyphID = strikes->GetStrike(startStrike + i).GetGlyphID();
		if (fontDict.GetGlyphClassValues(tempStrikes.PeekArray(), numStrikes, pClasses) == 0)
		{
			for (WRInt32 i = 0; i < numStrikes; i++)
				strikes->GetStrike(startStrike + i).SetGlyphClass(IWRStrike::kWRGlyphClassValue_Unknown);
		}
		else
		{
			for (WRInt32 i = 0; i < numStrikes; i++)
				strikes->GetStrike(startStrike + i).SetGlyphClass(IWRStrike::WRGlyphClassValue(pClasses[i] & 0x000000FF));
		}
	}
#else
	{
		WRVector<CTRealGlyphPoint> tempStrikes;
		WRVector<CTGlyphClassValue> tempClasses;
		for (WRInt32 i = 0; i < numStrikes; i++)
		{
			IWRStrike& strike = strikes->GetStrike(startStrike + i);
			if (strike->GetGlyphClass() == kWRGlyphClassValue_Unknown)
				(pRealGlyphPoint++)->glyphID = strikes->GetStrike(startStrike + i).GetGlyphID();
		if (fontDict.GetGlyphClassValues(tempStrikes.PeekArray(), numStrikes, pClasses) == 0)
		{
			for (WRInt32 i = 0; i < numStrikes; i++)
				strikes->GetStrike(startStrike + i).SetGlyphClass(IWRStrike::kWRGlyphClassValue_Unknown);
		}
		else
		{
			for (WRInt32 i = 0; i < numStrikes; i++)
				strikes->GetStrike(startStrike + i).SetGlyphClass(IWRStrike::WRGlyphClassValue(pClasses[i]));
		}
	}
#endif

	strikes->ResetChangeAttribs(startStrike,numStrikes);

	if (featureInfo)
	{
#ifndef BIB_NO_THROW
		try
		{
#endif
		strikes->SetRegionOfInterest(startStrike + numStrikes);
		fontInstance.ProcessFeatures(runProcs,
								 (void*)&clientRunContext,
								 featureInfo->script,
	  							 featureInfo->language,
			   					 featureInfo->features,
								 featureInfo->numFeatures,
								 flags,
								 0, numStrikes,
								 startIndex, limitIndex,
								 featureInfo->featureRanges ? FeatureSelectorProc : NULL);
		strikes->ClearRegionOfInterest();

		err = clientRunContext.fError;
		if (err == kWRNoErr)
		{
			//if (featureInfo->featureRanges)
			*pNumStrikes = static_cast<WRInt32>(clientRunContext.numStrikes);
		}
#ifndef BIB_NO_THROW
		}
		catch (...)
		{
			err = kWRCoolTypeError;
		}
#endif
	}
	return err;
}

/**
 * Callback function for CoolType (using ProcessFeatures mechanism)
 * This callback is used to return the glyph ID at a specific position
 **/
CTGlyphID GetGlyphIDAt (void* clientRunContext, size_t elementIndex)
{
	CoolTypeContext * ctx = (CoolTypeContext*) clientRunContext;
	WRInt32 i = static_cast<WRInt32>(elementIndex);
	if ( i < ctx->numStrikes)
		return (CTGlyphID) ctx->strikes->GetStrike(i + ctx->startStrike).GetGlyphID();
	else
	{
		// Should not happen. Still it happens sometimes ... to investigate
		return -1;
	}
}

/**
 * Callback function for CoolType (using ProcessFeatures mechanism)
 * This callback is used to replace one glyph with another one
 **/
void BIBEXPORT ReplaceOneByOne (void* clientRunContext, size_t strikeIndex, CTGlyphID newGlyphID, BRVBool32 /*isTemp*/)
{
	CoolTypeContext * ctx = (CoolTypeContext*) clientRunContext;
	ctx->ReplaceOneByOne(static_cast<WRInt32>(strikeIndex), (WRGlyphID32)newGlyphID);
}

/**
 * Callback function for CoolType (using ProcessFeatures mechanism)
 * This callback is used to replace one glyph by many glyphs
 **/
void BIBEXPORT ReplaceOneByMany (void* clientRunContext, size_t strikeIndex, const CTGlyphID* newGlyphIDs, size_t numGlyphIDs)
{
	CoolTypeContext * ctx = (CoolTypeContext*) clientRunContext;
	if (numGlyphIDs == 1)
		ctx->ReplaceOneByOne(static_cast<WRInt32>(strikeIndex), (WRGlyphID32)(newGlyphIDs[0]));
	else
		ctx->ReplaceOneByMany(static_cast<WRInt32>(strikeIndex),(WRGlyphID32*)newGlyphIDs,static_cast<WRInt32>(numGlyphIDs));	
}

/**
 * Callback function for CoolType (using ProcessFeatures mechanism)
 * This callback is used to replace a range of glyph by one glyph
 * \warning limitIndex is one *past* the last index of the range.
 **/
void BIBEXPORT ReplaceRangeByOne (void* clientRunContext, size_t startIndex, size_t limitIndex,	CTGlyphID newGlyphID)
{
	CoolTypeContext * ctx = (CoolTypeContext*) clientRunContext;
	if (limitIndex - startIndex == 1)
		ctx->ReplaceOneByOne(static_cast<WRInt32>(startIndex), (WRGlyphID32)newGlyphID);
	else
		ctx->ReplaceRangeByOne(static_cast<WRInt32>(startIndex),static_cast<WRInt32>(limitIndex),(WRGlyphID32)newGlyphID);
}

/**
 * Callback function for CoolType (using ProcessFeatures mechanism)
 * This callback is used to replace many glyphs (not always following each other) by one glyph
 * To test this case try : 0644 0650 0627 (kasra in the middle of a ligature)
 **/
void BIBEXPORT ReplaceManyByOne (void* clientRunContext, const size_t* strikeIndices, size_t indexCount, CTGlyphID newGlyphID)
{
	CoolTypeContext * ctx = (CoolTypeContext*) clientRunContext;
	if (indexCount == 1)
		ctx->ReplaceOneByOne(static_cast<WRInt32>(strikeIndices[0]), (WRGlyphID32)(newGlyphID));
	else
	{
		WRHybridVector<WRInt32,16> indexVector;
		WRInt32 idxcnt = static_cast<WRInt32>(indexCount);
		WRInt32* indexes = indexVector.Init(idxcnt);
		for (WRInt32 i = 0; i < idxcnt; i++)
			indexes[i] = static_cast<WRInt32>(strikeIndices[i]);
		ctx->ReplaceManyByOne(indexes,static_cast<WRInt32>(indexCount),(WRGlyphID32)newGlyphID);
	}
}

/**
 * Callback function for CoolType (using ProcessFeatures mechanism)
 **/
size_t BIBEXPORT GetLigatureComponentIndex (void* clientRunContext, size_t strikeIndex)
{
	CoolTypeContext * ctx = (CoolTypeContext*) clientRunContext;
	if (ctx->fError == kWRArrayTooShortErr)
		return 0;
	WRInt32 i = static_cast<WRInt32>(strikeIndex);
	if (i < ctx->numStrikes)
	{
		WRInt32 comp;
		if (ctx->gposProc)
		{
			ctx->gposProc(ctx->clientCtx, i  + ctx->startStrike, &comp);
			return comp;
		}
	}
	return 0;
}

/**
 * Callback function for CoolType (using ProcessFeatures mechanism)
 **/
void BIBEXPORT SetLigatureComponentIndex (void* /*clientRunContext*/, size_t /*strikeIndex*/, size_t /*newCompIndex*/)
{
	// Nothing to do : WRServices keeps this information (see GetLigatureComponentIndex)
}

/**
 * Callback function for CoolType (using ProcessFeatures mechanism)
 **/
size_t BIBEXPORT GetComponentCount (void *clientCtx, size_t strikeIndex)
{
	CoolTypeContext * ctx = (CoolTypeContext*) clientCtx;
	WRInt32 i = static_cast<WRInt32>(strikeIndex);
	if (i < ctx->numStrikes)
		return ctx->numCount[i];
	else
	{
		//@todo throw error
		return 1;
	}
}

/**
 * Callback function for CoolType (using ProcessFeatures mechanism)
 **/
void BIBEXPORT SetComponentCount (void *clientCtx, size_t strikeIndex, size_t newCompCount)
{
	CoolTypeContext * ctx = (CoolTypeContext*) clientCtx;
	ctx->numCount[static_cast<int>(strikeIndex)] = static_cast<WRInt32>(newCompCount);
}

/**
 * Callback function for CoolType (using ProcessFeatures mechanism)
 * This callback is used to move glyph without any reference to a base glyph (absolute movement)
 **/
void BIBEXPORT AdjustPlacementAndAdvance (void *clientCtx, size_t strikeIndex, BRVRealCoord xPlacementDelta, BRVRealCoord yPlacementDelta, BRVRealCoord xAdvanceDelta, BRVRealCoord yAdvanceDelta)
{
	CoolTypeContext * ctx = (CoolTypeContext*) clientCtx;
	ctx->AdjustPlacementAndAdvance(static_cast<WRInt32>(strikeIndex),xPlacementDelta, yPlacementDelta, xAdvanceDelta, yAdvanceDelta);
}

/**
 * Callback function for CoolType (using ProcessFeatures mechanism)
 * This callback is used to adjust positionning between anchors. (relative movement)
 **/
void BIBEXPORT MergeAnchors (void *clientCtx, size_t elementIndex1, BRVRealCoord anchor1x, BRVRealCoord anchor1y, size_t elementIndex2, BRVRealCoord anchor2x, BRVRealCoord anchor2y, BRVBool32 isCursiveAttachment, BRVBool32 lastOnBaseline)
{
	CoolTypeContext * ctx = (CoolTypeContext*) clientCtx;
	ctx->MergeAnchors ( static_cast<WRInt32>(elementIndex1), anchor1x, anchor1y, 
						static_cast<WRInt32>(elementIndex2), anchor2x, anchor2y, 
						isCursiveAttachment != 0, lastOnBaseline != 0);
}

/**
 * Callback function for CoolType (using ProcessFeatures mechanism)
 **/
size_t BIBEXPORT GetAlternateIndex (void *clientCtx, size_t elementIndex, const size_t* featureTagIndices, size_t numFeatureTagIndices)
{
	CoolTypeContext * ctx = (CoolTypeContext*) clientCtx;
	if (ctx->fError == kWRArrayTooShortErr)
		return 1;

	if (featureTagIndices == NULL || numFeatureTagIndices == 0 || *featureTagIndices > static_cast<size_t>(ctx->numRanges))
		return 1;
	
	std::string feat(ctx->features,4*ctx->numRanges);
	std::string featTags(ctx->features+4*featureTagIndices[0],4);

	if (ctx->choiceIndexes != NULL)
	{
		for (WRInt32 i=0; i < ctx->numRanges ; i++)
		{
			if (ctx->ranges[2*i] <= static_cast<WRInt32>(elementIndex) && static_cast<WRInt32>(elementIndex) <= ctx->ranges[2*i+1])
				if ((feat.substr(4*i, 4).compare(featTags) == 0))
				{
					// Found it
					// The choice semantic is :
					// -1 Regular --> use first value (return 1)
					//  0 undefined value (we choose to treat it as regular)
					// >0 Explicit value (sent as is to Cooltype)
					WRInt32 choice = ctx->choiceIndexes[i];
					if (choice <= 0)
						return 1;
					else
						return choice;
				}
		}
	}
	return 1;
}

/**
 * Callback function for CoolType (using ProcessFeatures mechanism)
 * This callback is used to enable the application of a feature on a particular range
 **/
BRVBool32 BIBEXPORT FeatureSelectorProc (void* clientRunContext, const size_t *positions, size_t nbPositions, const size_t* featureTagIndices, size_t numFeatureTagIndices)
{
	CoolTypeContext * ctx = (CoolTypeContext*) clientRunContext;
	if (ctx->fError == kWRArrayTooShortErr)
		return false;

	if (!ctx->ranges)
		return true;

	if (featureTagIndices == NULL)
		return true;
	
	WRInt32 start = static_cast<WRInt32>(positions[0]);
	WRInt32 end  = static_cast<WRInt32>(positions[nbPositions-1]);
	size_t rangeMaxIdx = ctx->numRanges*2-2;
	
	for (size_t fidx = 0; fidx < numFeatureTagIndices; fidx++)
	{		
		size_t tag_idx = featureTagIndices[fidx] * 2;
		
		if (tag_idx <= rangeMaxIdx && ctx->ranges[tag_idx] <= start && end <= ctx->ranges[tag_idx+1])
			return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////
// Misc. functions
//////////////////////////////////////////////////////////////////////////////

WRBool CoolType5aBasedFontAccess::UTF16toASCII(CTUTF16Unit *ucBuf, size_t ucLen, char* buffer, int avail)
{
	if ((int)ucLen >= avail - 1)
		return false;

	int i;
	for (i = 0; i < (int)ucLen ; i++)
		buffer[i] = char(ucBuf[i] & 0x7F);
	buffer[i] = 0;
	return true;
}

int CoolType5aBasedFontAccess::WR_tolower(int c) {
	if ( c >= 'A' && c <= 'Z')
	{
		return c - ('A' - 'a') ;
	}
	return c ;
}

int CoolType5aBasedFontAccess::WR_stricmp(const char *s1, const char *s2) {
	while (*s1 || *s2)
	{
		int c1 = WR_tolower(*(s1++));
		int c2 = WR_tolower(*(s2++));
		if (c1 != c2)
			return (c1 - c2);
	}
	return 0 ;
}

WRInt32 CoolType5aBasedFontAccess::WRGetNumPaths(WRFontDict* aFont) 
{ 
	CCTFontDict font((CTFontDict*)aFont);
	return static_cast<WRInt32>(font.GetNumPaths()); 
}

WRError CoolType5aBasedFontAccess::WRGetNthPath(WRFontDict* aFont, int i, WRPath& path) 
{ 
	CCTFontDict font((CTFontDict*)aFont);
	CTPathUnit	aPath[256];
	size_t pathLength = 256;
	if (font.GetNthPath(i,aPath,pathLength))
	{
#ifdef WR_MAC_ENV
		WRString pathString(aPath,static_cast<WRCharCount> (pathLength), kWRUTF8CodePage);
#elif WR_UNIX_ENV
		WRString pathString(aPath,static_cast<WRCharCount> (pathLength), kWRUTF8CodePage);
#else
		WRString pathString(aPath,static_cast<WRCharCount>(pathLength)); 
#endif
		path = WRPath(pathString);
		return kWRErr_noError;
	}
	return kWRErr_paramError;
}

bool CoolType5aBasedFontAccess::GetFontVersion(WRFontDict *fntDict, WRUInt8 *versionStr, WRByteCount len)
{
	if (versionStr == NULL)
		return false;

	*versionStr = 0;

	size_t versionStringLength = 255;
	CTUTF16Unit versionString[256];
	CCTFontDict ctFontDict((CTFontDict*)fntDict);
	ctFontDict.GetVersionString ( versionString,versionStringLength );
	WRFromUnicodeTranslator* fromUC = WRFromUnicodeTranslator::GetWRFromUnicodeTranslator();
	WRInt32	res = fromUC->TextCharToChar(versionString, static_cast<WRInt32>(versionStringLength), (WRByteChar*)versionStr, len, kWRRomanWindowsCodePage);
	versionStr[versionStringLength] = 0;
	WRUNUSED(res);

	return true;
}

bool CoolType5aBasedFontAccess::GetOutlineInfo(void* userData, OutlinePointCB callBack, WRFontDict *fntDict, WRGlyphID32 glyphID) 
{ 
	CCTFontDict cFont( (CTFontDict*) fntDict ); 
	CBRVCoordMatrix cMatrix(1.0); 

	CTGlyphSharedBuffer cGlyphBuf(1); 
	cGlyphBuf[0].glyphID = glyphID; 
	cGlyphBuf[0].xPosition = 0.0; 
	cGlyphBuf[0].yPosition = 0.0; 

	CCTText textOutlines(cFont, cMatrix, cGlyphBuf); 

	CAGMSharedBezierPath cOutlines; 
	const CBRVCoordMatrix devMatrix(2048.0); 

	BRVInt32Rect clipB; 
	clipB.xMin = BRVMINInt32; 
	clipB.yMin = BRVMINInt32; 
	clipB.xMax = BRVMAXInt32; 
	clipB.yMax = BRVMAXInt32; 

	textOutlines.GetOutlines( &devMatrix, clipB, kCTTextPreferOutlines, cOutlines); 

	size_t  pathNumPoints; 
	size_t  pathNumGlyphs; 
	const BRVRealCoord* pathCoords; 
	const AGMPointType* pathTypes; 
	const AGMGlyphInfo* pathGlyphPositions;
	size_t  pathCurPos = 0; 
	size_t  pathCurType = 0; 
	cOutlines.GetGlyphData ( &pathNumGlyphs, &pathGlyphPositions); 
	cOutlines.GetPathData( &pathNumPoints, &pathCoords, &pathTypes); 

	WRFloat coords[6];

	for (pathCurType = 0; pathCurType < pathNumPoints; pathCurType++)
	{
		switch ( pathTypes[pathCurType] ) 
		{ 
			case kAGMPathPtClose: 
				pathCurPos+=2;
				break; 
			case kAGMPathPtMoveTo: 
				coords[0] = pathCoords[pathCurPos++] / 2048.0f; 
				coords[1] = pathCoords[pathCurPos++] / 2048.0f; 
				callBack(userData, kGetOutlineInfo_MoveTo, coords);
				break; 
			case kAGMPathPtLineTo: 
				coords[0] = pathCoords[pathCurPos++] / 2048.0f; 
				coords[1] = pathCoords[pathCurPos++] / 2048.0f; 
				callBack(userData, kGetOutlineInfo_LineTo, coords);
			 	break; 
			case kAGMPathPtCurveTo: 
				coords[0] = pathCoords[pathCurPos++] / 2048.0f; 
				coords[1] = pathCoords[pathCurPos++] / 2048.0f; 
				coords[2] = pathCoords[pathCurPos++] / 2048.0f; 
				coords[3] = pathCoords[pathCurPos++] / 2048.0f; 
				coords[4] = pathCoords[pathCurPos++] / 2048.0f; 
				coords[5] = pathCoords[pathCurPos++] / 2048.0f; 
				pathCurType+=2;
				callBack(userData, kGetOutlineInfo_CubicTo, coords);
				break; 
			default:
				break;
		}
	} 
	return true;
} 




#endif
