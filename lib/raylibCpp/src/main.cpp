/*
** EPITECH PROJECT, 2021
** IndieStudio
** File description:
** Main Test
*/

#include "raylib.hpp"

static void moveCamera(std::shared_ptr<IInput> input, MyVector3 *camPos, std::shared_ptr<ICamera> camera)
{
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_DOWN)) {
        camPos->b -= 1.0f;
        camera->setPosition(*camPos);
    }
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_UP)) {
        camPos->b += 1.0f;
        camera->setPosition(*camPos);
    }
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_LEFT)) {
        camPos->a -= 1.0f;
        camera->setPosition(*camPos);
    }
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_RIGHT)) {
        camPos->a += 1.0f;
        camera->setPosition(*camPos);
    }
}

static void changeScreenSize(std::shared_ptr<IInput> input, MyVector2 *windowSize, std::shared_ptr<IWindow> window)
{
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_Z)) {
        windowSize->a += 100;
        windowSize->b += 100;
        window->setSize(*windowSize);
        window->setColor(raylib::RColor::RBLUE);
    }
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_A)) {
        windowSize->a -= 100;
        windowSize->b -= 100;
        window->setSize(*windowSize);
        window->setColor(raylib::RColor::RRED);
    }
}

static void drawCube(std::shared_ptr<ISolid> cube, MyVector3 cubePos)
{
    cube->setColor(raylib::RColor::RLIGHTGRAY);
    cube->setPosition(cubePos);
    cube->draw();
    cube->setColor(raylib::RColor::RGRAY);
    cubePos.a += 2.0f;
    cube->setPosition(cubePos);
    cube->draw();
    cubePos.a -= 4.0f;
    cube->setPosition(cubePos);
    cube->draw();
}

static void manageCubeTexture(std::shared_ptr<IInput> input, std::shared_ptr<ISolid> cube, std::shared_ptr<ITexture> texture)
{
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_Q))
        cube->setTexture(texture);
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_S))
        cube->setTexture(nullptr);
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_W))
        texture->setPath("../../../Asset/Texture/Desert/Ground/Sand.png");
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_X))
        texture->setPath("../../../Asset/Texture/Nether/Ground/Netherrack.png");
}

static void manageMusic(std::shared_ptr<IInput> input, std::shared_ptr<IAudio> music)
{
    static float pitch = 1.0f;

    if (input->isKeyPressed(raylib::KeyBoard::IKEY_E))
        music->play();
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_R))
        music->stop();
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_T))
        music->pause();
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_Y))
        music->resume();
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_D)) {
        pitch -= 0.01f;
        music->setPitch(pitch);
    }
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_F)) {
        pitch += 0.01f;
        music->setPitch(pitch);
    }
}

static void manageSound(std::shared_ptr<IInput> input, std::shared_ptr<IAudio> sound)
{
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_G)) {
        sound->setPath("../../../Asset/Sound/ButtonClick.ogg");
        sound->play();
    }
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_H)) {
        sound->setPath("../../../Asset/Sound/Explosion.ogg");
        sound->play();
    }
}

static void manageModel(std::shared_ptr<IInput> input, std::shared_ptr<IModel> model, std::shared_ptr<IModel> animation)
{
    static bool inAnim = false;

    if (input->isKeyPressed(raylib::KeyBoard::IKEY_C)) {
        inAnim = false;
    }
    if (input->isKeyPressed(raylib::KeyBoard::IKEY_V)) {
        inAnim = true;
    }
    if (!inAnim)
        model->draw();
    else
        animation->draw();
}

int main(void)
{
    MyVector2 windowSize(1200, 800);
    MyVector3 camPos(0, -5.0f, 10.0f);
    MyVector3 camTarget(0, 0, 0);
    MyVector3 camUp(0.0f, 1.0f, 0.0f);
    MyVector3 cubePos(0, 0, 0);
    MyVector3 cubeSize(2.0f, 2.0f, 2.0f);
    MyVector2 texturePos(100.0f, 0.0f);
    MyVector2 rectPos(100.0f, 0.0f);
    MyVector2 rectSize(600.0f, 100.0f);
    MyVector2 textPos(0.0f, 130.0f);
    MyVector4 textLimit(0.0f, 0.0f, 100.0f, 100.0f);
    size_t textSize = 25;
    MyVector3 modelPos(0, 0, 1);
    MyVector3 modelRot(-90, 0, 0);
    float scale = 0.5;
    std::shared_ptr<IWindow> window = std::make_shared<raylib::Window>(windowSize, "Bootstrap", raylib::RColor::RWHITE);
    std::shared_ptr<IInput> input = std::make_shared<raylib::Input>();
    std::shared_ptr<ICamera> camera = std::make_shared<raylib::Camera>(camPos, camTarget, camUp);
    std::shared_ptr<ISolid> cube = std::make_shared<raylib::Cuboid>(nullptr, cubePos, cubeSize, raylib::RColor::RLIGHTGRAY);
    std::shared_ptr<IShape> rect = std::make_shared<raylib::Rectangle>(rectPos, rectSize, raylib::RColor::RORANGE);
    std::shared_ptr<IText> text = std::make_shared<raylib::Text>("Ca va mon amigos ?", textPos, textSize, raylib::RColor::RPINK);
    std::shared_ptr<ITexture> texture = nullptr;
    std::shared_ptr<ITexture> texture2 = nullptr;
    std::shared_ptr<IAudio> music = nullptr;
    std::shared_ptr<IAudio> sound = nullptr;
    std::shared_ptr<IModel> model = nullptr;
    std::shared_ptr<IModel> animation = nullptr;

    window->setCamera(camera);
    window->open();
    texture = std::make_shared<raylib::Texture>("../../../Asset/Interface/TitleLogo.png");
    texture->setPosition(texturePos);
    texture2 = std::make_shared<raylib::Texture>("../../../Asset/Texture/Desert/Ground/Sand.png");
    music = std::make_shared<raylib::Music>("../../../Asset/Music/Fight9.mp3");
    sound = std::make_shared<raylib::Sound>("../../../Asset/Sound/ButtonClick.ogg");
    text->setFont("../../../Asset/Font/MinecraftRegular.ttf");
    text->setLimit(textLimit);
    model = std::make_shared<raylib::Model>(
        "../../../Asset/Skin/Basic_Test.png", "../../../Asset/Model/Model_Char/Model_Char.obj", modelPos, raylib::RColor::RWHITE);
    model->setRotation(modelRot);
    model->setScale(scale);
    animation = std::make_shared<raylib::Animation>(
        "../../../Asset/Skin/Basic_Test.png", "../../../Asset/Animation/Anim_Walk_20", modelPos, raylib::RColor::RWHITE);
    animation->setRotation(modelRot);
    animation->setScale(scale);
    while (window->isOpen()) {
        window->clear();
        changeScreenSize(input, &windowSize, window);
        moveCamera(input, &camPos, camera);
        manageCubeTexture(input, cube, texture2);
        manageMusic(input, music);
        manageSound(input, sound);
        rect->draw();
        texture->draw();
        music->update();
        text->draw();
        camera->begin3D();
        drawCube(cube, cubePos);
        manageModel(input, model, animation);
        camera->end3D();
        window->refresh();
    }
    window->close();
    return 0;
}