#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NO_DISKS 5 // number of disks - works even for 4+ ( wastes memory )
#define SCALE 10 // scale factor - default: 10

#define CALL_HEIGHT SCALE * 5
#define CALL_WIDTH SCALE * 25

#define CALL_SPACING_Y SCALE * 2
#define CALL_SPACING_X SCALE * 10

#define TEXT_SIZE SCALE * 2

typedef struct _disk{
  unsigned peg;
}disk_t;

/// ------------------ HEADER & FOOTER OUTPUT ------------------

void output_header(FILE *stream){
  unsigned height = pow(2, NO_DISKS) * (CALL_HEIGHT + CALL_SPACING_Y);
  unsigned width = (NO_DISKS + 1) * (CALL_WIDTH + CALL_SPACING_X);

  fprintf(stream, "<svg width=\"%u\" height=\"%u\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" overflow=\"scroll\">\n", width, height);
  fprintf(stream, "<style>\n\t.text { font: bold %upx sans-serif; }\n</style>\n", TEXT_SIZE);
}

void output_footer(FILE *stream){
  fprintf(stream, "</svg>");
}

/// ------------------ CALL DRAWING FUNCTION ------------------

void draw_call(FILE *stream, unsigned branch, int diskNr, char fromPeg, char toPeg, char auxPeg){
  static unsigned drawing = 0;

  unsigned x = branch * (CALL_WIDTH + CALL_SPACING_X);;
  unsigned y = drawing * (CALL_HEIGHT + CALL_SPACING_Y);

  // HANOI call printing
 fprintf(stream, "<rect x=\"%u\" y=\"%u\" width=\"%u\" height=\"%u\" stroke-width=\"1\" stroke=\"black\" fill=\"rgb(200,30,200)\" />\n", x, y, CALL_WIDTH, CALL_HEIGHT);
 fprintf(stream, "<text x=\"%u\" y=\"%u\" fill=\"black\" class=\"text\">HANOI(%u, %c, %c, %c)</text>\n", x + CALL_WIDTH/10, y + CALL_HEIGHT/2 + TEXT_SIZE/2, diskNr, fromPeg, toPeg, auxPeg);

  for (unsigned i = 0 ; i < NO_DISKS - branch ; i++){
    x += (CALL_WIDTH + CALL_SPACING_X);

     // MOVE call printing
    fprintf(stream, "<rect x=\"%u\" y=\"%u\" width=\"%u\" height=\"%u\" stroke-width=\"1\" stroke=\"black\" fill=\"rgb(128, 216, 216)\" />\n", x, y, CALL_WIDTH, CALL_HEIGHT);
    fprintf(stream, "<text x=\"%u\" y=\"%u\" fill=\"white\" class=\"text\">MOVE %u: %c -> %c</text>\n", x + CALL_WIDTH/10, y + CALL_HEIGHT/2 + TEXT_SIZE/2, diskNr, fromPeg, toPeg);
  }

  drawing++;
}

/// ------------------ DISK FUNCTIONS ------------------

disk_t get_disk(unsigned peg){
  disk_t disk;

  disk.peg = peg;

  return disk;
}

void get_disk_array(disk_t *diskArr){ // initializes disks -> peg, position, width, height, color
  for (unsigned i = 0 ; i < NO_DISKS ; i++){
    diskArr[i] = get_disk(1);
  }
}

void move_disk(disk_t disk, unsigned toPeg){ // moves disk: peg -> peg
  disk.peg = toPeg;
}

/// ------------------ HANOI FUNCTION ------------------

void hanoi(FILE *stream, disk_t *diskArr, int diskNr, char fromPeg, char toPeg, char auxPeg, unsigned branch){
  if (diskNr == 1){
    draw_call(stream, branch, diskNr, fromPeg, toPeg, auxPeg);

    move_disk(diskArr[0], toPeg - 'A' + 1);

  }
  else{
    hanoi(stream, diskArr, diskNr - 1, fromPeg, auxPeg, toPeg, branch + 1);

    draw_call(stream, branch, diskNr, fromPeg, toPeg, auxPeg);
    move_disk(diskArr[diskNr - 1], toPeg - 'A' + 1);
    //draw_call(stream, "MOVE", branch + 1);

    hanoi(stream, diskArr, diskNr - 1, auxPeg, toPeg, fromPeg, branch + 1);
  }
}

int main(){
  FILE *hanoi_calltree_out = fopen("hanoi_calltree.svg", "w");

  disk_t *diskArr = (disk_t*)malloc(NO_DISKS * sizeof(disk_t));

  get_disk_array(diskArr);

  output_header(hanoi_calltree_out);

  hanoi(hanoi_calltree_out, diskArr, NO_DISKS, 'A', 'C', 'B', 0);

  output_footer(hanoi_calltree_out);

  return 0;
}
