Thu 02/16/2006 

3Dlabs Acuity Driver
====================


2D Driver Build 3.01.0852

(c) Copyright 3Dlabs Inc. Ltd. 2003. All rights reserved worldwide.


** TO VIEW THIS FILE CORRECTLY IN NOTEPAD, ENABLE "WORD WRAP" FROM THE FORMAT MENU **


The material in this document is the intellectual property of 3Dlabs Inc. Ltd. While every care has been taken in the preparation of this document, 3Dlabs accepts no liability for any consequences of its use.  Our products are under continual improvement and we reserve the right to change their specification without notice.

3Dlabs, and Wildcat are registered trademarks of 3Dlabs Ltd., 3Dlabs Inc. Ltd., or 3Dlabs Inc. in the United States and/or other countries. Microsoft Windows, Windows NT, Windows 2000 and Direct3D are either registered trademarks or trademarks of Microsoft Corp. in the United States and/or other countries. Intel and Pentium are registered trademarks of Intel Corporation. AMD, K6 and Athlon are registered trademarks of Advanced Micro Devices (AMD), Inc. OpenGL is a registered trademark of Silicon Graphics, Inc. All other trademarks are acknowledged and recognized.



Contents
========

1.......Introduction
2.......Prerequisites
3.......Downloading And Installing The Drivers
3.1.............Downloading The Drivers
3.2.............Installing The Card
3.3.............Installing The Drivers
4.......Uninstalling The Drivers
5.......The 3Dlabs Control Panel
5.1.............The Information Tab
5.2.............The Setup Tab
5.3.............The OpenGL Tab
5.4.............The Direct3D Tab
5.5.............The Advanced Tab
5.6.............The Monitor Tab
5.7.............Supported Languages
6.......The Taskbar Utility
7.......Acuity Window Manager ("WinMan")
8.......Driver Release History
9.......Known Anomalies
10......Application specific notes
11......Trouble Shooting
11.1............Monitor Fails to Synchronize Following Boot
11.2............Windows Only Boots Into VGA mode
11.3............I Can't Set My Monitor to a High Resolution
12......Customer Support



1. Introduction
===============
IMPORTANT
The 3Dlabs Wildcat VP drivers DO NOT SUPPORT the Wildcat4000, 4110, 4210, Wildcat II range(5000, 5110), Wildcat III range(6110, 6210) or Wildcat 4 range (7110, 7210) of adapters. Please refer to 3Dlabs website www.3dlabs.com for drivers for the above products.

This Readme describes the Wildcat VP drivers for the 3Dlabs Wildcat VP range of graphics adapters. Supported adapters are:

• Wildcat VP560
• Wildcat VP760
• Wildcat VP870
• Wildcat VP970
• Wildcat VP880 Pro
• Wildcat VP990 Pro

Once the driver has been installed the display driver release number can be determined by starting the Display Applet in the Control Panel folder. Press the "Advanced..." button, then Select the "3Dlabs" tab. The Driver version number can be found at the bottom of the Hardware Information section. The x.yy-zzzz code uniquely identifies the driver build.



2. Prerequisites
================

• Windows XP or Windows 2000 with Service Pack 2 or later.
• Supported CPUs: Intel Pentium II, III, 4 processors or later, INtel Xeon processors, AMD K6 and Athlon processors or later.



3. Downloading And Installing The Drivers
=========================================

3.1. Downloading The Drivers
============================

To download the drivers from the 3Dlabs website, go to the Drivers section of http://www.3dlabs.com and select the appropriate drivers for your card, then download the file into an appropriate scratch directory (e.g. C:\3dlabs).

3.2. Installing The Card
========================

To install your 3Dlabs graphics adapter:-

1.) Shutdown the computer and power-off.
2.) Insert the adapter, power-on and boot-up into Windows 2000 or Windows XP.

After logging-in the Hardware Wizard will appear. These drivers are provided with their own installer so you should hit the cancel button for any "Found New Hardware" dialogs that appear.

3.3. Installing The Drivers
===========================

Go to the directory where you downloaded the drivers and run the self installing .exe file that you downloaded. This launches the '3Dlabs Graphics Driver Setup' program, which will guide you through the process of installing your driver. The setup program will ask you for confirmation before installing any drivers. You should hit the "Yes" button each time.

Once setup has completed, you will need to reboot your system in order for the drivers to load.



4. Uninstalling The Drivers
===========================

You must have administrator privileges to uninstall these drivers:-

1.) Open the Add/Remove Programs icon in the Control Panel. 
2.) Highlight the "3Dlabs Acuity Driver" in the list and click "Change/Remove".
3.) Follow the instructions to complete the removal of the display driver and OpenGL driver. You will be required to reboot your system in order to complete the uninstall process.



5. The 3Dlabs Control Panel
===========================

To access the 3Dlabs Control Panel, launch the Display Properties Control Panel, select the "Settings" tab, click the "Advanced..." button and select the "3Dlabs" tab. This tab shows basic information for your adapter and its drivers including the chipset type, board name, amount of physical memory on the board, the RAMDAC type, BIOS version, and Driver version.

The driver version number is in the form x.yy-zzzz and uniquely identifies the driver build.

Hitting the "Advanced..." button on this page loads the 3Dlabs control panel. The 3Dlabs control panel is split into a number of pages as listed below. The pages are selected by clicking on one of the configuration tabs at the top right of the window.

NB. It is necessary to have administrator privileges to change any settings in the 3Dlabs control panel. If you do not have administrator privileges the options will be greyed out and cannot be changed.

The 3Dlabs tabs support Tool Tips help. To find out more about a particular option, hover your mouse over the relevant item and a help bubble will appear.

5.1. The Information Tab
========================

This page gives more detailed information on the OpenGL and DirectX drivers.

5.2 The Color Control Tab
=========================
This tab allows you to adjust the brightness, contrast and gamma correction of your display to compensate for different monitors and ambient lighting conditions.

5.3 The OpenGL Tab
==================
This tab allows you to tune the following parameters of your OpenGL driver setup:
• Full Scene Antialiasing
• Buffer Swap Mode
• Z Buffer Depth
• Texture Color Depth
• Overlay/Alpha
• Texture Filtering
• Wait for Vertical Synch
• Enable Stereo OpenGL
Hover the mouse over each item to learn more about the settings using the Tool Tips Help.

Optimized Applications
~~~~~~~~~~~~~~~~~~~~~~
Allows you to choose which OpenGL application the driver is presently optimized to run. Use the pull down menu to optimize the driver configuration for a different application, or select "OpenGL(tm)Default" for a good all round setting.

You can create your own optimized setting. To do this:
1.) Choose a setting for an application which is similar to the one you want.
2.) Click the "Create Copy" button to create a copy and rename it in the pull down menu window.
3.) Change the settings as appropriate.
4.) Click the "Save" button.
You can also delete your own customized settings (but not those that come preset in the driver).

Dual Monitor OpenGL Options
~~~~~~~~~~~~~~~~~~~~~~~~~~~
If you have two monitors attached to your 3Dlabs card, then by default OpenGL will only be accelerated on the first monitor. Clicking on the "Dual Monitor OpenGL Options" button will bring up an additional page which enables you to accelerate OpenGl applications seamlessly across both monitors. To do this:
1.) Check the "Enable Dual Monitor OpenGL" box.
2.) Select a monitor resolution and color depth from the box at the bottom right.
3.) Check the Genlocked box if you wish to have both monitors refresh at the same rate and time.
4.) Finally choose a refresh rate for each monitor (one will be greyed out if you choose to genlock the displays.
5.) Hit Apply

Wait for Vertical Synch
~~~~~~~~~~~~~~~~~~~~~~~
Smooth animation of 3D applications can be achieved by rendering to an off-screen color buffer and copying or swapping the contents to the displayable front buffer at the completion of each frame. Enabling this option prevents tearing of the display (often visible as flickering horizontal lines), by synchronizing the swap of the back and front buffers to the vertical blank retrace interval of the monitor display.

5.4 The Direct3D Tab
====================
This tab allows you to tune the following parameters of your Direct3D driver setup:
• Full Scene Antialiasing
• Force Z Buffer Depth
• Wait for Vertical Synch
Hover the mouse over each item to learn more about the settings using the Tool Tips Help.

Optimized Applications
~~~~~~~~~~~~~~~~~~~~~~
Allows you to choose which Direct3D application the driver is presently optimized to run. Use the pull down menu to optimize the driver configuration for a different application, or select "Direct3D Default" for a good all round setting.

You can create your own optimized setting. To do this:
1.) Choose a setting for an application which is similar to the one you want.
2.) Click the "Create Copy" button to create a copy and rename it in the pull down menu window.
3.) Change the settings as appropriate.
4.) Click the "Save" button.
You can also delete your own customized settings (but not those that come preset in the driver).

Wait for Vertical Synch
~~~~~~~~~~~~~~~~~~~~~~~
Smooth animation of 3D applications can be achieved by rendering to an off-screen color buffer and copying or swapping the contents to the displayable front buffer at the completion of each frame. Enabling this option prevents tearing of the display (often visible as flickering horizontal lines), by synchronizing the swap of the back and front buffers to the vertical blank retrace interval of the monitor display.

5.5 The Advanced Tab
====================

Enable Taskbar Shortcut
~~~~~~~~~~~~~~~~~~~~~~~
Allows you to enable and disable the taskbar application which provides quick access to main features of the control panel. When the taskbar application is enabled it will be placed on the taskbar (system tray) each time the system is booted. Disabling the taskbar application from the setup page means that the application will not appear each time you reboot. 

Pipeline Optimizations
~~~~~~~~~~~~~~~~~~~~~~
Enables you to optimize your graphics adapter for maximum geoemetry throughput (ideal for CAD/CAM applications), or texture fill rate (ideal for games and texture intensive modelling applications). This setting affects applications using either the OpenGL or DirectX APIs.

5.6 The Monitor Tab
===================

This page allows you to specify your monitor type and display the available settings but does not permit actual selection of different monitor modes. To do that you should click on the "Settings" tab at the top of the Display panel. Windows 2000 has good monitor support, so the 3Dlabs Monitor tab should only be used for trouble-shooting monitor problems.

Clone this monitor
~~~~~~~~~~~~~~~~~~
This option allows you to display a single desktop on two separate monitors.  

Redetect
~~~~~~~~
When the display panel is started it automatically looks to see if a DDC type monitor is connected; in which case it will display the available modes. However, it is possible for the panel to get out of `sync` E.g. if the monitor is hot swapped. This option allows you to manually specify that the panel should look for a DDC monitor again.

Type
~~~~
This pull down menu allows you to specify the monitor type, overriding the detected type if required. VESA should be selected if the monitor type is non-DDC and is not a "Specific Type" shown in the list that is displayed bottom left with you select "Specific Type".

If you wish to change the monitor to a higher resolution than allowed when it is configured for DDC, select VESA then reboot. When the system restarts you will be able to select much higher monitor resolutions. Beware though that doing this could cause damage to your monitor - 3Dlabs does not recommend this practice nor accept responsibility for the consequences of using this option.

Extra Modes
~~~~~~~~~~~
Some older monitors do not report all the modes they support when DDC is selected. This menu item allows the driver to interpolate additional modes for these monitors.


5.7 Supported Languages
=======================

The 3Dlabs control panel supports the following languages: -

Chinese (Simplified)
Chinese (Traditional)
Dutch
English
French
German
Italian
Japanese
Korean
Spanish



6. The Taskbar Utility
======================

The task bar utility provides quick access to some of the facilities on the control panel. To access the application right click on the 3Dlabs icon in the taskbar. Full documentation is provided through the "Help" item on the pop-up menu.


7. Acuity Window Manager ("WinMan")
===================================
The Acuity Window Manager, WinMan for short, is a tool that provides extra windowing and desktop features that are of particular use in multi-monitor configurations. 

For example, WinMan can control the positioning of dialog boxes : a useful feature because their default positions are generally inconsistent, which can become annoying on multi-monitor systems. 
Another example : WinMan will also let you partition your desktop into any number of 'virtual' desktops; useful for users who keep a large number of applications open at once.

WinMan may be configured and enabled from either the wizard that appears after driver installation, or from the popup menu of the Taskbar Utility described above.



8. Driver Release History
=========================

Current Release
===============

• Fix for rendering issue seen in Unigraphics NX
• Fix for border size issue seen in Internet Explorer
• Fix for monitor detection issue
• Various fixes for issues seen with Maya 6

3.01-0739
=========

• Added SketchUp optimised application setting
• Fix for crash seen in Pro Engineer Wildfire
• Various WinMan fixes
• Fix allowing negative syncs to be specified in specific monitor data
• Fix for vertical lines disappearing when zooming in P-CAD
• Fix for clipping problem in off-screen bitmaps
• Fix for memory leak seen with Adobe After Effects


9. Application specific notes
=============================

3ds max
~~~~~~~
We recommend that for best results you select the OpenGL renderer for the 3ds max 4.x versions, and the Direct3D renderer for 3ds max 5.x and later.

Aliens vs. Predator2
~~~~~~~~~~~~~~~~~~~~
There is a problem with the grenade launcher target when out of ammunition. To workaround this problem
please run the game at 16bpp.

Half-Life
~~~~~~~~~
You will need to download the patch for at least version 1.0.0.8 from www.sierra.com to use hardware
accelerated OpenGL. Without this patch some elements are rendered without textures.



1. Trouble Shooting
===================

10.1. Monitor Fails to Synchronize Following Boot
================================================

Your display mode is probably too high a resolution. Reboot the system and at the DOS "OS loader screen" hit <F8> and select the "Safe Mode" boot option. Using the display properties applet set the display to 640x480x8bpp and the monitor to 60Hz refresh. Reboot again and set the monitor to the desired mode (obviously, lower than the mode causing the problems!)

10.2. Windows Only Boots Into VGA mode
======================================

You may have incorrectly installed the drivers. Try reinstalling the drivers, if the problem persists, look on the 3dlabs website for a driver upgrade.

10.3. I Can't Set My Monitor to a High Resolution
================================================
You may be using an older monitor which supports DDC but doesn't report all the modes that the monitor is capable of. You need to force the drivers to use the VESA monitor modes (see section 5.4 The Monitor Page).


11. Customer Support
====================
You can contact 3Dlab's technical support via http://www.3dlabs.com/support/contact/