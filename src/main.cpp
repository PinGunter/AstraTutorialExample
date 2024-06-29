#include <miApp.h>
#include <Utils.h>
#include <glm/ext/matrix_transform.hpp>
#include <miGui.h>

int main(int argc, char** argv)
{
	// Device Initialization
	Astra::DeviceCreateInfo createInfo{};
	AstraDevice.initDevice(createInfo);

	// App creation
	MyApp app;

	// Renderer
	Astra::Renderer* renderer = new Astra::Renderer();

	// Scene
	Astra::SceneRT* scene = new Astra::SceneRT();

	Astra::Camera cam;
	Astra::CameraController* camera = new Astra::OrbitCameraController(cam);

	Astra::Light* sun = new Astra::DirectionalLight(glm::vec3(1.0f), .6f, glm::vec3(1.0f));

	// Setup camera
	camera->setLookAt(glm::vec3(-2, 1, 2), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	scene->setCamera(camera);

	scene->addLight(sun);

	scene->loadModel("assets/aguacate.obj", glm::scale(glm::mat4(1.0f), glm::vec3(2.0f)));
	scene->loadModel("assets/espejo.obj", glm::translate(glm::rotate(glm::mat4(1.0f), 0.3f, glm::vec3(0, 1, 0)), glm::vec3(4, 0, -4)));
	scene->loadModel("assets/plane.obj");

	MyGui gui;
	try
	{
		app.init({ scene }, renderer, &gui);
		app.run();
	}
	catch (const std::exception& exc)
	{
		app.destroy();
		Astra::Log("Exception ocurred: " + std::string(exc.what()), Astra::LOG_LEVELS::ERR);
	}


	// destrucción de recursos
	AstraDevice.destroy();

	delete camera;
	delete renderer;
	delete scene;
	delete sun;
}