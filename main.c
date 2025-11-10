// main.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>

#include "BENSCHILLIBOWL.h"

// Tune these for testing
#define BENSCHILLIBOWL_SIZE 100
#define NUM_CUSTOMERS 90
#define NUM_COOKS 10
#define ORDERS_PER_CUSTOMER 3
#define EXPECTED_NUM_ORDERS (NUM_CUSTOMERS * ORDERS_PER_CUSTOMER)

// Global restaurant pointer
BENSCHILLIBOWL *bcb;

/**
 * Customer thread:
 *  - allocate an order
 *  - pick a menu item
 *  - set menu item and customer id
 *  - add order to restaurant
 */
void* BENSCHILLIBOWLCustomer(void* tid) {
    int customer_id = (int)(intptr_t) tid;

    for (int i = 0; i < ORDERS_PER_CUSTOMER; i++) {
        Order* order = (Order*) malloc(sizeof(Order));
        if (!order) {
            perror("malloc");
            pthread_exit(NULL);
        }
        order->menu_item = PickRandomMenuItem();
        order->customer_id = customer_id;
        order->next = NULL;

        int order_num = AddOrder(bcb, order);
        if (order_num < 0) {
            // Should not happen in normal flow
            free(order);
            break;
        }
    }
    return NULL;
}

/**
 * Cook thread:
 *  - get orders until GetOrder returns NULL
 *  - count and free each order
 */
void* BENSCHILLIBOWLCook(void* tid) {
    int cook_id = (int)(intptr_t) tid;
    int orders_fulfilled = 0;

    for (;;) {
        Order* order = GetOrder(bcb);
        if (order == NULL) {
            break; // no more orders to process
        }
        // Simulate work if desired
        // usleep(1000);
        orders_fulfilled++;
        free(order);
    }

    printf("Cook #%d fulfilled %d orders\n", cook_id, orders_fulfilled);
    return NULL;
}

/**
 * Program entry:
 *  - open restaurant
 *  - create customers and cooks
 *  - join all threads
 *  - close restaurant
 */
int main() {
    bcb = OpenRestaurant(BENSCHILLIBOWL_SIZE, EXPECTED_NUM_ORDERS);

    pthread_t customers[NUM_CUSTOMERS];
    pthread_t cooks[NUM_COOKS];

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_create(&customers[i], NULL, BENSCHILLIBOWLCustomer, (void*)(intptr_t)i);
    }
    for (int i = 0; i < NUM_COOKS; i++) {
        pthread_create(&cooks[i], NULL, BENSCHILLIBOWLCook, (void*)(intptr_t)i);
    }

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customers[i], NULL);
    }
    for (int i = 0; i < NUM_COOKS; i++) {
        pthread_join(cooks[i], NULL);
    }

    CloseRestaurant(bcb);
    return 0;
}
