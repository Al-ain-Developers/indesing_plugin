CSXSDemo
--------

This sample demonstrates how to use CSXS events, sometimes called messages, to enable communication between CEP extensions and native InDesign plug-ins.

Building & installing
---------------------

This sample is composed of a plug-in and a CEP extension written in HTML and Javascript.

To use this sample, in addition to compiling and copying the plug-in in the same way as the other sample plug-ins, copy the CSXSDemoExtension directory to the CEP extensions directory:

System wide extensions directory:

- Win: C:\Program Files (x86)\Common Files\Adobe\CEP\extensions
- Mac: /Library/Application Support/Adobe/CEP/extensions

Per-user extensions directory:

- Win: C:\<username>\AppData\Roaming\Adobe\CEP\extensions
- Mac: ~/Library/Application Support/Adobe/CEP/extensions

Since the CSXSDemoExtension is unsigned, PlayerDebugMode must be enabled to use it:

- Win: regedit > HKEY_CURRENT_USER/Software/Adobe/CSXS.6, then add a new entry PlayerDebugMode of type "string" with the value of "1".
- Mac: In the terminal, type: defaults write com.adobe.CSXS.6 PlayerDebugMode 1 (The plist is located at /Users/USERNAME/Library/Preferences/com.adobe.CSXS.6.plist).

Using the sample
----------------

1. Start InDesign and load the CEP extension by going to Window > Extensions > CSXSDemoExtension.
2. In the panel which loads, click the button to send a CSXS event from the CEP extension to the plug-in.
3. Upon receiving the event (or message), the plug-in will show an alert dialog containing the message it received.
4. Now create a new document with a text area and some text.
5. Use the select tool to select the text area (not the text itself).
6. Right click the text area and select 'Send to HTML extension'. This menu item is provided by the plug-in part of this sample and when clicked will send a CSXS event/messag from the plug-in to the HTML extension. When the HTML extension receives the message it will display the message in a Javascript alert dialog.