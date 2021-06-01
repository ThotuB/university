#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NO_DISKS 12 // number of disks - works even for 4+ ( wastes memory )

#define DRAWING_HEIGHT 200
#define LEFT_BORDER 25

#define TABLE_HEIGHT 20
#define TABLE_WIDTH 800

#define PEG_GAP TABLE_WIDTH/4
#define PEG_HEIGHT 160
#define PEG_WIDTH 10

typedef struct _disk{
  unsigned peg;
  unsigned pos;

  unsigned width;
  unsigned height;

  unsigned color:8;
}disk_t;

unsigned drawing = 1;

/// ------------------ HEADER & FOOTER OUTPUT ------------------

void output_header(FILE *stream){
  unsigned height = pow(2, NO_DISKS) * DRAWING_HEIGHT;
  fprintf(stream, "<svg width=\"1080\" height=\"%u\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" overflow=\"scroll\">\n", height);
}

void output_footer(FILE *stream){
  fprintf(stream, "</svg>");
}

/// ------------------ TABLE OUTPUT ------------------

void draw_table(FILE *stream){
  fprintf(stream, "<rect x=\"%u\" y=\"%u\" width=\"%u\" height=\"%u\" fill=\"orange\" stroke-width=\"1\" stroke=\"orange\" />\n", LEFT_BORDER, drawing * DRAWING_HEIGHT - TABLE_HEIGHT, TABLE_WIDTH, TABLE_HEIGHT);
}

void draw_pegs(FILE *stream){
  fprintf(stream, "<rect x=\"%u\" y=\"%u\" width=\"%u\" height=\"%u\" fill=\"orange\" stroke-width=\"1\" stroke=\"orange\" />\n", LEFT_BORDER + (1 * PEG_GAP), drawing * DRAWING_HEIGHT - PEG_HEIGHT - TABLE_HEIGHT, PEG_WIDTH, PEG_HEIGHT);
  fprintf(stream, "<rect x=\"%u\" y=\"%u\" width=\"%u\" height=\"%u\" fill=\"orange\" stroke-width=\"1\" stroke=\"orange\" />\n", LEFT_BORDER + (2 * PEG_GAP), drawing * DRAWING_HEIGHT - PEG_HEIGHT - TABLE_HEIGHT, PEG_WIDTH, PEG_HEIGHT);
  fprintf(stream, "<rect x=\"%u\" y=\"%u\" width=\"%u\" height=\"%u\" fill=\"orange\" stroke-width=\"1\" stroke=\"orange\" />\n", LEFT_BORDER + (3 * PEG_GAP), drawing * DRAWING_HEIGHT - PEG_HEIGHT - TABLE_HEIGHT, PEG_WIDTH, PEG_HEIGHT);
}

/// ------------------ DISK OUTPUT ------------------

void draw_disk(FILE *stream, disk_t disk){
  unsigned x = disk.peg * PEG_GAP - disk.width/2 + PEG_WIDTH/2 + LEFT_BORDER;
  unsigned y = drawing * DRAWING_HEIGHT - TABLE_HEIGHT - (disk.pos * disk.height);
  unsigned width = disk.width;
  unsigned height = disk.height;
  unsigned color = disk.color;

  fprintf(stream, "<rect x=\"%u\" y=\"%u\" width=\"%u\" height=\"%u\" fill=\"rgb(0,0,%d)\" stroke-width=\"1\" stroke=\"black\" />\n", x, y, width, height, color);
}

void draw_disk_array(FILE *stream, disk_t *diskArr){
  for (unsigned i = 0 ; i < NO_DISKS ; i++){
    draw_disk(stream, diskArr[i]);
  }
}

/// ------------------ DISK OUTPUT ------------------

void draw(FILE *stream, disk_t *diskArr){
  draw_table(stream);
  draw_pegs(stream);
  draw_disk_array(stream, diskArr);

  drawing++;
}

/// ------------------ DISK FUNCTIONS ------------------

disk_t get_disk(unsigned peg, unsigned pos, unsigned width, unsigned height, unsigned color){
  disk_t disk;

  disk.peg = peg;
  disk.pos = pos;

  disk.width = width;
  disk.height = height;

  disk.color = color;

  return disk;
}

void get_disk_array(disk_t *diskArr){ // initializes disks -> peg, position, width, height, color
  for (unsigned i = 0 ; i < NO_DISKS ; i++){
    diskArr[i] = get_disk(1, NO_DISKS - i, (i + 1) * PEG_GAP/(NO_DISKS + 1), (PEG_HEIGHT /(NO_DISKS + 1)), 255 - i * 255/NO_DISKS);
  }
}

void move_disk(disk_t *diskArr, unsigned diskNr, unsigned toPeg){ // moves disk: peg -> peg
  diskArr[diskNr].peg = toPeg;
  diskArr[diskNr].pos = 1;

  for (unsigned i = diskNr + 1 ; i < NO_DISKS ; i++){ // sets disk's position
    if ( diskArr[i].peg == toPeg){
      diskArr[diskNr].pos++;
    }
  }
}

void hanoi(FILE *stream, disk_t *diskArr, int diskNr, char fromPeg, char toPeg, char auxPeg){
  if (diskNr == 1){

    move_disk(diskArr, diskNr - 1, toPeg - 'A' + 1);
    draw(stream, diskArr);
    printf("Move disk 1 from [%c] to [%c]\n", fromPeg, toPeg);
  }
  else{
    hanoi(stream, diskArr, diskNr - 1, fromPeg, auxPeg, toPeg);

    move_disk(diskArr, diskNr - 1, toPeg - 'A' + 1);
    draw(stream, diskArr);

    printf("Move disk %d from [%c] to [%c]\n", diskNr, fromPeg, toPeg);
    hanoi(stream, diskArr, diskNr - 1, auxPeg, toPeg, fromPeg);
  }
}

int main(){
  FILE *hanoi_out = fopen("hanoi.svg", "w");

  disk_t *diskArr = (disk_t*)malloc(NO_DISKS * sizeof(disk_t));

  get_disk_array(diskArr);

  output_header(hanoi_out);

  draw(hanoi_out, diskArr);
  hanoi(hanoi_out, diskArr, NO_DISKS, 'A', 'C', 'B');

  output_footer(hanoi_out);

  return 0;
}
