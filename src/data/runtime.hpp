#pragma once
// Module that holds data that is loaded at runtime
// This includes various forms


using namespace std;
using namespace SKSE;
using namespace RE;

namespace Gts {
	class Runtime {
		public:
			[[nodiscard]] static Runtime& GetSingleton() noexcept;

			void Load();

			BGSSoundDescriptorForm* l_footstep_l = nullptr;
			BGSSoundDescriptorForm* l_footstep_r = nullptr;

			BGSSoundDescriptorForm* l_jump_land = nullptr;

			BGSSoundDescriptorForm* xl_footstep_l = nullptr;
			BGSSoundDescriptorForm* xl_footstep_r = nullptr;

			BGSSoundDescriptorForm* xl_rumble_l = nullptr;
			BGSSoundDescriptorForm* xl_rumble_r = nullptr;

			BGSSoundDescriptorForm* xl_sprint_l = nullptr;
			BGSSoundDescriptorForm* xl_sprint_r = nullptr;

			BGSSoundDescriptorForm* xxl_footstep_l = nullptr;
			BGSSoundDescriptorForm* xxl_footstep_r = nullptr;

			BGSSoundDescriptorForm* growth_sound = nullptr;

			EffectSetting* small_massive_threat = nullptr;

			EffectSetting* explosive_growth1 = nullptr;

			EffectSetting* explosive_growth2 = nullptr;

			EffectSetting* explosive_growth3 = nullptr;

			///Shrink Effects Start
			EffectSetting* shrink_pc_button = nullptr;
			EffectSetting* shrink_back = nullptr;
			EffectSetting* shrink_back_npc = nullptr;
			EffectSetting* shrink_spell = nullptr;
			EffectSetting* shrink_ally = nullptr;

			EffectSetting* shrink_enemy = nullptr;
			EffectSetting* shrink_enemy_aoe = nullptr;
			EffectSetting* shrink_enemy_aoe_mast = nullptr;
			EffectSetting* sword_enchant = nullptr;

			EffectSetting* shrink_to_nothing = nullptr;
			///End

			///Ally/Grow Spells
			EffectSetting* slow_growth = nullptr;
			EffectSetting* growth_spell = nullptr;
			EffectSetting* grow_pc_button = nullptr;

			EffectSetting* grow_ally = nullptr;
			EffectSetting* grow_ally_size_button = nullptr;
			EffectSetting* shrink_ally_size_button = nullptr;
			EffectSetting* ally_crush_growth = nullptr;
			EffectSetting* gts_mark_ally = nullptr;
			///end

			///Others
			EffectSetting* global_vore_growth = nullptr;

			EffectSetting* size_related_damage0 = nullptr;
			EffectSetting* size_related_damage1 = nullptr;
			EffectSetting* size_related_damage2 = nullptr;

			EffectSetting* absorb_mgef = nullptr;
			EffectSetting* true_absorb = nullptr;
			SpellItem * true_absorb_spell = nullptr;

			///End

			BGSExplosion* footstep_explosion = nullptr;

			BGSPerk* growth_on_hit_perk = nullptr;
			BGSPerk* hh_bonus = nullptr;
			BGSPerk* perk_part1 = nullptr;
			BGSPerk* perk_part2 = nullptr;
			BGSPerk* extra_growth = nullptr;
			BGSPerk* extra_growth_max = nullptr;

			TESGlobal * size_limit = nullptr;

			TESGlobal * gts_npc_effect_immunity_toggle = nullptr;

			TESGlobal * progression_multiplier = nullptr;
			TESGlobal * crush_growth_rate = nullptr;
			TESGlobal * chosen_game_mode = nullptr;
			TESGlobal * growth_mode_rate = nullptr;
			TESGlobal * shrink_mode_rate = nullptr;

			TESGlobal * chosen_game_mode_npc = nullptr;
			TESGlobal * growth_mode_rate_npc = nullptr;
			TESGlobal * shrink_mode_rate_npc = nullptr;

			TESGlobal * protect_essentials = nullptr;

			SpellItem * shrink_to_nothing_spell = nullptr;
			SpellItem * fake_crush_spell = nullptr;
			EffectSetting* fake_crush_effect = nullptr;

			MagicItem * shrink_back_npc_spell = nullptr;
			MagicItem * shrink_back_spell = nullptr;

	};
}
