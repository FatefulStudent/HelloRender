#include "MeshComponent.h"

UMeshComponent::UMeshComponent(std::string&& InTexturePath, float InRadius)
    : TexturePath(InTexturePath), Radius(InRadius) 
{}
