#include <stdio.h>
#include <string.h>

char getClass(char str[]) {

	char arr[4];
	int i = 0;
	while (str[i] != '.') {

		arr[i] = str[i];
		i++;
	}
	i--;

	int ip = 0, j = 1;
	while (i >= 0) {

		ip = ip + (str[i] - '0') * j;
		j = j * 10;
		i--;
	}
	// Now str is in numbers

	if (ip >= 1 && ip <= 126) {

		return 'A';
	}
	else if (ip >= 128 && ip <= 191) {

		return 'B';
	}
	else if (ip >= 192 && ip <= 223) {

		return 'C';
	}
	else if (ip >= 224 && ip <= 239) {

		return 'D';
	}
	else {

		return 'E';
	}
}

void separate(char str[], char ipClass) {

	char network[12], host[12];
	for (int k = 0; k < 12; k++)
		network[k] = host[k] = '\0';

	if (ipClass == 'A') {

		int i = 0, j = 0;
		while (str[j] != '.')
			network[i++] = str[j++];
		i = 0;
		j++;
		while (str[j] != '\0') {

			host[i++] = str[j++];
		}
		printf("Network ID: %s\n", network);
		printf("Host ID: %s\n", host);
	}
	else if (ipClass == 'B') {

		int i = 0, j = 0, dotCount = 0;

		while (dotCount < 2) {

			network[i++] = str[j++];
			if (str[j] == '.')
				dotCount++;
		}
		i = 0;
		j++;

		while (str[j] != '\0') {

			host[i++] = str[j++];
		}
		printf("Network ID: %s\n", network);
		printf("Host ID: %s\n", host);
	}
	else if (ipClass == 'C') {

		int i = 0, j = 0, dotCount = 0;

		// storing in network[] up to 3rd dot
		// dotCount keeps track of number of
		// dots or octets passed
		while (dotCount < 3) {

			network[i++] = str[j++];
			if (str[j] == '.')
				dotCount++;
		}

		i = 0;
		j++;

		while (str[j] != '\0') {

			host[i++] = str[j++];
		}

		printf("Network ID: %s\n", network);
		printf("Host ID: %s\n", host);
	}
	else {

		printf("Not divided");
	}
}

int main()
{
	char str[] = "1.4.5.5";
	char ipClass = getClass(str);

	 printf("IP: Class %c\n", ipClass);

	separate(str, ipClass);

	return 0;
}
