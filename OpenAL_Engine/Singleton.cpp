#include "Singleton.h"

namespace htAudio {
	const  int kMaxFinalizersSize = 256;
	static int gNumFinalizersSize = 0;
	static SingletonFinalizer::FinalizerFunc gFinalizers[kMaxFinalizersSize];

	void SingletonFinalizer::addFinalizer(FinalizerFunc func) {
		assert(gNumFinalizersSize < kMaxFinalizersSize);
		gFinalizers[gNumFinalizersSize++] = func;
	}

	void SingletonFinalizer::finalize() {
		for (int i = gNumFinalizersSize - 1; i >= 0; --i) {
			(*gFinalizers[i])();
		}
		gNumFinalizersSize = 0;
	}
}