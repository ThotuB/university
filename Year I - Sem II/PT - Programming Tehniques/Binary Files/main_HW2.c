#include <stdio.h>
#include <inttypes.h>
#include "encrypt.h"

typedef struct _repair_db{
  unsigned index;
  char repair_type[22];
  unsigned long long IMEI;
  unsigned price;
  unsigned investment;
  unsigned profit;
  unsigned total_profit;
  unsigned total_influx;
}repair_db;

char extraENDL;

/// ------------------ USEFUL FUNCTIONS ------------------

void print_options(){
  printf("Chose Option:\n");
  printf("0. EXIT\n");
  printf("1. Add Entry/Entries\n");
  printf("2. Read & Print Entry\n");
  printf("3. Read & Print Entries Belonging to IMEI\n");
  printf("4. Read & Print Database\n");
  printf("5. Delete Entry (Under Construction)\n");
  printf("6. Encrypt Database\n");
  printf("7. Decrypt Database\n");
  printf("\n");
}

unsigned get_database_size(FILE* stream_in){
  fseek(stream_in, 0, SEEK_END);
  long unsigned end = ftell(stream_in);

  return (end/sizeof(repair_db));
}

void update_totals(FILE* stream, int profit, int influx){
  repair_db entry;

  fseek(stream, 0, SEEK_SET);
  fread(&entry, sizeof(repair_db), 1, stream);

  entry.total_profit += profit;
  entry.total_influx += influx;

  fseek(stream, 0, SEEK_SET);
  fwrite(&entry, sizeof(repair_db), 1, stream);
}

void delete_entry_nr(FILE* stream, unsigned index){
  unsigned sizeDB = get_database_size(stream);
  repair_db entry;

  fseek(stream, 0, SEEK_SET);

  for (unsigned i = 0 ; i < sizeDB ; i++){
    fread(&entry, sizeof(repair_db), 1, stream);
    if ( entry.index != index ){
      entry.index = i;
      fseek(stream, -sizeof(repair_db), SEEK_CUR);
      fwrite(&entry, sizeof(repair_db), 1, stream);
    }
  }
}

void print_database_border(){
  printf("-------------------------------------------------------------------------------------------------------------------------\n");
}

void print_database_header(){
  print_database_border();
  printf("| Index |           Repair Type |             IMEI |      Price | Investment |     Profit | Total Profit | Total Influx |\n");
  print_database_border();
}

void print_entry(repair_db entry){
  printf("| %5u | %21s | %16llu | %10u | %10u | %10u | ", entry.index, entry.repair_type, entry.IMEI, entry.price, entry.investment, entry.profit);
  if ( entry.index == 0 ){
    printf("%12u | %12u |", entry.total_profit, entry.total_influx);
  }
  else{
    printf("           - |            - |");
  }
  printf("\n");
}

repair_db get_entry(unsigned index){
  repair_db entry;

  entry.index = index;
  extraENDL = getchar();
  printf("Repair Type: ");
  unsigned j = 0;
  for (char c = getchar() ; c != '\n' && j < 21 ; c = getchar()){
    entry.repair_type[j] = c;
    j++;
  }
  entry.repair_type[j] = '\0';
  printf("IMEI: "); scanf("%llu", &entry.IMEI);
  printf("Price: "); scanf("%u", &entry.price);
  printf("Investment: "); scanf("%u", &entry.investment);
  entry.profit = entry.price - entry.investment;
  entry.total_profit = 0;
  entry.total_influx = 0;

  return entry;
}

/// ------------------ OPTION FUNCTION ------------------

void add_entry(FILE* stream){
  unsigned nrEntries = 0;
  printf("Entries to Read: ");
  scanf("%u", &nrEntries);

  unsigned profit = 0;
  unsigned influx = 0;

  fseek(stream, 0, SEEK_END);

  repair_db tempDB[nrEntries];
  unsigned dbSize = get_database_size(stream);

  for (unsigned i = 0 ; i < nrEntries ; i++){
    tempDB[i] = get_entry(dbSize + i);
    profit += tempDB[i].profit;
    influx += tempDB[i].price;

    fwrite(tempDB + i, sizeof(repair_db), 1, stream);
    printf("ENTRY ADDED\n\n");
  }

  update_totals(stream, profit, influx);
}

void read_entry(FILE* stream){
  unsigned entryNr = 0;
  repair_db entry;
  unsigned sizeDB = get_database_size(stream);

  do{
    printf("Entry Nr: "); scanf("%u", &entryNr);
  }while( entryNr > sizeDB );

  fseek(stream, entryNr * sizeof(repair_db), SEEK_SET);
  fread(&entry, sizeof(repair_db), 1, stream);

  print_database_header();
  print_entry(entry);
  print_database_border();
}

void read_entries_IMEI(FILE* stream){
  repair_db entry;
  long long unsigned IMEI;
  unsigned sizeDB = get_database_size(stream);

  printf("IMEI: "); scanf("%llu", &IMEI);

  fseek(stream, 0, SEEK_SET);

  print_database_header();

  for (unsigned i = 0 ; i < sizeDB ; i++){
    fread(&entry, sizeof(repair_db), 1, stream);
    if ( entry.IMEI == IMEI ){
      print_entry(entry);
    }
  }

  print_database_border();
}

void read_database(FILE* stream_in){
  repair_db entry;
  unsigned sizeDB = get_database_size(stream_in);

  fseek(stream_in, 0, SEEK_SET);

  print_database_header();

  for (unsigned i = 0 ; i < sizeDB ; i++){
    fread(&entry, sizeof(repair_db), 1, stream_in);
    print_entry(entry);
  }

  print_database_border();
}

void delete_entry(FILE* stream){
  unsigned entryNr = 0;
  unsigned sizeDB = get_database_size(stream);

  do{
    printf("Entry Nr: "); scanf("%u", &entryNr);
  }while( entryNr == 0 || entryNr > sizeDB );

  delete_entry_nr(stream, entryNr);
}

int main(){
  FILE* database_file = fopen("repair_shop.bdb", "rb+");
  if ( !database_file ){
    database_file = fopen("repair_shop.bdb", "wb+");
  }
  unsigned option = 1;

  while ( option ){
    print_options();
    printf("Option: ");
    scanf("%u", &option);

    if ( option == 0 ){
      break;
    }
    else if ( option == 1 ){
      add_entry(database_file);
    }
    else if ( option == 2 ){
      read_entry(database_file);
    }
    else if ( option == 3 ){
      read_entries_IMEI(database_file);
    }
    else if ( option == 4 ){
      read_database(database_file);
    }
    else if ( option == 5 ){
      delete_entry(database_file);
    }
    else if ( option == 6 ){
      extraENDL = getchar();
      EncryptFile(database_file);
      fclose(database_file);
      database_file = fopen("repair_shop.bdb", "rb+");
    }
    else if ( option == 7 ){
      extraENDL = getchar();
      DecryptFile(database_file);
      fclose(database_file);
      database_file = fopen("repair_shop.bdb", "rb+");
    }
    else {
      printf("INVALID OPTION!\n");
    }
  }

  fclose(database_file);

  return 0;
}
