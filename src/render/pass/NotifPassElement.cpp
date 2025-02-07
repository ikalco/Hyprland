#include "NotifPassElement.hpp"
#include "../OpenGL.hpp"

#include <hyprutils/utils/ScopeGuard.hpp>
using namespace Hyprutils::Utils;

CNotifPassElement::CNotifPassElement(const CNotifPassElement::SRenderData& data_) : data(data_) {
    ;
}

void CNotifPassElement::draw(const CRegion& damage) {
    for (const auto& notif : data.notifs) {
        if (notif.lagRect.w <= 0 || notif.lagRect.h <= 0 || notif.backRect.w <= 0 || notif.backRect.h <= 0 || notif.gradientRect.w <= 0 || notif.gradientRect.h <= 0 ||
            notif.loadingRect.w <= 0 || notif.loadingRect.h <= 0)
            continue;
        g_pHyprOpenGL->renderRectWithDamage(notif.lagRect, notif.color, damage, 0, 2.0f);
        g_pHyprOpenGL->renderRectWithDamage(notif.backRect, CHyprColor(0.f, 0.f, 0.f, 1.f), damage, 0, 2.0f);
        g_pHyprOpenGL->renderRectWithDamage(notif.loadingRect, notif.color, damage, 0, 2.0f);
        g_pHyprOpenGL->renderRectWithDamage(notif.gradientRect, notif.iconColor.modifyA(0.333f), damage, 0, 2.0f /* , notif.iconColor.modifyA(0.f) */);
    }
    g_pHyprOpenGL->renderTextureInternalWithDamage(data.tex, data.texBox, 1.f, damage, 0, 2.0f);
    g_pHyprOpenGL->m_RenderData.clipBox = {};
}

bool CNotifPassElement::needsLiveBlur() {
    return false; // TODO?
}

bool CNotifPassElement::needsPrecomputeBlur() {
    return false; // TODO?
}

std::optional<CBox> CNotifPassElement::boundingBox() {
    // damage is fit around all notif stuff
    return data.texBox.copy().scale(1.F / g_pHyprOpenGL->m_RenderData.pMonitor->scale).round();
}

CRegion CNotifPassElement::opaqueRegion() {
    return {}; // TODO:
}

void CNotifPassElement::discard() {
    ;
}
