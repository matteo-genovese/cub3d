# cub3D

A small 3D engine in C: a Wolfenstein-style raycasting renderer on top of
[miniLibX](https://github.com/42Paris/minilibx-linux), with textured walls, a scene description
file and map validation.

**42 Roma Luiss — curriculum project (2025), two-person team.** Archived as delivered: study
project, not a maintained engine.

## Build

Requirements: a C compiler, GNU `make`, and the X11 development libraries
(`libx11-dev libxext-dev` on Debian/Ubuntu, `libx11 libxext` on Arch). miniLibX and libft are
vendored in `mlx/` and `libft/` and are built by the same `make`.

```bash
make            # produces ./cub3D
make clean      # objects
make fclean     # objects + binary
```

## Run

```bash
./cub3D maps/good/works.cub
```

Needs an X display (a real session, or `Xvfb`/`xvfb-run` headless).

## Controls

| Key | Action |
|---|---|
| `W` / `S` | move forward / backward |
| `A` / `D` | strafe left / right |
| `←` / `→` | rotate the view |
| `ESC` or window close | quit |

*(keycodes 119 / 115 / 97 / 100 / 65361 / 65363 / 65307 in `src/init/initialize.c`)*

## Scene file

```
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
11111111110100000000010000001
10000000000000000000000000001
10000000000000000000000000001
10000000000000000000000000001
11111111111111111111111111111
```

The texture paths and the two colours are mandatory, the map must come last, be fully enclosed by
`1` walls, and contain exactly one player start (`N`, `S`, `E` or `W`).

## How it works

- `src/rendering/dda.c` — DDA traversal of the grid from the player position along the camera
  direction, one ray per screen column; the hit distance sets the column height.
- `src/rendering/texture_draw.c` — per-pixel textured wall columns, with the texture X coordinate
  derived from the hit offset on the wall face.
- `src/rendering/move.c` — movement and rotation of the direction and camera-plane vectors, with a
  grid collision check (`is_valid_move`: walking into a `1` is refused).
- `src/parsing/` — scene reader: settings, RGB colours, texture paths, map extraction, enclosure
  validation, player position.

## Tests

`maps/good/` (17 maps) and `maps/bad/` (28 malformed maps: missing or duplicate textures, invalid
RGB, wall holes, no player / duplicated player / player on the edge, map not last, map too small,
wrong file extension…), driven by `run_all_tests.sh`, `run_good_maps.sh`, `run_bad_maps.sh` and
valgrind leak checks (`check_leaks_good.sh`, `check_leaks_bad.sh`).

Measured on the delivered code (binary built clean, each map run with a 3 s timeout under `Xvfb`):

- all 17 good maps run without crashing;
- 22 of the 28 bad maps exit with an error, as intended;
- `player_on_edge.cub` is accepted and runs;
- `wall_hole_{east,north,west}.cub` are accepted and run;
- `wall_hole_south.cub` and `wall_none.cub` **segfault** (exit 139, core dumped).

So malformed-map handling is incomplete: exactly the wall-enclosure cases the project is about are
the ones not caught. Rejecting any open edge and any map without a closed wall ring in
`src/parsing/map_validate.c`, then re-running `run_bad_maps.sh`, is the first thing to do if this
code is ever revived.

## Not implemented

No sprites, no doors, no minimap, no mouse look — the subject's mandatory part only.

## Credits

Team project: Matteo Genovese and Federico De Sisti.

Subject and assignment belong to [42](https://42.fr); this repository is a student implementation
of it. If you are a 42 student, reading this code to pass the project is on you: the school's rules
apply to you, not to this repository.
