/*
ADOBE SYSTEMS INCORPORATED
Copyright 2012 Adobe Systems Incorporated
All Rights Reserved.

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
terms of the Adobe license agreement accompanying it.  If you have received this file from a 
source other than Adobe, then your use, modification, or distribution of it requires the prior 
written permission of Adobe.
*/
package com.adobe.indesign.layouthelper.event 
{
	import com.adobe.indesign.*;
	
	import flash.events.Event;
	
	public class ConstrainsChangeEvent extends Event
	{
		public static const CHANGE:String = "objectchange";
		private var _item:Object;
		private var _constrain:DimensionsConstraints;
		public function ConstrainsChangeEvent(type:String, item:Object, constrain:DimensionsConstraints, bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(type, bubbles, cancelable);
			_item = item;
			_constrain = constrain;
		}
		
		//getter function for item object
		public function get item():Object
		{
			return _item;
		}
		//getter function for policy
		public function get constrain():DimensionsConstraints
		{
			return _constrain;
		}
		
	}
}
