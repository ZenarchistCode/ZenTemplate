This template file is a work-in-progress as I flesh out my "DayZ Modding for Dummies" guide.

It also includes some basic template files for setting up Workbench operations. 

Step-by-step instructions for setting up the Workbench are at the end of this file.

Check back every now and then for potential updates to this mod template as I make more tutorials.

Check my YouTube channel for the tutorials: https://www.youtube.com/@Zenarchist

And if you get value out of my content, please consider buying me a coffee - I sure need one.

https://buymeacoffee.com/zenarchist

---

INSTRUCTIONS:
To get the workbench working properly and understand how everything works, I recommend reading 
through these 2 official Bohemia wiki guides before following my video tutorials & steps below:

https://community.bistudio.com/wiki/DayZ:Modding_Basics
https://community.bistudio.com/wiki/DayZ:Workbench_Script_Debugging

Default DayZ Server Root Folder Location: 	C:\Program Files (x86)\Steam\steamapps\common\DayZServer
Default DayZ Game Root Folder Location: 	C:\Program Files (x86)\Steam\steamapps\common\DayZ
Default DayZ Tools Root Folder Location: 	C:\Program Files (x86)\Steam\steamapps\common\DayZ Tools

My Addon Builder List of Included Files:
*.emat;*.edds;*.ptc;*.c;*.imageset;*.layout;*.ogg;*.paa;*.fnt;*.tga;*.xml;*.csv;*.rvmat;*.map;*.html

PREPARATION (ONLY NEEDS TO BE DONE ONCE):
Step 1. Make sure your P: drive is mounted (run DayZ Tools)
Step 2. Run the Workbench and click Workbench -> Options -> Set your Source data directory to P:/
Step 3: Copy & paste the "mpmissions" folder from your "DayZServer" folder into your "DayZ" game's root folder
Step 4: Copy my "ZenTemplate" mod folder somewhere easy to find (but NOT in your P: drive - eg. keep it in Documents)
Step 5: Run the "RUN FIRST.bat" file in the #WORKBENCH Setup folder and follow the prompts. You can delete the RUN FIRST.bat file after.
Step 6: Cut & paste the P-drive folder contents onto your P: drive
Step 7: Cut & paste the Game_Root_Folder contents into your game directory and overwrite anything it says (eg. mpmissions folder)
Step 8: Run "@1-LinkScripts.bat" in your game root directory. This only needs to be done once - you can delete this batch file after if you want.
Step 9: You can delete the #WORKBENCH Setup folder out of your ZenTemplate folder now - you've set up the workbench successfully.

MOD SETUP:
Step 1: Clone the "ZenTemplate" folder onto your P: drive and rename the root folder to whatever mod name you want (eg. "MyFirstMod")
Step 2: Run the "RENAME.bat" file in the mod's root folder and enter your mod name - eg. "MyFirstMod" - to rename all the file paths
Step 3: Navigate to your DayZ game directory and run "@LinkMod.bat" - type in your mod name (eg. "MyFirstMod") - enables hot-loading
Step 4: Pack your mod to ensure everything works - run DayZ Tools -> Addon Builder:
  -> Source directory: P:\MyFirstMod
  -> Destination directory: P:\@PackedMods\@MyFirstMod\addons
  -> PACK
Step 5: To begin editing the mod in the Workbench, navigate to P: and run "@RunWorkbench.bat" - enter your mod name (eg. "MyFirstMod")
Step 6: To test your mod with hot-loading enabled, run "#run-server-debug_hotload" and then "#join-server-debug_hotload"
Step 7: To test your mod fully-packed in the .pbo, run the "_packed.bat" versions instead.

RECOMMENDED:
Create shortcuts to your DayZ root game folder AND DayZ client-side logs (C:\Users\YOUR_NAME\AppData\Local\DayZ) and put it in your P: drive for quick reference.
Create shortcuts to your #run batch files for the hot-loading/packed mod loading and also put them in your P: drive for quick reference.
Don't forget to check your client-side logs during testing as client-side errors can easily go unnoticed and cause issues for players down the line.
Also don't forget to periodically delete all your unneeded client-side and server-side logs - they can get quite hefty over time!