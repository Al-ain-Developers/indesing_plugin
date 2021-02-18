//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/SnapPrefsScriptProvider.cpp $
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
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IScriptRequestData.h"
#include "IDocument.h"
#include "IScriptUtils.h"
#include "IWorkspace.h"
#include "ISnapPrefsData.h"

// General includes:
#include "PrefsScriptProvider.h"

#include "Utils.h"
#include "PreferenceUtils.h"
#include "PNGFilterID.h"
#include "GIFFilterID.h"
#include "SCTFilterID.h"
#include "TIFFFilterID.h"
#include "JPEGFilterID.h"

// Project includes:
#include "SnapID.h"
#include "SnapScriptingDefs.h"

/** From SDK sample; Handles scripting of SnapShot preference that stores in the application workspace. 
	The Provider statement for kSnapPrefsScriptProviderBoss in Snap.fr adds the preferences into the 
	application scripting objects. Consequently this script provider is passed an IScript interface
	on a kWorkspaceBoss.

	@ingroup snapshot
 */
class SnapPrefsScriptProvider : public PrefsScriptProvider
{
public:
	/**	Constructor.
		@param boss interface pointer from boss object on which this interface is aggregated.
	 */
	SnapPrefsScriptProvider(IPMUnknown* boss);

	/**	Destructor.
	 */
	~SnapPrefsScriptProvider() {}

	/** Called if a provider can handle a property.
		@param propID identifies the ID of the property to handle.
		@param data identifies an interface pointer used to extract data.
		@param script identifies an interface pointer on a script object.
	 */
	virtual ErrorCode  AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);
 
private:

	/** Set or get the file name value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessFileNameProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the image format value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessImageFormatProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the scale value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessScaleProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the resolution value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessResolutionProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the minimum resolution value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessMinimumResolutionProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the bleed value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessBleedProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the draw area value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessDrawAreaProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the full resolution graphics value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessFullResolutionGraphicsProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the draw gray value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessDrawGrayProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the drawing flags value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessDrawingFlagsProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the JPEG encoding value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessJPEGEncodingProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the JPEG quality value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessJPEGQualityProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the TIFF palette type value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessTIFFPaletteTypeProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the GIF palette type value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessGIFPaletteTypeProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the TIFF transparent value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessTIFFTransparentProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the GIF transparent value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessGIFTransparentProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	

	/** Set or get the GIF interlaced value of ISnapPrefsData preference.
		@param propID identifies the ID of the property to handle (p_SnapData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessGIFInterlacedProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	
	
private:
	/** Get the given PMString parameter from the script event data.
		@param value OUT the parameter value
		@param scriptID IN identifies the desired parameter
		@param data IN the script event data
		@param isRequired kTrue if required, kFalse if optional
		@return kSuccess on success, other ErrorCode otherwise
	*/
	ErrorCode GetWideString(WideString& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired = kTrue) const;
};

/*	Make the implementation available to the application.
*/
CREATE_PMINTERFACE(SnapPrefsScriptProvider, kSnapPrefsScriptProviderImpl)

/*
*/
SnapPrefsScriptProvider::SnapPrefsScriptProvider(IPMUnknown* boss) : PrefsScriptProvider(boss)
{
	// Make the base class aware of the SnapShot's preferences scripting object.
	// The based will take care of creating a proxy script object when the preference
	// object is accessed.
	DefinePreference(c_SnapPref, p_SnapPref);
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do {
		switch (propID.Get())
		{
			case p_SnapFileName:
			{
				result = this->AccessFileNameProperty(propID, data, script);
				break;
			}
			case p_SnapImageFormat:
			{
				result = this->AccessImageFormatProperty(propID, data, script);
				break;
			}
			case p_SnapScale:
			{
				result = this->AccessScaleProperty(propID, data, script);
				break;
			}
			case p_SnapResolution:
			{
				result = this->AccessResolutionProperty(propID, data, script);
				break;
			}
			case p_SnapMinimumResolution:
			{
				result = this->AccessMinimumResolutionProperty(propID, data, script);
				break;
			}
			case p_SnapBleed:
			{
				result = this->AccessBleedProperty(propID, data, script);
				break;
			}
			case p_SnapDrawArea:
			{
				result = this->AccessDrawAreaProperty(propID, data, script);
				break;
			}
			case p_SnapFullResolutionGraphics:
			{
				result = this->AccessFullResolutionGraphicsProperty(propID, data, script);
				break;
			}
			case p_SnapDrawGray:
			{
				result = this->AccessDrawGrayProperty(propID, data, script);
				break;
			}
			case p_SnapDrawingFlags:
			{
				result = this->AccessDrawingFlagsProperty(propID, data, script);
				break;
			}
			case p_SnapJPEGEncoding:
			{
				result = this->AccessJPEGEncodingProperty(propID, data, script);
				break;
			}
			case p_SnapJPEGQuality:
			{
				result = this->AccessJPEGQualityProperty(propID, data, script);
				break;
			}
			case p_SnapTIFFPaletteType:
			{
				result = this->AccessTIFFPaletteTypeProperty(propID, data, script);
				break;
			}
			case p_SnapGIFPaletteType:
			{
				result = this->AccessGIFPaletteTypeProperty(propID, data, script);
				break;
			}
			case p_SnapTIFFTransparent:
			{
				result = this->AccessTIFFTransparentProperty(propID, data, script);
				break;
			}
			case p_SnapGIFTransparent:
			{
				result = this->AccessGIFTransparentProperty(propID, data, script);
				break;
			}
			case p_SnapGIFInterlaced:
			{
				result = this->AccessGIFInterlacedProperty(propID, data, script);
				break;
			}
				
			default:
			{
				result = PrefsScriptProvider::AccessProperty(propID, data, script);
				break;
			}
		}
	} while (false);
	if (result == kFailure) {
		result = kSnapFailureErrorCode;
	}
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessFileNameProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		if (data->IsPropertyPut())
		{
			// Get the new ISnapPrefsData's file name passed by the script.
			WideString newName;
			result = this->GetWideString(newName, propID, data);
			if (result != kSuccess) 
			{
				break;
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetName(newName);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the file name string value from the preferences and pass it back to the caller.
			ScriptData scriptData;
			scriptData.SetWideString(iSnapShotPreferences->GetName());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessImageFormatProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		ScriptID	imageFormatID;
		if (data->IsPropertyPut())
		{
			ClassID imageFormatClassID;
			// Get the new ISnapPrefsData's file name passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapImageFormat, scriptData ) ;
			if (err != kSuccess)
			{
				break;
			}
			err = scriptData.GetEnumeration(&imageFormatID);
			switch (imageFormatID.Get())
			{
				case	en_SnapExPNG:
					imageFormatClassID = kPNGImageWriteFormatBoss;
					break;
				case	en_SnapExGIF:
					imageFormatClassID = kGIFImageWriteFormatBoss;
					break;
				case	en_SnapExSCT:
					imageFormatClassID = kSCTImageWriteFormatBoss;
					break;
				case	en_SnapExTIFF:
					imageFormatClassID = kTIFFImageWriteFormatBoss;
					break;
				case	en_SnapExJPEG:
					imageFormatClassID = kJPEGImageWriteFormatBoss;
					break;
				default:
					return Utils<IScriptErrorUtils>()->SetInvalidParameterErrorData(data, p_SnapImageFormat);
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetFormatClassID(imageFormatClassID);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the image format value from the preferences and pass it back to the caller.
			switch ((iSnapShotPreferences->GetFormatClassID()).Get())
			{
				case	kPNGImageWriteFormatBoss:
					imageFormatID = en_SnapExPNG;
					break;
				case	kGIFImageWriteFormatBoss:
					imageFormatID = en_SnapExGIF;
					break;
				case	kSCTImageWriteFormatBoss:
					imageFormatID = en_SnapExSCT;
					break;
				case	kTIFFImageWriteFormatBoss:
					imageFormatID = en_SnapExTIFF;
					break;
				case	kJPEGImageWriteFormatBoss:
					imageFormatID = en_SnapExJPEG;
					break;
				default:
					return kFailure;
			}
			scriptData.SetEnumeration(imageFormatID);
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessScaleProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		if (data->IsPropertyPut())
		{
			PMReal scale;
			// Get the new ISnapPrefsData's scale factor passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapScale, scriptData ) ;
			err = scriptData.GetPMReal(&scale);
			if (err != kSuccess)
			{
				break;
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetScale(scale);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the image format value from the preferences and pass it back to the caller.
			scriptData.SetPMReal(iSnapShotPreferences->GetScale());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessResolutionProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		if (data->IsPropertyPut())
		{
			PMReal resolution;
			// Get the new ISnapPrefsData's resolution passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapResolution, scriptData ) ;
			err = scriptData.GetPMReal(&resolution);
			if (err != kSuccess)
			{
				break;
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetResolution(resolution);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the resolution value from the preferences and pass it back to the caller.
			scriptData.SetPMReal(iSnapShotPreferences->GetResolution());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessMinimumResolutionProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		if (data->IsPropertyPut())
		{
			PMReal resolution;
			// Get the new ISnapPrefsData's resolution passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapMinimumResolution, scriptData ) ;
			err = scriptData.GetPMReal(&resolution);
			if (err != kSuccess)
			{
				break;
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetMinimumResolution(resolution);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the resolution value from the preferences and pass it back to the caller.
			scriptData.SetPMReal(iSnapShotPreferences->GetMinimumResolution());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessBleedProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		PMReal bleed;
		if (data->IsPropertyPut())
		{
			// Get the new ISnapPrefsData's resolution passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapBleed, scriptData ) ;
			err = scriptData.GetUnit(&bleed, ScriptData::kXCoordinate, script, data->GetRequestContext());
			if (err != kSuccess)
			{
				break;
			}
			if (bleed < (-120 * 12) || bleed > 120 * 12)
			{
				result = Utils<IScriptErrorUtils>()->SetOutOfRangeErrorData( data, p_SnapBleed, ScriptData( bleed ) );
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetBleed(bleed);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the resolution value from the preferences and pass it back to the caller.
			bleed = iSnapShotPreferences->GetBleed();
			scriptData.SetUnit(bleed, ScriptData::kXCoordinate, script, data->GetRequestContext());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessDrawAreaProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		bool16 drawArea = true;
		if (data->IsPropertyPut())
		{
			// Get the new ISnapPrefsData's draw area boolean passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapDrawArea, scriptData ) ;
			err = scriptData.GetBoolean(&drawArea);
			if (err != kSuccess)
			{
				break;
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetDrawArea(drawArea);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the draw area boolean from the preferences and pass it back to the caller.
			scriptData.SetBoolean(iSnapShotPreferences->GetDrawArea());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessFullResolutionGraphicsProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		bool16 fullRes = false;
		if (data->IsPropertyPut())
		{
			// Get the new ISnapPrefsData's full res graphic boolean passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapFullResolutionGraphics, scriptData ) ;
			err = scriptData.GetBoolean(&fullRes);
			if (err != kSuccess)
			{
				break;
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetFullResolutionGraphics(fullRes);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the full res graphic boolean from the preferences and pass it back to the caller.
			scriptData.SetBoolean(iSnapShotPreferences->GetFullResolutionGraphics());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessDrawGrayProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		bool16 drawGray = true;
		if (data->IsPropertyPut())
		{
			// Get the new ISnapPrefsData's color mode boolean passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapDrawGray, scriptData ) ;
			err = scriptData.GetBoolean(&drawGray);
			if (err != kSuccess)
			{
				break;
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetDrawGray(drawGray);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the color mode boolean from the preferences and pass it back to the caller.
			scriptData.SetBoolean(iSnapShotPreferences->GetDrawGray());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessDrawingFlagsProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		int32 drawFlags;
		if (data->IsPropertyPut())
		{
			// Get the new ISnapPrefsData's drawing flags passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapDrawingFlags, scriptData ) ;
			err = scriptData.GetInt32(&drawFlags);
			if (err != kSuccess)
			{
				break;
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetDrawingFlags(drawFlags);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the drawing flags from the preferences and pass it back to the caller.
			scriptData.SetInt32(iSnapShotPreferences->GetDrawingFlags());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessJPEGEncodingProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		int32 jpegEncoding;
		if (data->IsPropertyPut())
		{
			// Get the new ISnapPrefsData's JPEG encoding passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapJPEGEncoding, scriptData ) ;
			err = scriptData.GetInt32(&jpegEncoding);
			if (err != kSuccess)
			{
				break;
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetJPEGEncoding(jpegEncoding);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the JPEG encoding from the preferences and pass it back to the caller.
			scriptData.SetInt32(iSnapShotPreferences->GetJPEGEncoding());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessJPEGQualityProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		int32 jpegQuality;
		if (data->IsPropertyPut())
		{
			// Get the new ISnapPrefsData's JPEG quality flag passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapJPEGQuality, scriptData ) ;
			err = scriptData.GetInt32(&jpegQuality);
			if (err != kSuccess)
			{
				break;
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetJPEGQuality(jpegQuality);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the JPEG quality flag from the preferences and pass it back to the caller.
			scriptData.SetInt32(iSnapShotPreferences->GetJPEGQuality());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessTIFFPaletteTypeProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		int32 tiffPalType;
		if (data->IsPropertyPut())
		{
			// Get the new ISnapPrefsData's TIFF palette type passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapTIFFPaletteType, scriptData ) ;
			err = scriptData.GetInt32(&tiffPalType);
			if (err != kSuccess)
			{
				break;
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetTIFFPaletteType(tiffPalType);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the TIFF palette type from the preferences and pass it back to the caller.
			scriptData.SetInt32(iSnapShotPreferences->GetTIFFPaletteType());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessGIFPaletteTypeProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		int32 gifPalType;
		if (data->IsPropertyPut())
		{
			// Get the new ISnapPrefsData's GIF palette type passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapGIFPaletteType, scriptData ) ;
			err = scriptData.GetInt32(&gifPalType);
			if (err != kSuccess)
			{
				break;
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetGIFPaletteType(gifPalType);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the GIF palette type from the preferences and pass it back to the caller.
			scriptData.SetInt32(iSnapShotPreferences->GetGIFPaletteType());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessTIFFTransparentProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		bool16 tiffTransparent = true;
		if (data->IsPropertyPut())
		{
			// Get the new ISnapPrefsData's TIFF Transparent mode passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapTIFFTransparent, scriptData ) ;
			err = scriptData.GetBoolean(&tiffTransparent);
			if (err != kSuccess)
			{
				break;
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetTIFFTransparent(tiffTransparent);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the TIFF Transparent mode from the preferences and pass it back to the caller.
			scriptData.SetBoolean(iSnapShotPreferences->GetTIFFTransparent());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessGIFTransparentProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		bool16 gifTransparent;
		if (data->IsPropertyPut())
		{
			// Get the new ISnapPrefsData's GIF Transparent mode passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapGIFTransparent, scriptData ) ;
			err = scriptData.GetBoolean(&gifTransparent);
			if (err != kSuccess)
			{
				break;
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetGIFTransparent(gifTransparent);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the GIF Transparent mode from the preferences and pass it back to the caller.
			scriptData.SetBoolean(iSnapShotPreferences->GetGIFTransparent());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::AccessGIFInterlacedProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{

	ErrorCode result = kFailure;
	do {
		InterfacePtr<ISnapPrefsData> iSnapShotPreferences((ISnapPrefsData*)::QuerySessionPreferences(IID_ISNAPPREFSDATA));
		ASSERT(iSnapShotPreferences);
		if (!iSnapShotPreferences) {
			result = kInvalidScriptTargetError;
			break;
		}	
		ScriptData scriptData;
		bool16 gifInterlaced;
		if (data->IsPropertyPut())
		{
			// Get the new ISnapPrefsData's GIF Interlaced mode passed by the script.
			ErrorCode err = data->ExtractRequestData( p_SnapGIFInterlaced, scriptData ) ;
			err = scriptData.GetBoolean(&gifInterlaced);
			if (err != kSuccess)
			{
				break;
			}
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSnapSetPrefsCmdBoss));
			if (!cmd)
			{
				break;
			}
			InterfacePtr<ISnapPrefsData> snapCmdPrefs(cmd, IID_ISNAPPREFSDATA);
			if (!snapCmdPrefs)
			{
				break;
			}
			snapCmdPrefs->CopyPrefs(iSnapShotPreferences);
			snapCmdPrefs->SetGIFInterlaced(gifInterlaced);
				
			result = CmdUtils::ProcessCommand(cmd);
			if(result != kSuccess) 
			{
				result = kSnapDataAccessErrorCode;
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the GIF Interlaced mode from the preferences and pass it back to the caller.
			scriptData.SetBoolean(iSnapShotPreferences->GetGIFInterlaced());
			data->AppendReturnData( script, propID, scriptData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode SnapPrefsScriptProvider::GetWideString(WideString& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired) const
{
	ErrorCode result = kFailure;
	do {
		ASSERT(data);
		ScriptData inputdata;
		result = data->ExtractRequestData(scriptID.Get(), inputdata);
		if (result != kSuccess) {
			break;
		}
		result = inputdata.GetWideString(value);
	} while(false);
	if (result != kSuccess && isRequired) {
		result = Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, scriptID);
	}
	return result;
}

// SnapPrefsScriptProvider.cpp
