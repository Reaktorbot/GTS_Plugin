#pragma once
// Serde generalisation
//

namespace SKSE;

namespace Gts {
	class Serde {
		virtual void ser(SerializationInterface* serde, int version);
		virtual void de(SerializationInterface* serde, int version);
	}
}
