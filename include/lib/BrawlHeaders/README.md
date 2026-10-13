# BrawlHeaders
This is a repository of MWCC compatible header files for use in both decompilation and modding of Super Smash Bros. Brawl for the Nintendo Wii. (SSBB). 

## Project Goal
The goal of this project is to provide a collaborative repository for reverse engineering and documenting the game. These headers are useful for both those interested in a decomp of the game as well as modders, which are the current largest userbase for this project. As more people use tools such as Syriinge or the BrawlModules repo, the greater the scene will benefit. Users may run into things not currently documented here that they need for their project, and if they are so inclined will contribute here to the benefit of all projects using it.

These headers are specifically designed to be used with MetroWerks TRK compilers. While we make every effort for these to also be compatible with other compilers, we make no guarantees that they will work or be accurate under them. Some other compilers that we know will work with these headers include:
 - [Kuribo Clang](https://github.com/DotKuribo/llvm-project)
   - Note that at the time of writing there is a bug with the compiler which causes incorrect sizing of derived objects in specific multi-inheritance cases.

## Other Projects Using This
 - [Syriinge](https://github.com/Sammi-Husky/Syriinge)
   - Runtime hooking and plugins for Super Smash Bros. Brawl
 - [BrawlModules](https://github.com/Sammi-Husky/BrawlModules)
   - Repository for brawl module reimplementations and decomps
 - [BrawlStageModules](https://github.com/ilazoja/BrawlStageModule)
   - Custom stage modules built with C++ for completely custom functionality
 - [Brawl Decompilation](https://github.com/doldecomp/brawl)
   - A work-in-progress matching decompilation of Super Smash Bros. Brawl

## Special Thanks
This project would not be possible without the gracious contributions of many wonderful people in the Brawl Modding scene. While i can't list everyone, i've listed the contributors who have had the greatest impact on this specific repo. If you believe your name to be missing please contact me or submit a PR!

<a href = "https://github.com/Sammi-Husky/BrawlHeaders/graphs/contributors">
  <img src = "https://contrib.rocks/image?repo=Sammi-Husky/BrawlHeaders"/>
</a>

### This Project also makes use of the following open source projects:
 - [OpenRVL](https://github.com/Sammi-Husky/open_rvl), an open source reimplementation of the Revolution SDK
