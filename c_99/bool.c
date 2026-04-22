#include <stdio.h>
#include <stdbool.h>

int main() {
	_Bool is_today_a_good_day = 1;

	if (is_today_a_good_day)
		printf("Today is a good day :)\n");

	bool is_today_also_a_good_day = true;

	if (is_today_also_a_good_day)
		printf("Today is also a good day :)\n");
}
