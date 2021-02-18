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
	import flash.events.Event;
	
	public class GuideSettingEvent extends Event
	{
		import com.adobe.indesign.HorizontalOrVertical;
		public static const CHANGE:String = "guidesetting";

		private var _orientation:HorizontalOrVertical;
		private var _coordinate:Number;
		
		public function GuideSettingEvent(type:String,
										  orientation:HorizontalOrVertical, coordinate:Number,
										  bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(type, bubbles, cancelable);
			_orientation = orientation;
			_coordinate = coordinate;
		}
		
		//getter function for orientation
		public function get orientation():HorizontalOrVertical
		{
			return _orientation;
		}
		
		//getter function for coordinate
		public function get coordinate():Number
		{
			return _coordinate;
		}
		
	}
}
