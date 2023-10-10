/*
 * testBalancer.cpp
 *
 * Unit tests for Balancer class
 *
 *  Created on: June 4, 2019
 *      Author: zeil
 */

#include "balancer.h"

#include <vector>
#include <string>

#include "unittest.h"


using namespace std;




UnitTest (BalancerDefaultConstructor) {
	Balancer bal;

	assertThat (bal.status(), is(1));
}

UnitTest (BalancerOneSingleton) {
	Balancer bal;

	bal.tag("<img src='foo.png' aligh='right'/>");
	assertThat (bal.status(), is(1));
}

UnitTest (BalancerOneOpener) {
	Balancer bal;

	bal.tag("<div class='title'>");
	assertThat (bal.status(), is(0));
}

UnitTest (BalancerOneCloser) {
	Balancer bal;

	bal.tag("</div>");
	assertThat (bal.status(), is(-1));
}

UnitTest (BalancerSimpleMismatch) {
	Balancer bal;

	bal.tag("<a>");
	assertThat (bal.status(), is(0));
	bal.tag("<b />");
	assertThat (bal.status(), is(0));
	bal.tag("</A>");
	assertThat (bal.status(), is(-1));
}


UnitTest (BalancerAlternation) {
	Balancer bal;

	for (int i = 0; i < 12; ++i) {
		if (i % 2 == 0) {
			bal.tag("<a>");
		} else {
			bal.tag("<b>");
		}
		assertThat(bal.status(), is(0));

		bal.tag("<a/>");
		assertThat(bal.status(), is(0));

		bal.tag("<b/>");
		assertThat(bal.status(), is(0));

		if (i % 2 == 0) {
			bal.tag("</a>");
		} else {
			bal.tag("</b>");
		}
		assertThat(bal.status(), is(1));
	}
	bal.tag("</a>");
	assertThat(bal.status(), is(-1));
}



UnitTest (BalancerNesting) {
	Balancer bal;

	for (int i = 0; i < 12; ++i) {
		if (i % 2 == 0) {
			bal.tag("<a>");
		} else {
			bal.tag("<b>");
		}
		assertThat(bal.status(), is(0));

		bal.tag("<a/>");
		assertThat(bal.status(), is(0));

		bal.tag("<b/>");
		assertThat(bal.status(), is(0));
	}


	for (int i = 0; i < 12; ++i) {
		bal.tag("<a/>");
		assertThat(bal.status(), is(0));

		bal.tag("<b/>");
		assertThat(bal.status(), is(0));

		if (i % 2 == 0) {
			bal.tag("</b>");
		} else {
			bal.tag("</a>");
		}
		int expected = (i < 11) ? 0 : 1;
		assertThat(bal.status(), is(expected));
	}
	bal.tag("</a>");
	assertThat(bal.status(), is(-1));
}

UnitTest (BalancerMixed) {
	Balancer bal;
	for (int k = 0; k < 4; ++k) {
		bal.tag("<a img=\"whatever.gif\">");
	}
	for (int k = 0; k < 2; ++k) {
		for (int i = 0; i < 12; ++i) {
			if (i % 2 == 0) {
				bal.tag("<a>");
			} else {
				bal.tag("<b>");
			}
			assertThat(bal.status(), is(0));

			bal.tag("<a/>");
			assertThat(bal.status(), is(0));

			bal.tag("<b/>");
			assertThat(bal.status(), is(0));
		}


		for (int i = 0; i < 12; ++i) {
			bal.tag("<a/>");
			assertThat(bal.status(), is(0));

			bal.tag("<b/>");
			assertThat(bal.status(), is(0));

			if (i % 2 == 0) {
				bal.tag("</b>");
			} else {
				bal.tag("</a>");
			}
			assertThat(bal.status(), is(0));
		}
	}
	for (int k = 0; k < 4; ++k) {
		bal.tag("</a>");
	}
	assertThat(bal.status(), is(1));
}
