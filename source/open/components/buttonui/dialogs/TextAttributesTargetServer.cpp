//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/dialogs/TextAttributesTargetServer.cpp $
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
//  Comments:	Based on FindChangeTargetServer.cpp in Find Change Format Panel plugin...
//  It simply makes sure that the information in the widgets is stored in
//  the ITextAttributes interface (on the same boss as this and the dialog controller)
//  and vice-versa. FindChangeTargetServer also updates a preference which we don't use...
//  This should, in principal be reusable in any dialog, since the dialog controller can
//  always comminicate the settings through ITextAttributes...  Not sure if all this is necessary
//  or not...
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "ISubject.h"
#include "ITextTargetAttributes.h" //from anna/source/components/panels/textPanel/includes
#include "IBoolData.h"
#include "IWorkspace.h"
#include "ITextAttributes.h"
#include "IStringData.h"
#include "ITextAttrUID.h"
#include "IStyleInfo.h"

#include "CObserver.h"
#include "K2SmartPtr.h"
#include "AttributeBossList.h"
//#include "TextPanelUtils.h" //from anna/source/components/panels/textPanel/includes
#include "ILayoutUIUtils.h"		// QueryActiveWorkspace()

#include "ShuksanID.h"
#include "TextPanelID.h"
#include "widgetid.h"
#include "FormFieldUIID.h"


#ifdef DEBUG
	#include "DebugClassUtils.h"
#endif

// ------------------------------------------------------------------------------------------

class TextAttributesTargetServer : public CObserver
{
public:
								TextAttributesTargetServer(IPMUnknown *boss);
		virtual					~TextAttributesTargetServer();

		virtual		void		AutoAttach();
		virtual		void 		AutoDetach();
		virtual		void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

		virtual		bool16		SetupWidget();

		virtual		void		Mute(bool16 bOn);
				// if mute is set update will return without any actions.
		virtual		bool16		IsMuted() const;



protected:
		bool16					fAttached;
		uint32					fMute;

		IPMUnknown *			QueryTarget();
		void					Notify(ClassID nClass, void *pTarget = nil);
		ITextTargetAttributes	*CreateTargetAttributes();

private:
		typedef 	CObserver	Inherited;

					IPMUnknown*	QuerySessionPreferences(PMIID prefInterfaceID);
					void		TargetToWidget(IObserver* pTargetObserver);
					void		WidgetToTarget(IObserver* pTargetObserver);
};

// ------------------------------------------------------------------------------------------

class TextAttributesTargetServerMuter
{
public:
	inline	TextAttributesTargetServerMuter(TextAttributesTargetServer *pObserver) : fObserver(pObserver) { pObserver->Mute(kTrue); }
	inline	~TextAttributesTargetServerMuter() { fObserver->Mute(kFalse); }

private:
	 TextAttributesTargetServer *fObserver;
};

CREATE_PMINTERFACE(TextAttributesTargetServer, kTextAttributesTargetServerImpl)

// ------------------------------------------------------------------------------------------

TextAttributesTargetServer::TextAttributesTargetServer(IPMUnknown *boss) :
	Inherited(boss, IID_ITEXTTARGETSERVER),
	fMute(0),
	fAttached(kFalse)
{
}


// ------------------------------------------------------------------------------------------

TextAttributesTargetServer::~TextAttributesTargetServer()
{
	ASSERT_MSG(fMute == 0, "TextAttributesTargetServer - unbalanced mute.");
}


// ------------------------------------------------------------------------------------------

void TextAttributesTargetServer::AutoAttach()
{
	if (fAttached)
		return;
	fAttached = kTrue;

	InterfacePtr<ISubject> pSubject(this, IID_ISUBJECT);
	if (pSubject)
	{
		// kMsgCallBack...
		if (!pSubject->IsAttached(this, IID_ITEXTTARGETSERVER, IID_ITEXTTARGETSERVER))
			pSubject->AttachObserver(this, IID_ITEXTTARGETSERVER, IID_ITEXTTARGETSERVER);
	}

/*TW?	
	InterfacePtr<ISubject> pPanelSubject(TextPanelUtils::QueryPanelSubject(this));
	if (pPanelSubject)
	{
		if (!pPanelSubject->IsAttached(this, IID_IFINDCHANGEFORMATPANELMSG))
			pPanelSubject->AttachObserver(this, IID_IFINDCHANGEFORMATPANELMSG);
	}
*/
	Inherited::AutoAttach();
	
	this->SetupWidget();

/*TW
	// Also save a copy of the attributes in their original state
	InterfacePtr<IFindChangeFormatData> formatData((IFindChangeFormatData*)QuerySessionPreferences(IID_IFINDCHANGEFORMATDATA));	
	const AttributeBossList* attributeBossList = nil;
	PMString paraName("Don't Care"), charName("Don't Care");
	if (formatData)
	{
		{
			if (formatData->GetDialogType() == IFindChangeFormatData::kFindDialogType)
			{
				IDataBase* targetDB = formatData->GetTargetDB();
				attributeBossList = formatData->GetFindAttrsToApply();
				UID paraStyle = formatData->GetFindParaStyle();
				if(paraStyle != kInvalidUID)
				{
					InterfacePtr<IStyleInfo>paraStyleInfo(targetDB,paraStyle, UseDefaultIID());
					paraName = paraStyleInfo->GetName();
				}
				UID charStyle = formatData->GetFindCharStyle();
				if(charStyle != kInvalidUID)
				{
					InterfacePtr<IStyleInfo>charStyleInfo(targetDB,charStyle, UseDefaultIID());
					charName = charStyleInfo->GetName();
				}
			}
			else
			{
				IDataBase* targetDB = formatData->GetTargetDB();
				attributeBossList = formatData->GetChangeAttrsToApply();

				UID paraStyle = formatData->GetChangeParaStyle();
				if (paraStyle != kInvalidUID)
				{
					InterfacePtr<IStyleInfo>paraStyleInfo(targetDB,paraStyle, UseDefaultIID());
					paraName = paraStyleInfo->GetName();
				}
				UID charStyle = formatData->GetChangeCharStyle();
				if(charStyle != kInvalidUID)
				{
					InterfacePtr<IStyleInfo>charStyleInfo(targetDB,charStyle, UseDefaultIID());
					charName = charStyleInfo->GetName();
				}
			}
		}
	}

	InterfacePtr<ITextAttributes> theOrig(this, IID_ISAVEDTEXTATTRIBUTES);
	if (theOrig && attributeBossList)
	{
		AttributeBossList* nonConstList = (AttributeBossList*)theOrig->GetBossList();
		if (nonConstList)
		{
			nonConstList->ClearAllOverrides();
			nonConstList->ApplyAttributes(attributeBossList);
		}
	}
	InterfacePtr<IStringData> savedParaName(this, IID_IFINDCHANGEPARASTYLENAME);
	if (savedParaName)
		savedParaName->Set(paraName);
	InterfacePtr<IStringData> savedCharName(this, IID_IFINDCHANGECHARSTYLENAME);
	if (savedCharName)
		savedCharName->Set(charName);
*/
}


// ------------------------------------------------------------------------------------------

void TextAttributesTargetServer::AutoDetach()
{
	if (!fAttached)
		return;
	fAttached = kFalse;

	Inherited::AutoDetach();

	InterfacePtr<ISubject> pSubject(this, IID_ISUBJECT);
	if (pSubject)
	{
		// kMsgCallBack...
		if (pSubject->IsAttached(this, IID_ITEXTTARGETSERVER, IID_ITEXTTARGETSERVER))
			pSubject->DetachObserver(this, IID_ITEXTTARGETSERVER, IID_ITEXTTARGETSERVER);
	}
/*TW ?
	InterfacePtr<ISubject> pPanelSubject(TextPanelUtils::QueryPanelSubject(this));
	if (pPanelSubject)
	{
		if (!pPanelSubject->IsAttached(this, IID_IFINDCHANGEFORMATPANELMSG))
			pPanelSubject->DetachObserver(this, IID_IFINDCHANGEFORMATPANELMSG);
	}
*/
}


// ------------------------------------------------------------------------------------------

void TextAttributesTargetServer::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	// ==> Please update GetObserverInfo()  <==

	if (protocol == IID_ITEXTTARGETSERVER  && theChange == kMsgCreateTargetImpl)
	{
		ITextTargetAttributes **pChangedBy = (ITextTargetAttributes **)changedBy;
		if (pChangedBy != nil  && *pChangedBy == nil)
		{
			InterfacePtr<IPMUnknown>pTarget(this->QueryTarget());
			*pChangedBy = ITextTargetAttributes::CreateTargetAttributes(pTarget);
		}
		return;
	}

	if (this->IsMuted())
		return;
	
	const TextAttributesTargetServerMuter aMuter(this);

#ifdef DEBUG
	if (fAttached)
	{
		InterfacePtr<ISubject>pServerSubject(this, IID_ISUBJECT);
		ASSERT_MSG(pServerSubject != nil, "TextAttributesTargetServer- missing IID_ISUBJECT at this.");
		if (pServerSubject)
			ASSERT_MSG(pServerSubject->IsAttached(this, IID_ITEXTTARGETSERVER, IID_ITEXTTARGETSERVER), "TextAttributesTargetServer - IID_ITEXTTARGETSERVER is not attached to its subject. You should use kTextPanelViewImpl for your panel.");
	}
	else
	{
		DebugClassUtilsBuffer aClassIDName;
		const char *pName = DebugClassUtils::GetIDName(&aClassIDName, ::GetClass(this), kTrue);
		// ASSERT_MSG(kFalse, "TextAttributesTargetServer- Update() called but not attached...");		
		return;
	}
#endif		
	
	// call back into the TextTargetObserver which is the changedBy
	if (protocol == IID_ITEXTTARGETSERVER )
	{
		IObserver *pTargetObserver = (IObserver *)changedBy;
		if (theChange == kMsgCallBackWidgetToTargetImpl)
		{
			WidgetToTarget(pTargetObserver);
			// extra notification here so widgets will update (esp. font-related fam/style lists)
			K2::scoped_ptr<ITextTargetAttributes>pTargetAttrs( this->CreateTargetAttributes() );	
			InterfacePtr<ISubject> pSubject(this, IID_ISUBJECT);
			if (pSubject)
			{
				pSubject->Change(kMsgTargetToWidgetImpl, IID_ITEXTTARGETOBSERVER, pTargetAttrs);
			}
			return;
		}
		
		if (theChange == kMsgCallBackTargetToWidgetImpl)
		{
			TargetToWidget(pTargetObserver);
			return;
		}

		return;
	}
			
	if (theChange == kMsgSetupWidgetImpl)
	{
		this->SetupWidget(); 
		return;
	}

	if (theChange == kMsgResetAttributeImpl)
	{
		// notify
		K2::scoped_ptr<ITextTargetAttributes>pTargetAttrs( this->CreateTargetAttributes() );	
		this->Notify( kMsgResetAttributeImpl, pTargetAttrs );
//		this->Notify( kMsgTargetToWidgetImpl, pTargetAttrs );
		return;
	}
}


// ------------------------------------------------------------------------------------------


void TextAttributesTargetServer::TargetToWidget(IObserver* pTargetObserver)
{
	InterfacePtr<ISubject>pSubject(this, IID_ISUBJECT);
	K2::scoped_ptr<ITextTargetAttributes>pTargetAttrs(this->CreateTargetAttributes());	

/*TW
	InterfacePtr<IFindChangeFormatData> formatData((IFindChangeFormatData*)QuerySessionPreferences(IID_IFINDCHANGEFORMATDATA));	
	const AttributeBossList* attributeBossList = nil;
	if (formatData)
		{
		if (formatData->GetDialogType() == IFindChangeFormatData::kFindDialogType)
			attributeBossList = formatData->GetFindAttrsToApply();
		else
			attributeBossList = formatData->GetChangeAttrsToApply();
		}

	InterfacePtr<ITextAttributes> pAttributeTarget((ITextAttributes*)pTargetAttrs->QueryTarget(IID_ITEXTATTRIBUTES));
	if (pAttributeTarget)
		pAttributeTarget->ApplyAttributes(attributeBossList);
*/
	if (pTargetObserver)
		pTargetObserver->Update(kMsgTargetToWidgetImpl, pSubject, IID_ITEXTTARGETOBSERVER, pTargetAttrs);				
	else
		pSubject->Change(kMsgTargetToWidgetImpl, IID_ITEXTTARGETOBSERVER, pTargetAttrs);

}

// ------------------------------------------------------------------------------------------

void TextAttributesTargetServer::WidgetToTarget(IObserver* pTargetObserver)
{
	K2::scoped_ptr<ITextTargetAttributes>pTargetAttrs(this->CreateTargetAttributes());	
	InterfacePtr<ISubject>pSubject(this, IID_ISUBJECT);
	if (pTargetObserver)
		pTargetObserver->Update(kMsgWidgetToTargetImpl, pSubject, IID_ITEXTTARGETOBSERVER, pTargetAttrs);
	else
		pSubject->Change(kMsgWidgetToTargetImpl, IID_ITEXTTARGETOBSERVER, pTargetAttrs);
	pTargetAttrs->ApplyToTarget();

/*TW
	InterfacePtr<ITextAttributes> pAttributeTarget((ITextAttributes*)pTargetAttrs->QueryTarget(IID_ITEXTATTRIBUTES));
	if (pAttributeTarget)
	{
#ifdef DEBUG
		//validate sourceList and sourceDB
		for (int32 i = 0; i<  pAttributeTarget->CountBosses(); i++)
		{
			InterfacePtr<const ITextAttrUID> uidAttr(static_cast<const ITextAttrUID*>(pAttributeTarget->GetBossList()->QueryBossN(i, IID_ITEXTATTRUID)));
			if (uidAttr)
			{
				UID uid = uidAttr->GetUIDData();
				
				if(uid != kInvalidUID)
				{
					InterfacePtr<IPMUnknown> pRefdUIDBoss (pTargetAttrs->GetTargetDataBase(), uid, IID_IUNKNOWN);
					if (!pRefdUIDBoss)
					{
						ASSERT_FAIL("invalid text target attribList and targetDB ");
						break;
					}
				}
			}
		}
#endif
		AttributeBossList* attribList = new AttributeBossList();	
		if (attribList)
		{
			const int32 nBoss = pAttributeTarget->CountBosses();
			attribList->ApplyAttributes((AttributeBossList *)pAttributeTarget->GetBossList());
			
			InterfacePtr<IFindChangeFormatData> formatData((IFindChangeFormatData*)QuerySessionPreferences(IID_IFINDCHANGEFORMATDATA));	
			if (formatData)
			{	
				if (formatData->GetDialogType() == IFindChangeFormatData::kFindDialogType)
				{
					formatData->SetTargetDB(pTargetAttrs->GetTargetDataBase());
					formatData->SetFindAttrsToApply(attribList);
				}
				else
				{
					formatData->SetTargetDB(pTargetAttrs->GetTargetDataBase());
					formatData->SetChangeAttrsToApply(attribList);
				}
			}
			delete attribList;
		}	
	}
*/
}

// ------------------------------------------------------------------------------------------

bool16 TextAttributesTargetServer::SetupWidget()
{
	const TextAttributesTargetServerMuter aMuter(this);
/*TW
	const ClassID nBoss = ::GetClass(this);
	ASSERT_MSG(nBoss == kFindChangeTextSelectableParaDialogBoss, "TextAttributesTargetServer - this boss is not supported.");
	if (nBoss != kFindChangeTextSelectableParaDialogBoss)
		return kFalse;
	
	InterfacePtr<IBoolData> dlgType(this, IID_IBOOLDATA);
	if (!dlgType)
		return kFalse;

	bool16 isFindFormatDlg = kFalse;

	if (dlgType->GetBool())		// kTrue means find format dialog box
		isFindFormatDlg = kTrue;

	InterfacePtr<IFindChangeFormatData> formatData((IFindChangeFormatData*)QuerySessionPreferences(IID_IFINDCHANGEFORMATDATA));	
	if (formatData)
		{
		if (isFindFormatDlg)
			formatData->SetDialogType(IFindChangeFormatData::kFindDialogType);
		else
			formatData->SetDialogType(IFindChangeFormatData::kChangeDialogType);
		}
*/
	InterfacePtr<ITextAttributes>pAttrList(this, IID_ITEXTATTRIBUTES);
	pAttrList->ClearAllOverrides();
	
#ifdef DEBUG
	{
		InterfacePtr<const ITextAttributes>pAttr(this, IID_ITEXTATTRIBUTES);	
		const AttributeBossList *pList = pAttr->GetBossList();
		for(int32 i = 0; i < pList->CountBosses(); ++i)
		{
			DebugClassUtilsBuffer aClassIDName;
			DebugClassUtils::GetIDName(&aClassIDName, pList->GetClassN(i), kTrue);
		}
	}
#endif

	// notify
	K2::scoped_ptr<ITextTargetAttributes>pTargetAttrs(this->CreateTargetAttributes());	
	this->Notify(kMsgTargetToWidgetImpl, pTargetAttrs);

	return kTrue;
}


// ------------------------------------------------------------------------------------------

void TextAttributesTargetServer::Mute(bool16 bOn)
{
	if (bOn)
		++fMute;
	else
	{
		if (fMute > 0)
			--fMute;
		else
			ASSERT_MSG(kFalse, "TextAttributesTargetServer - this has not been muted.");
	}
}


// ------------------------------------------------------------------------------------------

bool16 TextAttributesTargetServer::IsMuted() const
{
	return fMute > 0;
}


// ------------------------------------------------------------------------------------------

IPMUnknown *TextAttributesTargetServer::QueryTarget()
{
	this->AddRef();
	return this;
}


// ------------------------------------------------------------------------------------------

void TextAttributesTargetServer::Notify(ClassID nClass, void *pTarget)
{	
	InterfacePtr<ISubject> pSubject(this, IID_ISUBJECT);
	if (pSubject)
		{
		const TextAttributesTargetServerMuter aMuter(this);
		pSubject->Change(nClass, IID_ITEXTTARGETOBSERVER, pTarget);
		}
}


// ------------------------------------------------------------------------------------------

IPMUnknown* TextAttributesTargetServer::QuerySessionPreferences(PMIID prefInterfaceID)
{
	InterfacePtr<IWorkspace> sessionWorkSpace(GetExecutionContextSession()->QueryWorkspace());
	return sessionWorkSpace->QueryInterface(prefInterfaceID);
}


// ------------------------------------------------------------------------------------------

ITextTargetAttributes *TextAttributesTargetServer::CreateTargetAttributes()
{
	ITextTargetAttributes *pNew = nil;
	InterfacePtr<ITextAttributes>pTextStyles( this, IID_ITEXTATTRIBUTES );
	if( pTextStyles )
		pNew = new TextAttributesTarget( pTextStyles );

	if (pNew)
	{
		InterfacePtr<IPMUnknown> pWorkSpace(Utils<ILayoutUIUtils>()->QueryActiveWorkspace());
		IDataBase* dataBase = ::GetDataBase(pWorkSpace);
	
		pNew->SetTargetDataBase( dataBase );
		pNew->SetAcceptingUnknownValues(kTrue);
	}
	return pNew;
}


// ------------------------------------------------------------------------------------------


