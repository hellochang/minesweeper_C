#include <stdbool.h>
#include <stdio.h>
#include <cs136.h>
#include "game_core.h"

// is_inbound (c, r) checks whether (c, r) is within the boundaries of the map
bool is_inbound (int c, int r, int width, int height) {
    return !((c < 0) || (r + 1 > height) || (c + 1 > width) || (r < 0));
}

/// what if the map is already marked
// see game.h for documentation
bool step(const int c, const int r, const int width, const int height) {
    const int pos = r * width + c;
    if (is_inbound(c, r, width, height) == false) {
        return false;
    } else if (map[pos] == MARKED) {
        return false;
    } else if (mine_at(c, r) == true) {
        map[pos] = MINE;
        return true;
    } else {
        int adj_mines = 0;
        if (mine_at(c - 1, r) == true) {
            adj_mines++;
        }
        if (mine_at(c + 1, r) == true) {
            adj_mines++;
        }
        if (mine_at(c, r + 1) == true) {
            adj_mines++;
        }
        if (mine_at(c - 1, r - 1) == true) {
            adj_mines++;
        }
        if (mine_at(c - 1, r + 1) == true) {
            adj_mines++;
        }
        if (mine_at(c + 1, r + 1) == true) {
            adj_mines++;
        }
        if (mine_at(c, r - 1) == true) {
            adj_mines++;
        }
        if (mine_at(c + 1, r - 1) == true) {
            adj_mines++;
        }
        map[pos] = adj_mines;
        return false;
    }
}

// see game.h for documentation
bool step_adv(const int c, const int r, const int width, const int height) {
    const int pos = r * width + c;

    if (is_inbound(c, r, width, height) == false) {
        return false;
    } else if (map[pos] == MARKED) {
        return false;
    } else if (mine_at(c, r) == true) {
        map[pos] = MINE;
        return true;
    } else {
        int adj_mines = 0;
        if (mine_at(c - 1, r) == true) {
            adj_mines++;
        }
        if (mine_at(c + 1, r) == true) {
            adj_mines++;
        }
        if (mine_at(c, r + 1) == true) {
            adj_mines++;
        }
        if (mine_at(c - 1, r - 1) == true) {
            adj_mines++;
        }
        if (mine_at(c - 1, r + 1) == true) {
            adj_mines++;
        }
        if (mine_at(c + 1, r + 1) == true) {
            adj_mines++;
        }
        if (mine_at(c, r - 1) == true) {
            adj_mines++;
        }
        if (mine_at(c + 1, r - 1) == true) {
            adj_mines++;
        }
        map[pos] = adj_mines;

        if (map[pos] == 0) {
            if (is_inbound(c - 1, r, width, height)) {

                if (map[r * width + (c - 1)] == UNKNOWN) {

                    step_adv(c - 1, r, width, height);

                }
            }

            if (is_inbound(c + 1, r, width, height)) {
                if (map[r * width + (c + 1)] == UNKNOWN) {
                    step_adv(c + 1, r, width, height);
                }
            }

            if (is_inbound(c, r + 1, width, height)) {
                if (map[(r + 1) * width + c] == UNKNOWN) {
                    step_adv(c, r + 1, width, height); 
                }
            }

            if (is_inbound(c - 1, r + 1, width, height)) {
                if (map[(r + 1) * width + (c - 1)] == UNKNOWN) {
                    step_adv(c - 1, r + 1, width, height);
                } 
            }

            if (is_inbound(c + 1, r + 1, width, height)) {
                if (map[(r + 1) * width + (c + 1)] == UNKNOWN) {
                    step_adv(c + 1, r + 1, width, height);
                } 
            }

            if (is_inbound(c, r - 1, width, height)) {
                if (map[(r - 1) * width + c] == UNKNOWN) {
                    step_adv(c, r - 1, width, height);
                }
            }

            if (is_inbound(c + 1, r - 1, width, height)) {
                if (map[(r - 1) * width + (c + 1)] == UNKNOWN) {
                    step_adv(c + 1, r - 1, width, height);
                } 
            }

            if (is_inbound(c - 1, r - 1, width, height)) {
                if (map[(r - 1) * width + (c - 1)] == UNKNOWN) {
                    step_adv(c - 1, r - 1, width, height);
                }
            }
        }
        return false;
    }
}

// see game.h for documentation
bool mark(const int c, const int r, int width, int height) {
    const int pos = r * width + c;
    if (is_inbound(c, r, width, height) == false) {
        return false;
    } else if ((map[pos] == UNKNOWN) && (map[pos] != 0)) {
        map[pos] = MARKED;
    } else if (map[pos] == MARKED) {
        map[pos] = UNKNOWN;
    }
    if (all_marked() == true) {
        return true;
    }
    return false;
}

/// i don't understand the hintssssssss!! maybe check the boundaries!!
// see game.h for documentation
void print(int width, int height) {
    int pos = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[pos] == UNKNOWN) {
                printf("_");
            } else if (map[pos] == MARKED) {
                printf("P");
            } else if (map[pos] == MINE) {
                printf("X");
            } else {
                printf("%d", map[pos]);
            }

            if (j + 1 != width) {
                printf(" ");
            }
            pos++;
        }
        printf("\n");
    }
}
