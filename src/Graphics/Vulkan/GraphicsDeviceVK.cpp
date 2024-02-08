#include "GraphicsDeviceVK.hpp"

namespace Oak::Graphics::VK {
	Device* Device::Create(const Adapter* const graphicsAdapter) {
		const float queuePriority = 1.0f;

		VkPhysicalDeviceMeshShaderFeaturesEXT meshShadingFeatures = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT,
			.taskShader = true,
			.meshShader = true
		};

		VkPhysicalDeviceVulkan12Features vulkan12Features = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
			.pNext = &meshShadingFeatures
		};

		VkPhysicalDeviceFeatures2 physicalDeviceFeatures2 = {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
			.pNext = &vulkan12Features,
			.features = {
				.textureCompressionBC = true
			}
		};

		VkDeviceQueueCreateInfo graphicsQueueInfo = {
			.queueFamilyIndex = 0,
			.queueCount = 1,
			.pQueuePriorities = &queuePriority
		};

		std::vector<const char*> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
		
		VkDeviceCreateInfo deviceInfo = {
			.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
			.pNext = &physicalDeviceFeatures2,

		};
		
		//vkCreateDevice(graphicsAdapter->_vkPhysicalDevice, )

		return nullptr;
	}
}