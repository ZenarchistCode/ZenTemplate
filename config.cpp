/*
	© 2025 | ZenTemplate

	This mod is to be used as a template - replace this text with your own.
	Ctrl + F -> search for "ZenTemplate" -> replace with your mod folder name.

	[GENERAL MODDING INFO]

	Repair Kit Types
	    1: Weapon Cleaning Kit
	    2: Sewing Kit
	    3: Leather Sewing Kit
	    4: Whetstone
	    5: Duct Tape
	    6: Tire Repair Kit
	    7: Electronic Repair Kit
	    8: Epoxy Putty
		9: DOESN'T EXIT
		10: Blowtorch

		USAGE:
		repairableWithKits[] += {5};
		repairCosts[] += {20};

	Rotation Flags (rotationFlags=X)
	    ROTATE_Front		=	1
	    ROTATE_Top			=	2 
	    ROTATE_Left			=	4 
	    ROTATE_Right		=	8 
	    ROTATE_LeftRight	=	12 
	    ROTATE_Back			=	16
	    ROTATE_FrontBack	=	17 
	    ROTATE_Bottom		=	32 
	    ROTATE_BottomTop	=	34 
	    ROTATE_All			=	63 
	    ROTATE_Ignore		=	64

		USAGE: 
		rotationFlags=16;
*/

class CfgPatches
{
	class ZenTemplate
	{
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class ZenTemplate
	{
		dir = "ZenTemplate";
		name = "";
		author = "";
		credits = "";
		version = "1.0";
		type = "mod";
		//inputs = "ZenTemplate/data/inputs.xml";
		dependencies[] = 
		{ 
			"Game", 
			"World", 
			"Mission" 
		};
		class defs
		{
			class imageSets
			{
				files[] =
				{
					"ZenTemplate/data/gui/ZenTemplate.imageset"
				};
			};
			class gameScriptModule
			{
				files[] = 
				{
					"ZenTemplate/scripts/common",
					"ZenTemplate/scripts/3_game"
				};
			};
			class worldScriptModule
			{
				files[] = 
				{
					"ZenTemplate/scripts/common",
					"ZenTemplate/scripts/4_world"
				};
			};
			class missionScriptModule
			{
				files[] = 
				{
					"ZenTemplate/scripts/common",
					"ZenTemplate/scripts/5_mission"
				};
			};
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;

	// Define objects/items/clothing
	class OldPhoto : Inventory_Base
	{
		displayName = "$STR_CfgVehicles_ZenTemplate0";
		descriptionShort = "$STR_CfgVehicles_ZenTemplate1";
	};
};

// Weapon magazines
class CfgMagazines 
{
};

// Ballistic weapons
class CfgWeapons
{
};

// Ammo types/config
class CfgAmmo
{
	class DefaultAmmo;
};

// Attachment slot config
class CfgSlots
{
	//! Example slot
	class Slot_ZenExampleSlot
	{
		name = "ZenExampleSlot";
		displayName = "$STR_CfgVehicles_PurificationTablets0";
		description = "$STR_CfgVehicles_PurificationTablets1";
		ghostIcon = "missing"; // "set:ZenTemplate image:someimagename"
	};
};

class CfgNonAIVehicles
{
	class ProxyAttachment;

	// Define 3D attachment proxies
	class ProxyExampleItemProxy : ProxyAttachment
	{
		scope = 1;
		inventorySlot = "ExampleSlot";
		model = "\ZenTemplate\data\models\yourmodel\proxy\yourproxyfile.p3d";
	};
};

// Sound file config
class CfgSoundShaders
{
	class ZenTemplateBase_SoundShader
	{
		range=35;
	};

	class ZenTemplateExample_SoundShader : ZenTemplateBase_SoundShader
	{
		samples[]=
		{
			{
				"ZenTemplate\sounds\your_ogg_sound_file",
				1
			}
		};
		volume=0.5;
	};
};

// Sound play config
class CfgSoundSets
{
	class ZenTemplateBase_SoundSet
	{
		sound3DProcessingType="character3DProcessingType";
		distanceFilter="BaseCharacter_AttenuationFilter";
		volumeCurve="characterAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=0;
	};
	class ZenTemplateExample_SoundSet : ZenTemplateBase_SoundSet
	{
		soundShaders[]=
		{
			"ZenTemplateExample_SoundShader"
		};
	}
};