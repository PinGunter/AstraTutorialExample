#include "miGui.h"
#include <glm/gtc/type_ptr.hpp>

void MyGui::draw(Astra::App* app)
{
	ImGui::Text("Select rendering pipeline");
	ImGui::RadioButton("RayTracing", &app->getSelectedPipelineRef(), 0);
	ImGui::RadioButton("Raster", &app->getSelectedPipelineRef(), 1);
	ImGui::RadioButton("Wireframe", &app->getSelectedPipelineRef(), 2);
	ImGui::RadioButton("Normal", &app->getSelectedPipelineRef(), 3);


	ImGui::Separator;
	ImGui::ColorPicker4("WireColor", glm::value_ptr(app->getRenderer()->wireColor));
}
