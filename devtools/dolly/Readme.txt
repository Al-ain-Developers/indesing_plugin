Dolly: An InDesign plug-in project generator
========================================

Dolly is a tool for generating Visual Studio and Xcode projects, with source,
for new InDesign, InCopy and InDesign Server plug-in projects.

1. Requirements
========================================

Java runtime 1.7 or later is required to run Dolly.

On Mac, the simplest method to get this installed is to install the latest
JDK from java.com.

2. How to run Dolly
========================================

Double clicking dolly.jar should launch Dolly with its user-interface.

You can also use the following command line:

java -jar <sdk>/devtools/dolly/dolly.jar

Note: it is possible to use Dolly without user-interface, by using
an XML input file. Consult the rest of this readme for details on 
the XML required.

3. Dolly XML input
========================================

The specification for the plug-in that you want to create is contained in an XML
document. The example  specification win-input.xml is intended for a Windows
platform, and the version mac-input.xml shows a  Mac equivalent. You should back
up these files and edit them, making them consistent with your local file
system. You may edit these files with your favorite text editor, or using
DollyXs' User Interface.

The XML specification's outermost element (Code) contains 18 attributes.
Note that the mac-project-dir and win-project-dir attributes must
be absolute paths for the current system. Therefore, on Mac they will be Unix
paths, and on Windows they will be Windows paths. These result in project files
being  created at those locations on your hard drive. All other attributes
containing paths can be either absolute  or relative to the corresponding
project-dir. These entries are taken literally, so be careful what you type.
Whatever you specify becomes part of  the project file settings.  The
platform file separator should be used in these cases. For example, you might
wish to place your source relative to your project.  You may use "..\..\source"
on Windows and  "../../source" on the Mac. Keep in mind that it's to your
advantage to use relative paths when you can. This makes your source tree
less system dependent.

Here are the attributes listed alphabetically, followed by short descriptions.

    author
        A string that identifies the author of
        this generated plug-in.

    long-name
        The full name of this plug-in.

    mac-debug-target-dir
        The project build the debug target to the
        specified directory.

    mac-id-header-dir
        Generated ID.h files are placed in this
        directory (if running on Mac),  and this path
        is added to the project's access path.

    mac-project-dir
        Absolute path to the directory to which the Mac
        project will be generated.

    mac-release-target-dir
        The project builds the release target to the
        specified directory.

    mac-sdk-dir
        The relative or absolute path to the InDesign
        SDK on the Mac. The Mac project file
        uses this path to locate InDesign APIs. The path
        cannot contain any space characters. Otherwise,
        your project created may fail to build.

    mac-source-dir
        Generated source files are placed in this
        directory (if running on Mac) and this path
        is incorporated into the Mac project file.

    mac-target-type
        Specifies the architecture type of
        Mac OS on which the plug-in can run.

    mac-specific-xcconfig-file
        Optional; a relative or absolute path
        to a shared xcconfig file which will be
        used instead of the generated file.

    mac-specific-debug-xcconfig-file
        Optional; a relative or absolute path
        to a shared debug xcconfig file which
        will be used instead of the generated file.

    mac-specific-xcconfig-file
        Optional; a relative or absolute path
        to a shared release xcconfig file which
        will be used instead of the generated file.

    plugin-type
        The plug-in type, either kUIPlugin or
        kModelPlugin.

    product-type
        The string that will be embedded in the fr
        file that identifies which products (InDesign,
        InCopy, InDesign Server, etc.) the plug-in
        loads under. When "kInDesignServerProduct"
        appears in the string, the  plug-in is built as a
        model-only plug-in.  On Windows, it does not
        link against WidgetBin and on the Mac it uses
        InDesignModel.framework.

    prefix-id
        Your plug-in's assigned prefix ID.

    short-name
        The short name of your plug-in. This is used
        in IDs and file names.

    win-debug-intermediate-dir
        The path to the directory to which object code
        and other intermediate files are built.

    win-debug-target-dir
        The project builds the debug target to the
        specified directory.

    win-id-header-dir
        Generated ID.h files are placed in this
        directory (if running on Windows),  and this path
        will be added to the project's rsp files.

    win-project-dir
        Absolute path to the directory to which the Mac
        project is generated.

    win-release-intermediate-dir
        The directory to which object code and other intermediate
        files from the release build re built.

    win-release-target-dir
        The project builds the release target to the
        specified directory.

    win-sdk-dir
        The relative or absolute path to the InDesign CS5
        SDK on Windows.  The Windows MSDEV project file
        uses this path to locate InDesign APIs.

    win-specific-cpp-rsp-file
        Optional; a relative or absolute path to a shared rsp that
        will be used instead of the generated cpp rsp file.

    win-specific-odfrc-rsp-file
        Optional; a relative or absolute path to a shared rsp which
        will be used instead of the generated odfrc rsp file.

    win-source-dir
        Generated source files are placed in this
        directory (if running on Windows) and this path is
        incorporated into the Windows project file.

Beyond the outermost element and its 18 attributes, you will see a number of
simple elements resulting in  the generation of various files. These are self-
explanatory, and result in the items necessary to build an InDesign plug-in.

    <vcxproj-file/>
    <vcxproj-filters-file/>
    <rsp-cpp-file/>
    <rsp-odfrc-file/>
    <xcodeproj-file/>
    <id-h-file/>
    <id-cpp-file/>
    <nostrip-file/>
    <triggerresourcedeps-file/>
    <factorylist-file/>
    <rc-file/>
    <fr-file/>
    <enus-fr-file/>
    <jajp-fr-file/>
    <generate-menu/>

There are some optional items, which are also self-explanatory. These items
correspond to the check boxes in the features panel of the User Interface.

    <generate-dialog/>
    <generate-panel/>
    <generate-scriptprovider/>
    <scriptingdefs-h-file/>

Finally, you may see (or even wish to add) elements of the type impl-item or
boss-item.

An impl-item is expanded to create an ID for your implementation, the actual cpp
file, and the factory list reference.  It may contain the following attributes:
    impl-file
        The actual xsl template used to  instantiate. Feel
        free to add your own implementation types.
    impl-id
        Your implementation ID (for example, kMySpecialImplementationID).
        This attribute is optional.  If you wish to generate an implementation
        without adding to the factorylist.h and id.h files, then omit the
        impl-id attribute.
   impl-name
        Your implementation's name (for example, MySpecialImplemenation).

A boss-item element is expanded to create an ID for your boss and the
appropriate entry in the  ClassDescriptionTable of your plug-in's .fr resource
file. Here is an example of a boss-item.

    <boss-item
        boss-id="kDollyScriptProviderBoss"
        boss-parent="kBaseScriptProviderBoss">
            <boss-impl-pair
                impl-id="kDollyScriptProviderImpl"
                    interface-id="IID_ISCRIPTPROVIDER"/>
    </boss-item>

The boss-item element contains the following attributes:
    boss-id
        The ClassID to use for this boss.
    boss-parent
        The ClassID of this boss's parent (or kInvalidClass).

The boss-item can also contain 0 or more boss-impl-pair elements. These
elements describe  the mapping between interface and implementation
ID, as you would in the .fr file.

The boss-impl-pair contains the following attributes:
    impl-id
        The implementation ID for this implementation.
    interface-id
        The interface ID for this implementation.

You can also produce an add-in boss by using the boss-addin element. It is syntactically
identical to the boss-item element, except that it produces an add-in. Here's an example:
    <boss-addin
        boss-id="kDocumentDefaultSuiteBoss">
            <boss-impl-pair impl-id="kDollySuiteDefaultsCSBImpl"
            interface-id="IID_IDOLLYSUITE" />
    </boss-addin>
