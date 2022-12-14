#pragma once
#include "engine.h"

namespace SOCOM1 {

	class Offsets : public PS2
	{
	public:
		std::vector<int> OffsetArray = {
			0x5D708C, // gameEndAddr
			0x1F66F4, // forceMatch
			0x48D548, // PlayerPointer
			0x4D46A4, // entArray
			0x1E5AC0, // fog
			0x48CF60, // fps1
			0x48CF64  // fps2
		};

		std::vector<std::string> names = {
			"GameEndedAddress",
			"ForceStartMatch",
			"SEALPointer",
			"EntityArrayPointer",
			"FOG",
			"Framerate",
			"Framerate"
		};

		// Match
		int gameEndAddr = 0x5D708C;
		int forceMatch = 0x1F66F4;

		// Character
		int PlayerPointer = 0x48D548;
		int entArray = 0x4D46A4;

		// Environment
		int fog = 0x1E5AC0;
		int fps1 = 0x48CF60;
		int fps2 = 0x48CF64;

		// Auto Resolve List
	public:
		uintptr_t SEALPointer = GetClassPtr(PlayerPointer);
		uintptr_t EntityArray = GetAddr(entArray);
		uintptr_t GameEndAddress = GetAddr(gameEndAddr);
		uintptr_t FrameRate1 = GetAddr(fps1);
		uintptr_t FrameRate2 = GetAddr(fps2);

		//	Functions
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		//	OUTPUT
		// 0x00000000	0x00000000	:	<OffsetName>		// display like native PS2 Memory
		//NOTE: Ends with 2New Line
		std::string LogData()
		{

			char data[0x1024];
			const char* data2 = "%llX	0x%08X	:	%s\n";
			std::string result;
			for (int i = 0; i < OffsetArray.size(); i++) {
				sprintf_s(data, data2, GetAddr(OffsetArray[i]), PS2Read<int>(GetAddr(OffsetArray[i])), names[i].c_str());
				result += data;
			}
			return (result += "\n");
		}
	};

	class CCamera : public PS2 
	{
	
		//	OFFSETS
	public:
		char pad_0000[80];	//0x0000
		Vector3 Position;	//0x0050
		char pad_005C[132];	//0x005C

		//	FUNCTIONS
	public:	
		std::string LogData()
		{

		}
	};

	class CWeapon
	{

		/*
		
			- Core
			-- GiveAmmo
			-- GiveWeapon
			-- GetLoadoutData | Primary, Secondary, Equipment & Ammo

			- Systems
			-- Weapon Manager | Slot -> Type -> Weapon : Send
		
		*/

	public:
		enum WeaponSlot : unsigned int
		{
			Primary,	// = 0x60C,
			Secondary,	// = 0x610,
			EqSlot1,	// = 0x614,
			EqSlot2,	// = 0x618,
			EqSlot3,	// = 0x61C,
		};
		int e_selectedSlot = Primary;
		const char* AvailSlots[5] = { "Primary", "Secondary", "Equipment 1", "Equipment 2", "Equipment 3" };

		enum Primary : unsigned int
		{
			M4A1_SD = 0xCC3F80,
			AR_552 = 0xCC4550,
			SMG_9MM = 0x00CC61F0,
			abs1 = 0xCC6D90,
		};
		unsigned int e_selected_Primary = Primary::AR_552;
		const char* PrimaryWeapons[4] = { "M4A1 SD", "552", "9mm Sub", "abs" };

		enum Secondary : unsigned int
		{
			PISTOL_9MM = 0xCC2B60,
			_abs = 13402528,
			_abs2 = 13401072,
			_abs3 = 13395872,
			_abs4 = 13377488,
		};
		unsigned int e_selected_Secondary = Secondary::PISTOL_9MM;
		const char* SecondaryWeapons[5] = { "9MM Pistol", "abs", "abs2", "abs3", "abs4" };

		enum Equipment : unsigned int
		{
			Flashbang = 0x0,
		};
		unsigned int e_selected_Equipment = Equipment::Flashbang;
		const char* EquipmentWeapon[1] = { "Flashbang" };
	};

	class CPlayer : public PS2
	{
		// SUB CLASSES
	public:
		class CPlayerPhysics
		{
		public:
			char pad_0000[48];	//0x0000
			Vector3 absPosition;	//0x0030
			char pad_003C[348];	//0x003C

			//	FUNCTIONS
		public:

			std::string LogData()
			{
				return "";
			}

		};	//Size: 0x0198

		enum Teams : unsigned int
		{
			SEALS = 0x40000001,			//	Seal
			TERRORIST = 0x80000100,		//	Terrorist
			TURRET = 0x48000000,		//	Turret
			SPECTATOR = 0x00010000,		//	Spectator

			// CAMPAIGN
			SP_ABLE = 0x84000006,			//	Alpha Team
			SP_BRAVO = 0x8400000A,			//	Bravo Team
			SP_ENEMY_A = 0x40000050,		//	Iron Brother / Iron Leader
			SP_ENEMY_B = 0x40000100,		//	
			SP_ENEMY_C = 0x40000210,		//	
			SP_ENEMY_D = 0x40000410,		//	
			SP_ENEMY_E = 0x40000810,		//	
			SP_ENEMY_F = 0x40001010,		//	
			SP_ENEMY_G = 0x40002010,		//	
			SP_ENEMY_H = 0x40004010,		//	
			SP_ENEMY_I = 0x40021010,		//	
		};

		//	OFFSETS
	public:	// NATIVE OFFSETS (DO NOT DISRUPT)
		char pad_0000[20];				//0x0000
		int NamePTR;					//0x0014
		char pad_0018[4];				//0x0018
		Vector3 Position;				//0x001C
		CPlayerPhysics* CPlayerMovement;	//0x0028
		char pad_0030[148];				//0x0030
		int TeamID;						//0x00C4
		char pad_00C8[1348];			//0x00C8
		unsigned int PrimaryWeapon;		//0x060C
		unsigned int SecondaryWeapon;	//0x0610
		unsigned int EqSlot1;			//0x0614
		unsigned int EqSlot2;			//0x0618
		unsigned int EqSlot3;			//0x061C
		char pad_0620[220];				//0x0620
		int PrimaryMag[10];				//0x06FC
		int SecondaryMag[10];			//0x0724
		int EquipmentSlot1;				//0x074C
		char pad_0750[36];				//0x0750
		int EquipmentSlot2;				//0x0774
		char pad_0778[36];				//0x0778
		int EquipmentSlot3;				//0x079C
		char pad_07A0[1840];			//0x07A0
		float Health;					//0x0ED0



		//	FUNCTIONS
	public:

		/// <summary>
		/// Returns Class Pointer Status
		/// </summary>
		/// <returns>BOOL</returns>
		bool IsValid() 
		{
			return ((unsigned int)this->pad_0000 == 0x000000 || this->NamePTR == NULL || this->CPlayerMovement == nullptr || this->TeamID == NULL) ? FALSE : TRUE;
		}

		/// <summary>
		/// Returns Players Alive State
		/// </summary>
		/// <returns>BOOL</returns>
		bool IsAlive()
		{
			return (this->Health > 0.0f) ? TRUE : FALSE;
		}

		/// <summary>
		/// Returns a Pointer to CPlayerPhysics Class
		/// </summary>
		/// <returns>CPlayerPhysics*</returns>
		CPlayerPhysics* PlayerPhysicsPtr()
		{
			return (CPlayerPhysics*)((unsigned int)this->CPlayerMovement + BasePS2MemorySpace);
		}

		/// <summary>
		/// Returns Player Name
		/// </summary>
		/// <returns>std::string</returns>
		std::string GetPlayerName() 
		{
			return (char*)(NamePTR + BasePS2MemorySpace);
		}

		/// <summary>
		/// Returns Player Team Name
		/// </summary>
		/// <returns>std::string</returns>
		std::string GetTeamName() 
		{
			switch (this->TeamID)
			{
				case (SEALS):		return "SEAL";
				case (TERRORIST):	return "TERRORIST";
				case (SPECTATOR):	return "SPECTATOR";
				case (SP_ABLE):		return	"SEALS - ABLE Team";
				case (SP_BRAVO):	return	"SEALS - BRAVO Team";
				case (SP_ENEMY_A):	return	"Hostile";
				case (SP_ENEMY_B):	return	"Hostile";
				case (SP_ENEMY_C):	return	"Hostile";
				case (SP_ENEMY_D):	return	"Hostile";
				case (SP_ENEMY_E):	return	"Hostile";
				case (SP_ENEMY_F):	return	"Hostile";
				case (SP_ENEMY_G):	return	"Hostile";
				case (SP_ENEMY_H):	return	"Hostile";
				case (SP_ENEMY_I):	return	"Hostile";
			}
			return std::to_string(this->TeamID);
		}

		/// <summary>
		/// Returns Weapon Name
		/// </summary>
		/// <param name="Weapon"></param>
		/// <returns>std::string</returns>
		std::string GetWeaponName(unsigned int Weapon)
		{
			switch (Weapon)
			{
				case(CWeapon::AR_552): return "552";
				case(CWeapon::SMG_9MM): return "9MM SUB";
				case(CWeapon::PISTOL_9MM): return "9MM PISTOL";
			}

			char data[0x56];
			const char* data2 = "%08X";
			sprintf_s(data, data2, Weapon);
			return std::to_string(Weapon);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="amount"></param>
		/// <param name="mags"></param>
		void GiveAmmo(int amount, int mags = {})
		{
			if (mags <= NULL || mags > 10)
				mags = 3;

			for (int i = NULL; i < mags; i++)
			{
				this->PrimaryMag[i] = amount;
				this->SecondaryMag[i] = amount;
			}
			this->EquipmentSlot1 = NULL;
			this->EquipmentSlot2 = NULL;
			this->EquipmentSlot3 = NULL;
		}

		/// <summary>
		/// Replaces current weapon in slot with input Weapon
		/// </summary>
		/// <param name="Slot	: ">CWeapon::WeaponSlot</param>
		/// <param name="Weapon : ">CWeapon::Weapon</param>
		void GiveWeapon(unsigned int Slot, unsigned int Weapon)
		{
			// Intended usage
			switch (Slot)
			{
				case (CWeapon::WeaponSlot::Primary):		this->PrimaryWeapon		= Weapon;	break;
				case (CWeapon::WeaponSlot::Secondary):		this->SecondaryWeapon	= Weapon;	break;
				case (CWeapon::WeaponSlot::EqSlot1):		this->EqSlot1			= Weapon;	break;
				case (CWeapon::WeaponSlot::EqSlot2):		this->EqSlot2			= Weapon;	break;
				case (CWeapon::WeaponSlot::EqSlot3):		this->EqSlot3			= Weapon;	break;
			}
		}

		/// <summary>
		/// 
		/// </summary>
		void RemoveWeaponsandAmmo()
		{
			this->PrimaryWeapon = NULL;
			this->SecondaryWeapon = NULL;
			this->EqSlot1 = NULL;
			this->EqSlot2 = NULL;
			this->EqSlot3 = NULL;

			for (int i = NULL; i < 10; i++)
			{
				this->PrimaryMag[i] = NULL;
				this->SecondaryMag[i] = NULL;
			}
			this->EquipmentSlot1 = NULL;
			this->EquipmentSlot2 = NULL;
			this->EquipmentSlot3 = NULL;
		}

		/// <summary>
		/// Teleports this entity to desired position
		/// </summary>
		/// <param name="Pos"></param>
		void Teleport(Vector3 Pos)
		{
			unsigned int test = (unsigned int)this->CPlayerMovement;
			auto offset = (test + BasePS2MemorySpace);
			auto Movement = (CPlayerPhysics*)offset;
			Movement->absPosition = Pos;
		}

		/// <summary>
		/// generates a log containing important player data
		/// </summary>
		/// <returns>std::string</returns>
		/// NOTE: Ends with 2New Line
		std::string LogData()
		{
			Offsets offsets;
			auto SEAL = (CPlayer*)offsets.SEALPointer;
			float distance;
			if (SEAL != this)
				distance = GetDistanceTo3DObject(SEAL->Position, this->Position);
			else
				distance = 0.0f;

			char data[0x256];
			const char* data2 = "PlayerObjectBase: %llX\nPlayerName: %s\nTeamName: %s\nPrimary Weapon: %s	|	PrimaryAmmo: %i\nSecondary Weapon: %s	|	SecondaryAmmo: %i\nHealth: %0.f\nPosition: { %f, %f, %f }\nDistance: { %f }\n\n";
			sprintf_s(data, data2, this, this->GetPlayerName().c_str(), this->GetTeamName().c_str(),
				GetWeaponName(this->PrimaryWeapon).c_str(), this->PrimaryMag[0], 
				GetWeaponName(this->SecondaryWeapon).c_str(), this->SecondaryMag[0], 
				(this->Health * 100.f),
				this->Position.x, this->Position.y, this->Position.z, distance);
			return data;
		}

	};	//Size: 0x0ED4
	
	class MatchData : public PS2
	{
		/*
		* 
			- ForceHost
			- ForceStartMatch
			- ForceEndMatch
			- MatchNeverEnds
			- PlayerArray
			- GetLobbyInfo	| RoomName, MapName, Mode, #Players(Organized by team), Rounds Won/Current Round/Timer
		
		*/
		// NOTES
		// Host
		// - Force Start
		// - 
		// Match Info
		// - Map
		// - Round
		// - Time
		// - Players
		// - Score

		// SUB CLASSES
	public:

		//	OFFSETS
	public:

		//	FUNCTIONS
	public: 
		bool isMatchEnded()
		{
			Offsets offset;
			return (PS2Read<int>(offset.GameEndAddress) == NULL) ? TRUE : FALSE;
		}

		void ForceStartMatch()
		{	
			//
		}

		std::vector<CPlayer*> GetPlayers()
		{
			int count = NULL;
			Offsets offsets;
			std::vector<CPlayer*> ents{};

			//   Grab the first entityObjectPointer in the array
			auto entArray = offsets.EntityArray;
			if (entArray == NULL) return ents;

			//   Store base address for later because the entity array loops back to the beginning
			auto baseEntity = entArray;

			size_t maxSize = 0x64;
			for (int i = 0; i <= maxSize; i++)
			{
				//	Cast entity object to CPlayer Class
				CPlayer* ent = (CPlayer*)((*(int32_t*)(entArray + 0x8)) + BasePS2MemorySpace);
				if (ent == NULL)
					break;

				if (!ent->IsValid())
				{
					// Get next entity in the array
					entArray = *(int32_t*)entArray + BasePS2MemorySpace;
					continue;
				}

				//	Push CPlayer Object into the vector array
				ents.push_back(ent);

				// Get next entity in the array
				entArray = *(int32_t*)entArray + BasePS2MemorySpace;

				if (entArray == baseEntity)
					break;
			}
			
			//	return array of players
			return ents;
		}

		std::string LogData()
		{
			// Data
			// - Player Count
			// - Map Name
			// - Current Round
			// - Match Timer
			return "";
		}
	};
	
	/*
	//	Debug Weapon Manager
	//	Will not work in this scope!
	//	Does not work in current state, enum values need to be passed but instead is passing enum positions
	CWeapon WeaponData;
	void WeaponManager(CPlayer* player)
	{
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::TextCentered("[WEAPON MANAGER]", TRUE, ImColor(0, 255, 255, 200));
		ImGui::Separator();
		ImGui::SetNextItemWidth(100);
		ImGui::Combo("##jfhgjdflkhklsdh", (int*)&WeaponData.e_selectedSlot, WeaponData.AvailSlots, IM_ARRAYSIZE(WeaponData.AvailSlots));
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		switch (WeaponData.e_selectedSlot)
		{
			case(0): ImGui::Combo("##jfhgjdflkhklsdh1", (int*)&WeaponData.e_selected_Primary, WeaponData.PrimaryWeapons, IM_ARRAYSIZE(WeaponData.PrimaryWeapons)); break;
			case(1): ImGui::Combo("##kdgdsazhljfna", (int*)&WeaponData.e_selected_Secondary, WeaponData.SecondaryWeapons, IM_ARRAYSIZE(WeaponData.SecondaryWeapons)); break;
			case(2): ImGui::Combo("##zjdfhbadeh", (int*)&WeaponData.e_selected_Equipment, WeaponData.EquipmentWeapon, IM_ARRAYSIZE(WeaponData.EquipmentWeapon)); break;
			case(3): ImGui::Combo("##hsdfgjsytkiet", (int*)&WeaponData.e_selected_Equipment, WeaponData.EquipmentWeapon, IM_ARRAYSIZE(WeaponData.EquipmentWeapon)); break;
			case(4): ImGui::Combo("##gjnkdtoythmyuk", (int*)&WeaponData.e_selected_Equipment, WeaponData.EquipmentWeapon, IM_ARRAYSIZE(WeaponData.EquipmentWeapon)); break;
		}
		if (ImGui::Button("GIVE WEAPON", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
		{
			switch (WeaponData.e_selectedSlot)
			{
				case 0:        player->GiveWeapon(WeaponData.e_selectedSlot, WeaponData.e_selected_Primary); break;
				case 1:        player->GiveWeapon(WeaponData.e_selectedSlot, WeaponData.e_selected_Secondary); break;
				case 2:        player->GiveWeapon(WeaponData.e_selectedSlot, WeaponData.e_selected_Equipment); break;
				case 3:        player->GiveWeapon(WeaponData.e_selectedSlot, WeaponData.e_selected_Equipment); break;
				case 4:        player->GiveWeapon(WeaponData.e_selectedSlot, WeaponData.e_selected_Equipment); break;
			}
		}
	}

	void test_debug_menu()
	{
		SOCOM1::Offsets offsets;
		SOCOM1::CPlayer* PLAYER = (CPlayer*)offsets.SEALPointer;
		SOCOM1::MatchData MATCH;

		if (ImGui::Button("Test Read Memory", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			auto address = offsets.FrameRate1;

			auto value = g_Engine->PS2Read<int>(offsets.FrameRate1);

			g_Console->printdbg("Test Read Memory:\nFrameRate1: [%08X]\nVALUE: [%i]\n\n", Console::Colors::blue, address, value);
		}

		if (ImGui::Button("Test Write Memory", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			g_Engine->PS2Write<int>(offsets.FrameRate1, 30);

			g_Engine->PS2Write<int>(offsets.FrameRate2, 30);

			g_Console->printdbg("Test Write Memory:\nFrameRate1: [%i]\nFrameRate2: [%i]\n\n", Console::Colors::blue, g_Engine->PS2Read<int>(offsets.FrameRate1), g_Engine->PS2Read<int>(offsets.FrameRate2));

		}

		if (ImGui::Button("Test ResolvePointer", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			if (PLAYER->IsValid()) {

				CPlayer::CPlayerPhysics* move = PLAYER->PlayerPhysicsPtr();

				g_Console->printdbg("%s", Console::Colors::DEFAULT, PLAYER->LogData().c_str());
			}
			else
				g_Console->printdbg("[!] INVALID PLAYER OBJECT\n", Console::Colors::red);
		}

		if (ImGui::Button("Display Offsets Data", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
			g_Console->printdbg("Dumping Offset Data:\n%s", Console::Colors::DEFAULT, offsets.LogData().c_str());

		if (ImGui::Button("Check isValid", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			bool result = PLAYER->IsValid();

			switch (result) {

			case (TRUE):	g_Console->printdbg("isValid: [%i]\n", Console::Colors::yellow, result); break;

			case (FALSE):	g_Console->printdbg("isValid: [%i]\n", Console::Colors::red, result); break;
			}
		}

		if (ImGui::Button("Dump Player Data", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			if (PLAYER->IsValid())
				g_Console->printdbg("%s", Console::Colors::DEFAULT, PLAYER->LogData().c_str());
			else
				g_Console->printdbg("[!] INVALID PLAYER OBJECT\n", Console::Colors::red);
		}

		if (ImGui::Button("Give 552", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			if (PLAYER->IsValid()) {
				//player->PrimaryWeapon = CPlayer::CWeapon::AR_552;
				PLAYER->PrimaryWeapon = CWeapon::AR_552;
				for (int i = 0; i < 10; i++)
					PLAYER->PrimaryMag[i] = 1337;
			}
			else
				g_Console->printdbg("[!] INVALID PLAYER OBJECT\n", Console::Colors::red);
		}

		if (ImGui::Button("Dump Entity Array", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			std::vector<SOCOM1::CPlayer*> ent = MATCH.GetPlayers();

			if (!ent.empty()) {

				for (int i = 0; i < ent.size(); i++)
					g_Console->printdbg("%s", Console::Colors::DEFAULT, ent[i]->LogData().c_str());

			}

		}

		if (ImGui::Button("Telpeort All Entities", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			if (PLAYER->IsValid())
			{
				std::vector<SOCOM1::CPlayer*> ent = MATCH.GetPlayers();

				if (!ent.empty()) {

					for (int i = 0; i < ent.size(); i++) {

						float distance = PLAYER->GetDistanceTo3DObject(PLAYER->Position, ent[i]->Position);
						g_Console->printdbg("Teleporting Entity:\n- Name: %s\n - Position: { %0.2f, %0.2f, %0.2f }\n - Distance: %0.0fm\n\n", Console::Colors::DEFAULT, ent[i]->GetPlayerName().c_str(), ent[i]->Position.x, ent[i]->Position.y, ent[i]->Position.z, distance);
						ent[i]->Teleport(PLAYER->Position);
					}
				}
			}
		}

		if (ImGui::Button("Dump Match Data", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
			g_Console->printdbg("IsMatchEnded: [%i]\n\n", Console::Colors::yellow, MATCH.isMatchEnded());

		if (PLAYER->IsValid())
			WeaponManager(PLAYER);
	}
	*/
}