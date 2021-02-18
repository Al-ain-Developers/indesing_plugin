<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>
<xsl:output name="cppfile" method="text"/>

<xsl:template match="impl-item[@impl-file = 'preflight-rulevisitor-impl-file']">
Generating <xsl:value-of select="@impl-name"/>
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{@impl-name}.cpp" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
  <xsl:call-template name="preflight-rulevisitor"/>
  <xsl:call-template name="standard-footer"/>
 </xsl:document>
</xsl:template>

<xsl:template name="preflight-rulevisitor" match="preflight-rulevisitor">
<xsl:variable name="sname" select="/code/@short-name"/>
<xsl:variable name="uppersname" select="translate($sname, 'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>

#include "IPreflightProfile.h"
#include "IPreflightRuleVisitor.h"

#include "CPMUnknown.h"
#include "IPMStream.h"
#include "Utils.h"
#include "<xsl:value-of select="/code/@short-name"/>PreflightConsts.h"
#include "<xsl:value-of select="/code/@short-name"/>ID.h"
/**
    <xsl:variable name="groupname" select="translate(/code/@long-name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz')"/>
    @ingroup <xsl:value-of select="$groupname"/>
*/
class <xsl:value-of select="@impl-name"/> : CPMUnknown&lt;IPreflightRuleVisitor&gt;
{
private:

public:
    <xsl:value-of select="@impl-name"/>(IPMUnknown* iBoss)
        : CPMUnknown&lt;IPreflightRuleVisitor&gt;(iBoss) {}

	/** See IPreflightRuleVisitor::GetClassesToVisit
	*/
    virtual PreflightObjectClassIDVector GetClassesToVisit() const;

	/** See IPreflightRuleVisitor::Visit
	*/
    virtual void Visit(IPreflightVisitInfo* iVisit);

	/** See IPreflightRuleVisitor::AggregateResults
	*/
    virtual void AggregateResults
        (
            const IPreflightProcess* iProcess,
            const IPreflightProcess::NodeIDVector&amp; resultNodes,
            IPreflightAggregatedResults* iResults,
            IPreflightAggregatedResults::NodeID parentID
        ) const;
		
		
	/** See IPreflightRuleVisitor::UpdateRuleData
	*/
	virtual void UpdateRuleData();
	
	/** See IPreflightRuleVisitor::ValidateRuleData
	*/
	virtual ErrorCode ValidateRuleData(const IPreflightRuleData::Key&amp; key, const ScriptData&amp; proposedValue) const;
};

CREATE_PMINTERFACE(<xsl:value-of select="@impl-name"/>, <xsl:value-of select="@impl-id"/>);

PreflightObjectClassIDVector <xsl:value-of select="@impl-name"/>::GetClassesToVisit() const
{
	PreflightObjectClassIDVector classes;
	// classes.push_back(kPreflightOM_Document);
	return classes;
}

void <xsl:value-of select="@impl-name"/>::Visit(IPreflightVisitInfo* iVisit)
{
/*

There are only two outcomes to Visit(): either you create one or more
results records (an error, or potential error, condition), or you don't
(no error or potential error condition). As a really simple example say
you want to implement a rule that requires a prime number of pages. Then
you would ask to look at documents (via GetClassesToVisit(), which would
return kPreflightOM_Document). In Visit() you examine the document, grab
the page list interface, look at the number of pages, see if it's a
prime number, and if it's not, you add a record. Eg:

InterfacePtr&lt;IPreflightObject&gt; iObj(iVisit->QueryObject());
InterfacePtr&lt;IDocument&gt; iDoc(iVisit->GetModelRef(), UseDefaultIID());
if (!MyUtils::DocHasPrimeNumberOfPages(iDoc))
{
	InterfacePtr&lt;IPreflightResultRecord&gt; iRecord(iVisit->CreateResultRecord());
	iRecord->SetCriteria(kPreflightRC_Default);
}

If you add a result record, you'll later be called via
AggregateResults().

*/
}

void <xsl:value-of select="@impl-name"/>::AggregateResults
	(
		const IPreflightProcess* iProcess,
		const IPreflightProcess::NodeIDVector&amp; resultNodes,
		IPreflightAggregatedResults* iResults,
		IPreflightAggregatedResults::NodeID parentID
	) const
{
/*

The purpose of this method is to convert the results
records you found in the Visit() portion into something that can be put
in the tree of results.

For something as simple as a number of pages rule there's not much to
it. The absolutely simplest implementation is

Utils&lt;IPreflightAggregatedResultsUtils&gt; iUtils;
InterfacePtr&lt;const IPreflightResultRecordTable&gt; iTable(iUtils->CreateTableFromNodes(iProcess, resultNodes)); 
// Since we only check the doc, should only have one error.
ASSERT(iTable->GetRecordCount() == 1);
InterfacePtr&lt;const IPreflightResultRecord&gt; iRec(iTable->QueryNthRecord(0));
InterfacePtr&lt;IPreflightResultNodeInfo&gt; iNode(iUtils->CreateCriteriaAndViolationNode(iRec->GetObjectID(), "Number of pages isn't prime"));
iUtils->AddResultsNode(iResults, parentID, iNode);

*/
}

void <xsl:value-of select="@impl-name"/>::UpdateRuleData()
{
}

ErrorCode <xsl:value-of select="@impl-name"/>::ValidateRuleData(const IPreflightRuleData::Key&amp; key, const ScriptData&amp; proposedValue) const
{
	return kSuccess;
}

</xsl:template>
</xsl:stylesheet>