#include "cbase.h"
#include "hudelement.h"
#include "hud_numericdisplay.h"
#include "iclientmode.h"

#include <vgui_controls/Panel.h>
#include <vgui/ISurface.h>
#include <vgui/ILocalize.h>

using namespace vgui;

static ConVar bla_speedmeter("bla_speedmeter", "1", 
                             FCVAR_CLIENTDLL | FCVAR_ARCHIVE | FCVAR_DEMO, 
                             "Turn the speedmeter on/off");

class CHudSpeedMeter : public CHudElement, public CHudNumericDisplay
{
    DECLARE_CLASS_SIMPLE(CHudSpeedMeter, CHudNumericDisplay);

public:
    CHudSpeedMeter(const char *pElementName);
    virtual void Init()
    {
        Reset();
    }
    virtual void VidInit()
    {
        Reset();
    }
    virtual void Reset()
    {
        SetLabelText(L"UPS");
        SetDisplayValue(0);
    }
    virtual bool ShouldDraw()
    {
        return bla_speedmeter.GetBool() && CHudElement::ShouldDraw();
    }
    virtual void OnThink();
};

DECLARE_HUDELEMENT(CHudSpeedMeter);

CHudSpeedMeter::CHudSpeedMeter(const char *pElementName) :
    CHudElement(pElementName), CHudNumericDisplay(NULL, "HudSpeedmeter")
{
    SetParent(g_pClientMode->GetViewport());
    SetHiddenBits(HIDEHUD_PLAYERDEAD);
}

void CHudSpeedMeter::OnThink()
{
    Vector velocity(0, 0, 0);
    C_BasePlayer *player = C_BasePlayer::GetLocalPlayer();
    if (player)
        velocity = player->GetLocalVelocity();
    SetDisplayValue((int)velocity.Length());
}
