#pragma once

#include <articuno/articuno.h>

namespace Gts {
	class Debug {
		public:
			[[nodiscard]] inline spdlog::level::level_enum GetLogLevel() const noexcept {
				return _logLevel;
			}

			[[nodiscard]] inline spdlog::level::level_enum GetFlushLevel() const noexcept {
				return _flushLevel;
			}

		private:
			articuno_serialize(_ar) {
				auto logLevel = spdlog::level::to_string_view(_logLevel);
				auto _flushLevel = spdlog::level::to_string_view(_flushLevel);
				ar <=> articuno::kv(logLevel, "logLevel");
				ar <=> articuno::kv(flushLevel, "flushLevel");
			}

			ArticunoDeserialize(ar /*unused*/) {
				*this = Debug();
				std::string log_level;
				std::string flush_level;
				if (ar <=> articuno::kv(logLevel, "logLevel")) {
					_logLevel = spdlog::level::from_str(logLevel);
				}
				if (ar <=> articuno::kv(flushLevel, "flushLevel")) {
					_flushLevel = spdlog::level::from_str(flushLevel);
				}
			}

			spdlog::level::level_enum log_level{spdlog::level::level_enum::info};
			spdlog::level::level_enum flush_level{spdlog::level::level_enum::trace};

			friend class articuno::access;
	};

	class Frame {
		public:
			[[nodiscard]] inline int GetInitDelay() const noexcept {
				return _initDelay;
			}

			[[nodiscard]] inline int GetStep() const noexcept {
				return _step;
			}

		private:
			articuno_serialize(_ar) {
				ar <=> articuno::kv(_initDelay, "initDelay");
				ar <=> articuno::kv(_step, "step");
			}

			ArticunoDeserialize(ar /*unused*/) {
				*this = Frame();
				int step;
				int init_delay;
				if (ar <=> articuno::kv(step, "step")) {
					_step = step;
				}
				if (ar <=> articuno::kv(initDelay, "initDelay")) {
					_initDelay = initDelay;
				}
			}

			int step = 0;
			int init_delay = 0;

			friend class articuno::access;
	};

	class Sound {
		public:
			[[nodiscard]] inline std::string GetLFootstepL() const noexcept {
				return _lFootstepL;
			}
			[[nodiscard]] inline std::string GetLFootstepR() const noexcept {
				return _lFootstepR;
			}

			[[nodiscard]] inline std::string GetLJumpLand() const noexcept {
				return _lJumpLand;
			}

			[[nodiscard]] inline std::string GetXLFootstepL() const noexcept {
				return _xlFootstepL;
			}
			[[nodiscard]] inline std::string GetXLFootstepR() const noexcept {
				return _xlFootstepR;
			}

			[[nodiscard]] inline std::string GetXLRumbleL() const noexcept {
				return _xlRumbleL;
			}
			[[nodiscard]] inline std::string GetXLRumbleR() const noexcept {
				return _xlRumbleR;
			}

			[[nodiscard]] inline std::string GetXLSprintL() const noexcept {
				return _xlSprintL;
			}
			[[nodiscard]] inline std::string GetXLSprintR() const noexcept {
				return _xlSprintR;
			}

			[[nodiscard]] inline std::string GetXXLFootstepL() const noexcept {
				return _xxlFootstepL;
			}
			[[nodiscard]] inline std::string GetXXLFootstepR() const noexcept {
				return _xxlFootstepR;
			}

		private:
			articuno_serde(_ar) {
				ar <=> articuno::kv(_lFootstepL, "lFootstepL");
				ar <=> articuno::kv(_lFootstepR, "lFootstepR");

				ar <=> articuno::kv(_lJumpLand, "lJumpLand");

				ar <=> articuno::kv(_xlFootstepL, "xlFootstepL");
				ar <=> articuno::kv(_xlFootstepR, "xlFootstepR");

				ar <=> articuno::kv(_xlRumbleL, "xlRumbleL");
				ar <=> articuno::kv(_xlRumbleR, "xlRumbleR");

				ar <=> articuno::kv(_xlSprintL, "xlSprintL");
				ar <=> articuno::kv(_xlSprintR, "xlSprintR");

				ar <=> articuno::kv(_xxlFootstepL, "xxlFootstepL");
				ar <=> articuno::kv(_xxlFootstepR, "xxlFootstepR");


			}

			std::string l_footstep_l;
			std::string l_footstep_r;

			std::string l_jump_land;

			std::string xl_footstep_l;
			std::string xl_footstep_r;

			std::string xl_rumble_l;
			std::string xl_rumble_r;

			std::string xl_sprint_l;
			std::string xl_sprint_r;

			std::string xxl_footstep_l;
			std::string xxl_footstep_r;



			friend class articuno::access;
	};

	class SpellEffects {
		public:
			[[nodiscard]] inline std::string GetSmallMassiveThreat() const noexcept {
				return _smallMassiveThreat;
			}

		private:
			articuno_serde(_ar) {
				ar <=> articuno::kv(_smallMassiveThreat, "smallMassiveThreat");
			}

			std::string small_massive_threat;

			friend class articuno::access;
	};

	class Explosions {
		public:
			[[nodiscard]] inline std::string GetFootstepExplosion() const noexcept {
				return _footstepExplosion;
			}

		private:
			articuno_serde(_ar) {
				ar <=> articuno::kv(_footstepExplosion, "footstepExplosion");
			}

			std::string footstep_explosion;

			friend class articuno::access;
	};

	class Perks {
		public:
			[[nodiscard]] inline std::string GetHHBonus() const noexcept {
				return _hhBonus;
			}

		private:
			articuno_serde(_ar) {
				ar <=> articuno::kv(_hhBonus, "hhBonus");
			}

			std::string hh_bonus;

			friend class articuno::access;
	};

	class Tremor {
		public:
			[[nodiscard]] inline std::string GetMethod() const noexcept {
				return _method;
			}
			[[nodiscard]] inline float GetHalfScale() const noexcept {
				return _halfScale;
			}
			[[nodiscard]] inline float GetPowerAtMin() const noexcept {
				return _powerAtMin;
			}
			[[nodiscard]] inline float GetPowerAtMax() const noexcept {
				return _powerAtMax;
			}
			[[nodiscard]] inline float GetMaxScale() const noexcept {
				return _maxScale;
			}
			[[nodiscard]] inline float GetMinScale() const noexcept {
				return _minScale;
			}

		private:
			articuno_serde(_ar) {
				ar <=> articuno::kv(_method, "method");
				ar <=> articuno::kv(_halfScale, "halfScale");
				ar <=> articuno::kv(_powerAtMin, "powerAtMin");
				ar <=> articuno::kv(_powerAtMax, "powerAtMax");
				ar <=> articuno::kv(_maxScale, "maxScale");
				ar <=> articuno::kv(_minScale, "minScale");
			}

			std::string method;
			float half_scale;
			float power_at_min;
			float power_at_max;
			float max_scale;
			float min_scale;

			friend class articuno::access;
	};

	class Config {
		public:
			[[nodiscard]] inline const Debug& GetDebug() const noexcept {
				return _debug;
			}

			[[nodiscard]] inline const Frame& GetFrame() const noexcept {
				return _frame;
			}

			[[nodiscard]] inline const Sound& GetSound() const noexcept {
				return _sound;
			}

			[[nodiscard]] inline const SpellEffects& GetSpellEffects() const noexcept {
				return _spellEffects;
			}

			[[nodiscard]] inline const Explosions& GetExplosions() const noexcept {
				return _explosions;
			}

			[[nodiscard]] inline const Perks& GetPerks() const noexcept {
				return _perks;
			}

			[[nodiscard]] inline const Tremor& GetTremor() const noexcept {
				return _tremor;
			}

			[[nodiscard]] static const Config& GetSingleton() noexcept;

		private:
			articuno_serde(_ar) {
				ar <=> articuno::kv(_debug, "debug");
				ar <=> articuno::kv(_frame, "frame");
				ar <=> articuno::kv(_sound, "sound");
				ar <=> articuno::kv(_spellEffects, "spellEffects");
				ar <=> articuno::kv(_explosions, "explosions");
				ar <=> articuno::kv(_perks, "perks");
				ar <=> articuno::kv(_tremor, "tremor");
			}

			Debug debug;
			Frame frame;
			Sound sound;
			SpellEffects spell_effects;
			Explosions explosions;
			Perks perks;
			Tremor tremor;

			friend class articuno::access;
	};
}
