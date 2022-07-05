#include "Options.hpp"
#include "Constants.hpp"
#include "scenes/SceneManager.hpp"

bool OptionsScene::Update(double elapsedTime)
{
    if (m_VolumeActive)
    {
        LeftMenu();
    }
    else
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                m_keep_playing = false;
                break;
            case SDL_KEYDOWN:

                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    if (m_menuPos.y > 0)
                        m_menuPos.y--;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    if (m_menuPos.y < 1)
                        m_menuPos.y++;
                    break;
                case SDL_SCANCODE_KP_ENTER:
                case SDL_SCANCODE_RETURN:
                    switch (m_menuPos.y)
                    {
                    case 0: // Volume
                    {
                        m_VolumeActive = true;
                        break;
                    }
                    case 1: // exit options
                    {
                        m_localSceneManager.QueueSceneChange("MAINMENU");
                        break;
                    }
                    }
                    break;
                case SDL_SCANCODE_ESCAPE:
                    m_localSceneManager.QueueSceneChange("MAINMENU");
                }
            }
        }
        m_pointerPixel.x = (SCREENWIDTH - m_setVolumeTexture->width()) / 2 - 2 * m_pointerTexture->width();
        m_pointerPixel.y = SCREENHEIGHT / 2 - m_setVolumeTexture->height() + m_setVolumeTexture->height() * m_menuPos.y;
    }
    return m_keep_playing;
}

void OptionsScene::LeftMenu()
{
    int volume = Mix_VolumeMusic(-1);
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_keep_playing = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                g_sfx.SetMusicVol(volume + 16);
                if (volume > MIX_MAX_VOLUME)
                    volume = MIX_MAX_VOLUME;
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                g_sfx.SetMusicVol(volume - 16);
                if (volume < 0)
                    volume = 0;
                break;
            case SDL_SCANCODE_KP_ENTER:
            case SDL_SCANCODE_RETURN:
                m_VolumeActive = false;
                orgVolume = volume;
                break;
            case SDL_SCANCODE_ESCAPE:
                g_sfx.SetMusicVol(orgVolume);
                volume = orgVolume;
                m_VolumeActive = false;
                break;
            }
        }
    }
    m_pointerPixel.x = (SCREENWIDTH - m_setVolumeTexture->width()) / 2 + (m_setVolumeTexture->width() * 1.4);
    m_pointerPixel.y = (SCREENHEIGHT / 2) - (m_setVolumeTexture->height() * 2) + m_lineTexture->height() - m_pointerTexture->height() / 2 - volume;
}

void OptionsScene::RenderGraphics(double elapsedTime)
{

    g_gfx.ResetRenderArea();
    g_gfx.RenderRaw(*m_setVolumeTexture, m_setVolumePixel);
    g_gfx.RenderRaw(*m_optionsTexture, m_optionsPixel);
    g_gfx.RenderRaw(*m_lineTexture, m_linePixel);
    g_gfx.RenderRaw(*m_pointerTexture, m_pointerPixel);
    g_gfx.RenderBuffer();
}

void OptionsScene::Load()
{
    // Sound stuff
    int orgVolume = Mix_VolumeMusic(-1);
    // Font Stuff
}

void OptionsScene::Unload()
{
}

OptionsScene::OptionsScene(SceneManager &sceneManager, SceneManager &localSceneManager)
    : Scene(sceneManager),
      m_localSceneManager(localSceneManager),
	  m_setVolumeTexture(g_gfx.RequestTexture("Set Volume", m_fontSize, m_color)),
	  m_optionsTexture(g_gfx.RequestTexture("Exit Options", m_fontSize, m_color)),
	  m_pointerTexture(g_gfx.RequestTexture("assets/sprites/misc/smiley.png", 1, 1)),
	  m_lineTexture(g_gfx.RequestTexture("assets/sprites/menu/line.png", 1, 1))

{
    m_setVolumePixel.x = (SCREENWIDTH - m_setVolumeTexture->width()) / 2;
	m_setVolumePixel.y = SCREENHEIGHT / 2 - m_setVolumeTexture->height();

    m_optionsPixel.x = (SCREENWIDTH - m_setVolumeTexture->width()) / 2;
    m_optionsPixel.y = SCREENHEIGHT / 2;

    m_pointerPixel.x = (SCREENWIDTH - m_setVolumeTexture->width()) / 2 - 2 * m_pointerTexture->width();
    m_pointerPixel.y = SCREENHEIGHT / 2 - m_setVolumeTexture->height();

    m_lineTexture->Scale(2.0f);
    m_linePixel.x = (SCREENWIDTH - m_setVolumeTexture->width()) / 2 + (m_setVolumeTexture->width() * 1.43);
    m_linePixel.y = SCREENHEIGHT / 2 - (m_setVolumeTexture->height() * 2);
}