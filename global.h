/*
 * Copyright 2010-2011 Brian Uechi <buasst@gmail.com>
 *
 * This file is part of mochad.
 *
 * mochad is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * mochad is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with mochad.  If not, see <http://www.gnu.org/licenses/>.
 */

struct SecEventRec {
    unsigned char funct;
    const char *name;
};

int Cm19a;
int PollTimeOut;

/* 1 bit per house code, 1=RF to PL, 0=off, default all house codes on */
unsigned short RfToPl16;

unsigned short RfToRf16;


#define dbprintf(fmt, ...) _dbprintf(fmt, __FILE__,__LINE__, ## __VA_ARGS__)
int _dbprintf(const char *fmt, ...);

int write_usb(unsigned char *buf, size_t len);

int statusprintf(int fd, const char *fmt, ...);
int sockprintf(int fd, const char *fmt, ...);
int sockprintf_json(int fd, const char *command, const char *fmt, ...);

void hexdump(void *p, size_t len);

void sockhexdump(int fd, void *p, size_t len);

void mh_sockhexdump(int fd, void *p, size_t len);

int or20client(int fd);

int del_client(int fd);

struct client *client_find(int fd);
void client_add(int fd);

#define OFMT_NONE       (0)
#define OFMT_NORMAL     (1)
#define OFMT_NORMALRAW  (2)
#define OFMT_JSON       (3)

#define IFMT_NORMAL      (0)
#define IFMT_XML         (1)
#define IFMT_OPEN_REMOTE (2)

/* Client sockets */
#include <poll.h>
#include "uthash.h"
struct client {
    int fd;               /* we'll use this field as the key */
    int ofmt;             /* Output format */
    int ifmt;             /* Input format */
    struct pollfd pollfd; 
    UT_hash_handle hh; /* makes this structure hashable */
};
