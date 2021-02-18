//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationUIManagePresetListBoxWidgetMgr.cpp $
//  
//  Owner: Yeming Liu
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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

// ----- Interfaces -----

#include "IMotionPresetMgr.h"
#include "ITextControlData.h"

// ----- Utils -----

#include "IMotionPresetUtils.h"

// ----- Includes -----

#include "StringListBoxTreeViewWidgetMgr.h" 
#include "DynamicDocumentsUIDefs.h"
#include "StringNodeID.h"

// ----- ID.h files -----
#include "DynamicDocumentsUIID.h"

class AnimationUIManagePresetListBoxWidgetMgr : public StringListBoxWidgetMgr
{
		typedef StringListBoxWidgetMgr inherited;

	public:
		AnimationUIManagePresetListBoxWidgetMgr (IPMUnknown *boss) : inherited (boss) {}
		virtual ~AnimationUIManagePresetListBoxWidgetMgr() {}

	protected:
		virtual bool16	ApplyDataToWidget( const NodeID& node, IPanelControlData* widgetList, int32 message = 0 ) const
		{
			inherited::ApplyDataToWidget(node, widgetList, message);

			IControlView* iTextWidgetView = widgetList->FindWidget( kStaticTextWidgetID );
			InterfacePtr<ITextControlData>	iTextControlData(iTextWidgetView, UseDefaultIID());
			if (iTextControlData)
			{
				PMString presetName = iTextControlData->GetString();

				InterfacePtr<IMotionPresetMgr> iAppPresetMgr(Utils<IMotionPresetUtils>()->QueryMotionPresetManager ()); 
				int32 presetIndex = iAppPresetMgr->FindPreset(presetName);

				if (presetIndex >= 0 && iAppPresetMgr->IsDefaultPreset(presetIndex))
				{
					presetName.SetTranslatable(kTrue);
					presetName.Translate ();

					PMString prefix("kAnimationUIManagePresetNamePrefix", PMString::kTranslateDuringCall);
					prefix.Append(presetName);	// becomes "[presetname

					PMString suffix("kAnimationUIManagePresetNameSuffix", PMString::kTranslateDuringCall);
					prefix.Append(suffix); // becomes "[presetname]"

					presetName = prefix;
				}

				iTextControlData->SetString( presetName );
			}

			return kTrue;
		}

		virtual void RegisterStyles()
		{
			RegisterStyleWidget( kLargePaletteRowsTreeStyle, kAnimationUIManagePresetsDialogListNodeRsrcID, kDynamicDocumentsUIPluginID);
		}
};

CREATE_PMINTERFACE(AnimationUIManagePresetListBoxWidgetMgr, kAnimationUIManagePresetListBoxWidgetMgrImpl)
