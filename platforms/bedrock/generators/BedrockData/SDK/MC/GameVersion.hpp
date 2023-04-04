#pragma once
#include "HookAPI.h"


namespace MinecraftAPI {
	class GameVersion {
		static int* _major;
		static int* _minor;
		static int* _patch;
		static int* _revision;

	public:
		static int major() {
			if (_major != nullptr) {
				return *_major;
			}
			else {
				return -1;
			}
		};
		static int minor() {
			if (_major != nullptr) {
				return *_minor;
			}
			else {
				return -1;
			}
		};
		static int patch() {
			if (_major != nullptr) {
				return *_patch;
			}
			else {
				return -1;
			}
		};
		static int revision() {
			if (_major != nullptr) {
				return *_revision;
			}
			else {
				return -1;
			}
		};
	};
}
