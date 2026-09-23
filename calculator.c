#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct Data {
	int n1;
	int n2;
	int result;
	char current_tier[32];
	int thinking_time;
	int verifying_time;
	int max_numbers;
	int coins;
};

void limit(struct Data *data) {
	if (data->result >= data->max_numbers) {
		printf("\nNumbers exceeding beyond current tier limit, please upgrade your tier\n");
		exit(0);
	}
}

void buy_coins(struct Data *data) {
	int coins_ordered;
	int custom_coins_order;
	int coins_to_add;
	int current_coins = 0;
	int coins_packages[] = {
		35, 85, 150, 350, 850, 1000
	};
	FILE *f;

	printf("You have %d coins\n", data->coins);
	printf("1. 35 Coins\n2. 85 Coins\n3. 150 Coins\n4. 350 Coins\n5. 850 Coins\n6. 1000 Coins\n7. Custom\n");

	printf("[Select Coins Package]> ");
	scanf("%d", &coins_ordered);

	if (coins_ordered == 7) {
		printf("[Enter a Value]> ");
		scanf("%d", &custom_coins_order);
		coins_to_add = custom_coins_order;
	} else {
		if (coins_ordered < 1 || coins_ordered > 6) {
			printf("Please select a valid coins package\n");
			return;
		}
		coins_to_add = coins_packages[coins_ordered - 1];
	}

	f = fopen("coins.txt", "r");
	if (f != NULL) {
		if (fscanf(f, "%d", &current_coins) != 1)
			current_coins = 0;
		fclose(f);
	}

	f = fopen("coins.txt", "w");
	if (f == NULL) {
		perror("fopen");
		return;
	}
	fprintf(f, "%d\n", current_coins + coins_to_add);
	fclose(f);
	data->coins = current_coins + coins_to_add;
	printf("Transaction Successfully!\n");

}

void buy_prem(struct Data *data) {
	int tier_buy;
	const char list_tier_simplefied[][64] = {
		"FREE PACKAGE", "PRO PACKAGE", "HACKER PACKAGE", "STUDENTS PACKAGE", "ENTERPRISE PACKAGE", "SCIENTIST PACKAGE" };
	const int price[] = {0, 450, 1200, 1700, 4800, 857000};
	const char list_tier[][128] = {
		"0. --->\t[FREE PACKAGE]",
		"\t|-- Features",
		"\t|",
		"\t|-> Up to 128 Numbers",
		"\t|-> 12s Thinking",
		"\t|-> Free Forever",
		"\t|---> Price: 0 Coins\n",

		"1. --->\t[PRO PACKAGE]",
		"\t|-- Features",
		"\t|",
		"\t|-> Up to 1024 Numbers",
		"\t|-> 7s Thinking",
		"\t|-> Thats it",
		"\t|---> Price: 450 Coins\n",

		"2. --->\t[HACKER PACKAGE]",
		"\t|-- Features",
		"\t|",
		"\t|-> Up to 4096 Numbers",
		"\t|-> 5s Thinking",
		"\t|-> Dev Follow Back Your TikTok :)",
		"\t|---> Price: 1200 Coins\n",

		"3. --->\t[STUDENTS PACKAGE]",
		"\t|-- Features",
		"\t|",
		"\t|-> Up to 16384 Numbers",
		"\t|-> 3s Thinking",
		"\t|-> Best for students who want big numbers",
		"\t|---> Price: 1700 Coins",

		"4. --->\t[ENTERPRISE PACKAGE]",
		"\t|-- Features",
		"\t|",
		"\t|-> Up to 32768 Numbers",
		"\t|-> 1s Thinking",
		"\t|-> Companies Only",
		"\t|-> Encrypted Answers",
		"\t|-> Dev Priority",
		"\t|---> Price: 4800 Coins\n",

		"5. --->\t[SCIENTIST PACKAGE]",
		"\t|-- Features",
		"\t|",
		"\t|-> Unlimited Numbers for research purpose",
		"\t|-> Instant Thinking, Using real computing performance for research purpose",
		"\t|-> High Performance Encrypting Algorithm for research purpose",
		"\t|-> Critical Dev Priority",
		"\t|-> Verfied Scientist required",
		"\t|-> Dev's Thighs Reveal UwU",
		"\t|-> No Follow back.",
		"\t|---> Price: 857000 Coins",
	};

	size_t length_list_tier = sizeof(list_tier) / sizeof(list_tier[0]);

	for (int i = 0; i < length_list_tier; i++) {
		printf("%s\n", list_tier[i]);
	}
	printf("\n--- These are one time buy package ---\n");
	printf("Coins: %d\n", data->coins);
	
	FILE *fptr;
	FILE *fptr_coins;

	printf("[Select tier]> ");
	scanf("%d", &tier_buy);
	if (tier_buy < 0 || tier_buy >= (int)(sizeof(price) / sizeof(price[0]))) {
		printf("Please select a valid tier\n");
		return;
	}
	if (data->coins < price[tier_buy]) {
		printf("Not enough coins for this packages\n");
		return;
	}
	printf("Ordering...\n");
	sleep(3);
	printf("Saving...\n");
	fptr = fopen("tier.txt", "w");
	fptr_coins = fopen("coins.txt", "w");
	
	fprintf(fptr, "%s\n", list_tier_simplefied[tier_buy]);
		data->coins -= price[tier_buy];
		fprintf(fptr_coins, "%d\n", data->coins);
	fclose(fptr);
		fclose(fptr_coins);
	sleep(3);
		printf("Succesfully buying tier %s for %d coins\n", list_tier_simplefied[tier_buy], price[tier_buy]);
}

void applying_tier_features(struct Data *data_pointer) {

	if (data_pointer->current_tier[0] == '\0') return;
	if (strcmp(data_pointer->current_tier, "FREE PACKAGE") == 0) {
		data_pointer->thinking_time = 6;
		data_pointer->verifying_time = 6;
		data_pointer->max_numbers = 128;
	}
	else if (strcmp(data_pointer->current_tier, "PRO PACKAGE") == 0) {
		data_pointer->thinking_time = 3;
		data_pointer->verifying_time = 3;
		data_pointer->max_numbers = 1024;
	}
	else if (strcmp(data_pointer->current_tier, "HACKER PACKAGE") == 0) {
		data_pointer->thinking_time = 3;
		data_pointer->verifying_time = 2;
		data_pointer->max_numbers = 4096;
	}
	else if (strcmp(data_pointer->current_tier, "STUDENTS PACKAGE") == 0) {
		data_pointer->thinking_time = 2;
		data_pointer->verifying_time = 1;
		data_pointer->max_numbers = 16384;
	}
	else if (strcmp(data_pointer->current_tier, "ENTERPRISE PACKAGE") == 0) {
		data_pointer->thinking_time = 1;
		data_pointer->verifying_time = 0;
		data_pointer->max_numbers = 32768;
	}
	else if (strcmp(data_pointer->current_tier, "SCIENTIST PACKAGE") == 0) {
		data_pointer->thinking_time = 0;
		data_pointer->verifying_time = 0;
		data_pointer->max_numbers = 0;
	}
}

void calculating(struct Data *data_pointer) {
	printf("[Enter first number]> ");
	scanf("%d", &data_pointer->n1);
	printf("[Enter second number]> ");
	scanf("%d", &data_pointer->n2);

	data_pointer->result = data_pointer->n1 * data_pointer->n2;

	limit(data_pointer);

	printf("\nThinking...\n");
	sleep(data_pointer->thinking_time);
	printf("Verifying...\n");
	sleep(data_pointer->verifying_time);
	printf("Found the answer...\n");

	printf("Result: %d\n", data_pointer->result);
}

int main(void) {
	int choice;
	char coins_stringed[32];
	struct Data data;
	//struct Data *dptr = &data;
	memset(&data, 0, sizeof data);

 FILE *f_tier = fopen("tier.txt", "r");
  if (f_tier) {
      if (fgets(data.current_tier, sizeof data.current_tier, f_tier) != NULL) {
          data.current_tier[strcspn(data.current_tier, "\r\n")] = '\0';
      }
      fclose(f_tier);
    }
		else {
      f_tier = fopen("tier.txt", "w");
      if (!f_tier) {
          perror("fopen");
          return 1;
      }
      fputs("FREE PACKAGE\n100", f_tier);
      fclose(f_tier);
      strcpy(data.current_tier, "FREE PACKAGE");
  }

	// Read "coins.txt" value to the variable
	FILE *f_coins = fopen("coins.txt", "r");
	if (f_coins != NULL) {
		if (fgets(coins_stringed, sizeof coins_stringed, f_coins) != NULL)
			data.coins = atoi(coins_stringed);
		fclose(f_coins);
	}

	applying_tier_features(&data);

	printf("Coins: %d\n", data.coins);
	printf("Current tier: '%s'\n", data.current_tier);
	printf("Thinking Time: %d\n", data.thinking_time);
	printf("Verifying Time: %d\n", data.verifying_time);
	printf("Max Numbers: %d\n\n", data.max_numbers);
	printf("0. Exit\n1. Start Calculating\n2. Buy Tier\n3. Coins Store\n");
	printf("> ");
	scanf("%d", &choice);
	printf("\n");

	if (choice == 0) { exit(0); }
	else if (choice == 1) { calculating(&data); }
	else if (choice == 2) { buy_prem(&data); }
	else if (choice == 3) { buy_coins(&data); }
	else { printf("Please select the right number\n"); exit(1); }

	return 0;
}
