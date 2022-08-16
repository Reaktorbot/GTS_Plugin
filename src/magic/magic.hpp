
#pragma once
// Module that handles footsteps

using namespace std;
using namespace SKSE;
using namespace RE;

namespace Gts {
	template <class T>
	T* FindForm(std::string_view lookup_id) {
		// From https://github.com/Exit-9B/MCM-Helper/blob/a39b292909923a75dbe79dc02eeda161763b312e/src/FormUtil.cpp
		std::string lookup_id_str(lookup_id);
		std::istringstream ss{ lookup_id_str };
		std::string plugin, id;

		std::getline(ss, plugin, '|');
		std::getline(ss, id);
		RE::FormID relative_id;
		std::istringstream{ id } >> std::hex >> relativeID;
		const auto data_handler = RE::TESDataHandler::GetSingleton();
		return dataHandler ? dataHandler->LookupForm<T>(relativeID, plugin) : nullptr;
	}

	class Magic {
		public:
			virtual void OnStart();
			virtual void OnUpdate();
			virtual void OnFinish();

			void Poll();

			Actor* GetTarget();
			Actor* GetCaster();

			ActiveEffect* GetActiveEffect();
			EffectSetting* GetBaseEffect();

			void Dispel();
			bool IsDualCasting();
			inline bool DualCasted() const {
				return this->_dual_casted;
			}

			Magic(ActiveEffect* effect);

			inline bool IsFinished() {
				return this->_state == State::CleanUp;
			}

		private:
			enum State {
				Init,
				Start,
				Update,
				Finish,
				CleanUp,
			};
			State _state = State::Init;
			Actor* _target = nullptr;
			Actor* _caster = nullptr;
			ActiveEffect* _activeEffect = nullptr;
			EffectSetting* _effectSetting = nullptr;
			bool _dual_casted = false;
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
