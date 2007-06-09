/*
 * Copyright (c) 2006-2007 Bjorn Andersson <flex@kryo.se>, Erik Ekman <yarrick@kryo.se>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "encoding.h"
#include "base64.h"
#include "test.h"

static struct tuple
{
	char *a;
	char *b;
} testpairs[] = {
	{ "iodinetestingtesting", "Aw8KAw4LDgvZDgLUz2rLC2rPBMC" },
	{ "abc123", "ywjJmtiZ" },
	{ NULL, NULL }	
};

START_TEST(test_base64_encode)
{
	size_t len;
	char buf[4096];
	int val;
	int i;

	for (i = 0; testpairs[i].a != NULL; i++) {
		len = sizeof(buf);
		val = base64_encode(buf, &len, testpairs[i].a, strlen(testpairs[i].a));

		fail_unless(val > 0, strerror(errno));
		fail_unless(strcmp(buf, testpairs[i].b) == 0, 
				va_str("'%s' != '%s'", buf, testpairs[i].b));
	}
}
END_TEST

START_TEST(test_base64_decode)
{
	size_t len;
	char buf[4096];
	int val;
	int i;

	for (i = 0; testpairs[i].a != NULL; i++) {
		len = sizeof(buf);
		val = base64_decode(buf, &len, testpairs[i].b, strlen(testpairs[i].b));

		fail_unless(val > 0, strerror(errno));
		fail_unless(buf != NULL, "buf == NULL");
		fail_unless(strcmp(buf, testpairs[i].a) == 0, 
				va_str("'%s' != '%s'", buf, testpairs[i].a));
	}
}
END_TEST

TCase *
test_base64_create_tests()
{
	TCase *tc;

	tc = tcase_create("Base64");
	tcase_add_test(tc, test_base64_encode);
	tcase_add_test(tc, test_base64_decode);

	return tc;
}
