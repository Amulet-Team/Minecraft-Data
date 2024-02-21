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
			if (_ActorDigestFormat) {
				return *_ActorDigestFormat;
			}
			else {
				return -1;
			}
		};
		static int blendVersion() {
			if (_BlendVersion) {
				return *_BlendVersion;
			}
			else {
				return -1;
			}
		};
		static int levelChunkFormat() {
			if (_LevelChunkFormat) {
				return *_LevelChunkFormat;
			}
			else {
				return -1;
			}
		};
		static int storageVersion() {
			if (_StorageVersion) {
				return *_StorageVersion;
			}
			else {
				return -1;
			}
		};

		static int subChunkFormat() {
			if (_SubChunkFormat) {
				return *_SubChunkFormat;
			}
			else {
				return -1;
			}
		};
	};
}
