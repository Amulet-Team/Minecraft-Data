#pragma once
#include "HookAPI.h"


namespace MinecraftAPI {
	class DataVersion {
		static enum ActorDigestFormat* _ActorDigestFormat;
		static enum BlendVersion* _BlendVersion;
		static enum LevelChunkFormat* _LevelChunkFormat;
		static enum StorageVersion* _StorageVersion;
		static enum SubChunkFormat* _SubChunkFormat;

	public:
		static int actorDigestFormat() {
			if (_ActorDigestFormat != nullptr) {
				return *_ActorDigestFormat;
			}
			else {
				return -1;
			}
		};
		static int blendVersion() {
			if (_BlendVersion != nullptr) {
				return *_BlendVersion;
			}
			else {
				return -1;
			}
		};
		static int levelChunkFormat() {
			if (_LevelChunkFormat != nullptr) {
				return *_LevelChunkFormat;
			}
			else {
				return -1;
			}
		};
		static int storageVersion() {
			if (_StorageVersion != nullptr) {
				return *_StorageVersion;
			}
			else {
				return -1;
			}
		};

		static int subChunkFormat() {
			if (_SubChunkFormat != nullptr) {
				return *_SubChunkFormat;
			}
			else {
				return -1;
			}
		};
	};
}
