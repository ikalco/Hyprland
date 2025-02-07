#pragma once
#include "PassElement.hpp"
#include <optional>

class CWLSurfaceResource;
class CTexture;
class CSyncTimeline;

class CNotifPassElement : public IPassElement {
  public:
    struct SNotifRenderData {
        CBox       backRect;
        CBox       lagRect;
        CBox       gradientRect;
        CBox       loadingRect;
        CHyprColor color;
        CHyprColor iconColor;
    };

    struct SRenderData {
        SP<CTexture> tex;
        CBox         texBox;
        // CBox                          damage;
        std::vector<SNotifRenderData> notifs;
    };

    CNotifPassElement(const SRenderData& data);
    virtual ~CNotifPassElement() = default;

    virtual void                draw(const CRegion& damage);
    virtual bool                needsLiveBlur();
    virtual bool                needsPrecomputeBlur();
    virtual std::optional<CBox> boundingBox();
    virtual CRegion             opaqueRegion();
    virtual void                discard();

    virtual const char*         passName() {
        return "CNotifPassElement";
    }

  private:
    SRenderData data;
};
