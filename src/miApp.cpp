#include <miApp.h>
#include <miPipelines.h>

void MyApp::createPipelines()
{
	auto rtPipeline = new Astra::RayTracingPipeline();
	rtPipeline->create(AstraDevice.getVkDevice(), { _rtDescSetLayout, _descSetLayout }, _alloc);
	auto rasterPipeline = new Astra::OffscreenRaster();
	rasterPipeline->create(AstraDevice.getVkDevice(), { _descSetLayout }, _renderer->getOffscreenRenderPass());
	auto wireframe = new WireframePipeline();
	wireframe->create(AstraDevice.getVkDevice(), { _descSetLayout }, _renderer->getOffscreenRenderPass());
	auto normal = new NormalPipeline();
	normal->create(AstraDevice.getVkDevice(), { _descSetLayout }, _renderer->getOffscreenRenderPass());
	_pipelines = { rtPipeline, rasterPipeline, wireframe, normal };
}

void MyApp::run()
{
	// inicio del bucle
	while (!Astra::Input.windowShouldClose()) {
		Astra::Input.pollEvents();
		// no queremos renderizar si está minimizada	
		if (isMinimized()) continue;

		// empieza el render
		auto cmdList = _renderer->beginFrame();
		// actualizar escena
		_scenes[_currentScene]->update(cmdList);
		// dibuja la escena

		if (_pipelines[_selectedPipeline]->doesRayTracing()) {
			_renderer->render(cmdList,
				_scenes[_currentScene], // escena actual
				_pipelines[_selectedPipeline], // pipeline seleccionado
				{ _rtDescSet, _descSet }, // descriptor sets, como es RT hacen falta ambos
				_gui // puntero a GUI si tenemos
			);
		}
		else {
			_renderer->render(cmdList,
				_scenes[_currentScene], // escena actual
				_pipelines[_selectedPipeline], // pipeline seleccionado
				{ _descSet }, // descriptor sets
				_gui // puntero a GUI si tenemos
			);
		}
		// termina el render
		_renderer->endFrame(cmdList);
	}
	destroy();
}
