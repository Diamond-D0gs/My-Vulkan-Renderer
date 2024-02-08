#pragma once

#include "../GraphicsAdapter.hpp"

#include <volk.h>
#include <VkBootstrap.h>

#include <vector>

namespace Oak::Graphics::VK {
	class Instance;
	class Device;

	class Adapter : public Graphics::Adapter {
	protected:
		struct OptionalFeatures {
			bool _meshShading : 1;
			bool _rayTracing : 1;
		} _optionalFeatures;

		struct QueueIndices {
			int32_t _graphics;
			int32_t _transfer;
			int32_t _compute;
		} _queueIndices;

		struct MemoryProperties {
			struct MemoryEntry {
				int32_t _heapIndex;
				uint64_t _heapSize;
			} _local, _assetStaging, _cpuUpload;
		} _memoryProperties;

		VkPhysicalDevice _vkPhysicalDevice;

		Adapter() = default;

		const std::vector<VkDeviceQueueCreateInfo> CreateDeviceQueueCreateInfos() const;

		VkPhysicalDeviceFeatures2 CreateExtensionNamesAndFeatureStructs(std::vector<const char*>& extensionNamesOut, std::vector<std::unique_ptr<VkBaseOutStructure>> featureStructsOut) const;

		static Adapter* Create(const vkb::Instance& vkInstance);

	public:
		~Adapter() = default;

		friend Instance;
		friend Device;
	};
}
