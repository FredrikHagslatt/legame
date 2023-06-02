#include "Constants.h"
#include "Logger/Logger.h"
#include "XMLHandler/XMLHandler.h"
#include <sys/stat.h>

bool XMLHandler::FileExists(const std::string filename)
{
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

void XMLHandler::SaveAnimation(tinyxml2::XMLElement *components, const Animation animation)
{

    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "Animation");

    tinyxml2::XMLElement *numFrames = component->InsertNewChildElement("numFrames");
    tinyxml2::XMLElement *frameRateSpeed = component->InsertNewChildElement("frameRateSpeed");
    tinyxml2::XMLElement *isLoop = component->InsertNewChildElement("isLoop");
    tinyxml2::XMLElement *hasDirections = component->InsertNewChildElement("hasDirections");

    numFrames->SetText(animation.numFrames);
    frameRateSpeed->SetText(animation.frameRateSpeed);
    isLoop->SetText(animation.isLoop);
    hasDirections->SetText(animation.hasDirections);
}

void XMLHandler::SaveBoxCollider(tinyxml2::XMLElement *components, const BoxCollider boxCollider)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "BoxCollider");

    tinyxml2::XMLElement *width = component->InsertNewChildElement("width");
    tinyxml2::XMLElement *height = component->InsertNewChildElement("height");
    tinyxml2::XMLElement *offset = component->InsertNewChildElement("offset");

    width->SetText(boxCollider.width / SCALE);
    height->SetText(boxCollider.height / SCALE);

    tinyxml2::XMLElement *offsetX = offset->InsertNewChildElement("x");
    tinyxml2::XMLElement *offsetY = offset->InsertNewChildElement("y");

    offsetX->SetText(boxCollider.offset.x / SCALE);
    offsetY->SetText(boxCollider.offset.x / SCALE);
}

void XMLHandler::SaveCircleCollider(tinyxml2::XMLElement *components, const CircleCollider circleCollider)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "CircleCollider");

    tinyxml2::XMLElement *radius = component->InsertNewChildElement("radius");
    radius->SetText(circleCollider.radius / SCALE);

    tinyxml2::XMLElement *offset = component->InsertNewChildElement("offset");
    tinyxml2::XMLElement *offsetX = offset->InsertNewChildElement("x");
    tinyxml2::XMLElement *offsetY = offset->InsertNewChildElement("y");

    offsetX->SetText(circleCollider.offset.x / SCALE);
    offsetY->SetText(circleCollider.offset.y / SCALE);
}

void XMLHandler::SaveHealth(tinyxml2::XMLElement *components, const Health health)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "Health");

    tinyxml2::XMLElement *healthElement = component->InsertNewChildElement("hitPoints");
    healthElement->SetText(health.hitPoints);
}

void XMLHandler::SaveMenuNavigator(tinyxml2::XMLElement *components, const MenuNavigator menuNavigator)
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

void XMLHandler::SaveProjectile(tinyxml2::XMLElement *components, const Projectile projectile)
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

void XMLHandler::SaveProjectileEmitter(tinyxml2::XMLElement *components, const ProjectileEmitter projectileEmitter)
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

void XMLHandler::SaveSceneSwitcher(tinyxml2::XMLElement *components, const SceneSwitcher sceneSwitcher)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "SceneSwitcher");

    tinyxml2::XMLElement *sceneManagerId = component->InsertNewChildElement("sceneManagerId");
    tinyxml2::XMLElement *sceneName = component->InsertNewChildElement("sceneName");

    sceneManagerId->SetText(sceneSwitcher.sceneManagerId.c_str());
    sceneName->SetText(sceneSwitcher.sceneName.c_str());
}

void XMLHandler::SaveSprite(tinyxml2::XMLElement *components, const Sprite sprite)
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

void XMLHandler::SaveTextLabel(tinyxml2::XMLElement *components, const TextLabel textLabel)
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

void XMLHandler::SaveTransform(tinyxml2::XMLElement *components, const Transform transform)
{
    tinyxml2::XMLElement *component = components->InsertNewChildElement("component");
    component->SetAttribute("type", "Transform");

    tinyxml2::XMLElement *position = component->InsertNewChildElement("position");
    tinyxml2::XMLElement *positionX = position->InsertNewChildElement("x");
    tinyxml2::XMLElement *positionY = position->InsertNewChildElement("y");

    positionX->SetText(transform.position.x);
    positionY->SetText(transform.position.y);

    tinyxml2::XMLElement *scale = component->InsertNewChildElement("scale");
    tinyxml2::XMLElement *scaleX = scale->InsertNewChildElement("x");
    tinyxml2::XMLElement *scaleY = scale->InsertNewChildElement("y");

    scaleX->SetText(transform.scale.x / SCALE);
    scaleY->SetText(transform.scale.y / SCALE);

    tinyxml2::XMLElement *rotation = component->InsertNewChildElement("rotation");

    rotation->SetText(transform.rotation);
}

void XMLHandler::SaveVelocity(tinyxml2::XMLElement *components, const Velocity velocity)
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

void XMLHandler::SaveTags(tinyxml2::XMLElement *components, const std::shared_ptr<entt::registry> registry, const entt::entity entity)
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

void XMLHandler::LoadTags(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component)
{
    for (tinyxml2::XMLElement *tag = component->FirstChildElement("tag");
         tag != NULL;
         tag = tag->NextSiblingElement())
    {
        std::string tagName = tag->FirstChild()->ToText()->Value();

        if (tagName == "Player_Tag")
        {
            registry->emplace<Player_Tag>(entity);
        }
        else if (tagName == "Enemy_Tag")
        {
            registry->emplace<Enemy_Tag>(entity);
        }
        else if (tagName == "Obstacle_Tag")
        {
            registry->emplace<Obstacle_Tag>(entity);
        }
        else if (tagName == "KeyboardControlled_Tag")
        {
            registry->emplace<KeyboardControlled_Tag>(entity);
        }
        else if (tagName == "Projectile_Tag")
        {
            registry->emplace<Projectile_Tag>(entity);
        }
        else if (tagName == "StayOnMap_Tag")
        {
            registry->emplace<StayOnMap_Tag>(entity);
        }
        else if (tagName == "Trigger_Tag")
        {
            registry->emplace<Trigger_Tag>(entity);
        }
        else if (tagName == "Airborne_Tag")
        {
            registry->emplace<Airborne_Tag>(entity);
        }
        else if (tagName == "Effect_Tag")
        {
            registry->emplace<Effect_Tag>(entity);
        }
        else if (tagName == "UI_Tag")
        {
            registry->emplace<UI_Tag>(entity);
        }
    }
}

void XMLHandler::LoadAnimation(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component)
{
    tinyxml2::XMLElement *numFramesElement = component->FirstChildElement("numFrames");
    tinyxml2::XMLElement *frameRateSpeedElement = component->FirstChildElement("frameRateSpeed");
    tinyxml2::XMLElement *isLoopElement = component->FirstChildElement("isLoop");
    tinyxml2::XMLElement *hasDirectionElement = component->FirstChildElement("hasDirections");

    std::string numFrames_str = numFramesElement->FirstChild()->ToText()->Value();
    std::string frameRateSpeed_str = frameRateSpeedElement->FirstChild()->ToText()->Value();
    std::string isLoop_str = isLoopElement->FirstChild()->ToText()->Value();
    std::string hasDirections_str = hasDirectionElement->FirstChild()->ToText()->Value();

    int numFrames = std::stoi(numFrames_str);
    int frameRateSpeed = std::stoi(frameRateSpeed_str);
    bool isLoop = (isLoop_str == "true");
    bool hasDirections = (hasDirections_str == "true");

    registry->emplace<Animation>(entity, numFrames, frameRateSpeed, isLoop, hasDirections);
}

void XMLHandler::LoadBoxCollider(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component)
{
    tinyxml2::XMLElement *widthElement = component->FirstChildElement("width");
    tinyxml2::XMLElement *heightElement = component->FirstChildElement("height");

    tinyxml2::XMLElement *offsetElement = component->FirstChildElement("offset");
    tinyxml2::XMLElement *offsetXElement = offsetElement->FirstChildElement("x");
    tinyxml2::XMLElement *offsetYElement = offsetElement->FirstChildElement("y");

    std::string width_str = widthElement->FirstChild()->ToText()->Value();
    std::string height_str = heightElement->FirstChild()->ToText()->Value();
    std::string offsetX_str = offsetXElement->FirstChild()->ToText()->Value();
    std::string offsetY_str = offsetYElement->FirstChild()->ToText()->Value();

    int width = std::stoi(width_str);
    int height = std::stoi(height_str);
    vec2f offset = vec2f(std::stof(offsetX_str), std::stof(offsetY_str));

    registry->emplace<BoxCollider>(entity, width, height, offset);
}

void XMLHandler::LoadCircleCollider(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component)
{
    tinyxml2::XMLElement *radiusElement = component->FirstChildElement("radius");
    tinyxml2::XMLElement *offsetElement = component->FirstChildElement("offset");
    tinyxml2::XMLElement *offsetXElement = offsetElement->FirstChildElement("x");
    tinyxml2::XMLElement *offsetYElement = offsetElement->FirstChildElement("y");

    std::string radius_str = radiusElement->FirstChild()->ToText()->Value();
    std::string offsetX_str = offsetXElement->FirstChild()->ToText()->Value();
    std::string offsetY_str = offsetYElement->FirstChild()->ToText()->Value();

    int radius = std::stoi(radius_str);
    vec2f offset = vec2f(std::stof(offsetX_str), std::stof(offsetY_str));

    registry->emplace<CircleCollider>(entity, radius, offset);
}

void XMLHandler::LoadHealth(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component)
{
    tinyxml2::XMLElement *healthElement = component->FirstChildElement("hitPoints");
    std::string health_str = healthElement->FirstChild()->ToText()->Value();
    int hitPoints = std::stoi(health_str);
    registry->emplace<Health>(entity, hitPoints);
}

void XMLHandler::LoadMenuNavigator(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component)
{
    tinyxml2::XMLElement *numRowsElement = component->FirstChildElement("numRows");
    tinyxml2::XMLElement *rowDistanceElement = component->FirstChildElement("rowDistance");
    tinyxml2::XMLElement *atRowElement = component->FirstChildElement("atRow");

    std::string numRows_str = numRowsElement->FirstChild()->ToText()->Value();
    std::string rowDistance_str = rowDistanceElement->FirstChild()->ToText()->Value();
    std::string atRow_str = atRowElement->FirstChild()->ToText()->Value();

    int numRows = std::stoi(numRows_str);
    int rowDistance = std::stoi(rowDistance_str);
    int atRow = std::stoi(atRow_str);

    registry->emplace<MenuNavigator>(entity, numRows, rowDistance, atRow);
}
void XMLHandler::LoadProjectile(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component)
{
}
void XMLHandler::LoadProjectileEmitter(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component)
{
    tinyxml2::XMLElement *speedElement = component->FirstChildElement("speed");
    tinyxml2::XMLElement *directionElement = component->FirstChildElement("direction");
    tinyxml2::XMLElement *directionXElement = directionElement->FirstChildElement("x");
    tinyxml2::XMLElement *directionYElement = directionElement->FirstChildElement("y");

    tinyxml2::XMLElement *durationElement = component->FirstChildElement("duration");
    tinyxml2::XMLElement *isFriendlyElement = component->FirstChildElement("isFriendly");
    tinyxml2::XMLElement *repeatFrequencyElement = component->FirstChildElement("repeatFrequency");
    tinyxml2::XMLElement *hitPercentDamageElement = component->FirstChildElement("hitPercentDamage");
    tinyxml2::XMLElement *inheritDirectionElement = component->FirstChildElement("inheritDirection");

    std::string speed_str = speedElement->FirstChild()->ToText()->Value();
    std::string directionX_str = directionXElement->FirstChild()->ToText()->Value();
    std::string directionY_str = directionYElement->FirstChild()->ToText()->Value();

    std::string duration_str = durationElement->FirstChild()->ToText()->Value();
    std::string isFriendly_str = isFriendlyElement->FirstChild()->ToText()->Value();
    std::string repeatFrequency_str = repeatFrequencyElement->FirstChild()->ToText()->Value();
    std::string hitPercentDamage_str = hitPercentDamageElement->FirstChild()->ToText()->Value();
    std::string inheritDirection_str = inheritDirectionElement->FirstChild()->ToText()->Value();

    double speed = std::stod(speed_str);
    vec2f direction = vec2f(std::stof(directionX_str), std::stof(directionY_str));
    int repeatFrequency = std::stoi(repeatFrequency_str);
    int duration = std::stoi(duration_str);
    int hitPercentDamage = std::stoi(hitPercentDamage_str);
    bool isFriendly = (isFriendly_str == "true");
    bool inheritDirection = (inheritDirection_str == "true");

    registry->emplace<ProjectileEmitter>(entity,
                                         speed,
                                         direction,
                                         repeatFrequency,
                                         duration,
                                         hitPercentDamage,
                                         isFriendly,
                                         inheritDirection);
}
void XMLHandler::LoadSceneSwitcher(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component)
{
    tinyxml2::XMLElement *sceneManagerIdElement = component->FirstChildElement("sceneManagerId");
    tinyxml2::XMLElement *sceneNameElement = component->FirstChildElement("sceneName");

    std::string sceneManagerId = sceneManagerIdElement->FirstChild()->ToText()->Value();
    std::string sceneName = sceneNameElement->FirstChild()->ToText()->Value();

    registry->emplace<SceneSwitcher>(entity, sceneManagerId, sceneName);
}
void XMLHandler::LoadSprite(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component)
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
void XMLHandler::LoadTextLabel(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component)
{
    tinyxml2::XMLElement *positionElement = component->FirstChildElement("position");
    tinyxml2::XMLElement *positionXElement = positionElement->FirstChildElement("x");
    tinyxml2::XMLElement *positionYElement = positionElement->FirstChildElement("y");
    tinyxml2::XMLElement *textElement = component->FirstChildElement("text");
    tinyxml2::XMLElement *assetIdElement = component->FirstChildElement("assetId");
    tinyxml2::XMLElement *colorElement = component->FirstChildElement("color");
    tinyxml2::XMLElement *colorRElement = colorElement->FirstChildElement("r");
    tinyxml2::XMLElement *colorGElement = colorElement->FirstChildElement("g");
    tinyxml2::XMLElement *colorBElement = colorElement->FirstChildElement("b");
    tinyxml2::XMLElement *isFixedElement = component->FirstChildElement("isFixed");

    std::string positionX_str = positionXElement->FirstChild()->ToText()->Value();
    std::string positionY_str = positionYElement->FirstChild()->ToText()->Value();
    std::string text = textElement->FirstChild()->ToText()->Value();
    std::string assetId = assetIdElement->FirstChild()->ToText()->Value();
    std::string colorR_str = colorRElement->FirstChild()->ToText()->Value();
    std::string colorG_str = colorGElement->FirstChild()->ToText()->Value();
    std::string colorB_str = colorBElement->FirstChild()->ToText()->Value();
    std::string isFixed_str = isFixedElement->FirstChild()->ToText()->Value();

    vec2f position = vec2f(std::stof(positionX_str), std::stof(positionY_str));
    // std::string text // Done
    // std::string assetId // Done
    SDL_Color color = {(Uint8)std::stoi(colorR_str),
                       (Uint8)std::stoi(colorG_str),
                       (Uint8)std::stoi(colorB_str)};
    bool isFixed = (isFixed_str == "true");

    registry->emplace<TextLabel>(entity, position, text, assetId, color, isFixed);
}
void XMLHandler::LoadTransform(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component)
{
    tinyxml2::XMLElement *positionElement = component->FirstChildElement("position");
    tinyxml2::XMLElement *positionXElement = positionElement->FirstChildElement("x");
    tinyxml2::XMLElement *positionYElement = positionElement->FirstChildElement("y");
    tinyxml2::XMLElement *scaleElement = component->FirstChildElement("scale");
    tinyxml2::XMLElement *scaleXElement = scaleElement->FirstChildElement("x");
    tinyxml2::XMLElement *scaleYElement = scaleElement->FirstChildElement("y");
    tinyxml2::XMLElement *rotationElement = component->FirstChildElement("rotation");

    std::string positionX_str = positionXElement->FirstChild()->ToText()->Value();
    std::string positionY_str = positionYElement->FirstChild()->ToText()->Value();
    std::string scaleX_str = scaleXElement->FirstChild()->ToText()->Value();
    std::string scaleY_str = scaleYElement->FirstChild()->ToText()->Value();
    std::string rotation_str = rotationElement->FirstChild()->ToText()->Value();

    vec2f position = vec2f(std::stof(positionX_str), std::stof(positionY_str));
    vec2f scale = vec2f(std::stof(scaleX_str), std::stof(scaleY_str));
    double rotation = std::stof(rotation_str);

    registry->emplace<Transform>(entity, position, scale, rotation);
}
void XMLHandler::LoadVelocity(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component)
{
    tinyxml2::XMLElement *speedElement = component->FirstChildElement("speed");
    tinyxml2::XMLElement *directionElement = component->FirstChildElement("direction");
    tinyxml2::XMLElement *directionXElement = directionElement->FirstChildElement("x");
    tinyxml2::XMLElement *directionYElement = directionElement->FirstChildElement("y");

    tinyxml2::XMLElement *lastNonZeroDirectionElement = component->FirstChildElement("lastNonZeroDirection");
    tinyxml2::XMLElement *lastNonZeroDirectionXElement = lastNonZeroDirectionElement->FirstChildElement("x");
    tinyxml2::XMLElement *lastNonZeroDirectionYElement = lastNonZeroDirectionElement->FirstChildElement("y");

    std::string speed_str = speedElement->FirstChild()->ToText()->Value();
    std::string directionX_str = directionXElement->FirstChild()->ToText()->Value();
    std::string directionY_str = directionYElement->FirstChild()->ToText()->Value();
    std::string lastNonZeroDirectionX_str = lastNonZeroDirectionXElement->FirstChild()->ToText()->Value();
    std::string lastNonZeroDirectionY_str = lastNonZeroDirectionYElement->FirstChild()->ToText()->Value();

    double speed = std::stod(speed_str);
    vec2f direction = vec2f(std::stof(directionX_str), std::stof(directionY_str));
    vec2f lastNonZeroDirection = vec2f(std::stof(lastNonZeroDirectionX_str), std::stof(lastNonZeroDirectionY_str));

    registry->emplace<Velocity>(entity, speed, direction, lastNonZeroDirection);
}

void XMLHandler::LoadComponent(std::shared_ptr<entt::registry> registry, entt::entity entity, tinyxml2::XMLElement *component)
{
    std::string componentType = component->Attribute("type");
    if (componentType == "Animation")
    {
        LoadAnimation(registry, entity, component);
    }
    else if (componentType == "BoxCollider")
    {
        LoadBoxCollider(registry, entity, component);
    }
    else if (componentType == "CircleCollider")
    {
        LoadCircleCollider(registry, entity, component);
    }
    else if (componentType == "Health")
    {
        LoadHealth(registry, entity, component);
    }
    else if (componentType == "MenuNavigator")
    {
        LoadMenuNavigator(registry, entity, component);
    }
    else if (componentType == "Projectile")
    {
        LoadProjectile(registry, entity, component);
    }
    else if (componentType == "ProjectileEmitter")
    {
        LoadProjectileEmitter(registry, entity, component);
    }
    else if (componentType == "SceneSwitcher")
    {
        LoadSceneSwitcher(registry, entity, component);
    }
    else if (componentType == "Sprite")
    {
        LoadSprite(registry, entity, component);
    }
    else if (componentType == "Tags")
    {
        LoadTags(registry, entity, component);
    }
    else if (componentType == "TextLabel")
    {
        LoadTextLabel(registry, entity, component);
    }
    else if (componentType == "Transform")
    {
        LoadTransform(registry, entity, component);
    }
    else if (componentType == "Velocity")
    {
        LoadVelocity(registry, entity, component);
    }
    else
    {
        Logger::Error("Component from xml does not match any game component");
    }
}

std::pair<std::string, std::string> XMLHandler::GetMapInfoFromXML(std::string filename)
{
    if (!FileExists(filename))
    {
        Logger::Error("Could not load " + filename + ". No such file.");
        return std::pair(" - ", " - ");
    }

    const char *file = filename.c_str();
    tinyxml2::XMLDocument doc;
    doc.LoadFile(file);

    tinyxml2::XMLElement *root = doc.FirstChildElement("level");

    tinyxml2::XMLElement *tilemap = root->FirstChildElement("tilemap");
    tinyxml2::XMLElement *tilemapSpritesheet = tilemap->FirstChildElement("spritesheet");
    tinyxml2::XMLElement *tilemapLayout = tilemap->FirstChildElement("layout");

    std::string tilemapSpritesheet_str = tilemapSpritesheet->FirstChild()->ToText()->Value();
    std::string tilemapLayout_str = tilemapLayout->FirstChild()->ToText()->Value();

    return std::pair(tilemapSpritesheet_str, tilemapLayout_str);
}

void XMLHandler::LoadAssets(tinyxml2::XMLElement *root, SDL_Renderer *renderer, std::shared_ptr<AssetStore> assetStore)
{

    // Textures
    tinyxml2::XMLElement *textures = root->FirstChildElement("textures");
    Logger::Error("Got here");
    for (tinyxml2::XMLElement *texture = textures->FirstChildElement("texture");
         texture != NULL;
         texture = texture->NextSiblingElement())
    {
        Logger::Error("Iteration");
        tinyxml2::XMLElement *id = texture->FirstChildElement("id");
        tinyxml2::XMLElement *path = texture->FirstChildElement("path");
        std::string id_str = id->FirstChild()->ToText()->Value();
        std::string path_str = path->FirstChild()->ToText()->Value();
        assetStore->AddTexture(renderer, id_str, path_str);
    }

    // Fonts
    tinyxml2::XMLElement *fonts = root->FirstChildElement("fonts");
    for (tinyxml2::XMLElement *font = fonts->FirstChildElement("font");
         font != NULL;
         font = font->NextSiblingElement())
    {
        tinyxml2::XMLElement *id = font->FirstChildElement("id");
        tinyxml2::XMLElement *path = font->FirstChildElement("path");
        tinyxml2::XMLElement *size = font->FirstChildElement("size");
        std::string id_str = id->FirstChild()->ToText()->Value();
        std::string path_str = path->FirstChild()->ToText()->Value();
        std::string size_str = size->FirstChild()->ToText()->Value();
        assetStore->AddFont(id_str, path_str, stoi(size_str));
    }
}

void XMLHandler::LoadEntities(tinyxml2::XMLElement *root, std::shared_ptr<entt::registry> registry, std::shared_ptr<AssetStore> assetStore)
{
    tinyxml2::XMLElement *entities = root->FirstChildElement("entities");
    for (tinyxml2::XMLElement *entity = entities->FirstChildElement("entity");
         entity != NULL;
         entity = entity->NextSiblingElement())
    {
        tinyxml2::XMLElement *components = entity->FirstChildElement("components");
        entt::entity newEntity = registry->create();
        for (tinyxml2::XMLElement *component = components->FirstChildElement("component");
             component != NULL;
             component = component->NextSiblingElement())
        {
            LoadComponent(registry, newEntity, component);
        }
    }
}

void XMLHandler::LoadFromXML(std::shared_ptr<entt::registry> registry, SDL_Renderer *renderer, std::shared_ptr<AssetStore> assetStore, std::string filename)
{
    if (!FileExists(filename))
    {
        Logger::Error("Could not load " + filename + ". No such file.");
        return;
    }

    const char *file = filename.c_str();
    tinyxml2::XMLDocument doc;
    doc.LoadFile(file);
    tinyxml2::XMLElement *root = doc.FirstChildElement("level");

    LoadAssets(root, renderer, assetStore);

    LoadEntities(root, registry, assetStore);
}

void XMLHandler::SaveEntityToXML(const std::shared_ptr<entt::registry> registry, tinyxml2::XMLElement *entities, const entt::entity entity)
{
    if (registry->any_of<Player_Tag>(entity))
    {
        return; // Dont save player to xml
    }

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
                   { 
                    Logger::Info("Saving entity");
                    SaveEntityToXML(registry, entities, entity); });

    root->InsertEndChild(entities);
    tinyxml2::XMLError result = doc.SaveFile("SavedData.xml");
}
