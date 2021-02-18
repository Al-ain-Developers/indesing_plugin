//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/uifactories/FormFieldUIFactory.cpp $
//  
//  Owner: Tim Wright
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
//  Comments:	 User interface associated with a form field type.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

//#include "IControlView.h"
#include "ITextAttributes.h"
#include "IGraphicAttributeSuite.h"
#include "IPanelControlData.h"

#include "IListControlDataOf.h"
#include "IListBoxController.h"
#include "IGraphicStyleAttrBossList.h"
#include "ITextControlData.h"
#include "ITextAttrFont.h"
#include "ITextAttributes.h"
#include "IGraphicAttrRealNumber.h"
#include "IGraphicAttrBoolean.h"
#include "ITextAttrRealNumber.h"
#include "ITextAttrBoolean.h"
#include "ITextAttrUID.h"
#include "IDocFontMgr.h"
#include "IPMFont.h"
#include "ISwatchUtils.h"
#include "IActiveContext.h"

#include "IChoiceListAttr.h"
#include "IFormFieldFactory.h"

#include "PreferenceUtils.h"
//#include "ShuksanCoolType.h"
#include "IGraphicStateUtils.h"
#include "CAlert.h"
#include "LocaleSetting.h"
#include "CoreResTypes.h"

#include "FormFieldUIFactory.h"
#include "AttributesUtils.h"
#include "UserInterfaceUtils.h"
#include "FormFieldUIDefs.h"

using namespace AttributesUtils;
using namespace UserInterfaceUtils;

//------------------------------------------------------------------------

FormFieldUIFactory::FormFieldUIFactory(IPMUnknown * boss) :
	CPMUnknown<IFormFieldUIFactory>(boss)
{
}

//------------------------------------------------------------------------

WidgetID FormFieldUIFactory::GetPropertiesWidget() const
{
	return kInvalidWidgetID;
}

//------------------------------------------------------------------------

WidgetID FormFieldUIFactory::ValidatePropertyFields( IPanelControlData*  )
{ 
	return kDefaultWidgetId;
}

//------------------------------------------------------------------------

void FormFieldUIFactory::InitializePropertyFields( IPanelControlData* inPanelData,  IGraphicAttributeSuite* inGraphicAttrSuite )
{
}

//------------------------------------------------------------------------

void FormFieldUIFactory::GetPropertyAttributes( IPanelControlData* inPanelData,  IGraphicStyleAttributeBossList* ioProperties )
{
}

//------------------------------------------------------------------------

static void InitReal(	IGraphicAttributeSuite * inGfxAttrSuite,
						ITextAttributes* inTextAttrs,
						const ClassID inFormAttrBoss,
						const ClassID inTextAttrBoss,
						IGraphicStyleAttributeBossList* inDefaults )
{
	if ( inGfxAttrSuite->GetAttributeCount(inFormAttrBoss) == 0 )
	{
		InterfacePtr<ITextAttrRealNumber> attr( static_cast<ITextAttrRealNumber*>(::CreateObject( inTextAttrBoss, ITextAttrRealNumber::kDefaultIID)));
		attr->Set( GetRealValue(inDefaults, inFormAttrBoss)  );
		inTextAttrs->ApplyAttribute( attr );
	}
	else if ( HasUniqueValue( inGfxAttrSuite, inFormAttrBoss ) )
	{
		InterfacePtr<IGraphicAttrRealNumber> srcAttr ((IGraphicAttrRealNumber*)(inGfxAttrSuite->QueryAttribute (0, inFormAttrBoss, IGraphicAttrRealNumber::kDefaultIID)));
		InterfacePtr<ITextAttrRealNumber> dstAttr( (ITextAttrRealNumber*)(inTextAttrs->QueryByClassID(inTextAttrBoss, ITextAttrRealNumber::kDefaultIID)));

		if (dstAttr == 0)
		{
			InterfacePtr<IPMUnknown> pAttrClass( ::CreateObject( inTextAttrBoss ) );
			//textAttrs->ClearOverride(kTextAttrLeadBoss); //SPAM ???
			inTextAttrs->ApplyAttribute( pAttrClass);
			dstAttr.reset( (ITextAttrRealNumber*)(inTextAttrs->QueryByClassID(inTextAttrBoss, ITextAttrRealNumber::kDefaultIID)));
		}
	
		dstAttr->Set( srcAttr->GetRealNumber() );
	}
}

//------------------------------------------------------------------------

static void InitBoolean(	IGraphicAttributeSuite * inGfxAttrSuite,
							ITextAttributes* inTextAttrs,
							const ClassID inFormAttrBoss,
							const ClassID inTextAttrBoss,
							IGraphicStyleAttributeBossList* inDefaults )
{
	if ( inGfxAttrSuite->GetAttributeCount(inFormAttrBoss) == 0 )
	{
		InterfacePtr<ITextAttrBoolean> attr( static_cast<ITextAttrBoolean*>(::CreateObject( inTextAttrBoss, ITextAttrBoolean::kDefaultIID)));
		attr->Set(  GetBoolValue(inDefaults, inFormAttrBoss)   );
		inTextAttrs->ApplyAttribute( attr );
	}
	else if ( HasUniqueValue( inGfxAttrSuite, inFormAttrBoss ) )
	{
		InterfacePtr<IGraphicAttrBoolean> srcAttr ((IGraphicAttrBoolean*)(inGfxAttrSuite->QueryAttribute (0, inFormAttrBoss, IID_IGRAPHICATTR_BOOLEAN)));
		InterfacePtr<ITextAttrBoolean> dstAttr( (ITextAttrBoolean*)(inTextAttrs->QueryByClassID(inTextAttrBoss, IID_ITEXTATTRBOOLEAN)));

		if (dstAttr == 0)
		{
			InterfacePtr<IPMUnknown> pAttrClass( ::CreateObject( inTextAttrBoss ) );
			//textAttrs->ClearOverride(kTextAttrLeadBoss); //SPAM ???
			inTextAttrs->ApplyAttribute( pAttrClass);
			dstAttr.reset( (ITextAttrBoolean*)(inTextAttrs->QueryByClassID(inTextAttrBoss, IID_ITEXTATTRBOOLEAN)));
		}
	
		dstAttr->Set( srcAttr->GetBoolean() );
	}
}

//------------------------------------------------------------------------

static void InitColor(	IGraphicAttributeSuite * inGfxAttrSuite,
							ITextAttributes* inTextAttrs,
							const ClassID inFormAttrBoss,
							const ClassID inTextAttrBoss )
{
	if ( inGfxAttrSuite->GetAttributeCount(inFormAttrBoss) == 0 )
	{
		// setting up the attributes with the default font...
		InterfacePtr<IDocFontMgr>docfontmgr( static_cast<IDocFontMgr*>(::QueryPreferences( IID_IDOCFONTMGR , GetExecutionContextSession()->GetActiveContext())) );	
		if( docfontmgr )
		{
			InterfacePtr<ITextAttrUID> attrColor( static_cast<ITextAttrUID*>(::CreateObject( inTextAttrBoss, ITextAttrUID::kDefaultIID)));
			if (inFormAttrBoss == kFormFontStrokeColorAttrBoss)
				attrColor->Set( Utils<ISwatchUtils>()->GetNoneSwatchUID ( ::GetUIDRef(docfontmgr).GetDataBase() ) );
			else
				attrColor->Set( Utils<ISwatchUtils>()->GetBlackSwatchUID ( ::GetUIDRef(docfontmgr).GetDataBase() ) );
			inTextAttrs->ApplyAttribute( attrColor );
		}	
	}
	else if ( HasUniqueValue( inGfxAttrSuite, inFormAttrBoss ) )
	{
		InterfacePtr<ITextAttrUID> srcAttr ( (ITextAttrUID*)inGfxAttrSuite->QueryAttribute (0, inFormAttrBoss, IID_ITEXTATTRUID) );
		InterfacePtr<ITextAttrUID> dstAttr( (ITextAttrUID*)inTextAttrs->QueryByClassID(inTextAttrBoss, IID_ITEXTATTRUID) );

		if (dstAttr == 0)
		{
			InterfacePtr<IPMUnknown> pAttrClass( ::CreateObject( inTextAttrBoss ) );
			//textAttrs->ClearOverride(kTextAttrColorBoss); //SPAM ???
			inTextAttrs->ApplyAttribute( pAttrClass);
			dstAttr.reset( (ITextAttrUID*)(inTextAttrs->QueryByClassID(inTextAttrBoss, IID_ITEXTATTRUID)));
		}
	
		dstAttr->SetUIDData( srcAttr->GetUIDData() );
	}
}


//------------------------------------------------------------------------

void FormFieldUIFactory::InitializeTextPropertyFields( IPanelControlData* inPanelData,  IGraphicAttributeSuite* inGfxAttrSuite )
{
	InterfacePtr<ITextAttributes> textAttrs(inPanelData, ::UseDefaultIID());
	if (textAttrs)
	{
		//If we don't have a font attribute, set it up using default font in font mgr...

		
		if ( inGfxAttrSuite->GetAttributeCount(kFormFontStyleAttrBoss) == 0  || inGfxAttrSuite->GetAttributeCount(kFormFontUIDAttrBoss) == 0 )
		{
			// setting up the attributes with the default font...
			InterfacePtr<IDocFontMgr>docfontmgr( static_cast<IDocFontMgr*>(::QueryPreferences( IID_IDOCFONTMGR , GetExecutionContextSession()->GetActiveContext())) );	
			if( docfontmgr )
			{
				InterfacePtr<IFontMgr> fontMgr(GetExecutionContextSession(), UseDefaultIID());
				PMString defaultFontName( fontMgr->GetDefaultFontName() );
				InterfacePtr<IPMFont>defaultFont(fontMgr->QueryFont(defaultFontName) );
				if( defaultFont )
				{
					InterfacePtr<ITextAttrUID> attrFontFamily( static_cast<ITextAttrUID*>(::CreateObject( kTextAttrFontUIDBoss, ITextAttrUID::kDefaultIID)));
					if( attrFontFamily )
					{
						const UID newUIDvalue = docfontmgr->GetFontFamilyUID( defaultFont );
						attrFontFamily->SetUIDData( newUIDvalue );
					
						textAttrs->ApplyAttribute( attrFontFamily );
					}			

					InterfacePtr<ITextAttrFont> attrFontStyle( static_cast<ITextAttrFont*>(::CreateObject( kTextAttrFontStyleBoss, ITextAttrFont::kDefaultIID)));
					if( attrFontStyle )
					{
						PMString styleName;			
						defaultFont->AppendStyleName( styleName );
						attrFontStyle->SetFontName( styleName );
						
						textAttrs->ApplyAttribute( attrFontStyle );
					}			
				}
			}	
		}
		else
		{
			if ( HasUniqueValue( inGfxAttrSuite, kFormFontStyleAttrBoss ) )
			{
				InterfacePtr<ITextAttrFont> srcAttr ( (ITextAttrFont*)inGfxAttrSuite->QueryAttribute (0, kFormFontStyleAttrBoss, IID_ITEXTATTRFONT) );
				InterfacePtr<ITextAttrFont> dstAttr( (ITextAttrFont*)textAttrs->QueryByClassID(kTextAttrFontStyleBoss, IID_ITEXTATTRFONT) );

				if (dstAttr == 0)
				{
					InterfacePtr<IPMUnknown> pAttrClass( ::CreateObject( kTextAttrFontStyleBoss) );
					//textAttrs->ClearOverride(kTextAttrFontStyleBoss); //SPAM ???
					textAttrs->ApplyAttribute( pAttrClass);

					dstAttr.reset( (ITextAttrFont*)textAttrs->QueryByClassID(kTextAttrFontStyleBoss, IID_ITEXTATTRFONT) );
				}


				if (srcAttr->GetInheritAxis())
				{
					dstAttr->SetInheritAxis (kTrue);
				}
				else
				{
					dstAttr->SetInheritAxis (kFalse);
					dstAttr->SetFontName (srcAttr->GetFontName());
					dstAttr->SetMMAxes (srcAttr->GetNumMMAxes(), srcAttr->GetMMAxes());
				}
			}
			
			if ( HasUniqueValue( inGfxAttrSuite, kFormFontUIDAttrBoss ) )
			{
				InterfacePtr<ITextAttrUID> srcAttr ( (ITextAttrUID*)inGfxAttrSuite->QueryAttribute (0, kFormFontUIDAttrBoss, IID_ITEXTATTRUID) );
				InterfacePtr<ITextAttrUID> dstAttr( (ITextAttrUID*)textAttrs->QueryByClassID(kTextAttrFontUIDBoss, IID_ITEXTATTRUID) );

				if (dstAttr == 0)
				{
					InterfacePtr<IPMUnknown> pAttrClass( ::CreateObject( kTextAttrFontUIDBoss ) );
					//textAttrs->ClearOverride(kTextAttrFontUIDBoss); //SPAM ???
					textAttrs->ApplyAttribute( pAttrClass);
					dstAttr.reset( (ITextAttrUID*)textAttrs->QueryByClassID(kTextAttrFontUIDBoss, IID_ITEXTATTRUID) );
				}

				dstAttr->SetUIDData( srcAttr->GetUIDData() );
			}
		}

		InterfacePtr<IGraphicStyleAttributeBossList> defaultAttrs( QueryDefaultAttributes() );

		InitColor(inGfxAttrSuite, textAttrs, kFormFontColorAttrBoss, kTextAttrColorBoss );
		InitColor(inGfxAttrSuite, textAttrs, kFormFontStrokeColorAttrBoss, kTextAttrStrokeColorBoss );

		InitReal(inGfxAttrSuite, textAttrs, kFormFontSizeAttrBoss, kTextAttrLeadBoss,  defaultAttrs );
		InitReal(inGfxAttrSuite, textAttrs, kFormFontTintAttrBoss, kTextAttrTintBoss,  defaultAttrs );
		InitBoolean(inGfxAttrSuite, textAttrs, kFormFontOverprintAttrBoss, kTextAttrOverprintBoss,   defaultAttrs );

		InitReal(inGfxAttrSuite, textAttrs, kFormFontStrokeWeightAttrBoss, kTextAttrOutlineBoss,  defaultAttrs );
		InitReal(inGfxAttrSuite, textAttrs, kFormFontStrokeTintAttrBoss, kTextAttrStrokeTintBoss,  defaultAttrs );
		InitBoolean(inGfxAttrSuite, textAttrs, kFormFontStrokeOverprintAttrBoss, kTextAttrStrokeOverprintBoss,  defaultAttrs );
	
	}

}

//------------------------------------------------------------------------

void FormFieldUIFactory::GetTextPropertyAttributes( IPanelControlData* inPanelData,  IGraphicStyleAttributeBossList* ioProperties )
{
	InterfacePtr<ITextAttributes> textAttrs(inPanelData, ::UseDefaultIID());
	if (textAttrs)
	{
		InterfacePtr<ITextAttrFont> attrFontStyle( (ITextAttrFont*)textAttrs->QueryByClassID(kTextAttrFontStyleBoss, IID_ITEXTATTRFONT) );

		if ( attrFontStyle )
		{
			InterfacePtr<ITextAttrFont> dstAttr( (ITextAttrFont*)::CreateObject (nil, kFormFontStyleAttrBoss, IID_ITEXTATTRFONT) );

			if (attrFontStyle->GetInheritAxis())
			{
				dstAttr->SetInheritAxis (kTrue);
			}
			else
			{
				dstAttr->SetInheritAxis (kFalse);
				dstAttr->SetFontName (attrFontStyle->GetFontName());
				dstAttr->SetMMAxes (attrFontStyle->GetNumMMAxes(), attrFontStyle->GetMMAxes());
			}

			AttributesUtils::AddValue(ioProperties, kFormFontStyleAttrBoss, dstAttr );
		}


		InterfacePtr<ITextAttrUID> attrFontFamily( (ITextAttrUID*)(textAttrs->QueryByClassID(kTextAttrFontUIDBoss, IID_ITEXTATTRUID)));
		if ( attrFontFamily )
		{
			InterfacePtr<ITextAttrUID> dstAttr( (ITextAttrUID*)::CreateObject (nil, kFormFontUIDAttrBoss, IID_ITEXTATTRUID) );
			dstAttr->SetUIDData(attrFontFamily->GetUIDData());
			AttributesUtils::AddValue(ioProperties, kFormFontUIDAttrBoss, dstAttr );
		}

		InterfacePtr<ITextAttrUID> attrFontColor( (ITextAttrUID*)(textAttrs->QueryByClassID(kTextAttrColorBoss, IID_ITEXTATTRUID)));
		if ( attrFontColor )
		{
			InterfacePtr<ITextAttrUID> dstAttr( (ITextAttrUID*)::CreateObject (nil, kFormFontColorAttrBoss, IID_ITEXTATTRUID) );
			dstAttr->SetUIDData(attrFontColor->GetUIDData());
			AttributesUtils::AddValue(ioProperties, kFormFontColorAttrBoss, dstAttr );
		}


		InterfacePtr<ITextAttrUID> attrFontStrokeColor( (ITextAttrUID*)(textAttrs->QueryByClassID(kTextAttrStrokeColorBoss, IID_ITEXTATTRUID)));
		if ( attrFontStrokeColor )
		{
			InterfacePtr<ITextAttrUID> dstAttr( (ITextAttrUID*)::CreateObject (nil, kFormFontStrokeColorAttrBoss, IID_ITEXTATTRUID) );
			dstAttr->SetUIDData(attrFontStrokeColor->GetUIDData());
			AttributesUtils::AddValue(ioProperties, kFormFontStrokeColorAttrBoss, dstAttr );
		}


		InterfacePtr<ITextAttrRealNumber> attrSize( (ITextAttrRealNumber*)(textAttrs->QueryByClassID(kTextAttrLeadBoss, IID_ITEXTATTRREALNUMBER)));
		if ( attrSize )
			AttributesUtils::AddRealValue(ioProperties, kFormFontSizeAttrBoss, attrSize->GetRealNumber() );

		InterfacePtr<ITextAttrRealNumber> attrTint( (ITextAttrRealNumber*)(textAttrs->QueryByClassID(kTextAttrTintBoss, IID_ITEXTATTRREALNUMBER)));
		if ( attrTint )
			AttributesUtils::AddRealValue(ioProperties, kFormFontTintAttrBoss, attrTint->GetRealNumber() );

		InterfacePtr<ITextAttrBoolean> attrOverprint( (ITextAttrBoolean*)(textAttrs->QueryByClassID(kTextAttrOverprintBoss, IID_ITEXTATTRBOOLEAN)));
		if ( attrOverprint )
			AttributesUtils::AddBoolValue(ioProperties, kFormFontOverprintAttrBoss, attrOverprint->Get() );



		InterfacePtr<ITextAttrRealNumber> attrStrokeWeight( (ITextAttrRealNumber*)(textAttrs->QueryByClassID(kTextAttrOutlineBoss, IID_ITEXTATTRREALNUMBER)));
		if ( attrStrokeWeight )
			AttributesUtils::AddRealValue(ioProperties, kFormFontStrokeWeightAttrBoss, attrStrokeWeight->GetRealNumber() );

		InterfacePtr<ITextAttrRealNumber> attrStrokeTint( (ITextAttrRealNumber*)(textAttrs->QueryByClassID(kTextAttrStrokeTintBoss, IID_ITEXTATTRREALNUMBER)));
		if ( attrStrokeTint )
			AttributesUtils::AddRealValue(ioProperties, kFormFontStrokeTintAttrBoss, attrStrokeTint->GetRealNumber() );

		InterfacePtr<ITextAttrBoolean> attrStrokeOverprint( (ITextAttrBoolean*)(textAttrs->QueryByClassID(kTextAttrStrokeOverprintBoss, IID_ITEXTATTRBOOLEAN)));
		if ( attrStrokeOverprint )
			AttributesUtils::AddBoolValue(ioProperties, kFormFontStrokeOverprintAttrBoss, attrStrokeOverprint->Get() );


	}
}

//------------------------------------------------------------------------

PMString FormFieldUIFactory::GetTextControlValue( IPanelControlData*  inPanelData, WidgetID inWidget )
{
	PMString value;
	IControlView* view = inPanelData->FindWidget(inWidget);
	ASSERT_MSG(view, "Text control widget not found");
	if (view)
	{
		InterfacePtr<ITextControlData> data(view, IID_ITEXTCONTROLDATA);
		if (data)
			value = data->GetString();
	}
	return value;
}


//------------------------------------------------------------------------

WidgetID FormFieldUIFactory::ValidateExportValue( IPanelControlData*  inPanelData, WidgetID inWidgetID, const PMString& inOrigExportValue )
{
	// Check that the export value isn't empty
	PMString exportValue = GetTextControlValue(inPanelData, inWidgetID);
	if ( exportValue.IsEmpty() )
	{
		CAlert::ErrorAlert("$$$/Error/YouNeedToSpecifyAnExportValue");

		IControlView* view = inPanelData->FindWidget(inWidgetID);

		return kCheckExportValueEditWID;
	}
	
	// Check that the export value isn't all white space
	PMString stripedExportValue(exportValue);
	stripedExportValue.StripWhiteSpace();
	if (stripedExportValue.IsEmpty()) {
		
		CAlert::ErrorAlert("$$$/Error/YouNeedToSpecifyANonBlankExportValue");

		IControlView* view = inPanelData->FindWidget(inWidgetID);

		return kCheckExportValueEditWID;
	}
	
	
	return kDefaultWidgetId;
}

//----------------------------------------------------------------------------------------

IControlView* FormFieldUIFactory::CreatePanel() const
{
	return 0; //No extra options...
}

//----------------------------------------------------------------------------------------

IGraphicStyleAttributeBossList* FormFieldUIFactory::QueryDefaultAttributes()
{
	InterfacePtr<IFormFieldFactory> formFieldFactory( this, ::UseDefaultIID() );
	return formFieldFactory->QueryDefaultAttributes();
}

