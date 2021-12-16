#include "Slot.h"
#include <cstdlib>
#include <ctime>
#include <vector>

#define BOMB 11
#define EMPTY 10

class Board {
public:
  int sizeX, sizeY;
  int bombAmount;
  int markedAmount, markedCorrectly;
  short end;
  Slot** board;

  Board(int sizeX, int sizeY, int bombAmount);

  ~Board();

  bool isEmpty(unsigned int slot);

  bool isClickable(unsigned int slot);

  int toSlot(unsigned int x, unsigned int y);

  int click(unsigned int slot);

  void rightClick(unsigned int slot);

private:
  short getAround(unsigned int slot);
};
