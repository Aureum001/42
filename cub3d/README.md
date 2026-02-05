# cub3d Template

Minimal kick-off scaffold for the 42 cub3d project. The template focuses on a
clean directory layout, a Norm-compliant Makefile, and stub functions you can
flesh out while implementing the ray-caster.

## Layout

- include/ : public headers (see cub3d.h)
- src/     : source files split into core, parser, render, utils, bonus hooks
- maps/    : sample .cub configuration
- assets/  : placeholder texture folder (expects XPM files)
- lib/mlx/ : drop MiniLibX sources here before building

## Build

```sh
make        # build mandatory target
make bonus  # build bonus target once you implement it
make clean  # remove objects
make fclean # remove objects and binaries
```

To compile successfully you must provide a working MiniLibX installation in
`lib/mlx` and adjust the `MLX_FLAGS` variables in the Makefile if needed.

## Next Steps

1. Replace the parser stubs with full identifier and map parsing.
2. Wire input handling and the render loop to MiniLibX.
3. Implement ray-casting, texture lookup, and depth buffering.
4. Populate bonus hooks (mouse look, minimap, animated doors, etc.).

Happy coding!
