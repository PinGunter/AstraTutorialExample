#include "miPipelines.h"
#include <nvvk/pipeline_vk.hpp>
#include <nvh/fileoperations.hpp>
#include <host_device.h>
#include <nvpsystem.hpp>

void WireframePipeline::create(VkDevice vkdev, const std::vector<VkDescriptorSetLayout>& descsetsLayouts, VkRenderPass rp)
{
	std::vector<std::string> defaultSearchPaths = {
		NVPSystem::exePath() + PROJECT_RELDIRECTORY,
		NVPSystem::exePath() + PROJECT_RELDIRECTORY "..",
		std::string(PROJECT_NAME),
	};

	VkPushConstantRange pushConstantRanges = { VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(PushConstantRaster) };

	// Creating the Pipeline Layout
	VkPipelineLayoutCreateInfo createInfo{ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
	createInfo.setLayoutCount = static_cast<uint32_t>(descsetsLayouts.size());
	createInfo.pSetLayouts = descsetsLayouts.data();
	createInfo.pushConstantRangeCount = 1;
	createInfo.pPushConstantRanges = &pushConstantRanges;
	vkCreatePipelineLayout(vkdev, &createInfo, nullptr, &_layout);


	// Pipeline: completely generic, no vertices
	nvvk::GraphicsPipelineGeneratorCombined gpb(vkdev, _layout, rp);
	gpb.addShader(nvh::loadFile("spv/" + std::string(PROJECT_NAME) + "/wireframe.vert.spv", true, defaultSearchPaths, true), VK_SHADER_STAGE_VERTEX_BIT);
	gpb.addShader(nvh::loadFile("spv/" + std::string(PROJECT_NAME) + "/wireframe.frag.spv", true, defaultSearchPaths, true), VK_SHADER_STAGE_FRAGMENT_BIT);
	gpb.rasterizationState.cullMode = VK_CULL_MODE_NONE;
	gpb.rasterizationState.polygonMode = VK_POLYGON_MODE_LINE;
	gpb.addBindingDescription({ 0, sizeof(Vertex) });
	gpb.addAttributeDescriptions({
		{0, 0, VK_FORMAT_R32G32B32_SFLOAT, static_cast<uint32_t>(offsetof(Vertex, pos))},
		{1, 0, VK_FORMAT_R32G32B32_SFLOAT, static_cast<uint32_t>(offsetof(Vertex, color))}
		});
	_pipeline = gpb.createPipeline();
}

void NormalPipeline::create(VkDevice vkdev, const std::vector<VkDescriptorSetLayout>& descsetsLayouts, VkRenderPass rp)
{
	std::vector<std::string> defaultSearchPaths = {
	NVPSystem::exePath() + PROJECT_RELDIRECTORY,
	NVPSystem::exePath() + PROJECT_RELDIRECTORY "..",
	std::string(PROJECT_NAME),
	};

	VkPushConstantRange pushConstantRanges = { VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(PushConstantRaster) };

	// Creating the Pipeline Layout
	VkPipelineLayoutCreateInfo createInfo{ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
	createInfo.setLayoutCount = static_cast<uint32_t>(descsetsLayouts.size());
	createInfo.pSetLayouts = descsetsLayouts.data();
	createInfo.pushConstantRangeCount = 1;
	createInfo.pPushConstantRanges = &pushConstantRanges;
	vkCreatePipelineLayout(vkdev, &createInfo, nullptr, &_layout);


	// Pipeline: completely generic, no vertices
	nvvk::GraphicsPipelineGeneratorCombined gpb(vkdev, _layout, rp);
	gpb.addShader(nvh::loadFile("spv/" + std::string(PROJECT_NAME) + "/normal.vert.spv", true, defaultSearchPaths, true), VK_SHADER_STAGE_VERTEX_BIT);
	gpb.addShader(nvh::loadFile("spv/" + std::string(PROJECT_NAME) + "/normal.frag.spv", true, defaultSearchPaths, true), VK_SHADER_STAGE_FRAGMENT_BIT);
	gpb.rasterizationState.cullMode = VK_CULL_MODE_NONE;
	gpb.addBindingDescription({ 0, sizeof(Vertex) });
	gpb.addAttributeDescriptions({
		{0, 0, VK_FORMAT_R32G32B32_SFLOAT,static_cast<uint32_t>(offsetof(Vertex, pos))},
		{1, 0, VK_FORMAT_R32G32B32_SFLOAT,	static_cast<uint32_t>(offsetof(Vertex, nrm))} });
	_pipeline = gpb.createPipeline();

}
