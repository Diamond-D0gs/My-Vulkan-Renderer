#include "GraphicsAdapterVK.hpp"

#include <exception>
#include <vector>
#include <string>

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

const GraphicsAdapterVK* GraphicsAdapterVK::Create(const vkb::Instance& vkInstance) {
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

	GraphicsAdapterVK* graphicsAdapter = new GraphicsAdapterVK();
	graphicsAdapter->_vkPhysicalDevice = vkPhysicalDevice;
	graphicsAdapter->_info = {};

	return graphicsAdapter;
}