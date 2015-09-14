#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vrt.h"
#include "cache/cache.h"
#include "vcc_if.h"

typedef struct timersConfig {
  int multiplier;             // To go from seconds -> milli, micro or nanoseconds
} config_t;

int init_function(struct vmod_priv *priv, const struct VCL_conf *conf)
{
  config_t *cfg;
  cfg             = malloc(sizeof(config_t));
  cfg->multiplier = 1000;     // default to milliseconds

  priv->priv      = cfg;
  return (0);
}

VCL_VOID vmod_unit(const struct vrt_ctx *ctx, struct vmod_priv *priv, const char *unit) {
    config_t *cfg   = priv->priv;

    cfg->multiplier =
        strcasecmp( unit, "seconds"      ) == 0 ? 1                     :
        strcasecmp( unit, "milliseconds" ) == 0 ? 1000                  :
        strcasecmp( unit, "microseconds" ) == 0 ? 1000 * 1000           :
        strcasecmp( unit, "nanoseconds"  ) == 0 ? 1000 * 1000 * 1000    :
        1000;   // default back to milliseconds if you gave us garbage.
}

// Returns the end of request reading, which is the start of request processing.
VCL_TIME vmod_req_start(const struct vrt_ctx *ctx) {
	return ctx->req->t_req;
}

VCL_INT vmod_duration2int(const struct vrt_ctx *ctx, VCL_DURATION dur, VCL_INT mult) {
	return dur * mult;
}

// Returns time in miliseconds from delegation to backend to first byte from backend
VCL_INT vmod_req_response_time(const struct vrt_ctx *ctx, struct vmod_priv *priv) {
  config_t *cfg   = priv->priv;

  return (int) ((ctx->req->t_prev - ctx->req->t_first) * cfg->multiplier);
}
