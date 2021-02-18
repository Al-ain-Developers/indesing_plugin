<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>
<xsl:output name="cppfile" method="text"/>

<xsl:template match="impl-item[@impl-file = 'actioncomponent-impl-file']">Generating Simple Implementation file for <xsl:value-of select="@impl-name"/>
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{@impl-name}.cpp" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
  <xsl:call-template name="actioncomponent"/>
  <xsl:call-template name="standard-footer"/>
 </xsl:document>	
</xsl:template>

<xsl:template match="actioncomponent" name="actioncomponent">
<xsl:variable name="implname" select="@impl-name"/>
// Interface includes:
<xsl:if test="/code/generate-dialog">#include "ISession.h"
#include "IApplication.h"
#include "IDialogMgr.h"
#include "IDialog.h"
// Dialog-specific resource includes:
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
</xsl:if>
// General includes:
#include "CActionComponent.h"
#include "CAlert.h"

// Project includes:
#include "<xsl:value-of select="/code/@short-name"/>ID.h"

/** Implements IActionComponent; performs the actions that are executed when the plug-in's
	menu items are selected.

	<xsl:variable name="groupname" select="translate(/code/@long-name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz')"/>
	@ingroup <xsl:value-of select="$groupname"/>

*/
class <xsl:value-of select="@impl-name"/> : public CActionComponent
{
public:
/**
 Constructor.
 @param boss interface ptr from boss object on which this interface is aggregated.
 */
		<xsl:value-of select="@impl-name"/>(IPMUnknown* boss);

		/** The action component should perform the requested action.
			This is where the menu item's action is taken.
			When a menu item is selected, the Menu Manager determines
			which plug-in is responsible for it, and calls its DoAction
			with the ID for the menu item chosen.

			@param actionID identifies the menu item that was selected.
			@param ac active context
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not relevant.
			@param widget contains the widget that invoked this action. May be nil. 
			*/
		virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

	private:
		/** Encapsulates functionality for the about menu item. */
		void DoAbout();
		
<xsl:if test="/code/generate-dialog">		/** Opens this plug-in's dialog. */
		void DoDialog();
		
</xsl:if>

<xsl:for-each select="/code/action-item">	       
		void Do<xsl:value-of select="@action-name"/>(IActiveContext* ac);
</xsl:for-each>

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(<xsl:value-of select="@impl-name"/>, <xsl:value-of select="@impl-id"/>)

/* <xsl:value-of select="@impl-name"/> Constructor
*/
<xsl:value-of select="@impl-name"/>::<xsl:value-of select="@impl-name"/>(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/* DoAction
*/
void <xsl:value-of select="$implname"/>::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
<xsl:if test="/code/generate-panel">
		case k<xsl:value-of select="/code/@short-name"/>PopupAboutThisActionID:</xsl:if>
		case k<xsl:value-of select="/code/@short-name"/>AboutActionID:
		{
			this->DoAbout();
			break;
		}
					
<xsl:if test="/code/generate-dialog">
		case k<xsl:value-of select="/code/@short-name"/>DialogActionID:
		{
			this->DoDialog();
			break;
		}
</xsl:if>

<xsl:for-each select="/code/action-item">		
		case <xsl:value-of select="@action-id"/>:
		{
			this->Do<xsl:value-of select="@action-name"/>(ac);
			break;
		}
</xsl:for-each>

		default:
		{
			break;
		}
	}
}

/* DoAbout
*/
void <xsl:value-of select="$implname"/><xsl:value-of select="@name-postfix"/>::DoAbout()
{
	CAlert::ModalAlert
	(
		k<xsl:value-of select="/code/@short-name"/>AboutBoxStringKey,				// Alert string
		kOKString, 						// OK button
		kNullString, 						// No second button
		kNullString, 						// No third button
		1,							// Set OK button to default
		CAlert::eInformationIcon				// Information icon.
	);
}


<xsl:for-each select="/code/action-item">/* Do<xsl:value-of select="@action-name"/>
*/
void <xsl:value-of select="$implname"/>::Do<xsl:value-of select="@action-name"/>(IActiveContext* ac)
{
	CAlert::InformationAlert("<xsl:value-of select="@action-string"/>");
}
</xsl:for-each>

<xsl:if test="/code/generate-dialog">
/* DoDialog
*/
void <xsl:value-of select="/code/@short-name"/>ActionComponent::DoDialog()
{
	do
	{
		// Get the application interface and the DialogMgr.	
		InterfacePtr&lt;IApplication&gt; application(GetExecutionContextSession()->QueryApplication());
		ASSERT(application);
		if (application == nil) {	
			break;
		}
		InterfacePtr&lt;IDialogMgr&gt; dialogMgr(application, UseDefaultIID());
		ASSERT(dialogMgr);
		if (dialogMgr == nil) {
			break;
		}

		// Load the plug-in's resource.
		PMLocaleId nLocale = LocaleSetting::GetLocale();
		RsrcSpec dialogSpec
		(
			nLocale,					// Locale index from PMLocaleIDs.h. 
			k<xsl:value-of select="/code/@short-name"/>PluginID,			// Our Plug-in ID  
			kViewRsrcType,				// This is the kViewRsrcType.
			kSDKDefDialogResourceID,	// Resource ID for our dialog.
			kTrue						// Initially visible.
		);

		// CreateNewDialog takes the dialogSpec created above, and also
		// the type of dialog being created (kMovableModal).
		IDialog* dialog = dialogMgr->CreateNewDialog(dialogSpec, IDialog::kMovableModal);
		ASSERT(dialog);
		if (dialog == nil) {
			break;
		}

		// Open the dialog.
		dialog->Open(); 
	
	} while (false);			
}
</xsl:if>

</xsl:template>

</xsl:stylesheet>
