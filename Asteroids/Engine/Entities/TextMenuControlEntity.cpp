#include "Engine/Components/TextComponent.hpp"
//#include "Engine/Components/TextRenderComponent.hpp"
#include "Engine/Entities/TextMenuControlEntity.hpp"

TextMenuControlEntity::TextMenuControlEntity(std::string text, int size) {
//    this->addNode(new TextComponent(size, {0xFF, 0xFF, 0xFF}, "Verdana.ttf", text));
//    this->addNode(new TextRenderComponent());
}

void TextMenuControlEntity::render(SDL_Renderer& renderer) {
//    TextComponent* textComponent = this->getNode<TextComponent>();
//    TextRenderComponent* textRenderComponent = this->getNode<TextRenderComponent>();
//    if(textComponent != nullptr && textRenderComponent != nullptr) {
//        textRenderComponent->render(renderer, *textComponent);
//    }
}
