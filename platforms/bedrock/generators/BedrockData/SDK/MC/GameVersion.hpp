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
			if (_major) {
				return *_major;
			}
			else {
				return -1;
			}
		};
		static int minor() {
			if (_major) {
				return *_minor;
			}
			else {
				return -1;
			}
		};
		static int patch() {
			if (_major) {
				return *_patch;
			}
			else {
				return -1;
			}
		};
		static int revision() {
			if (_major) {
				return *_revision;
			}
			else {
				return -1;
			}
		};
	};
}


enum VersionComparison {
	Equal = 1,
	Greater = 2,
	GreaterEqual = 3,
	Less = 4,
	LessEqual = 5
};

VersionComparison compareVersions(int v1[4], int v2[4]);
