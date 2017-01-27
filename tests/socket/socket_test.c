/*
 * (C) 2017 by Harald Welte <laforge@gnumonks.org>
 * All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <osmocom/core/utils.h>
#include <osmocom/core/socket.h>

#include "../config.h"

static int test_sockinit(void)
{
	int fd, rc;
	char *name;

	printf("Checking osmo_sock_init() with bind to a random local UDP port\n");
	fd = osmo_sock_init(AF_INET, SOCK_DGRAM, IPPROTO_UDP,
			    "0.0.0.0", 0, OSMO_SOCK_F_BIND);
	OSMO_ASSERT(fd >= 0);
	name = osmo_sock_get_name(NULL, fd);
	/* expect it to be not connected. We cannot match on INADDR_ANY,
	 * as apparently that won't work on FreeBSD if there's only one
	 * address (e.g. 127.0.0.1) assigned to the entire system, like
	 * the Osmocom FreeBSD build slaves */
	OSMO_ASSERT(!strncmp(name, "(NULL<->", 7));
	talloc_free(name);
	/* expect it to be blocking */
	rc = fcntl(fd, F_GETFL);
	OSMO_ASSERT(!(rc & O_NONBLOCK));
	close(fd);

	printf("Checking for OSMO_SOCK_F_NONBLOCK\n");
	fd = osmo_sock_init(AF_INET, SOCK_DGRAM, IPPROTO_UDP,
			    "0.0.0.0", 0, OSMO_SOCK_F_BIND|OSMO_SOCK_F_NONBLOCK);
	OSMO_ASSERT(fd >= 0);
	/* expect it to be blocking */
	rc = fcntl(fd, F_GETFL);
	OSMO_ASSERT(rc & O_NONBLOCK);
	close(fd);

	printf("Checking for invalid flags\n");
	fd = osmo_sock_init(AF_INET, SOCK_DGRAM, IPPROTO_UDP,
			    "0.0.0.0", 0, OSMO_SOCK_F_BIND|OSMO_SOCK_F_CONNECT);
	OSMO_ASSERT(fd < 0);

	return 0;
}

int main(int argc, char *argv[])
{
	test_sockinit();
	return 0;
}
