#include "XMLHandler/XMLHandler.h"

void XMLHandler::SaveAnimation(tinyxml2::XMLElement *components, Animation animation)
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

void XMLHandler::SaveBoxCollider(tinyxml2::XMLElement *components, BoxCollider boxCollider)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "BoxCollider");

    tinyxml2::XMLElement *width = component->InsertNewChildElement("width");
    tinyxml2::XMLElement *height = component->InsertNewChildElement("height");
    tinyxml2::XMLElement *offset = component->InsertNewChildElement("offset");

    width->SetText(boxCollider.width);
    height->SetText(boxCollider.height);

    tinyxml2::XMLElement *offsetX = offset->InsertNewChildElement("x");
    tinyxml2::XMLElement *offsetY = offset->InsertNewChildElement("y");

    offsetX->SetText(boxCollider.offset.x);
    offsetY->SetText(boxCollider.offset.x);
}

void XMLHandler::SaveCircleCollider(tinyxml2::XMLElement *components, CircleCollider circleCollider)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "CircleCollider");

    tinyxml2::XMLElement *radius = component->InsertNewChildElement("radius");
    radius->SetText(circleCollider.radius);

    tinyxml2::XMLElement *offset = component->InsertNewChildElement("offset");
    tinyxml2::XMLElement *offsetX = offset->InsertNewChildElement("x");
    tinyxml2::XMLElement *offsetY = offset->InsertNewChildElement("y");

    offsetX->SetText(circleCollider.offset.x);
    offsetY->SetText(circleCollider.offset.y);
}

void XMLHandler::SaveHealth(tinyxml2::XMLElement *components, Health health)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "Health");

    tinyxml2::XMLElement *healthPercentage = component->InsertNewChildElement("healthPercentage");
    healthPercentage->SetText(health.healthPercentage);
}

void XMLHandler::SaveMenuNavigator(tinyxml2::XMLElement *components, MenuNavigator menuNavigator)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "MenuNavigator");

    tinyxml2::XMLElement *numRows = component->InsertNewChildElement("numRows");
    tinyxml2::XMLElement *rowDistance = component->InsertNewChildElement("rowDistance");
    tinyxml2::XMLElement *atRow = component->InsertNewChildElement("atRow");

    numRows->SetText(menuNavigator.numRows);
    rowDistance->SetText(menuNavigator.rowDistance);
    atRow->SetText(menuNavigator.atRow);
}

void XMLHandler::SaveProjectile(tinyxml2::XMLElement *components, Projectile projectile)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "Projectile");

    tinyxml2::XMLElement *isFriendly = component->InsertNewChildElement("isFriendly");
    tinyxml2::XMLElement *hitPercentDamage = component->InsertNewChildElement("hitPercentDamage");
    tinyxml2::XMLElement *duration = component->InsertNewChildElement("duration");

    isFriendly->SetText(projectile.isFriendly);
    hitPercentDamage->SetText(projectile.hitPercentDamage);
    duration->SetText(projectile.duration);
}

void XMLHandler::SaveProjectileEmitter(tinyxml2::XMLElement *components, ProjectileEmitter projectileEmitter)
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

    speed->SetText(projectileEmitter.speed);
    repeatFrequency->SetText(projectileEmitter.repeatFrequency);
    duration->SetText(projectileEmitter.duration);
    hitPercentDamage->SetText(projectileEmitter.hitPercentDamage);
    isFriendly->SetText(projectileEmitter.isFriendly);
    inheritDirection->SetText(projectileEmitter.inheritDirection);

    tinyxml2::XMLElement *directionX = direction->InsertNewChildElement("x");
    tinyxml2::XMLElement *directionY = direction->InsertNewChildElement("y");

    directionX->SetText(projectileEmitter.direction.x);
    directionY->SetText(projectileEmitter.direction.y);
}

void XMLHandler::SaveSceneSwitcher(tinyxml2::XMLElement *components, SceneSwitcher sceneSwitcher)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "SceneSwitcher");

    tinyxml2::XMLElement *sceneManagerId = component->InsertNewChildElement("sceneManagerId");
    tinyxml2::XMLElement *sceneName = component->InsertNewChildElement("sceneName");

    sceneManagerId->SetText(sceneSwitcher.sceneManagerId.c_str());
    sceneName->SetText(sceneSwitcher.sceneName.c_str());
}

void XMLHandler::SaveSprite(tinyxml2::XMLElement *components, Sprite sprite)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "Sprite");

    tinyxml2::XMLElement *assetId = component->InsertNewChildElement("assetId");
    tinyxml2::XMLElement *width = component->InsertNewChildElement("width");
    tinyxml2::XMLElement *height = component->InsertNewChildElement("height");
    tinyxml2::XMLElement *pivotPoint = component->InsertNewChildElement("pivotPoint");
    tinyxml2::XMLElement *fixedPosition = component->InsertNewChildElement("fixedPosition");
    tinyxml2::XMLElement *srcRect = component->InsertNewChildElement("srcRect");
    tinyxml2::XMLElement *flip = component->InsertNewChildElement("flip");

    tinyxml2::XMLElement *srcRectX = srcRect->InsertNewChildElement("x");
    tinyxml2::XMLElement *srcRectY = srcRect->InsertNewChildElement("y");

    assetId->SetText(sprite.assetId.c_str());
    width->SetText(sprite.width);
    height->SetText(sprite.height);
    pivotPoint->SetText(sprite.pivotPoint);
    fixedPosition->SetText(sprite.fixedPosition);
    srcRectX->SetText(sprite.srcRect.x);
    srcRectY->SetText(sprite.srcRect.y);
    flip->SetText(sprite.flip);
}

void XMLHandler::SaveTextLabel(tinyxml2::XMLElement *components, TextLabel textLabel)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "TextLabel");

    tinyxml2::XMLElement *position = component->InsertNewChildElement("position");
    tinyxml2::XMLElement *text = component->InsertNewChildElement("text");
    tinyxml2::XMLElement *assetId = component->InsertNewChildElement("assetId");
    tinyxml2::XMLElement *color = component->InsertNewChildElement("color");
    tinyxml2::XMLElement *isFixed = component->InsertNewChildElement("isFixed");

    text->SetText(textLabel.text.c_str());
    assetId->SetText(textLabel.assetId.c_str());
    isFixed->SetText(textLabel.isFixed);

    tinyxml2::XMLElement *positionX = position->InsertNewChildElement("x");
    tinyxml2::XMLElement *positionY = position->InsertNewChildElement("y");

    positionX->SetText(textLabel.position.x);
    positionY->SetText(textLabel.position.y);

    tinyxml2::XMLElement *colorR = color->InsertNewChildElement("r");
    tinyxml2::XMLElement *colorG = color->InsertNewChildElement("g");
    tinyxml2::XMLElement *colorB = color->InsertNewChildElement("b");

    colorR->SetText(textLabel.color.r);
    colorG->SetText(textLabel.color.g);
    colorB->SetText(textLabel.color.b);
}

void XMLHandler::SaveTransform(tinyxml2::XMLElement *components, Transform transform)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "Transform");

    tinyxml2::XMLElement *x = component->InsertNewChildElement("x");
    tinyxml2::XMLElement *y = component->InsertNewChildElement("y");
    tinyxml2::XMLElement *rotation = component->InsertNewChildElement("rotation");

    x->SetText(transform.position.x);
    y->SetText(transform.position.y);
    rotation->SetText(transform.rotation);

    tinyxml2::XMLElement *scale = component->InsertNewChildElement("scale");
    tinyxml2::XMLElement *scaleX = scale->InsertNewChildElement("x");
    tinyxml2::XMLElement *scaleY = scale->InsertNewChildElement("y");

    scaleX->SetText(transform.scale.x);
    scaleY->SetText(transform.scale.y);
}

void XMLHandler::SaveVelocity(tinyxml2::XMLElement *components, Velocity velocity)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "Velocity");

    tinyxml2::XMLElement *speed = component->InsertNewChildElement("speed");
    tinyxml2::XMLElement *direction = component->InsertNewChildElement("direction");
    tinyxml2::XMLElement *lastNonZeroDirection = component->InsertNewChildElement("lastNonZeroDirection");

    speed->SetText(velocity.speed);

    tinyxml2::XMLElement *directionX = direction->InsertNewChildElement("x");
    tinyxml2::XMLElement *directionY = direction->InsertNewChildElement("y");

    directionX->SetText(velocity.direction.x);
    directionY->SetText(velocity.direction.y);

    tinyxml2::XMLElement *lastNonZeroDirectionX = lastNonZeroDirection->InsertNewChildElement("x");
    tinyxml2::XMLElement *lastNonZeroDirectionY = lastNonZeroDirection->InsertNewChildElement("y");

    lastNonZeroDirectionX->SetText(velocity.lastNonZeroDirection.x);
    lastNonZeroDirectionY->SetText(velocity.lastNonZeroDirection.y);
}

void XMLHandler::SaveTags(tinyxml2::XMLElement *components, std::shared_ptr<entt::registry> registry, entt::entity entity)
{
    tinyxml2::XMLElement *tags = components->InsertNewChildElement("component");
    tags->SetAttribute("type", "Tags");

    if (registry->all_of<Player_Tag>(entity))
    {
        tags->InsertNewChildElement("tag")->SetText("Player_Tag");
    }
    if (registry->all_of<Enemy_Tag>(entity))
    {
        tags->InsertNewChildElement("tag")->SetText("Enemy_Tag");
    }
    if (registry->all_of<Obstacle_Tag>(entity))
    {
        tags->InsertNewChildElement("tag")->SetText("Obstacle_Tag");
    }
    if (registry->all_of<KeyboardControlled_Tag>(entity))
    {
        tags->InsertNewChildElement("tag")->SetText("KeyboardControlled_Tag");
    }
    if (registry->all_of<Projectile_Tag>(entity))
    {
        tags->InsertNewChildElement("tag")->SetText("Projectile_Tag");
    }
    if (registry->all_of<StayOnMap_Tag>(entity))
    {
        tags->InsertNewChildElement("tag")->SetText("StayOnMap_Tag");
    }
    if (registry->all_of<Trigger_Tag>(entity))
    {
        tags->InsertNewChildElement("tag")->SetText("Trigger_Tag");
    }
    if (registry->all_of<Airborne_Tag>(entity))
    {
        tags->InsertNewChildElement("tag")->SetText("Airborne_Tag");
    }
    if (registry->all_of<Effect_Tag>(entity))
    {
        tags->InsertNewChildElement("tag")->SetText("Effect_Tag");
    }
    if (registry->all_of<UI_Tag>(entity))
    {
        tags->InsertNewChildElement("tag")->SetText("UI_Tag");
    }
}

void XMLHandler::LoadTags(tinyxml2::XMLElement *component)
{
    for (tinyxml2::XMLElement *tag = component->FirstChildElement("tag");
         tag != NULL;
         tag = tag->NextSiblingElement())
    {
        const char *tagName = tag->FirstChild()->ToText()->Value();
        std::cout << tagName << std::endl;
    }
}

void XMLHandler::LoadComponent(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component)
{
    std::string componentType = component->Attribute("type");

    if (componentType == "Animation")
    {
    }
    else if (componentType == "BoxCollider")
    {
    }
    else if (componentType == "CircleCollider")
    {
    }
    else if (componentType == "Health")
    {
    }
    else if (componentType == "MenuNavigator")
    {
    }
    else if (componentType == "Projectile")
    {
    }
    else if (componentType == "ProjectileEmitter")
    {
    }
    else if (componentType == "SceneSwitcher")
    {
    }
    else if (componentType == "Sprite")
    {
        tinyxml2::XMLElement *assetIdElement = component->FirstChildElement("assetId");
        tinyxml2::XMLElement *widthElement = component->FirstChildElement("width");
        tinyxml2::XMLElement *heightElement = component->FirstChildElement("height");
        tinyxml2::XMLElement *pivotPointElement = component->FirstChildElement("pivotPoint");
        tinyxml2::XMLElement *fixedPositionElement = component->FirstChildElement("fixedPosition");
        tinyxml2::XMLElement *srcRectElement = component->FirstChildElement("srcRect");
        tinyxml2::XMLElement *flipElement = component->FirstChildElement("flip");

        tinyxml2::XMLElement *srcRectXElement = srcRectElement->FirstChildElement("x");
        tinyxml2::XMLElement *srcRectYElement = srcRectElement->FirstChildElement("y");

        std::string assetId = assetIdElement->FirstChild()->ToText()->Value();
        std::string width_str = widthElement->FirstChild()->ToText()->Value();
        std::string height_str = heightElement->FirstChild()->ToText()->Value();
        std::string pivotPoint_str = pivotPointElement->FirstChild()->ToText()->Value();
        std::string fixedPosition_str = fixedPositionElement->FirstChild()->ToText()->Value();
        std::string srcRectX_str = srcRectXElement->FirstChild()->ToText()->Value();
        std::string srcRectY_str = srcRectYElement->FirstChild()->ToText()->Value();
        std::string flip_str = flipElement->FirstChild()->ToText()->Value();

        // std::string assetId // Done
        int width = std::stoi(width_str);
        int height = std::stoi(height_str);
        int pivotPoint = std::stoi(pivotPoint_str);
        bool fixedPosition = (fixedPosition_str == "true");
        int srcRectX = std::stoi(srcRectX_str);
        int srcRectY = std::stoi(srcRectY_str);
        SDL_RendererFlip flip = (SDL_RendererFlip)(std::stoi(flip_str));

        registry->emplace<Sprite>(entity, assetId, width, height, pivotPoint, fixedPosition, srcRectX, srcRectY, SDL_FLIP_NONE);
    }
    else if (componentType == "Tags")
    {
        LoadTags(component);
    }
    else if (componentType == "TextLabel")
    {
    }
    else if (componentType == "Transform")
    {
        tinyxml2::XMLElement *xElement = component->FirstChildElement("x");
        tinyxml2::XMLElement *yElement = component->FirstChildElement("y");
        tinyxml2::XMLElement *rotationElement = component->FirstChildElement("rotation");
        tinyxml2::XMLElement *scaleElement = component->FirstChildElement("scale");
        tinyxml2::XMLElement *scaleXElement = scaleElement->FirstChildElement("x");
        tinyxml2::XMLElement *scaleYElement = scaleElement->FirstChildElement("y");

        std::string x = xElement->FirstChild()->ToText()->Value();
        std::string y = yElement->FirstChild()->ToText()->Value();
        std::string rotation_str = rotationElement->FirstChild()->ToText()->Value();
        std::string scaleX = scaleXElement->FirstChild()->ToText()->Value();
        std::string scaleY = scaleYElement->FirstChild()->ToText()->Value();

        vec2f position = vec2f(std::stof(x), std::stof(y));
        vec2f scale = vec2f(std::stof(scaleX), std::stof(scaleY));
        double rotation = std::stof(rotation_str);

        registry->emplace<Transform>(entity, position, scale, rotation);

        std::cout << "Transform" << std::endl;
    }
    else if (componentType == "Velocity")
    {
    }
    else
    {
        std::cout << "Component from xml does not match any game component" << std::endl;
    }
}

void XMLHandler::LoadFromXML(std::shared_ptr<entt::registry> registry)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile("assets/SavedData.xml");

    tinyxml2::XMLElement *root = doc.FirstChildElement("level");
    tinyxml2::XMLElement *entities = root->FirstChildElement("entities");
    tinyxml2::XMLElement *entity = entities->FirstChildElement("entity");
    tinyxml2::XMLElement *components = entity->FirstChildElement("components");

    entt::entity newEntity = registry->create();
    for (tinyxml2::XMLElement *component = components->FirstChildElement("component");
         component != NULL;
         component = component->NextSiblingElement())
    {
        LoadComponent(registry, newEntity, component);
    }
}

void XMLHandler::SaveEntityToXML(std::shared_ptr<entt::registry> registry, tinyxml2::XMLElement *entities, entt::entity entity)
{
    tinyxml2::XMLElement *entityElement = entities->InsertNewChildElement("entity");
    tinyxml2::XMLElement *components = entityElement->InsertNewChildElement("components");

    if (registry->all_of<Animation>(entity))
    {
        auto animation = registry->get<Animation>(entity);
        SaveAnimation(components, animation);
    }
    if (registry->all_of<BoxCollider>(entity))
    {
        auto boxCollider = registry->get<BoxCollider>(entity);
        SaveBoxCollider(components, boxCollider);
    }
    if (registry->all_of<CircleCollider>(entity))
    {
        auto circleCollider = registry->get<CircleCollider>(entity);
        SaveCircleCollider(components, circleCollider);
    }
    if (registry->all_of<Health>(entity))
    {
        auto health = registry->get<Health>(entity);
        SaveHealth(components, health);
    }
    if (registry->all_of<MenuNavigator>(entity))
    {
        auto menuNavigator = registry->get<MenuNavigator>(entity);
        SaveMenuNavigator(components, menuNavigator);
    }
    if (registry->all_of<Projectile>(entity))
    {
        auto projectile = registry->get<Projectile>(entity);
        SaveProjectile(components, projectile);
    }
    if (registry->all_of<ProjectileEmitter>(entity))
    {
        auto projectileEmitter = registry->get<ProjectileEmitter>(entity);
        SaveProjectileEmitter(components, projectileEmitter);
    }

    if (registry->all_of<SceneSwitcher>(entity))
    {
        auto sceneSwitcher = registry->get<SceneSwitcher>(entity);
        SaveSceneSwitcher(components, sceneSwitcher);
    }

    if (registry->all_of<Sprite>(entity))
    {
        auto sprite = registry->get<Sprite>(entity);
        SaveSprite(components, sprite);
    }
    if (registry->all_of<TextLabel>(entity))
    {
        auto textLabel = registry->get<TextLabel>(entity);
        SaveTextLabel(components, textLabel);
    }
    if (registry->all_of<Transform>(entity))
    {
        auto transform = registry->get<Transform>(entity);
        SaveTransform(components, transform);
    }

    if (registry->all_of<Velocity>(entity))
    {
        auto velocity = registry->get<Velocity>(entity);
        SaveVelocity(components, velocity);
    }

    if (registry->any_of<KeyboardControlled_Tag,
                         Player_Tag,
                         Enemy_Tag,
                         Obstacle_Tag,
                         Projectile_Tag,
                         StayOnMap_Tag,
                         Trigger_Tag,
                         Airborne_Tag,
                         Effect_Tag,
                         UI_Tag>(entity))
    {
        SaveTags(components, registry, entity);
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
