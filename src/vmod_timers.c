#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cache/cache.h>
#include <vcl.h>
#include <vcc_if.h>

typedef struct timersConfig
{
  int multiplier; // To go from seconds -> milli, micro or nanoseconds
} config_t;

int vmod_event_function(VRT_CTX, struct vmod_priv *priv, enum vcl_event_e e)
{
  if (e != VCL_EVENT_LOAD)
    return (0);

  config_t *cfg;
  cfg = malloc(sizeof(config_t));
  cfg->multiplier = 1000; // default to milliseconds

  priv->priv = cfg;
  return (0);
}

VCL_VOID vmod_unit(VRT_CTX, struct vmod_priv *priv, const char *unit)
{
  config_t *cfg = priv->priv;

  cfg->multiplier =
      strcasecmp(unit, "seconds") == 0 ? 1 : strcasecmp(unit, "milliseconds") == 0 ? 1000 : strcasecmp(unit, "microseconds") == 0 ? 1000 * 1000 : strcasecmp(unit, "nanoseconds") == 0 ? 1000 * 1000 * 1000 : 1000; // default back to milliseconds if you gave us garbage.
}

// Returns the end of request reading, which is the start of request processing.
VCL_TIME vmod_req_start(VRT_CTX)
{
  return ctx->req->t_req;
}

VCL_INT vmod_duration2int(VRT_CTX, VCL_DURATION dur, VCL_INT mult)
{
  return dur * mult;
}

// Returns time in miliseconds from delegation to backend to first byte from backend
VCL_INT vmod_req_response_time(VRT_CTX, struct vmod_priv *priv)
{
  config_t *cfg = priv->priv;

  return (int)((ctx->req->t_prev - ctx->req->t_first) * cfg->multiplier);
}
