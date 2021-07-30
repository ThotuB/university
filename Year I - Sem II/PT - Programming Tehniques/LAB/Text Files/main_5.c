#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TIME_JUMP_SECS -4365
#define TIME_JUMP_MSECS 826

typedef struct _time{
  unsigned h;
  unsigned m;
  unsigned s;
  unsigned ms;
}time;

typedef struct _Sub_Entry {
  unsigned counter;
  time timeBegin;
  time timeEnd;
  char *text;
}Sub_Entry;

/// ------------------ PRINTING FUNCTIONS ------------------

void fprint_time(FILE *stream_out, time subTime){
  fprintf(stream_out, "%02u:%02u:%02u,%03u", subTime.h, subTime.m, subTime.s, subTime.ms);
}

void fprint_text(FILE *stream_out, char *text){
  for (unsigned i = 0 ; text[i] != '\0' ; i++){
    fprintf(stream_out, "%c", text[i]);
  }
}

void fprint_sub(FILE *stream_out, Sub_Entry sub){
  fprintf(stream_out, "%u\n", sub.counter);
  fprint_time(stream_out, sub.timeBegin);
  fprintf(stream_out, " --> ");
  fprint_time(stream_out, sub.timeEnd);
  fprintf(stream_out, "\n");
  fprint_text(stream_out, sub.text);
}

void fprint_entries(FILE *stream_out, Sub_Entry *subs, unsigned size){
  for (unsigned i = 0 ; i < size ; i++){
    fprint_sub(stream_out, subs[i]);
  }
}

/// ------------------ CHANGING/CONVERTING FUNCTIONS ------------------

char *remove_tags(char *text){
  int tagBegin = -1;
  int tagEnd = -1;

  for (int i = 0 ; text[i] != '\0' ; i++){
    if ( text[i] == '<' ){
      tagBegin = i;
    }
    else if ( text[i] == '>' ){
      tagEnd = i;
    }

    if ( tagBegin != -1 && tagEnd != -1 ){
      strcpy(text + tagBegin, text + tagEnd + 1);

      i = tagBegin-1;
      tagBegin = -1; tagEnd = -1;
    }
  }

  return text;
}

time shift_time(time subTime, unsigned secs, unsigned msecs){
  subTime.ms += msecs;
  subTime.s += (subTime.ms/1000) + secs;
  subTime.m += (subTime.s/60);
  subTime.h += (subTime.m/60);

  subTime.ms %= 1000;
  subTime.s %= 60;
  subTime.m %= 60;
  subTime.h %= 24;

  return subTime;
}

void change_entries(Sub_Entry *entries, unsigned size){
  for (unsigned i = 0 ; i < size ; i++){
    entries[i].text = remove_tags(entries[i].text);
    entries[i].timeBegin = shift_time(entries[i].timeBegin, TIME_JUMP_SECS, TIME_JUMP_MSECS);
    entries[i].timeEnd = shift_time(entries[i].timeEnd, TIME_JUMP_SECS, TIME_JUMP_MSECS);
  }
}

/// ------------------ GETTING FUNCTIONS ------------------

time get_time(FILE *stream_in){
  time subTime;

  fscanf(stream_in, "%u:%u:%u,%u", &subTime.h, &subTime.m, &subTime.s, &subTime.ms);

  return subTime;
}

char* get_text(FILE *stream_in){
  char *text = (char*)malloc(sizeof(char));
  char c = fgetc(stream_in);
  unsigned i = 0;

  while ( c != EOF ){
    text[i] = c;

    i++;
    text = (char*)realloc(text, (i+1)*sizeof(char));

    if ( text[i-1] == '\n' && text[i-2] == '\n' ){
      break;
    }
    c = fgetc(stream_in);
  }
  text[i] = '\0';

  return text;
}

Sub_Entry* get_subs(FILE *stream_in, unsigned *size){
  Sub_Entry *entries = NULL;

  while ( fscanf(stream_in, "%u", size) == 1 ){
    entries = (Sub_Entry*)realloc(entries,(*size) * sizeof(Sub_Entry));
    // counter
    entries[(*size)-1].counter = (*size);
    // time
    entries[(*size)-1].timeBegin = get_time(stream_in);
    fscanf(stream_in, " --> ");
    entries[(*size)-1].timeEnd = get_time(stream_in);
    fgetc(stream_in);
    // text
    entries[(*size)-1].text = get_text(stream_in);
  }

  return entries;
}

int main(){
  FILE *subtitles_in = fopen("sub_in.srt", "r");
  FILE *subtitles_out = fopen("sub_out.srt", "w");

  unsigned entriesSize = 0;
  Sub_Entry *entries = get_subs(subtitles_in, &entriesSize);

  change_entries(entries, entriesSize);

  fprint_entries(subtitles_out, entries, entriesSize);

  fclose(subtitles_in);
  fclose(subtitles_out);
  return 0;
}
