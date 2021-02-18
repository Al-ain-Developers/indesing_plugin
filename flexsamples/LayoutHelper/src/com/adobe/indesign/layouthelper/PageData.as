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
	import com.adobe.indesign.Document;
	import com.adobe.indesign.DocumentPreset;
	
	public class PageData
	{
		[Bindable]
		public var policy:String = "";
		[Bindable]
		public var pagename:String = "";
		[Bindable]
		public var pageidx:Number;
		[Bindable]
		public var pageid:Number;
	}
	

}
