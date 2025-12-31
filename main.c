#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"
#include <limits.h>
#include <stdbool.h>

typedef struct Bucket{
	bool value_status; 
	void* value;                                                       
}Bucket;

struct Hashtable{
	Bucket *chunk;
	size_t elem_size;
	size_t size;
	size_t capacity;
};

void imprimir_chunk(Bucket *b){
	printf("%p: ", (void*)b);

	if(b->value_status){
		printf("valor:%i ", *(int*)b->value);
	} else {
		printf("valor:NULL ");
	}

	printf("estado:%i", b->value_status);
}


void imprimir(Hashtable *table){
	for(int i = 0; i < table->capacity; i++){
		printf("i:%i.- ", i);
		imprimir_chunk(table->chunk+i);
		printf("\n");
	}
}

int main(){

	Hashtable *h=hashtable_create(sizeof(int), 10);
	int x = 11;

	hashtable_add(h, "ximena galindo mata", &x);
	
	printf("\n");
	imprimir(h);
	hashtable_add(h, "como estas?", &x);
	printf("\n");
	imprimir(h);
	return 0;

}

Hashtable* hashtable_create(size_t elem_size, size_t capacity){
	Hashtable *ht=(Hashtable*)malloc(sizeof(Hashtable));
	if(!ht) return NULL;
	ht->elem_size=elem_size;
	ht->chunk=(Bucket*)malloc(sizeof(Bucket)*capacity);
	if(!ht->chunk){
		free(ht);
		return NULL;
	}
	ht->capacity=capacity;
	ht->size=0;
	Bucket* aux=ht->chunk;
	for(size_t i = 0; i < ht->capacity; i++){
	        aux[i].value_status=0;
		aux[i].value=NULL;
	}
	return ht;
}

bool most_significan_bit(unsigned int value){
	unsigned int mask = 1u << (sizeof(unsigned int)*CHAR_BIT-1);
	unsigned int msb = value&mask;
	return (msb!=0)? 1: 0;
}

unsigned int hash_function(const unsigned char *key, size_t capacity){
	unsigned int hash = 0;
	while(*key){
		bool msb = most_significan_bit(hash);
		if(msb==0){
			hash=hash<<1;
			hash=hash^*key;          
		}else{
			hash=hash<<1;
			hash=hash|1;
			hash=hash^*key;          
		}
		key++;
	}
	hash=hash%capacity;
	return hash;
}



int hashtable_reserve(Hashtable *table, size_t size){
	if(!table) return -1;
	size_t new_capacity = table->capacity+size;
	Bucket *aux = realloc(table->chunk, sizeof(Bucket) * new_capacity);
	if(!aux) return -1;
	for(size_t i = table->capacity; i < new_capacity; i++){
		aux[i].value=NULL;
		aux[i].value_status=0;
	}
	table->chunk=aux;
	table->capacity = new_capacity;
	return 0;
}


int hashtable_add(Hashtable *table, const char* key, const void* value){
	if(!table || !table->chunk) return -1;
	if(table->size >= table->capacity){
		return 1;
	}else{
		Bucket *aux=table->chunk;
		unsigned int i = hash_function(key, table->capacity);
		if(aux[i].value_status == 1) return -1;
		aux[i].value=malloc(table->elem_size);
		aux[i].value_status=1;
		memcpy(aux[i].value, value, table->elem_size);
		table->size++;
		return 0;
	}
}










