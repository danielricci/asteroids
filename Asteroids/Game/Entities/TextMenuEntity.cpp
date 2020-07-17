#include "Engine/Components/TextComponent.hpp"
#include "Engine/Components/TextRenderComponent.hpp"
#include "Game/Entities/TextMenuEntity.hpp"

TextMenuEntity::TextMenuEntity(std::string text) {
    this->addNode(new TextComponent(24, {0xFF, 0xFF, 0xFF}, "Fonts/Verdana.ttf", text));
    this->addNode(new TextRenderComponent());
}

void TextMenuEntity::render(SDL_Renderer& renderer) {
//    TextRenderComponent* textRenderComponent = this->getNode<TextRenderComponent>();
//    for(TextComponent* textComponent : this->getNodes<TextComponent>()) {
//        if(textComponent != nullptr) {
//            textRenderComponent->render(renderer, *textComponent);
//        }
//    }
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
