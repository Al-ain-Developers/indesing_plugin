<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>

<xsl:template match="impl-item[@impl-file = 'dialogcontroller-impl-file']">
Generating DialogController file for <xsl:value-of select="@impl-name"/>
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{@impl-name}.cpp" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
  <xsl:call-template name="dialogcontroller"/>
  <xsl:call-template name="standard-footer"/>
 </xsl:document>	
</xsl:template>

<xsl:template name="dialogcontroller" match="dialogcontroller">
// Interface includes:
#include "IActiveContext.h"
// General includes:
#include "CDialogController.h"
// Project includes:
#include "<xsl:value-of select="/code/@short-name"/>ID.h"

/** <xsl:value-of select="@impl-name"/>
	Methods allow for the initialization, validation, and application of dialog widget
	values.
	Implements IDialogController based on the partial implementation CDialogController.

	<xsl:variable name="groupname" select="translate(/code/@long-name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz')"/>
	@ingroup <xsl:value-of select="$groupname"/>
*/
class <xsl:value-of select="@impl-name"/> : public CDialogController
{
	public:
		/** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		<xsl:value-of select="@impl-name"/>(IPMUnknown* boss) : CDialogController(boss) {}

		/** Destructor.
		*/
		virtual ~<xsl:value-of select="@impl-name"/>() {}

		/** Initialize each widget in the dialog with its default value.
			Called when the dialog is opened.
		*/
	       virtual void InitializeDialogFields(IActiveContext* dlgContext);

		/** Validate the values in the widgets.
			By default, the widget with ID kOKButtonWidgetID causes
			ValidateFields to be called. When all widgets are valid,
			ApplyFields will be called.
			@return kDefaultWidgetId if all widget values are valid, WidgetID of the widget to select otherwise.

		*/
	       virtual WidgetID ValidateDialogFields(IActiveContext* myContext);


		/** Retrieve the values from the widgets and act on them.
			@param widgetId identifies the widget on which to act.
		*/
		virtual void ApplyDialogFields(IActiveContext* myContext, const WidgetID&amp; widgetId);
};

CREATE_PMINTERFACE(<xsl:value-of select="@impl-name"/>, <xsl:value-of select="@impl-id"/>)

/* ApplyFields
*/
void <xsl:value-of select="@impl-name"/>::InitializeDialogFields(IActiveContext* dlgContext)
{
	CDialogController::InitializeDialogFields(dlgContext);
	// Put code to initialize widget values here.
}

/* ValidateFields
*/
WidgetID <xsl:value-of select="@impl-name"/>::ValidateDialogFields(IActiveContext* myContext)
{
	WidgetID result = CDialogController::ValidateDialogFields(myContext);
	// Put code to validate widget values here.
	return result;
}

/* ApplyFields
*/
void <xsl:value-of select="@impl-name"/>::ApplyDialogFields(IActiveContext* myContext, const WidgetID&amp; widgetId)
{
	// TODO add code that gathers widget values and applies them.
}
</xsl:template>
</xsl:stylesheet>
