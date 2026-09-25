# HEARTHWAKE

> A 1–4 player co-op survival-crafting game built in **Unreal Engine 5.8 (C++)**. Networking correctness is the core of this codebase.

**Status:** pre-production. The design is locked; no playable build yet. See [`docs/STATUS.md`](docs/STATUS.md).

## The pitch
You and your friends wake on a cold island where the sun barely rises. Gather, craft, and build a network of hearths to push back the frost. Night brings frost-wraiths that attack your structures.

## Technical goals
| Area | Approach |
|---|---|
| Authority | Server-authoritative: clients send validated intent through Server RPCs |
| Inventory | `FFastArraySerializer` entries; idempotent operations with request IDs |
| Building | Snap placement with a client preview, server validation, and stability computed from ground connections |
| Survival | Warmth, Hunger, Stamina and Health as a GAS attribute set |
| World | Seeded PCG resource scattering by biome; day/night time replicated through GameState |
| Sessions | Online Subsystem Null for LAN/development; Steam behind a config flag |
| Persistence | Versioned world save on the host |
| Quality | Automation tests under emulated lag and packet loss (150 ms, 2%) |

## Roadmap
- [ ] M0 Repository and project
- [ ] M1 Character and LAN host/join
- [ ] M2 Replicated inventory
- [ ] M3 Gathering and tools
- [ ] M4 Crafting and stations
- [ ] M5 Building and structural stability
- [ ] M6 Survival stats, hearths, day/night
- [ ] M7 Seeded PCG world
- [ ] M8 Night enemies
- [ ] M9 World save/load
- [ ] M10 Packaging and network profiling

## Documents
- [Game Design Document](docs/GDD.md)

## Development note
Development uses AI coding assistants under my direction and review. Commits carry honest co-author trailers, and the history is never rewritten.
