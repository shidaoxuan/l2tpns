#include <string.h>
#include <netinet/ip6.h>
#include "dhcp6.h"
#include "l2tpns.h"
#include "plugin.h"

/* fudge up session rx speed if not set */

int plugin_api_version = PLUGIN_API_VERSION;
static struct pluginfuncs *f = 0;

int plugin_post_auth(struct param_post_auth *data)
{
    if (!data->auth_allowed)
    	return PLUGIN_RET_OK;

    if (data->s->rx_connect_speed)
    	return PLUGIN_RET_OK;

    switch (data->s->tx_connect_speed)
    {
    case 256:
	data->s->rx_connect_speed = 64;
	break;

    case 512:
	data->s->rx_connect_speed = 128;
	break;

    case 1500:
	data->s->rx_connect_speed = 256;
	break;
    }

    return PLUGIN_RET_OK;
}

int plugin_init(struct pluginfuncs *funcs)
{
    return ((f = funcs)) ? 1 : 0;
}
