#include "render/SapperRenderer.h"

int main() {

  Board* board = new Board(20, 20, 50);

  SapperRenderer* sapper = new SapperRenderer(board);

  delete sapper;

  return 0;
}
