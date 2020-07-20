#include "Engine/Components/TextComponent.hpp"
#include "Engine/Components/TextRenderComponent.hpp"
#include "Engine/Entities/TextMenuEntity.hpp"

TextMenuEntity::TextMenuEntity(std::string text, int size) {
    this->addNode(new TextComponent(size, {0xFF, 0xFF, 0xFF}, "Fonts/Verdana.ttf", text));
    this->addNode(new TextRenderComponent());
}

void TextMenuEntity::render(SDL_Renderer& renderer) {
    TextComponent* textComponent = this->getNode<TextComponent>();
    TextRenderComponent* textRenderComponent = this->getNode<TextRenderComponent>();
    if(textComponent != nullptr && textRenderComponent != nullptr) {
        textRenderComponent->render(renderer, *textComponent);
    }
}

//void TextMenuEntity::onEntered() {
////    std::cout << "StartMenuEntity::onEntered" << std::endl;
//}
//
//void TextMenuEntity::onExited() {
//  //  std::cout << "StartMenuEntity::onExited" << std::endl;
//}
//
//void TextMenuEntity::onExecute() {
//    //std::cout << "StartMenuEntity::onExecute" << std::endl;
//}
