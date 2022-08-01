#pragma once

#include "integrator.h"

namespace psdr
{

PSDR_CLASS_DECL_BEGIN(DirectIntegrator, final, Integrator)
public:
    DirectIntegrator(int bsdf_samples = 1, int light_samples = 1);
    virtual ~DirectIntegrator();

    void preprocess_secondary_edges(const Scene &scene, int sensor_id, const ScalarVector4i &reso, int nrounds = 1) override;

    bool m_hide_emitters = false;

protected:
    SpectrumC Li(const Scene &scene, Sampler &sampler, const RayC &ray, MaskC active = true, int sensor_id=0) const override;
    SpectrumD Li(const Scene &scene, Sampler &sampler, const RayD &ray, MaskD active = true, int sensor_id=0) const override;

    
    IntC _compress(IntC input, MaskC mask) const;

    template <bool ad>
    Spectrum<ad> __Li(const Scene &scene, Sampler &sampler, const Ray<ad> &ray, Mask<ad> active) const;

    void render_secondary_edges(const Scene &scene, int sensor_id, SpectrumD &result) const override;

    template <bool ad>
    std::pair<IntC, Spectrum<ad>> eval_secondary_edge(const Scene &scene, const Sensor &sensor, const Vector3fC &sample3) const;

    template <bool ad>
    void eval_secondary_edge_bssrdf(const Scene &scene, const IntersectionC &its, const Sensor &sensor, const Vector3fC &sample3, SpectrumD &result) const;

    int m_bsdf_samples, m_light_samples;
    std::vector<HyperCubeDistribution3f*> m_warpper;
PSDR_CLASS_DECL_END(DirectIntegrator)

} // namespace psdr
