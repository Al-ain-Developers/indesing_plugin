package com.adobe.idmltools
{
	import flash.filesystem.File;
	
	/**
	 * Given an extracted IDML file, this class
	 * will return specific files or directories.
	 */ 
	public class PackageXmlLocator
	{
		private var _expandedIdmlDir:File;
		
		public function PackageXmlLocator(expandedIdmlDir:File)
		{
			_expandedIdmlDir = expandedIdmlDir;
		}
		
		/**
		 * Returns an array contaning the spread files.
		 */ 
		public function getSpreadFiles():Array
		{
			var spreadDir:File = _expandedIdmlDir.resolvePath("Spreads");
			return spreadDir.getDirectoryListing();
		}
	}
}