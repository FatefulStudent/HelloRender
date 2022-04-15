#include "TextureComponent.h"

UTextureComponent::UTextureComponent(std::string&& InPath,
                                     int InTextureUnitNumber,
                                     int InTextureWrappingS,
                                     int InTextureWrappingT,
                                     int InTextureMagFilter,
                                     int InTextureMinFilter)
    : Path(InPath),
      TextureUnitNumber(InTextureUnitNumber),
      TextureWrappingS(InTextureWrappingS),
      TextureWrappingT(InTextureWrappingT),
      TextureMagFilter(InTextureMagFilter),
      TextureMinFilter(InTextureMinFilter)
{}
