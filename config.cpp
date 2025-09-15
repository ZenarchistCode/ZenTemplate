/*
	(c) 2025 | ZenTemplate

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

	Item Rotation Flags
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
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts",
			"DZ_Gear_Drinks",
			"DZ_Gear_Medical"
		};
	};
};

class CfgMods
{
	class ZenTemplate
	{
		author = "";
		type = "mod";
		inputs = "ZenTemplate/data/inputs.xml";
		class defs
		{
			class imageSets
			{
				files[] =
				{
					"ZenTemplate/data/gui/imagesets/zen_imageset.imageset"
				};
			};
			class gameScriptModule
			{
				value = "";
				files[] = 
				{ 
					"ZenTemplate/Scripts/3_Game",
					"ZenTemplate/Scripts/Common"
				};
			};
			class worldScriptModule
			{
				value = "";
				files[] = 
				{ 
					"ZenTemplate/Scripts/4_World",
					"ZenTemplate/Scripts/Common"
				};
			};
			class missionScriptModule
			{
				value = "";
				files[] = 
				{ 
					"ZenTemplate/Scripts/5_Mission",
					"ZenTemplate/Scripts/Common"
				};
			};
		};
	};
};


class CfgVehicles
{
	// Required vanilla base classes
	class Inventory_Base;
	class Bottle_Base;
	class Edible_Base;

	class PurificationTablets: Edible_Base
	{
		// inventorySlot = define which attachments this item can go on.
		inventorySlot[] +=
		{
			"ZenExampleSlot"
		};
	};

	class Canteen: Bottle_Base
	{
		// attachments = define which items can attach onto this item.
		attachments[] +=
		{
			"ZenExampleSlot"
		};
		// Define the GUI attachment categories for this item
		class GUIInventoryAttachmentsProps
		{
			class ZenChlorineTablets
			{
				name="$STR_CfgVehicles_PurificationTablets0";
				description="";
				attachmentSlots[] =
				{
					"ZenExampleSlot"
				};
				icon="set:zen_template image:chlorine_tablets";
			};
		};
	};

	// Create a retextured canteen with all the same properties as vanilla
	// This item will also inherit all the attachment slots, so no need to redefine them.
	class Zen_Canteen_Black : Canteen
	{
		scope = 2;
		hiddenSelections[] =
		{
			"zbytek" // Find this texture selection via Mikero tools or vanilla cpp files
		};
		hiddenSelectionsTextures[] =
		{
			"ZenTemplate\data\textures\canteen\canteen_black_co.paa"
		};
	};
};

// Attachment slot config
class CfgSlots
{
	//! Example slot. Classname must be Slot_NameParameter. Then the slot is identified by name= parameter.
	class Slot_ZenExampleSlot
	{
		name = "ZenExampleSlot";
		displayName = "$STR_CfgVehicles_PurificationTablets0";
		ghostIcon = "set:zen_attachment_icons image:purification_tablets_upsidedown";
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

// Ammo config
class CfgAmmo
{
	class DefaultAmmo;
};

// Ammo types
class CfgAmmoTypes
{
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
				"ZenTemplate\data\sounds\your_ogg_sound_file",
				1
			}
		};
		volume=1.0;
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
		class NoiseAI
		{
			strength=200;
			type="sound";
		};
	};
};