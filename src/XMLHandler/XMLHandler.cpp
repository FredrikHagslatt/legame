#include "XMLHandler/XMLHandler.h"

void XMLHandler::SaveTransform(tinyxml2::XMLElement *components)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "Transform");

    tinyxml2::XMLElement *x = component->InsertNewChildElement("x");
    tinyxml2::XMLElement *y = component->InsertNewChildElement("y");
    tinyxml2::XMLElement *rotation = component->InsertNewChildElement("rotation");

    x->SetText("0.0");
    y->SetText("5.2");
    rotation->SetText("0.0");

    tinyxml2::XMLElement *scale = component->InsertNewChildElement("scale");
    tinyxml2::XMLElement *scaleX = scale->InsertNewChildElement("x");
    tinyxml2::XMLElement *scaleY = scale->InsertNewChildElement("y");

    scaleX->SetText("1.0");
    scaleY->SetText("1.0");
}

void XMLHandler::SaveAnimation(tinyxml2::XMLElement *components)
{

    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "Animation");

    tinyxml2::XMLElement *numFrames = component->InsertNewChildElement("numFrames");
    tinyxml2::XMLElement *frameRateSpeed = component->InsertNewChildElement("frameRateSpeed");
    tinyxml2::XMLElement *isLoop = component->InsertNewChildElement("isLoop");
    tinyxml2::XMLElement *hasDirections = component->InsertNewChildElement("hasDirections");

    numFrames->SetText(1);
    frameRateSpeed->SetText(1);
    isLoop->SetText(true);
    hasDirections->SetText(false);
}

void XMLHandler::SaveBoxCollider(tinyxml2::XMLElement *components)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "BoxCollider");

    tinyxml2::XMLElement *width = component->InsertNewChildElement("width");
    tinyxml2::XMLElement *height = component->InsertNewChildElement("height");
    tinyxml2::XMLElement *offset = component->InsertNewChildElement("offset");

    width->SetText(16);
    height->SetText(16);

    tinyxml2::XMLElement *offsetX = offset->InsertNewChildElement("x");
    tinyxml2::XMLElement *offsetY = offset->InsertNewChildElement("y");

    offsetX->SetText("0.0");
    offsetY->SetText("0.0");
}

void XMLHandler::SaveCircleCollider(tinyxml2::XMLElement *components)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "CircleCollider");

    tinyxml2::XMLElement *radius = component->InsertNewChildElement("radius");
    radius->SetText(16);

    tinyxml2::XMLElement *offset = component->InsertNewChildElement("offset");
    tinyxml2::XMLElement *offsetX = offset->InsertNewChildElement("x");
    tinyxml2::XMLElement *offsetY = offset->InsertNewChildElement("y");

    offsetX->SetText("0.0");
    offsetY->SetText("0.0");
}

void XMLHandler::SaveHealth(tinyxml2::XMLElement *components)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "Health");

    tinyxml2::XMLElement *healthPercentage = component->InsertNewChildElement("healthPercentage");
    healthPercentage->SetText(16);
}

void XMLHandler::SaveMenuNavigator(tinyxml2::XMLElement *components)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "MenuNavigator");

    tinyxml2::XMLElement *numRows = component->InsertNewChildElement("numRows");
    tinyxml2::XMLElement *rowDistance = component->InsertNewChildElement("rowDistance");
    tinyxml2::XMLElement *atRow = component->InsertNewChildElement("atRow");

    numRows->SetText(4);
    rowDistance->SetText(60);
    atRow->SetText(0);
}

void XMLHandler::SaveProjectile(tinyxml2::XMLElement *components)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "Projectile");

    tinyxml2::XMLElement *isFriendly = component->InsertNewChildElement("isFriendly");
    tinyxml2::XMLElement *hitPercentDamage = component->InsertNewChildElement("hitPercentDamage");
    tinyxml2::XMLElement *duration = component->InsertNewChildElement("duration");

    isFriendly->SetText(false);
    hitPercentDamage->SetText(10);
    duration->SetText(10);
}

void XMLHandler::SaveProjectileEmitter(tinyxml2::XMLElement *components)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "ProjectileEmitter");

    tinyxml2::XMLElement *speed = component->InsertNewChildElement("speed");
    tinyxml2::XMLElement *direction = component->InsertNewChildElement("direction");
    tinyxml2::XMLElement *repeatFrequency = component->InsertNewChildElement("repeatFrequency");
    tinyxml2::XMLElement *duration = component->InsertNewChildElement("duration");
    tinyxml2::XMLElement *hitPercentDamage = component->InsertNewChildElement("hitPercentDamage");
    tinyxml2::XMLElement *isFriendly = component->InsertNewChildElement("isFriendly");
    tinyxml2::XMLElement *inheritDirection = component->InsertNewChildElement("inheritDirection");

    speed->SetText("0.0");
    repeatFrequency->SetText(1);
    duration->SetText(10000);
    hitPercentDamage->SetText(10);
    isFriendly->SetText(false);
    inheritDirection->SetText(false);

    tinyxml2::XMLElement *directionX = direction->InsertNewChildElement("x");
    tinyxml2::XMLElement *directionY = direction->InsertNewChildElement("y");

    directionX->SetText("1.0");
    directionY->SetText("-1.0");
}

void XMLHandler::SaveSceneSwitcher(tinyxml2::XMLElement *components)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "SceneSwitcher");

    tinyxml2::XMLElement *sceneManagerId = component->InsertNewChildElement("sceneManagerId");
    tinyxml2::XMLElement *sceneName = component->InsertNewChildElement("sceneName");

    sceneManagerId->SetText("Main");
    sceneName->SetText("Garden");
}

void XMLHandler::SaveSprite(tinyxml2::XMLElement *components)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "Sprite");

    tinyxml2::XMLElement *assetId = component->InsertNewChildElement("assetId");
    tinyxml2::XMLElement *width = component->InsertNewChildElement("width");
    tinyxml2::XMLElement *height = component->InsertNewChildElement("height");
    tinyxml2::XMLElement *pivotPoint = component->InsertNewChildElement("pivotPoint");
    tinyxml2::XMLElement *fixedPosition = component->InsertNewChildElement("fixedPosition");
    tinyxml2::XMLElement *srcRectX = component->InsertNewChildElement("srcRextX");
    tinyxml2::XMLElement *srcRextY = component->InsertNewChildElement("srcRectY");
    tinyxml2::XMLElement *SDL_RenderFlip = component->InsertNewChildElement("SDL_RenderFlip");

    assetId->SetText("sample-name");
    width->SetText(0);
    height->SetText(0);
    pivotPoint->SetText(16);
    fixedPosition->SetText(false);
    srcRectX->SetText(16);
    srcRextY->SetText(16);
    SDL_RenderFlip->SetText("SDL_FLIP_NONE");
}

void XMLHandler::SaveTextLabel(tinyxml2::XMLElement *components)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "TextLabel");

    tinyxml2::XMLElement *position = component->InsertNewChildElement("position");
    tinyxml2::XMLElement *text = component->InsertNewChildElement("text");
    tinyxml2::XMLElement *assetId = component->InsertNewChildElement("assetId");
    tinyxml2::XMLElement *color = component->InsertNewChildElement("color");
    tinyxml2::XMLElement *isFixed = component->InsertNewChildElement("isFixed");

    text->SetText("Thunderballs and lightning, very very frightening");
    assetId->SetText("font-name");
    isFixed->SetText(true);

    tinyxml2::XMLElement *positionX = position->InsertNewChildElement("x");
    tinyxml2::XMLElement *positionY = position->InsertNewChildElement("y");

    positionX->SetText("600.0");
    positionY->SetText("300.0");

    tinyxml2::XMLElement *colorR = color->InsertNewChildElement("r");
    tinyxml2::XMLElement *colorG = color->InsertNewChildElement("g");
    tinyxml2::XMLElement *colorB = color->InsertNewChildElement("b");

    colorR->SetText(25);
    colorG->SetText(25);
    colorB->SetText(25);
}

void XMLHandler::SaveVelocity(tinyxml2::XMLElement *components)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "Velocity");

    tinyxml2::XMLElement *speed = component->InsertNewChildElement("speed");
    tinyxml2::XMLElement *direction = component->InsertNewChildElement("direction");
    tinyxml2::XMLElement *lastNonZeroDirection = component->InsertNewChildElement("lastNonZeroDirection");

    speed->SetText("10.0");

    tinyxml2::XMLElement *directionX = direction->InsertNewChildElement("x");
    tinyxml2::XMLElement *directionY = direction->InsertNewChildElement("y");

    directionX->SetText("1.0");
    directionY->SetText("1.0");

    tinyxml2::XMLElement *lastNonZeroDirectionX = lastNonZeroDirection->InsertNewChildElement("x");
    tinyxml2::XMLElement *lastNonZeroDirectionY = lastNonZeroDirection->InsertNewChildElement("y");

    lastNonZeroDirectionX->SetText("1.0");
    lastNonZeroDirectionY->SetText("1.0");
}

void XMLHandler::SaveTags(tinyxml2::XMLElement *components)
{
    tinyxml2::XMLElement *tags = components->InsertNewChildElement("component");
    tags->SetAttribute("type", "Tags");

    tags->InsertNewChildElement("tag")->SetText("Player_Tag");
    tags->InsertNewChildElement("tag")->SetText("Enemy_Tag");
    tags->InsertNewChildElement("tag")->SetText("Obstacle_Tag");
    tags->InsertNewChildElement("tag")->SetText("KeyboardControlled_Tag");
    tags->InsertNewChildElement("tag")->SetText("Projectile_Tag");
    tags->InsertNewChildElement("tag")->SetText("StayOnMap_Tag");
    tags->InsertNewChildElement("tag")->SetText("Trigger_Tag");
    tags->InsertNewChildElement("tag")->SetText("Airborne_Tag");
    tags->InsertNewChildElement("tag")->SetText("Effect_Tag");
    tags->InsertNewChildElement("tag")->SetText("UI_Tag");
}

void XMLHandler::AddTags(tinyxml2::XMLElement *component)
{
    for (tinyxml2::XMLElement *tag = component->FirstChildElement("tag");
         tag != NULL;
         tag = tag->NextSiblingElement())
    {
        const char *tagName = tag->FirstChild()->ToText()->Value();
        std::cout << tagName << std::endl;
    }
}

void XMLHandler::AddComponent(tinyxml2::XMLElement *component)
{
    std::string componentType = component->Attribute("type");

    if (componentType == "Animation")
    {
        std::cout << "Animation" << std::endl;
    }
    else if (componentType == "BoxCollider")
    {
        std::cout << "BoxCollider" << std::endl;
    }
    else if (componentType == "CircleCollider")
    {
        std::cout << "CircleCollider" << std::endl;
    }
    else if (componentType == "Health")
    {
        std::cout << "Health" << std::endl;
    }
    else if (componentType == "MenuNavigator")
    {
        std::cout << "MenuNavigator" << std::endl;
    }
    else if (componentType == "Projectile")
    {
        std::cout << "Projectile" << std::endl;
    }
    else if (componentType == "ProjectileEmitter")
    {
        std::cout << "ProjectileEmitter" << std::endl;
    }
    else if (componentType == "SceneSwitcher")
    {
        std::cout << "SceneSwitcher" << std::endl;
    }
    else if (componentType == "Sprite")
    {
        std::cout << "Sprite" << std::endl;
    }
    else if (componentType == "Tags")
    {
        AddTags(component);
    }
    else if (componentType == "TextLabel")
    {
        std::cout << "TextLabel" << std::endl;
    }
    else if (componentType == "Transform")
    {
        std::cout << "Transform" << std::endl;
    }
    else if (componentType == "Velocity")
    {
        std::cout << "Velocity" << std::endl;
    }
    else
    {
        std::cout << "Component from xml does not match any game component" << std::endl;
    }
}

void XMLHandler::ReadFromXML()
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile("assets/SavedData.xml");

    tinyxml2::XMLElement *root = doc.FirstChildElement("level");
    tinyxml2::XMLElement *entities = root->FirstChildElement("entities");
    tinyxml2::XMLElement *entity = entities->FirstChildElement("entity");
    tinyxml2::XMLElement *components = entity->FirstChildElement("components");

    for (tinyxml2::XMLElement *component = components->FirstChildElement("component");
         component != NULL;
         component = component->NextSiblingElement())
    {
        AddComponent(component);
    }
}

void XMLHandler::SaveEntityToXML(std::shared_ptr<entt::registry> registry, tinyxml2::XMLElement *entities, entt::entity entity)
{
    tinyxml2::XMLElement *entityElement = entities->InsertNewChildElement("entity");
    tinyxml2::XMLElement *components = entityElement->InsertNewChildElement("components");

    if (registry->all_of<Animation>(entity))
    {
        SaveAnimation(components);
    }
    if (registry->all_of<BoxCollider>(entity))
    {
        SaveBoxCollider(components);
    }
    if (registry->all_of<CircleCollider>(entity))
    {
        SaveCircleCollider(components);
    }
    if (registry->all_of<Health>(entity))
    {
        SaveHealth(components);
    }
    if (registry->all_of<MenuNavigator>(entity))
    {
        SaveMenuNavigator(components);
    }
    if (registry->all_of<Projectile>(entity))
    {
        SaveProjectile(components);
    }

    if (registry->all_of<ProjectileEmitter>(entity))
    {
        SaveProjectileEmitter(components);
    }

    if (registry->all_of<SceneSwitcher>(entity))
    {
        SaveSceneSwitcher(components);
    }

    if (registry->all_of<Sprite>(entity))
    {
        SaveSprite(components);
    }
    if (registry->all_of<TextLabel>(entity))
    {
        SaveTextLabel(components);
    }
    if (registry->all_of<Velocity>(entity))
    {
        SaveVelocity(components);
    }

    if (registry->all_of<Transform>(entity))
    {
        SaveTransform(components);
    }

    // Handle Tags
}

void XMLHandler::SaveToXML(std::shared_ptr<entt::registry> registry)
{

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLNode *root = doc.NewElement("level");
    doc.InsertFirstChild(root);

    tinyxml2::XMLElement *entities = doc.NewElement("entities");

    registry->each([entities, registry](auto entity)
                   { SaveEntityToXML(registry, entities, entity); });

    root->InsertEndChild(entities);
    tinyxml2::XMLError result = doc.SaveFile("SavedData.xml");
}
