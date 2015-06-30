#include <string.h>
#include <netinet/ip6.h>
#include "dhcp6.h"
#include "l2tpns.h"
#include "plugin.h"

/* strip domain part of username before sending RADIUS requests */

int plugin_api_version = PLUGIN_API_VERSION;
static struct pluginfuncs *f = 0;

int plugin_pre_auth(struct param_pre_auth *data)
{
    char *p;

    if (!data->continue_auth) return PLUGIN_RET_STOP;

    // Strip off @domain
    if ((p = strchr(data->username, '@')))
    {
	f->log(3, 0, 0, "Stripping off trailing domain name \"%s\"\n", p);
	*p = 0;
    }

    return PLUGIN_RET_OK;
}

int plugin_init(struct pluginfuncs *funcs)
{
    return ((f = funcs)) ? 1 : 0;
}
