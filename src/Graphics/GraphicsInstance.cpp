#include "GraphicsInstance.hpp"
#include "Vulkan/GraphicsInstanceVK.hpp"

namespace Oak::Graphics {
	const Instance* Instance::CreateGraphicsInstance() {
		return VK::Instance::CreateGraphicsInstance();
	}
}