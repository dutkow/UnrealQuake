# Quake III Arena Code Port to Unreal Engine

This project is an educational effort to port parts of **Quake III Arena's** code, originally written in C, into Unreal Engine. The goal is to integrate certain gameplay systems and mechanics from Quake III into Unreal, with a focus on movement and core game features.

The original source code for Quake III Arena can be found on id Software's GitHub:  
[https://github.com/id-Software/Quake-III-Arena](https://github.com/id-Software/Quake-III-Arena)

## Project Overview

This project consists of a plugin that can be integrated into any Unreal Engine project. Please note that the code is not in a fully usable state yet. It is currently in the process of being ported, and additional work will be needed to make it functional and ready for production use.

## Plan

The plan for porting the Quake III Arena code to Unreal Engine will evolve over time, but here is the general approach I am currently following:

1. **Add Quake III Source Code**: Integrate the Quake III Arena game source code directly into the plugin.
2. **Resolve Compilation Issues**: Address compilation errors caused by:
   - Over 25 years of time passing since the original code was written.
   - Converting the code from C to C++.
   - Compatibility issues with Unreal Engine's environment and APIs.
3. **Expose Key Elements to Unreal**: Once the game code is ported and compiling, I plan to expose gameplay oriented features to Unreal classes so that they can be accessed and utilized in Unreal projects.
4. **Port Movement Code**: As an initial step, my focus will be on porting the movement system (especially Quake-style movement) into a base pawn class in Unreal. This will serve as a foundation for future features and gameplay systems.

## Future Goals

If porting the movement code is successful and I have continued interest, I may continue to explore porting additional mechanics.
