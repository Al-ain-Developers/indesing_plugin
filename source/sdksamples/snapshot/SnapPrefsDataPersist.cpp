//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/SnapPrefsDataPersist.cpp $
//  
//  Owner: Adobe Developer Technologies
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
//  
//  SnapPrefsDataPersist is the persistent implementation of ISnapPrefsData. 
//  
//========================================================================================

#include "VCPlugInHeaders.h"
 
// Interface includes:
#include "IPMStream.h"
 
// General includes:
#include "Trace.h"
#include "CPMUnknown.h"

// Project includes:
#include "SnapID.h"
#include "ISnapPrefsData.h"

/**	SnapPrefsDataPersist

	The persistent implementation of ISnapPrefsData.
	
	@ingroup snapshot
*/
class SnapPrefsDataPersist : public CPMUnknown<ISnapPrefsData>
{
	public:
		SnapPrefsDataPersist(IPMUnknown* boss);

		virtual ~SnapPrefsDataPersist();

   		virtual void CopyPrefs(ISnapPrefsData* prefsToCopy);
	
		virtual void SetName(const WideString& name);

		virtual const WideString& GetName();

		virtual void SetFormatClassID(const ClassID& formatClassID);

		virtual const ClassID& GetFormatClassID();
		
		virtual void SetScale(const PMReal& scale);

		virtual const PMReal& GetScale();

		virtual void SetResolution(const PMReal& resolution);

		virtual const PMReal& GetResolution();

		virtual void SetMinimumResolution(const PMReal& minimumResolution);

		virtual const PMReal& GetMinimumResolution();

		virtual void SetBleed(const PMReal& bleed);

		virtual const PMReal& GetBleed();

		virtual void SetDrawArea(bool16 drawArea);

		virtual const bool16& GetDrawArea();

		virtual void SetFullResolutionGraphics (bool16 fullResolutionGraphics);

		virtual const bool16& GetFullResolutionGraphics();

		virtual void SetDrawGray(bool16 drawGray);

		virtual const bool16& GetDrawGray();

		virtual void SetDrawingFlags (int32 drawingFlags);

		virtual const int32& GetDrawingFlags();

		virtual void SetJPEGEncoding(const int32 encoding);

		virtual const int32& GetJPEGEncoding();

		virtual void SetJPEGQuality(const int32 quality);

		virtual const int32& GetJPEGQuality();

		virtual void SetTIFFPaletteType(const int32 paletteType);

		virtual const int32& GetTIFFPaletteType();

		virtual void SetGIFPaletteType(const int32 paletteType);

		virtual const int32& GetGIFPaletteType();

		virtual void SetTIFFTransparent(const bool16 transparent);

		virtual const bool16& GetTIFFTransparent();

		virtual void SetGIFTransparent(const bool16 transparent);

		virtual const bool16& GetGIFTransparent();

		virtual void SetGIFInterlaced(const bool16 interlaced);

		virtual const bool16& GetGIFInterlaced();

		virtual void ReadWrite(IPMStream* s, ImplementationID prop);
		
	private:
		WideString fName;
		ClassID fFormatClassID;
		PMReal fScale;
		PMReal fResolution;
		PMReal fMinimumResolution;
		PMReal fBleed;
		bool16 fDrawArea;
		bool16 fFullResolutionGraphics;
		bool16 fDrawGray;
		int32 fDrawingFlags;
		int32 fJPEGEncoding;
		int32 fJPEGQuality;
		int32 fTIFFPaletteType;
		int32 fGIFPaletteType;
		bool16 fTIFFTransparent;
		bool16 fGIFTransparent;
		bool16 fGIFInterlaced;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PERSIST_PMINTERFACE(SnapPrefsDataPersist, kSnapPrefsDataPersistImpl)

/* Constructor
*/
SnapPrefsDataPersist::SnapPrefsDataPersist(IPMUnknown* boss) : 	
		CPMUnknown<ISnapPrefsData>(boss),
		fName(kDialogDefaultFilenameKey),
		fFormatClassID(kInvalidClass),
		fScale(1.0),
		fResolution(kDefaultResolution),
		fMinimumResolution(kDefaultResolution),
		fBleed(0.0),
		fDrawArea(kFalse),
		fFullResolutionGraphics(kFalse),
		fDrawGray(kFalse),
		fDrawingFlags(IShape::kPrinting),
		fJPEGEncoding(SnapshotUtils::kSSJPEGBaseline),
		fJPEGQuality(SnapshotUtils::kSSJPEGExcellentQuality),
		fTIFFPaletteType(SnapshotUtils::kNoPalette),
		fGIFPaletteType(SnapshotUtils::kTryExactThenAdaptivePalette),
		fTIFFTransparent(kFalse),
		fGIFTransparent(kFalse),
		fGIFInterlaced(kFalse)
{
	TRACEFLOW("SnapShot", "SnapPrefsDataPersist::Constructor(), iDataBase = %x\n", ::GetDataBase(boss));
	//fName.SetTranslatable(kFalse);
}

/* Destructor.
*/
SnapPrefsDataPersist::~SnapPrefsDataPersist()
{
	TRACEFLOW("SnapShot","SnapPrefsDataPersist::Destructor()\n");
}

/* CopyPrefs
*/
void SnapPrefsDataPersist::CopyPrefs(ISnapPrefsData* prefsToCopy)
{
	SetName(prefsToCopy->GetName()); 
	SetFormatClassID(prefsToCopy->GetFormatClassID()); 
	SetScale(prefsToCopy->GetScale());
	SetResolution(prefsToCopy->GetResolution());
	SetBleed(prefsToCopy->GetBleed());
	SetDrawArea(prefsToCopy->GetDrawArea());
	SetFullResolutionGraphics(prefsToCopy->GetFullResolutionGraphics());
	SetDrawGray(prefsToCopy->GetDrawGray());
	SetMinimumResolution(prefsToCopy->GetMinimumResolution());
	SetDrawingFlags(prefsToCopy->GetDrawingFlags());
	SetJPEGEncoding(prefsToCopy->GetJPEGEncoding());
	SetJPEGQuality(prefsToCopy->GetJPEGQuality());
	SetTIFFPaletteType(prefsToCopy->GetTIFFPaletteType());
	SetGIFPaletteType(prefsToCopy->GetGIFPaletteType());
	SetTIFFTransparent(prefsToCopy->GetTIFFTransparent());
	SetGIFTransparent(prefsToCopy->GetGIFTransparent());
	SetGIFInterlaced(prefsToCopy->GetGIFInterlaced());
}

/* SetName
*/
void SnapPrefsDataPersist::SetName(const WideString& name)
{
	if (fName != name)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fName = name;
		
	}
}

/* GetName
*/
const WideString& SnapPrefsDataPersist::GetName ()
{
	return fName;
}

/* SetFormatClassID
*/
void SnapPrefsDataPersist::SetFormatClassID(const ClassID& formatClassID)
{
	if (fFormatClassID != formatClassID)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fFormatClassID = formatClassID;
		
	}
}

/* GetFormatClassID
*/
const ClassID& SnapPrefsDataPersist::GetFormatClassID()
{
	return fFormatClassID;
}

/* SetScale
*/
void SnapPrefsDataPersist::SetScale(const PMReal& scale)
{
	if (fScale != scale)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fScale = scale;
		
	}
}

/* GetScale
*/
const PMReal& SnapPrefsDataPersist::GetScale()
{
	return fScale;
}

/* SetResolution
*/
void SnapPrefsDataPersist::SetResolution(const PMReal& resolution)
{
	if (fResolution != resolution)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fResolution = resolution;
		
	}
}

/* GetResolution
*/
const PMReal& SnapPrefsDataPersist::GetResolution ()
{
	return fResolution;
}

/* SetBleed
*/
void SnapPrefsDataPersist::SetBleed(const PMReal& bleed)
{
	if (fBleed != bleed)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fBleed = bleed;
		
	}
}

/* GetBleed
*/
const PMReal& SnapPrefsDataPersist::GetBleed()
{
	return fBleed;
}

/* SetDrawArea
*/
void SnapPrefsDataPersist::SetDrawArea(bool16 drawArea)
{
	if (fDrawArea != drawArea)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fDrawArea = drawArea;
		
	}
}

/* GetDrawArea
*/
const bool16& SnapPrefsDataPersist::GetDrawArea()
{
	return fDrawArea;
}


/* SetFullResolutionGraphics
*/
void SnapPrefsDataPersist::SetFullResolutionGraphics(bool16 fullResolutionGraphics)
{
	if (fFullResolutionGraphics != fullResolutionGraphics)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fFullResolutionGraphics = fullResolutionGraphics;
		
	}
}

/* GetFullResolutionGraphics
*/
const bool16& SnapPrefsDataPersist::GetFullResolutionGraphics()
{
	return fFullResolutionGraphics;
}


/* SetDrawGray
*/
void SnapPrefsDataPersist::SetDrawGray(bool16 DrawGray)
{
	if (fDrawGray != DrawGray)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fDrawGray = DrawGray;
		
	}
}

/* GetDrawGray
*/
const bool16& SnapPrefsDataPersist::GetDrawGray()
{
	return fDrawGray;
}

/* SetMinimumResolution
*/
void SnapPrefsDataPersist::SetMinimumResolution(const PMReal& minimumResolution)
{
	if (fMinimumResolution != minimumResolution)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fMinimumResolution = minimumResolution;
		
	}
}

/* GetMinimumResolution
*/
const PMReal& SnapPrefsDataPersist::GetMinimumResolution()
{
	return fMinimumResolution;
}

/* SetDrawingFlags
*/
void SnapPrefsDataPersist::SetDrawingFlags(int32 drawingFlags)
{
	if (fDrawingFlags != drawingFlags)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fDrawingFlags = drawingFlags;
		
	}
}

/* GetDrawingFlags
*/
const int32& SnapPrefsDataPersist::GetDrawingFlags()
{
	return fDrawingFlags;
}

/* SetJPEGEncoding
*/
void SnapPrefsDataPersist::SetJPEGEncoding(const int32 encoding) 
{
	if (fJPEGEncoding != encoding)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fJPEGEncoding = encoding;
		
	}
}

/* GetJPEGEncoding
*/
const int32& SnapPrefsDataPersist::GetJPEGEncoding()
{
	return fJPEGEncoding;
}

/* SetJPEGQuality
*/
void SnapPrefsDataPersist::SetJPEGQuality(const int32 quality)
{
	if (fJPEGQuality != quality)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fJPEGQuality = quality;
		
	}
}

/* GetJPEGQuality
*/
const int32& SnapPrefsDataPersist::GetJPEGQuality() 
{
	return fJPEGQuality;
}

/* SetTIFFPaletteType
*/
void SnapPrefsDataPersist::SetTIFFPaletteType(const int32 paletteType) 
{
	if (fTIFFPaletteType != paletteType)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fTIFFPaletteType = paletteType;
		
	}
}

/* GetTIFFPaletteType
*/
const int32& SnapPrefsDataPersist::GetTIFFPaletteType() 
{
	return fTIFFPaletteType;
}

/* SetGIFPaletteType
*/
void SnapPrefsDataPersist::SetGIFPaletteType(const int32 paletteType) 
{
	if (fGIFPaletteType != paletteType)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fGIFPaletteType = paletteType;
		
	}
}

/* GetTIFFPaletteType
*/
const int32& SnapPrefsDataPersist::GetGIFPaletteType() 
{
	return fGIFPaletteType;
}

/* SetTIFFTransparent
*/
void SnapPrefsDataPersist::SetTIFFTransparent(const bool16 transparent)
{
	if (fTIFFTransparent != transparent)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fTIFFTransparent = transparent;
		
	}
}

/* GetTIFFTransaprent
*/
const bool16& SnapPrefsDataPersist::GetTIFFTransparent()
{
	return fTIFFTransparent;
}

/* SetGIFTransparent
*/
void SnapPrefsDataPersist::SetGIFTransparent(const bool16 transparent) 
{
	if (fGIFTransparent != transparent)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fGIFTransparent = transparent;
		
	}
}

/* GetGIFTransparent
*/
const bool16& SnapPrefsDataPersist::GetGIFTransparent()
{
	return fGIFTransparent;
}

/* SetGIFInterlaced
*/
void SnapPrefsDataPersist::SetGIFInterlaced(const bool16 interlaced)
{
	if (fGIFInterlaced != interlaced)
	{
		PreDirty (kSnapPrefsDataPersistImpl);
		fGIFInterlaced = interlaced;
		
	}
}

/* GetGIFInterlaced
*/
const bool16& SnapPrefsDataPersist::GetGIFInterlaced()
{
	return fGIFInterlaced;
}



/* ReadWrite
*/
void SnapPrefsDataPersist::ReadWrite(IPMStream* s, ImplementationID prop)
{
	TRACEFLOW("SnapShot","SnapPrefsDataPersist::ReadWrite()\n");
	fName.ReadWrite(s);
	s->XferID(fFormatClassID);
	s->XferRealNumber(fScale);
	s->XferRealNumber(fResolution);
	s->XferRealNumber(fMinimumResolution);
	s->XferRealNumber(fBleed);
	s->XferBool(fDrawArea);
	s->XferBool(fFullResolutionGraphics);
	s->XferBool(fDrawGray);
	s->XferInt32((int32&)fDrawingFlags);

	s->XferInt32(fJPEGEncoding);
	s->XferInt32(fJPEGQuality);
	s->XferInt32(fTIFFPaletteType);
	s->XferInt32(fGIFPaletteType);
	s->XferBool(fTIFFTransparent);
	s->XferBool(fGIFTransparent);
	s->XferBool(fGIFInterlaced);
}

// End, SnapPrefsDataPersist.cpp.


