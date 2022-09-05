
#pragma once
// Module that handles footsteps

using namespace std;
using namespace SKSE;
using namespace RE;

namespace Gts {
	template <class T>
	T* find_form(std::string_view lookup_id) {
		// From https://github.com/Exit-9B/MCM-Helper/blob/a39b292909923a75dbe79dc02eeda161763b312e/src/FormUtil.cpp
		std::string lookup_id_str(lookup_id);
		std::istringstream ss{ lookup_id_str };
		std::string plugin, id;

		std::getline(ss, plugin, '|');
		std::getline(ss, id);
		RE::FormID relativeID;
		std::istringstream{ id } >> std::hex >> relativeID;
		const auto dataHandler = RE::TESDataHandler::GetSingleton();
		return dataHandler ? dataHandler->LookupForm<T>(relativeID, plugin) : nullptr;
	}

	class Magic {
		public:
			virtual void OnStart();
			virtual void OnUpdate();
			virtual void OnFinish();

			virtual std::string GetName();

			void poll();

			Actor* GetTarget();
			Actor* GetCaster();

			ActiveEffect* GetActiveEffect();
			EffectSetting* GetBaseEffect();

			void Dispel();
			bool IsDualCasting();
			inline bool DualCasted() {
				return this->dual_casted;
			}
			inline bool HasDuration() {
				if (this->activeEffect) {
					if (this->activeEffect->spell) {
						// switch (this->activeEffect->spell->GetSpellType()) {
						// 	case  MagicSystem::SpellType::kEnchantment: {
						// 		return false;
						// 	}
						// }
						switch (this->activeEffect->spell->GetCastingType()) {
							case  MagicSystem::CastingType::kConstantEffect: {
								return false;
							}
						}
					}
				}
				if (this->effectSetting) {
					if (this->effectSetting->data.flags.all(EffectSetting::EffectSettingData::Flag::kNoDuration)) {
						return false;
					}
				}
				return true;
			}

			Magic(ActiveEffect* effect);

			inline bool IsFinished() {
				return this->state == State::CleanUp;
			}

		private:
			enum State {
				Init,
				Start,
				Update,
				Finish,
				CleanUp,
			};
			State state = State::Init;
			Actor* target = nullptr;
			Actor* caster = nullptr;
			ActiveEffect* activeEffect = nullptr;
			EffectSetting* effectSetting = nullptr;
			bool dual_casted = false;
	};

	class MagicManager {
		public:
			[[nodiscard]] static MagicManager& GetSingleton() noexcept;

			void Update();
			void ProcessActiveEffects(Actor* actor);
		private:
			std::map<ActiveEffect*, std::unique_ptr<Magic> > active_effects;
	};
}
