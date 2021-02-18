<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>


<xsl:template match="impl-item[@impl-file = 'dialogobserver-impl-file']">
Generating dialogobserver file for <xsl:value-of select="@impl-name"/>
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{@impl-name}.cpp" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
  <xsl:call-template name="dialogobserver"/>
  <xsl:call-template name="standard-footer"/>
 </xsl:document>	
</xsl:template>

<xsl:template name="dialogobserver" match="dialogobserver">
// Interface includes:
#include "IControlView.h"
#include "IPanelControlData.h"
#include "ISubject.h"
// General includes:
#include "CDialogObserver.h"
// Project includes:
#include "<xsl:value-of select="/code/@short-name"/>ID.h"


/** Implements IObserver based on the partial implementation CDialogObserver.

	<xsl:variable name="groupname" select="translate(/code/@long-name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz')"/>
	@ingroup <xsl:value-of select="$groupname"/>
*/
class <xsl:value-of select="@impl-name"/> : public CDialogObserver
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		<xsl:value-of select="@impl-name"/>(IPMUnknown* boss) : CDialogObserver(boss) {}

		/** Destructor. */
		virtual ~<xsl:value-of select="@impl-name"/>() {}

		/**
			Called by the application to allow the observer to attach to the subjects
			to be observed, in this case the dialog's info button widget. If you want
			to observe other widgets on the dialog you could add them here.
		*/
		virtual void AutoAttach();

		/** Called by the application to allow the observer to detach from the subjects being observed. */
		virtual void AutoDetach();

		/**
			Called by the host when the observed object changes, in this case when
			the dialog's info button is clicked.
			@param theChange specifies the class ID of the change to the subject. Frequently this is a command ID.
			@param theSubject points to the ISubject interface for the subject that has changed.
			@param protocol specifies the ID of the changed interface on the subject boss.
			@param changedBy points to additional data about the change. Often this pointer indicates the class ID of the command that has caused the change.
		*/
		virtual void Update
		(
			const ClassID&amp; theChange,
			ISubject* theSubject,
			const PMIID&amp; protocol,
			void* changedBy
		);
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(<xsl:value-of select="@impl-name"/>, <xsl:value-of select="@impl-id"/>)

/* AutoAttach
*/
void <xsl:value-of select="@impl-name"/>::AutoAttach()
{
	// Call the base class AutoAttach() function so that default behavior
	// will still occur (OK and Cancel buttons, etc.).
	CDialogObserver::AutoAttach();
	do
	{
		InterfacePtr&lt;IPanelControlData&gt; panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if(!panelControlData) {
			break;
		}
		// Attach to other widgets you want to handle dynamically here.

	} while (kFalse);
}

/* AutoDetach
*/
void <xsl:value-of select="@impl-name"/>::AutoDetach()
{
	// Call base class AutoDetach() so that default behavior will occur (OK and Cancel buttons, etc.).
	CDialogObserver::AutoDetach();
	do
	{
		InterfacePtr&lt;IPanelControlData&gt; panelControlData(this, UseDefaultIID());
		ASSERT(panelControlData);
		if(!panelControlData) {
			break;
		}
		// Detach from other widgets you handle dynamically here.

	} while (kFalse);
}

/* Update
*/
void <xsl:value-of select="@impl-name"/>::Update
(
	const ClassID&amp; theChange,
	ISubject* theSubject,
	const PMIID&amp; protocol,
	void* changedBy
)
{
	// Call the base class Update function so that default behavior will still occur (OK and Cancel buttons, etc.).
	CDialogObserver::Update(theChange, theSubject, protocol, changedBy);
	do
	{
		InterfacePtr&lt;IControlView&gt; controlView(theSubject, UseDefaultIID());
		ASSERT(controlView);
		if(!controlView) {
			break;
		}
		// Get the button ID from the view.
		WidgetID theSelectedWidget = controlView->GetWidgetID();
		// TODO: process this

	} while (kFalse);
}
</xsl:template>
</xsl:stylesheet>
