//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectTreeViewAdapter.cpp $
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

#include "VCPlugInHeaders.h"

#include "IAutoCorrectPrefs.h"
#include "IIntData.h"
#include "ILanguage.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IUIDData.h"
#include "IWidgetParent.h"
#include "ISubject.h"

#include "AutoCorrectNodeID.h"
#include "HelperInterface.h"
#include "K2Vector.h"
#include "LanguageID.h"
#include "PreferenceUtils.h"
#include "SpellPanelID.h"

//----------------------------------------------------------------------------------------
// AutoCorrectTreeViewAdapter constructor
//----------------------------------------------------------------------------------------
class AutoCorrectTreeViewAdapter : public ITreeViewHierarchyAdapter
{
public:
	AutoCorrectTreeViewAdapter(IPMUnknown *boss);
	~AutoCorrectTreeViewAdapter();
	
	virtual NodeID_rv			GetRootNode() const;
	virtual NodeID_rv			GetParentNode(const NodeID& node) const;
	virtual int32				GetNumChildren(const NodeID& node) const;
	virtual NodeID_rv			GetNthChild(const NodeID& node, const int32& nth) const;
	virtual int32				GetChildIndex(const NodeID& parent, const NodeID& child) const;
	virtual NodeID_rv			GetGenericNodeID() const;
	virtual bool16				ShouldAddNthChild( const NodeID& node, const int32& nth ) const { return kTrue; }

private:
	ISubject*	QueryPanelSubject();
	ILanguage*	QueryLanguage();

DECLARE_HELPER_METHODS()
};

CREATE_PMINTERFACE(AutoCorrectTreeViewAdapter, kAutoCorrectTreeViewAdapterImpl)
DEFINE_HELPER_METHODS(AutoCorrectTreeViewAdapter)

//----------------------------------------------------------------------------------------
// AutoCorrectTreeViewAdapter constructor
//----------------------------------------------------------------------------------------

AutoCorrectTreeViewAdapter::AutoCorrectTreeViewAdapter(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss)
{
}


//----------------------------------------------------------------------------------------
// AutoCorrectTreeViewAdapter::~AutoCorrectTreeViewAdapter 
//----------------------------------------------------------------------------------------

AutoCorrectTreeViewAdapter::~AutoCorrectTreeViewAdapter()
{
}

//----------------------------------------------------------------------------------------
// AutoCorrectTreeViewAdapter::GetRootNode 
//----------------------------------------------------------------------------------------
NodeID_rv AutoCorrectTreeViewAdapter::GetRootNode() const
{
	WideString rootNode("!");
	return AutoCorrectNodeID::Create(rootNode, rootNode);
}

//----------------------------------------------------------------------------------------
// AutoCorrectTreeViewAdapter::GetParentNode 
//----------------------------------------------------------------------------------------
NodeID_rv AutoCorrectTreeViewAdapter::GetParentNode(const NodeID& node) const
{
    WideString rootNode("!");

    // Check if the noteIDholder is the root
    if (static_cast<AutoCorrectNodeID*>(node.Get())->GetMisspelledName() == rootNode)
        return kInvalidNodeID;

    return AutoCorrectNodeID::Create( rootNode, rootNode );
}

//----------------------------------------------------------------------------------------
// AutoCorrectTreeViewAdapter::GetNumChildren 
//----------------------------------------------------------------------------------------
int32 AutoCorrectTreeViewAdapter::GetNumChildren(const NodeID& node) const
{
	if (node == this->GetRootNode())
	{	
		InterfacePtr<ILanguage> language(const_cast<AutoCorrectTreeViewAdapter*>(this)->QueryLanguage());
		if (! language)
			return 0;
		LanguageID langID = language->GetLanguageID();

		InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences( IID_IAUTOCORRECTPREFS ));
		if (autoCorrectPrefs)
		{
			/* get the correct language */
			const AutoCorrectList& autoCorrectList = autoCorrectPrefs->GetAutoCorrectList();    /* do not copy */

			if (autoCorrectList.Length() > 0)
			{
				for (int32 j = 0; j < autoCorrectList.Length(); j++)
				{
					if (langID == autoCorrectList[j].fLanguageID)
					{
						return autoCorrectList[j].fAutoStringPair.Length();
					}
				}
			}
		}
	}
	
	// only the root has children
	return 0;
}

//----------------------------------------------------------------------------------------
// AutoCorrectTreeViewAdapter::GetNthChild
//----------------------------------------------------------------------------------------
NodeID_rv AutoCorrectTreeViewAdapter::GetNthChild(const NodeID& node, const int32& nth) const
{
	InterfacePtr<ILanguage> language(const_cast<AutoCorrectTreeViewAdapter*>(this)->QueryLanguage());
	if (! language)
		return kInvalidNodeID;
	LanguageID langID = language->GetLanguageID();
	
	InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences( IID_IAUTOCORRECTPREFS ));
	if (autoCorrectPrefs)
	{
		/* get the correct language */
		const AutoCorrectList& autoCorrectList = autoCorrectPrefs->GetAutoCorrectList();    /* do not copy */

		if (autoCorrectList.Length() > 0)
		{
			for (int32 j = 0; j < autoCorrectList.Length(); j++)
			{
				if (langID == autoCorrectList[j].fLanguageID)
				{
					//const WideString& misspelledWord = autoCorrectList[j].fAutoStringPair[nth].Key();
					//const WideString& correctedWord = autoCorrectList[j].fAutoStringPair[nth].Value();
					const WideString& misspelledWord = autoCorrectList[j].fAutoStringPair.Key(nth);
					const WideString& correctedWord = autoCorrectList[j].fAutoStringPair.Value(nth);

					return AutoCorrectNodeID::Create(correctedWord, misspelledWord);
				}
			}
		}
	}

	return kInvalidNodeID;
}

//----------------------------------------------------------------------------------------
// AutoCorrectTreeViewAdapter::GetChildIndex
//----------------------------------------------------------------------------------------
int32 AutoCorrectTreeViewAdapter::GetChildIndex(const NodeID& parent, const NodeID& child) const
{
	const WideString& misspelledWord = static_cast<AutoCorrectNodeID*>(child.Get())->GetMisspelledName();
	const WideString& correctedWord = static_cast<AutoCorrectNodeID*>(child.Get())->GetCorrectedName();
	
	NodeID parentNode = this->GetParentNode(child);
	if (!parentNode.IsValid())
		return -1;

	InterfacePtr<ILanguage> language(const_cast<AutoCorrectTreeViewAdapter*>(this)->QueryLanguage());
	if (! language)
		return 0;
	LanguageID langID = language->GetLanguageID();

	InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences( IID_IAUTOCORRECTPREFS ));
	if (autoCorrectPrefs)
	{
		/* get the correct language */
		const AutoCorrectList& autoCorrectList = autoCorrectPrefs->GetAutoCorrectList();    /* do not copy */

		if (autoCorrectList.Length() > 0)
		{
			for (int32 j = 0; j < autoCorrectList.Length(); j++)
			{
				if (langID == autoCorrectList[j].fLanguageID)
				{
					for (int32 i = 0; i < autoCorrectList[j].fAutoStringPair.Length(); i++)
					{
						//if (autoCorrectList[j].fAutoStringPair[i].Key() == misspelledWord &&
						//	autoCorrectList[j].fAutoStringPair[i].Value()  == correctedWord)
						if (autoCorrectList[j].fAutoStringPair.Key(i) == misspelledWord &&
							autoCorrectList[j].fAutoStringPair.Value(i)  == correctedWord)
						{
							return i;
						}
					}
					break;
				}
			}
		}
	}

	return -1;

}

//----------------------------------------------------------------------------------------
// AutoCorrectTreeViewAdapter::GetGenericNodeID() const
//----------------------------------------------------------------------------------------
NodeID_rv AutoCorrectTreeViewAdapter::GetGenericNodeID() const
{
	WideString str; //empty string
	return AutoCorrectNodeID::Create( str, str );	
}

#include "IPanelControlData.h"

ILanguage* AutoCorrectTreeViewAdapter::QueryLanguage()
{
    InterfacePtr<ISubject> pPanel(this->QueryPanelSubject());
    if (!pPanel)
        return nil;

    InterfacePtr<ILanguage> pLanguage(pPanel, IID_ILANGUAGE);
    if (!pLanguage)
        return nil;
	
	pLanguage->AddRef();

	return pLanguage;
}

ISubject* AutoCorrectTreeViewAdapter::QueryPanelSubject()
{
    InterfacePtr<IWidgetParent>pParent( this, IID_IWIDGETPARENT );
    if( !pParent )
        return nil;

    InterfacePtr<IPMUnknown> pPanel( pParent->QueryParentFor( IID_IAUTOCORRECTPANELMSG ) );
    if( !pPanel )
        return nil;

    return (ISubject*)pPanel->QueryInterface( IID_ISUBJECT );

}
