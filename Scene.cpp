#include "Scene.h"

Scene::Scene():renderer_(RenderType::New()),
			   window_(WindowType::New()),
			   interator_(InteractorType::New())
{
	window_->AddRenderer(renderer_);
	interator_->SetRenderWindow(window_);
}


Scene::~Scene()
{
}

Scene::RenderType Scene::GetRenderer() const {
	return renderer_;
}

Scene::WindowType Scene::GetWindow() const {
	return window_;
}

Scene::InteractorType Scene::GetInteractor() const {
	return interator_;
}