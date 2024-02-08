#include "GraphicsAdapterVK.hpp"

#include <exception>
#include <memory>
#include <vector>
#include <string>

namespace Oak::Graphics::VK {
	struct PhysicalDeviceFeatureStructs {
		VkPhysicalDeviceMeshShaderFeaturesEXT meshShaderFeatures = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT
		};
		VkPhysicalDeviceAccelerationStructureFeaturesKHR accelStructFeatures = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR,
			.pNext = &meshShaderFeatures
		};
		VkPhysicalDeviceRayTracingPipelineFeaturesKHR raytracingFeatures = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR,
			.pNext = &accelStructFeatures
		};
		VkPhysicalDeviceVulkan12Features vulkan12Features = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
			.pNext = &raytracingFeatures
		};
		VkPhysicalDeviceVulkan11Features vulkan11Features = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES,
			.pNext = &vulkan12Features
		};
		VkPhysicalDeviceFeatures physicalDeviceFeatures = {};
	};

	struct PhysicalDevicePropertyStructs {
		VkPhysicalDeviceMeshShaderPropertiesEXT meshShaderProperties = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_EXT
		};
		VkPhysicalDeviceAccelerationStructurePropertiesKHR accelStructProperties = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR,
			.pNext = &meshShaderProperties
		};
		VkPhysicalDeviceRayTracingPipelinePropertiesKHR raytracingProperties = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR,
			.pNext = &accelStructProperties
		};
		VkPhysicalDeviceVulkan12Properties vulkan12Properties = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES,
			.pNext = &raytracingProperties
		};
		VkPhysicalDeviceVulkan11Properties vulkan11Properties = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES,
			.pNext = &vulkan12Properties
		};
		VkPhysicalDeviceProperties physicalDeviceProperties = {};
	};

	const std::vector<VkDeviceQueueCreateInfo> Adapter::CreateDeviceQueueCreateInfos() const {
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

		const float queuePriority = 1.0f;

		VkDeviceQueueCreateInfo graphicsQueueInfo = {
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.queueFamilyIndex = static_cast<uint32_t>(_queueIndices._graphics),
			.queueCount = 1,
			.pQueuePriorities = &queuePriority
		};

		queueCreateInfos.push_back(graphicsQueueInfo);

		if (_queueIndices._transfer != -1) {
			VkDeviceQueueCreateInfo transferQueueInfo = {
				.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
				.queueFamilyIndex = static_cast<uint32_t>(_queueIndices._transfer),
				.queueCount = 1,
				.pQueuePriorities = &queuePriority
			};

			queueCreateInfos.push_back(transferQueueInfo);
		}

		if (_queueIndices._compute != -1) {
			VkDeviceQueueCreateInfo computeQueueInfo = {
				.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
				.queueFamilyIndex = static_cast<uint32_t>(_queueIndices._compute),
				.queueCount = 1,
				.pQueuePriorities = &queuePriority
			};

			queueCreateInfos.push_back(computeQueueInfo);
		}

		return queueCreateInfos;
	}

	VkPhysicalDeviceFeatures2 Adapter::CreateExtensionNamesAndFeatureStructs(std::vector<const char*>& extensionNamesOut, std::vector<std::unique_ptr<VkBaseOutStructure>> featureStructsOut) const {
		/*VkPhysicalDeviceVulkan12Features* vulkan12Features = new VkPhysicalDeviceVulkan12Features();
		vulkan12Features->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
		vulkan12Features->drawIndirectCount = true;
		vulkan12Features->storageBuffer8BitAccess = true;
		vulkan12Features->uniformAndStorageBuffer8BitAccess = true;
		vulkan12Features->storagePushConstant8 = true;
		vulkan12Features->shaderFloat16 = true;
		vulkan12Features->shaderInt8 = true;
		vulkan12Features->descriptorIndexing = true;
		vulkan12Features->shaderInputAttachmentArrayDynamicIndexing = true;
		vulkan12Features->shaderSampledImageArrayNonUniformIndexing = true;
		vulkan12Features->descriptorBindingVariableDescriptorCount = true;
		vulkan12Features->runtimeDescriptorArray = true;
		vulkan12Features->timelineSemaphore = true;
		vulkan12Features->bufferDeviceAddress = true;

		VkPhysicalDeviceVulkan11Features* vulkan11Features = new VkPhysicalDeviceVulkan11Features();
		vulkan11Features->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
		vulkan11Features->pNext = vulkan12Features;
		vulkan11Features->storageBuffer16BitAccess = true;
		vulkan11Features->uniformAndStorageBuffer16BitAccess = true;
		vulkan11Features->storagePushConstant16 = true;
		vulkan11Features->storageInputOutput16 = true;
		vulkan11Features->shaderDrawParameters = true;

		VkPhysicalDeviceFeatures2 physicalDeviceFeatures = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
			.pNext = &vulkan11Features,
			.features = {
				.textureCompressionBC = true
			}
		};

		featureStructsOut.push_back(std::make_unique<VkBaseOutStructure>(vulkan11Features));
		featureStructsOut.push_back(std::make_unique<VkBaseOutStructure>(vulkan12Features));

		extensionNamesOut.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

		if (_optionalFeatures._meshShading) {
			extensionNamesOut.push_back(VK_EXT_MESH_SHADER_EXTENSION_NAME);
			
			VkPhysicalDeviceMeshShaderFeaturesEXT* meshShaderFeatures = new VkPhysicalDeviceMeshShaderFeaturesEXT();
			meshShaderFeatures->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT;
			meshShaderFeatures->pNext = featureStructsOut.end()->get();
			meshShaderFeatures->meshShader = true;
			meshShaderFeatures->taskShader = true;

			featureStructsOut.push_back(std::make_unique<VkBaseOutStructure>(meshShaderFeatures));
		}

		if (_optionalFeatures._rayTracing) {
			extensionNamesOut.push_back(VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME);
			extensionNamesOut.push_back(VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME);
			extensionNamesOut.push_back(VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME);

			VkPhysicalDeviceAccelerationStructureFeaturesKHR* accelStructFeatures = new VkPhysicalDeviceAccelerationStructureFeaturesKHR();
			accelStructFeatures->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
			accelStructFeatures->pNext = featureStructsOut.end()->get();
			accelStructFeatures->accelerationStructure = true;

			VkPhysicalDeviceRayTracingPipelineFeaturesKHR* rayTracingFeatures = new VkPhysicalDeviceRayTracingPipelineFeaturesKHR();
			rayTracingFeatures->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
			rayTracingFeatures->pNext = &accelStructFeatures;
			rayTracingFeatures->rayTracingPipelineTraceRaysIndirect = true;
			rayTracingFeatures->rayTracingPipeline = true;

			featureStructsOut.push_back(std::make_unique<VkBaseOutStructure>(accelStructFeatures));
			featureStructsOut.push_back(std::make_unique<VkBaseOutStructure>(rayTracingFeatures));
		}

		return physicalDeviceFeatures;*/

		return VkPhysicalDeviceFeatures2();
	}

	PhysicalDeviceFeatureStructs GetPhysicalDeviceFeatures(const VkPhysicalDevice vkPhysicalDevice) {
		PhysicalDeviceFeatureStructs physicalDeviceFeatureStructs = {};
		
		VkPhysicalDeviceFeatures2 vkPhysicalDeviceFeatures2 = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
			.pNext = &physicalDeviceFeatureStructs.vulkan11Features
		};
		vkGetPhysicalDeviceFeatures2(vkPhysicalDevice, &vkPhysicalDeviceFeatures2);

		physicalDeviceFeatureStructs.physicalDeviceFeatures = vkPhysicalDeviceFeatures2.features;

		return physicalDeviceFeatureStructs;
	}

	PhysicalDevicePropertyStructs GetPhysicalDeviceProperties(const VkPhysicalDevice vkPhysicalDevice) {
		PhysicalDevicePropertyStructs physicalDevicePropertyStructs = {};
		
		VkPhysicalDeviceProperties2 vkPhysicalDeviceProperties2 = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
			.pNext = &physicalDevicePropertyStructs.vulkan11Properties
		};
		vkGetPhysicalDeviceProperties2(vkPhysicalDevice, &vkPhysicalDeviceProperties2);

		physicalDevicePropertyStructs.physicalDeviceProperties = vkPhysicalDeviceProperties2.properties;

		return physicalDevicePropertyStructs;
	}

	void CheckRequiredFeatures(const vkb::PhysicalDevice& vkPhysicalDevice, const PhysicalDeviceFeatureStructs& physicalDeviceFeatures, const PhysicalDevicePropertyStructs& physicalDeviceProperties) {
		if (!vkPhysicalDevice.is_extension_present(VK_KHR_SWAPCHAIN_EXTENSION_NAME))
			throw std::runtime_error("Vulkan physical device missing swapchain support.");
		if (!physicalDeviceFeatures.physicalDeviceFeatures.textureCompressionBC)
			throw std::runtime_error("Vulkan physical device missing BC texture compression.");
		if (!physicalDeviceFeatures.vulkan12Features.bufferDeviceAddress)
			throw std::runtime_error("Vulkan physical device missing buffer device address.");
		if (!physicalDeviceFeatures.vulkan12Features.descriptorIndexing)
			throw std::runtime_error("Vulkan physical device missing descriptor indexing.");
		if (!physicalDeviceFeatures.vulkan12Features.shaderSampledImageArrayNonUniformIndexing)
			throw std::runtime_error("Vulkan physical device missing non-uniform sampled image array indexing.");
		if (physicalDeviceProperties.physicalDeviceProperties.limits.maxDescriptorSetSampledImages < UINT16_MAX)
			throw std::runtime_error("Vulkan physical device does not support adequate sampled image descriptors bound.");
	}

	Adapter* Adapter::Create(const vkb::Instance& vkInstance) {
		vkb::Result<vkb::PhysicalDevice> physicalDeviceResult = vkb::PhysicalDeviceSelector(vkInstance)
			.select_first_device_unconditionally(true)
			.defer_surface_initialization()
			.select();

		if (!physicalDeviceResult)
			throw std::runtime_error("Could not select a Vulkan physical device");

		vkb::PhysicalDevice& vkPhysicalDevice = physicalDeviceResult.value();
		const PhysicalDeviceFeatureStructs physicalDeviceFeatures = GetPhysicalDeviceFeatures(vkPhysicalDevice);
		const PhysicalDevicePropertyStructs physicalDeviceProperties = GetPhysicalDeviceProperties(vkPhysicalDevice);

		CheckRequiredFeatures(vkPhysicalDevice, physicalDeviceFeatures, physicalDeviceProperties);

		Adapter* graphicsAdapter = new Adapter();
		graphicsAdapter->_vkPhysicalDevice = vkPhysicalDevice.physical_device;
		graphicsAdapter->_info = {};

		return graphicsAdapter;
	}
}