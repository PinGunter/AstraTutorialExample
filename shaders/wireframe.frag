#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_EXT_scalar_block_layout : enable
#extension GL_GOOGLE_include_directive : enable

#extension GL_EXT_shader_explicit_arithmetic_types_int64 : require

#include "../AstraEngine/AstraCore/shaders/wavefront.glsl"

layout(location = 0) in vec3 i_color;

layout(location = 0) out vec4 fragColor;

layout(push_constant) uniform _PushConstantRaster
{
  PushConstantRaster pcRaster;
};
void main()
{
	fragColor = vec4(pcRaster.wireR, pcRaster.wireG, pcRaster.wireB, 1.0f);
}