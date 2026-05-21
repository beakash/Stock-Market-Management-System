##include <stdio.h>
#include <string.h>

struct Stock {
    int id;
    char company[50];
    float price;
};

int main() {

    struct Stock s[100];
    int n = 0;
    int choice, i, id;
    char search[50];

    while(1) {

        printf("\n===== STOCK PRICE MANAGEMENT SYSTEM =====\n");
        printf("1. Add Stock\n");
        printf("2. Display Stocks\n");
        printf("3. Search Stock\n");
        printf("4. Update Stock Price\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:

                printf("Enter Stock ID: ");
                scanf("%d", &s[n].id);

                printf("Enter Company Name: ");
                scanf("%s", s[n].company);

                printf("Enter Stock Price: ");
                scanf("%f", &s[n].price);

                n++;

                printf("Stock Added Successfully!\n");
                break;

            case 2:

                if(n == 0) {
                    printf("No Stocks Available!\n");
                } else {

                    printf("\n--- Stock List ---\n");

                    for(i = 0; i < n; i++) {

                        printf("ID: %d\n", s[i].id);
                        printf("Company: %s\n", s[i].company);
                        printf("Price: %.2f\n", s[i].price);
                        printf("----------------------\n");
                    }
                }

                break;

            case 3:

                printf("Enter Company Name to Search: ");
                scanf("%s", search);

                for(i = 0; i < n; i++) {

                    if(strcmp(s[i].company, search) == 0) {

                        printf("\nStock Found!\n");
                        printf("ID: %d\n", s[i].id);
                        printf("Company: %s\n", s[i].company);
                        printf("Price: %.2f\n", s[i].price);
                        break;
                    }
                }

                if(i == n) {
                    printf("Stock Not Found!\n");
                }

                break;

            case 4:

                printf("Enter Stock ID to Update Price: ");
                scanf("%d", &id);

                for(i = 0; i < n; i++) {

                    if(s[i].id == id) {

                        printf("Enter New Price: ");
                        scanf("%f", &s[i].price);

                        printf("Price Updated Successfully!\n");
                        break;
                    }
                }

                if(i == n) {
                    printf("Stock ID Not Found!\n");
                }

                break;

            case 5:

                printf("Exiting Program...\n");
                return 0;

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}
