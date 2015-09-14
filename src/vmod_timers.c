#include "vrt.h"
#include "cache/cache.h"
#include "vcc_if.h"

// Returns the end of request reading, which is the start of request processing.
VCL_TIME vmod_req_start(const struct vrt_ctx *ctx) {
	return ctx->req->t_req;
}

VCL_INT vmod_duration2int(const struct vrt_ctx *ctx, VCL_DURATION dur, VCL_INT mult) {
	return dur * mult;
}
