/*
ADOBE SYSTEMS INCORPORATED
Copyright 2012 Adobe Systems Incorporated
All Rights Reserved.

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
terms of the Adobe license agreement accompanying it.  If you have received this file from a 
source other than Adobe, then your use, modification, or distribution of it requires the prior 
written permission of Adobe.
*/
package com.adobe.indesign.layouthelper
{
	import com.adobe.csawlib.indesign.InDesign;
	import com.adobe.indesign.*;
	
	public class Util
	{
		public static function mapLayoutOptiontoStr(policyOption:LayoutRuleOptions):String
		{
			var policy:String;
			switch(policyOption)
			{
				case LayoutRuleOptions.OFF:
					policy = "off";
					break;
				case LayoutRuleOptions.GUIDE_BASED:
					policy = "guidebased";
					break;
				case LayoutRuleOptions.OBJECT_BASED:
					policy = "objectbased";
					break;
				case LayoutRuleOptions.SCALE:
					policy = "scale";
					break;
				case LayoutRuleOptions.RECENTER:
					policy = "recenter";
					break;
				default:
					policy = "off";
					break;
			}

			return policy;
		}
		
		public static function mapStrtoLayoutOption(policyStr:String):LayoutRuleOptions
		{
			var policy:LayoutRuleOptions;
			if(policyStr == "off")
			{
				policy = LayoutRuleOptions.OFF;
			}
			else if(policyStr == "guidebased")
			{
				policy = LayoutRuleOptions.GUIDE_BASED;
			}
			else if(policyStr == "objectbased")
			{
				policy = LayoutRuleOptions.OBJECT_BASED;
			}
			else if(policyStr == "scale")
			{
				policy = LayoutRuleOptions.SCALE;
			}
			else if(policyStr == "recenter")
			{
				policy = LayoutRuleOptions.RECENTER;
			}
			else
			{
				policy = LayoutRuleOptions.OFF;
			}
			
			return policy;
		}
	}
}