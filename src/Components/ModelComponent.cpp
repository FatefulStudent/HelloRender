#include "ModelComponent.h"

UModelComponent::UModelComponent(const std::string& InPath) 
	: Path(InPath) {
    ComponentClass = EComponentClass::UModelComponent;
}
